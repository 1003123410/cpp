
// NamePipeClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNamePipeClientApp: 
// �йش����ʵ�֣������ NamePipeClient.cpp
//

class CNamePipeClientApp : public CWinApp
{
public:
	CNamePipeClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNamePipeClientApp theApp;