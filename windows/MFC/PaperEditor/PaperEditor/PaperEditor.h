
// PaperEditor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPaperEditorApp: 
// �йش����ʵ�֣������ PaperEditor.cpp
//

class CPaperEditorApp : public CWinApp
{
public:
	CPaperEditorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPaperEditorApp theApp;