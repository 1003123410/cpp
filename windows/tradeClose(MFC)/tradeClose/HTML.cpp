// HTML.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "tradeClose.h"
#include <regex>
#include "HTML.h"
#include "autoClose.h"
#include <afxinet.h>
#include <string>
#include <map>
#include <iostream>
#include <thread>
using namespace std;

// HTML �Ի���

IMPLEMENT_DYNCREATE(HTML, CDHtmlDialog)

HTML::HTML(CWnd* pParent /*=NULL*/)
: CDHtmlDialog(HTML::IDD, HTML::IDH, pParent)
, m_user_name(_T(""))
, m_seller_num_id(_T(""))
, m_login_flag(false)
, m_tb_token(_T(""))
{
	
}

HTML::~HTML()
{

}

void HTML::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL HTML::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	GetParent()->ShowWindow(SW_HIDE);
	//��ֹ���ٵ�¼
	Navigate(_T("https://login.taobao.com/member/login.jhtml?style=minisimple&disableQuickLogin=true"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(HTML, CDHtmlDialog)

END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(HTML)
	//DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	//DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()

//HTML ��Ϣ�������

HRESULT HTML::OnButtonOK(IHTMLElement* /*pElement*/)
{
	//OnOK();
	//MessageBox(_T("1111"));
	return S_OK;
}

HRESULT HTML::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	//OnCancel();
	//MessageBox(_T("1111"));
	return S_OK;
}


void HTML::OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl)
{
	CDHtmlDialog::OnDocumentComplete(pDisp, szUrl);
	CString url;
	GetCurrentUrl(url);
	if (url == _T("https://www.taobao.com/") || url == _T("https://www.taobao.com"))
	{
		Navigate(_T("https://login.taobao.com/member/login.jhtml?style=minisimple&disableQuickLogin=true"));
	}
	if (-1 != url.Find(_T("https://i.taobao.com/my_taobao.htm"))  )
	{																	
		ShowWindow(SW_HIDE);
		Navigate(_T("https://mai.taobao.com/seller_admin.htm"));
	}
	if (url == _T("https://mai.taobao.com/seller_admin.htm"))
	//��½�ɹ���ת��������ӣ�ֱ�ӱȽ�������ȷ���Ƿ��½�ɹ�
	{
		ShowWindow(SW_HIDE);
		//���ص�ǰ���ڣ���ʾmainDlg
		CComPtr<IHTMLElement>sp_name;//�û���
		HRESULT hr_name = S_OK;
		hr_name = this->GetElementInterface(_T("seller-nav"), IID_IHTMLElement, (void**)&sp_name);
		if (hr_name != S_OK)
		{
			this->MessageBox(_T("��ȡ��¼��Ϣʧ�ܣ������µ�½!"));
		}
		else
		{
			//��cookie�л�ȡuser_num_id��user_num_id���Բ�Ҫ������ʱ����ȡ
			m_seller_num_id = "";
			IHTMLDocument2 *htmld;
			GetDHtmlDocument(&htmld);
			BSTR tempCookies;
			htmld->get_cookie(&tempCookies);
			htmld->close();
			CString tempCookiesCS(tempCookies);
			int tb_token_start = tempCookiesCS.Find(_T("_tb_token_="));
			if (/*num_start != -1 &&*/ tb_token_start != -1)
			{				int tb_token_end = tempCookiesCS.Find(_T(";"), tb_token_start);
				if (tb_token_end != -1)
				{
					m_tb_token = tempCookiesCS.Mid(tb_token_start + 11, tb_token_end - tb_token_start - 11);
				}
				else
					MessageBox(_T("�û���Ϣ��ȡʧ��,�����Ի���ϵ������Ա!"));
			}
			else
				MessageBox(_T("�û���Ϣ��ȡʧ��,�����Ի���ϵ������Ա!"));
			::PostMessage(GetParent()->m_hWnd, WM_PARENT_HIDE, 0, 0);
			BSTR tempName;
			sp_name->get_innerText(&tempName);
			m_user_name = CString(tempName);
			int name_start = m_user_name.Find(_T("�����ֻ���"));
			int name_end = m_user_name.Find(_T("�˳�"));
			if (name_start == -1 || name_end == -1)
			{
				MessageBox(_T("�����û�����ȡʧ�ܣ�"));
			}
			else
			{
				m_user_name = m_user_name.Mid(name_start + 6, name_end - name_start - 8);
				m_login_flag = true;
				MessageBoxTimeout(GetSafeHwnd(), _T("��½�ɹ�!��ӭ ") + m_user_name, _T("��½�ɹ�"), MB_ICONINFORMATION, GetSystemDefaultLangID(), 2000);
				::PostMessage(GetParent()->m_hWnd, WM_USERNMECHANGED, 0, 0);
			}
		}
	}
}