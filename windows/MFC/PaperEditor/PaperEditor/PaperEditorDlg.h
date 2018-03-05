
// PaperEditorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "PaperStruct.h"
#include <vector>
#include "afxext.h"

// CPaperEditorDlg �Ի���
class CPaperEditorDlg : public CDialogEx
{
// ����
public:
	CPaperEditorDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAPEREDITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	//����enter�˳�
	virtual void OnOK();
	//����esc�˳�
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	//���ƴ��ڴ�С
	void OnGetMinMaxInfo(MINMAXINFO * lpMMI);

private:
	//�ؼ�����
	CEdit	   m_editTopicTitle;
	CListBox   m_listTopicFile;
	CButton    m_checkA;
	CButton    m_checkB;
	CButton    m_checkC;
	CButton    m_checkD;
	CButton    m_checkE;
	CEdit      m_editA;
	CEdit      m_editB;
	CEdit      m_editC;
	CEdit      m_editD;
	CEdit      m_editE;
	CEdit      m_editAnswer;
	CComboBox  m_comboSelect;
	CEdit	   m_editPaperTitle;
	CListBox   m_listPaperFile;
	CStatic    m_groupPaper;
	CStatic    m_groupContent;
	CStatic    m_groupType;
	//��Ŀ����
	eTopicType m_topicType;
	//�Ծ�ṹ
	stuPaper   m_paper;
	//�����Ծ��ʼ��Ϣ�������½����򿪡��ر��Ծ�ʱ��������Ƿ��и��£��и�������ʾ���棩
	stuPaper   m_tempPaper; 
	//��ǰ�����Ŀλ��
	int		   m_viewPos;
	//���ڱ���
	CString	   m_strWindowTitle;
	//���ڱ��浱ǰ�Ծ��·��
	CString    m_curPaperPath;
	//��ǰ��������·��
	CString    m_currentPath;
	//��ť����ͼ�õ�
	CBitmapButton m_btnNew;
	CBitmapButton m_btnOpen;
	CBitmapButton m_btnSave;
	CBitmapButton m_btnSaveAs;
	CBitmapButton m_btnScore;
	CBitmapButton m_btnFile;
	CBitmapButton m_btnPreview;
	CBitmapButton m_btnPrint;
	CBitmapButton m_btnNewtopic;
	CBitmapButton m_btnInsert;
	CBitmapButton m_btnLast10;
	CBitmapButton m_btnLast;
	CBitmapButton m_btnNext;
	CBitmapButton m_btnNext10;
	CBitmapButton m_btnDelete;
	CBitmapButton m_btnTopicFile;
	CBitmapButton m_btnSeprator;

private:
	//������Ŀ���пؼ�
	void HideAllTopicControl();
	//����ָ����Ŀ�Ŀؼ�
	void ShowTopicControl(const eTopicType & type);
	//tooltip����
	BOOL SetToolTipText(UINT id, NMHDR *pTTTStruct, LRESULT *pResult);
	//��ʾָ����Ŀ
	void ShowFigureTopic(const stuTopic & topic,const int & pos);
	//���浱ǰ��Ŀ
	void SaveCurTopic(const eTopicType & type);
	//�����Ŀ�ǲ��ǺϷ�
	BOOL CheckTopicValid();
	//��յ�ǰ��Ŀ
	void CleanTopicContent();
	//��ӡ��Ԥ�����ã�����ǰ�Ծ���Ϊhtm�ļ�������htm�ļ���ʾ
	void ShowHtmDialog(const stuPaper & paper,const ePaperViewType & viewType,const CString & filePath);
	//��鵱ǰ�Ծ��Ƿ��޸�
	BOOL IsPaperModify();
	//��ʾ�û��Ƿ񱣴浱ǰ���ڱ༭���Ծ�
	void PromptSave();
	//��ʾedit�Ĺ�����
	void ShowEditScrollBar();
	//��ť��ͼ
	void BeautifyButtons();
	//�����Ծ����
	void SetPaperScore();

public:
	afx_msg void OnBnClickedRadioselect();
	afx_msg void OnBnClickedRadioblank();
	afx_msg void OnBnClickedRadioqa();
	afx_msg void OnCbnSelchangeComboselect();
	//�����ؼ���С
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//��ť�ص�
	afx_msg void OnBnClickedNew();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedSaveas();
	afx_msg void OnBnClickedScore();
	afx_msg void OnBnClickedAddfile();
	afx_msg void OnBnClickedPreview();
	afx_msg void OnBnClickedPrint();
	afx_msg void OnBnClickedNewtopic();
	afx_msg void OnBnClickedInserttopic();
	afx_msg void OnBnClickedLast10topic();
	afx_msg void OnBnClickedLasttopic();
	afx_msg void OnBnClickedNexttopic();
	afx_msg void OnBnClickedNext10topic();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedAddfiletotopic();
	afx_msg void OnBnClickedSeprator();
	afx_msg void OnCancel();
};
