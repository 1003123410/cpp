
// NamePipeDlg.h : ͷ�ļ�
//

#pragma once

typedef struct 
{
	HANDLE	hTread;
	HANDLE	hPipe;
	HANDLE	hEvent;
} PIPE_INSTRUCT;

#define MAX_BUFFER_LEN 4096
#define MAX_THREAD_COUNT 3

extern volatile BOOL m_run;
// CNamePipeDlg �Ի���
class CNamePipeDlg : public CDialogEx
{
// ����
public:
	CNamePipeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NAMEPIPE_DIALOG };
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
	static UINT ServerThread(LPVOID para);
	PIPE_INSTRUCT  PipeInst[MAX_THREAD_COUNT];
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
};
