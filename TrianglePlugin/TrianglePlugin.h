// TrianglePlugin.h : main header file for the TrianglePlugin DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTrianglePluginApp
// See TrianglePlugin.cpp for the implementation of this class
//

class CTrianglePluginApp : public CWinApp
{
public:
	CTrianglePluginApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
