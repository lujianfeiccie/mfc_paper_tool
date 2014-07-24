
// paper_toolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "paper_tool.h"
#include "paper_toolDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Cpaper_toolDlg �Ի���




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
// Cpaper_toolDlg ��Ϣ�������
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

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cpaper_toolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cpaper_toolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT ThreadToParagraphProcess(LPVOID param)
{
	Cpaper_toolDlg *dlg = (Cpaper_toolDlg*)param;
	//CDialogEx::OnOK();
	if(!ICTCLAS_Init()) //��ʼ���ִ������
	{
		Util::LOG("Init fails\n");  
		return 0;
	}
	else
	{
		Util::LOG("Init ok\n");
	}
	
	dlg->SendMessageStatus(MSG_TYPE::MSG_Processing);
	//���ô��Ա�ע��(0 ������������ע����1 ������һ����ע����2 ���������ע����3 ����һ����ע��)
	ICTCLAS_SetPOSmap(2);

	

	char* sSentence=dlg->m_str_paper.GetBuffer(); // ��Ҫ�ִʵ�����
	dlg->m_str_paper.ReleaseBuffer();
	//Util::LOG(sSentence);
	unsigned int nPaLen=strlen(sSentence); // ��Ҫ�ִʵĳ���
	char* sRst=0;   //�û����з���ռ䣬���ڱ�������
	sRst=(char *)malloc(nPaLen*6); //���鳤��Ϊ�ַ������ȵı���
	int nRstLen=0; //�ִʽ���ĳ���

	nRstLen = ICTCLAS_ParagraphProcess(sSentence,nPaLen,sRst,CODE_TYPE_UNKNOWN,0);  //�ַ�������
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
	//Ҳ�������ļ��ı�����,�����ļ��ִʽӿڣ����ִʽ��д�롰Test_reslult.txt���ļ���
	ICTCLAS_FileProcess("Test.txt", "Test_result.txt",CODE_TYPE_GB,1);
	ICTCLAS_Exit();	//�ͷ���Դ�˳�
	
	dlg->SendMessageStatus(MSG_TYPE::MSG_Finish);
	return 0;
}

void Cpaper_toolDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CString tmp;
	//m_edit_paper.GetWindowTextA(tmp);
	//Util::LOG(tmp);
}

//ʵ��edit controlȫѡ
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

