
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
	//ON_EN_CHANGE(IDC_EDIT_PAPER, &Cpaper_toolDlg::OnEnChangeEditPaper)	
	
END_MESSAGE_MAP()


// Cpaper_toolDlg ��Ϣ�������

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
	//m_edit_paper.SubclassDlgItem(IDC_EDIT_PAPER,this);
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



void Cpaper_toolDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString paper;
	m_edit_paper.GetWindowTextA(paper);

	if(""==paper.Trim()) return;

	
	//CDialogEx::OnOK();
	if(!ICTCLAS_Init()) //��ʼ���ִ������
	{
		Util::LOG("Init fails\n");  
		return ;
	}
	else
	{
		Util::LOG("Init ok\n");
	}
	//���ô��Ա�ע��(0 ������������ע����1 ������һ����ע����2 ���������ע����3 ����һ����ע��)
	ICTCLAS_SetPOSmap(2);

	

	char* sSentence=paper.GetBuffer(); // ��Ҫ�ִʵ�����
	paper.ReleaseBuffer();
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
	//Ҳ�������ļ��ı�����,�����ļ��ִʽӿڣ����ִʽ��д�롰Test_reslult.txt���ļ���
	ICTCLAS_FileProcess("Test.txt", "Test_result.txt",CODE_TYPE_GB,1);
	ICTCLAS_Exit();	//�ͷ���Դ�˳�

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CString tmp;
	//m_edit_paper.GetWindowTextA(tmp);
	//Util::LOG(tmp);
}
void Cpaper_toolDlg::OnClose()
{
	CDialog::OnClose();
	CDialog::OnCancel();
}

