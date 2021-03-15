#include "newbrush/Core.h"
#ifdef NB_OS_FAMILY_WINDOWS
	#include <Windows.h>
#elif defined NB_OS_FAMILY_UNIX
	#include <unistd.h>
#endif

uint32_t nb::getPid()
{
#ifdef NB_OS_FAMILY_WINDOWS
	return ::GetCurrentProcessId();
#else
	return getpid();
#endif
}

void nb::stringTrim(std::string& str)
{
	std::string::size_type front = 0;
	std::string::size_type back = 0;
	std::string::size_type length = str.length();
	std::string::const_iterator tIt = str.begin();
	std::string::const_iterator tEnd = str.end();
	for (; tIt != tEnd; ++tIt, ++front)
	{
		if ((*tIt) != ' ') break;
	}
	if (tIt != tEnd)
	{
		std::string::const_reverse_iterator tRit = str.rbegin();
		std::string::const_reverse_iterator tRend = str.rend();
		for (; tRit != tRend; ++tRit, ++back)
		{
			if ((*tRit) != ' ') break;
		}
	}
	str = str.substr(front, length - back - front);
}

std::vector<std::string> nb::stringSplit(const std::string & str, const std::string & separators, bool ignoreEmpty, bool doTrim)
{
	std::vector<std::string> ret;

	std::string::const_iterator it = str.begin();
	std::string::const_iterator itEnd = str.end();
	std::string token;
	bool lastToken = false;

	for (; it != itEnd; ++it)
	{
		if (separators.find(*it) != std::string::npos)
		{
			if (doTrim) stringTrim(token);
			if (!token.empty() || !ignoreEmpty) ret.push_back(token);
			if (!ignoreEmpty) lastToken = true;
			token.clear();
		}
		else
		{
			token += *it;
			lastToken = false;
		}
	}

	if (!token.empty())
	{
		if (doTrim) stringTrim(token);
		if (!token.empty() || !ignoreEmpty) ret.push_back(token);
	}
	else if (lastToken)
	{
		ret.push_back(std::string());
	}

	return ret;
}
