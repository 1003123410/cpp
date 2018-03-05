
// SocketDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Socket.h"
#include "SocketDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSocketDlg �Ի���



CSocketDlg::CSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SOCKET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITSEND, m_editSend);
	DDX_Control(pDX, IDC_EDIT, m_edit);
}

BEGIN_MESSAGE_MAP(CSocketDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CSocketDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CSocketDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDOK, &CSocketDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSocketDlg ��Ϣ�������

BOOL CSocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_edit.ShowScrollBar(SB_VERT, TRUE);
	m_editSend.ShowScrollBar(SB_VERT, TRUE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSocketDlg::OnPaint()
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
HCURSOR CSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketDlg::OnBnClickedStart()
{
	m_run = TRUE;
	if (!AfxBeginThread(CSocketDlg::StartRecvThread, this, THREAD_PRIORITY_ABOVE_NORMAL))
	{
		OutputDebugString("func:AfxBeginThread StartRecvThread failed");
		return;
	}
}

void CSocketDlg::OnBnClickedStop()
{
	m_run = FALSE;
	SOCKADDR_IN addr;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8101);
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);//��Ϊaccept�����ģ������ܹ������˳������߳�
	CString msg;
	connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	closesocket(sock);
}

UINT CSocketDlg::StartRecvThread(LPVOID para)
{
	//�����׽���
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest = MAKEWORD(2, 2);
	int err;
	err = WSAStartup(myVersionRequest, &wsaData);
	if (err != 0)
	{
		CString s;
		s.Format(_T("func:WSAStartup failed,error:%d"), GetLastError());
		OutputDebugString(s);
		char cstrNewDosCmd[] = "netsh.exe winsock reset";
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		GetStartupInfo(&si);
		si.wShowWindow = SW_HIDE;
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
		PROCESS_INFORMATION pi;
		// ��������  
		DWORD dwCreationFlag = NORMAL_PRIORITY_CLASS | CREATE_UNICODE_ENVIRONMENT | CREATE_NO_WINDOW;
		BOOL bSuc = CreateProcess(NULL, cstrNewDosCmd, NULL, NULL, TRUE, dwCreationFlag, NULL, NULL, &si, &pi);
		WaitForSingleObject(pi.hProcess, 5000);
		err = WSAStartup(myVersionRequest, &wsaData);
		if (err != 0)
			return 0;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		CString s;
		s.Format(_T("func:WSAStartup version not ok,error:%d"), GetLastError());
		OutputDebugString(s);
		WSACleanup();
		return 0;
	}

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);//�����˿�ʶ���׽���
	SOCKADDR_IN listenAddr;
	listenAddr.sin_family = AF_INET;
	listenAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip��ַ
	listenAddr.sin_port = htons(8101);//�󶨶˿�
	int flag = 1;
	int len = sizeof(int);
	if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&flag, len) == -1)
	{
		CString s;
		s.Format(_T("set reuse recvSock IP:%s port:%d failed ,error:%d"), inet_ntoa(listenAddr.sin_addr), listenAddr.sin_port, WSAGetLastError());
		OutputDebugString(s);
	}
	if (SOCKET_ERROR == bind(listenSocket, (SOCKADDR*)&listenAddr, sizeof(SOCKADDR)))
	{
		CString s;
		s.Format(_T("bind recvSock IP:%s port:%d failed ,error:%d"), inet_ntoa(listenAddr.sin_addr), listenAddr.sin_port, WSAGetLastError());
		OutputDebugString(s);
		closesocket(listenSocket);
		WSACleanup();
		return 0;
	}
	if (SOCKET_ERROR == listen(listenSocket, 5))
	{
		CString s;
		s.Format(_T("listen recvSock IP:%s port:%d failed ,error:%d"), inet_ntoa(listenAddr.sin_addr), listenAddr.sin_port, WSAGetLastError());
		OutputDebugString(s);
		closesocket(listenSocket);
		WSACleanup();
		return 0;
	}
	OutputDebugString("StartRecvThread OK");
	CSocketDlg * pParent = (CSocketDlg *)para;
	SOCKADDR_IN clientsocket;
	int AddrLen = sizeof(SOCKADDR);
	TCHAR recvBuf[4096];
	while (pParent->m_run)
	{
		ZeroMemory(recvBuf, 4096);
		SOCKET serConn = accept(listenSocket, (SOCKADDR*)&clientsocket, &AddrLen);
		if (serConn == INVALID_SOCKET)
		{
			CString msg;
			msg.Format("server sccept error:%d", WSAGetLastError());
			OutputDebugString(msg);
			continue;
		}
		OutputDebugString("server StartRecvThread accept");
		int recvLen = recv(serConn, recvBuf, 4096, 0);
		OutputDebugString(recvBuf);
		if (recvLen < 1)
		{
			CString msg;
			msg.Format("server recv error:%d", WSAGetLastError());
			OutputDebugString(msg);
			closesocket(serConn);//�ر�
			continue;
		}
		CString sendText;
		pParent->m_editSend.GetWindowText(sendText);
		SOCKADDR_IN sendAddr;
		sendAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		sendAddr.sin_family = AF_INET;
		sendAddr.sin_port = htons(8102);
		if (SOCKET_ERROR != send(serConn, sendText, sendText.GetLength(), 0))
		{
			OutputDebugString("server send ok");
		}
		else
		{
			OutputDebugString("server send error");
		}
		CString text;
		pParent->m_edit.GetWindowText(text);
		text = text+ "���յ���"+CString(recvBuf)+"\r\n"+"���ͣ�"+sendText+"\r\n";
		pParent->m_edit.SetWindowText(text);
		pParent->m_edit.LineScroll(pParent->m_edit.GetLineCount() - 1, 0);
		closesocket(serConn);//�ر�
	}
	closesocket(listenSocket);
	WSACleanup();
	OutputDebugString("StartRecvThread STOP");
	return 0;
}

void CSocketDlg::OnBnClickedOk()
{
	m_run = FALSE;
	CDialogEx::OnOK();
}
