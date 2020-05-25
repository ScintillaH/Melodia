// MelodiaEditor.h : main header file for the MELODIAEDITOR application
//

#if !defined(AFX_MELODIAEDITOR_H__46F567DF_B99F_4FF6_B5E1_0A8EF8304AC3__INCLUDED_)
#define AFX_MELODIAEDITOR_H__46F567DF_B99F_4FF6_B5E1_0A8EF8304AC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMelodiaEditorApp:
// See MelodiaEditor.cpp for the implementation of this class
//

class CMelodiaEditorApp : public CWinApp
{
public:
	CMelodiaEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMelodiaEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMelodiaEditorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MELODIAEDITOR_H__46F567DF_B99F_4FF6_B5E1_0A8EF8304AC3__INCLUDED_)
