
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
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Cpaper_toolDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Cpaper_toolDlg::OnBnClickedCancel)
	//ON_EN_CHANGE(IDC_EDIT_PAPER, &Cpaper_toolDlg::OnEnChangeEditPaper)	
	
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// Cpaper_toolDlg ��Ϣ��������

BOOL Cpaper_toolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

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

	// TODO: �ڴ����Ӷ���ĳ�ʼ������
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

// �����Ի���������С����ť������Ҫ����Ĵ���
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
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
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

	CString paper;
	m_edit_paper.GetWindowTextA(paper);

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

	
	do{
		// Get next token.
		Token = words.Tokenize(" ", Position);
		ExcelTool::getInstance()->Add(Token);	
	} 
	while(!Token.IsEmpty());

	ExcelTool::getInstance()->Close();


	free(sRst);
	//Ҳ�������ļ��ı�����,�����ļ��ִʽӿڣ����ִʽ��д�롰Test_reslult.txt���ļ���
	ICTCLAS_FileProcess("Test.txt", "Test_result.txt",CODE_TYPE_GB,1);
	ICTCLAS_Exit();	//�ͷ���Դ�˳�

	MessageBox("Success!");
}


void Cpaper_toolDlg::OnBnClickedCancel()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CDialogEx::OnCancel();
}


void Cpaper_toolDlg::OnEnChangeEditPaper()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	//CString tmp;
	//m_edit_paper.GetWindowTextA(tmp);
	//Util::LOG(tmp);
}

void Cpaper_toolDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	Util::LOG("Button up");	
	GetDlgItem(m_edit_paper.GetDlgCtrlID())->PostMessage(WM_KILLFOCUS, 0, 0);
	CDialogEx::OnLButtonUp(nFlags, point);
}