
// KillPSDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KillPS.h"
#include "KillPSDlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKillPSDlg �Ի���



CKillPSDlg::CKillPSDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_KILLPS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKillPSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKillPSDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CKillPSDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CKillPSDlg ��Ϣ�������

BOOL CKillPSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKillPSDlg::OnPaint()
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
HCURSOR CKillPSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�����ȡ��Ȩ
BOOL CKillPSDlg::SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnable)
{
	OutputDebugString(lpszPrivilege);
	BOOL bRet = FALSE;
	HANDLE hToken = NULL;
	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ::GetCurrentProcessId());
	if (!::OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		goto __EXIT;
	}
	LUID Luid;
	if (!::LookupPrivilegeValue(NULL, lpszPrivilege, &Luid))
	{
		goto __EXIT;
	}
	TOKEN_PRIVILEGES newPrivilege;
	newPrivilege.PrivilegeCount = 1;
	newPrivilege.Privileges[0].Luid = Luid;
	newPrivilege.Privileges[0].Attributes = //������Ȩ����
		bEnable ?
		SE_PRIVILEGE_ENABLED :
		SE_PRIVILEGE_ENABLED_BY_DEFAULT;
	if (!::AdjustTokenPrivileges(hToken, FALSE, &newPrivilege,
		sizeof(TOKEN_PRIVILEGES), NULL, NULL))
	{
		CString s;
		s.Format(_T("AdjustTokenPrivileges error: %u\n"), GetLastError());
		OutputDebugString(s);
		goto __EXIT;
	}
	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)//�鿴�Ƿ�������óɹ���
	{
		OutputDebugString(_T("The token does not have the specified privilege. \n"));
		goto __EXIT;
	}
	bRet = TRUE;
	OutputDebugString(_T("Set OK"));
__EXIT:
	if (hProcess)
	{
		::CloseHandle(hProcess);
	}
	if (hToken)
	{
		::CloseHandle(hToken);
	}
	return bRet;
}

BOOL CKillPSDlg::KillPS(DWORD id)
{
	HANDLE hProcess = NULL, hProcessToken = NULL;
	BOOL IsKilled = FALSE, bRet = FALSE;
	if ((hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id)) != NULL)
	{
		if (TerminateProcess(hProcess, 1))
		{
			return TRUE;
		}
	}
	__try
	{
		SetPrivilege(SE_DEBUG_NAME, TRUE);
		if ((hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id)) == NULL)
		{
			printf("\nOpen Process %d failed:%d", id, GetLastError());
			__leave;
		}
		//printf("\nOpen Process %d ok!",id);
		if (!TerminateProcess(hProcess, 1))
		{
			printf("\nTerminateProcess failed:%d", GetLastError());
			__leave;
		}
		IsKilled = TRUE;
	}
	__finally
	{
		if (hProcessToken != NULL) CloseHandle(hProcessToken);
		if (hProcess != NULL) CloseHandle(hProcess);
	}
	return(IsKilled);
}

void CKillPSDlg::OnBnClickedOk()
{
	CString name;
	GetDlgItemText(IDC_EDIT1, name);
	if (!name.IsEmpty())
	{
		PROCESSENTRY32 pe;
		auto handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(handle, &pe))
		{
			while (TRUE)
			{
				pe.dwSize = sizeof(PROCESSENTRY32);
				if (!Process32Next(handle, &pe))
					break;
				if (CString(pe.szExeFile).CompareNoCase(name) == 0)
				{
					KillPS(pe.th32ProcessID);
				}
			}
		}
		CloseHandle(handle);
	}
	CDialogEx::OnOK();
}
