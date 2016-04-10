// LOCKDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "LOCKDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLOCKDlg dialog
CBrush m_bkbrush;

int user=0;

CString PASSWORD1;
CString	PASSWORD2;
CString PASSWORD3;

CLOCKDlg::CLOCKDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLOCKDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLOCKDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLOCKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLOCKDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLOCKDlg, CDialog)
	//{{AFX_MSG_MAP(CLOCKDlg)
	ON_BN_CLICKED(ID_SETLOCK, OnSetlock)
	ON_BN_CLICKED(ID_QUIT, OnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLOCKDlg message handlers
BOOL CLOCKDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_bkbrush.CreateSolidBrush(RGB(0,0,0));
	
	SendDlgItemMessage(IDC_UNLOCK,EM_SETREADONLY,1); 
	
	SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CLOCKDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}
HCURSOR CLOCKDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CLOCKDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = (HBRUSH)m_bkbrush;
	
    if(nCtlColor==CTLCOLOR_EDIT)
	{  
		return NULL;
	}
	if(nCtlColor==CTLCOLOR_STATIC)
	{ 
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return hbr;
	}
	
	return hbr;
}

BOOL CLOCKDlg::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg -> message == WM_KEYDOWN)
	{
        if(pMsg -> wParam == VK_ESCAPE)
			return TRUE;
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void CLOCKDlg::OnSetlock() 
{
	// TODO: Add your control notification handler code here
	if(user==0)
	{
		GetDlgItemText(IDC_SET,PASSWORD1);
		GetDlgItemText(IDC_SETAGAIN,PASSWORD2);
		if(PASSWORD1!=PASSWORD2)
		{
			SetDlgItemText(IDC_SET,"");
			SetDlgItemText(IDC_SETAGAIN,"");
			GetDlgItem(IDC_SET)->SetFocus();
			return;
		}
		if(PASSWORD1=="")
		{
			GetDlgItem(IDC_SET)->SetFocus();
			return;
		}
		
		SendDlgItemMessage(IDC_SET,EM_SETREADONLY,1);
		SendDlgItemMessage(IDC_SETAGAIN,EM_SETREADONLY,1);
		SendDlgItemMessage(IDC_UNLOCK,EM_SETREADONLY,0);
		SetDlgItemText(ID_SETLOCK,"·ÀµÁ½âËø");
		SetDlgItemText(IDC_SET,"");
		SetDlgItemText(IDC_SETAGAIN,"");
		GetDlgItem(ID_QUIT)->EnableWindow(false);
		user=1;		
		return;
	}
	if(user==1)
	{
        GetDlgItemText(IDC_UNLOCK,PASSWORD3);
		if(PASSWORD1!=PASSWORD3)
		{
			SetDlgItemText(IDC_UNLOCK,"");
			GetDlgItem(IDC_UNLOCK)->SetFocus();
			return;
		}
		
		SendDlgItemMessage(IDC_SET,EM_SETREADONLY,0);
		SendDlgItemMessage(IDC_SETAGAIN,EM_SETREADONLY,0);
		SendDlgItemMessage(IDC_UNLOCK,EM_SETREADONLY,1);
		SetDlgItemText(ID_SETLOCK,"¼ÓËø");
		SetDlgItemText(IDC_UNLOCK,"");
		GetDlgItem(ID_QUIT)->EnableWindow(true);
		user=0;
	}
}

void CLOCKDlg::OnQuit() 
{
	// TODO: Add your control notification handler code here
	OnOK();	
}
