
// paper_toolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "paper_tool.h"
#include "paper_toolDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cpaper_toolDlg 对话框




Cpaper_toolDlg::Cpaper_toolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cpaper_toolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cpaper_toolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PAPER, m_edit_paper);
}

BEGIN_MESSAGE_MAP(Cpaper_toolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Cpaper_toolDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Cpaper_toolDlg::OnBnClickedCancel)
	ON_MESSAGE(WM_CALL_BACK_SELECT,&Cpaper_toolDlg::OnCallBack_Select)
	ON_MESSAGE(WM_CALL_BACK_SELECT_FOR_INITDATA,&Cpaper_toolDlg::OnCallBack_SelectForInitData)
	ON_MESSAGE(WM_CALL_BACK_SELECT_FOR_STATUS,&Cpaper_toolDlg::OnCallBack_STATUS)
	
	//ON_EN_CHANGE(IDC_EDIT_PAPER, &Cpaper_toolDlg::OnEnChangeEditPaper)		
END_MESSAGE_MAP()

void CallBack_SelectForInitData(CString origin,CString synonymous)
{
//	Util::LOG(origin+" "+synonymous);
	::SendMessageA(::AfxGetMainWnd()->m_hWnd,WM_CALL_BACK_SELECT_FOR_INITDATA,(WPARAM)origin.GetBuffer(),(LPARAM)synonymous.GetBuffer());
}

LONG Cpaper_toolDlg::OnCallBack_SelectForInitData(WPARAM wParam,LPARAM lParam)
{
	CString origin = (char*)wParam;
	CString synonymous = (char*)lParam;
	if("finish"==origin)
	{
		Util::LOG("Finsh loading");
		m_statusbar_status.SetPaneText(0,"Finish");
		return 0;
	}
	Util::LOG("Loading data");
	m_map_list.insert(map<CString,CString>::value_type(origin,synonymous));
	return 0;
}
// Cpaper_toolDlg 消息处理程序
UINT OnInitDialogLoadData(LPVOID param)
{
	
	Cpaper_toolDlg *dlg = (Cpaper_toolDlg*)param;
	
	char directory[1024];
	Util::GetFileDirectory(directory);
	strcat(directory,EXCEL_FILE_NAME);
	if(!Util::isExist(directory)) return TRUE;
		
	dlg->SendMessageStatus(MSG_TYPE::MSG_Loading);

	ExcelTool::getInstance()->Open(directory);

	ExcelTool::getInstance()->GetString(CallBack_SelectForInitData);

	ExcelTool::getInstance()->Close();	

	
	
	return 0;
}
BOOL Cpaper_toolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
		//Add Status Bar
	if (!m_statusbar_status.Create(this) ||
        !m_statusbar_status.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT))
        )
	{
		   TRACE0("Failed to create status bar\n");
		   return -1;      // fail to create
	}
	m_statusbar_status.SetPaneInfo(0,indicators[0],SBPS_STRETCH,400);	
    
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,AFX_IDW_CONTROLBAR_FIRST);
	//m_edit_paper.SubclassDlgItem(IDC_EDIT_PAPER,this);
	


	AfxBeginThread(OnInitDialogLoadData,this);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cpaper_toolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cpaper_toolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cpaper_toolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT ThreadToParagraphProcess(LPVOID param)
{
	Cpaper_toolDlg *dlg = (Cpaper_toolDlg*)param;
	//CDialogEx::OnOK();
	if(!ICTCLAS_Init()) //初始化分词组件。
	{
		Util::LOG("Init fails\n");  
		return 0;
	}
	else
	{
		Util::LOG("Init ok\n");
	}
	
	dlg->SendMessageStatus(MSG_TYPE::MSG_Processing);
	//设置词性标注集(0 计算所二级标注集，1 计算所一级标注集，2 北大二级标注集，3 北大一级标注集)
	ICTCLAS_SetPOSmap(2);

	

	char* sSentence=dlg->m_str_paper.GetBuffer(); // 需要分词的内容
	dlg->m_str_paper.ReleaseBuffer();
	//Util::LOG(sSentence);
	unsigned int nPaLen=strlen(sSentence); // 需要分词的长度
	char* sRst=0;   //用户自行分配空间，用于保存结果；
	sRst=(char *)malloc(nPaLen*6); //建议长度为字符串长度的倍。
	int nRstLen=0; //分词结果的长度

	nRstLen = ICTCLAS_ParagraphProcess(sSentence,nPaLen,sRst,CODE_TYPE_UNKNOWN,0);  //字符串处理
	//Util::LOG("The result is:\n%s\n",sRst);
	
	char directory[1024];

	Util::GetFileDirectory(directory);

	strcat(directory,EXCEL_FILE_NAME);


	ExcelTool::getInstance()->WriteAndOpenTemplate(directory);

	CString words = sRst;
	int Position = 0;
	CString Token;

	
	
	do{
		// Get next token.
		Token = words.Tokenize(" ", Position);
		
		if(dlg->m_map_list.find(Token)==dlg->m_map_list.end() && Token.GetLength()>2){
			dlg->m_map_list.insert(map<CString,CString>::value_type(Token,Token));
			
			ExcelTool::getInstance()->Add(Token);	
			
		}
		
	} 
	while(!Token.IsEmpty());

	ExcelTool::getInstance()->Close();
	

	free(sRst);
	//也可以用文件文本导入,调用文件分词接口，将分词结果写入“Test_reslult.txt”文件中
	ICTCLAS_FileProcess("Test.txt", "Test_result.txt",CODE_TYPE_GB,1);
	ICTCLAS_Exit();	//释放资源退出
	
	dlg->SendMessageStatus(MSG_TYPE::MSG_Finish);
	return 0;
}

void Cpaper_toolDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	m_edit_paper.GetWindowTextA(m_str_paper);

	if(""==m_str_paper.Trim()){ 
		MessageBox("Edit Control can not be empty!");
		return;
	}
	AfxBeginThread(ThreadToParagraphProcess,this);
}

UINT OnOpenDlg(LPVOID param)
{
	
	Cpaper_toolDlg *dlg = (Cpaper_toolDlg*)param;
	
	while(!dlg->m_dlg.m_b_initied) Sleep(10);

	
	
	dlg->SendMessageStatus(MSG_TYPE::MSG_FinishParagraphProcessing);
	return 0;
}

void Cpaper_toolDlg::SendMessageStatus(MSG_TYPE type)
{
	SendMessageA(WM_CALL_BACK_SELECT_FOR_STATUS,type,0);
}
LONG Cpaper_toolDlg::OnCallBack_STATUS(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
	case MSG_TYPE::MSG_FinishParagraphProcessing:
		{
			m_dlg.m_edit_result.SetWindowTextA(m_str_result);
			m_statusbar_status.SetPaneText(0,"Finish");
		}
		break;
	case MSG_TYPE::MSG_Processing:
		{
		    m_statusbar_status.SetPaneText(0,"Processing");
		}
		break;
	case MSG_TYPE::MSG_Finish:
		{
			m_statusbar_status.SetPaneText(0,"Finish");
			MessageBox("Success");
		}
		break;
	case MSG_TYPE::MSG_Loading:
		{
		    m_statusbar_status.SetPaneText(0,"Loading");
		}
		break;
	}
	return 0;
}
void CallBack_Select(CString origin,CString synonymous)
{
//	Util::LOG(origin+" "+synonymous);
	::SendMessageA(::AfxGetMainWnd()->m_hWnd,WM_CALL_BACK_SELECT,(WPARAM)origin.GetBuffer(),(LPARAM)synonymous.GetBuffer());
}

void Cpaper_toolDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
	m_statusbar_status.SetPaneText(0,"Processing");

	char directory[1024];
	Util::GetFileDirectory(directory);
	strcat(directory,EXCEL_FILE_NAME);

	m_edit_paper.GetWindowTextA(m_str_result);

	ExcelTool::getInstance()->Open(directory);

	ExcelTool::getInstance()->GetString(CallBack_Select);

	ExcelTool::getInstance()->Close();

	m_dlg.DoModal();
	
}


LONG Cpaper_toolDlg::OnCallBack_Select(WPARAM wParam,LPARAM lParam)
{
	CString origin = (char*)wParam;
	CString synonymous = (char*)lParam;
	//MessageBox(origin+" "+synonymous);
	if(""!=synonymous.Trim()) m_str_result.Replace(origin,synonymous);

	if("finish"==origin)
	{
		DWORD dwThreadId;
		
		 AfxBeginThread(OnOpenDlg,this);
	}
	return 0;
}
void Cpaper_toolDlg::OnEnChangeEditPaper()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//CString tmp;
	//m_edit_paper.GetWindowTextA(tmp);
	//Util::LOG(tmp);
}

//实现edit control全选
BOOL Cpaper_toolDlg::PreTranslateMessage(MSG* pMsg)
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
			m_edit_paper.SetSel(0,-1);
		}
		break;
		}
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 

return CDialog::PreTranslateMessage(pMsg);
}
void Cpaper_toolDlg::OnClose()
{
	CDialog::OnClose();
	CDialog::OnCancel();
}

