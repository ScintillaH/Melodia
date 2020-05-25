#include "stdafx.h"
#include "Buttons.h"

CRectButton::CRectButton()
{
	hover = false;
}

void CRectButton::SetRect(int left, int top, int right, int bottom)
{
	rect.SetRect(left, top, right, bottom);
}

void CRectButton::SetText(LPCTSTR str)
{
	text = str;
}

bool CRectButton::InRect(int x, int y)
{
	if (x >= rect.left && x <= rect.right && y > rect.top && y < rect.bottom)
	{
		if(hover == false)
		{
			hover = true;
		}
	}
	else
		hover = false;
	return hover;
}

void CRectButton::Update(CDC *pDC)
{
	CFont *oldFont, newFont;
	newFont.CreateFont(48, 0, 0, 0, 800, 0, 0, 0, 0, 0, 0, 0, 0, "Î¢ÈíÑÅºÚ");
	oldFont = pDC->SelectObject(&newFont);
	if (hover)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->FillSolidRect(rect, RGB(255, 255, 255));
	}
	else
	{
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->FillSolidRect(rect, RGB(24, 155, 255));
	}
	pDC->DrawText(text, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->SelectObject(oldFont);
	newFont.DeleteObject();
}

void CRectBmpButton::SetBitmap(UINT normalID, UINT focusID)
{
	normal.LoadBitmap(normalID);
	focus.LoadBitmap(focusID);
}

void CRectBmpButton::Update(CDC *pDC)
{
	CDC canvas;
	canvas.CreateCompatibleDC(NULL);
	CBitmap *oldBmp;
	if (hover)
		oldBmp = canvas.SelectObject(&focus);
	else
		oldBmp = canvas.SelectObject(&normal);
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &canvas, 0, 0, SRCCOPY);
	canvas.SelectObject(oldBmp);
	canvas.DeleteDC();
}