
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
	//ON_EN_CHANGE(IDC_EDIT_PAPER, &Cpaper_toolDlg::OnEnChangeEditPaper)	
	
END_MESSAGE_MAP()


// Cpaper_toolDlg 消息处理程序

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
	//m_edit_paper.SubclassDlgItem(IDC_EDIT_PAPER,this);
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



void Cpaper_toolDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString paper;
	m_edit_paper.GetWindowTextA(paper);

	if(""==paper.Trim()) return;

	
	//CDialogEx::OnOK();
	if(!ICTCLAS_Init()) //初始化分词组件。
	{
		Util::LOG("Init fails\n");  
		return ;
	}
	else
	{
		Util::LOG("Init ok\n");
	}
	//设置词性标注集(0 计算所二级标注集，1 计算所一级标注集，2 北大二级标注集，3 北大一级标注集)
	ICTCLAS_SetPOSmap(2);

	

	char* sSentence=paper.GetBuffer(); // 需要分词的内容
	paper.ReleaseBuffer();
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

	map<CString,CString> list;
	
	do{
		// Get next token.
		Token = words.Tokenize(" ", Position);
		
		if(list.find(Token)==list.end() && Token.GetLength()>2){
			list.insert(map<CString,CString>::value_type(Token,Token));
			
			ExcelTool::getInstance()->Add(Token);	
			
		}
		
	} 
	while(!Token.IsEmpty());

	ExcelTool::getInstance()->Close();
	list.clear();

	free(sRst);
	//也可以用文件文本导入,调用文件分词接口，将分词结果写入“Test_reslult.txt”文件中
	ICTCLAS_FileProcess("Test.txt", "Test_result.txt",CODE_TYPE_GB,1);
	ICTCLAS_Exit();	//释放资源退出

	MessageBox("Success!");
}

DWORD WINAPI OnOpenDlg(LPVOID param)
{
	Sleep(1000);
	Cpaper_toolDlg *dlg = (Cpaper_toolDlg*)param;

	dlg->m_dlg.m_edit_result.SetWindowTextA(dlg->m_str_result);
	return 0;
}
void Cpaper_toolDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
	char directory[1024];
	Util::GetFileDirectory(directory);
	strcat(directory,EXCEL_FILE_NAME);

	m_edit_paper.GetWindowTextA(m_str_result);

	ExcelTool::getInstance()->Open(directory);

	ExcelTool::getInstance()->GetString(CallBack_Select);

	ExcelTool::getInstance()->Close();
	
	m_dlg.DoModal();
	
}

void Cpaper_toolDlg::CallBack_Select(CString origin,CString synonymous)
{
//	Util::LOG(origin+" "+synonymous);
	::SendMessageA(::AfxGetMainWnd()->m_hWnd,WM_CALL_BACK_SELECT,(WPARAM)origin.GetBuffer(),(LPARAM)synonymous.GetBuffer());
}
LONG Cpaper_toolDlg::OnCallBack_Select(WPARAM wParam,LPARAM lParam)
{
	CString origin = (char*)wParam;
	CString synonymous = (char*)lParam;
	//MessageBox(origin+" "+synonymous);
	m_str_result.Replace(origin,synonymous);
	if("finish"==origin)
	{
		DWORD dwThreadId;
	 CreateThread(NULL, // default security attributes 
                            0, // use default stack size 
                           OnOpenDlg, // thread function 
                            this, // argument to thread function 
                            0, // use default creation flags 
                            &dwThreadId);  		
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
void Cpaper_toolDlg::OnClose()
{
	CDialog::OnClose();
	CDialog::OnCancel();
}

