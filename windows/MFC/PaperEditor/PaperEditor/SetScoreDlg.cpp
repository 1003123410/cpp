// SetScoreDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PaperEditor.h"
#include "SetScoreDlg.h"
#include "afxdialogex.h"

// CSetScoreDlg �Ի���
IMPLEMENT_DYNAMIC(CSetScoreDlg, CDialogEx)

CSetScoreDlg::CSetScoreDlg(const stuScoreSet & set, const size_t & topicNum, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SETSCOREDLG, pParent)
{
	m_set = set;
	m_topicNum = topicNum;
	for (size_t i = m_set.m_vecSigle.size();i < topicNum;++i)//�����㹻�����Ŀ����
		m_set.m_vecSigle.push_back(0.0);
	m_singlePos = 0;
	m_BatchPos = 0;
}

CSetScoreDlg::~CSetScoreDlg()
{
}

void CSetScoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITAVERAGE, m_editAverage);
	DDX_Control(pDX, IDC_COMBOSINGLE, m_comboSingle);
	DDX_Control(pDX, IDC_EDITSINGLE, m_editSingle);
	DDX_Control(pDX, IDC_COMBOBATCH, m_comboBatch);
	DDX_Control(pDX, IDC_EDITBATCH, m_editBatch);
}

BEGIN_MESSAGE_MAP(CSetScoreDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIOAVERAGE, &CSetScoreDlg::OnBnClickedRadioaverage)
	ON_BN_CLICKED(IDC_RADIOSINGLE, &CSetScoreDlg::OnBnClickedRadiosingle)
	ON_BN_CLICKED(IDC_RADIOBATCH, &CSetScoreDlg::OnBnClickedRadiobatch)
	ON_BN_CLICKED(IDOK, &CSetScoreDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBOSINGLE, &CSetScoreDlg::OnCbnSelchangeCombosingle)
	ON_CBN_SELCHANGE(IDC_COMBOBATCH, &CSetScoreDlg::OnCbnSelchangeCombobatch)
END_MESSAGE_MAP()

BOOL CSetScoreDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_str.Format("%.2lf", m_set.m_type == eScoreTypeAverage ? m_set.m_total : 100);	//ƽ�������ܷ�
	m_editAverage.SetWindowText(m_str);
	m_comboSingle.ResetContent();						//ɾ��������
	for (size_t i = 0;i < m_topicNum;++i)				//�����Ŀ
	{
		m_str.Format("��%d��", i + 1);
		m_comboSingle.AddString(m_str);
	}
	if (m_topicNum > 0)									//��һ��
	{
		m_str.Format("%.2lf", m_set.m_vecSigle[0]);
		m_editSingle.SetWindowText(m_str);
		m_comboSingle.SetCurSel(0);
	}
	m_comboBatch.SetCurSel(0);							//��������
	m_str.Format("%.2lf", m_set.m_batch[0]);
	m_editBatch.SetWindowText(m_str);
	if (m_set.m_type == eScoreTypeAverage)				//��һ�°�ť
		OnBnClickedRadioaverage();
	else if (m_set.m_type == eScoreTypeSingle)
		OnBnClickedRadiosingle();
	else if (m_set.m_type == eScoreTypeBatch)
		OnBnClickedRadiobatch();

	return TRUE; 
}

void CSetScoreDlg::OnBnClickedRadioaverage()	//ƽ��
{
	m_set.m_type = eScoreTypeAverage;
	ShowWindowControls();
}

void CSetScoreDlg::OnBnClickedRadiosingle()		//����
{
	m_set.m_type = eScoreTypeSingle;
	ShowWindowControls();
}

void CSetScoreDlg::OnBnClickedRadiobatch()		//����
{
	m_set.m_type = eScoreTypeBatch;
	ShowWindowControls();
}

void CSetScoreDlg::ShowWindowControls()		//����ؼ�״̬�л�
{
	((CButton *)GetDlgItem(IDC_RADIOAVERAGE))->SetCheck(m_set.m_type == eScoreTypeAverage); //radio״̬�л�
	((CButton *)GetDlgItem(IDC_RADIOSINGLE))->SetCheck(m_set.m_type == eScoreTypeSingle);
	((CButton *)GetDlgItem(IDC_RADIOBATCH))->SetCheck(m_set.m_type == eScoreTypeBatch);
	m_editAverage.EnableWindow(m_set.m_type == eScoreTypeAverage);
	m_comboSingle.EnableWindow(m_set.m_type == eScoreTypeSingle);
	m_editSingle.EnableWindow(m_set.m_type == eScoreTypeSingle);
	m_comboBatch.EnableWindow(m_set.m_type == eScoreTypeBatch);
	m_editBatch.EnableWindow(m_set.m_type == eScoreTypeBatch);
}

void CSetScoreDlg::OnCbnSelchangeCombosingle()
{
	m_editSingle.GetWindowText(m_str);					
	if (m_singlePos < m_topicNum)	 //���浱ǰֵ
		m_set.m_vecSigle[m_singlePos] = atof(m_str);	 
	m_singlePos = m_comboSingle.GetCurSel();			 
	if (m_singlePos < m_topicNum)	 //�����µ�λ�õ����ݵ�����
	{
		m_str.Format("%.2lf", m_set.m_vecSigle[m_singlePos]);
		m_editSingle.SetWindowText(m_str);
	}
}

void CSetScoreDlg::OnCbnSelchangeCombobatch()
{
	m_editBatch.GetWindowText(m_str);
	if (m_BatchPos < 4)				//���浱ǰֵ
		m_set.m_batch[m_BatchPos] = atof(m_str);
	m_BatchPos = m_comboBatch.GetCurSel();
	if (m_BatchPos < 4)				//�����µ�λ�õ����ݵ�����
	{
		m_str.Format("%.2lf", m_set.m_batch[m_BatchPos]);
		m_editBatch.SetWindowText(m_str);
	}
}

void CSetScoreDlg::OnBnClickedOk()				//ȷ��
{
	if (m_set.m_type == eScoreTypeAverage)		//����������õĵ�ǰֵ
	{
		m_editAverage.GetWindowText(m_str);
		m_set.m_total = atof(m_str);
	}
	else if (m_set.m_type == eScoreTypeSingle)
	{
		m_editSingle.GetWindowText(m_str);
		if (m_set.m_vecSigle.size() > m_singlePos)
			m_set.m_vecSigle[m_singlePos] = atof(m_str);
	}
	else if (m_set.m_type == eScoreTypeBatch)
	{
		m_editBatch.GetWindowText(m_str);
		if(m_BatchPos < 4)
			m_set.m_batch[m_BatchPos] = atof(m_str);
	}
	CDialogEx::OnOK();
}
