
// EnumModuleDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CEnumModuleDlg �Ի���
class CEnumModuleDlg : public CDialogEx
{
// ����
public:
	CEnumModuleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENUMMODULE_DIALOG };
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
	afx_msg void OnBnClickedDll();
	CListCtrl m_list;
};
