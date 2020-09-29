#include "newbrush/model/StringFunctions.h"

using namespace nb;

void trim(std::string& token)
{
	std::string::size_type front = 0;
	std::string::size_type back = 0;
	std::string::size_type length = token.length();
	std::string::const_iterator tIt = token.begin();
	std::string::const_iterator tEnd = token.end();
	for (; tIt != tEnd; ++tIt, ++front)
	{
		if ((*tIt) != ' ') break;
	}
	if (tIt != tEnd)
	{
		std::string::const_reverse_iterator tRit = token.rbegin();
		std::string::const_reverse_iterator tRend = token.rend();
		for (; tRit != tRend; ++tRit, ++back)
		{
			if ((*tRit) != ' ') break;
		}
	}
	token = token.substr(front, length - back - front);
}

std::vector<std::string> StringFunctions::split(const std::string & str, const std::string & separators, bool ignoreEmpty, bool doTrim)
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
			if (doTrim) trim(token);
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
		if (doTrim) trim(token);
		if (!token.empty() || !ignoreEmpty) ret.push_back(token);
	}
	else if (lastToken)
	{
		ret.push_back(std::string());
	}

	return ret;
}
