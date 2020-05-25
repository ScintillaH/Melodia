// ProjectInfo.cpp : implementation file
//

#include "stdafx.h"
#include "MelodiaEditor.h"
#include "ProjectInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectInfo dialog


CProjectInfo::CProjectInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjectInfo)
	m_bpm = 0;
	m_name = _T("");
	m_notesNum = 0;
	m_startPos = 0;
	m_bg = _T("");
	m_cover = _T("");
	m_full = _T("");
	m_preview = _T("");
	m_composer = _T("");
	//}}AFX_DATA_INIT
}


void CProjectInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectInfo)
	DDX_Text(pDX, IDC_BPM, m_bpm);
	DDV_MinMaxInt(pDX, m_bpm, 1, 300);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_NOTESNUM, m_notesNum);
	DDX_Text(pDX, IDC_STARTPOS, m_startPos);
	DDV_MinMaxInt(pDX, m_startPos, 0, 10000);
	DDX_Text(pDX, IDC_BGBMP, m_bg);
	DDX_Text(pDX, IDC_COVERBMP, m_cover);
	DDX_Text(pDX, IDC_FULL, m_full);
	DDX_Text(pDX, IDC_PREVIEW, m_preview);
	DDX_Text(pDX, IDC_COMPOSER, m_composer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProjectInfo, CDialog)
	//{{AFX_MSG_MAP(CProjectInfo)
	ON_BN_CLICKED(IDC_SELECT_BG, OnSelectBg)
	ON_BN_CLICKED(IDC_SELECT_COVER, OnSelectCover)
	ON_BN_CLICKED(IDC_SELECT_PREVIEW, OnSelectPreview)
	ON_BN_CLICKED(IDC_SELECT_FULL, OnSelectFull)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectInfo message handlers

void CProjectInfo::OnSelectBg() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(true, "bmp", "*.bmp", OFN_HIDEREADONLY, "位图文件 (*.bmp) | *.bmp ||");
	if (dlg.DoModal() == IDOK)
	{
		UpdateData();
		m_bg = dlg.GetPathName();
		HBITMAP hbmp;
		CBitmap bmp;
		hbmp = (HBITMAP)LoadImage(AfxGetInstanceHandle(), m_bg, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		bmp.Attach(hbmp);
		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);
		if (bmpInfo.bmWidth != 360 || bmpInfo.bmHeight != 225)
		{
			MessageBox("所选图片大小需为360×225", "提示", MB_ICONWARNING);
			m_bg = "";
		}
		bmp.DeleteObject();
		UpdateData(false);
	}
}

void CProjectInfo::OnSelectCover() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(true, "bmp", "*.bmp", OFN_HIDEREADONLY, "位图文件 (*.bmp) | *.bmp ||");
	if (dlg.DoModal() == IDOK)
	{
		UpdateData();
		m_cover = dlg.GetPathName();
		HBITMAP hbmp;
		CBitmap bmp;
		hbmp = (HBITMAP)LoadImage(AfxGetInstanceHandle(), m_cover, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		bmp.Attach(hbmp);
		BITMAP bmpInfo;
		bmp.GetBitmap(&bmpInfo);
		if (bmpInfo.bmWidth != 300 || bmpInfo.bmHeight != 300)
		{
			MessageBox("所选图片大小需为300×300", "提示", MB_ICONWARNING);
			m_cover = "";
		}
		bmp.DeleteObject();
		UpdateData(false);
	}
}

void CProjectInfo::OnSelectPreview() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(true, "mp3", "*.mp3", OFN_HIDEREADONLY, "MP3文件 (*.mp3) | *.mp3 ||");
	if (dlg.DoModal() == IDOK)
	{
		UpdateData();
		m_preview = dlg.GetPathName();
		UpdateData(false);
	}
}

void CProjectInfo::OnSelectFull() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(true, "mp3", "*.mp3", OFN_HIDEREADONLY, "MP3文件 (*.mp3) | *.mp3 ||");
	if (dlg.DoModal() == IDOK)
	{
		UpdateData();
		m_full = dlg.GetPathName();
		UpdateData(false);
	}
}
