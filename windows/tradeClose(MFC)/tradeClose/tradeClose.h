
// tradeClose.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CtradeCloseApp: 
// �йش����ʵ�֣������ tradeClose.cpp
//

class CtradeCloseApp : public CWinApp
{
public:
	CtradeCloseApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CtradeCloseApp theApp;