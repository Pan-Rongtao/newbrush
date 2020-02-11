/*******************************************************
**	Log
**
**	日志
**
**		向控制台输出信息
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "newbrush/core/Def.h"

namespace nb
{

class NB_API Log
{
public:
	//输出一条info日志
	template<class... ARGS>
	static void info(const char *format, ARGS... args)
	{
		printf((std::string("[INFO] ") + format + "\n").data(), args...);
	}

	//输出一条warn日志
	template<class... ARGS>
	static void warn(const char *format, ARGS... args)
	{
		printf((std::string("[WARN] ") + format + "\n").data(), args...);
	}

	//输出一条error日志
	template<class... ARGS>
	static void error(const char *format, ARGS... args)
	{
		printf((std::string("[ERROR] ") + format + "\n").data(), args...);
	}

	//输出一条debug日志
	//注意：仅在debug模式下才有输出
	template<class... ARGS>
	static void debug(const char *format, ARGS... args)
	{
#ifndef NDEBUG
		printf((std::string("[DEBUG] ") + format + "\n").data(), args...);
#endif
	}
};

}