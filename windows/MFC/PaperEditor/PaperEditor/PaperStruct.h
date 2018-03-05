#pragma once
#include <vector>

enum ePaperType				  //�Ծ�������
{
	ePaperTypePaper = 0,	  //�Ծ�
	ePaperTypeAnswer		  //��
};

enum eTopicType				  //��Ŀ����
{
	eTopicTypeSelect = 0,	  //ѡ����
	eTopicTypeBlank,		  //�����
	eTopicTypeQA,			  //�ʴ���
	eTopicTypeNone			  //��
};

enum ePaperViewType			  //�Ծ���������
{
	ePaperViewTypeView = 0,	  //��ʦ��Ԥ��
	ePaperViewTypePrint,	  //��ʦ�˴�ӡ
	ePaperViewTypeExam,		  //ѧ���˿���
	ePaperViewTypeScore,	  //��ʦ�˸���
	ePaperViewTypeShowAns,    //ѧ������ʾ��
	ePaperViewTypeExcel		  //��ʦ�˱���Ϊexcel
};

enum eScoreType				  //������������
{
	eScoreTypeAverage = 0,	  //ƽ��
	eScoreTypeSingle,		  //������Ŀ����
	eScoreTypeBatch			  //����������������
};

struct stuTopic		  //����ṹ
{
	stuTopic()
	{
		m_type = eTopicTypeSelect;
		m_selectNum = 4;	  //��ѡ
		m_score = 100;
		m_checkA = m_checkB = m_checkC = m_checkD = m_checkE = BST_UNCHECKED;
		m_title = m_ans = m_ansA = m_ansB = m_ansC = m_ansD = m_ansE = CString();
	}
	eTopicType  m_type;       //��������
	double      m_score;      //����
	int			m_selectNum;  //ѡ����ѡ������
	int			m_checkA;	  //Aѡ�� BST_CHECKED BST_UNCHECKED
	int			m_checkB;	  //
	int			m_checkC;	  //
	int			m_checkD;	  //
	int			m_checkE;	  //
	CString		m_title;	  //��Ŀ����
	CString		m_ans;		  //��
	CString		m_ansA;		  //ѡ�����
	CString		m_ansB;		  //
	CString		m_ansC;		  //
	CString		m_ansD;		  //
	CString		m_ansE;		  //
	std::vector<CString> m_files;//�ļ�	
	bool operator == (const stuTopic& other) const//���رȽ������
	{
		return ((m_type == other.m_type) && (m_selectNum == other.m_selectNum) && (m_score == other.m_score) && (m_checkA == other.m_checkA) && (m_checkB == other.m_checkB) && (m_checkC == other.m_checkC) && (m_checkD == other.m_checkD) && (m_checkE == other.m_checkE) && (m_title == other.m_title) && (m_ans == other.m_ans) && (m_ansA == other.m_ansA) && (m_ansB == other.m_ansB) && (m_ansC == other.m_ansC) && (m_ansD == other.m_ansD) && (m_ansE == other.m_ansE) && (m_files == other.m_files));
	}
	//�жϵ�ǰ��Ŀ�ǲ��ǵ�ѡ��
	BOOL IsSingleChoice()
	{
		if (m_type == eTopicTypeSelect)
		{
			std::vector<int> vec;
			vec.push_back(m_checkA);		//����ѡ��
			vec.push_back(m_checkB);
			if (m_selectNum > 2)
				vec.push_back(m_checkC);
			if (m_selectNum > 3)
				vec.push_back(m_checkD);
			if (m_selectNum > 4)
				vec.push_back(m_checkE);
			int count = 0;
			for (size_t i = 0;i < vec.size();++i)
				if (vec[i] == BST_CHECKED)
					++count;
			if (count == 1)					//ֻѡ��һ��
				return TRUE;
		}
		return FALSE;
	}
};

struct stuScoreSet                        //�������ýṹ
{
	stuScoreSet()
	{
		m_type = eScoreTypeAverage;
		m_total = 100;
		m_batch[0] = m_batch[1] = m_batch[2] = m_batch[3] = 0;
	}
	eScoreType			m_type;			//��������
	double				m_total;		//ƽ��������ܷ�
	double				m_batch[4];		//��ѡ����ѡ����ա��ʴ� �ܷ�
	std::vector<double> m_vecSigle;		//��ÿ���ⵥ�����÷���
};

struct stuPaper				//�Ծ�ṹ
{
	stuPaper()
	{
		m_timeStamp = 0;
		m_stuName = m_stuID = m_paperTitle = CString();
	}
	int					  m_timeStamp;		  //ʱ�������ʾһ������
	CString				  m_stuName;		  //ѧ������
	CString				  m_stuID;            //ѧ��ѧ��
	CString				  m_paperTitle;	      //�Ծ���
	std::vector<CString>  m_paperFiles;	      //�Ծ����ļ�
	std::vector<stuTopic> m_vecTopic;		  //�Ծ���Ŀ
	stuScoreSet           m_scoreSet;		  //��������
	bool operator == (const stuPaper& other) const //���رȽ�����������ڱȽ������Ծ��Ƿ���ͬ
	{
		return ((m_paperTitle == other.m_paperTitle) && (m_paperFiles == other.m_paperFiles) && (m_vecTopic == other.m_vecTopic));
	}
	double GetTotalScore()
	{
		double score = 0.0;
		for (size_t i = 0;i < m_vecTopic.size();++i)
			score += m_vecTopic[i].m_score;
		return score;
	}
};

struct stuClientInfo		//ѧ������Ϣ
{
	stuClientInfo()
	{
		m_ip = m_mac = m_pcName = CString();
	}
	stuClientInfo(const CString & ip,const CString & mac,const CString & name)
	{
		m_ip = ip;
		m_mac = mac;
		m_pcName = name;
	}
	CString m_ip;			//ip
	CString m_mac;			//mac
	CString m_pcName;		//�������
};