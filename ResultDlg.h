#pragma once
#include "afxwin.h"


// CResultDlg 对话框

class CResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResultDlg)

public:
	CResultDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CResultDlg();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_RESULTDLG };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_result;
	BOOL m_b_initied;
};
