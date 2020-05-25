#if !defined(AFX_AUDIOVIEW_H__AFEE50CF_4FF5_4D5A_B88E_38D44D3A4BEC__INCLUDED_)
#define AFX_AUDIOVIEW_H__AFEE50CF_4FF5_4D5A_B88E_38D44D3A4BEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AudioView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAudioView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CAudioView : public CFormView
{
protected:
	CAudioView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAudioView)

// Form Data
public:
	//{{AFX_DATA(CAudioView)
	enum { IDD = IDD_AUDIOVIEW };
	CSliderCtrl	m_slider;
	int		m_bar;
	int		m_denominator;
	int		m_numerator;
	int		m_position;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudioView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAudioView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAudioView)
	afx_msg void OnAudioPlay();
	afx_msg void OnAudioPause();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSetStart();
	afx_msg void OnLocate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_isPlay;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUDIOVIEW_H__AFEE50CF_4FF5_4D5A_B88E_38D44D3A4BEC__INCLUDED_)
