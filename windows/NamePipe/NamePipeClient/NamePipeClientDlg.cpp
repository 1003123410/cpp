
// NamePipeClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NamePipeClient.h"
#include "NamePipeClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNamePipeClientDlg �Ի���



CNamePipeClientDlg::CNamePipeClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NAMEPIPECLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNamePipeClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNamePipeClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CNamePipeClientDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CNamePipeClientDlg ��Ϣ�������

BOOL CNamePipeClientDlg::OnInitDialog()
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

void CNamePipeClientDlg::OnPaint()
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
HCURSOR CNamePipeClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNamePipeClientDlg::OnBnClickedSend()
{
	// �򿪹ܵ�
	HANDLE hPipe = CreateFile("\\\\.\\Pipe\\NamedPipe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		//AfxMessageBox("�򿪹ܵ�ʧ�ܣ���������δ����,���߿ͻ�����������");
		OutputDebugString("�򿪹ܵ�ʧ�ܣ���������δ����,���߿ͻ�����������");
		return;
	}
	DWORD nReadByte = 0, nWriteByte = 0;
	TCHAR buf[MAX_BUFFER_LEN] = { 0 };
	GetDlgItemText(IDC_EDIT1, buf, MAX_BUFFER_LEN);
	if (!WriteFile(hPipe, buf, MAX_BUFFER_LEN, &nWriteByte, NULL))
	{
		CString err;
		err.Format("func:WriteFile failed error:%d", GetLastError());
		OutputDebugString(err);
		CloseHandle(hPipe);
		return;
	}
	if (nWriteByte == 0)
	{
		CString err;
		err.Format("func:nWriteByte ==0 error:%d", GetLastError());
		OutputDebugString(err);
		CloseHandle(hPipe);
		return;
	}
	ZeroMemory(buf, MAX_BUFFER_LEN);
	if (!ReadFile(hPipe, buf, MAX_BUFFER_LEN, &nReadByte, NULL))
	{
		CString err;
		err.Format("func:ReadFile failed error:%d", GetLastError());
		OutputDebugString(err);
		CloseHandle(hPipe);
		return;
	}
	if (nReadByte == 0)
	{
		CString err;
		err.Format("func:nWriteByte ==0 error:%d", GetLastError());
		OutputDebugString(err);
		CloseHandle(hPipe);
		return;
	}
	SetDlgItemText(IDC_EDIT2, buf);
	CloseHandle(hPipe);
}
