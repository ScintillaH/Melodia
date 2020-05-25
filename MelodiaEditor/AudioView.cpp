// AudioView.cpp : implementation file
//

#include "stdafx.h"
#include "MelodiaEditor.h"
#include "MelodiaEditorDoc.h"
#include "AudioView.h"
#include "ProjectInfo.h"
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudioView

IMPLEMENT_DYNCREATE(CAudioView, CFormView)

CAudioView::CAudioView()
	: CFormView(CAudioView::IDD)
{
	//{{AFX_DATA_INIT(CAudioView)
	m_bar = 1;
	m_denominator = 1;
	m_numerator = 0;
	m_position = 0;
	//}}AFX_DATA_INIT
	m_isPlay = 0;
}

CAudioView::~CAudioView()
{
}

void CAudioView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAudioView)
	DDX_Control(pDX, IDC_AUDIO_SLIDER, m_slider);
	DDX_Text(pDX, IDC_AUDIO_BAR, m_bar);
	DDV_MinMaxInt(pDX, m_bar, 1, 999);
	DDX_Text(pDX, IDC_AUDIO_DENOMINATOR, m_denominator);
	DDV_MinMaxInt(pDX, m_denominator, 1, 128);
	DDX_Text(pDX, IDC_AUDIO_NUMERATOR, m_numerator);
	DDX_Text(pDX, IDC_AUDIO_POS, m_position);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAudioView, CFormView)
	//{{AFX_MSG_MAP(CAudioView)
	ON_BN_CLICKED(IDC_AUDIO_PLAY, OnAudioPlay)
	ON_BN_CLICKED(IDC_AUDIO_PAUSE, OnAudioPause)
	ON_WM_TIMER()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_SET_START, OnSetStart)
	ON_BN_CLICKED(IDC_LOCATE, OnLocate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudioView diagnostics

#ifdef _DEBUG
void CAudioView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAudioView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAudioView message handlers

void CAudioView::OnAudioPlay() 
{
	// TODO: Add your control notification handler code here
	CMelodiaEditorDoc *pDoc = (CMelodiaEditorDoc *)GetDocument();
	if (pDoc->m_full != "")
	{
		UpdateData();
		CString str;
		str.Format("play audio from %d", m_position);
		mciSendString(str, 0, 0, 0);
		m_isPlay = true;
		SetTimer(1, 25, NULL);
	}
}

void CAudioView::OnAudioPause() 
{
	// TODO: Add your control notification handler code here
	if (m_isPlay)
	{
		mciSendString("stop audio", 0, 0, 0);
		m_isPlay = false;
		KillTimer(1);
	}
}

void CAudioView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMelodiaEditorDoc *pDoc = (CMelodiaEditorDoc *)GetDocument();
	if (pDoc->m_full != "")
	{
		char positionStr[256];
		CString str;
		str.Format("open %s alias audio", pDoc->m_full);
		mciSendString(str, 0, 0, 0);
		mciSendString("status audio length", positionStr, 255, 0);
		int length = atoi(positionStr);
		m_slider.SetRange(0, length);
	}
	m_position = pDoc->m_curPos;
	m_slider.SetPos(m_position);
	UpdateData(false);
}

void CAudioView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_isPlay)
	{
		CMelodiaEditorDoc* pDoc = (CMelodiaEditorDoc *)GetDocument();
		char positionStr[256];
		CString str;
		str.Format("status audio position");
		mciSendString(str, positionStr, 255, 0);
		m_position = atoi(positionStr);
		m_slider.SetPos(m_position);
		pDoc->m_curPos = m_position;
		pDoc->UpdateAllViews(this, 1);
		if (m_position == m_slider.GetRangeMax())
		{
			m_isPlay = false;
			KillTimer(1);
		}
		UpdateData(false);
	}	
	CFormView::OnTimer(nIDEvent);
}

void CAudioView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar->GetDlgCtrlID() == IDC_AUDIO_SLIDER)
	{
		CMelodiaEditorDoc* pDoc = (CMelodiaEditorDoc *)GetDocument();
		m_position = m_slider.GetPos();
		pDoc->m_curPos = m_position;
		UpdateData(false);
		pDoc->UpdateAllViews(this, 1);
	}
	CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CAudioView::OnSetStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CMelodiaEditorDoc *pDoc = (CMelodiaEditorDoc *)GetDocument();
	pDoc->m_startPos = m_position;
	pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);
}

void CAudioView::OnLocate() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_denominator < 1 || m_denominator > 128 || m_bar < 1 || m_bar > 999)
		return;
	CMelodiaEditorDoc* pDoc = (CMelodiaEditorDoc *)GetDocument();
	m_position = (int)(pDoc->m_startPos + 240000.0 / pDoc->m_bpm * (m_bar - 1 + (double)m_numerator / m_denominator));
	m_slider.SetPos(m_position);
	pDoc->m_curPos = m_position;
	UpdateData(false);
	pDoc->UpdateAllViews(NULL);
}
