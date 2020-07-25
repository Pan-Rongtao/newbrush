#include "newbrush/core/Def.h"
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
	return GetTickCount64();
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

std::string nb::getFullName(const std::type_index & t)
{
#ifdef NB_OS_FAMILY_WINDOWS
	std::string s = t.name();
	auto n = s.find(' ');
	return n == std::string::npos ? s : s.substr(n + 1);
#else
	nbThrowException(std::runtime_error, "not implement.");
#endif

}

std::string nb::getNamespace(const std::type_index & t)
{
#ifdef NB_OS_FAMILY_WINDOWS
	std::string s = t.name();
	auto n = s.find(' ');
	if (n == std::string::npos)	//нч"class "
	{
		return "";
	}
	else
	{
		auto n1 = s.rfind("::");//
		return n1 == std::string::npos ? "" : s.substr(n + 1, n1 - n - 1);
	}
#else
	nbThrowException(std::runtime_error, "not implement.");
#endif
}

std::string nb::getClassName(const std::type_index & t)
{
#ifdef NB_OS_FAMILY_WINDOWS
	std::string s = t.name();
	auto n = s.find(' ');
	if (n == std::string::npos)
	{
		return s;
	}
	else
	{
		auto n1 = s.rfind(":");
		return n1 == std::string::npos ? s : s.substr(n1 + 1);
	}
#else
	nbThrowException(std::runtime_error, "not implement.");
#endif
}

std::vector<std::string> nb::stringSplit(const std::string & s, const std::string & sSymbol, bool bSkipEmptyString)
{
	std::vector<std::string> ret;
	std::string sSource = s;
	char *p = nullptr;
#ifdef NB_OS_FAMILY_WINDOWS
	#define STRTOK	strtok_s
#else
	#define STRTOK	strtok_r
#endif
	auto* token = STRTOK((char*)sSource.data(), sSymbol.data(), &p);
	while (token)
	{
		std::string s = token;
		if (!(bSkipEmptyString && s.empty()))
			ret.emplace_back(s);
		token = STRTOK(nullptr, sSymbol.data(), &p);
	}
	return ret;
}
