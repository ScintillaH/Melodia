// NoteInfoView.cpp : implementation file
//

#include "stdafx.h"
#include "MelodiaEditor.h"
#include "NoteInfoView.h"
#include "MelodiaEditorDoc.h"
#include "ProjectInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoteInfoView

IMPLEMENT_DYNCREATE(CNoteInfoView, CFormView)

CNoteInfoView::CNoteInfoView()
	: CFormView(CNoteInfoView::IDD)
{
	//{{AFX_DATA_INIT(CNoteInfoView)
	m_bar = 1;
	m_denominator = 4;
	m_hold = 0;
	m_holdDenominator = 0;
	m_numerator = 0;
	m_time = 0;
	m_track = 0;
	m_holdNumerator = 0;
	//}}AFX_DATA_INIT
}

CNoteInfoView::~CNoteInfoView()
{
}

void CNoteInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNoteInfoView)
	DDX_Control(pDX, IDC_SPIN, m_spin);
	DDX_Control(pDX, IDC_NOTELIST, m_noteList);
	DDX_Text(pDX, IDC_BAR, m_bar);
	DDV_MinMaxInt(pDX, m_bar, 1, 999);
	DDX_Text(pDX, IDC_DENOMINATOR, m_denominator);
	DDV_MinMaxInt(pDX, m_denominator, 1, 128);
	DDX_Text(pDX, IDC_HOLD, m_hold);
	DDX_Text(pDX, IDC_HOLDDENOMINATOR, m_holdDenominator);
	DDX_Text(pDX, IDC_NUMERATOR, m_numerator);
	DDX_Text(pDX, IDC_TIME, m_time);
	DDX_Text(pDX, IDC_TRACK, m_track);
	DDV_MinMaxInt(pDX, m_track, 0, 7);
	DDX_Text(pDX, IDC_HOLDNUMERATOR, m_holdNumerator);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNoteInfoView, CFormView)
	//{{AFX_MSG_MAP(CNoteInfoView)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_LBN_SELCHANGE(IDC_NOTELIST, OnSelchangeNotelist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoteInfoView diagnostics

#ifdef _DEBUG
void CNoteInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CNoteInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNoteInfoView message handlers

void CNoteInfoView::OnAdd() 
{
	// TODO: Add your control notification handler code here
	CMelodiaEditorDoc *pDoc = (CMelodiaEditorDoc *)GetDocument();
	UpdateData();
	if (m_bar < 1 || m_bar > 999|| m_denominator < 1 || m_denominator > 128 || m_track < 0 || m_track > 7)
		return;
	if (m_numerator / m_denominator >= 1)
	{
		MessageBox("节拍数必须效于1！", "提示", MB_ICONWARNING);
		return;
	}
	CNoteInfo *note = new CNoteInfo;
	note->bar = m_bar;
	note->numerator = m_numerator;
	note->denominator = m_denominator;
	note->holdNumerator = m_holdNumerator;
	note->holdDenominator = m_holdDenominator;
	note->track = m_track;
	CString str;
	str.Format("M%03d B%.3f (%d/%d) T%d", m_bar, (double)m_numerator / m_denominator, m_numerator, m_denominator, m_track);
	if (m_noteList.FindStringExact(-1, str) != LB_ERR)
	{
		MessageBox("有重叠的音符！", "提示", MB_ICONWARNING);
		return;
	}
	int nIndex = m_noteList.AddString(str);
	pDoc->AddNote(nIndex, note);
	pDoc->SetModifiedFlag();
}

void CNoteInfoView::OnDelete() 
{
	// TODO: Add your control notification handler code here
	CMelodiaEditorDoc *pDoc = (CMelodiaEditorDoc *)GetDocument();
	int nIndex = m_noteList.GetCurSel();
	if (nIndex != LB_ERR)
	{
		pDoc->DeleteNote(nIndex);
		m_noteList.DeleteString(nIndex);
		m_bar = 1;
		m_numerator = 0;
		m_denominator = 4;
		m_holdNumerator = 0;
		m_holdDenominator = 0;
		m_track = 0;
		m_time = 0;
		m_hold = 0;
		UpdateData(false);
		pDoc->m_selection = -1;
		pDoc->UpdateAllViews(NULL);
		pDoc->SetModifiedFlag();
	}
}

void CNoteInfoView::OnSelchangeNotelist() 
{
	// TODO: Add your control notification handler code here
	CMelodiaEditorDoc *pDoc = (CMelodiaEditorDoc *)GetDocument();
	int nIndex = m_noteList.GetCurSel();
	if (nIndex != LB_ERR)
	{
		pDoc->m_selection = nIndex;
		CNoteInfo *note = pDoc->GetNoteInfo(nIndex);
		m_bar = note->bar;
		m_numerator = note->numerator;
		m_denominator = note->denominator;
		m_holdNumerator = note->holdNumerator;
		m_holdDenominator = note->holdDenominator;
		m_track = note->track;
		m_time = (int)(240000.0 / pDoc->m_bpm * (m_bar - 1 + (double)m_numerator / m_denominator) + pDoc->m_startPos);
		if (m_holdDenominator != 0)
			m_hold = (int)(240000.0 / pDoc->m_bpm * m_holdNumerator / m_holdDenominator);
		else
			m_hold = 0;
		pDoc->m_curPos = m_time;
		UpdateData(false);
		pDoc->UpdateAllViews(this, 1);
	}
}


void CNoteInfoView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_spin.SetRange(1, 999);
	CMelodiaEditorDoc* pDoc = (CMelodiaEditorDoc *)GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->m_notesNum == 0 || pDoc->m_notesNum != m_noteList.GetCount())
	{
		m_noteList.ResetContent();
	}
	for (int i = 0; i < pDoc->m_notesNum; i++)
	{
		CNoteInfo *note = pDoc->GetNoteInfo(i);
		CString str;
		str.Format("M%03d B%.3f (%d/%d) T%d", note->bar, (double)note->numerator / note->denominator, note->numerator, note->denominator, note->track);
		if (m_noteList.FindStringExact(-1, str) == LB_ERR)
		{
			m_noteList.AddString(str);
		}
	}
}

void CNoteInfoView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (lHint == 0)
		Invalidate(false);
}
