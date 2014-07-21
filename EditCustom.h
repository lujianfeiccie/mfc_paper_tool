#pragma once


// CEditCustom

class CEditCustom : public CEdit
{
	DECLARE_DYNAMIC(CEditCustom)

public:
	CEditCustom();
	virtual ~CEditCustom();
	void OnKillFocus(CWnd* pNewWnd);
	void OnSetFocus(CWnd* pOldWnd);
	void OnLButtonUp(UINT nFlags, CPoint point);
	
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	DECLARE_MESSAGE_MAP()
};


