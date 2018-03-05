
// RebootDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Reboot.h"
#include "RebootDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRebootDlg �Ի���



CRebootDlg::CRebootDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REBOOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRebootDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRebootDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRebootDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_MESSAGE_MAP(CRebootDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, &CRebootDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_OK, &CRebootDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CRebootDlg ��Ϣ�������
BOOL CRebootDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	((CButton*)GetDlgItem(IDC_REBOOT))->SetCheck(TRUE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRebootDlg::OnBnClickedExit()
{
	CDialogEx::OnOK();
}

void CRebootDlg::OnBnClickedOk()
{
	UINT flag = 0xFFFF;
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_REBOOT))->GetCheck())
		flag = EWX_REBOOT;
	else if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_SHUTDOWN))->GetCheck())
		flag = EWX_SHUTDOWN;
	else if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_LOGOFF))->GetCheck())
		flag = EWX_LOGOFF;
	if (flag != 0xFFFF)
	{
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;
		// ��ý�������
		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
		// ��ѯ�ػ���Ȩֵ
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
		tkp.PrivilegeCount = 1;
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		// ���������ùػ���Ȩ
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
		if (GetLastError() == ERROR_SUCCESS)
			ExitWindowsEx(flag | EWX_FORCE, 0);
	}
}
