
// NamePipe.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNamePipeApp: 
// �йش����ʵ�֣������ NamePipe.cpp
//

class CNamePipeApp : public CWinApp
{
public:
	CNamePipeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNamePipeApp theApp;