class CRectButton
{
protected:
	CRect rect;
	CString text;
	bool hover;
public:
	CRectButton();
	void SetRect(int left, int top, int right, int bottom);
	void SetText(LPCTSTR str);
	bool InRect(int x, int y);
	virtual void Update(CDC *pDC);
};

class CRectBmpButton : public CRectButton
{
protected:
	CBitmap normal, focus;
public:
	void SetBitmap(UINT normalID, UINT focusID);
	void Update(CDC *pDC);
};