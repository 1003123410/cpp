
// AsyncSocketDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AsyncSocket.h"
#include "AsyncSocketDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAsyncSocketDlg �Ի���



CAsyncSocketDlg::CAsyncSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ASYNCSOCKET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAsyncSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, m_edit);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAsyncSocketDlg::OnPaint()
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
HCURSOR CAsyncSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_MESSAGE_MAP(CAsyncSocketDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAsyncSocketDlg::OnBnClickedOk)
	ON_MESSAGE(WM_SOCKET_MSG, &CAsyncSocketDlg::OnSockMsg)
END_MESSAGE_MAP()

// CAsyncSocketDlg ��Ϣ�������
BOOL CAsyncSocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	m_listenSock = socket(PF_INET, SOCK_STREAM, 0);
	WSAAsyncSelect(m_listenSock, GetSafeHwnd(), WM_SOCKET_MSG, FD_ACCEPT);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = ADDR_ANY;
	addr.sin_port = htons(9999);
	bind(m_listenSock, (SOCKADDR*)&addr, sizeof(addr));
	listen(m_listenSock, 5);
	m_edit.ShowScrollBar(SB_VERT, TRUE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
void CAsyncSocketDlg::OnBnClickedOk()
{
	closesocket(m_clientSock);
	closesocket(m_listenSock);
	WSACleanup();
	CDialogEx::OnOK();
}

LRESULT CAsyncSocketDlg::OnSockMsg(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam))
		return 0;
	CString msg;
	m_edit.GetWindowText(msg);
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:
	{
		SOCKADDR_IN addr;
		int size = sizeof(addr);
		m_clientSock = accept(m_listenSock, (SOCKADDR*)&addr, &size);
		WSAAsyncSelect(m_clientSock, GetSafeHwnd(), WM_SOCKET_MSG, FD_READ | FD_CLOSE);
		CString s;
		s.Format(_T("�ͻ��˵�ַ��%s:%d\r\n"), inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
		msg += s;
	}
		break;
	case FD_READ:
	{
		ZeroMemory(m_buf, sizeof(m_buf));
		recv(m_clientSock, m_buf, sizeof(m_buf), 0);
		msg = msg + "���յ���" + CString(m_buf) + "\r\n";
		CString s = CString("server send:") + CString(m_buf);
		send(m_clientSock, s, s.GetLength(), 0);
	}
		break;
	case FD_CLOSE:
	{
		closesocket(m_clientSock);
		msg += "�ͻ��˹ر�����\r\n";
	}
		break;
	default:
		break;
	}
	m_edit.SetWindowText(msg);
	m_edit.LineScroll(m_edit.GetLineCount() - 1, 0);
	return 0;
}