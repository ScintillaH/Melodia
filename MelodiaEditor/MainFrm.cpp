// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MelodiaEditor.h"

#include "MainFrm.h"
#include "MelodiaEditorView.h"
#include "NoteInfoView.h"
#include "AudioView.h"
#include "ProjectInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_COMMAND(ID_VIEW_PROJECTINFO, OnViewProjectinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	/*return m_wndSplitter.Create(this,
		2, 2,               // TODO: adjust the number of rows, columns
		CSize(10, 10),      // TODO: adjust the minimum pane size
		pContext);*/
	VERIFY(m_wndSplitter.CreateStatic(this, 1, 3));
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CNoteInfoView), CSize(0, 0), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CAudioView), CSize(0, 0), pContext);
	m_wndSplitter.CreateView(0, 2, RUNTIME_CLASS(CMelodiaEditorView), CSize(0, 0), pContext);
	CNoteInfoView *pWnd1 = (CNoteInfoView *)m_wndSplitter.GetPane(0, 0);
	CSize size = pWnd1->GetTotalSize();
	m_wndSplitter.SetColumnInfo(0, size.cx, 1);
	CAudioView *pWnd2 = (CAudioView *)m_wndSplitter.GetPane(0, 1);
	size = pWnd2->GetTotalSize();
	m_wndSplitter.SetColumnInfo(1, size.cx, 1);
	return true;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnFileExport() 
{
	// TODO: Add your command handler code here
	CMelodiaEditorDoc* pDoc = (CMelodiaEditorDoc *)GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->m_name == "" || pDoc->m_bg == "" || pDoc->m_cover == "" || pDoc->m_preview == "" || pDoc->m_full == "")
	{
		AfxMessageBox("请完善工程信息！");
		return;
	}

	char path[256];
	CString str;
	BROWSEINFO bi;

	ZeroMemory(path, sizeof(path));
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = path;
	bi.lpszTitle = "请选择导出目录：(Melodia游戏目录)";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	LPITEMIDLIST lp = SHBrowseForFolder(&bi);
	if(lp && SHGetPathFromIDList(lp, path))
	{
		pDoc->m_name.Replace(' ', '_');
		str.Format("%s\\songs\\%s", path, pDoc->m_name);
		CreateDirectory(str, NULL);
		str.Format("%s\\songs\\%s\\bg.bmp", path, pDoc->m_name);
		CopyFile(pDoc->m_bg, str, false);
		str.Format("%s\\songs\\%s\\cover.bmp", path, pDoc->m_name);
		CopyFile(pDoc->m_cover, str, false);
		str.Format("%s\\songs\\%s\\preview.mp3", path, pDoc->m_name);
		CopyFile(pDoc->m_preview, str, false);
		str.Format("%s\\songs\\%s\\full.mp3", path, pDoc->m_name);
		CopyFile(pDoc->m_full, str, false);

		str.Format("%s\\data\\songs.txt", path);
		CStdioFile songs(str, CFile::modeRead | CFile::typeText);
		songs.ReadString(str);
		int songsNum = atoi(str);
		CString *songsName = new CString[songsNum];
		for (int i = 0; i < songsNum; i++)
		{
			songs.ReadString(str);
			songsName[i] = str;
		}
		songs.Close();
		str.Format("%s\\data\\songs.txt", path);
		songs.Open(str, CFile::modeCreate | CFile::modeWrite);
		str.Format("%d\n", songsNum + 1);
		songs.WriteString(str);
		for (i = 0; i < songsNum; i++)
		{
			songs.WriteString(songsName[i]);
			songs.WriteString("\n");
		}
		str.Format("%s\t%s\n", pDoc->m_name, pDoc->m_composer);
		songs.WriteString(str);
		songs.Close();

		str.Format("%s\\songs\\%s\\score.txt", path, pDoc->m_name);
		CStdioFile score(str, CFile::modeCreate | CFile::modeWrite);
		str.Format("%d\n", pDoc->m_notesNum);
		score.WriteString(str);
		for (i = 0; i < pDoc->m_notesNum; i++)
		{
			CNoteInfo *note = pDoc->GetNoteInfo(i);
			int noteTime = (int)(240000.0 / pDoc->m_bpm * (note->bar - 1 + (double)note->numerator / note->denominator) + pDoc->m_startPos);
			int noteHold = 0;
			if (note->holdDenominator != 0)
				noteHold = (int)(240000.0 / pDoc->m_bpm * note->holdNumerator / note->holdDenominator);
			str.Format("%d\t%d\t%d\n", noteTime, note->track, noteHold);
			score.WriteString(str);
		}
		delete []songsName;
		AfxMessageBox("导出完成！");
	}
}

void CMainFrame::OnViewProjectinfo() 
{
	// TODO: Add your command handler code here
	CMelodiaEditorDoc* pDoc = (CMelodiaEditorDoc *)GetActiveDocument();
	ASSERT_VALID(pDoc);
	CProjectInfo dlg;
	dlg.m_name = pDoc->m_name;
	dlg.m_composer = pDoc->m_composer;
	dlg.m_bpm = pDoc->m_bpm;
	dlg.m_notesNum = pDoc->m_notesNum;
	dlg.m_startPos = pDoc->m_startPos;
	dlg.m_bg = pDoc->m_bg;
	dlg.m_cover = pDoc->m_cover;
	dlg.m_preview = pDoc->m_preview;
	dlg.m_full = pDoc->m_full;
	if (dlg.DoModal() == IDOK)
	{
		pDoc->m_name = dlg.m_name;
		pDoc->m_composer = dlg.m_composer;
		pDoc->m_bpm = dlg.m_bpm;
		pDoc->m_startPos = dlg.m_startPos;
		pDoc->m_bg = dlg.m_bg;
		pDoc->m_cover = dlg.m_cover;
		pDoc->m_preview = dlg.m_preview;
		pDoc->m_full = dlg.m_full;
		pDoc->SetModifiedFlag();
		pDoc->UpdateAllViews(NULL);
	}	
}
