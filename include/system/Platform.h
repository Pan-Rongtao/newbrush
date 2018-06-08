/*******************************************************
**	平台
**
**	
**	提供平台相关的函数封装
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include <string>
#include "PlatformConfigure.h"
#include "Global.h"

namespace nb{ namespace System{

class NB_EXPORT Platform
{
public:
	//字节序模式
	enum DataEndian
	{
		AutoDetect,		//自动检测
		BigEndian,		//大端
		LittleEndian,	//小端（x86一般都是小端）
	};

public:
	//获取目标平台类型
	static int GetTargetPlatformType();
	static std::string GetTargetPlatformName();

	//获取开机以来的时钟滴答数（毫秒数）
	static UInt64 GetTickCount();

	//获取当前进程id
	static int GetCurrentProcessId();

	//获取当前线程id
	static int GetCurrentThreadId();

	//根据pid获取进程名
	static std::string GetProcessNameByPid(int pid);

	//判断大小端模式
	static DataEndian DetectEndian();

	//2字节单位内存块设置设置；nSize表示short个数
	static void MemoryTwoByteSet(short *pDst, short *pSrc, int nSize);

	//休眠秒/毫秒/微秒
	static void Sleep(int seconds);
	static void MSleep(int milliSeconds);
	static void USleep(int uSeconds);
};

}}
