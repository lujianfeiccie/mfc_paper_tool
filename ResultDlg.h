#pragma once
#include "afxwin.h"


// CResultDlg �Ի���

class CResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResultDlg)

public:
	CResultDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CResultDlg();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_RESULTDLG };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_result;
	BOOL m_b_initied;
};
