
// TrayAndBubble.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTrayAndBubbleApp: 
// �йش����ʵ�֣������ TrayAndBubble.cpp
//

class CTrayAndBubbleApp : public CWinApp
{
public:
	CTrayAndBubbleApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTrayAndBubbleApp theApp;