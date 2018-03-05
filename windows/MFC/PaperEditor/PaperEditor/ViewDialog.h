#pragma once
#include "PaperStruct.h"
#include <vector>
#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CDHtmlDialog��"
#endif 
/*
�Ծ�༭������ʦ�ˡ�ѧ���˹��õļ��ز鿴htm���࣬ʹ��ʱ�ڸ�����Ŀ�����htm��Ҫ��dlg��htm��ʹ��ʱ�ڹ��캯���д���ID
*/
// CViewDialog �Ի���
class CViewDialog : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CViewDialog)

public:
	CViewDialog(CWnd* pParent = NULL);   // ��׼���캯��
	CViewDialog(UINT idDlg,UINT idHtm,const stuPaper &paper,const ePaperViewType & type, const CString & filePath,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CViewDialog();
// ��д
	HRESULT On_btn_close(IHTMLElement *pElement);
	HRESULT On_btn_submit(IHTMLElement* pElement);

	//�ر��˳�����
	void close_window();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIEWDIALOG, IDH = IDR_HTML_VIEWDIALOG };
#endif

protected:
	virtual BOOL CanAccessExternal(){ return TRUE; };			//���Ρ��ڴ�ҳ�ϵ�ActiveX�ؼ��ͱ�ҳ�ϵ��������ֵĽ������ܲ���ȫ,Ȼ����excel���ǵ�
	//virtual BOOL IsExternalDispatchSafe(){ return TRUE; }		//Ĭ������activex
	void	OnDocumentComplete(LPDISPATCH pDisp,LPCTSTR szUrl);	//�������
	virtual void DoDataExchange(CDataExchange* pDX);			// DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message,WPARAM wParam,LPARAM lParam);	//��Ϣ����
	virtual HRESULT STDMETHODCALLTYPE ShowContextMenu(DWORD dwID,POINT *ppt,IUnknown *pcmdtReserved,IDispatch *pdispReserved);//�����Ҽ�

private:
	//���ص�htm·��
	CString m_filePath;
	//��ʾ���ͣ���ӡ��ʹ��Ҫ�õ�
	ePaperViewType m_type;
	//�Ծ�
	const stuPaper * m_pPaper;
	//����ض���ť�󣬿��ԹرնԻ���
	BOOL m_bCanClose;

private:
	VOID set_answer_score(VARIANT & row, VARIANT & col, VARIANT & value);			//���ش�����

public:
	//�𰸽ṹ
	stuPaper m_answer;
	//��ʦ����
	std::vector<double> m_score;

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
	DECLARE_DISPATCH_MAP()
public:
	//���θ����˳���ʽ��ֻ���ڵ���ض���ť���˳�
	virtual void OnOK();
	virtual void OnCancel();
};
