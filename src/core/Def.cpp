#include "core/Def.h"
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

std::string nb::simpleFormatting(const std::string &str, const std::map<char, int> &char_v)
{
	auto getLastSameFlag = [&](char c, size_t beg)->size_t
	{
		if (beg == str.size())	beg -= 1;
		for (int i = beg; i != str.size(); ++i)
		{
			if (c != str[i])					return i - 1;
			else if (i == str.size() - 1)	return i;
		}
		return std::string::npos;	//never go this
	};

	std::string ret;
	for (int i = 0; i != str.size();)
	{
		auto ch = str[i];
		size_t len = 1;
		auto iter = char_v.find(ch);
		if (iter != char_v.end())
		{
			len = getLastSameFlag(ch, i + 1) - i + 1;
			char f[10] = { 0 }, arr[80] = { 0 };
			snprintf(f, sizeof(f), "%%0%dd", len);
			snprintf(arr, sizeof(arr), f, iter->second);
			ret += arr;
		}
		else
		{
			ret += ch;
		}
		i += len;
	}
	return ret;
}
