
// EnumServiceDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CEnumServiceDlg �Ի���
class CEnumServiceDlg : public CDialogEx
{
// ����
public:
	CEnumServiceDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENUMSERVICE_DIALOG };
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
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedDriver();
	afx_msg void OnBnClickedWin32();
	CListCtrl m_list;
	VOID ShowServiceStatus(DWORD type);
};
