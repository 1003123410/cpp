#pragma once
#include "../PaperEditor/PaperStruct.h"
#include <vector>

#define MAX_READ_BUFFER 40960

class CLoadSavePaper
{
public:
	CLoadSavePaper();
	~CLoadSavePaper();

public:
	//����paper��path�ļ�������typeȷ�������Ծ��Ǵ𰸣��Ծ���������Ϣ����ֻ����𰸲���
	BOOL SavePaper(const stuPaper & paper, const ePaperType & type, const CString & path);
	//����path�ļ���paper������typeȷ�������Ծ��Ǵ𰸣��Ծ����������Ϣ����ֻ���ش𰸲���
	BOOL LoadPaper(stuPaper & paper, const ePaperType & type, const CString & path);

private:
	//д��str�ͷָ���
	VOID WriteSection(CStdioFile & file,const CString & str);
	//���ļ��з�Ϊ�Ӵ������浽vector��
	BOOL ReadPaperFile(const CString & path, std::vector<CString> & vec);

private:
	//�ָ���
	TCHAR m_separator;
};

