#if !defined(AFX_NOTEINFOVIEW_H__C80732B8_489F_4AAD_AE2E_3F1EA1DFB4B8__INCLUDED_)
#define AFX_NOTEINFOVIEW_H__C80732B8_489F_4AAD_AE2E_3F1EA1DFB4B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NoteInfoView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNoteInfoView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "NoteInfo.h"

class CNoteInfoView : public CFormView
{
protected:
	CNoteInfoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CNoteInfoView)

// Form Data
public:
	//{{AFX_DATA(CNoteInfoView)
	enum { IDD = IDD_NOTEINFOVIEW };
	CSpinButtonCtrl	m_spin;
	CListBox	m_noteList;
	int		m_bar;
	int		m_denominator;
	int		m_hold;
	int		m_holdDenominator;
	int		m_numerator;
	int		m_time;
	int		m_track;
	int		m_holdNumerator;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoteInfoView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CNoteInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CNoteInfoView)
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnSelchangeNotelist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTEINFOVIEW_H__C80732B8_489F_4AAD_AE2E_3F1EA1DFB4B8__INCLUDED_)
