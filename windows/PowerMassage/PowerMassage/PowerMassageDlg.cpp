
// PowerMassageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PowerMassage.h"
#include "PowerMassageDlg.h"
#include "afxdialogex.h"
#include <WtsApi32.h>
#pragma comment(lib,"WtsApi32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPowerMassageDlg �Ի���

const UINT WMEX_TASKBARCREATED = ::RegisterWindowMessage(TEXT("TaskbarCreated"));

CPowerMassageDlg::CPowerMassageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_POWERMASSAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPowerMassageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPowerMassageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_REGISTERED_MESSAGE(WMEX_TASKBARCREATED, OnRestartExplorer)
END_MESSAGE_MAP()


// CPowerMassageDlg ��Ϣ�������

BOOL CPowerMassageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	hPowerNotify = RegisterPowerSettingNotification(m_hWnd, &GUID_LIDSWITCH_STATE_CHANGE, DEVICE_NOTIFY_WINDOW_HANDLE);//ע��WM_POWERBROADCAST��Ϣ
	WTSRegisterSessionNotification(m_hWnd, NOTIFY_FOR_THIS_SESSION);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPowerMassageDlg::OnPaint()
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
HCURSOR CPowerMassageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

typedef HDESK(WINAPI *PFNOPENDESKTOP)(LPSTR, DWORD, BOOL, ACCESS_MASK);
typedef BOOL(WINAPI *PFNCLOSEDESKTOP)(HDESK);
typedef BOOL(WINAPI *PFNSWITCHDESKTOP)(HDESK);
BOOL PP_IsWorkStationLocked()//�ж��Ƿ�����������
{
	BOOL bLocked = FALSE;
	static HMODULE hUser32 = LoadLibrary(_T("user32.dll"));
	if (hUser32) 
	{
		static PFNOPENDESKTOP fnOpenDesktop = (PFNOPENDESKTOP)GetProcAddress(hUser32, "OpenDesktopA");
		static PFNCLOSEDESKTOP fnCloseDesktop = (PFNCLOSEDESKTOP)GetProcAddress(hUser32, "CloseDesktop");
		static PFNSWITCHDESKTOP fnSwitchDesktop = (PFNSWITCHDESKTOP)GetProcAddress(hUser32, "SwitchDesktop");
		if (fnOpenDesktop && fnCloseDesktop && fnSwitchDesktop) 
		{
			HDESK hDesk = fnOpenDesktop("Default", 0, FALSE, DESKTOP_SWITCHDESKTOP);
			if (hDesk) 
			{
				bLocked = !fnSwitchDesktop(hDesk);
				fnCloseDesktop(hDesk);
			}
		}
	}
	return bLocked;
}

LRESULT CPowerMassageDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_QUERYENDSESSION://���жϹػ���������
	{
		OutputDebugString(_T("WM_QUERYENDSESSION"));
	}
	break;
	case WM_POWERBROADCAST://�ж�˯�ߡ����ߵ�
	{
		OutputDebugString(_T("WM_POWERBROADCAST "));
		if (wParam == PBT_APMSUSPEND)//ϵͳ��ͣ����
			OutputDebugString(_T("power off"));
		else if ((wParam == PBT_APMRESUMEAUTOMATIC) || (wParam == PBT_APMRESUMESUSPEND))//����
			OutputDebugString(_T("power ON"));
		else
			OutputDebugString(_T("other option"));
	}
	break;
	case WM_DESTROY:
	{
		WTSUnRegisterSessionNotification(m_hWnd);
		UnregisterPowerSettingNotification(hPowerNotify);
	}
	case WM_WTSSESSION_CHANGE://�жϵ�¼��ע����������
	{
		switch (wParam)
		{
		case WTS_CONSOLE_CONNECT:
			OutputDebugString(_T("session login"));
		break;
		case WTS_CONSOLE_DISCONNECT:
			OutputDebugString(_T("session logoff"));
		break;
		case WTS_SESSION_LOCK:
			OutputDebugString(_T("session lock"));
		break;
		default:
			break;
		}
	}
	default:
		break;
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}

LRESULT CPowerMassageDlg::OnRestartExplorer(WPARAM wParam, LPARAM lParam) //�ж���Դ����������
{
	OutputDebugString(_T("RestartExplorer"));
	return TRUE;
}