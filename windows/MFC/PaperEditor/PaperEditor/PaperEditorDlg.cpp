// PaperEditorDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "PaperEditor.h"
#include "PaperEditorDlg.h"
#include "afxdialogex.h"
#include "ViewDialog.h"
#include "../GenerateHtm/GenerateHtm.h"
#include "../LoadSavePaper/LoadSavePaper.h"
#include "SetScoreDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CPaperEditorDlg �Ի���
CPaperEditorDlg::CPaperEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAPEREDITOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPaperEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_TOPICTITLE,m_editTopicTitle);
	DDX_Control(pDX,IDC_TOPICFILE,m_listTopicFile);
	DDX_Control(pDX,IDC_CHECKA,m_checkA);
	DDX_Control(pDX,IDC_CHECKB,m_checkB);
	DDX_Control(pDX,IDC_CHECKC,m_checkC);
	DDX_Control(pDX,IDC_CHECKD,m_checkD);
	DDX_Control(pDX,IDC_CHECKE,m_checkE);
	DDX_Control(pDX,IDC_ANSA,m_editA);
	DDX_Control(pDX,IDC_ANSB,m_editB);
	DDX_Control(pDX,IDC_ANSC,m_editC);
	DDX_Control(pDX,IDC_ANSD,m_editD);
	DDX_Control(pDX,IDC_ANSE,m_editE);
	DDX_Control(pDX,IDC_ANS,m_editAnswer);
	DDX_Control(pDX,IDC_COMBOSELECT,m_comboSelect);
	DDX_Control(pDX,IDC_PAPERNAME,m_editPaperTitle);
	DDX_Control(pDX,IDC_GROUPEDITPAPER,m_groupPaper);
	DDX_Control(pDX,IDC_GROUPCONTENT,m_groupContent);
	DDX_Control(pDX,IDC_GROUPTYPE,m_groupType);
	DDX_Control(pDX,IDC_PAPERFILE,m_listPaperFile);
}

BEGIN_MESSAGE_MAP(CPaperEditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_RADIOSELECT,&CPaperEditorDlg::OnBnClickedRadioselect)
	ON_BN_CLICKED(IDC_RADIOBLANK,&CPaperEditorDlg::OnBnClickedRadioblank)
	ON_BN_CLICKED(IDC_RADIOQA,&CPaperEditorDlg::OnBnClickedRadioqa)
	ON_CBN_SELCHANGE(IDC_COMBOSELECT,&CPaperEditorDlg::OnCbnSelchangeComboselect)
	ON_WM_SIZE()
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,SetToolTipText)
	ON_BN_CLICKED(IDC_NEW, &CPaperEditorDlg::OnBnClickedNew)
	ON_BN_CLICKED(IDC_OPEN, &CPaperEditorDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_SAVE, &CPaperEditorDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_SAVEAS, &CPaperEditorDlg::OnBnClickedSaveas)
	ON_BN_CLICKED(IDC_SCORE, &CPaperEditorDlg::OnBnClickedScore)
	ON_BN_CLICKED(IDC_ADDFILE, &CPaperEditorDlg::OnBnClickedAddfile)
	ON_BN_CLICKED(IDC_PREVIEW, &CPaperEditorDlg::OnBnClickedPreview)
	ON_BN_CLICKED(IDC_PRINT, &CPaperEditorDlg::OnBnClickedPrint)
	ON_BN_CLICKED(IDC_NEWTOPIC, &CPaperEditorDlg::OnBnClickedNewtopic)
	ON_BN_CLICKED(IDC_INSERTTOPIC, &CPaperEditorDlg::OnBnClickedInserttopic)
	ON_BN_CLICKED(IDC_LAST10TOPIC, &CPaperEditorDlg::OnBnClickedLast10topic)
	ON_BN_CLICKED(IDC_LASTTOPIC, &CPaperEditorDlg::OnBnClickedLasttopic)
	ON_BN_CLICKED(IDC_NEXTTOPIC, &CPaperEditorDlg::OnBnClickedNexttopic)
	ON_BN_CLICKED(IDC_NEXT10Topic, &CPaperEditorDlg::OnBnClickedNext10topic)
	ON_BN_CLICKED(IDC_DELETE, &CPaperEditorDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_ADDFILETOTOPIC, &CPaperEditorDlg::OnBnClickedAddfiletotopic)
	ON_BN_CLICKED(IDC_SEPRATOR, &CPaperEditorDlg::OnBnClickedSeprator)
END_MESSAGE_MAP()

// CPaperEditorDlg ��Ϣ�������
BOOL CPaperEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	//���ô��ڱ���
	m_strWindowTitle = _T("�Ծ�༭�� -UnTitle");
	SetWindowText(m_strWindowTitle);
	//Ĭ��ѡ����ѡ��
	((CButton *)GetDlgItem(IDC_RADIOSELECT))->SetCheck(TRUE);
	((CComboBox *)GetDlgItem(IDC_COMBOSELECT))->SetCurSel(2);
	m_topicType = eTopicTypeSelect;
	m_listTopicFile.ShowWindow(SW_HIDE);
	EnableToolTips(TRUE);
	m_paper.m_vecTopic.push_back(stuTopic());		//���Ȳ���һ����Ŀ
	m_viewPos = 0;
	m_tempPaper = m_paper;							//�����Ծ�ĳ�ʼ��Ϣ
	ShowEditScrollBar();
	BeautifyButtons();
	m_btnSeprator.ShowWindow(SW_HIDE);				//���ذ�ť
	m_btnFile.ShowWindow(SW_HIDE);			
	m_btnTopicFile.ShowWindow(SW_HIDE);
	TCHAR buf[MAX_PATH] = {0};						//��ȡ��������·��
	GetCurrentDirectory(MAX_PATH,buf);
	m_currentPath = CString(buf) + "\\";
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
//��ʾedit�Ĺ�����
void CPaperEditorDlg::ShowEditScrollBar()
{
	m_editTopicTitle.ShowScrollBar(SB_VERT, TRUE);	//��ʾ������
	m_editAnswer.ShowScrollBar(SB_VERT, TRUE);
	m_editA.ShowScrollBar(SB_VERT, TRUE);
	m_editB.ShowScrollBar(SB_VERT, TRUE);
	m_editC.ShowScrollBar(SB_VERT, TRUE);
	m_editD.ShowScrollBar(SB_VERT, TRUE);
	m_editE.ShowScrollBar(SB_VERT, TRUE);
}
//��ť��ͼ
void CPaperEditorDlg::BeautifyButtons()
{
	m_btnNew.SubclassDlgItem(IDC_NEW, this);
	m_btnOpen.SubclassDlgItem(IDC_OPEN, this);
	m_btnSave.SubclassDlgItem(IDC_SAVE, this);
	m_btnSaveAs.SubclassDlgItem(IDC_SAVEAS, this);
	m_btnScore.SubclassDlgItem(IDC_SCORE, this);
	m_btnFile.SubclassDlgItem(IDC_ADDFILE, this);
	m_btnPreview.SubclassDlgItem(IDC_PREVIEW, this);
	m_btnPrint.SubclassDlgItem(IDC_PRINT, this);
	m_btnNewtopic.SubclassDlgItem(IDC_NEWTOPIC, this);
	m_btnInsert.SubclassDlgItem(IDC_INSERTTOPIC, this);
	m_btnLast10.SubclassDlgItem(IDC_LAST10TOPIC, this);
	m_btnLast.SubclassDlgItem(IDC_LASTTOPIC, this);
	m_btnNext.SubclassDlgItem(IDC_NEXTTOPIC, this);
	m_btnNext10.SubclassDlgItem(IDC_NEXT10Topic, this);
	m_btnDelete.SubclassDlgItem(IDC_DELETE, this);
	m_btnTopicFile.SubclassDlgItem(IDC_ADDFILETOTOPIC, this);
	m_btnSeprator.SubclassDlgItem(IDC_SEPRATOR, this);
	m_btnNew.LoadBitmaps(IDB_NEW, IDB_NEW2);
	m_btnOpen.LoadBitmaps(IDB_OPEN, IDB_OPEN2);
	m_btnSave.LoadBitmaps(IDB_SAVE, IDB_SAVE2);
	m_btnSaveAs.LoadBitmaps(IDB_SAVEAS, IDB_SAVEAS2);
	m_btnScore.LoadBitmaps(IDB_SCORE, IDB_SCORE2);
	m_btnFile.LoadBitmaps(IDB_FILE, IDB_FILE2);
	m_btnPreview.LoadBitmaps(IDB_PREVIEW, IDB_PREVIEW2);
	m_btnPrint.LoadBitmaps(IDB_PRINT, IDB_PRINT2);
	m_btnNewtopic.LoadBitmaps(IDB_NEWTOPIC, IDB_NEWTOPIC2);
	m_btnInsert.LoadBitmaps(IDB_INSERT, IDB_INSERT2);
	m_btnLast10.LoadBitmaps(IDB_LAST10, IDB_LAST102);
	m_btnLast.LoadBitmaps(IDB_LAST, IDB_LAST2);
	m_btnNext.LoadBitmaps(IDB_NEXT, IDB_NEXT2);
	m_btnNext10.LoadBitmaps(IDB_NEXT10, IDB_NEXT102);
	m_btnDelete.LoadBitmaps(IDB_DELETE, IDB_DELETE2);
	m_btnTopicFile.LoadBitmaps(IDB_FILETOPIC, IDB_FILETOPIC2);
	m_btnSeprator.LoadBitmaps(IDB_SEPRATOR, IDB_SEPRATOR2);
}
//����enter�˳�
void CPaperEditorDlg::OnOK()
{
}
//����esc�˳�
BOOL CPaperEditorDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
void CPaperEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CPaperEditorDlg::OnPaint()
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
HCURSOR CPaperEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//���ƴ�����С��С
void CPaperEditorDlg::OnGetMinMaxInfo(MINMAXINFO * lpMMI)
{
	lpMMI->ptMinTrackSize.x = 1017;
	lpMMI->ptMinTrackSize.y = 711;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
//ѡ����
void CPaperEditorDlg::OnBnClickedRadioselect()		//�����ǰ����ѡ���⡢�������пؼ�����ʾ
{
	if (m_topicType == eTopicTypeSelect)
		return;
	m_topicType = eTopicTypeSelect;
	m_comboSelect.EnableWindow(TRUE);
	HideAllTopicControl();
	ShowTopicControl(m_topicType);
}
//�����
void CPaperEditorDlg::OnBnClickedRadioblank()		//�����ǰ��������⡢�������пؼ�����ʾ
{
	if (m_topicType == eTopicTypeBlank)
		return;
	m_topicType = eTopicTypeBlank;
	m_comboSelect.EnableWindow(FALSE);
	HideAllTopicControl();
	ShowTopicControl(m_topicType);
}
//�ʴ���
void CPaperEditorDlg::OnBnClickedRadioqa()			//�����ǰ�����ʴ��⡢�������пؼ�����ʾ
{
	if (m_topicType == eTopicTypeQA)
		return;
	m_topicType = eTopicTypeQA;
	m_comboSelect.EnableWindow(FALSE);
	HideAllTopicControl();
	ShowTopicControl(m_topicType);
}
//ѡ���������ı�
void CPaperEditorDlg::OnCbnSelchangeComboselect()	//����Ҫ��ʾ�Ĵ𰸸���
{
	ShowTopicControl(eTopicTypeSelect);
}
//�������пؼ�
void CPaperEditorDlg::HideAllTopicControl()	//������Ŀ�Ƕ������пؼ�
{
	m_editTopicTitle.ShowWindow(SW_HIDE);
	m_listTopicFile.ShowWindow(SW_HIDE);
	m_checkA.ShowWindow(SW_HIDE);
	m_checkB.ShowWindow(SW_HIDE);
	m_checkC.ShowWindow(SW_HIDE);
	m_checkD.ShowWindow(SW_HIDE);
	m_checkE.ShowWindow(SW_HIDE);
	m_editA.ShowWindow(SW_HIDE);
	m_editB.ShowWindow(SW_HIDE);
	m_editC.ShowWindow(SW_HIDE);
	m_editD.ShowWindow(SW_HIDE);
	m_editE.ShowWindow(SW_HIDE);
	m_editAnswer.ShowWindow(SW_HIDE);
	m_btnSeprator.ShowWindow(SW_HIDE);
}
//��ʾָ�����͵Ŀؼ��������ؼ���С
void CPaperEditorDlg::ShowTopicControl(const eTopicType & type)
{
	m_editTopicTitle.ShowWindow(SW_SHOW);
	CRect rect;
	GetWindowRect(&rect);
	CPoint point;
	point.x = 203;
	point.y = 191;
	int width = rect.Width() - 232;
	m_editTopicTitle.SetWindowPos(this,point.x,point.y,width,185,SWP_NOZORDER);//��Ŀλ��
	switch(type)
	{
	case eTopicTypeSelect:
	{
		int height = (int)((rect.Height() - point.y - 185 - 65)/5.0);
		point.x += 51;
		point.y += 188;
		//�޸�ѡ��λ�ã�����ʾ������ѡ��
		m_editA.SetWindowPos(this, point.x, point.y, width - 51, height, SWP_NOZORDER);
		m_checkA.SetWindowPos(this, point.x - 35, point.y + 16, 0,0, SWP_NOZORDER | SWP_NOSIZE);
		point.y = point.y + height + 3;
		m_editB.SetWindowPos(this, point.x, point.y, width - 51, height, SWP_NOZORDER);
		m_checkB.SetWindowPos(this, point.x - 35, point.y + 16, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		point.y = point.y + height + 3;
		m_editC.SetWindowPos(this, point.x, point.y, width - 51, height, SWP_NOZORDER);
		m_checkC.SetWindowPos(this, point.x - 35, point.y + 16, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		point.y = point.y + height + 3;
		m_editD.SetWindowPos(this, point.x, point.y, width - 51, height, SWP_NOZORDER);
		m_checkD.SetWindowPos(this, point.x - 35, point.y + 16, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		point.y = point.y + height + 3;
		m_editE.SetWindowPos(this, point.x, point.y, width - 51, height, SWP_NOZORDER);
		m_checkE.SetWindowPos(this, point.x - 35, point.y + 16, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		int curSel = m_comboSelect.GetCurSel();
		m_checkA.ShowWindow(SW_SHOW);
		m_editA.ShowWindow(SW_SHOW);
		m_checkB.ShowWindow(SW_SHOW);
		m_editB.ShowWindow(SW_SHOW);
		m_checkC.ShowWindow(curSel > 0 ? SW_SHOW : SW_HIDE);
		m_editC.ShowWindow(curSel > 0 ? SW_SHOW : SW_HIDE);
		m_checkD.ShowWindow(curSel > 1 ? SW_SHOW : SW_HIDE);
		m_editD.ShowWindow(curSel > 1 ? SW_SHOW : SW_HIDE);
		m_checkE.ShowWindow(curSel > 2 ? SW_SHOW : SW_HIDE);
		m_editE.ShowWindow(curSel > 2 ? SW_SHOW : SW_HIDE);
		break;
	}
	case eTopicTypeBlank:
	{
		m_editAnswer.SetWindowPos(this, 0, 0, width, 60, SWP_NOZORDER | SWP_NOMOVE);
		m_btnSeprator.SetWindowPos(this, rect.Width() - 133, 454,0,0, SWP_NOZORDER | SWP_NOSIZE);
		m_editAnswer.ShowWindow(SW_SHOW);
		m_btnSeprator.ShowWindow(SW_SHOW);
		break;
	}
	case eTopicTypeQA:
	{
		m_editAnswer.SetWindowPos(this, 0,0,width,180, SWP_NOZORDER | SWP_NOMOVE);
		m_editAnswer.ShowWindow(SW_SHOW);
		break;
	}
	default:
		break;
	}
}
//��С�ı�����ؼ�
void CPaperEditorDlg::OnSize(UINT nType,int cx,int cy)
{
	CDialogEx::OnSize(nType,cx,cy);
	if(nType == SIZE_MINIMIZED)//��С��
		return;
	if(m_groupContent.m_hWnd != NULL)			  //�޸����λ��
	{	
		m_groupPaper.SetWindowPos(this,4,88,cx - 8,cy - 91,SWP_NOZORDER);
		m_groupType.SetWindowPos(this,9,179,187,cy - 187,SWP_NOZORDER);
		m_groupContent.SetWindowPos(this,198,179,cx - 206,cy - 187,SWP_NOZORDER);
		ShowTopicControl(m_topicType);
	}
}
//tooltip����
BOOL CPaperEditorDlg::SetToolTipText(UINT id, NMHDR *pTTTStruct, LRESULT *pResult)
{
	TOOLTIPTEXT * pTTT = (TOOLTIPTEXT *)pTTTStruct;
	UINT nID = pTTTStruct->idFrom;				  //�õ���Ӧ����ID���п�����HWND   
	nID = ::GetDlgCtrlID((HWND)nID);			  //��HWND�õ�IDֵ
	if (nID && (pTTT->uFlags & TTF_IDISHWND))     //����nID�Ƿ�ΪHWND
	{
		switch (nID)							  //����ID����tooltip�ַ���
		{
		case IDC_NEW:
			strcpy_s(pTTT->lpszText, 80, _T("�½��Ծ�"));
			break;
		case IDC_OPEN:
			strcpy_s(pTTT->lpszText, 80, _T("���ѱ�����Ծ�"));
			break;
		case IDC_SAVE:
			strcpy_s(pTTT->lpszText, 80, _T("���浱ǰ�Ծ�"));
			break;
		case IDC_SAVEAS:
			strcpy_s(pTTT->lpszText, 80, _T("����ǰ�Ծ����"));
			break;
		case IDC_SCORE:
			strcpy_s(pTTT->lpszText, 80, _T("�����Ծ����"));
			break;
		case IDC_ADDFILE:
			strcpy_s(pTTT->lpszText, 80, _T("�����ļ����Ծ�"));
			break;
		case IDC_PREVIEW:
			strcpy_s(pTTT->lpszText, 80, _T("Ԥ���Ծ�"));
			break;
		case IDC_PRINT:
			strcpy_s(pTTT->lpszText, 80, _T("��ӡ�Ծ�"));
			break;
		case IDC_NEWTOPIC:
			strcpy_s(pTTT->lpszText, 80, _T("����Ŀĩβ������Ŀ"));
			break;
		case IDC_INSERTTOPIC:
			strcpy_s(pTTT->lpszText, 80, _T("�ڵ�ǰ��Ŀǰ��������Ŀ"));
			break;
		case IDC_DELETE:
			strcpy_s(pTTT->lpszText, 80, _T("ɾ����ǰ��Ŀ"));
			break;
		case IDC_ADDFILETOTOPIC:
			strcpy_s(pTTT->lpszText, 80, _T("�����ļ�����ǰ��Ŀ"));
			break;
		case IDC_COMBOSELECT:
			strcpy_s(pTTT->lpszText, 80, _T("ѡ����ѡ������"));
			break;
		case IDC_LAST10TOPIC:
			strcpy_s(pTTT->lpszText, 80, _T("����ʮ��"));
			break;
		case IDC_LASTTOPIC:
			strcpy_s(pTTT->lpszText, 80, _T("����һ��"));
			break;
		case IDC_NEXTTOPIC:
			strcpy_s(pTTT->lpszText, 80, _T("ǰ��һ��"));
			break;
		case IDC_NEXT10Topic:
			strcpy_s(pTTT->lpszText, 80, _T("ǰ��ʮ��"));
			break;
		case IDC_PAPERTITLE:
			strcpy_s(pTTT->lpszText, 80, _T("�����Ծ�����"));
			break;
		case IDC_TOPICTITLE:
			strcpy_s(pTTT->lpszText, 80, _T("������Ŀ����"));
			break;
		case IDC_CHECKA:
			strcpy_s(pTTT->lpszText, 80, _T("ѡ��A"));
			break;
		case IDC_CHECKB:
			strcpy_s(pTTT->lpszText, 80, _T("ѡ��B"));
			break;
		case IDC_CHECKC:
			strcpy_s(pTTT->lpszText, 80, _T("ѡ��C"));
			break;
		case IDC_CHECKD:
			strcpy_s(pTTT->lpszText, 80, _T("ѡ��D"));
			break;
		case IDC_CHECKE:
			strcpy_s(pTTT->lpszText, 80, _T("ѡ��E"));
			break;
		case IDC_ANS:
			strcpy_s(pTTT->lpszText, 80, _T("���������"));
			break;
		case IDC_ANSA:
			strcpy_s(pTTT->lpszText, 80, _T("�����A������"));
			break;
		case IDC_ANSB:
			strcpy_s(pTTT->lpszText, 80, _T("�����B������"));
			break;
		case IDC_ANSC:
			strcpy_s(pTTT->lpszText, 80, _T("�����C������"));
			break;
		case IDC_ANSD:
			strcpy_s(pTTT->lpszText, 80, _T("�����D������"));
			break;
		case IDC_ANSE:
			strcpy_s(pTTT->lpszText, 80, _T("�����E������"));
			break;
		case IDC_SEPRATOR:
			strcpy_s(pTTT->lpszText, 80, _T("���������в���ָ���@"));
			break;
		case IDC_TOPICFILE:
			strcpy_s(pTTT->lpszText, 80, _T("��Ŀ�����ļ�����ѡ�и����Ҽ��Ƴ�"));
			break;
		case IDC_PAPERFILE:
			strcpy_s(pTTT->lpszText, 80, _T("�Ծ����ļ�����ѡ�и����Ҽ��Ƴ�"));
			break;
		default:
			break;
		}
		return TRUE;
	}
	return FALSE;
}
//��ʾָ�����⣬�޸Ľ�����ʾ
void CPaperEditorDlg::ShowFigureTopic(const stuTopic & topic,const int & pos)	
{
	m_editTopicTitle.SetWindowText(topic.m_title);
	CString s;
	s.Format("����%d",pos + 1);
	SetDlgItemText(IDC_STATICQUESTION,s);
	m_viewPos = pos;
	((CButton *)GetDlgItem(IDC_RADIOSELECT))->SetCheck(topic.m_type == eTopicTypeSelect);	//�л�����״̬
	((CButton *)GetDlgItem(IDC_RADIOBLANK))->SetCheck(topic.m_type == eTopicTypeBlank);
	((CButton *)GetDlgItem(IDC_RADIOQA))->SetCheck(topic.m_type == eTopicTypeQA);
	m_topicType = eTopicTypeNone;
	switch (topic.m_type)
	{
	case eTopicTypeSelect:
	{
		m_comboSelect.SetCurSel(topic.m_selectNum - 2);
		m_checkA.SetCheck(topic.m_checkA);
		m_checkB.SetCheck(topic.m_checkB);
		m_checkC.SetCheck(topic.m_checkC);
		m_checkD.SetCheck(topic.m_checkD);
		m_checkE.SetCheck(topic.m_checkE);
		m_editA.SetWindowText(topic.m_ansA);
		m_editB.SetWindowText(topic.m_ansB);
		m_editC.SetWindowText(topic.m_ansC);
		m_editD.SetWindowText(topic.m_ansD);
		m_editE.SetWindowText(topic.m_ansE);
		OnBnClickedRadioselect();
		break;
	}
	case eTopicTypeBlank:
	{
		OnBnClickedRadioblank();
		m_editAnswer.SetWindowText(topic.m_ans);
		break;
	}
	case eTopicTypeQA:
	{
		OnBnClickedRadioqa();
		m_editAnswer.SetWindowText(topic.m_ans);
		break;
	}
	default:
		break;
	}
}
//�½��Ծ�
void CPaperEditorDlg::OnBnClickedNew()
{
    if(IsPaperModify())								//����ǰ����δ��ɱ༭���Ծ���ʾ�û�����
		PromptSave();
	m_paper = stuPaper();							//������ǰ�Ծ�����
	m_paper.m_vecTopic.push_back(stuTopic());		//����һ����Ŀ	
	m_editPaperTitle.SetWindowText("");
	m_strWindowTitle = _T("�Ծ�༭�� -UnTitle"); 	//���´��ڱ���
	SetWindowText(m_strWindowTitle);
	m_curPaperPath = "";							//�½��Ծ�����·������Ϊ��
	((CComboBox *)GetDlgItem(IDC_COMBOSELECT))->SetCurSel(2);
	((CButton *)GetDlgItem(IDC_RADIOBLANK))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_RADIOQA))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_RADIOSELECT))->SetCheck(TRUE);  //����Ϊ��ʼ״̬
	m_topicType = eTopicTypeNone;					//ȷ�����¼�����ʾ
	CleanTopicContent();
	ShowFigureTopic(m_paper.m_vecTopic[0], 0);
	m_tempPaper = m_paper;							//����m_tempPaper��ϢΪ��ʼ��Ϣ
}
//���Ծ�
void CPaperEditorDlg::OnBnClickedOpen()
{
    if(IsPaperModify())								//����ǰ����δ��ɱ༭���Ծ���ʾ�û�����
		PromptSave();								//����ǰ�Ծ����½��Ծ���㱣�浯·������򣬷��򲻵�
	CFileDialog openFileDlg(TRUE, ".exm","",OFN_HIDEREADONLY | OFN_READONLY, "Exam files(*.exm)|*.exm||", NULL);
	openFileDlg.m_ofn.lpstrTitle = "��";
	if (openFileDlg.DoModal() == IDOK)
	{
		CString filePath = openFileDlg.GetPathName();
		m_paper = stuPaper();
		CLoadSavePaper loader;
		if(loader.LoadPaper(m_paper,ePaperTypePaper,filePath))				//�����ļ����ݣ�������Ŀ��ʾ���Ծ�༭���У��������Ĭ��ͣ�ڵ�һ����
		{
			CleanTopicContent();								//��յ�ǰ������������
			m_curPaperPath = filePath;
			m_strWindowTitle = _T("�Ծ�༭�� ") + m_curPaperPath;//�򿪳ɹ����޸Ĵ��ڱ���Ϊ�Ծ�·��������
			SetWindowText(m_strWindowTitle);
			m_editPaperTitle.SetWindowText(m_paper.m_paperTitle);//�����Ծ���
			if (m_paper.m_vecTopic.size() < 1)
				m_paper.m_vecTopic.push_back(stuTopic());
			m_topicType = eTopicTypeNone;						//ȷ�����¼�����ʾ
			ShowFigureTopic(m_paper.m_vecTopic[0], 0);
			m_tempPaper = m_paper;								//����m_tempPaper��ϢΪ��ʼ��Ϣ
		}
		else
			AfxMessageBox(_T("���Ծ�ʧ�ܣ�"));
	}
}
//�����Ծ�
void CPaperEditorDlg::OnBnClickedSave()
{
	SaveCurTopic(m_topicType);								//���桢���
	if (!CheckTopicValid())
		return;										//�������
	CString tempPath = m_curPaperPath;
	if (m_curPaperPath.IsEmpty())							//ѡ�񱣴�·��
	{
		CFileDialog openFileDlg(FALSE, ".exm", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Exam files(*.exm)| *.exm||", NULL);
		openFileDlg.m_ofn.lpstrTitle = "����";
		if (openFileDlg.DoModal() == IDOK)
			tempPath = openFileDlg.GetPathName();
	}
	if (tempPath.IsEmpty())							//ѡ�񱣴�·��ʱȡ��
		return;
	CLoadSavePaper saver;
	if (saver.SavePaper(m_paper,ePaperTypePaper,tempPath))
	{
		m_curPaperPath = tempPath;
		m_strWindowTitle = _T("�Ծ�༭�� ") + m_curPaperPath;
		SetWindowText(m_strWindowTitle);
		m_tempPaper = m_paper;
		AfxMessageBox("����ɹ���");
	}
	else
		AfxMessageBox("����ʧ�ܣ��ļ��޷���.");
}
//����Ծ�
void CPaperEditorDlg::OnBnClickedSaveas()
{
	SaveCurTopic(m_topicType);								//���桢���
	if (!CheckTopicValid())
		return;									//�������
	CFileDialog openFileDlg(FALSE, ".exm", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Exam files(*.exm)| *.exm||", NULL);
	openFileDlg.m_ofn.lpstrTitle = "���Ϊ";
	CString tempPath = m_curPaperPath;
	if (openFileDlg.DoModal() == IDOK)
		tempPath = openFileDlg.GetPathName();
	if (tempPath.IsEmpty())							//ѡ�񱣴�·��ʱȡ��
		return;
	CLoadSavePaper saver;
	if (saver.SavePaper(m_paper, ePaperTypePaper, tempPath))
	{
		m_curPaperPath = tempPath;
		m_strWindowTitle = _T("�Ծ�༭�� ") + m_curPaperPath;
		SetWindowText(m_strWindowTitle);
		m_tempPaper = m_paper;
		AfxMessageBox("����ɹ���");
	}
	else
		AfxMessageBox("����ʧ�ܣ��ļ��޷���.");
}
//��������
void CPaperEditorDlg::OnBnClickedScore()
{
	CSetScoreDlg  dlgScore(m_paper.m_scoreSet, m_paper.m_vecTopic.size(), this);
	if (dlgScore.DoModal() == IDOK)
	{
		m_paper.m_scoreSet = dlgScore.m_set;
		SetPaperScore();
	}
}
//�����ļ����Ծ�  //δʹ��
void CPaperEditorDlg::OnBnClickedAddfile()
{
	////Author&Time:sunx@2017-12-05
	////1-According window select files
	//BOOL isOpen = TRUE;//Save-TRUE Open-FALSE  
	//CString defaultDir = _T("");//Default file path
	//CString fileName = _T("");//Default file name  
	//CString filter = _T("All Files(*.*)| *.*||");//File type  
	//CFileDialog openFileDlg(isOpen, defaultDir, fileName, 
	//	OFN_ENABLESIZING |//Use mouse to change file picture size
	//	OFN_HIDEREADONLY
	//	, filter, NULL);
	//openFileDlg.GetOFN().lpstrInitialDir = _T("");
	//INT_PTR result = openFileDlg.DoModal();
	//CString filePath = defaultDir + "\\" + fileName;
	//if (result == IDOK)
	//{
	//	filePath = openFileDlg.GetPathName();
	//}
	//
	////2-Add file path to struct
	//m_paper.m_paperFiles.push_back(filePath);
}
//��ӡ��Ԥ�����ã�����ǰ�Ծ���Ϊhtm�ļ�������htm�ļ���ʾ
void CPaperEditorDlg::ShowHtmDialog(const stuPaper & paper,const ePaperViewType & viewType,const CString & filePath)
{
	SaveCurTopic(m_topicType);
	SetPaperScore();								//�������
	CGenerateHtm htm;
	if(htm.GeneratePaperToHtm(m_paper,filePath,viewType))
	{
		CViewDialog dlg(IDD_VIEWDIALOG,IDR_HTML_VIEWDIALOG,paper, viewType, CString("file:///") + filePath, this);
		dlg.DoModal();
	}
}
//Ԥ��
void CPaperEditorDlg::OnBnClickedPreview()
{
	ShowHtmDialog(m_paper,ePaperViewTypeView,m_currentPath + "test1.htm");
}
//��ӡ
void CPaperEditorDlg::OnBnClickedPrint()
{
	HKEY hkey;
	CString keyPath = "Software\\Microsoft\\Internet Explorer\\PageSetup";		//��ӡ֮ǰ����IE��ӡʱ����ӡҳü  ҳ�Ŵ�ӡҳ��
	if(ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER,keyPath,0,KEY_WRITE,&hkey))
	{
		LRESULT r = RegSetValueEx(hkey,"header",0,REG_SZ,(LPBYTE)"",0);			//���ҳü
		LRESULT r1 = RegSetValueEx(hkey,"footer",0,REG_SZ,(LPBYTE)"&b&p/&P",8);	//ҳ�� ���ƣ�1/4
		RegFlushKey(hkey);
		RegCloseKey(hkey);
	}
	ShowHtmDialog(m_paper,ePaperViewTypePrint,m_currentPath + "test1.htm");
}
//�½���Ŀ
void CPaperEditorDlg::OnBnClickedNewtopic()			//���桢���Ϸ��ԡ����뵽ĩβ����ս���
{
	SaveCurTopic(m_topicType);
	if (CheckTopicValid())
	{
		m_paper.m_vecTopic.push_back(stuTopic());
		m_viewPos = m_paper.m_vecTopic.size() - 1;
		m_paper.m_vecTopic[m_viewPos].m_type = m_topicType;
		if (m_topicType == eTopicTypeSelect)
			m_paper.m_vecTopic[m_viewPos].m_selectNum = m_comboSelect.GetCurSel() + 2;
		ShowFigureTopic(m_paper.m_vecTopic[m_viewPos],m_viewPos);
		CleanTopicContent();
	}
}
//������Ŀ
void CPaperEditorDlg::OnBnClickedInserttopic()		//���桢���Ϸ��ԡ����뵽��ǰλ�á���ս���
{
	SaveCurTopic(m_topicType);
	if(CheckTopicValid())
	{
		std::vector<stuTopic>::iterator it = m_paper.m_vecTopic.begin() + m_viewPos;
		m_paper.m_vecTopic.insert(it, stuTopic());
		m_paper.m_vecTopic[m_viewPos].m_type = m_topicType;
		if (m_topicType == eTopicTypeSelect)
			m_paper.m_vecTopic[m_viewPos].m_selectNum = m_comboSelect.GetCurSel() + 2;
		ShowFigureTopic(m_paper.m_vecTopic[m_viewPos], m_viewPos);
		CleanTopicContent();
	}
}
//����10��
void CPaperEditorDlg::OnBnClickedLast10topic()		//���浱ǰ�ġ�����ת��ʾ
{
	SaveCurTopic(m_topicType);
	m_viewPos -= 10;
	m_viewPos = m_viewPos > 0 ? m_viewPos : 0;
	CleanTopicContent();
	ShowFigureTopic(m_paper.m_vecTopic[m_viewPos],m_viewPos);
}
//��һ��
void CPaperEditorDlg::OnBnClickedLasttopic()		//���浱ǰ�ġ�����ת��ʾ
{
	SaveCurTopic(m_topicType);
	m_viewPos -= 1;
	m_viewPos = m_viewPos > 0 ? m_viewPos : 0;
	CleanTopicContent();
	ShowFigureTopic(m_paper.m_vecTopic[m_viewPos],m_viewPos);
}
//��һ��
void CPaperEditorDlg::OnBnClickedNexttopic()		//���浱ǰ�ġ�����ת��ʾ
{
	SaveCurTopic(m_topicType);
	m_viewPos += 1;
	m_viewPos = m_viewPos > (int)m_paper.m_vecTopic.size() - 1 ? m_paper.m_vecTopic.size() - 1 : m_viewPos;
	CleanTopicContent();
	ShowFigureTopic(m_paper.m_vecTopic[m_viewPos],m_viewPos);
}
//ǰ��10��
void CPaperEditorDlg::OnBnClickedNext10topic()		//���浱ǰ�ġ�����ת��ʾ
{
	SaveCurTopic(m_topicType);
	m_viewPos += 10;
	m_viewPos = m_viewPos > (int)m_paper.m_vecTopic.size() - 1 ? m_paper.m_vecTopic.size() - 1 : m_viewPos;
	CleanTopicContent();
	ShowFigureTopic(m_paper.m_vecTopic[m_viewPos],m_viewPos);
}
//ɾ��
void CPaperEditorDlg::OnBnClickedDelete()
{
	if (m_paper.m_vecTopic.size() < 1)
		return;
	m_paper.m_vecTopic.erase(m_paper.m_vecTopic.begin() + m_viewPos);		//ɾ��
	if(m_paper.m_vecTopic.size() < 1)				//ɾ���ˣ����һ��
		m_paper.m_vecTopic.push_back(stuTopic());
	m_viewPos = m_viewPos > (int)m_paper.m_vecTopic.size() - 1 ? m_paper.m_vecTopic.size() - 1 : m_viewPos;
	CleanTopicContent();
	ShowFigureTopic(m_paper.m_vecTopic[m_viewPos], m_viewPos);
	SetPaperScore();
}
//�����ļ�����Ŀ
void CPaperEditorDlg::OnBnClickedAddfiletotopic()
{
}
//�ָ���
void CPaperEditorDlg::OnBnClickedSeprator()
{
	m_editAnswer.SendMessage(WM_CHAR, '@', 0);	//@�ָ��
}
//�����Ŀ�ǲ��ǺϷ�
BOOL CPaperEditorDlg::CheckTopicValid()
{
	CString str;
	m_editPaperTitle.GetWindowText(m_paper.m_paperTitle);	//�Ծ���
	if (m_paper.m_paperTitle.GetLength() < 1)
	{
		AfxMessageBox("�������Ծ���!");
		m_editPaperTitle.SetFocus();
		return FALSE;
	}
	for(size_t i = 0;i < m_paper.m_vecTopic.size();++i)		//�������
	{
		str.Format("����%d:",i + 1);
		if(m_paper.m_vecTopic[i].m_title.GetLength() < 1)		//��Ŀ
		{
			AfxMessageBox(str + "��������Ŀ����!");
			ShowFigureTopic(m_paper.m_vecTopic[i],i);
			m_editTopicTitle.SetFocus();
			return FALSE;
		}
		if(m_paper.m_vecTopic[i].m_type == eTopicTypeSelect)
		{
			int cul = m_paper.m_vecTopic[i].m_selectNum;
			if(m_paper.m_vecTopic[i].m_ansA.GetLength() < 1)		//ѡ�����ݲ���Ϊ��
			{
				AfxMessageBox(str + "������Aѡ������!");
				ShowFigureTopic(m_paper.m_vecTopic[i],i);
				m_editA.SetFocus();
				return FALSE;
			}
			if(m_paper.m_vecTopic[i].m_ansB.GetLength() < 1)
			{
				AfxMessageBox(str + "������Bѡ������!");
				ShowFigureTopic(m_paper.m_vecTopic[i],i);
				m_editB.SetFocus();
				return FALSE;
			}
			if(cul > 2 && m_paper.m_vecTopic[i].m_ansC.GetLength() < 1)
			{
				AfxMessageBox(str + "������Cѡ������!");
				ShowFigureTopic(m_paper.m_vecTopic[i],i);
				m_editC.SetFocus();
				return FALSE;
			}
			if(cul > 3 && m_paper.m_vecTopic[i].m_ansD.GetLength() < 1)
			{
				AfxMessageBox(str + "������Dѡ������!");
				ShowFigureTopic(m_paper.m_vecTopic[i],i);
				m_editD.SetFocus();
				return FALSE;
			}
			if(cul > 4 && m_paper.m_vecTopic[i].m_ansE.GetLength() < 1)
			{
				AfxMessageBox(str + "������Eѡ������!");
				ShowFigureTopic(m_paper.m_vecTopic[i],i);
				m_editE.SetFocus();
				return FALSE;
			}
			std::vector<CString>vec;					//�ж�ѡ����ѡ����ͬ
			vec.push_back(m_paper.m_vecTopic[i].m_ansA);
			vec.push_back(m_paper.m_vecTopic[i].m_ansB);
			if (cul > 2)
				vec.push_back(m_paper.m_vecTopic[i].m_ansC);
			if (cul > 3)
				vec.push_back(m_paper.m_vecTopic[i].m_ansD);
			if (cul > 4)
				vec.push_back(m_paper.m_vecTopic[i].m_ansE);
			for (size_t j = 0;j < vec.size();++j)
			{
				for (size_t k = j + 1; k < vec.size();++k)
				{
					if (vec[j] == vec[k])
					{
						CString temps;
						temps.Format("ѡ��%c��ѡ��%c��ͬ�����޸�!", 'A' + j, 'A' + k);
						AfxMessageBox(str + temps);
						ShowFigureTopic(m_paper.m_vecTopic[i], i);
						return FALSE;
					}
				}
			}
			std::vector<int> vec1;
			vec1.push_back(m_paper.m_vecTopic[i].m_checkA);		//ѡ���ж�
			vec1.push_back(m_paper.m_vecTopic[i].m_checkB);
			if (cul > 2)
				vec1.push_back(m_paper.m_vecTopic[i].m_checkC);
			if (cul > 3)
				vec1.push_back(m_paper.m_vecTopic[i].m_checkD);
			if (cul > 4)
				vec1.push_back(m_paper.m_vecTopic[i].m_checkE);
			int count = 0;
			for (size_t j = 0;j < vec1.size();++j)
				if (vec1[j] == BST_CHECKED)
					++count;
			if (count < 1)							//������һ��ѡ�е�
			{
				AfxMessageBox(str + "��ѡ����ȷ�Ĵ�!");
				ShowFigureTopic(m_paper.m_vecTopic[i], i);
				return FALSE;
			}
		}
		else
		{
			if(m_paper.m_vecTopic[i].m_ans.GetLength() < 1)		//�𰸲���Ϊ��
			{
				AfxMessageBox(str + "��������ȷ��!");
				ShowFigureTopic(m_paper.m_vecTopic[i],i);
				m_editAnswer.SetFocus();
				return FALSE;
			}
		}
	}
	SetPaperScore();										//�������
	return TRUE;
}
//���浱ǰ��Ŀ
void CPaperEditorDlg::SaveCurTopic(const eTopicType & type)
{
	m_editPaperTitle.GetWindowText(m_paper.m_paperTitle);	//�����Ծ���
	CString s;
	m_editTopicTitle.GetWindowText(s);	
	m_paper.m_vecTopic[m_viewPos].m_title = s;		//���⡢����
	m_paper.m_vecTopic[m_viewPos].m_type = type;
	switch(type)
	{
	case eTopicTypeSelect:
	{
		m_paper.m_vecTopic[m_viewPos].m_selectNum = m_comboSelect.GetCurSel() + 2;	//ѡ���
		m_paper.m_vecTopic[m_viewPos].m_checkA = m_checkA.GetCheck();
		m_paper.m_vecTopic[m_viewPos].m_checkB = m_checkB.GetCheck();
		m_editA.GetWindowText(s);
		m_paper.m_vecTopic[m_viewPos].m_ansA = s;
		m_editB.GetWindowText(s);
		m_paper.m_vecTopic[m_viewPos].m_ansB = s;
		if(m_paper.m_vecTopic[m_viewPos].m_selectNum > 2)
		{
			m_paper.m_vecTopic[m_viewPos].m_checkC = m_checkC.GetCheck();
			m_editC.GetWindowText(s);
			m_paper.m_vecTopic[m_viewPos].m_ansC = s;
		}
		if(m_paper.m_vecTopic[m_viewPos].m_selectNum > 3)
		{
			m_paper.m_vecTopic[m_viewPos].m_checkD = m_checkD.GetCheck();
			m_editD.GetWindowText(s);
			m_paper.m_vecTopic[m_viewPos].m_ansD = s;
		}
		if(m_paper.m_vecTopic[m_viewPos].m_selectNum > 4)
		{
			m_paper.m_vecTopic[m_viewPos].m_checkE = m_checkE.GetCheck();
			m_editE.GetWindowText(s);
			m_paper.m_vecTopic[m_viewPos].m_ansE = s;
		}
		break;
	}
	case eTopicTypeBlank:
	case eTopicTypeQA:
	{
		m_editAnswer.GetWindowText(s);			//��
		m_paper.m_vecTopic[m_viewPos].m_ans = s;
		break;
	}
	default:
		break;
	}
}
//��յ�ǰ��Ŀ��������
void CPaperEditorDlg::CleanTopicContent()
{
	m_editTopicTitle.SetWindowText("");
	m_checkA.SetCheck(BST_UNCHECKED);
	m_checkB.SetCheck(BST_UNCHECKED);
	m_checkC.SetCheck(BST_UNCHECKED);
	m_checkD.SetCheck(BST_UNCHECKED);
	m_checkE.SetCheck(BST_UNCHECKED);
	m_editA.SetWindowText("");
	m_editB.SetWindowText("");
	m_editC.SetWindowText("");
	m_editD.SetWindowText("");
	m_editE.SetWindowText("");
	m_editAnswer.SetWindowText("");
}
//��鵱ǰ�Ծ��Ƿ��޸�
BOOL CPaperEditorDlg::IsPaperModify()
{
	SaveCurTopic(m_topicType);			//���浱ǰ���ڱ༭����Ŀ
	return !(m_tempPaper == m_paper);
}
//��ʾ�û��Ƿ񱣴浱ǰ���ڱ༭���Ծ�
void CPaperEditorDlg::PromptSave()
{
	if (IDYES == MessageBox(_T("�Ƿ񱣴浱ǰ���ڱ༭���Ծ�"), _T("��ʾ"), MB_YESNO))  //ѡ�񱣴�
		OnBnClickedSave();
}
//�ر��Ծ�༭��
void CPaperEditorDlg::OnCancel()
{
	//AfxMessageBox(_T("�ر��Ծ�༭��"));
	////����ǰ����δ��ɱ༭���Ծ���ʾ�û�����
	if (IsPaperModify())
	{
		PromptSave();
	}
	CDialogEx::OnCancel();
}
// �����Ծ����
void CPaperEditorDlg::SetPaperScore()
{
	if (m_paper.m_scoreSet.m_type == eScoreTypeAverage)			//ƽ������
	{
		double score = m_paper.m_scoreSet.m_total / m_paper.m_vecTopic.size();
		for (size_t i = 0;i < m_paper.m_vecTopic.size();++i)
			m_paper.m_vecTopic[i].m_score = score;
	}
	else if (m_paper.m_scoreSet.m_type == eScoreTypeSingle)		//��������
	{
		size_t len = min(m_paper.m_vecTopic.size(), m_paper.m_scoreSet.m_vecSigle.size());
		for (size_t i = 0;i < len;++i)
			m_paper.m_vecTopic[i].m_score = m_paper.m_scoreSet.m_vecSigle[i];
	}
	else if (m_paper.m_scoreSet.m_type == eScoreTypeBatch)		//��������
	{
		double choice = 0, multiChoice = 0, blank = 0, qa = 0;
		for (size_t i = 0;i < m_paper.m_vecTopic.size();++i)	//���������������
		{
			if (m_paper.m_vecTopic[i].m_type == eTopicTypeBlank)		//���
				++blank;
			else if (m_paper.m_vecTopic[i].m_type == eTopicTypeQA)		//�ʴ�
				++qa;
			else if (m_paper.m_vecTopic[i].m_type == eTopicTypeSelect && m_paper.m_vecTopic[i].IsSingleChoice())//��ѡ
				++choice;
			else                                  //��ѡ
				++multiChoice;
		}
		choice = choice == 0 ? 0 : m_paper.m_scoreSet.m_batch[0] / choice;				//ÿ��ķ���
		multiChoice = multiChoice == 0 ? 0 : m_paper.m_scoreSet.m_batch[1] / multiChoice;
		blank = blank == 0 ? 0 : m_paper.m_scoreSet.m_batch[2] / blank;
		qa = qa == 0 ? 0 : m_paper.m_scoreSet.m_batch[3] / qa;
		for (size_t i = 0;i < m_paper.m_vecTopic.size();++i)			//��������
		{
			if (m_paper.m_vecTopic[i].m_type == eTopicTypeBlank)		//���
				m_paper.m_vecTopic[i].m_score = blank;
			else if (m_paper.m_vecTopic[i].m_type == eTopicTypeQA)		//�ʴ�
				m_paper.m_vecTopic[i].m_score = qa;
			else if (m_paper.m_vecTopic[i].m_type == eTopicTypeSelect && m_paper.m_vecTopic[i].IsSingleChoice())//��ѡ
				m_paper.m_vecTopic[i].m_score = choice;
			else                                  //��ѡ
				m_paper.m_vecTopic[i].m_score = multiChoice;
		}
	}
}
