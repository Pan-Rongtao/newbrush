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
#include "Def.h"

namespace nb
{

class NB_API Log
{
public:
	//输出一条info日志
	static void info(const char *format, ...);

	//输出一条warn日志
	static void warn(const char *format, ...);

	//输出一条error日志
	static void error(const char *format, ...);

	//输出一条debug日志
	//注意：仅在debug模式下才有输出
	static void debug(const char *format, ...);
};

}