
// EnumModule.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEnumModuleApp: 
// �йش����ʵ�֣������ EnumModule.cpp
//

class CEnumModuleApp : public CWinApp
{
public:
	CEnumModuleApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEnumModuleApp theApp;