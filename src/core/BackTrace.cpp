#include "core/BackTrace.h"
#include "core/Def.h"
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
	#include <Windows.h>
	#include <DbgHelp.h>
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM || PLATFORM_LINUX_X11 == PLATFORM_LINUX_X11
	#include <signal.h>
	#include <execinfo.h>
#endif
using namespace nb::core;

static nb::core::Event<BackTrace::SignalArgs>	SignalEvent;
#if NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
void OnSignal(int32_t sig)
{
	printf("on signal %d\r\n", sig);

	void *sigs[10] = { 0 };
	size_t count = backtrace(sigs, 10);
	char **symbols = (char **)backtrace_symbols(sigs, count);
	std::vector<std::string> contexts;
	for (size_t i = 0; i != count; ++i)
		contexts.push_back(symbols[i]);

	BackTrace::SignalArgs args;
	args.symbols = contexts;
	BackTrace::signalEvent().dispatch(args);

	exit(0);
}
#endif

BackTrace::BackTrace()
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
//	HANDLE hd = ::GetCurrentProcess();
//	::SymInitialize(hd, NULL, true);
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM || PLATFORM_LINUX_X11 == PLATFORM_LINUX_X11
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

nb::core::Event<BackTrace::SignalArgs> &BackTrace::signalEvent()
{
	return SignalEvent;
}
