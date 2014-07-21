// EditCustom.cpp : 实现文件
//

#include "stdafx.h"
#include "paper_tool.h"
#include "EditCustom.h"


// CEditCustom

IMPLEMENT_DYNAMIC(CEditCustom, CEdit)

CEditCustom::CEditCustom()
{

}

CEditCustom::~CEditCustom()
{
}
void CEditCustom::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	//MessageBox("Lost focus");
	Util::LOG("Lost Focus");
}

void CEditCustom::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);
	//MessageBox("Get focus");
	Util::LOG("Get Focus");
}
void CEditCustom::OnLButtonUp(UINT nFlags, CPoint point)
{
	CEdit::OnLButtonUp(nFlags,point);
	Util::LOG("CEditCustom OnLButtonUp");
	//this->SetFocus();
}
HBRUSH CEditCustom::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	pDC->SetTextColor(RGB(255,255,0));
    pDC->SetBkMode(TRANSPARENT);
	Util::LOG("OnCtlColor");
   return (HBRUSH)::GetStockObject(NULL_BRUSH); 

	//return CEdit::OnCtlColor(pDC,pWnd,nCtlColor);	
}
BEGIN_MESSAGE_MAP(CEditCustom, CEdit)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CEditCustom 消息处理程序


