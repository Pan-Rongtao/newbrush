#include <stdio.h>
#include "system/Platform.h"
#include "system/PlatformConfigure.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	#include <Windows.h>
	#include <WinBase.h>
	#include <TlHelp32.h>
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	#include <unistd.h>
	#include <sys/time.h>
	#include <pthread.h>
#endif

using namespace nb::System;


int Platform::GetTargetPlatformType()
{
	return NEWBRUSH_SDK_TARGET_PLATFORM;
}

std::string Platform::GetTargetPlatformName()
{
	std::string sRet;
	switch(GetTargetPlatformType())
	{
	case PLATFORM_WIN32:
		sRet = "Win32";
		break;
	case PLATFORM_LINUX_X11:
		sRet = "Linux_X11";
		break;
	case PLATFORM_LINUX_ARM:
		sRet = "Linux_Arm";
		break;
	case PLATFORM_MAC:
		sRet = "Mac";
		break;
	case PLATFORM_IOS:
		sRet = "Ios";
		break;
	case PLATFORM_ANDROID:
		sRet = "Android";
		break;
	default:
		sRet = "Unknown";
		break;
	}
	return sRet;
}
//只测试了Win32平台和linux平台
UInt64 Platform::GetTickCount()
{
	UInt64 nRet = 0;
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	nRet = ::GetTickCount();
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	nRet = (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_MAC
	
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_MAC

#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_IOS

#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_ANDROID

#endif
	return nRet;
}

int Platform::GetCurrentProcessId()
{
	int nRet = 0;
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	nRet = ::GetCurrentProcessId();
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	nRet = getpid();
#endif
	return nRet;
}

int Platform::GetCurrentThreadId()
{
	int nRet = 0;
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	nRet = ::GetCurrentThreadId();
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	nRet = pthread_self();
#endif
	return nRet;
}

std::string Platform::GetProcessNameByPid(int pid)
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return "";

	bool b = ::Process32First(hProcessSnap, &pe32);
	while (b)
	{
		if (pe32.th32ProcessID == pid)
		{
			::CloseHandle(hProcessSnap);
			return pe32.szExeFile;
		}
		b = ::Process32Next(hProcessSnap, &pe32);
	}
	::CloseHandle(hProcessSnap);
	return "";
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	int BUFFER_SIZE = 1024;
	char ret[BUFFER_SIZE] = { 0 };
	char pidFilePath[BUFFER_SIZE] = { 0 };
	char buffer[BUFFER_SIZE] = { 0 };
	sprintf(pidFilePath, "/proc/%d/status", pid);
	FILE *f = fopen(pidFilePath, "r");
	if (f)
	{
		if (fgets(buffer, BUFFER_SIZE - 1, f) == NULL)
			fclose(f);

		fclose(f);
		sscanf(buffer, "%*s %s", ret);
		return ret;
	}
	else
	{
		return "";
	}

#else
	#error "not realize GetProcessNameByPid in this platform."
#endif
}

Platform::DataEndian Platform::DetectEndian()
{
	int x = 0x000000ff;
	return *((char *)(&x)) == 0xff ? Platform::LittleEndian : Platform::BigEndian;
}

void Platform::MemoryTwoByteSet(short *pDst, short *pSrc, int nSize)
{
	int nRemainSize = nSize;

}

void Platform::Sleep(int seconds)
{
	MSleep(seconds * 1000);
}

void Platform::MSleep(int milliSeconds)
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	::Sleep(milliSeconds);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	usleep(milliSeconds * 1000);
#endif
}

//在window下精确不到us
void Platform::USleep(int uSeconds)
{
	MSleep(uSeconds / 1000);
}
