// Client.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Client.h"

#include "MainFrm.h"
#include "ClientDoc.h"
#include "TabView.h"
//#include "LOGIN.h"
//LOGIN Login;
// #include "SkinH.h"
// #pragma comment(lib, "SkinH.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void dbg_dump(struct _EXCEPTION_POINTERS* ExceptionInfo) {
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	wsprintf
		(buff, 
		"CRASH CODE:0x%.8x ADDR=0x%.8x FLAGS=0x%.8x PARAMS=0x%.8x\n"
		"eax=%.8x ebx=%.8x ecx=%.8x\nedx=%.8x esi=%.8x edi=%.8x\neip=%.8x esp=%.8x ebp=%.8x\n",
		ExceptionInfo->ExceptionRecord->ExceptionCode,
		ExceptionInfo->ExceptionRecord->ExceptionAddress,
		ExceptionInfo->ExceptionRecord->ExceptionFlags,
		ExceptionInfo->ExceptionRecord->NumberParameters,
		ExceptionInfo->ContextRecord->Eax,
		ExceptionInfo->ContextRecord->Ebx,
		ExceptionInfo->ContextRecord->Ecx,
		ExceptionInfo->ContextRecord->Edx,
		ExceptionInfo->ContextRecord->Esi,
		ExceptionInfo->ContextRecord->Edi,
		ExceptionInfo->ContextRecord->Eip,
		ExceptionInfo->ContextRecord->Esp,
		ExceptionInfo->ContextRecord->Ebp
		);
	
	MessageBox(NULL, buff, _T("Gh0st Rat 3.6 Exception"), MB_OK);
}

LONG WINAPI bad_exception(struct _EXCEPTION_POINTERS* ExceptionInfo) {
	dbg_dump(ExceptionInfo);
	// 不退出
	return true;
	/*ExitProcess(0);*/
}
/////////////////////////////////////////////////////////////////////////////
// CClientApp

BEGIN_MESSAGE_MAP(CClientApp, CWinApp)
	//{{AFX_MSG_MAP(CClientApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
// 	ON_COMMAND(IDM_SKIN_QQ2009, OnSkinQq2009)
// 	ON_COMMAND(IDM_SKIN_CHINA, OnSkinChina)
// 	ON_COMMAND(IDM_SKIN_BLACK, OnSkinBlack)
// 	ON_COMMAND(IDM_SKIN_AERO, OnSkinAero)
// 	ON_COMMAND(IDM_CLOSESKIN, OnCloseskin)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientApp construction
char CClientApp::szDatPath[]={NULL};
CClientApp::CClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	// 初始化本进程的图像列表, 为加载系统图标列表做准备
	typedef BOOL (WINAPI * pfn_FileIconInit) (BOOL fFullInit);
	pfn_FileIconInit FileIconInit = (pfn_FileIconInit) GetProcAddress(LoadLibrary("shell32.dll"), (LPCSTR)660);
	FileIconInit(TRUE);

	HANDLE	hFile = CreateFile(_T("QQwry.dat"), 0, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		m_bIsQQwryExist = true;
	}
	else
	{
		m_bIsQQwryExist = false;
	}
	CloseHandle(hFile);

	
	GetCurrentDirectory(MAX_PATH,szDatPath);
	strcat(szDatPath,"\\Cache\\Install.dat");
	
//	if( INVALID_FILE_ATTRIBUTES==GetFileAttributes(szDatPath))
//	{
//		MessageBox(NULL,"Dat 文件无法找到!无法创建服务端!","警告",MB_OK);
//	}

	m_bIsDisablePopTips = m_IniFile.GetInt(_T("Settings"), _T("PopTips"), false);
	m_bisDisableSound = m_IniFile.GetInt(_T("Settings"), _T("Sound"), false);
	m_pConnectView = NULL;

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CClientApp object

CClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CClientApp initialization

BOOL CClientApp::InitInstance()
{
	//加皮肤
	HGLOBAL hRes;
	HRSRC hResInfo;
	HINSTANCE hinst = AfxGetInstanceHandle();
	hResInfo = FindResource( hinst, MAKEINTRESOURCE(IDR_SKIN), "SKIN" );
	if (hResInfo != NULL)
	{
		hRes = LoadResource( hinst, hResInfo);
		if (hRes != NULL)
		{
			SkinH_AttachRes( (LPBYTE)hRes, SizeofResource(hinst,hResInfo), NULL, NULL, NULL, NULL );
//			SkinH_SetAero(TRUE);
			FreeResource(hRes);
		}
	}

	SetUnhandledExceptionFilter(bad_exception);
	AfxEnableControlContainer();
// 
// 	Login.DoModal();
// 	if ( Login.dLogin <= 10000 )
// 	{
// 		return FALSE;
// 	}

// 	char Path[200]={0};
// 	GetModuleFileName(NULL,Path,200);
// 	*strrchr(Path,'\\')=0;
// 	CString str="\\Skins\\"+m_IniFile.GetString("Settings","Skin","china.she");
// 	strcat(Path,str);
// 	SkinH_AttachEx(Path,NULL);
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
//	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

//	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CClientDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CTabView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 去掉菜单栏
	//m_pMainWnd->SetMenu(NULL);
	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_HIDE);
	m_pMainWnd->UpdateWindow();

// 	pSplash=new CSplashScreenEx();
// 	pSplash->Create(m_pMainWnd,NULL,CSS_FADE | CSS_CENTERSCREEN | CSS_SHADOW);
// 	pSplash->SetBitmap(IDB_SPLASH,255,0,255);
// // 	pSplash->SetTextFont("宋体",150,CSS_TEXT_NORMAL);
// // 	pSplash->SetTextRect(CRect(20,100,120,0));//左上右下
// // 	pSplash->SetTextColor(RGB(38,236,110));
// // 	pSplash->SetTextFormat(DT_SINGLELINE | DT_CENTER | DT_VCENTER);
// // 	char strText[] = "Ghost Rat 3.6";
// // 	pSplash->SetText(strText);               //设置文字
//  	pSplash->Show();
// 	Sleep(1000);
// 	pSplash->Hide();
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();	
	// 启动IOCP服务器
	int	nPort = m_IniFile.GetInt("Settings", "ListenPort");
	int	nMaxConnection = m_IniFile.GetInt("Settings", "MaxConnection");
	if (nPort == 0)
		nPort = 81;
	if (nMaxConnection == 0)
		nMaxConnection = 10000;
	
	if (m_IniFile.GetInt("Settings", "MaxConnectionAuto"))
		nMaxConnection = 8000;

	((CMainFrame*) m_pMainWnd)->Activate(nPort, nMaxConnection);
	
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CClientApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/*
void CClientApp::OnSkinQq2009() 
{
	// TODO: Add your command handler code here
	char Path[200]={0};
	GetModuleFileName(NULL,Path,200);
	*strrchr(Path,'\\')=0;
	strcat(Path,"\\Skins\\QQ2009.she");
	SkinH_AttachEx(Path,NULL);
	m_IniFile.SetString("Settings","Skin","QQ2009.she");
}

void CClientApp::OnSkinChina() 
{
	// TODO: Add your command handler code here
	char Path[200]={0};
	GetModuleFileName(NULL,Path,200);
	*strrchr(Path,'\\')=0;
	strcat(Path,"\\Skins\\china.she");
	SkinH_AttachEx(Path,NULL);
	m_IniFile.SetString("Settings","Skin","china.she");
}

void CClientApp::OnSkinBlack() 
{
	// TODO: Add your command handler code here
	char Path[200]={0};
	GetModuleFileName(NULL,Path,200);
	*strrchr(Path,'\\')=0;
	strcat(Path,"\\Skins\\black.she");
	SkinH_AttachEx(Path,NULL);
	m_IniFile.SetString("Settings","Skin","black.she");
}

void CClientApp::OnSkinAero() 
{
	// TODO: Add your command handler code here
	char Path[200]={0};
	GetModuleFileName(NULL,Path,200);
	*strrchr(Path,'\\')=0;
	strcat(Path,"\\Skins\\aero.she");
	SkinH_AttachEx(Path,NULL);
	m_IniFile.SetString("Settings","Skin","aero.she");
}

void CClientApp::OnCloseskin() 
{
	// TODO: Add your command handler code here
	SkinH_Detach();
	m_IniFile.SetString("Settings","Skin","NO");
}
*/