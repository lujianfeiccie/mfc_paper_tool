
// paper_toolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "ResultDlg.h"
#include <vector>
#include <map>
using namespace std;
const int WM_CALL_BACK_SELECT = WM_USER+100;
const int WM_CALL_BACK_SELECT_FOR_INITDATA = WM_USER+101;
const int WM_CALL_BACK_SELECT_FOR_STATUS = WM_USER+102;

enum MSG_TYPE
{
	MSG_Processing,
	MSG_Finish,
	MSG_FinishParagraphProcessing,
	MSG_Loading
};
static UINT indicators[]={
IDS_STRING_STATUS
};
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
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	// For Paper
	CEditCustom m_edit_paper;	;
	afx_msg void OnEnChangeEditPaper();	
	
	BOOL PreTranslateMessage(MSG* pMsg);
	
	LONG OnCallBack_Select(WPARAM wParam,LPARAM lParam);
	LONG OnCallBack_SelectForInitData(WPARAM wParam,LPARAM lParam);
	LONG OnCallBack_STATUS(WPARAM wParam,LPARAM lParam);
	void SendMessageStatus(MSG_TYPE type);
	CResultDlg m_dlg;
	CString m_str_result;
	map<CString,CString> m_map_list;
	CStatusBar m_statusbar_status;
	CString m_str_paper;
};
