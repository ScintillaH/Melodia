// MelodiaEditorDoc.cpp : implementation of the CMelodiaEditorDoc class
//

#include "stdafx.h"
#include "MelodiaEditor.h"
#include "ProjectInfo.h"
#include "MelodiaEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMelodiaEditorDoc

IMPLEMENT_DYNCREATE(CMelodiaEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMelodiaEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CMelodiaEditorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMelodiaEditorDoc construction/destruction

CMelodiaEditorDoc::CMelodiaEditorDoc()
{
	// TODO: add one-time construction code here
	m_bpm = 60;
	m_notesNum = 0;
	m_startPos = 0;
	m_curPos = 0;
	m_selection = 0;
}

CMelodiaEditorDoc::~CMelodiaEditorDoc()
{
}

BOOL CMelodiaEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	m_noteArray.RemoveAll();
	m_name = "";
	m_bpm = 60;
	m_notesNum = 0;
	m_startPos = 0;
	m_bg = "";
	m_cover = "";
	m_preview = "";
	m_full = "";
	CProjectInfo dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_name = dlg.m_name;
		m_composer = dlg.m_composer;
		m_bpm = dlg.m_bpm;
		m_startPos = dlg.m_startPos;
		m_bg = dlg.m_bg;
		m_cover = dlg.m_cover;
		m_preview = dlg.m_preview;
		m_full = dlg.m_full;
	}
	UpdateAllViews(NULL);
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMelodiaEditorDoc serialization

void CMelodiaEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_name << m_composer << m_bpm << m_notesNum << m_startPos << m_bg << m_cover << m_preview << m_full;
		for (int i = 0; i < m_notesNum; i++)
		{
			CNoteInfo *note = m_noteArray.GetAt(i);
			ar << note->bar << note->numerator << note->denominator << note->holdNumerator << note->holdDenominator << note->track;
		}
	}
	else
	{
		// TODO: add loading code here
		ar >> m_name >> m_composer >> m_bpm >> m_notesNum >> m_startPos >> m_bg >> m_cover >> m_preview >> m_full;
		for (int i = 0; i < m_notesNum; i++)
		{
			CNoteInfo *note = new CNoteInfo;
			ar >> note->bar >> note->numerator >> note->denominator >> note->holdNumerator >> note->holdDenominator >> note->track;
			m_noteArray.Add(note);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMelodiaEditorDoc diagnostics

#ifdef _DEBUG
void CMelodiaEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMelodiaEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMelodiaEditorDoc commands

void CMelodiaEditorDoc::AddNote(int nStartIndex, CNoteInfo *note)
{
	m_noteArray.InsertAt(nStartIndex, note);
	m_notesNum = m_noteArray.GetSize();
	UpdateAllViews(NULL);
}

bool CMelodiaEditorDoc::DeleteNote(int nIndex)
{
	if (nIndex < 0 || nIndex > m_noteArray.GetUpperBound())
		return false;
	m_noteArray.RemoveAt(nIndex);
	m_notesNum = m_noteArray.GetSize();
	UpdateAllViews(NULL);
	return true;
}

CNoteInfo * CMelodiaEditorDoc::GetNoteInfo(int nIndex)
{
	if (nIndex < 0 || nIndex > m_noteArray.GetUpperBound())
		return NULL;
	return m_noteArray.GetAt(nIndex);
}


BOOL CMelodiaEditorDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	m_noteArray.RemoveAll();
	UpdateAllViews(NULL);
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}
