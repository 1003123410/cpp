
// SocketClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SocketClient.h"
#include "SocketClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSocketClientDlg �Ի���



CSocketClientDlg::CSocketClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SOCKETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITSEND, m_editSend);
	DDX_Control(pDX, IDC_EDITRECV, m_editRecv);
}

BEGIN_MESSAGE_MAP(CSocketClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CSocketClientDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDOK, &CSocketClientDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSocketClientDlg ��Ϣ�������

BOOL CSocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	m_editRecv.ShowScrollBar(SB_VERT, TRUE);
	m_editSend.ShowScrollBar(SB_VERT, TRUE);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSocketClientDlg::OnPaint()
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
HCURSOR CSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketClientDlg::OnBnClickedSend()
{//�����׽���
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
			return;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		CString s;
		s.Format(_T("func:WSAStartup version not ok,error:%d"), GetLastError());
		OutputDebugString(s);
		WSACleanup();
		return;
	}
	OutputDebugString("CSocketClientDlg StartSendThread OK");
	SOCKADDR_IN sendAddr;
	sendAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	sendAddr.sin_family = AF_INET;
	sendAddr.sin_port = htons(8101);
	CString sendText;
	m_editSend.GetWindowText(sendText);
	SOCKET SendSocket = socket(AF_INET, SOCK_STREAM, 0);//�����˿�ʶ���׽���
	CString msg;
	if (SOCKET_ERROR != connect(SendSocket, (SOCKADDR*)&sendAddr, sizeof(SOCKADDR)))
	{
		if (SOCKET_ERROR != send(SendSocket, sendText.GetBuffer(), sendText.GetLength(), 0))
		{
			OutputDebugString("CSocketClientDlg client send ok");
			char recvBuf[4096] = { 0 };
			if (recv(SendSocket, recvBuf, 4096, 0) > 0)
			{
				CString recvText;
				m_editRecv.GetWindowText(recvText);
				recvText = recvText + "client recv: " + CString(recvBuf) + "\r\n";
				m_editRecv.SetWindowText(recvText);
				m_editRecv.LineScroll(m_editRecv.GetLineCount()-1, 0);
			}
			else
			{
				msg.Format("CSocketClientDlg recv error:%d", WSAGetLastError());
				OutputDebugString(msg);
			}
		}
		else
		{
			msg.Format("CSocketClientDlg StartSendThread send error:%d", WSAGetLastError());
			OutputDebugString(msg);
		}
	}
	else
	{
		msg.Format("CSocketClientDlg connect error:%d", WSAGetLastError());
		OutputDebugString(msg);
	}
	closesocket(SendSocket);
	WSACleanup();
	return;
}

void CSocketClientDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
