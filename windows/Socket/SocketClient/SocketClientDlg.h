
// SocketClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CSocketClientDlg �Ի���
class CSocketClientDlg : public CDialogEx
{
// ����
public:
	CSocketClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCKETCLIENT_DIALOG };
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
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedOk();
	CEdit m_editSend;
	CEdit m_editRecv;
};
