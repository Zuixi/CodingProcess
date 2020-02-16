
// MFCChapter2.h : main header file for the MFCChapter2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCChapter2App:
// See MFCChapter2.cpp for the implementation of this class
//

class CMFCChapter2App : public CWinAppEx
{
public:
	CMFCChapter2App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCChapter2App theApp;
