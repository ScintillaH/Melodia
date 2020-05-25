// MelodiaEditorDoc.h : interface of the CMelodiaEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MELODIAEDITORDOC_H__A452B4B8_0DC2_41D7_B508_2301668C9860__INCLUDED_)
#define AFX_MELODIAEDITORDOC_H__A452B4B8_0DC2_41D7_B508_2301668C9860__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NoteInfo.h"
#include <afxtempl.h>


class CMelodiaEditorDoc : public CDocument
{
protected: // create from serialization only
	CMelodiaEditorDoc();
	DECLARE_DYNCREATE(CMelodiaEditorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMelodiaEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_name;
	CString m_composer;
	int m_bpm;
	int m_notesNum;
	int m_startPos;
	int m_curPos;
	int m_selection;
	CString m_bg;
	CString m_cover;
	CString m_preview;
	CString m_full;
	virtual ~CMelodiaEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	CNoteInfo * GetNoteInfo(int nIndex);
	void AddNote(int nStartIndex, CNoteInfo *note);
	bool DeleteNote(int nIndex);
#endif

protected:
	CTypedPtrArray<CObArray, CNoteInfo*> m_noteArray;

// Generated message map functions
protected:
	//{{AFX_MSG(CMelodiaEditorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MELODIAEDITORDOC_H__A452B4B8_0DC2_41D7_B508_2301668C9860__INCLUDED_)
