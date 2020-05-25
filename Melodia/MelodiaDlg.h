// MelodiaDlg.h : header file
//

#if !defined(AFX_MELODIADLG_H__C087EDCE_08FC_444C_A333_9A7B418DF9CC__INCLUDED_)
#define AFX_MELODIADLG_H__C087EDCE_08FC_444C_A333_9A7B418DF9CC__INCLUDED_

#include "Buttons.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMelodiaDlg dialog

struct Animator
{
	int state;
	long duration;
};

struct KeyInfo
{
	bool down;
	long downTime;
	long upTime;
	void Reset()
	{
		down = false;
		downTime = 0;
		upTime = 0;
	}
};

struct NoteInfo
{
	int track;
	int time;
	int hold;
	int judge;
};

struct StatInfo
{
	int perfect;
	int good;
	int bad;
	int miss;
	int combo;
	int maxCombo;
	int score;
	double comboScore;
	void Reset()
	{
		perfect = good = bad = miss = combo = maxCombo = score = 0;
		comboScore = 0;
	}
	void Calculate(int noteNum)
	{
		double temp = (int)(900000.0 / noteNum * perfect + 630000.0 / noteNum * good + 270000.0 / noteNum * bad);
		comboScore += combo * 200000.0 / (1 + noteNum) / noteNum;
		score = (int)(temp + comboScore);
		if (combo > maxCombo)
			maxCombo = combo;
	}
};

struct Effect
{
	bool enable;
	int duration;
	int track;
	COLORREF lineColor;
	void Reset()
	{
		enable = false;
		duration = 0;
		track = 0;
		lineColor = 0;
	}
	void Set(int newTrack, int judge)
	{
		track = newTrack;
		switch (judge)
		{
		case 4:
			lineColor = RGB(255, 240, 100);
			break;
		case 3:
			lineColor = RGB(100, 255, 100);
			break;
		case 2:
			lineColor = RGB(100, 200, 255);
			break;
		}
		enable = true;
	}
	void Update(CRect *rect, CDC *pDC, int deltaTime);
};

class CMelodiaDlg : public CDialog
{
// Construction
public:
	CMelodiaDlg(CWnd* pParent = NULL);	// standard constructor
	static void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);
// Dialog Data
	//{{AFX_DATA(CMelodiaDlg)
	enum { IDD = IDD_MELODIA_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMelodiaDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMelodiaDlg)
	virtual BOOL OnInitDialog();
	virtual BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHelpAbout();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDisplayFps();
	afx_msg void OnUpdateDisplayFps(CCmdUI* pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnDisplayResolution1();
	afx_msg void OnDisplayResolution2();
	afx_msg void OnDisplayResolution3();
	afx_msg void OnLeapSelect();
	afx_msg void OnLeapStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRect area;
	BLENDFUNCTION blend;
	int state;
	Animator animator;
	Effect effector[20];

	int deltaTime;
	long curTime;
	long startTime;

	int songSelection;
	CString *songsName;
	CString *songsComposer;
	int songsNum;

	KeyInfo keys[8];
	NoteInfo *score;
	StatInfo stat;
	int noteCount;
	//////////设置//////////
	bool m_showFPS;
	int m_FPSValue;
	bool m_beat;
	int m_dropSpeed;
	//////////按钮//////////
	CRectButton startButtons[4];
	CRectBmpButton startBmpButtons[2];
	CRectButton settingsButtons[3];
	CRectBmpButton selectBmpButtons[4];
	CRectBmpButton exitButton;
	//////////动画//////////
	void FadeIn(int currentState, CDC *pDC);		//animator.state = 1
	void FadeOut(int currentState, CDC *pDC);		//animator.state = 2
	void ButtonExpand(int nID, CDC *pDC);			//animator.state = 3
	void ButtonWithdraw(int nID, CDC *pDC);			//animator.state = 4
	void SongChange(int change, CDC *pDC);			//animator.state = 5
	void SceneChange(int change, CDC *pDC);			//animator.state = 6
	//////////界面更新//////////
	void UpdateStart(CDC *pDC);						//state = 1，开始界面
	void UpdateHelp(CDC *pDC);						//state = 2，帮助界面
	void UpdateSettings(CDC *pDC);					//state = 3，设置界面
	void UpdateSelect(CDC *pDC);					//state = 4，歌曲选择界面
	void UpdatePlay(CDC *pDC);						//state = 5，游戏界面
	void UpdateResult(CDC *pDC);					//state = 6，结算界面
	//////////用户管理//////////
	CString (*usersInfo)[2];
	CString userName;
	int *userData;
	int usersNum;
	void OnLogin();
	void OnRegister();
	//////////读取谱面//////////
	void LoadScore();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MELODIADLG_H__C087EDCE_08FC_444C_A333_9A7B418DF9CC__INCLUDED_)
