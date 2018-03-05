
// EnumWindowDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CEnumWindowDlg �Ի���
class CEnumWindowDlg : public CDialogEx
{
// ����
public:
	CEnumWindowDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENUMWINDOW_DIALOG };
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
	afx_msg void OnBnClickedEnum();
	afx_msg void OnBnClickedFind();
	BOOL myEnumWindow(HWND hwnd);
	afx_msg void OnBnClickedFindMsg();
	afx_msg void OnBnClickedExit();
};
