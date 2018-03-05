
// testQtDllDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "testQtDll.h"
#include "testQtDllDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestQtDllDlg �Ի���



CtestQtDllDlg::CtestQtDllDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTQTDLL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestQtDllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestQtDllDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtestQtDllDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CtestQtDllDlg ��Ϣ�������

BOOL CtestQtDllDlg::OnInitDialog()
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

void CtestQtDllDlg::OnPaint()
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
HCURSOR CtestQtDllDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestQtDllDlg::OnBnClickedButton1()
{
	TCHAR dllName[] = _T("testQt.dll");
	HMODULE hDLL = LoadLibrary(dllName);

	if (hDLL != NULL)
	{
		typedef bool(*pShow)(HWND parent);
		pShow fp1 = pShow(GetProcAddress(hDLL, "showDialog"));
		if (fp1 != NULL)
			fp1(m_hWnd);
		FreeLibrary(hDLL);
	}
	else
	{
		CString strInfo;
		strInfo.Format(_T("Cannot Find %s"), dllName);
		AfxMessageBox(strInfo);
	}
}
