
// resendSocket.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CresendSocketApp: 
// �йش����ʵ�֣������ resendSocket.cpp
//

class CresendSocketApp : public CWinApp
{
public:
	CresendSocketApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CresendSocketApp theApp;