
// paper_toolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// Cpaper_toolDlg �Ի���
class Cpaper_toolDlg : public CDialogEx
{
// ����
public:
	Cpaper_toolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PAPER_TOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	// For Paper
	CEditCustom m_edit_paper;
	afx_msg void OnEnChangeEditPaper();	
	
	
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
