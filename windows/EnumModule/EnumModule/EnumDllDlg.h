#pragma once
#include "afxcmn.h"
#include "tlhelp32.h"


// CEnumDllDlg �Ի���

class CEnumDllDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEnumDllDlg)

public:
	CEnumDllDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEnumDllDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	int m_pID;
};
