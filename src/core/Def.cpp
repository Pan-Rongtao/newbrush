#include "core/Def.h"
#include <sstream>
#include <thread>
#ifdef NB_OS_FAMILY_WINDOWS
	#include <Windows.h>
	#include <WinBase.h>
	#include <TlHelp32.h>
#elif defined NB_OS_FAMILY_UNIX
	#include <unistd.h>
	#include <sys/time.h>
	#include <pthread.h>
#endif

NB_API uint64_t nb::getTickCount()
{
#ifdef NB_OS_FAMILY_WINDOWS
	return GetTickCount();
#else
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#endif

}

uint32_t nb::getPid()
{
	std::stringstream  os;
	os << std::this_thread::get_id();
	return std::stoi(os.str());
}
