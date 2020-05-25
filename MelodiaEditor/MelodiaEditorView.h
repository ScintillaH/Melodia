// MelodiaEditorView.h : interface of the CMelodiaEditorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MELODIAEDITORVIEW_H__2E3F44A3_7F01_4BE1_B70D_AC91362C5B12__INCLUDED_)
#define AFX_MELODIAEDITORVIEW_H__2E3F44A3_7F01_4BE1_B70D_AC91362C5B12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MelodiaEditorDoc.h"


class CMelodiaEditorView : public CView
{
protected: // create from serialization only
	CMelodiaEditorView();
	DECLARE_DYNCREATE(CMelodiaEditorView)

// Attributes
public:
	CMelodiaEditorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMelodiaEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMelodiaEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMelodiaEditorView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRect area;
};

#ifndef _DEBUG  // debug version in MelodiaEditorView.cpp
inline CMelodiaEditorDoc* CMelodiaEditorView::GetDocument()
   { return (CMelodiaEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MELODIAEDITORVIEW_H__2E3F44A3_7F01_4BE1_B70D_AC91362C5B12__INCLUDED_)
