
// SuspendProcess.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSuspendProcessApp: 
// �йش����ʵ�֣������ SuspendProcess.cpp
//

class CSuspendProcessApp : public CWinApp
{
public:
	CSuspendProcessApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSuspendProcessApp theApp;