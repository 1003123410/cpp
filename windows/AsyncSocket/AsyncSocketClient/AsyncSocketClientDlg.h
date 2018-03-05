
// AsyncSocketClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CAsyncSocketClientDlg �Ի���
class CAsyncSocketClientDlg : public CDialogEx
{
// ����
public:
	CAsyncSocketClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASYNCSOCKETCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedSend();
	afx_msg LRESULT OnSockMsg(WPARAM wParam, LPARAM lParam);
	CEdit m_editSend;
	CEdit m_edit;
	SOCKET m_sock;
	CHAR m_buf[2048];
};
