#pragma once
#include "afxcmn.h"
#include <vector>


// SelectProcess �Ի���

class SelectProcess : public CDialogEx
{
	DECLARE_DYNAMIC(SelectProcess)

public:
	SelectProcess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SelectProcess();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECTPROCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	INT m_select;
	std::vector<PPROCESS_STRUCT>m_vec;
	afx_msg void OnBnClickedSelect();
};
