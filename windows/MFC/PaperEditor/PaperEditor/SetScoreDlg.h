#pragma once
#include "afxwin.h"
#include "PaperStruct.h"

// CSetScoreDlg �Ի���

class CSetScoreDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetScoreDlg)

public:
	CSetScoreDlg(const stuScoreSet & set, const size_t & topicNum,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetScoreDlg();
	virtual BOOL OnInitDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETSCOREDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioaverage();
	afx_msg void OnBnClickedRadiosingle();
	afx_msg void OnBnClickedRadiobatch();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombosingle();
	afx_msg void OnCbnSelchangeCombobatch();

public:
	//���汣��ķ���������Ϣ
	stuScoreSet m_set;

private:
	//�ؼ�����
	CEdit		m_editAverage;
	CComboBox	m_comboSingle;
	CEdit		m_editSingle;
	CComboBox	m_comboBatch;
	CEdit		m_editBatch;
	//���浥������comboBox�ı�ǰ��λ��
	size_t		m_singlePos;
	//������������comboBox�ı�ǰ��λ��
	size_t		m_BatchPos;
	//��Ŀ����
	size_t		m_topicNum;
	//���ڸ�ʽ�����ַ���
	CString		m_str;

private:
	//��ʾ������ָ������ؼ�
	void ShowWindowControls();
};
