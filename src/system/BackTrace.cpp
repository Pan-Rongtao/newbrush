#include "system/BackTrace.h"
#include "system/PlatformConfigure.h"
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	#include <Windows.h>
	#include <DbgHelp.h>
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM || PLATFORM_LINUX_X11 == PLATFORM_LINUX_X11
	#include <signal.h>
	#include <execinfo.h>
#endif
using namespace nb::System;

static nbEvent<BackTrace::SignalEventParam>	SignalEvent;
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
void OnSignal(int32_t sig)
{
	printf("on signal %d\r\n", sig);

	void *sigs[10] = { 0 };
	size_t count = backtrace(sigs, 10);
	char **symbols = (char **)backtrace_symbols(sigs, count);
	std::vector<std::string> contexts;
	for (size_t i = 0; i != count; ++i)
		contexts.push_back(symbols[i]);

	BackTrace::SignalEventParam p;
	p.m_Context = contexts;
	BackTrace::signalEvent().Dispatch(p);

	exit(0);
}
#endif

BackTrace::BackTrace()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
//	HANDLE hd = ::GetCurrentProcess();
//	::SymInitialize(hd, NULL, true);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM || PLATFORM_LINUX_X11 == PLATFORM_LINUX_X11
    signal(SIGTSTP, OnSignal);
    signal(SIGBUS, OnSignal);
    signal(SIGFPE, OnSignal);
    signal(SIGSTKFLT, OnSignal);
    signal(SIGABRT, OnSignal);
    signal(SIGSEGV, OnSignal);
    signal(SIGINT, OnSignal);
#endif
}

BackTrace::~BackTrace()
{
}

nbEvent<BackTrace::SignalEventParam> &BackTrace::signalEvent()
{
	return SignalEvent;
}
