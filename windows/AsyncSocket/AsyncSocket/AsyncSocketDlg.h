
// AsyncSocketDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CAsyncSocketDlg �Ի���
class CAsyncSocketDlg : public CDialogEx
{
// ����
public:
	CAsyncSocketDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASYNCSOCKET_DIALOG };
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
	afx_msg LRESULT OnSockMsg(WPARAM wParam,LPARAM lParam);
private:
	SOCKET m_listenSock;
	SOCKET m_clientSock;
	CHAR   m_buf[2048];
public:
	CEdit m_edit;
};
