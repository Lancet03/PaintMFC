// RectanglePlugin.h : main header file for the RectanglePlugin DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRectanglePluginApp
// See RectanglePlugin.cpp for the implementation of this class
//

class CRectanglePluginApp : public CWinApp
{
public:
	CRectanglePluginApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
