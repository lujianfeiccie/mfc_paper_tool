
// paper_tool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cpaper_toolApp:
// �йش����ʵ�֣������ paper_tool.cpp
//

class Cpaper_toolApp : public CWinApp
{
public:
	Cpaper_toolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cpaper_toolApp theApp;