
// testQtDll.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CtestQtDllApp: 
// �йش����ʵ�֣������ testQtDll.cpp
//

class CtestQtDllApp : public CWinApp
{
public:
	CtestQtDllApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CtestQtDllApp theApp;