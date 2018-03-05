
// NamePipeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NamePipe.h"
#include "NamePipeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNamePipeDlg �Ի���
volatile BOOL m_run;


CNamePipeDlg::CNamePipeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NAMEPIPE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_run = FALSE;
}

void CNamePipeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNamePipeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CNamePipeDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CNamePipeDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CNamePipeDlg ��Ϣ�������

BOOL CNamePipeDlg::OnInitDialog()
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

void CNamePipeDlg::OnPaint()
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
HCURSOR CNamePipeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CNamePipeDlg::ServerThread(LPVOID para)
{
	DWORD nReadByte = 0, nWriteByte = 0, dwByte = 0;
	TCHAR szBuf[MAX_BUFFER_LEN] = { 0 };
	PIPE_INSTRUCT CurPipeInst = *(PIPE_INSTRUCT*)para;
	OVERLAPPED OverLapStruct = { 0, 0, 0, 0, CurPipeInst.hEvent };
	CString err;
	DWORD curThreadID = GetCurrentThreadId();
	err.Format("func:thread %d begin", curThreadID);
	OutputDebugString(err);
	while (m_run)
	{
		ZeroMemory(szBuf, MAX_BUFFER_LEN);
		ConnectNamedPipe(CurPipeInst.hPipe, &OverLapStruct);
		WaitForSingleObject(CurPipeInst.hEvent, INFINITE);
		OutputDebugString("waited");
		if (!GetOverlappedResult(CurPipeInst.hPipe, &OverLapStruct, &dwByte, true))
		{
			DisconnectNamedPipe(CurPipeInst.hPipe);
			continue;
		}
		if (!ReadFile(CurPipeInst.hPipe, szBuf, MAX_BUFFER_LEN, &nReadByte, NULL))
		{
			err.Format("func:ReadFile failed %d error:%d", GetLastError());
			OutputDebugString(err);
			DisconnectNamedPipe(CurPipeInst.hPipe);
			continue;
		}
		if(nReadByte == 0)
		{
			DisconnectNamedPipe(CurPipeInst.hPipe);
			continue;
		}
		err.Format("func:thread:%d recv:%s", curThreadID, szBuf);
		OutputDebugString(err);
		ZeroMemory(szBuf, MAX_BUFFER_LEN);
		sprintf_s(szBuf, "server %d sendmsg.", curThreadID);
		if (!WriteFile(CurPipeInst.hPipe, szBuf, MAX_BUFFER_LEN, &nWriteByte, NULL))
		{
			err.Format("func:WriteFile failed %d error:%d", GetLastError());
			OutputDebugString(err);
			DisconnectNamedPipe(CurPipeInst.hPipe);
			continue;
		}
		DisconnectNamedPipe(CurPipeInst.hPipe);
	}
	err.Format("func:thread %d exit", curThreadID);
	OutputDebugString(err);
	return 0;
}

void CNamePipeDlg::OnBnClickedStart()
{
	m_run = TRUE;
	CString lpPipeName = "\\\\.\\Pipe\\NamedPipe";
	for (UINT i = 0; i < MAX_THREAD_COUNT; ++i)
	{
		PipeInst[i].hPipe = CreateNamedPipe(lpPipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, MAX_THREAD_COUNT, 0, 0, 1000, NULL);
		DWORD error = GetLastError();
		if (PipeInst[i].hPipe == INVALID_HANDLE_VALUE)
		{
			CString err;
			err.Format("func:CreateNamedPipe failed %d error:%d", i, error);
			OutputDebugString(err);
			continue;
		}
		PipeInst[i].hEvent = CreateEvent(NULL, FALSE, FALSE, FALSE);
		error = GetLastError();
		if (!PipeInst[i].hEvent)
		{
			CString err;
			err.Format("func:CreateEvent failed %d error:%d", i, error);
			OutputDebugString(err);
			continue;
		}
		PipeInst[i].hTread = AfxBeginThread(ServerThread, &PipeInst[i], THREAD_PRIORITY_NORMAL);
		error = GetLastError();
		if (!PipeInst[i].hTread)
		{
			CString err;
			err.Format("func:AfxBeginThread failed %d error:%d", i, error);
			OutputDebugString(err);
			continue;
		}
	}
	AfxMessageBox("���������ɹ�");
}


void CNamePipeDlg::OnBnClickedStop()
{
	DWORD dwNewMode = PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_NOWAIT;
	m_run = FALSE;
	for (UINT i = 0; i < MAX_THREAD_COUNT; i++)
	{
		SetEvent(PipeInst[i].hEvent);
		CloseHandle(PipeInst[i].hTread);
		CloseHandle(PipeInst[i].hPipe);
	}
	AfxMessageBox("ֹͣ�����ɹ�");
}
