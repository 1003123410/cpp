#pragma once
#include "../PaperEditor/PaperStruct.h"

//����htm�������Ծ��
class CAnalyzeHtm
{
public:
	CAnalyzeHtm();
	~CAnalyzeHtm();

public:
	//��ȡ�Ծ��
	VOID GetPaperAnswer(stuPaper & answer,const stuPaper & paper,CDHtmlDialog * dlg);

private:
	//��ȡָ��ID�� html ���� text��<p><h><textArea>��ǩ��
	BOOL GetElementText(CString & str,const CString & id,CDHtmlDialog * dlg);
	//��ȡָ��ID�� Input �ؼ���ֵ���������
	BOOL GetInputElementText(CString & str,const CString & id,CDHtmlDialog * dlg);
	//��ȡָ��ID�� checkbox �ؼ��� check ״̬ ���� TRUE��checked FALSE:unchecked
	BOOL GetCheckElementState(const CString & id,CDHtmlDialog * dlg);
};

