#pragma once
#include "../PaperEditor/PaperStruct.h"
#include <map>

class CGenerateHtm
{
public:
	CGenerateHtm();
	~CGenerateHtm();

public:
	//��paper�Ծ��������htm���浽filePath�ļ� type����ʦ��Ԥ��/ѧ���˿���
	BOOL GeneratePaperToHtm(const stuPaper & paper,const CString & filePath, const ePaperViewType & type);
	//���ɴ����Ϣ����ʦ���ľ����
	BOOL GenerateAnswerToHtm(const stuPaper & paper,const std::map<CString,stuPaper> & answer,const std::map<CString,stuClientInfo> & info,const CString & filePath,const ePaperViewType & type);
	//���ɴ����Ϣ��ѧ������ʾ��
	BOOL GenerateShowAnswerHtm(const stuPaper & paper,const stuPaper & answer,const stuClientInfo & info,const CString & filePath,const ePaperViewType & type);

private:
	//����htm�ļ��ļ����� type:��ʦ��Ԥ��/ѧ���˿���
	VOID GeneratePaperHead(const stuPaper & paper,const ePaperViewType & type);
	VOID GeneratePaperCss(const stuPaper & paper,const ePaperViewType & type);
	VOID GeneratePaperJs(const stuPaper & paper,const ePaperViewType & type);
	VOID GeneratePaperBody(const stuPaper & paper,const ePaperViewType & type);
	//��htm�ļ����ζ�д���ļ�
	BOOL  WriteHtmFile(const CString & filePath,const ePaperViewType & type = ePaperViewTypeView);
	//��ʾ�𰸵�body����
	VOID GenerateShowAnswerHtmBody(const stuPaper & paper,const stuPaper & answer,const stuClientInfo & info,const ePaperViewType & type);
	//д�����ߵ�htm
	BOOL WriteAnswerMainHtm(const CString & dir,const CString & path);
	//д������JS
	VOID WriteAnswerScoreJs(const ePaperViewType & type,BOOL onLoadRun = FALSE);
	//д������htm
	BOOL WriteAnswerScoreHtm(const stuPaper & paper,const std::map<CString,stuPaper> & answer,const std::map<CString,stuClientInfo> & info,const CString & path);
	//д�������б�htm
	BOOL WriteAnswerScoreTableHtm(const stuPaper & paper,const std::map<CString,stuPaper> & answer,const std::map<CString,stuClientInfo> & info,const CString & path,const ePaperViewType & type);

private:
	CString m_head;			//ͷ
	CString m_css;			//css��
	CString m_js;			//js��
	CString m_body;			//body��
};