
// AdaptInfoDlg.h : ͷ�ļ�
//

#pragma once


// CAdaptInfoDlg �Ի���
class CAdaptInfoDlg : public CDialogEx
{
// ����
public:
	CAdaptInfoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADAPTINFO_DIALOG };
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
	afx_msg void OnBnClickedInfo();
	afx_msg void OnBnClickedAdress();
	void ShowAdaptersInfo();
	void ShowAdaptersAddresses();
};
