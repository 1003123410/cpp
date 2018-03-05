// ViewDialog.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "ViewDialog.h"
#include "../AnalyzeHtm/AnalyzeHtm.h"

// CViewDialog �Ի���
IMPLEMENT_DYNCREATE(CViewDialog, CDHtmlDialog)

CViewDialog::CViewDialog(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog((UINT)0,0,pParent)
{
	m_bCanClose = FALSE;
}

CViewDialog::CViewDialog(UINT idDlg,UINT idHtm,const stuPaper &paper,const ePaperViewType & type,const CString & filePath,CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(idDlg,idHtm,pParent)
{
	m_filePath = filePath;
	m_type = type;
	m_pPaper = &paper;
	m_bCanClose = FALSE;
}

CViewDialog::~CViewDialog()
{
}

void CViewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL CViewDialog::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	//����js����c++����
	EnableAutomation();
	SetExternalDispatch(GetIDispatch(TRUE));	//��������
	if(m_type == ePaperViewTypePrint || m_type == ePaperViewTypeExcel)			//��ӡ���ؽ���
		SetWindowPos(&wndBottom,0,0,0,0,0);
	else                                        //ȫ��
		//SetWindowPos(&wndTopMost,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),0);
		SetWindowPos(&wndTopMost,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),SWP_NOZORDER);
	if(!m_filePath.IsEmpty())
		Navigate(m_filePath);					//����
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(CViewDialog, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CViewDialog)
	DHTML_EVENT_ONCLICK(_T("btn_close"),On_btn_close)
	DHTML_EVENT_ONCLICK(_T("btn_submit"),On_btn_submit)
END_DHTML_EVENT_MAP()
//js����c++���룬������
BEGIN_DISPATCH_MAP(CViewDialog, CDHtmlDialog)
	DISP_FUNCTION(CViewDialog, "close_window", close_window, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CViewDialog, "set_answer_score", set_answer_score, VT_EMPTY, VTS_VARIANT VTS_VARIANT VTS_VARIANT)
END_DISPATCH_MAP()

VOID CViewDialog::set_answer_score(VARIANT & row, VARIANT & col, VARIANT & value)			//���ش�����
{
	CString s;
	s.Format("func:%s row:%d col:%d value:%s", __FUNCTION__, row.intVal, col.intVal, CString(value.bstrVal));
	OutputDebugString(s);
	if (row.intVal == 1)	//Ŀǰֻ����һ��ѧ������Ϣ
		m_score.push_back(atof(CString(value.bstrVal)));
}
void CViewDialog::close_window()
{	//��ӡ��Ϻ�رմ��ڣ���Ȼ������������
	m_bCanClose = TRUE;
	OnOK();
}
// ��ʦ��Ԥ��ʱ  ����ر�ҳ��
HRESULT CViewDialog::On_btn_close(IHTMLElement* /*pElement*/)
{
	m_bCanClose = TRUE;
	OnOK();
	return S_OK;
}
//ѧ������ʱ  ����ύ��ť
HRESULT CViewDialog::On_btn_submit(IHTMLElement* /*pElement*/)
{
	CAnalyzeHtm analyze;
	analyze.GetPaperAnswer(m_answer,*m_pPaper,this);
	m_bCanClose = TRUE;
	OnOK();
	return S_OK;
}
//�������  ��ӡ
void CViewDialog::OnDocumentComplete(LPDISPATCH pDisp,LPCTSTR szUrl)
{
	CDHtmlDialog::OnDocumentComplete(pDisp,szUrl);
	if(m_type == ePaperViewTypePrint)
	{
		CString url;
		GetCurrentUrl(url);			//��ȡURL
		if(url.CompareNoCase(m_filePath.Right(m_filePath.GetLength() - 8)) == 0)	//�������
		{
			CComPtr<IHTMLElement> sp_name;
			if(GetElementInterface("btn_print",IID_IHTMLElement,(void**)&sp_name) == S_OK)//��ȡ����ӡ��ť����һ��
				sp_name->click();
		}
	}
}
//���θ����˳���ʽ��ֻ���ڵ���ض���ť���˳�
void CViewDialog::OnOK()
{
	if(m_bCanClose)
		CDHtmlDialog::OnOK();
}
void CViewDialog::OnCancel()
{
}
LRESULT CViewDialog::WindowProc(UINT message,WPARAM wParam,LPARAM lParam)
{
	if(message == WM_USER + 145)		//����Ϣֻ����ѧ����ʹ�ã�Ϊ����ѧ���ˡ���ʦ�ˡ��Ծ�༭����������Ի���ʹ����WM_USER + 145������ѧ���˶����WM_SUBMITPAPERֵ���
	{
		On_btn_submit(NULL);
		return 0;
	}
	return CDHtmlDialog::WindowProc(message,wParam,lParam);
}
//�Ҽ�����
HRESULT STDMETHODCALLTYPE CViewDialog::ShowContextMenu(DWORD dwID,POINT *ppt,IUnknown *pcmdtReserved,IDispatch *pdispReserved)
{
	return S_OK;
}