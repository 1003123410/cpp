
// SuspendProcessDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SuspendProcess.h"
#include "SuspendProcessDlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSuspendProcessDlg �Ի���



CSuspendProcessDlg::CSuspendProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SUSPENDPROCESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSuspendProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}


// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSuspendProcessDlg::OnPaint()
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
HCURSOR CSuspendProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BEGIN_MESSAGE_MAP(CSuspendProcessDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SUSPEND, &CSuspendProcessDlg::OnBnClickedSuspend)
	ON_BN_CLICKED(IDC_RESUME, &CSuspendProcessDlg::OnBnClickedResume)
	ON_BN_CLICKED(IDOK, &CSuspendProcessDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CSuspendProcessDlg ��Ϣ�������
BOOL CSuspendProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	CRect rect;
	m_list.GetWindowRect(&rect);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, _T("����ID"), LVCFMT_LEFT, rect.Width() / 4, 0);
	m_list.InsertColumn(1, _T("������"), LVCFMT_LEFT, 3 * rect.Width() / 5, 1);
	PROCESSENTRY32 pe;
	auto handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (handle != INVALID_HANDLE_VALUE)
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(handle, &pe))
			return FALSE;
		CString s;
		int item = 0;
		while (TRUE)
		{
			pe.dwSize = sizeof(PROCESSENTRY32);
			if (!Process32Next(handle, &pe))
				break;
			s.Format(_T("%u"), pe.th32ProcessID);
			m_list.InsertItem(item, s);
			m_list.SetItemText(item, 1, pe.szExeFile);
			++item;
		}
		CloseHandle(handle);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSuspendProcessDlg::OnBnClickedSuspend()
{
	ControlProcess();
}

void CSuspendProcessDlg::OnBnClickedResume()
{
	ControlProcess(FALSE);
}

void CSuspendProcessDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void CSuspendProcessDlg::ControlProcess(BOOL suspend)const
{
	auto pos = m_list.GetFirstSelectedItemPosition();
	if (!pos)
		return;
	int item = m_list.GetNextSelectedItem(pos);
	if (item < 0)
		return;
	CString sPid = m_list.GetItemText(item, 0);
	int pId = _ttoi(sPid);
	if (pId <= 0)
		return;
	auto hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pId);
	if (INVALID_HANDLE_VALUE == hSnap)
		return;
	THREADENTRY32 th32;
	ZeroMemory(&th32, sizeof(th32));
	th32.dwSize = sizeof(th32);
	BOOL ret = Thread32First(hSnap, &th32);
	while (ret)
	{
		if (th32.th32OwnerProcessID == pId)
		{
			auto hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, th32.th32ThreadID);
			if (hThread != INVALID_HANDLE_VALUE)
			{
				if (suspend)
				{
					if (SuspendThread(hThread) != -1)
						OutputDebugString(_T("SuspendThread ok"));
				}
				else
				{
					if (ResumeThread(hThread) != -1)
						OutputDebugString(_T("ResumeThread ok"));
				}
				CloseHandle(hThread);
			}
		}
		ret = Thread32Next(hSnap, &th32);
	}
	CloseHandle(hSnap);
}