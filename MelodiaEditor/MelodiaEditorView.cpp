// MelodiaEditorView.cpp : implementation of the CMelodiaEditorView class
//

#include "stdafx.h"
#include "MelodiaEditor.h"

#include "MelodiaEditorDoc.h"
#include "MelodiaEditorView.h"
#include "ProjectInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMelodiaEditorView

IMPLEMENT_DYNCREATE(CMelodiaEditorView, CView)

BEGIN_MESSAGE_MAP(CMelodiaEditorView, CView)
	//{{AFX_MSG_MAP(CMelodiaEditorView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMelodiaEditorView construction/destruction

CMelodiaEditorView::CMelodiaEditorView()
{
	// TODO: add construction code here

}

CMelodiaEditorView::~CMelodiaEditorView()
{
}

BOOL CMelodiaEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMelodiaEditorView drawing

void CMelodiaEditorView::OnDraw(CDC* pDC)
{
	CMelodiaEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	GetClientRect(&area);
	CRect rect;

	CDC memDC;
	CBitmap memBmp;
	memDC.CreateCompatibleDC(NULL);
	memBmp.CreateCompatibleBitmap(pDC, area.right, area.bottom);
	memDC.SetBkMode(TRANSPARENT);
	CBitmap *oldBmp = memDC.SelectObject(&memBmp);
	memDC.FillSolidRect(area, RGB(255, 255, 255));

	rect.SetRect(0, area.bottom - 102, area.right, area.bottom - 98);
	memDC.FillSolidRect(rect, RGB(191, 191, 191));
	int center = area.right / 2;
	for (int i = 0; i < 9; i++)
	{
		rect.SetRect(center - 322 + 80 * i, 0, center - 318 + 80 * i, area.bottom - 100);
		memDC.FillSolidRect(rect, RGB(191, 191, 191));
	}
	CFont *oldFont, newFont;
	newFont.CreatePointFont(200, "Î¢ÈíÑÅºÚ");
	oldFont = memDC.SelectObject(&newFont);
	memDC.SetTextColor(RGB(191, 191, 191));
	CString str;
	for (i = 0; i < 8; i++)
	{
		str.Format("%d", i);
		rect.SetRect(center - 320 + 80 * i, area.Height() - 100, center - 240 + 80 * i, area.Height() - 60);
		memDC.DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	memDC.SelectObject(oldFont);
	newFont.DeleteObject();
	for (i = 0; i < pDoc->m_notesNum; i++)
	{
		CNoteInfo *note = pDoc->GetNoteInfo(i);
		COLORREF color = pDoc->m_selection == i ? RGB(255, 0, 0) : RGB(0, 0, 0);
		int noteTime = (int)(240000.0 / pDoc->m_bpm * (note->bar - 1 + (double)note->numerator / note->denominator) + pDoc->m_startPos);
		int noteHold = 0;
		if (note->holdDenominator != 0)
			noteHold = (int)(240000.0 / pDoc->m_bpm * note->holdNumerator / note->holdDenominator);
		if (noteTime + noteHold - pDoc->m_curPos < -1000)
			continue;
		else if (noteTime - pDoc->m_curPos > 4000)
			break;
		memDC.FillSolidRect(center - 320 + 80 * note->track, area.bottom - 105 - (int)((noteTime - pDoc->m_curPos + noteHold) * 0.6), 80, 10 + (int)(noteHold * 0.6), color);
	}
	pDC->BitBlt(0, 0, area.right, area.bottom, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(oldBmp);
	memDC.DeleteDC();
	memBmp.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CMelodiaEditorView diagnostics

#ifdef _DEBUG
void CMelodiaEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CMelodiaEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMelodiaEditorDoc* CMelodiaEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMelodiaEditorDoc)));
	return (CMelodiaEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMelodiaEditorView message handlers

void CMelodiaEditorView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	Invalidate(false);
}
