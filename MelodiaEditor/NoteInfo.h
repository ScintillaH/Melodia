// NoteInfo.h: interface for the CNoteInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTEINFO_H__8F4602C2_FB5D_4CD3_B776_745399107EC3__INCLUDED_)
#define AFX_NOTEINFO_H__8F4602C2_FB5D_4CD3_B776_745399107EC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNoteInfo : public CObject  
{
public:
	int bar;
	int numerator;
	int denominator;
	int holdNumerator;
	int holdDenominator;
	int track;
	CNoteInfo();
	virtual ~CNoteInfo();
};

#endif // !defined(AFX_NOTEINFO_H__8F4602C2_FB5D_4CD3_B776_745399107EC3__INCLUDED_)
