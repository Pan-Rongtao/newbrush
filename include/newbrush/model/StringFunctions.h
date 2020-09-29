#pragma once
#include "newbrush/model/Def.h"

namespace nb 
{

class NB_API StringFunctions
{
public:
	static std::vector<std::string> split(const std::string& str, const std::string& separators, bool ignoreEmpty = false, bool doTrim = false);
};

}