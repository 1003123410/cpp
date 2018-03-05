
// AsyncSocketClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AsyncSocketClient.h"
#include "AsyncSocketClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAsyncSocketClientDlg �Ի���



CAsyncSocketClientDlg::CAsyncSocketClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ASYNCSOCKETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAsyncSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITSEND, m_editSend);
	DDX_Control(pDX, IDC_EDIT, m_edit);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAsyncSocketClientDlg::OnPaint()
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
HCURSOR CAsyncSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BEGIN_MESSAGE_MAP(CAsyncSocketClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAsyncSocketClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CONNECT, &CAsyncSocketClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_SEND, &CAsyncSocketClientDlg::OnBnClickedSend)
	ON_MESSAGE(WM_SOCKET_MSG, &CAsyncSocketClientDlg::OnSockMsg)
END_MESSAGE_MAP()

// CAsyncSocketClientDlg ��Ϣ�������
BOOL CAsyncSocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	m_sock = socket(PF_INET, SOCK_STREAM, 0);
	m_edit.ShowScrollBar(SB_VERT, TRUE);
	m_editSend.ShowScrollBar(SB_VERT, TRUE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAsyncSocketClientDlg::OnBnClickedOk()
{
	closesocket(m_sock);
	WSACleanup();
	CDialogEx::OnOK();
}

void CAsyncSocketClientDlg::OnBnClickedConnect()
{
	CString s;
	GetDlgItemText(IDC_CONNECT, s);
	if (s == "����")
	{
		m_sock = socket(PF_INET, SOCK_STREAM, 0);
		WSAAsyncSelect(m_sock, GetSafeHwnd(), WM_SOCKET_MSG, FD_CONNECT | FD_CLOSE | FD_READ);
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(9999);
		connect(m_sock,(SOCKADDR*)&addr, (sizeof(addr)));
		CString msg;
		m_edit.GetWindowText(msg);
		msg += "���ӷ����\r\n";
		m_edit.SetWindowText(msg);
		SetDlgItemText(IDC_CONNECT, "�Ͽ�");
	}
	else if (s == "�Ͽ�")
	{
		closesocket(m_sock);
		SetDlgItemText(IDC_CONNECT, "����");
		CString msg;
		m_edit.GetWindowText(msg);
		msg += "�Ͽ�����\r\n";
		m_edit.SetWindowText(msg);
	}
}

void CAsyncSocketClientDlg::OnBnClickedSend()
{
	CString s;
	m_editSend.GetWindowText(s);
	send(m_sock, s, s.GetLength(), 0);
}

LRESULT CAsyncSocketClientDlg::OnSockMsg(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam))
		return 0;
	CString msg;
	m_edit.GetWindowText(msg);
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_CONNECT:
	{
		msg += "���ӳɹ�\r\n";
	}
	break;
	case FD_READ:
	{
		ZeroMemory(m_buf, sizeof(m_buf));
		recv(m_sock, m_buf, sizeof(m_buf), 0);
		msg = msg + "���յ���" + CString(m_buf) + "\r\n";
	}
	break;
	case FD_CLOSE:
	{
		closesocket(m_sock);
		msg += "����˹ر�����\r\n";
	}
	break;
	default:
		break;
	}
	m_edit.SetWindowText(msg);
	m_edit.LineScroll(m_edit.GetLineCount() - 1, 0);
	return 0;
}