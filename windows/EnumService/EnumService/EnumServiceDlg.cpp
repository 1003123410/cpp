
// EnumServiceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EnumService.h"
#include "EnumServiceDlg.h"
#include "afxdialogex.h"
#include <winsvc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEnumServiceDlg �Ի���



CEnumServiceDlg::CEnumServiceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ENUMSERVICE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnumServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEnumServiceDlg::OnPaint()
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
HCURSOR CEnumServiceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BEGIN_MESSAGE_MAP(CEnumServiceDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CEnumServiceDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CEnumServiceDlg::OnBnClickedStop)
	ON_BN_CLICKED(ID_EXIT, &CEnumServiceDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_DRIVER, &CEnumServiceDlg::OnBnClickedDriver)
	ON_BN_CLICKED(IDC_WIN32, &CEnumServiceDlg::OnBnClickedWin32)
END_MESSAGE_MAP()

// CEnumServiceDlg ��Ϣ�������
BOOL CEnumServiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	((CButton*)GetDlgItem(IDC_WIN32))->SetCheck(TRUE);
	CRect rect;
	m_list.GetWindowRect(&rect);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, _T("������"), LVCFMT_LEFT, rect.Width() / 4, 0);
	m_list.InsertColumn(1, _T("����"), LVCFMT_LEFT, 5*rect.Width() / 8, 1);
	m_list.InsertColumn(2, _T("״̬"), LVCFMT_LEFT, rect.Width() / 8, 2);
	ShowServiceStatus(SERVICE_WIN32);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

VOID CEnumServiceDlg::ShowServiceStatus(DWORD type)
{
	m_list.DeleteAllItems();
	SC_HANDLE hSc = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSc)
	{
		DWORD dwCount = 0;
		DWORD dwSize = 0;
		LPENUM_SERVICE_STATUS lpStatus;
		auto ret = EnumServicesStatus(hSc, type, SERVICE_STATE_ALL, NULL, 0, &dwSize, &dwCount, NULL);
		if (!ret && GetLastError() == ERROR_MORE_DATA)
		{
			lpStatus = (LPENUM_SERVICE_STATUS)(new BYTE[dwSize]);
			ret = EnumServicesStatus(hSc, type, SERVICE_STATE_ALL, lpStatus, dwSize, &dwSize, &dwCount, NULL);
			if (ret)
			{
				for (DWORD i = 0;i < dwCount;++i)
				{
					m_list.InsertItem(i, lpStatus[i].lpServiceName);
					m_list.SetItemText(i, 1, lpStatus[i].lpDisplayName);
					CString s;
					switch (lpStatus[i].ServiceStatus.dwCurrentState)
					{
					case SERVICE_RUNNING:
						s = _T("����");
						break;
					case SERVICE_STOP:
						s = _T("ֹͣ");
						break;
					case SERVICE_PAUSED:
						s = _T("��ͣ");
						break;
					default:
						s = _T("����");
						break;
					}
					m_list.SetItemText(i, 2, s);
				}
			}
			delete lpStatus;
		}
		CloseServiceHandle(hSc);
	}
}

void CEnumServiceDlg::OnBnClickedStart()
{
	auto pos = m_list.GetFirstSelectedItemPosition();
	if (pos)
	{
		int item = m_list.GetNextSelectedItem(pos);
		if (item > -1)
		{
			SC_HANDLE hSc = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
			if (hSc)
			{
				CString name = m_list.GetItemText(item, 0);
				if (!name.IsEmpty())
				{
					SC_HANDLE hService = OpenService(hSc, name, SERVICE_ALL_ACCESS);
					if (hService)
					{
						if (StartServiceW(hService, 0, NULL))
							m_list.SetItemText(item, 2, _T("����"));
						else
							AfxMessageBox(CString(_T("������")) + name + _T("ʧ��!"));
						CloseServiceHandle(hService);
					}
				}
				CloseServiceHandle(hSc);
			}
		}
	}
}

void CEnumServiceDlg::OnBnClickedStop()
{
	auto pos = m_list.GetFirstSelectedItemPosition();
	if (pos)
	{
		int item = m_list.GetNextSelectedItem(pos);
		if (item > -1)
		{
			SC_HANDLE hSc = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
			if (hSc)
			{
				CString name = m_list.GetItemText(item, 0);
				if (!name.IsEmpty())
				{
					SC_HANDLE hService = OpenService(hSc, name, SERVICE_ALL_ACCESS);
					if (hService)
					{
						SERVICE_STATUS status;
						if (ControlService(hService, SERVICE_CONTROL_STOP, &status))
							m_list.SetItemText(item, 2, _T("ֹͣ"));
						else
							AfxMessageBox(CString(_T("ֹͣ��")) + name + _T("ʧ��!"));
						CloseServiceHandle(hService);
					}
				}
				CloseServiceHandle(hSc);
			}
		}
	}
}

void CEnumServiceDlg::OnBnClickedExit()
{
	CDialogEx::OnOK();
}

void CEnumServiceDlg::OnBnClickedDriver()
{
	ShowServiceStatus(SERVICE_DRIVER);
}

void CEnumServiceDlg::OnBnClickedWin32()
{
	ShowServiceStatus(SERVICE_WIN32);
}
