
// TrayAndBubbleDlg.h : ͷ�ļ�
//

#pragma once


// CTrayAndBubbleDlg �Ի���
class CTrayAndBubbleDlg : public CDialogEx
{
// ����
public:
	CTrayAndBubbleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRAYANDBUBBLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	BOOL AddRemoveTray(BOOL flag);
	NOTIFYICONDATA m_tray;
	BOOL ShowBubbleTip(LPCTSTR lpTitle, LPCTSTR lpText, DWORD infoflags);
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNotifyicon(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
