#if !defined(AFX_REGISTER_H__71ADA580_BF9B_49B3_8CD4_F4AD9AE887E0__INCLUDED_)
#define AFX_REGISTER_H__71ADA580_BF9B_49B3_8CD4_F4AD9AE887E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Register.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegister dialog

class CRegister : public CDialog
{
// Construction
public:
	CRegister(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRegister)
	enum { IDD = IDD_REGISTER };
	CString	m_username;
	CString	m_password;
	CString	m_confirm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegister)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegister)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTER_H__71ADA580_BF9B_49B3_8CD4_F4AD9AE887E0__INCLUDED_)
