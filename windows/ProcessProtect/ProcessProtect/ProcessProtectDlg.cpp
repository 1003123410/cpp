
// ProcessProtectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProcessProtect.h"
#include "ProcessProtectDlg.h"
#include "afxdialogex.h"
#include "SelectProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProcessProtectDlg �Ի���



CProcessProtectDlg::CProcessProtectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PROCESSPROTECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProcessProtectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}
// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CProcessProtectDlg::OnPaint()
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
HCURSOR CProcessProtectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_MESSAGE_MAP(CProcessProtectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CProcessProtectDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_EXIT, &CProcessProtectDlg::OnBnClickedExit)
	ON_MESSAGE(WM_PROCESSEND, &CProcessProtectDlg::OnProcessend)
END_MESSAGE_MAP()

// CProcessProtectDlg ��Ϣ�������
BOOL CProcessProtectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	CRect rect;
	m_list.GetWindowRect(&rect);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, _T("ID"), LVCFMT_LEFT, rect.Width() / 15, 0);
	m_list.InsertColumn(1, _T("���"), LVCFMT_LEFT, 2 * rect.Width() / 15, 1);
	m_list.InsertColumn(2, _T("������"), LVCFMT_LEFT, 3 * rect.Width() / 15, 2);
	m_list.InsertColumn(3, _T("·��"), LVCFMT_LEFT, 8 * rect.Width() / 15, 3);
	AfxBeginThread(CheckProc, this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

UINT CProcessProtectDlg::CheckProc(LPVOID param)
{
	CProcessProtectDlg * pParent = (CProcessProtectDlg *)param;
	HANDLE handles[20] = { 0 };
	handles[0] = CreateEvent(NULL, TRUE, FALSE, NULL);
	handles[1] = CreateEvent(NULL, TRUE, FALSE, NULL);
	pParent->m_processList[0].hProcess = handles[0];
	pParent->m_processList[1].hProcess = handles[1];
	pParent->m_hExit = handles[0];
	pParent->m_hAdd = handles[1];
	pParent->m_listUse = 2;
	int count = pParent->m_listUse;
	CString s;
	while (TRUE)
	{
		DWORD ret = WaitForMultipleObjects(count, handles, FALSE, INFINITE);
		ret -= WAIT_OBJECT_0;
		if(ret == 0)//����
			break;
		else if (ret == 1)//��ӽ���
		{
			ResetEvent(handles[ret]);
			++pParent->m_listUse;
			count = pParent->m_listUse;
			handles[count - 1] = pParent->m_processList[pParent->m_listUse - 1].hProcess;
		}
		else if (ret > 1 && ret < 20)//���̽���
		{
			SHELLEXECUTEINFO sei;
			ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));
			sei.cbSize = sizeof(SHELLEXECUTEINFO);
			sei.lpFile = pParent->m_processList[pParent->m_listUse - 1].path;
			sei.nShow = SW_SHOWDEFAULT;
			sei.fMask = SEE_MASK_NOCLOSEPROCESS;
			sei.lpVerb = _T("open");
			CloseHandle(handles[count - 1]);
			if (ShellExecuteEx(&sei))
			{
				pParent->m_processList[pParent->m_listUse - 1].hProcess = sei.hProcess;
				pParent->m_processList[pParent->m_listUse - 1].PID = GetProcessId(sei.hProcess);
				handles[count - 1] = sei.hProcess;
			}
			else
			{
				--pParent->m_listUse;
				count = pParent->m_listUse;
			}
			pParent->PostMessage(WM_PROCESSEND, 0, 0);
		}
	}
	CloseHandle(pParent->m_processList[0].hProcess);
	CloseHandle(pParent->m_processList[1].hProcess);
	return 0;
}

void CProcessProtectDlg::OnBnClickedAdd()
{
	SelectProcess dlg;
	dlg.DoModal();
	if (dlg.m_select != -1)
	{
		m_processList[m_listUse].hProcess = dlg.m_vec[dlg.m_select]->hProcess;
		m_processList[m_listUse].PID = dlg.m_vec[dlg.m_select]->PID;
		memcpy_s(m_processList[m_listUse].name, sizeof(m_processList[m_listUse].name), dlg.m_vec[dlg.m_select]->name, sizeof(dlg.m_vec[dlg.m_select]->name));
		memcpy_s(m_processList[m_listUse].path, sizeof(m_processList[m_listUse].path), dlg.m_vec[dlg.m_select]->path, sizeof(dlg.m_vec[dlg.m_select]->path));
		int pos = m_list.GetItemCount();
		if (pos > -1)
		{
			CString s;
			s.Format(_T("%u"), m_processList[m_listUse].PID);
			m_list.InsertItem(pos, s);
			s.Format(_T("%p"), m_processList[m_listUse].hProcess);
			m_list.SetItemText(pos, 1, s);
			m_list.SetItemText(pos, 2, m_processList[m_listUse].name);
			m_list.SetItemText(pos, 3, m_processList[m_listUse].path);
		}
		SetEvent(m_hAdd);
	}
}

void CProcessProtectDlg::OnBnClickedExit()
{
	SetEvent(m_hExit);
	CDialogEx::OnOK();
}

afx_msg LRESULT CProcessProtectDlg::OnProcessend(WPARAM wParam, LPARAM lParam)
{
	m_list.DeleteAllItems();
	CString s;
	for (int i = 2;i < m_listUse;++i)
	{
		s.Format(_T("%u"), m_processList[i].PID);
		m_list.InsertItem(i - 2, s);
		s.Format(_T("%p"), m_processList[i].hProcess);
		m_list.SetItemText(i - 2, 1, s);
		m_list.SetItemText(i - 2, 2, m_processList[i].name);
		m_list.SetItemText(i - 2, 3, m_processList[i].path);
	}
	return 0;
}
