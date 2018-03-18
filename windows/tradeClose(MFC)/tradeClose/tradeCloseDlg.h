
// tradeCloseDlg.h : ͷ�ļ�
//
#include <vector>
using namespace std;
#pragma once
#include "HTML.h"//��������html�Ĳ���
#include "afxwin.h"
// CtradeCloseDlg �Ի���

#define TIMER1 1

class CtradeCloseDlg : public CDialogEx
{
// ����
public:
	CtradeCloseDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TRADECLOSE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	HRESULT OnButtonOK(IHTMLElement *pElement);

// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();

	//bool m_flag;
	
	HTML* m_html;
protected:
	afx_msg LRESULT OnParentHide(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnOrderChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDetailChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserNameChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStop(WPARAM wParam, LPARAM lParam);
public:

	//vector<order_list>m_order_list;
	//vector<detail>m_detail;
	//������
	CString m_order_list;
	vector<order_list>m_order_list_vector;
	map<CString, order_list>m_order_list_map;
	//�����
	CString m_detail;
	CEdit m_detailCEdit;
	map<CString, CString>m_detail_map;

	CComboBox m_reason;
	CString m_reason_cstring;
	CString m_search_name;
	CString m_tb_token;
	bool m_stop_flag;
	int m_count;
	CString m_user_name;
	int m_search_time;
	afx_msg void OnBnClickedButton1();
	//afx_msg void OnBnClickedButton2();

	// �ظ������ʱ�䣬�ر���ɺ󣬶�ʱ��ͬ��������ر�
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheck2();

	int getOrderList(CString);
	CString SendURLPost(CString strServerName, CString strFormActionUrl, CString strPostStr, CString requestType);
	int htmlToOrder(CString&html, vector<order_list>&order);
	//���ݻ�õ�URL����post��Ϣ���رս���
	int TradeClose(vector<order_list>);
	CString UrlEncode(CString strUnicode);
};