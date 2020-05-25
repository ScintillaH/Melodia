// MelodiaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Melodia.h"
#include "MelodiaDlg.h"
#include "Curves.h"
#include "Login.h"
#include "Register.h"
#include <mmsystem.h>
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void Encode(CString &str)
{
	int key[] = {1, 2, 3, 4, 5, 6, 7};
	int length = str.GetLength();
	char *ch = str.GetBuffer(0);
	for (int i = 0; i < length; i++)
	{
		ch[i] ^= key[i % 7];
	}
	str.ReleaseBuffer();
}

void Decode(CString &str)
{
	int key[] = {1, 2, 3, 4, 5, 6, 7};
	int length = str.GetLength();
	char *ch = str.GetBuffer(0);
	for (int i = 0; i < length; i++)
	{
		ch[i] ^= key[i % 7];
	}
	str.ReleaseBuffer();
}

void Effect::Update(CRect *rect, CDC *pDC, int deltaTime)
{
	if (enable)
	{
		POINT pts[4], origin;
		origin.x = rect->right / 2 - 280 + track * 80;
		origin.y = rect->bottom - 100;
		pts[0].x = origin.x - Decel(0, 150, duration / 500.0);
		pts[2].x = origin.x + Decel(0, 150, duration / 500.0);
		pts[0].y = pts[2].y = origin.y;
		pts[1].y = origin.y - Decel(0, 150, duration / 500.0);
		pts[3].y = origin.y + Decel(0, 150, duration / 500.0);
		pts[1].x = pts[3].x = origin.x;
		int lineWidth = Decel(40, 0, duration / 500.0);
		CPen *oldPen, newPen;
		CBrush *oldBrush, newBrush;
		newPen.CreatePen(PS_SOLID, lineWidth, lineColor);
		newBrush.CreateStockObject(NULL_BRUSH);
		oldPen = pDC->SelectObject(&newPen);
		oldBrush = pDC->SelectObject(&newBrush);
		pDC->Polygon(pts, 4);
		pDC->SelectObject(oldPen);
		pDC->SelectObject(oldBrush);
		newPen.DeleteObject();
		newBrush.DeleteObject();
		duration += deltaTime;
		if (duration >= 500.0)
		{
			Reset();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMelodiaDlg dialog

CMelodiaDlg::CMelodiaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMelodiaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMelodiaDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_showFPS = false;
	m_dropSpeed = 6;
	m_beat = true;
	for (int i = 0; i < 8; i++)
	{
		keys[i].Reset();
	}
	songsName = NULL;
	songsComposer = NULL;
	score = NULL;
	noteCount = 0;
	usersInfo = NULL;
	userData = NULL;
	usersNum = 0;
}

void CALLBACK CMelodiaDlg::TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	CWnd::FromHandle(hWnd)->Invalidate(false);
}

void CMelodiaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMelodiaDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMelodiaDlg, CDialog)
	//{{AFX_MSG_MAP(CMelodiaDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_DISPLAY_FPS, OnDisplayFps)
	ON_UPDATE_COMMAND_UI(ID_DISPLAY_FPS, OnUpdateDisplayFps)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_DISPLAY_RESOLUTION1, OnDisplayResolution1)
	ON_COMMAND(ID_DISPLAY_RESOLUTION2, OnDisplayResolution2)
	ON_COMMAND(ID_DISPLAY_RESOLUTION3, OnDisplayResolution3)
	ON_COMMAND(ID_LEAP_SELECT, OnLeapSelect)
	ON_COMMAND(ID_LEAP_START, OnLeapStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMelodiaDlg message handlers

BOOL CMelodiaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetTimer(1, 10, TimerProc);
	SetTimer(2, 400, NULL);
	curTime = GetTickCount();
	deltaTime = 0;
	GetClientRect(&area);

	startButtons[0].SetText("开始游戏");
	startButtons[1].SetText("游戏帮助");
	startButtons[2].SetText("登录");
	startButtons[3].SetText("注册");
	startBmpButtons[0].SetBitmap(IDB_SETTINGS_NORMAL, IDB_SETTINGS_FOCUS);
	startBmpButtons[1].SetBitmap(IDB_EXIT_NORMAL, IDB_EXIT_FOCUS);
	settingsButtons[0].SetText("－");
	settingsButtons[1].SetText("＋");
	settingsButtons[2].SetText("ON");
	selectBmpButtons[0].SetBitmap(IDB_PREV_NORMAL, IDB_PREV_FOCUS);
	selectBmpButtons[1].SetBitmap(IDB_START_NORMAL, IDB_START_FOCUS);
	selectBmpButtons[2].SetBitmap(IDB_NEXT_NORMAL, IDB_NEXT_FOCUS);
	selectBmpButtons[3].SetBitmap(IDB_BACK_NORMAL, IDB_BACK_FOCUS);
	exitButton.SetBitmap(IDB_EXIT_NORMAL, IDB_EXIT_FOCUS);

	animator.duration = 0;
	animator.state = 1;
	for (int i = 0; i < 20; i++)
	{
		effector[i].Reset();
	}
	state = 1;
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.AlphaFormat = 0;
	
	CStdioFile songsInfo("data\\songs.txt", CFile::typeText | CFile::modeRead);
	CString str, folder;
	songsInfo.ReadString(str);
	songsNum = atoi(str);
	if (songsNum > 0)
	{
		userData = new int[songsNum];
		songsName = new CString[songsNum];
		songsComposer = new CString[songsNum];
		for (int i = 0; i < songsNum; i++)
		{
			songsInfo.ReadString(str);
			songsName[i] = str.Left(str.Find(_T('\t')));
			songsComposer[i] = str.Mid(str.Find(_T('\t')) + 1);
			str.Format("open songs\\%s\\preview.mp3 alias preview%d", songsName[i], i);
			mciSendString(str, 0, 0, 0);
			str.Format("open songs\\%s\\full.mp3 alias full%d", songsName[i], i);
			mciSendString(str, 0, 0, 0);
		}
	}
	songsInfo.Close();
	songSelection = 0;
	stat.Reset();

	CStdioFile usersFile("data\\users.txt", CFile::typeText | CFile::modeRead);
	usersFile.ReadString(str);
	usersNum = atoi(str);
	userName = "";
	if (usersNum > 0)
	{
		usersInfo = new CString[usersNum][2];
		for (int i = 0; i < usersNum; i++)
		{
			usersFile.ReadString(str);
			usersInfo[i][0] = str.Left(str.Find('\t'));
			usersInfo[i][1] = str.Mid(str.Find('\t') + 1);
			Decode(usersInfo[i][1]);
		}
	}

	mciSendString("open res\\audio\\menu.mp3 alias menu", 0, 0, 0);
	mciSendString("open res\\audio\\buttonclick.mp3 alias buttonclick", 0, 0, 0);
	mciSendString("open res\\audio\\start.mp3 alias start", 0, 0, 0);
	mciSendString("open res\\audio\\beat.wav alias beat", 0, 0, 0);
	mciSendString("play menu repeat", 0, 0, 0);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMelodiaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

BOOL CMelodiaDlg::OnEraseBkgnd(CDC *pDC)
{
	return true;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMelodiaDlg::OnPaint() 
{
	deltaTime = GetTickCount() - curTime;
	curTime = GetTickCount();
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		GetClientRect(&area);
		CPaintDC dc(this);
		CDC memDC;
		CBitmap memBmp;
		memDC.CreateCompatibleDC(NULL);
		memBmp.CreateCompatibleBitmap(&dc, area.Width(), area.Height());
		memDC.SetBkMode(TRANSPARENT);
		CBitmap *oldBmp = memDC.SelectObject(&memBmp);

		if (animator.state == 0)
		{
			switch (state)
			{
			case 1:
				UpdateStart(&memDC);
				break;
			case 2:
				UpdateHelp(&memDC);
				break;
			case 3:
				UpdateSettings(&memDC);
				break;
			case 4:
				UpdateSelect(&memDC);
				break;
			case 5:
				UpdatePlay(&memDC);
				break;
			case 6:
				UpdateResult(&memDC);
				break;
			}
		}
		else
		{
			switch (animator.state)
			{
			case 1:
				FadeIn(0, &memDC);
				break;
			case 2:
				FadeOut(0, &memDC);
				break;
			case 3:
				UpdateStart(&memDC);
				ButtonExpand(0, &memDC);
				break;
			case 4:
				UpdateStart(&memDC);
				ButtonWithdraw(0, &memDC);
				break;
			case 5:
				SongChange(0, &memDC);
				break;
			case 6:
				SceneChange(0, &memDC);
				break;
			}
		}
		if (m_showFPS)
		{
			CString str;
			str.Format("FPS: %d", m_FPSValue);
			memDC.SetBkMode(OPAQUE);
			memDC.SetBkColor(RGB(0, 0, 0));
			memDC.SetTextColor(RGB(255, 255, 255));
			memDC.TextOut(0, 0, str);
		}

		dc.BitBlt(0, 0, area.Width(), area.Height(), &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(oldBmp);
		memDC.DeleteDC();
		memBmp.DeleteObject();
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMelodiaDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMelodiaDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (userName != "")
	{
		CString str;
		str.Format("data\\%s.txt", userName);
		CStdioFile userDataFile(str, CFile::modeCreate | CFile::modeWrite);
		for (int i = 0; i < songsNum; i++)
		{
			str.Format("%d\n", userData[i]);
			userDataFile.WriteString(str);
		}
	}
	if (songsName)
		delete []songsName;
	if (songsComposer)
		delete []songsComposer;
	if (score)
		delete []score;
	if (usersInfo)
		delete []usersInfo;
	if (userData)
		delete []userData;
	KillTimer(1);
	KillTimer(2);
	CDialog::OnClose();
}

void CMelodiaDlg::OnHelpAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

void CMelodiaDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	if (animator.state == 0)
	{
		switch (state)
		{
		case 1:
			if (startButtons[0].InRect(point.x, point.y))
			{
				FadeOut(1, NULL);
				state = 4;
				mciSendString("play buttonclick from 0", 0, 0, 0);
			}
			else if (startButtons[1].InRect(point.x, point.y))
			{
				ButtonExpand(1, NULL);
				state = 2;
				mciSendString("play buttonclick from 0", 0, 0, 0);
			}
			else if (startButtons[2].InRect(point.x, point.y))
			{
				OnLogin();
			}
			else if (startButtons[3].InRect(point.x, point.y))
			{
				OnRegister();
			}
			else if (startBmpButtons[0].InRect(point.x, point.y))
			{
				ButtonExpand(2, NULL);
				state = 3;
				mciSendString("play buttonclick from 0", 0, 0, 0);
			}
			else if (startBmpButtons[1].InRect(point.x, point.y))
			{
				mciSendString("play buttonclick from 0", 0, 0, 0);
				if(MessageBox("确定要退出吗？", NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
				{
					SendMessage(WM_CLOSE);
				}
			}
			break;
		case 3:
			if (settingsButtons[0].InRect(point.x, point.y))
			{
				if (m_dropSpeed > 1)
					m_dropSpeed--;
			}
			else if (settingsButtons[1].InRect(point.x, point.y))
			{
				if (m_dropSpeed < 9)
					m_dropSpeed++;
			}
			else if (settingsButtons[2].InRect(point.x, point.y))
			{
				if (m_beat)
				{
					m_beat = false;
					settingsButtons[2].SetText("OFF");
				}
				else
				{
					m_beat = true;
					settingsButtons[2].SetText("ON");
				}
			}
		case 2:
			if (exitButton.InRect(point.x, point.y))
			{
				ButtonWithdraw(state - 1, NULL);
				state = 1;
				mciSendString("play buttonclick from 0", 0, 0, 0);
			}
			break;
		case 4:
			if (selectBmpButtons[0].InRect(point.x, point.y))
			{
				SongChange(-1, NULL);
				str.Format("play preview%d repeat from 0", songSelection);
				mciSendString(str, 0, 0, 0);
				str.Format("setaudio preview%d volume to 1000", songSelection);
				mciSendString(str, 0, 0, 0);
				mciSendString("play buttonclick from 0", 0, 0, 0);
			}
			else if (selectBmpButtons[1].InRect(point.x, point.y))
			{
				SceneChange(1, NULL);
				state = 5;
				mciSendString("play start from 0", 0, 0, 0);
			}
			else if (selectBmpButtons[2].InRect(point.x, point.y))
			{
				SongChange(1, NULL);
				str.Format("play preview%d repeat from 0", songSelection);
				mciSendString(str, 0, 0, 0);
				str.Format("setaudio preview%d volume to 1000", songSelection);
				mciSendString(str, 0, 0, 0);
				mciSendString("play buttonclick from 0", 0, 0, 0);
			}
			else if (selectBmpButtons[3].InRect(point.x, point.y))
			{
				FadeOut(4, NULL);
				state = 1;
				mciSendString("play buttonclick from 0", 0, 0, 0);
			}
			break;
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CMelodiaDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (state != 5 || animator.state != 0)
		return;
	int keyNum = -1;
	switch (nChar)
	{
	case 'A':
		keyNum = 0;
		break;
	case 'S':
		keyNum = 1;
		break;
	case 'D':
		keyNum = 2;
		break;
	case 'F':
		keyNum = 3;
		break;
	case 'J':
		keyNum = 4;
		break;
	case 'K':
		keyNum = 5;
		break;
	case 'L':
		keyNum = 6;
		break;
	case 186:
		keyNum = 7;
		break;
	}
	if (keyNum != -1 && !keys[keyNum].down)
	{
		keys[keyNum].down = true;
		keys[keyNum].downTime = GetTickCount() - startTime;
	}
}

void CMelodiaDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (state != 5 || animator.state != 0)
		return;
	int keyNum = -1;
	switch (nChar)
	{
	case 'A':
		keyNum = 0;
		break;
	case 'S':
		keyNum = 1;
		break;
	case 'D':
		keyNum = 2;
		break;
	case 'F':
		keyNum = 3;
		break;
	case 'J':
		keyNum = 4;
		break;
	case 'K':
		keyNum = 5;
		break;
	case 'L':
		keyNum = 6;
		break;
	case 186:
		keyNum = 7;
		break;
	}
	if (keyNum != -1 && keys[keyNum].down)
	{
		keys[keyNum].down = false;
		keys[keyNum].upTime = GetTickCount() - startTime;
	}
}

BOOL CMelodiaDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		if (animator.state == 0 && state == 6)
		{
			FadeOut(state, NULL);
			state = 4;
		}
		else if (animator.state == 0 && state == 5)
		{
			SceneChange(-1, NULL);
			state = 4;
		}
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (animator.state == 0 && state == 6)
		{
			SceneChange(-2, NULL);
			state = 5;
		}
		else if (animator.state == 0 && state == 5)
		{
			FadeOut(5, NULL);
			state = 5;
		}
		return TRUE;
	}
	else
		return CDialog::PreTranslateMessage(pMsg);
}

void CMelodiaDlg::LoadScore()
{
	if (score)
		delete []score;
	CString str;
	int mark;
	str.Format("songs\\%s\\score.txt", songsName[songSelection]);
	CStdioFile scoreFile(str, CFile::modeRead);
	scoreFile.ReadString(str);
	noteCount = atoi(str);
	score = new NoteInfo[noteCount];
	for (int i = 0; i < noteCount; i++)
	{
		scoreFile.ReadString(str);
		mark = str.Find(_T('\t'));
		score[i].time = atoi(str.Left(mark));
		str.Delete(0, mark + 1);
		mark = str.Find(_T('\t'));
		score[i].track = atoi(str.Left(mark));
		score[i].hold = atoi(str.Mid(mark));
		score[i].judge = 0;
	}
	scoreFile.Close();
}

void CMelodiaDlg::UpdateStart(CDC *pDC)
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	pDC->FillSolidRect(area, RGB(0, 100, 200));
	for (int i = 0; i < 2; i++)
	{
		startButtons[i].SetRect(area.right / 2 + 50, area.bottom / 2 - 50 + 100 * i, area.right / 2 + 350, area.bottom / 2 + 30 + 100 * i);
		if(GetFocus() == this && animator.state < 3)
			startButtons[i].InRect(point.x, point.y);
		startButtons[i].Update(pDC);
	}
	for (i = 0; i < 2; i++)
	{
		if (userName == "")
		{
			startButtons[i + 2].SetRect(area.right / 2 - 400 + 150 * i, area.bottom / 2 + 190, area.right / 2 - 250 + 150 * i, area.bottom / 2 + 270);
			if(GetFocus() == this && animator.state < 3)
				startButtons[i + 2].InRect(point.x, point.y);
			startButtons[i + 2].Update(pDC);
		}
		startBmpButtons[i].SetRect(area.right / 2 + 50 + 160 * i, area.bottom / 2 + 150, area.right / 2 + 190 + 160 * i, area.bottom / 2 + 270);
		if(GetFocus() == this && animator.state < 3)
			startBmpButtons[i].InRect(point.x, point.y);
		startBmpButtons[i].Update(pDC);
	}
	if (userName != "")
	{
		CString str;
		str.Format("欢迎回来，%s", userName);
		CFont *oldFont, newFont;
		newFont.CreateFont(40, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, "微软雅黑");
		oldFont = pDC->SelectObject(&newFont);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->TextOut(area.right / 2 - 400, area.bottom / 2 + 230, str);
		pDC->SelectObject(oldFont);
		newFont.DeleteObject();
	}
}

void CMelodiaDlg::UpdateHelp(CDC *pDC)
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	pDC->FillSolidRect(area, RGB(255, 255, 255));
	CBitmap helpBmp;
	helpBmp.LoadBitmap(IDB_HELP);
	CDC canvas;
	canvas.CreateCompatibleDC(NULL);
	canvas.SelectObject(&helpBmp);
	pDC->BitBlt(area.right / 2 -300, area.bottom / 2 - 200, 600, 350, &canvas, 0, 0, SRCCOPY);
	canvas.DeleteDC();
	helpBmp.DeleteObject();
	CRect caption;
	caption.SetRect(area.left, area.top, area.right, area.top + 80);
	CFont *oldFont, newFont;
	newFont.CreateFont(48, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, "微软雅黑");
	oldFont = pDC->SelectObject(&newFont);
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->DrawText("游戏帮助", caption, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	newFont.DeleteObject();
	
	pDC->SelectObject(oldFont);

	exitButton.SetRect(area.right / 2 + 210, area.bottom / 2 + 150, area.right / 2 + 350, area.bottom / 2 + 270);
	if(GetFocus() == this && animator.state < 3)
		exitButton.InRect(point.x, point.y);
	exitButton.Update(pDC);
}

void CMelodiaDlg::UpdateSettings(CDC *pDC)
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	pDC->FillSolidRect(area, RGB(255, 255, 255));
	CDC canvas;
	canvas.CreateCompatibleDC(NULL);
	CBitmap icon;
	icon.LoadBitmap(IDB_SETTINGS_FOCUS);
	CBitmap *oldBmp = canvas.SelectObject(&icon);
	pDC->BitBlt(area.left, area.top, 140, 120, &canvas, 0, 0, SRCCOPY);
	canvas.SelectObject(oldBmp);
	canvas.DeleteDC();
	icon.DeleteObject();

	CFont *oldFont, newFont;
	newFont.CreatePointFont(240, "微软雅黑");
	oldFont = pDC->SelectObject(&newFont);
	pDC->TextOut(area.right / 2 - 240, area.bottom / 2 - 100, "下落速度");
	pDC->TextOut(area.right / 2 - 240, area.bottom / 2, "击打音");
	CString str;
	str.Format("%d", m_dropSpeed);
	pDC->TextOut(area.right / 2 - 20, area.bottom / 2 - 95, str);
	newFont.DeleteObject();
	
	exitButton.SetRect(area.right / 2 + 210, area.bottom / 2 + 150, area.right / 2 + 350, area.bottom / 2 + 270);
	settingsButtons[0].SetRect(area.right / 2 - 80, area.bottom / 2 - 95, area.right / 2 - 40, area.bottom / 2 - 55);
	settingsButtons[1].SetRect(area.right / 2 + 20, area.bottom / 2 - 95, area.right / 2 + 60, area.bottom / 2 - 55);
	settingsButtons[2].SetRect(area.right / 2 - 80, area.bottom / 2 - 5, area.right / 2 + 20, area.bottom / 2 + 55);
	if(GetFocus() == this && animator.state < 3)
	{
		exitButton.InRect(point.x, point.y);
		settingsButtons[0].InRect(point.x, point.y);
		settingsButtons[1].InRect(point.x, point.y);
		settingsButtons[2].InRect(point.x, point.y);
	}
	exitButton.Update(pDC);
	settingsButtons[0].Update(pDC);
	settingsButtons[1].Update(pDC);
	settingsButtons[2].Update(pDC);
}

void CMelodiaDlg::UpdateSelect(CDC *pDC)
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	CDC canvas;
	canvas.CreateCompatibleDC(NULL);
	HBITMAP hcover, hbg;
	CBitmap cover, bg;
	CString str;

	str.Format("songs\\%s\\cover.bmp", songsName[songSelection]);		//载入与关联位图
	hcover = (HBITMAP)LoadImage(AfxGetInstanceHandle(), str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	cover.Attach(hcover);
	str.Format("songs\\%s\\bg.bmp", songsName[songSelection]);
	hbg = (HBITMAP)LoadImage(AfxGetInstanceHandle(), str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bg.Attach(hbg);

	CBitmap *oldBmp = canvas.SelectObject(&bg);
	if (area.right / 24.0 > area.bottom / 17.0)		//绘制背景
		pDC->StretchBlt(0, (int)((area.bottom - area.right / 24.0 * 17) / 2), area.right, (int)(area.right / 24.0 * 17), &canvas, 0, 0, 360, 225, SRCCOPY);
	else
		pDC->StretchBlt((int)((area.right - area.bottom / 17.0 * 24) / 2), 0, (int)(area.bottom / 17.0 * 24), area.bottom, &canvas, 0, 0, 360, 225, SRCCOPY);
	canvas.SelectObject(&cover);
	pDC->BitBlt(area.right / 2 + 50, area.bottom / 2 - 150, 300, 300, &canvas, 0, 0, SRCCOPY);		//绘制封面

	canvas.SelectObject(oldBmp);
	cover.DeleteObject();
	bg.DeleteObject();
	canvas.DeleteDC();

	CFont *oldFont, newFont;
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);

	newFont.CreateFont(60, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, "微软雅黑");
	oldFont = pDC->SelectObject(&newFont);
	songsName[songSelection].Replace('_', ' ');
	pDC->TextOut(area.right / 2 - 330, area.bottom / 2 - 60, songsName[songSelection]);		//显示标题
	songsName[songSelection].Replace(' ', '_');
	pDC->SelectObject(oldFont);
	newFont.DeleteObject();

	newFont.CreatePointFont(240, "微软雅黑");
	oldFont = pDC->SelectObject(&newFont);
	pDC->TextOut(area.right / 2 - 330, area.bottom / 2, songsComposer[songSelection]);		//显示作者
	if (userName != "")
	{
		str.Format("High Score: %d", userData[songSelection]);
		pDC->TextOut(area.right / 2 - 330, area.bottom / 2 + 50, str);
	}
	pDC->SelectObject(oldFont);
	newFont.DeleteObject();

	selectBmpButtons[0].SetRect(area.right / 2 - 280, area.bottom - 80, area.right / 2 - 200, area.bottom);
	selectBmpButtons[1].SetRect(area.right / 2 - 200, area.bottom - 80, area.right / 2 + 200, area.bottom);
	selectBmpButtons[2].SetRect(area.right / 2 + 200, area.bottom - 80, area.right / 2 + 280, area.bottom);
	selectBmpButtons[3].SetRect(0, 0, 160, 60);
	for (int i = 0; i < 4; i++)		//绘制按钮
	{
		if(GetFocus() == this)
			selectBmpButtons[i].InRect(point.x, point.y);
		selectBmpButtons[i].Update(pDC);
	}
}

void CMelodiaDlg::UpdatePlay(CDC *pDC)
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	CDC canvas;
	canvas.CreateCompatibleDC(NULL);
	HBITMAP hbg;
	CBitmap bg, track, black;
	CString str;
	
	str.Format("songs\\%s\\bg.bmp", songsName[songSelection]);
	hbg = (HBITMAP)LoadImage(AfxGetInstanceHandle(), str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bg.Attach(hbg);
	track.LoadBitmap(IDB_TRACK);
	black.LoadBitmap(IDB_BACKGROUND);

	CBitmap *oldBmp = canvas.SelectObject(&bg);
	if (area.right / 24.0 > area.bottom / 17.0)		//绘制背景
		pDC->StretchBlt(0, (int)((area.bottom - area.right / 24.0 * 17) / 2), area.right, (int)(area.right / 24.0 * 17), &canvas, 0, 0, 360, 225, SRCCOPY);
	else
		pDC->StretchBlt((int)((area.right - area.bottom / 17.0 * 24) / 2), 0, (int)(area.bottom / 17.0 * 24), area.bottom, &canvas, 0, 0, 360, 225, SRCCOPY);
	canvas.SelectObject(&track);
	for(int i = 0; i < 8; i++)		//绘制轨道
	{
		if (keys[i].down)
			blend.SourceConstantAlpha = 191;
		else
			blend.SourceConstantAlpha = 63;
		AlphaBlend(pDC->m_hDC, area.right / 2 - 316 + 80 * i, 0, 72, area.bottom - 100, canvas.m_hDC, 36 * i, 0, 36, 10, blend);
		pDC->FillSolidRect(area.right / 2 - 324 + 80 * i, 0, 8, area.bottom - 100, RGB(255, 255, 255));
	}
	pDC->FillSolidRect(area.right / 2 + 316, 0, 8, area.bottom - 100, RGB(255, 255, 255));
	pDC->FillSolidRect(0, area.bottom - 100, area.right, 8, RGB(255, 255, 255));
	canvas.SelectObject(&black);
	blend.SourceConstantAlpha = 63;
	AlphaBlend(pDC->m_hDC, 0, area.bottom - 92, area.right, 92, canvas.m_hDC, 0, 0, 20, 20, blend);
	canvas.SelectObject(oldBmp);
	bg.DeleteObject();
	track.DeleteObject();
	canvas.DeleteDC();
	if (score)
	{
		int passedTime = curTime - startTime;		//绘制音符与判定
		for (i = 0; i < noteCount; i++)
		{
			if (score[i].judge > 0)
				continue;
			if (score[i].time - passedTime > 4000)
				break;
			bool hit = false;
			int deltaTime = score[i].time - passedTime;
			if (score[i].judge == 0)
				pDC->FillSolidRect(area.right / 2 - 320 + score[i].track * 80, (int)(area.bottom - 110 - (deltaTime + score[i].hold) * m_dropSpeed / 10.0), 80, 20 + score[i].hold * m_dropSpeed / 10, RGB(255, 255, 255));
			else
				pDC->FillSolidRect(area.right / 2 - 320 + score[i].track * 80, (int)(area.bottom - 110 - (deltaTime + score[i].hold) * m_dropSpeed / 10.0), 80, 15 + (deltaTime + score[i].hold) * m_dropSpeed / 10, RGB(255, 255, 255));
			if (deltaTime <= -250 && score[i].judge == 0 || score[i].judge < 0 && deltaTime + score[i].hold <= -250)		//音符miss
			{
				score[i].judge = 1;
				stat.miss++;
				stat.combo = 0;
			}
			else if (keys[score[i].track].downTime != 0)		//键盘按下
			{
				deltaTime = score[i].time - keys[score[i].track].downTime;
				if (deltaTime < 60 && deltaTime > -60)
				{
					if (score[i].hold == 0)
					{
						score[i].judge = 4;
						stat.perfect++;
						stat.combo++;
						stat.Calculate(noteCount);
						hit = true;
					}
					else
					{
						score[i].judge = -4;
						hit = true;
					}
					for (int j = 0; j < 20; j++)
					{
						if (!effector[j].enable)
						{
							effector[j].Set(score[i].track, 4);
							break;
						}
					}
				}
				else if (deltaTime < 150 && deltaTime > -200)
				{
					if (score[i].hold == 0)
					{
						score[i].judge = 3;
						stat.good++;
						stat.combo++;
						stat.Calculate(noteCount);
						hit = true;
					}
					else
					{
						score[i].judge = -3;
						hit = true;
					}
					for (int j = 0; j < 20; j++)
					{
						if (!effector[j].enable)
						{
							effector[j].Set(score[i].track, 3);
							break;
						}
					}
				}
				else if (deltaTime < 300 && deltaTime > -400)
				{
					if (score[i].hold == 0)
					{
						score[i].judge = 2;
						stat.bad++;
						stat.combo = 0;
						stat.Calculate(noteCount);
						hit = true;
					}
					else
					{
						score[i].judge = -2;
						hit = true;
					}
					for (int j = 0; j < 20; j++)
					{
						if (!effector[j].enable)
						{
							effector[j].Set(score[i].track, 2);
							break;
						}
					}
				}
				keys[score[i].track].downTime = 0;
			}
			else if (keys[score[i].track].upTime != 0)		//键盘抬起
			{
				if (score[i].judge < 0)
				{
					deltaTime = score[i].time + score[i].hold - keys[score[i].track].upTime;
					if (score[i].judge < -2 && deltaTime < 150 && deltaTime > -200 || score[i].judge == -3 && deltaTime < 60 && deltaTime > -60)
					{
						score[i].judge = 4;
						stat.perfect++;
						stat.combo++;
						stat.Calculate(noteCount);
						hit = true;
						for (int j = 0; j < 20; j++)
						{
							if (!effector[j].enable)
							{
								effector[j].Set(score[i].track, 4);
								break;
							}
						}
					}
					else if (score[i].judge == -2 && deltaTime < 300 && deltaTime > 150 && deltaTime > -400 && deltaTime < -200)
					{
						score[i].judge = 2;
						stat.bad++;
						stat.combo = 0;
						stat.Calculate(noteCount);
						hit = true;
						for (int j = 0; j < 20; j++)
						{
							if (!effector[j].enable)
							{
								effector[j].Set(score[i].track, 2);
								break;
							}
						}
					}
					else if (deltaTime < 300 && deltaTime > -400)
					{
						score[i].judge = 3;
						stat.good++;
						stat.combo++;
						stat.Calculate(noteCount);
						hit = true;
						for (int j = 0; j < 20; j++)
						{
							if (!effector[j].enable)
							{
								effector[j].Set(score[i].track, 3);
								break;
							}
						}
					}
					else
					{
						score[i].judge = 1;
						stat.miss++;
						stat.combo = 0;
					}
				}
				keys[score[i].track].upTime = 0;
			}
			if (m_beat && hit)
				mciSendString("play beat from 0", 0, 0, 0);
		}
	}
	for (i = 0; i < 20; i++)		//特效
	{
		effector[i].Update(&area, pDC, deltaTime);
	}
	CFont *oldFont, newFont;		//绘制数据
	newFont.CreateFont(60, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, "微软雅黑");
	pDC->SetTextColor(RGB(255, 255, 255));
	oldFont = pDC->SelectObject(&newFont);
	str.Format("%d", stat.score);
	pDC->DrawText(str, area, DT_RIGHT | DT_BOTTOM | DT_SINGLELINE);
	str.Format("%d", stat.combo);
	pDC->DrawText(str, area, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
	songsName[songSelection].Replace('_', ' ');
	pDC->DrawText(songsName[songSelection], area, DT_BOTTOM | DT_SINGLELINE);
	songsName[songSelection].Replace(' ', '_');
	pDC->SelectObject(oldFont);
	newFont.DeleteObject();
	
	char length[10];
	str.Format("status full%d mode", songSelection);
	mciSendString(str, length, sizeof(length), 0);
	str = length;
	if (animator.state == 0 && str == "stopped")
	{
		SceneChange(2, pDC);
		state = 6;
		delete []score;
		score = NULL;
		for (int i = 0; i < 8; i++)
		{
			keys[i].Reset();
		}
	}
}

void CMelodiaDlg::UpdateResult(CDC *pDC)
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	CDC canvas;
	canvas.CreateCompatibleDC(NULL);
	HBITMAP hbg;
	CBitmap bg, black;
	CString str;
	
	str.Format("songs\\%s\\bg.bmp", songsName[songSelection]);
	hbg = (HBITMAP)LoadImage(AfxGetInstanceHandle(), str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bg.Attach(hbg);
	black.LoadBitmap(IDB_BACKGROUND);

	CBitmap *oldBmp = canvas.SelectObject(&bg);
	if (area.right / 24.0 > area.bottom / 17.0)		//绘制背景
		pDC->StretchBlt(0, (int)((area.bottom - area.right / 24.0 * 17) / 2), area.right, (int)(area.right / 24.0 * 17), &canvas, 0, 0, 360, 225, SRCCOPY);
	else
		pDC->StretchBlt((int)((area.right - area.bottom / 17.0 * 24) / 2), 0, (int)(area.bottom / 17.0 * 24), area.bottom, &canvas, 0, 0, 360, 225, SRCCOPY);
	blend.SourceConstantAlpha = 127;
	canvas.SelectObject(&black);
	AlphaBlend(pDC->m_hDC, 0, area.bottom / 2 - 100, area.right, 200, canvas.m_hDC, 0, 0, 20, 20, blend);
	canvas.SelectObject(oldBmp);
	bg.DeleteObject();
	black.DeleteObject();
	canvas.DeleteDC();

	COLORREF rankColor;
	CString rankName;
	if (stat.score == 1000000)
	{
		rankColor = RGB(255, 100, 135);
		rankName = "M";
	}
	else if (stat.score >= 950000)
	{
		rankColor = RGB(255, 200, 50);
		rankName = "S";
	}
	else if (stat.score >= 900000)
	{
		rankColor = RGB(25, 200, 80);
		rankName = "A";
	}
	else if (stat.score >= 800000)
	{
		rankColor = RGB(100, 200, 255);
		rankName = "B";
	}
	else if (stat.score >= 700000)
	{
		rankColor = RGB(200, 160, 130);
		rankName = "C";
	}
	else
	{
		rankColor = RGB(0, 0, 0);
		rankName = "F";
	}
	CPen *oldPen, newPen;
	CBrush *oldBrush, newBrush;
	newPen.CreatePen(PS_SOLID, 12, RGB(255, 255, 255));
	newBrush.CreateSolidBrush(rankColor);
	oldPen = pDC->SelectObject(&newPen);
	oldBrush = pDC->SelectObject(&newBrush);
	pDC->Ellipse(area.right / 2 - 120, area.bottom / 2 - 120, area.right / 2 + 120, area.bottom / 2 + 120);

	CFont *oldFont, bigFont, smallFont;
	CRect rect;
	pDC->SetTextColor(RGB(255, 255, 255));
	bigFont.CreateFont(180, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");
	oldFont = pDC->SelectObject(&bigFont);
	pDC->DrawText(rankName, area, DT_CENTER | DT_VCENTER | DT_SINGLELINE);		//等级
	bigFont.DeleteObject();
	bigFont.CreateFont(80, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, "微软雅黑");
	smallFont.CreatePointFont(240, "微软雅黑", NULL);
	pDC->SelectObject(&bigFont);
	songsName[songSelection].Replace('_', ' ');
	pDC->DrawText(songsName[songSelection], area, DT_CENTER);					//曲名
	songsName[songSelection].Replace(' ', '_');
	rect.SetRect(0, area.bottom / 2 - 90, area.right / 2 - 120, area.bottom / 2 + 90);
	str.Format("%d", stat.score);
	pDC->DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);			//分数
	pDC->SelectObject(&smallFont);
	pDC->DrawText("SCORE", rect, DT_CENTER);
	if (userName != "" && stat.score > userData[songSelection])
		pDC->DrawText("NEW BEST", rect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
	rect.SetRect(area.right / 2 + 120, area.bottom / 2 - 90, area.right, area.bottom / 2 + 90);
	pDC->DrawText("MAX COMBO", rect, DT_CENTER);
	if (stat.maxCombo == noteCount)
		pDC->DrawText("FULL COMBO", rect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
	pDC->SelectObject(bigFont);
	str.Format("%d", stat.maxCombo);
	pDC->DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);			//最大连击
	
	CString category[4] = {"PERFECT", "GOOD", "BAD", "MISS"};
	int noteNum[4] = {stat.perfect, stat.good, stat.bad, stat.miss};
	for (int i = 0; i < 4; i++)
	{
		rect.SetRect(area.right / 2 - 300 + 150 * i, area.bottom - 120, area.right / 2 - 150 + 150 * i, area.bottom - 10);
		pDC->SelectObject(smallFont);
		pDC->DrawText(category[i], rect, DT_CENTER);
		pDC->SelectObject(bigFont);
		str.Format("%d", noteNum[i]);
		pDC->DrawText(str, rect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
	}
	pDC->SelectObject(oldFont);
	bigFont.DeleteObject();
	smallFont.DeleteObject();
}

void CMelodiaDlg::FadeIn(int currentState, CDC *pDC)
{
	static int sourceState = 1;
	CString str;
	if (currentState > 0)
	{
		animator.state = 1;
		sourceState = currentState;
		if (sourceState == 4)
		{
			str.Format("play preview%d repeat from 0", songSelection);
			mciSendString(str, 0, 0, 0);
			str.Format("setaudio preview%d volume to 1000", songSelection);
			mciSendString(str, 0, 0, 0);
		}
	}
	if (pDC)
	{
		int process = (int)((1 - animator.duration / 600.0) * 255);
		switch (sourceState)
		{
		case 1:
			UpdateStart(pDC);
			str.Format("setaudio menu volume to %d", (int)(1000 - process / 255.0 * 1000));
			mciSendString(str, 0, 0, 0);
			break;
		case 4:
			UpdateSelect(pDC);
			break;
		case 5:
			UpdatePlay(pDC);
			break;
		}
		CDC bg;
		bg.CreateCompatibleDC(NULL);
		CBitmap bmp;
		bmp.LoadBitmap(IDB_BACKGROUND);
		CBitmap *oldBmp = bg.SelectObject(&bmp);
		blend.SourceConstantAlpha = process;
		AlphaBlend(pDC->m_hDC, 0, 0, area.right, area.bottom, bg.m_hDC, 0, 0, 20, 20, blend);
		bg.SelectObject(oldBmp);
		bg.DeleteDC();
		bmp.DeleteObject();
	}

	animator.duration += deltaTime;
	if (animator.duration >= 600)
	{
		animator.state = 0;
		animator.duration = 0;
		if (sourceState == 5)
		{
			LoadScore();
			str.Format("setaudio full%d volume to 1000", songSelection);
			mciSendString(str, 0, 0, 0);
			str.Format("play full%d from 0", songSelection);
			mciSendString(str, 0, 0, 0);
			startTime = GetTickCount();
		}
	}
}

void CMelodiaDlg::FadeOut(int currentState, CDC *pDC)
{
	static int sourceState;
	CString str;
	if (currentState > 0)
	{
		sourceState = currentState;
		animator.state = 2;
	}
	if (pDC)
	{
		int process = (int)(animator.duration / 600.0 * 255);
		switch (sourceState)
		{
		case 1:
			UpdateStart(pDC);
			str.Format("setaudio menu volume to %d", (int)(1000 - process / 255.0 * 1000));
			mciSendString(str, 0, 0, 0);
			break;
		case 4:
			UpdateSelect(pDC);
			str.Format("setaudio preview%d volume to %d", songSelection, (int)(1000 - process / 255.0 * 1000));
			mciSendString(str, 0, 0, 0);
			break;
		case 5:
			UpdatePlay(pDC);
			str.Format("setaudio full%d volume to %d", songSelection, (int)(1000 - process / 255.0 * 1000));
			mciSendString(str, 0, 0, 0);
			break;
		case 6:
			UpdateResult(pDC);
			break;
		}
		CDC bg;
		bg.CreateCompatibleDC(NULL);
		CBitmap bmp;
		bmp.LoadBitmap(IDB_BACKGROUND);
		CBitmap *oldBmp = bg.SelectObject(&bmp);
		blend.SourceConstantAlpha = process;
		AlphaBlend(pDC->m_hDC, 0, 0, area.Width(), area.Height(), bg.m_hDC, 0, 0, 20, 20, blend);
		bg.SelectObject(oldBmp);
		bg.DeleteDC();
		bmp.DeleteObject();
	}

	animator.duration += deltaTime;
	if (animator.duration >= 600)
	{
		animator.state = 0;
		animator.duration = 0;
		if (sourceState == 1)
		{
			mciSendString("setaudio menu volume to 0", 0, 0, 0);
		}
		else if (sourceState == 4)
		{
			str.Format("stop preview%d", songSelection);
			mciSendString(str, 0, 0, 0);
		}
		else if (sourceState == 5)
		{
			delete []score;
			score = NULL;
			stat.Reset();
			for (int i = 0; i < 8; i++)
			{
				keys[i].Reset();
			}
			for (i = 0; i < 20; i++)
			{
				effector[i].Reset();
			}
			str.Format("stop full%d", songSelection);
			mciSendString(str, 0, 0, 0);
		}
		else if (sourceState == 6 && userName != "" && stat.score > userData[songSelection])
		{
			userData[songSelection] = stat.score;
		}
		FadeIn(state, pDC);
	}
}

void CMelodiaDlg::ButtonExpand(int nID, CDC *pDC)
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	static int buttonID;
	static CRect rect;
	static CString str;
	static CBitmap bmp;
	CRect process;
	if(nID > 0)
	{
		animator.state = 3;
		buttonID = nID;
		switch (buttonID)
		{
		case 1:
			rect.SetRect(area.right / 2 + 50, area.bottom / 2 + 50, area.right / 2 + 350, area.bottom / 2 + 130);
			str = "游戏帮助";
			break;
		case 2:
			rect.SetRect(area.right / 2 + 50, area.bottom / 2 + 150, area.right / 2 + 190, area.bottom / 2 + 270);
			bmp.LoadBitmap(IDB_SETTINGS_FOCUS);
			break;
		}
	}
	int left = Ease(rect.left, area.left, animator.duration / 800.0);
	int top = Ease(rect.top, area.top, animator.duration / 800.0);
	int right = Ease(rect.right, area.right, animator.duration / 800.0);
	int bottom = Ease(rect.bottom, area.bottom, animator.duration / 800.0);
	process.SetRect(left, top, right, bottom);
	if (pDC)
	{
		pDC->FillSolidRect(process, RGB(255, 255, 255));
		switch (buttonID)
		{
		case 1:
			{
				process.bottom = process.top + 80;
				CFont *oldFont, newFont;
				newFont.CreateFont(48, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, "微软雅黑");
				oldFont = pDC->SelectObject(&newFont);
				pDC->SetTextColor(RGB(0, 0, 0));
				pDC->DrawText(str, process, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				pDC->SelectObject(oldFont);
				newFont.DeleteObject();
				break;
			}
		case 2:
			{
				process.bottom = process.top + 120;
				CDC canvas;
				canvas.CreateCompatibleDC(NULL);
				CBitmap *oldBmp = canvas.SelectObject(&bmp);
				pDC->BitBlt(process.left, process.top, 140, 120, &canvas, 0, 0, SRCCOPY);
				canvas.SelectObject(oldBmp);
				canvas.DeleteDC();
				break;
			}
		}
		exitButton.SetRect(area.right / 2 + 210, area.bottom / 2 + 150, area.right / 2 + 350, area.bottom / 2 + 270);
		exitButton.InRect(point.x, point.y);
		exitButton.Update(pDC);
	}
	animator.duration += deltaTime;
	if(animator.duration >= 800)
	{
		animator.duration = 0;
		animator.state = 0;
		bmp.DeleteObject();
	}
}

void CMelodiaDlg::ButtonWithdraw(int nID, CDC *pDC)
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	static int buttonID;
	static CRect rect;
	static CString str;
	static CBitmap bmp;
	CRect process;
	if(nID > 0)
	{
		animator.state = 4;
		buttonID = nID;
		switch (buttonID)
		{
		case 1:
			rect.SetRect(area.right / 2 + 50, area.bottom / 2 + 50, area.right / 2 + 350, area.bottom / 2 + 130);
			str = "游戏帮助";
			break;
		case 2:
			rect.SetRect(area.right / 2 + 50, area.bottom / 2 + 150, area.right / 2 + 190, area.bottom / 2 + 270);
			bmp.LoadBitmap(IDB_SETTINGS_FOCUS);
			break;
		}
	}
	int left = Ease(area.left, rect.left, animator.duration / 800.0);
	int top = Ease(area.top, rect.top, animator.duration / 800.0);
	int right = Ease(area.right, rect.right, animator.duration / 800.0);
	int bottom = Ease(area.bottom, rect.bottom, animator.duration / 800.0);
	process.SetRect(left, top, right, bottom);
	if (pDC)
	{
		pDC->FillSolidRect(process, RGB(255, 255, 255));
		switch (buttonID)
		{
		case 1:
			{
				process.bottom = process.top + 80;
				CFont *oldFont, newFont;
				newFont.CreateFont(48, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, "微软雅黑");
				oldFont = pDC->SelectObject(&newFont);
				pDC->SetTextColor(RGB(0, 0, 0));
				pDC->DrawText(str, process, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				pDC->SelectObject(oldFont);
				newFont.DeleteObject();
				break;
			}
		case 2:
			{
				process.bottom = process.top + 120;
				CDC canvas;
				canvas.CreateCompatibleDC(NULL);
				CBitmap *oldBmp = canvas.SelectObject(&bmp);
				pDC->BitBlt(process.left, process.top, 140, 120, &canvas, 0, 0, SRCCOPY);
				canvas.SelectObject(oldBmp);
				canvas.DeleteDC();
				break;
			}
		}
		exitButton.SetRect(area.right / 2 + 210, area.bottom / 2 + 150, area.right / 2 + 350, area.bottom / 2 + 270);
		exitButton.InRect(point.x, point.y);
		exitButton.Update(pDC);
	}
	animator.duration += deltaTime;
	if(animator.duration >= 800)
	{
		animator.duration = 0;
		animator.state = 0;
		bmp.DeleteObject();
	}
}

void CMelodiaDlg::SongChange(int change, CDC *pDC)
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	static int sourceChange;
	static int prevSelection;
	static CBitmap oldCover, newCover, oldBg, newBg;
	static CDC canvas;
	CString str;
	double process = animator.duration / 800.0;
		
	str.Format("setaudio preview%d volume to %d", prevSelection, (int)(1000 - process * 1000));
	mciSendString(str, 0, 0, 0);

	if (change != 0)
	{
		prevSelection = songSelection;
		animator.state = 5;
		sourceChange = change;
		songSelection += sourceChange;
		if (songSelection < 0)
			songSelection = songsNum - 1;
		else if (songSelection == songsNum)
			songSelection = 0;
		canvas.CreateCompatibleDC(NULL);
		HBITMAP hOldCover, hNewCover, hOldBg, hNewBg;
		
		str.Format("songs\\%s\\cover.bmp", songsName[prevSelection]);		//载入与关联位图
		hOldCover = (HBITMAP)LoadImage(AfxGetInstanceHandle(), str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		oldCover.Attach(hOldCover);
		str.Format("songs\\%s\\bg.bmp", songsName[prevSelection]);
		hOldBg = (HBITMAP)LoadImage(AfxGetInstanceHandle(), str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		oldBg.Attach(hOldBg);
		
		str.Format("songs\\%s\\cover.bmp", songsName[songSelection]);
		hNewCover = (HBITMAP)LoadImage(AfxGetInstanceHandle(), str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		newCover.Attach(hNewCover);
		str.Format("songs\\%s\\bg.bmp", songsName[songSelection]);
		hNewBg = (HBITMAP)LoadImage(AfxGetInstanceHandle(), str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		newBg.Attach(hNewBg);
	}
	
	if (pDC)
	{
		CBitmap *oldBmp = canvas.SelectObject(&oldBg);
		if (area.right / 24.0 > area.bottom / 17.0)
		{
			int fixedHeight = (int)(area.right / 24.0 * 17);
			pDC->StretchBlt(Decel(0, sourceChange * -300, process), (area.bottom - fixedHeight) / 2, area.right, fixedHeight, &canvas, 0, 0, 360, 225, SRCCOPY);
			canvas.SelectObject(&newBg);
			pDC->StretchBlt(Decel(sourceChange * area.right, 0, process), (area.bottom - fixedHeight) / 2, area.right, fixedHeight, &canvas, 0, 0, 360, 225, SRCCOPY);
		}
		else
		{
			int fixedWidth = (int)(area.bottom / 17.0 * 24);
			pDC->StretchBlt((area.right - fixedWidth) / 2 + Decel(0, sourceChange * -300, process), 0, fixedWidth, area.bottom, &canvas, 0, 0, 360, 225, SRCCOPY);
			canvas.SelectObject(&newBg);
			pDC->StretchBlt((area.right - fixedWidth) / 2 + Decel(sourceChange * fixedWidth, 0, process), 0, fixedWidth, area.bottom, &canvas, 0, 0, 360, 225, SRCCOPY);
		}
		canvas.SelectObject(&oldCover);
		pDC->BitBlt(area.right / 2 + 50, area.bottom / 2 - 150, 300, 300, &canvas, 0, 0, SRCCOPY);
		canvas.SelectObject(&newCover);
		if (sourceChange == 1)
			pDC->BitBlt(area.right / 2 + Decel(350, 50, process), area.bottom / 2 - 150, Decel(1, 301, process), 300, &canvas, 0, 0, SRCCOPY);
		else
			pDC->BitBlt(area.right / 2 + 50, area.bottom / 2 - 150, Decel(0, 300, process), 300, &canvas, Decel(350, 0, process), 0, SRCCOPY);
		canvas.SelectObject(oldBmp);
		
		CFont *oldFont, newFont;
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		
		newFont.CreateFont(60, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, "微软雅黑");
		oldFont = pDC->SelectObject(&newFont);
		songsName[songSelection].Replace('_', ' ');
		pDC->TextOut(area.right / 2 - 330, area.bottom / 2 - 60, songsName[songSelection]);		//显示标题
		songsName[songSelection].Replace(' ', '_');
		pDC->SelectObject(oldFont);
		newFont.DeleteObject();
		
		newFont.CreatePointFont(240, "微软雅黑");
		oldFont = pDC->SelectObject(&newFont);
		pDC->TextOut(area.right / 2 - 330, area.bottom / 2, songsComposer[songSelection]);		//显示作者
		if (userName != "")
		{
			str.Format("High Score: %d", userData[songSelection]);
			pDC->TextOut(area.right / 2 - 330, area.bottom / 2 + 50, str);
		}
		pDC->SelectObject(oldFont);
		newFont.DeleteObject();
		
		selectBmpButtons[0].SetRect(area.right / 2 - 280, area.bottom - 80, area.right / 2 - 200, area.bottom);
		selectBmpButtons[1].SetRect(area.right / 2 - 200, area.bottom - 80, area.right / 2 + 200, area.bottom);
		selectBmpButtons[2].SetRect(area.right / 2 + 200, area.bottom - 80, area.right / 2 + 280, area.bottom);
		selectBmpButtons[3].SetRect(0, 0, 160, 60);
		for (int i = 0; i < 4; i++)		//绘制按钮
		{
			selectBmpButtons[i].InRect(point.x, point.y);
			selectBmpButtons[i].Update(pDC);
		}
	}

	animator.duration += deltaTime;
	if(animator.duration >= 800)
	{
		oldCover.DeleteObject();
		oldBg.DeleteObject();
		newCover.DeleteObject();
		newBg.DeleteObject();
		canvas.DeleteDC();
		animator.duration = 0;
		animator.state = 0;
		str.Format("stop preview%d", prevSelection);
		mciSendString(str, 0, 0, 0);
		str.Format("setaudio preview%d volume to 1000", prevSelection);
		mciSendString(str, 0, 0, 0);
	}
}

void CMelodiaDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_FPSValue = (int)(1000.0 / deltaTime);
	CDialog::OnTimer(nIDEvent);
}

void CMelodiaDlg::SceneChange(int change, CDC *pDC)
{
	static int sourceChange;
	static CBitmap bg;
	static CDC canvas;
	CString str;
	double process = animator.duration / 2000.0;

	if (change != 0)
	{
		if (change == 1)
			stat.Reset();
		animator.state = 6;
		sourceChange = change;
		canvas.CreateCompatibleDC(NULL);
		HBITMAP hbg;
		str.Format("songs\\%s\\bg.bmp", songsName[songSelection]);
		hbg = (HBITMAP)LoadImage(AfxGetInstanceHandle(), str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		bg.Attach(hbg);
	}
	
	if (pDC)
	{
		CBitmap *oldBmp = canvas.SelectObject(&bg);
		if (sourceChange == 1)				//Select->Play
		{
			if (process < 0.5)
			{
				UpdateSelect(pDC);
				blend.SourceConstantAlpha = (int)(process * 510);
			}
			else
			{
				UpdatePlay(pDC);
				blend.SourceConstantAlpha = (int)(510 - process * 510);
			}
			str.Format("setaudio preview%d volume to %d", songSelection, (int)(1000 - process * 1000));
			mciSendString(str, 0, 0, 0);
		}
		else if (sourceChange == -1)		//Play->Select
		{
			if (process < 0.5)
			{
				UpdatePlay(pDC);
				blend.SourceConstantAlpha = (int)(process * 510);
				str.Format("setaudio full%d volume to %d", songSelection, (int)(1000 - process * 2000));
				mciSendString(str, 0, 0, 0);
			}
			else
			{
				UpdateSelect(pDC);
				blend.SourceConstantAlpha = (int)(510 - process * 510);
				str.Format("stop full%d", songSelection);
				mciSendString(str, 0, 0, 0);
			}
		}
		else if (sourceChange == 2)			//Play->Result
		{
			if (process < 0.5)
			{
				UpdatePlay(pDC);
				blend.SourceConstantAlpha = (int)(process * 510);
			}
			else
			{
				UpdateResult(pDC);
				blend.SourceConstantAlpha = (int)(510 - process * 510);
			}
		}
		else if (sourceChange == -2)		//Result->Play
		{
			if (process < 0.5)
			{
				UpdateResult(pDC);
				blend.SourceConstantAlpha = (int)(process * 510);
			}
			else
			{
				if (userName != "" && stat.score > userData[songSelection])
				{
					userData[songSelection] = stat.score;
				}
				stat.Reset();
				UpdatePlay(pDC);
				blend.SourceConstantAlpha = (int)(510 - process * 510);
			}
		}
		if (area.right / 24.0 > area.bottom / 17.0)
		{
			int fixedHeight = (int)(area.right / 24.0 * 17);
			AlphaBlend(pDC->m_hDC, 0, (area.bottom - fixedHeight) / 2, area.right, fixedHeight, canvas.m_hDC, 0, 0, 360, 225, blend);
		}
		else
		{
			int fixedWidth = (int)(area.bottom / 17.0 * 24);
			AlphaBlend(pDC->m_hDC, (area.right - fixedWidth) / 2, 0, fixedWidth, area.bottom, canvas.m_hDC, 0, 0, 360, 225, blend);
		}
		canvas.SelectObject(oldBmp);
	}

	animator.duration += deltaTime;
	if (animator.duration >= 2000)
	{
		bg.DeleteObject();
		canvas.DeleteDC();
		animator.state = 0;
		animator.duration = 0;
		str.Format("stop preview%d", songSelection);
		mciSendString(str, 0, 0, 0);
		if (sourceChange == 1 || sourceChange == -2)
		{
			LoadScore();
			str.Format("setaudio full%d volume to 1000", songSelection);
			mciSendString(str, 0, 0, 0);
			str.Format("play full%d from 0", songSelection);
			mciSendString(str, 0, 0, 0);
			startTime = GetTickCount();
		}
		else if (sourceChange == -1)
		{
			delete []score;
			score = NULL;
			stat.Reset();
			for (int i = 0; i < 8; i++)
			{
				keys[i].Reset();
			}
			for (i = 0; i < 20; i++)
			{
				effector[i].Reset();
			}
			str.Format("play preview%d repeat from 0", songSelection);
			mciSendString(str, 0, 0, 0);
			str.Format("setaudio preview%d volume to 1000", songSelection);
			mciSendString(str, 0, 0, 0);
		}
	}
}

void CMelodiaDlg::OnDisplayFps() 
{
	// TODO: Add your command handler code here
	m_showFPS = !m_showFPS;
}

void CMelodiaDlg::OnUpdateDisplayFps(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_showFPS);
}

void CMelodiaDlg::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	ASSERT(pPopupMenu != NULL);
	// Check the enabled state of various menu items.
	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// Determine if menu is popup in top-level menu and set m_pOther to
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup).
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu) state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = this;
		// Child windows don't have menus--need to go to the top!
		if (pParent != NULL && (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					// When popup is found, m_pParentMenu is containing menu.
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}
 
	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax; state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // Menu separator or invalid cmd - ignore it.
 
		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// Possibly a popup menu, route to first item of that popup.
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL || (state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 || state.m_nID == (UINT)-1)
			{
				continue;       // First item of popup can't be routed to.
			}
			state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
		}
		else
		{
			// Normal menu item.
			// Auto enable/disable if frame window has m_bAutoMenuEnable
			// set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}
 
		// Adjust for menu deletions and additions.
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount && pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}

void CMelodiaDlg::OnDisplayResolution1() 
{
	// TODO: Add your command handler code here
	CWnd::SetWindowPos(NULL, 0, 0, 960, 720, SWP_NOZORDER | SWP_NOMOVE);
}

void CMelodiaDlg::OnDisplayResolution2() 
{
	// TODO: Add your command handler code here
	CWnd::SetWindowPos(NULL, 0, 0, 1200, 800, SWP_NOZORDER | SWP_NOMOVE);
}

void CMelodiaDlg::OnDisplayResolution3() 
{
	// TODO: Add your command handler code here
	CWnd::SetWindowPos(NULL, 0, 0, 1920, 800, SWP_NOZORDER | SWP_NOMOVE);
}

void CMelodiaDlg::OnLeapSelect() 
{
	// TODO: Add your command handler code here
	if (animator.state == 0)
	{
		FadeOut(state, NULL);
		state = 4;
	}
}

void CMelodiaDlg::OnLeapStart() 
{
	// TODO: Add your command handler code here
	if (animator.state == 0)
	{
		FadeOut(state, NULL);
		state = 1;
	}
}

void CMelodiaDlg::OnLogin()
{
	CLogin dlg;
	while (true)
	{
		if (dlg.DoModal() == IDOK)
		{
			if (dlg.m_username == "" || dlg.m_password == "")
			{
				MessageBox("存在未填写的项目。", "提示", MB_ICONWARNING);
				continue;
			}
			for (int i = 0; i < usersNum; i++)
			{
				if (dlg.m_username == usersInfo[i][0])
					break;
			}
			if (i == usersNum)
			{
				MessageBox("该用户未注册！", "提示", MB_ICONWARNING);
			}
			else if (dlg.m_password != usersInfo[i][1])
			{
				MessageBox("密码不正确！", "提示", MB_ICONWARNING);
			}
			else
			{
				userName = usersInfo[i][0];
				CString str;
				str.Format("data\\%s.txt", userName);
				CStdioFile userDataFile(str, CFile::modeRead | CFile::typeText);
				for (int i = 0; i < songsNum; i++)
				{
					userDataFile.ReadString(str);
					if (str.GetLength() > 0)
						userData[i] = atoi(str);
					else
						userData[i] = 0;
				}
				MessageBox("登录成功！", "提示");
				break;
			}
		}
		else
		{
			break;
		}
	}
}

void CMelodiaDlg::OnRegister()
{
	CRegister dlg;
	while (true)
	{
		if (dlg.DoModal() == IDOK)
		{
			CString check = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
			if (dlg.m_username == "" || dlg.m_password == "" || dlg.m_confirm == "")
			{
				MessageBox("存在未填写的项目。", "提示", MB_ICONWARNING);
			}
			else if (dlg.m_username != dlg.m_username.SpanIncluding(check) || dlg.m_password != dlg.m_password.SpanIncluding(check))
			{
				MessageBox("用户名与密码只能由数字、字母与下划线构成！", "提示", MB_ICONWARNING);
			}
			else if (dlg.m_password.GetLength() < 6)
			{
				MessageBox("密码至少需要6位！", "提示", MB_ICONWARNING);
			}
			else if (dlg.m_password != dlg.m_confirm)
			{
				MessageBox("两次输入的密码不一致！", "提示", MB_ICONWARNING);
			}
			else
			{
				for (int i = 0; i < usersNum; i++)
				{
					if (usersInfo[i][0] == dlg.m_username)
						break;
				}
				if (i < usersNum)
				{
					MessageBox("该用户名已被占用。", "提示", MB_ICONWARNING);
					continue;
				}
				usersNum++;
				CString (*newUsersInfo)[2] = new CString[usersNum][2];
				for (i = 0; i < usersNum - 1; i++)
				{
					newUsersInfo[i][0] = usersInfo[i][0];
					newUsersInfo[i][1] = usersInfo[i][1];
				}
				newUsersInfo[i][0] = dlg.m_username;
				newUsersInfo[i][1] = dlg.m_password;
				delete []usersInfo;
				usersInfo = newUsersInfo;
				CStdioFile users("data\\users.txt", CFile::modeCreate | CFile::modeWrite);
				CString str;
				str.Format("%d\n", usersNum);
				users.WriteString(str);
				for (i = 0; i < usersNum; i++)
				{
					Decode(usersInfo[i][1]);
					str.Format("%s\t%s\n", usersInfo[i][0], usersInfo[i][1]);
					users.WriteString(str);
					Encode(usersInfo[i][1]);
				}
				userName = usersInfo[usersNum - 1][0];

				str.Format("data\\%s.txt", userName);
				CStdioFile userDataFile(str, CFile::modeCreate | CFile::modeWrite);
				str = "0\n";
				for (i = 0; i < songsNum; i++)
				{
					userDataFile.WriteString(str);
					userData[i] = 0;
				}
				MessageBox("注册成功！", "提示");
				users.Close();
				break;
			}
		}
		else
		{
			break;
		}
	}
}
