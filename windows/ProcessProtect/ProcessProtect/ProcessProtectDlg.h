
// ProcessProtectDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CProcessProtectDlg �Ի���
class CProcessProtectDlg : public CDialogEx
{
// ����
public:
	CProcessProtectDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESSPROTECT_DIALOG };
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
	CListCtrl m_list;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedExit();
	PROCESS_STRUCT m_processList[20];
	INT m_listUse;
	HANDLE m_hExit;
	HANDLE m_hAdd;
	static UINT CheckProc(LPVOID param);
protected:
	afx_msg LRESULT OnProcessend(WPARAM wParam, LPARAM lParam);
};
