
// EnumWindowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EnumWindow.h"
#include "EnumWindowDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEnumWindowDlg �Ի���



CEnumWindowDlg::CEnumWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ENUMWINDOW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnumWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}


// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEnumWindowDlg::OnPaint()
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
HCURSOR CEnumWindowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BEGIN_MESSAGE_MAP(CEnumWindowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ENUM, &CEnumWindowDlg::OnBnClickedEnum)
	ON_BN_CLICKED(IDC_FIND, &CEnumWindowDlg::OnBnClickedFind)
	ON_BN_CLICKED(IDC_FIND_MSG, &CEnumWindowDlg::OnBnClickedFindMsg)
	ON_BN_CLICKED(ID_EXIT, &CEnumWindowDlg::OnBnClickedExit)
END_MESSAGE_MAP()

BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lParam)
{
	CEnumWindowDlg * pParent = (CEnumWindowDlg*)lParam;
	TCHAR title[MAX_PATH] = { 0 };
	if (GetWindowText(hwnd, title, sizeof(title)) > 0)
	{
		CString s;
		int pos = pParent->m_list.GetItemCount();
		s.Format(_T("%d"), pos);
		pParent->m_list.InsertItem(pos, s);
		s.Format(_T("%p"), hwnd);
		pParent->m_list.SetItemText(pos, 1, s);
		pParent->m_list.SetItemText(pos, 2, CString(title));
	}
	return true;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	CEnumWindowDlg * pParent = (CEnumWindowDlg*)lParam;
	TCHAR title[MAX_PATH] = { 0 };
	if (GetWindowText(hwnd, title, sizeof(title)))
	{
		CString s;
		int pos = pParent->m_list.GetItemCount();
		s.Format(_T("%d"), pos);
		pParent->m_list.InsertItem(pos, s);
		s.Format(_T("%p"), hwnd);
		pParent->m_list.SetItemText(pos, 1, s);
		pParent->m_list.SetItemText(pos, 2, CString(title));
	}
	EnumChildWindows(hwnd, EnumChildWindowsProc, lParam);
	return true;
}

BOOL CEnumWindowDlg::myEnumWindow(HWND hwnd)
{
	TCHAR title[MAX_PATH] = { 0 };
	HWND after = NULL;
	while (after = ::FindWindowEx(hwnd, after, NULL, NULL))
	{
		if (::GetWindowText(after, title, sizeof(title)) > 0)
		{
			CString s;
			int pos = m_list.GetItemCount();
			s.Format(_T("%d"), pos);
			m_list.InsertItem(pos, s);
			s.Format(_T("%p"), after);
			m_list.SetItemText(pos, 1, s);
			m_list.SetItemText(pos, 2, CString(title));
		}
		myEnumWindow(after);
	}
	return true;
}

// CEnumWindowDlg ��Ϣ�������
BOOL CEnumWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_list.SetExtendedStyle(m_list.GetStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rect;
	GetWindowRect(&rect);
	m_list.InsertColumn(0, _T("���"), LVCFMT_LEFT, rect.Width() / 8, 0);
	m_list.InsertColumn(1, _T("���"), LVCFMT_LEFT, rect.Width() / 4, 1);
	m_list.InsertColumn(2, _T("������"), LVCFMT_LEFT, 5 * rect.Width() / 8, 2);
	((CButton*)GetDlgItem(IDC_ENUM))->SetCheck(TRUE);
	EnumWindows(EnumWindowsProc, (LPARAM)this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CEnumWindowDlg::OnBnClickedEnum()
{
	m_list.DeleteAllItems();
	EnumWindows(EnumWindowsProc, (LPARAM)this);
}

void CEnumWindowDlg::OnBnClickedFind()
{
	m_list.DeleteAllItems();
	myEnumWindow(NULL);//ʹ��FindWindowExö�ٴ���
}

void CEnumWindowDlg::OnBnClickedFindMsg()
{
	m_list.DeleteAllItems();
	myEnumWindow(HWND_MESSAGE);//ʹ��FindWindowExö�ٴ���
}

void CEnumWindowDlg::OnBnClickedExit()
{
	CDialogEx::OnOK();
}