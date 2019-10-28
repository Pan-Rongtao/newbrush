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
#ifdef NB_OS_FAMILY_WINDOWS
	return ::GetCurrentProcessId();
#else
	return getpid();
#endif
}

uint32_t nb::getTid()
{
	std::stringstream  os;
	os << std::this_thread::get_id();
	return std::stoi(os.str());
}

std::vector<std::string> nb::stringSplit(const std::string & s, const std::string & sSymbol, bool bSkipEmptyString)
{
	std::vector<std::string> ret;
	std::string sSource = s;
	char *token = strtok((char *)sSource.data(), sSymbol.data());
	while (token)
	{
		std::string s = token;
		if (bSkipEmptyString && s.empty())
		{
			token = strtok(nullptr, sSymbol.data());
			continue;
		}
		ret.push_back(std::move(s));
		token = strtok(nullptr, sSymbol.data());
	}
	return ret;
}
