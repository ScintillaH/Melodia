#if !defined(AFX_PROJECTINFO_H__E472029A_37F3_4233_B892_4C76EECBDAA8__INCLUDED_)
#define AFX_PROJECTINFO_H__E472029A_37F3_4233_B892_4C76EECBDAA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProjectInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProjectInfo dialog

class CProjectInfo : public CDialog
{
// Construction
public:
	CProjectInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProjectInfo)
	enum { IDD = IDD_PROJECTINFO };
	int		m_bpm;
	CString	m_name;
	int		m_notesNum;
	int		m_startPos;
	CString	m_bg;
	CString	m_cover;
	CString	m_full;
	CString	m_preview;
	CString	m_composer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProjectInfo)
	afx_msg void OnSelectBg();
	afx_msg void OnSelectCover();
	afx_msg void OnSelectPreview();
	afx_msg void OnSelectFull();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTINFO_H__E472029A_37F3_4233_B892_4C76EECBDAA8__INCLUDED_)
