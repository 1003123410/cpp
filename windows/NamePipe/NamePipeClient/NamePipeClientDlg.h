
// NamePipeClientDlg.h : ͷ�ļ�
//

#pragma once
#define MAX_BUFFER_LEN 4096

// CNamePipeClientDlg �Ի���
class CNamePipeClientDlg : public CDialogEx
{
// ����
public:
	CNamePipeClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NAMEPIPECLIENT_DIALOG };
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
};
