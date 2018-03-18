#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CDHtmlDialog��"
#endif 
#include "resource.h"

#include<vector>

#define WM_PARENT_HIDE WM_USER+1
#define WM_ORDERCHANGED WM_USER+2
#define WM_DETAILCHANGED WM_USER+3
#define WM_USERNMECHANGED WM_USER+4
#define WM_STOP WM_USER+5
#include <map>
// HTML �Ի���

using namespace std;

typedef struct order_list
{
	CString m_name;//���װ�������
	CString m_number;//���װ������
	CString m_url;//���װ����
	CString m_time;//���װ��������ʱ��
}order_list;

// typedef struct detail
// {
// 	CString m_reason;
// 	CString m_statu;
// }detail;

class HTML : public CDHtmlDialog
{
	DECLARE_DYNCREATE(HTML)

public:
	HTML(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~HTML();
// ��д
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// �Ի�������
	enum { IDD = IDD_HTML, IDH = IDR_HTML_HTML };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()

	void OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl);
public:
	CString m_user_name;
protected:
public:
	CString m_seller_num_id;
	// ��½�Ƿ�ɹ�
	bool m_login_flag;
	// ���������cookie�л�ȡ����Ҫpost��ȥ��
	CString m_tb_token;
};
