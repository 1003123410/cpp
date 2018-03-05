
// SuspendProcessDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CSuspendProcessDlg �Ի���
class CSuspendProcessDlg : public CDialogEx
{
// ����
public:
	CSuspendProcessDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUSPENDPROCESS_DIALOG };
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
	afx_msg void OnBnClickedSuspend();
	afx_msg void OnBnClickedResume();
	afx_msg void OnBnClickedOk();
	CListCtrl m_list;
private:
	void ControlProcess(BOOL suspend = TRUE)const;
};
