// Register.cpp : implementation file
//

#include "stdafx.h"
#include "melodia.h"
#include "Register.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegister dialog


CRegister::CRegister(CWnd* pParent /*=NULL*/)
	: CDialog(CRegister::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegister)
	m_username = _T("");
	m_password = _T("");
	m_confirm = _T("");
	//}}AFX_DATA_INIT
}


void CRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegister)
	DDX_Text(pDX, IDC_USERNAME, m_username);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDX_Text(pDX, IDC_CONFIRM, m_confirm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegister, CDialog)
	//{{AFX_MSG_MAP(CRegister)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegister message handlers
