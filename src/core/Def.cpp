#include "core/Def.h"
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
	#include <Windows.h>
	#include <WinBase.h>
	#include <TlHelp32.h>
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	#include <unistd.h>
	#include <sys/time.h>
	#include <pthread.h>
#endif

double nb::pi()
{
	return 3.1415926;
}

double nb::e()
{
	return 2.7182818;
}

double nb::angleToRadian(double angle)
{
	return angle * pi() / 180.0;
}

double nb::radioToAngle(double radian)
{
	return radian * 180.0 / pi();
}

bool nb::approximatelyEqual(float f1, float f2)
{
	return std::abs(f1 - f2) <= 0.00001f;
}

bool nb::approximatelyEqual(double d1, double d2)
{
	return std::abs(d1 - d2) <= 0.000000000001;
}

bool nb::magnitudeEqual(float f1, float f2)
{
	return (std::abs(f1 - f2) <= 0.00001f * (std::min)(std::abs(f1), std::abs(f2)));
}

bool nb::magnitudeEqual(double d1, double d2)
{
	return (std::abs(d1 - d2) <= 0.000000000001 * (std::min)(std::abs(d1), std::abs(d2)));
}

int nb::getTargetPlatformType()
{
	return NB_SDK_TARGET_PLATFORM;
}

std::string nb::getTargetPlatformName()
{
	switch (getTargetPlatformType())
	{
	case PLATFORM_WINDOWS:		return "Windows";
	case PLATFORM_LINUX_X11:	return "Linux_X11";
	case PLATFORM_LINUX_ARM:	return "Linux_Arm";
	case PLATFORM_MAC:			return "Mac";
	case PLATFORM_IOS:			return "Ios";
	case PLATFORM_ANDROID:		return "Android";
	default:					return "Unknown";
	}
}

uint64_t nb::getTickCount()
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
	return ::GetTickCount();
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#else
	#error "not define getTickCount on this platform"
#endif
}

int nb::getCurrentProcessId()
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
	return ::GetCurrentProcessId();
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	return getpid();
#else
	#error "not define getCurrentProcessId on this platform"
#endif
}

int nb::getCurrentThreadId()
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
	return ::GetCurrentThreadId();
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	return pthread_self();
#else
	#error "not define getCurrentThreadId on this platform"
#endif
}

std::string nb::getProcessName(int pid)
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
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
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
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
	#error "not define getProcessName on this platform."
#endif
}

void nb::sleep(int seconds)
{
	msleep(seconds * 1000);
}

void nb::msleep(int milliseconds)
{
	usleep(milliseconds * 1000);
}

void nb::usleep(int useconds)
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
	::Sleep(useconds / 1000);
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	usleep(useconds);
#else
	#error "not define usleep on this platform."
#endif
}
