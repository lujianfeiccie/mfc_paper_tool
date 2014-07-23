// ResultDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "paper_tool.h"
#include "ResultDlg.h"
#include "afxdialogex.h"


// CResultDlg 对话框

IMPLEMENT_DYNAMIC(CResultDlg, CDialogEx)

CResultDlg::CResultDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResultDlg::IDD, pParent)
{
	Util::LOG("CResultDlg");
	m_b_initied = FALSE;
}

CResultDlg::~CResultDlg()
{
}
BOOL CResultDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Util::LOG("OnInitDialog");

	m_b_initied = TRUE;
	return TRUE;
}
void CResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_edit_result);
}


BEGIN_MESSAGE_MAP(CResultDlg, CDialogEx)
END_MESSAGE_MAP()


// CResultDlg 消息处理程序
//实现edit control全选
BOOL CResultDlg::PreTranslateMessage(MSG* pMsg)
{
// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message==WM_KEYDOWN)
	{
	BOOL bCtrl=::GetKeyState(VK_CONTROL)&0x8000;
	BOOL bShift=::GetKeyState(VK_SHIFT)&0x8000;

	// only gets here if CTRL key is pressed
	BOOL bAlt=::GetKeyState(VK_MENU)&0x8000;
	
	switch( pMsg->wParam )
	{

		case 'A':
		if (bCtrl){
			m_edit_result.SetSel(0,-1);
		}
		break;
		}
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 

return CDialog::PreTranslateMessage(pMsg);
}