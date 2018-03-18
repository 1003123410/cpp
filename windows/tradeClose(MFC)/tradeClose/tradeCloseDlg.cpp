#include "stdafx.h"
#include "tradeClose.h"
#include "tradeCloseDlg.h"
#include <thread>
#include "autoClose.h"
#include "afxdialogex.h"
#include <map>
#include "HTML.h"
#include <afxinet.h>

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
END_MESSAGE_MAP()

CtradeCloseDlg::CtradeCloseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtradeCloseDlg::IDD, pParent)
	,m_order_list(_T(""))
	,m_order_list_vector()
	,m_order_list_map()
	, m_detail(_T(""))
	,m_detailCEdit()
	,m_detail_map()
	, m_reason()
	, m_reason_cstring(_T(""))
	, m_search_name(_T(""))
	, m_tb_token(_T(""))
	,m_stop_flag(false)
	,m_count(0)
	, m_user_name(_T(""))
	, m_search_time(30 * 1000)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtradeCloseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USER_NAME, m_user_name);
	//DDX_Text(pDX, IDC_EDIT3, m_detail);//ɾ���������
	DDX_Text(pDX, IDC_EDIT1, m_order_list);
	//DDX_Control(pDX, IDC_COMBO1, m_reason);
	DDX_Control(pDX, IDC_COMBO1, m_reason);
	DDX_Text(pDX, IDC_EDIT2, m_search_name);
	DDX_Control(pDX, IDC_EDIT3, m_detailCEdit);
}

BEGIN_MESSAGE_MAP(CtradeCloseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CtradeCloseDlg::OnBnClickedButton3)
	ON_MESSAGE(WM_PARENT_HIDE, &CtradeCloseDlg::OnParentHide)
	ON_MESSAGE(WM_ORDERCHANGED, &CtradeCloseDlg::OnOrderChanged)
	ON_MESSAGE(WM_STOP, &CtradeCloseDlg::OnStop)
	ON_MESSAGE(WM_DETAILCHANGED, &CtradeCloseDlg::OnDetailChanged)
	ON_MESSAGE(WM_USERNMECHANGED, &CtradeCloseDlg::OnUserNameChanged)
	ON_BN_CLICKED(IDC_BUTTON1, &CtradeCloseDlg::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_BUTTON2, &CtradeCloseDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	//ON_BN_CLICKED(IDC_CHECK2, &CtradeCloseDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()

// CtradeCloseDlg ��Ϣ�������

BOOL CtradeCloseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_reason.SetCurSel(0);

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);


	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	this->ShowWindow(SW_HIDE);

	m_html = new HTML;
	m_html->SetParent(this);
	m_html->Create(IDD_HTML);
	m_html->CenterWindow(this);
	m_html->ShowWindow(SW_NORMAL);
	//������ģ̬�Ի�����ʾ

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CtradeCloseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CtradeCloseDlg::OnPaint()
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
HCURSOR CtradeCloseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CtradeCloseDlg::OnBnClickedButton3()
{
	//�����ֹͣ��ť������Ļ������Զ�ִ�йص�����
	m_stop_flag = true;
}

afx_msg LRESULT CtradeCloseDlg::OnParentHide(WPARAM wParam, LPARAM lParam)
{
	ShowWindow(SW_SHOW);
	//m_flag = true;
	return S_OK;
}

afx_msg LRESULT CtradeCloseDlg::OnOrderChanged(WPARAM wParam, LPARAM lParam)
{
	UpdateData(False);
	return S_OK;
}
afx_msg LRESULT CtradeCloseDlg::OnStop(WPARAM wParam, LPARAM lParam)
{
	m_stop_flag = false;
	return S_OK;
}
afx_msg LRESULT CtradeCloseDlg::OnDetailChanged(WPARAM wParam, LPARAM lParam)
{
	m_detailCEdit.SetWindowText(m_detail);
	m_detailCEdit.LineScroll(m_detailCEdit.GetLineCount());
	UpdateData(false);
	return S_OK;
}
afx_msg LRESULT CtradeCloseDlg::OnUserNameChanged(WPARAM wParam, LPARAM lParam)
{
	m_user_name = m_html->m_user_name;
	m_tb_token = m_html->m_tb_token;
	UpdateData(False);
	return S_OK;
}

void CtradeCloseDlg::OnBnClickedButton1()
{
	//SetTimer(TIMER1, m_search_time, NULL);
	UpdateData();
	m_order_list.Empty();
	::PostMessage(this->m_hWnd, WM_ORDERCHANGED, 0, 0);
	m_order_list_map.clear();
	m_order_list_vector.clear();//��ʼʱҪ���֮ǰ���ڵı�

	m_stop_flag = false;
	m_count = 0;
	m_detail_map.clear();
	::PostMessage(this->m_hWnd, WM_ORDERCHANGED, 0, 0);
	m_reason.GetLBText(m_reason.GetCurSel(), m_reason_cstring);//���ùر�ԭ��Ĭ���ǵ�һ��

	if (m_html->m_login_flag)//�϶�Ҫ��½�ɹ����ܲ�������ʾ֮
	{
		if (0 !=getOrderList(_T("https://trade.taobao.com/trade/itemlist/list_sold_items.htm")))
		{//Ҫ���Ķ�ȷʵ�б����Թر�
			m_order_list_vector.clear();//���֮��֮��whileѭ���Ĳ�����ȫ�ر�����
			::PostMessage(this->m_hWnd,WM_ORDERCHANGED,0,0);
			m_detail += CString(_T("�Ѽ��������ԹرյĶ���!\r\n"));
			::PostMessage(this->m_hWnd, WM_DETAILCHANGED, 0, 0);
			while (true)
			{
				if (true == m_stop_flag)
				//��ֹͣ��,��teadeClose�ĵط��ټ��һ��ֹͣ����ֹͣ��ʱ��Ҫ���棬�Զ�ִ�ж��ٴΣ�һ���رն��ٵ�
				{
					CString count;
					count.Format(_T("%d"), m_detail_map.size());
					MessageBoxTimeout(this->GetSafeHwnd(), _T("�رճɹ������ιرն�����") + count + _T(" ��"), _T(""), MB_ICONINFORMATION, GetSystemDefaultLangID(), 5000);
					count = _T("�رճɹ������ιرն�����") + count + _T(" ��\r\n\r\n\r\n");
					m_detail+=count;
					::PostMessage(this->m_hWnd, WM_DETAILCHANGED, 0, 0);
					break;
				}

				m_order_list_vector.clear();
				if (0 != getOrderList(_T("https://trade.taobao.com/trade/itemlist/list_sold_items.htm")))
				{
					m_detail += CString(_T("���ڹرս���...\r\n"));
					::PostMessage(this->m_hWnd, WM_DETAILCHANGED, 0, 0);
					TradeClose(m_order_list_vector);
					m_order_list_vector.clear();
				}
				else
				{
					CString count;
					count.Format(_T("%d"), m_detail_map.size());
					MessageBoxTimeout(this->GetSafeHwnd(), _T("�رճɹ������ιرն�����") + count + _T(" ��"), _T(""), MB_ICONINFORMATION, GetSystemDefaultLangID(), 5000);
					count = _T("�رճɹ������ιرն�����") + count + _T(" ��\r\n\r\n\r\n");
					m_detail += count;
					::PostMessage(this->m_hWnd, WM_DETAILCHANGED, 0, 0);
					break;
				}
			}
		}
		else
		{
			MessageBoxTimeout(this->GetSafeHwnd(), _T("δ�ҵ�������������\"") + m_search_name + _T("\"�Ķ���!"), _T(""), MB_ICONINFORMATION, GetSystemDefaultLangID(), 5000);
			m_detail += CString(_T("δ�ҵ�������������\"")) + m_search_name + _T("\"�Ķ���!\r\n");
			m_detail += CString(_T("ԭ�������û�з��������Ķ�����������Ƶ�ʹ��ߣ����������Ƶ�ʹ��ߣ��뵽��ҳ�ֶ�����������֤�룬�����ԣ�\r\n\r\n"));
			::PostMessage(this->m_hWnd,WM_DETAILCHANGED,0,0);
		}
	}
	else
		MessageBox(_T("δ��¼�ɹ������˳�����"));
}

void CtradeCloseDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case TIMER1:
		//OnBnClickedButton1();
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CtradeCloseDlg::OnBnClickedCheck2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

int  CtradeCloseDlg::getOrderList(CString url)
{
	//ȡ��Ҫpost����Ϣ
	m_detail += CString(_T("���ڴ��Ա���ȡ����...\r\n"));
	::PostMessage(this->m_hWnd,WM_DETAILCHANGED,0,0);
	int first = url.Find(_T("://")) + 3;
	int count = url.Find(_T(".com")) - first + 4;
	CString m_server = (url.Mid(first, count));
	CString m_action = url.Right(url.GetLength() - first - count - 1);
	
	CString m_msg = CString(_T("event_submit_do_query=1&closeorder_flag=1&isArchive=false&isArchiveDefault=0&user_Type=1&pageNum=0&order=desc&order_Type=orderList&"))
		+ _T("isQueryMore=false&select_shop_name=&isOwnOfficialShop=false&")
		+ _T("sellerNumID=") + m_html->m_seller_num_id
		+ _T("&from_flag=&timeStamp=&sessionID=&authType=1&")
		//��Ҫ�����Ĺؼ��ֲ��뵽auctionTitle
		+ _T("auctionTitle=") + UrlEncode(m_search_name)
		+ _T("&bizOrderTimeBegin=&bizOrderHourBegin=00&bizOrderMinBegin=00&bizOrderTimeEnd=&bizOrderHourEnd=00&bizOrderMinEnd=00&buyerNick=&")
		+ _T("auctionStatus=NOT_PAID&commentStatus=ALL&")
		+ _T("bizOrderId=&logisticsService=ALL&tradeDissension=ALL&auctionType=0&queryBizType=&shopName=All&action=itemlist/QueryAction");
	CString html = SendURLPost(m_server, m_action, m_msg,CString(_T("UTF-8")));
	m_order_list += html;
	m_order_list += m_msg + m_server + m_action;
	int num=htmlToOrder(html, m_order_list_vector);
	::PostMessage(this->m_hWnd, WM_ORDERCHANGED, 0, 0);
	return num;
}

CString CtradeCloseDlg::SendURLPost(CString strServerName, CString strFormActionUrl, CString strPostStr, CString requestType)
{
	string strPostStrS = CStringA(strPostStr);
	strPostStr.ReleaseBuffer();
	CInternetSession mySession;
	CString strHeaders = _T("Content-Type: application/x-www-form-urlencoded;charset="); // ����ͷ
	strHeaders += requestType;
	CHttpConnection *pConnection = mySession.GetHttpConnection(strServerName);
	CHttpFile *htmlFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST, strFormActionUrl);
	TCHAR sRecv[1024];
	CString strHtml;
	UINT CodePage = 936;//CP_UTF8:65001 CP_ACP:0 //GB3212 936
	if (htmlFile) {
		htmlFile->AddRequestHeaders(strHeaders);
		htmlFile->SendRequestEx(strPostStrS.length());
		htmlFile->Write((LPCTSTR)strPostStrS.c_str(), strPostStrS.length());
		htmlFile->EndRequest();
		while (htmlFile->ReadString(sRecv, 1024)) {
			int nBufferSize = MultiByteToWideChar(CodePage, 0, (LPCSTR)sRecv, -1, NULL, 0);
			wchar_t *pBuffer = new wchar_t[nBufferSize + 1];
			memset(pBuffer, 0, (nBufferSize + 1)*sizeof(wchar_t));
			//�ַ�����ת������������
			MultiByteToWideChar(CodePage, 0, (LPCSTR)sRecv, -1, pBuffer, nBufferSize*sizeof(wchar_t));
			strHtml += pBuffer;
			strHtml += "\r\n";
			delete pBuffer;
		}
		htmlFile->Close();
		mySession.Close();
		pConnection->Close();
		return strHtml;
	}
	return CString();
}

int CtradeCloseDlg::htmlToOrder(CString&html, vector<order_list>&order)
{
	string strHtml(CStringA(html).GetBuffer());
	for (auto&i : strHtml)
		if ('\n' == i)
			i = ' ';
	string m_order_begin("<tbody id=\"order");
	string m_order_end("</tbody>");
	//�������ҵ�λ��
	int m_order_pos_begin = -1;
	int m_order_pos_end = 0;
	while ((m_order_pos_begin = strHtml.find(m_order_begin, m_order_pos_end)) != string::npos)
	{
		//��ĩβ��λ�ÿ�ʼ����
		//ȷ�����ҵ�������ʼ�Ĳ��֣��������Ľ���λ��
		if ((m_order_pos_end = strHtml.find(m_order_end, m_order_pos_begin)) != string::npos)
		{
			string m_order(strHtml.begin() + m_order_pos_begin, strHtml.begin() + m_order_pos_end);
			order_list temp_order;
			string number(m_order.begin() + 16, m_order.begin() + 32);
			//MessageBox(CString(number.c_str()));
			temp_order.m_number = CString(number.c_str());
			//�����Ż�ȡ�ɹ�
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//�ر����Ӳ��Ҳ��ֵĴ���
			//�ҵ�������֮��Ҫ�ҹرս��׵����ӣ�
			string url_begin("<div class=\"trade-actions\">");
			string url_end("</div>");
			//�رս������Ӳ��ҵĿ�ʼλ�úͽ���λ��
			int url_pos_begin = m_order.find(url_begin);
			//��¼�����رս��׵����ӵ�ַ
			string url = "";
			if (string::npos != url_pos_begin)
			{
				//���Ľ���״̬��λ�ã���߰����رս��׵ĵ�ַ���Ȼ�ȡ�ⲿ�ֵĴ��룬���������Ҫ�ĵ�ַ
				int url_pos_end = string::npos;
				if ((url_pos_end = m_order.find(url_end, url_pos_begin)) != string::npos)
				{
					//���ӵĳ�ʼλ�úͽ���λ��
					string url_be("href=\"//");
					string url_en("\"");
					//�����ⲿ�ֵ�strHtml���룬����йرս��׵ĵ�ַ
					string url_frame(m_order.begin() + url_pos_begin, m_order.begin() + url_pos_end);
					//MessageBox(CString(url_frame.c_str()));
					int url_begin = url_frame.find(url_be);
					if (string::npos != url_begin)
					{
						int url_end = string::npos;
						if ((url_end = url_frame.find(url_en, url_begin + 9)) != string::npos)
						{
							url = string(url_frame.begin() + url_begin + 8, url_frame.begin() + url_end);
							//MessageBox(CString(url.c_str()));
						}
					}
				}
			}
			//�ر����Ӳ��ҽ���
			temp_order.m_url = CString(url.c_str());
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//����������ֵĲ���
			//һ���Ǳ�ǩ�Ŀ�ʼ��һ��������������ֿ�ʼ֮ǰ�ĵط���Ҳ�Ǳ�ǩ������λ�ã����һ����������ֲ��ҽ�����λ��
			string m_name_frame_begin("<a class=\"nickname\" href=\"//member1");
			string m_name_begin("\">");
			string m_name_end("</a>");
			int m_name_frame_pos_begin = m_order.find(m_name_frame_begin);
			string name(" ");
			if (string::npos != m_name_frame_pos_begin)
			{
				int m_name_pos_begin = string::npos;
				if ((m_name_pos_begin = m_order.find(m_name_begin, m_name_frame_pos_begin)) != string::npos)
				{
					int m_name_pos_end = string::npos;
					if ((m_name_pos_end = m_order.find(m_name_end, m_name_pos_begin)) != string::npos)
					{
						name = string(m_order.begin() + m_name_pos_begin + 2, m_order.begin() + m_name_pos_end);
					}
				}
			}
			temp_order.m_name = CString(name.c_str());
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//����Ҫ��ȡ�������ɵ�ʱ��
			string m_time("");
			string m_time_begin("<span class=\"deal-time\">");
			string m_time_end("</span>");
			int m_time_pos_begin = string::npos;
			if ((m_time_pos_begin = m_order.find(m_time_begin)))
			{
				int m_time_pos_end = string::npos;
				if ((m_time_pos_end = m_order.find(m_time_end, m_time_pos_begin)) != string::npos)
				{
					m_time = string(m_order.begin() + m_time_pos_begin + 32, m_order.begin() + m_time_pos_end);
				}
			}
			temp_order.m_time = CString(m_time.c_str());
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			order.push_back(temp_order);
		}
		else
			break;
	}
	//�޳����ܲ��ԵĶ���
	for (auto i = order.begin(); i != order.end();++i)
	{
		if (i->m_url.GetLength() < 10)
			i =order.erase(i);
	}
	return order.size();
}
int CtradeCloseDlg::TradeClose(vector<order_list>order)
{
	for (auto i : order)
	{
		m_detail += CString(_T("���ڹرս���...\r\n"));
		::PostMessage(this->m_hWnd,WM_DETAILCHANGED,0,0);
		CString url(i.m_url);
		int pos = url.Find(_T(".com"));
		CString m_server = (url.Left(pos + 4));
		CString m_action = url.Right(url.GetLength() - pos - 5);
		CString m_msg = CString(_T("_tb_token_="))+m_tb_token + _T("&bizType=200&") + _T("bizOrderId=")
			+ i.m_number + _T("&action=cancelOrderAction.htm&") + _T("event_submit_do_cancel=1")
			+ _T("&J_CloseReason=%ce%b4%bc%b0%ca%b1%b8%b6%bf%ee");
		CString html = SendURLPost(m_server, m_action, m_msg,CString(_T("GBK")));

		m_order_list += m_msg + m_server + m_action;

		auto it_d = m_detail_map.find(i.m_number);
		if (it_d==m_detail_map.end())
		{
			CString detail;
			detail = CString(_T("������ ")) + i.m_number + _T(" �ѹر�\r\n") + _T("�ر�ԭ�� ") + m_reason_cstring + _T("\r\n\r\n");
			m_detail_map.insert(make_pair(i.m_number, detail));
			m_detail += detail;
			++m_count;
			::PostMessage(this->m_hWnd, WM_DETAILCHANGED, 0, 0);
		}

		auto it_o = m_order_list_map.find(i.m_number);
		if (it_o==m_order_list_map.end())
		{
			m_order_list_map.insert(make_pair(i.m_number,i));
			CString order;
			order = _T("�������:") + i.m_number + _T("  ����ǳ�:") + i.m_name + _T("  ��������ʱ��")
				+ i.m_time + _T("��ַ�� ")+i.m_url+_T("\r\n\r\n\r\n");
			m_order_list += order;
			::PostMessage(this->m_hWnd, WM_ORDERCHANGED, 0, 0);
		}
		if (true == m_stop_flag)
			//��ֹͣ��,��teadeClose�ĵط��ټ��һ��ֹͣ����ֹͣ��ʱ��Ҫ���棬�Զ�ִ�ж��ٴΣ�һ���رն��ٵ�
		{
			CString count;
			count.Format(_T("%d"), m_detail_map.size());
			MessageBoxTimeout(this->GetSafeHwnd(), _T("�رճɹ������ιرն�����") + count + _T(" ��"), _T(""), MB_ICONINFORMATION, GetSystemDefaultLangID(), 5000);
			count = _T("�رճɹ������ιرն�����") + count + _T(" ��\r\n\r\n\r\n");
			m_detail += count;
			::PostMessage(this->m_hWnd, WM_DETAILCHANGED, 0, 0);
			break;
		}
		Sleep(100);
	}
	return 0;
}

CString CtradeCloseDlg::UrlEncode(CString strUnicode)
{
	LPCWSTR unicode = T2CW(strUnicode);
	int len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, 0, 0, 0, 0);
	if (!len)
		return strUnicode;
	char *utf8 = new char[len + 1];
	char *utf8temp = utf8;
	WideCharToMultiByte(CP_UTF8, 0, unicode, -1, utf8, len + 1, 0, 0);
	utf8[len] = NULL;
	CString strTemp, strEncodeData;
	while (*utf8 != '\0') {
		strTemp.Format(_T("%%%2X"), (BYTE)*utf8);
		strEncodeData += strTemp;
		++utf8;
	}
	delete[]utf8temp;
	return CString(strEncodeData);
}