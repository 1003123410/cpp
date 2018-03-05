
// PaperEditor.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "PaperEditor.h"
#include "PaperEditorDlg.h"
#include <Psapi.h>
#pragma comment (lib,"Psapi.lib")

#define EClass_MUTEX_GUID_Paper_Edit_COMMONUSER _T("{ 273C8C03 - 099A - 4AC7 - 830E-4D57257A2ECA }")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaperEditorApp

BEGIN_MESSAGE_MAP(CPaperEditorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPaperEditorApp ����

CPaperEditorApp::CPaperEditorApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPaperEditorApp ����

CPaperEditorApp theApp;

BOOL CALLBACK EnumWindowsProc(HWND hwnd/*��ǰ�ҵ��Ĵ��ھ��*/, LPARAM lParam/*�Զ������*/)  //ö�ٵ�ǰ����
{
	TCHAR tcClass[256];
	LPWSTR  pStr = (LPWSTR)lParam;
	HWND htmpWnd = NULL;
	::GetClassName(hwnd, tcClass, 255);

	DWORD dwProcessID;
	TCHAR szProcessName[260] = { 0 };
	GetWindowThreadProcessId(hwnd, &dwProcessID);
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessID);

	GetModuleFileNameEx(hProcess, NULL, szProcessName, MAX_PATH);

	if (strstr(szProcessName, _T("\\PaperEditor.exe")) != NULL)
	{
		CWnd * pWndPrev = CWnd::FromHandle(hwnd);
		pWndPrev = pWndPrev->GetParent();
		if (pWndPrev != NULL)
		{
			CWnd * pWndChild = pWndPrev->GetLastActivePopup();
			if (pWndPrev->IsIconic())
				pWndPrev->ShowWindow(SW_RESTORE);
			pWndChild->SetForegroundWindow();
		}
	}
	return TRUE;
}

// CPaperEditorApp ��ʼ��

BOOL CPaperEditorApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	CreateMutex(NULL, TRUE, EClass_MUTEX_GUID_Paper_Edit_COMMONUSER);

	//�Ծ�༭�����ڣ��ظ������ö���ʾ
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		EnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)(_T("CabinetWClass")));//ö��������Ļ�ϵĶ��㴰��																		 
		return FALSE;
	}

	CPaperEditorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

