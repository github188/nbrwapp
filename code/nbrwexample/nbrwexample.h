// nbrwexample.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CnbrwexampleApp:
// �йش����ʵ�֣������ nbrwexample.cpp
//

class CnbrwexampleApp : public CWinApp
{
public:
	CnbrwexampleApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CnbrwexampleApp theApp;