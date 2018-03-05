#include "stdafx.h"
#include "LoadSavePaper.h"

CLoadSavePaper::CLoadSavePaper()
{
	m_separator = 0;
}

CLoadSavePaper::~CLoadSavePaper()
{
}
//д��str�ͷָ���
VOID CLoadSavePaper::WriteSection(CStdioFile & file, const CString & str)
{
	file.WriteString(str);
	file.Write(&m_separator,sizeof(TCHAR));
}
//����paper��path�ļ�������typeȷ�������Ծ��Ǵ𰸣��Ծ���������Ϣ����ֻ����𰸲���
BOOL CLoadSavePaper::SavePaper(const stuPaper & paper, const ePaperType & type, const CString & path)
{
	CStdioFile file;
	CString str;
	if (file.Open(path, CFile::modeCreate | CFile::modeWrite))
	{
		file.SetLength(0);
		file.SeekToBegin();
		str.Format("%08d", paper.m_timeStamp);	  //�̶�����8λ
		WriteSection(file,str);
		if (type == ePaperTypeAnswer)				//��д��ѧ��ѧ������
		{
			WriteSection(file,paper.m_stuName);
			WriteSection(file,paper.m_stuID);
		}
		WriteSection(file,paper.m_paperTitle);
		str.Format("%d",paper.m_paperFiles.size());				//��������
		WriteSection(file,str);
		for(size_t i = 0; i < paper.m_paperFiles.size(); ++i)		//�Ծ����ļ�
			WriteSection(file,paper.m_paperFiles[i]);
		str.Format("%d",paper.m_scoreSet.m_type);					//�������� ����
		WriteSection(file,str);
		if (paper.m_scoreSet.m_type == eScoreTypeAverage)			//ƽ������
		{
			str.Format("%.2lf", paper.m_scoreSet.m_total);
			WriteSection(file, str);
		}
		else if (paper.m_scoreSet.m_type == eScoreTypeBatch)		//��������
		{
			for (int i = 0;i < 4;++i)								//���ͷ���
			{
				str.Format("%.2lf", paper.m_scoreSet.m_batch[i]);
				WriteSection(file, str);
			}
		}
		else if (paper.m_scoreSet.m_type == eScoreTypeSingle)		//��������
		{
			str.Format("%d", paper.m_scoreSet.m_vecSigle.size());	//����
			WriteSection(file, str);
			for (size_t i = 0;i < paper.m_scoreSet.m_vecSigle.size();++i)	//����
			{
				str.Format("%.2lf", paper.m_scoreSet.m_vecSigle[i]);
				WriteSection(file, str);
			}
		}
		for (size_t i = 0; i < paper.m_vecTopic.size(); ++i)		//�Ծ���Ŀ
		{
			str.Format("%d", paper.m_vecTopic[i].m_type);			//����
			WriteSection(file, str);
			WriteSection(file, paper.m_vecTopic[i].m_title);		//��Ŀ
			str.Format("%.2lf", paper.m_vecTopic[i].m_score);		//����
			WriteSection(file, str);
			if (paper.m_vecTopic[i].m_type == eTopicTypeSelect)		//ѡ��
			{
				str.Format("%d", paper.m_vecTopic[i].m_selectNum);	//ѡ������
				WriteSection(file, str);
				str.Format("%d", paper.m_vecTopic[i].m_checkA);		//Aѡ��
				WriteSection(file, str);
				WriteSection(file, paper.m_vecTopic[i].m_ansA);
				str.Format("%d", paper.m_vecTopic[i].m_checkB);
				WriteSection(file, str);
				WriteSection(file, paper.m_vecTopic[i].m_ansB);
				if (paper.m_vecTopic[i].m_selectNum > 2)
				{
					str.Format("%d", paper.m_vecTopic[i].m_checkC);
					WriteSection(file, str);
					WriteSection(file, paper.m_vecTopic[i].m_ansC);
				}
				if (paper.m_vecTopic[i].m_selectNum > 3)
				{
					str.Format("%d", paper.m_vecTopic[i].m_checkD);
					WriteSection(file, str);
					WriteSection(file, paper.m_vecTopic[i].m_ansD);
				}
				if (paper.m_vecTopic[i].m_selectNum > 4)
				{
					str.Format("%d", paper.m_vecTopic[i].m_checkE);
					WriteSection(file, str);
					WriteSection(file, paper.m_vecTopic[i].m_ansE);
				}
			}
			else                                                    //�ʴ����յĴ�
				WriteSection(file, paper.m_vecTopic[i].m_ans);
			str.Format("%d", paper.m_vecTopic[i].m_files.size());				//��Ŀ��������
			WriteSection(file, str);
			for (size_t j = 0; j < paper.m_vecTopic[i].m_files.size(); ++j)		//��Ŀ�����ļ�
				WriteSection(file, paper.m_vecTopic[i].m_files[j]);
		}
		file.Close();
		return TRUE;
	}
	return FALSE;
}
//����path�ļ���paper������typeȷ�������Ծ��Ǵ𰸣��Ծ����������Ϣ����ֻ���ش𰸲���
BOOL CLoadSavePaper::LoadPaper(stuPaper & paper, const ePaperType & type, const CString & path)
{
	std::vector<CString> vec;
	if (!ReadPaperFile(path, vec))								//��ȡ����ȡ�Ӵ�
		return FALSE;
	if (vec.size() > 0)
		paper.m_timeStamp = atoi(vec[0]);						//ʱ��
	size_t pos = 1;												//vecλ��
	if (type == ePaperTypeAnswer)								//���
	{
		if (vec.size() > 1)										//ѧ������
			paper.m_stuName = vec[1];
		if (vec.size() > 2)
			paper.m_stuID = vec[2];
		pos = 3;
	}
	if (vec.size() > pos)										//�Ծ���
		paper.m_paperTitle = vec[pos];
	++pos;
	int fileNum = 0;											//�Ծ�������
	if (vec.size() > pos)
		fileNum = atoi(vec[pos]);
	++pos;
	for (int i = 0;i < fileNum && pos + i < vec.size();++i, ++pos)//�Ծ���
		paper.m_paperFiles.push_back(vec[pos]);
	if (vec.size() > pos)										//�Ծ��������
		paper.m_scoreSet.m_type = (eScoreType)atoi(vec[pos]);
	++pos;
	if (paper.m_scoreSet.m_type == eScoreTypeAverage)			//ƽ������
	{
		if (vec.size() > pos)
			paper.m_scoreSet.m_total = atof(vec[pos]);
		++pos;
	}
	else if (paper.m_scoreSet.m_type == eScoreTypeBatch)		//��������
	{
		for (size_t i = 0;i < 4 && pos < vec.size();++pos, ++i)
			paper.m_scoreSet.m_batch[i] = atof(vec[pos]);
	}
	else if (paper.m_scoreSet.m_type == eScoreTypeSingle)		//��������
	{
		int num = 0;											//������Ŀ������
		if (vec.size() > pos)									
			num = atoi(vec[pos]);
		++pos;
		for (int i = 0;i < num && pos + i < vec.size();++i, ++pos)//ÿ����Ŀ��Ӧ�ķ�������
			paper.m_scoreSet.m_vecSigle.push_back(atof(vec[pos]));
	}
	for (;pos < vec.size();++pos)
	{
		paper.m_vecTopic.push_back(stuTopic());
		paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_type = (eTopicType)atoi(vec[pos]);//����
		++pos;
		if (pos < vec.size())
			paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_title = vec[pos];			  //��Ŀ
		++pos;
		if (pos < vec.size())
			paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_score =atof(vec[pos]);		  //����
		++pos;
		if (paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_type == eTopicTypeSelect)	  //ѡ��
		{
			if (pos < vec.size())
				paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_selectNum = atoi(vec[pos]);	//ѡ��
			++pos;
			if (pos < vec.size())
				paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_checkA = atoi(vec[pos]);
			++pos;
			if (pos < vec.size())
				paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_ansA = vec[pos];
			++pos;
			if (pos < vec.size())
				paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_checkB = atoi(vec[pos]);
			++pos;
			if (pos < vec.size())
				paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_ansB = vec[pos];
			if (paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_selectNum > 2)			//ѡ�����2
			{
				++pos;
				if (pos < vec.size())
					paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_checkC = atoi(vec[pos]);
				++pos;
				if (pos < vec.size())
					paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_ansC = vec[pos];
			}
			if (paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_selectNum > 3)			//ѡ�����3
			{
				++pos;
				if (pos < vec.size())
					paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_checkD = atoi(vec[pos]);
				++pos;
				if (pos < vec.size())
					paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_ansD = vec[pos];
			}
			if (paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_selectNum > 4)			////ѡ�����4
			{
				++pos;
				if (pos < vec.size())
					paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_checkE = atoi(vec[pos]);
				++pos;
				if (pos < vec.size())
					paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_ansE = vec[pos];
			}
		}
		else                              //��ա��ʴ� ��
		{
			if (pos < vec.size())
				paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_ans = vec[pos];
		}
		++pos;
		if (pos < vec.size())		       //��Ŀ��������
			fileNum = atoi(vec[pos]);
		++pos;
		for (int j = 0;j < fileNum && pos + j < vec.size();++j, ++pos)	//��Ŀ����
			paper.m_vecTopic[paper.m_vecTopic.size() - 1].m_files.push_back(vec[pos]);
		--pos;
	}
	return TRUE;
}
//���ļ��з�Ϊ�Ӵ������浽vector��
BOOL CLoadSavePaper::ReadPaperFile(const CString & path, std::vector<CString> & vec)
{
	CFileFind finder;
	if (!finder.FindFile(path))										//ȷ���ļ�����
		return FALSE;
	finder.Close();
	CFile file;
	if (file.Open(path, CFile::modeRead))
	{
		file.SeekToBegin();
		char buf[MAX_READ_BUFFER] = { 0 };		//40kb
		CString str;
		UINT readLen = 0;
		while ((readLen = file.Read(buf, MAX_READ_BUFFER)) > 0)    //�����ȡ������buffer����Ӵ���������
		{
			UINT posStart = 0;
			for (UINT i = 0;i < readLen;++i)
			{
				if (m_separator == buf[i])								//����Ѱ�ұ��
				{
					str.Format("%s", buf + posStart);				//��ʽ���������Ӵ�
					vec.push_back(str);
					posStart = i + 1;									//������ʼλ�ü�¼
				}
			}
			file.Seek(file.GetPosition() - readLen + posStart, 0);	//���´���һ����Ǻ��ȡ
			ZeroMemory(buf, MAX_READ_BUFFER);						//��ջ���
		}
		file.Close();
		return TRUE;
	}
	return FALSE;
}