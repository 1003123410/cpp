
// KillPSDlg.h : ͷ�ļ�
//

#pragma once


// CKillPSDlg �Ի���
class CKillPSDlg : public CDialogEx
{
// ����
public:
	CKillPSDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KILLPS_DIALOG };
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
	BOOL KillPS(DWORD id);
	BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnable = TRUE);
};
