// ResultDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "paper_tool.h"
#include "ResultDlg.h"
#include "afxdialogex.h"


// CResultDlg �Ի���

IMPLEMENT_DYNAMIC(CResultDlg, CDialogEx)

CResultDlg::CResultDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResultDlg::IDD, pParent)
{

}

CResultDlg::~CResultDlg()
{
}

void CResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_edit_result);
}


BEGIN_MESSAGE_MAP(CResultDlg, CDialogEx)
END_MESSAGE_MAP()


// CResultDlg ��Ϣ�������
