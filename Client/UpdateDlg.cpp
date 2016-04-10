// UpdateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "UpdateDlg.h"

#include "winsock.h"//---
#include "afxinet.h" //WinInet所需要的头文件

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg dialog


CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpdateDlg)
	m_DnsUser = _T("xxx@hotmail.com");
	m_DnsPass = _T("xxxxx");
	m_DnsDomain = _T("xxx.no-ip.org");
	//}}AFX_DATA_INIT
}


void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpdateDlg)
	DDX_Control(pDX, IDC_SIGNNOIP, m_SignNOIP);
	DDX_Control(pDX, IDC_COMBO_DNSIP, m_Combo_DnsIP);
	DDX_Text(pDX, IDC_EDIT_DNSUSER, m_DnsUser);
	DDV_MaxChars(pDX, m_DnsUser, 100);
	DDX_Text(pDX, IDC_EDIT_DNSPASS, m_DnsPass);
	DDV_MaxChars(pDX, m_DnsPass, 100);
	DDX_Text(pDX, IDC_EDIT_DNSDOMAIN, m_DnsDomain);
	DDV_MaxChars(pDX, m_DnsDomain, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpdateDlg, CDialog)
	//{{AFX_MSG_MAP(CUpdateDlg)
	ON_BN_CLICKED(IDC_BTN_DNSUPDATE, OnBtnDnsupdate)
	ON_BN_CLICKED(IDC_GETWAN, OnGetwan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateDlg message handlers
BOOL CUpdateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_SignNOIP.SetURL(_T("http://www.no-ip.com/newUser.php"));

	//获得IP--------------------------------
	WSADATA wsaData;
	WSAStartup(MAKEWORD(1,1),&wsaData);
	char szhostname[128];
    
	if( gethostname(szhostname, 128) == 0 )
	{
		
		struct hostent * phost;
		int i,j,h_length=4;
		phost = gethostbyname(szhostname);
		for( i = 0; phost!= NULL && phost->h_addr_list[i]!= NULL; i++) 
		{
			CString str;
			for( j = 0; j<h_length; j++ ) 
			{
				CString addr;			
				if( j > 0 )
					str += ".";			
				addr.Format("%u", (unsigned int)((unsigned char*)phost->h_addr_list[i])[j]);
				str += addr;
			}
			m_Combo_DnsIP.AddString(str);	
		}
		m_Combo_DnsIP.SetCurSel(0);
	}

	
	BOOL   m_bOnline=TRUE;//是否在线
	DWORD dwFlag;
	m_bOnline=InternetGetConnectedState(&dwFlag,0);   
	if(m_bOnline)//在线
	{
		GetDlgItem(IDC_GETWAN)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_GETWAN)->EnableWindow(FALSE);
		SetDlgItemText(IDC_COMBO_DNSIP,"No Internet");
	}

	UpdateData(FALSE);	
	return TRUE; 
}

static char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int base64_encode1(const void *data, int size, char **str)
{
	char *s, *p;
	int i;
	int c;
	const unsigned char *q;
	
	p = s = (char*)malloc(size*4/3+4);
	if (p == NULL)
		return -1;
	q = (const unsigned char*)data;
	i=0;
	for(i = 0; i < size;){
		c=q[i++];
		c*=256;
		if(i < size)
			c+=q[i];
		i++;
		c*=256;
		if(i < size)
			c+=q[i];
		i++;
		p[0]=base64[(c&0x00fc0000) >> 18];
		p[1]=base64[(c&0x0003f000) >> 12];
		p[2]=base64[(c&0x00000fc0) >> 6];
		p[3]=base64[(c&0x0000003f) >> 0];
		if(i > size)
			p[3]='=';
		if(i > size+1)
			p[2]='=';
		p+=4;
	}
	*p=0;
	*str = s;
	return strlen(s);
}

void CUpdateDlg::OnBtnDnsupdate() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CString strUrl, strDNS, strTmp = _T("");
	CString id,pass,ip;
	GetDlgItem(IDC_EDIT_DNSUSER)->GetWindowText(id);
	GetDlgItem(IDC_EDIT_DNSPASS)->GetWindowText(pass);
	GetDlgItem(IDC_EDIT_DNSDOMAIN)->GetWindowText(strDNS);
	GetDlgItem(IDC_COMBO_DNSIP)->GetWindowText(ip);

	strUrl = _T("http://");
	strUrl += _T("dynupdate.no-ip.com/nic/update?hostname=");
	strUrl += strDNS;
	strUrl += _T("&myip=");
	strUrl += ip;
	
	char szEncode[MAX_PATH];
	char *szOut;
	wsprintfA(szEncode, _T("%s:%s"), id, pass);
	base64_encode1(szEncode, strlen(szEncode), &szOut);
	
	SetDlgItemText(IDC_SHOWTIPS, _T("Update...Wait..."));
	
	CString strHeaders;
	strHeaders.Format(_T("Authorization:Basic %s"), szOut);//= _T("c2Vla3dpbmRzQGdtYWlsLmNvbTp5aW5nNTg0MjAzMzQ0");
	CInternetSession m_Session(NULL, 0);
	CHttpFile* pHttpFile = NULL;
	pHttpFile = (CHttpFile*)m_Session.OpenURL(strUrl, 1, INTERNET_FLAG_TRANSFER_ASCII | INTERNET_FLAG_SECURE, strHeaders, strHeaders.GetLength());
	char szRet[1024];
	if(pHttpFile != NULL)
	{	
		while (pHttpFile->ReadString((LPTSTR)szRet, 1024) != NULL)
		{
			strTmp += szRet;
		}
	}
	pHttpFile->Close();
	m_Session.Close();							
	delete pHttpFile;
	pHttpFile = NULL;
	if(strTmp.GetLength()>0)
	{
		if(strstr(strTmp,_T("badauth")))
		{
			SetDlgItemText(IDC_SHOWTIPS, _T("Password or UserName Wrong"));
		}
		if(strstr(strTmp,_T("good")))
		{
			SetDlgItemText(IDC_SHOWTIPS, _T("No-IP 更新成功"));
		}
		if(strstr(strTmp,_T("nohost")))
		{
			SetDlgItemText(IDC_SHOWTIPS, _T("域名不存在"));
		}
		if(strstr(strTmp,_T("nochg")))
		{
			SetDlgItemText(IDC_SHOWTIPS, _T("IP已经指向该域名"));
		}
	}
	else
	{
		SetDlgItemText(IDC_SHOWTIPS, _T("No-IP 更新成功"));
	}	
}

void CUpdateDlg::OnGetwan() 
{
	// TODO: Add your control notification handler code here
	try
    {
        CInternetSession session;
        CString strURL(_T("http://ip.3322.org/"));
        CFile* pFile = session.OpenURL(strURL);
        DWORD dwLen = pFile->GetLength();
        char* pBuf = new char[dwLen+1];
        memset(pBuf, 0, sizeof(char)*(dwLen+1));
        pFile->Read(pBuf, dwLen);
        SetDlgItemText(IDC_COMBO_DNSIP, CString(pBuf));
        delete[] pBuf;
        pBuf = NULL;
        pFile->Close();
		SetDlgItemText(IDC_SHOWTIPS, _T("获取外网IP成功"));
    }
    catch (CException* e)
    {
        e->ReportError();
        e->Delete();
    }
}
