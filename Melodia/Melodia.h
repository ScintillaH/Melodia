// Melodia.h : main header file for the MELODIA application
//

#if !defined(AFX_MELODIA_H__13B63DA3_ACD8_4EB8_ABBD_7BBAA94A40B0__INCLUDED_)
#define AFX_MELODIA_H__13B63DA3_ACD8_4EB8_ABBD_7BBAA94A40B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMelodiaApp:
// See Melodia.cpp for the implementation of this class
//

class CMelodiaApp : public CWinApp
{
public:
	CMelodiaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMelodiaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMelodiaApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MELODIA_H__13B63DA3_ACD8_4EB8_ABBD_7BBAA94A40B0__INCLUDED_)
