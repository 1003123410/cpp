
// AdaptInfo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAdaptInfoApp: 
// �йش����ʵ�֣������ AdaptInfo.cpp
//

class CAdaptInfoApp : public CWinApp
{
public:
	CAdaptInfoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAdaptInfoApp theApp;