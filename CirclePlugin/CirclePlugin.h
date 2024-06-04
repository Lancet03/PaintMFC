// CirclePlugin.h : main header file for the CirclePlugin DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCirclePluginApp
// See CirclePlugin.cpp for the implementation of this class
//

class CCirclePluginApp : public CWinApp
{
public:
	CCirclePluginApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
