
// PowerMassage.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPowerMassageApp: 
// �йش����ʵ�֣������ PowerMassage.cpp
//

class CPowerMassageApp : public CWinApp
{
public:
	CPowerMassageApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPowerMassageApp theApp;