
// EnumService.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEnumServiceApp: 
// �йش����ʵ�֣������ EnumService.cpp
//

class CEnumServiceApp : public CWinApp
{
public:
	CEnumServiceApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEnumServiceApp theApp;