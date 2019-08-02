#include "core/Log.h"
#include <stdarg.h>
#include <stdio.h>

using namespace nb;

#define __Log__(levelStr)\
	char logBuffer[1024] = { 0 };\
	int nPrefix = snprintf(logBuffer, sizeof(logBuffer), "[%s] ", #levelStr); \
	va_list args; \
	va_start(args, format); \
	vsnprintf(logBuffer + nPrefix, sizeof(logBuffer) - nPrefix, format, args);	\
	va_end(args); \
	printf("%s\n", logBuffer);\

void nb::Log::info(const char * format, ...)
{
	__Log__(INFO);
}

void nb::Log::warn(const char * format, ...)
{
	__Log__(WARN);
}

void nb::Log::error(const char * format, ...)
{
	__Log__(ERROR);
}

void nb::Log::debug(const char * format, ...)
{
#ifndef NDEBUG
	__Log__(DEBUG);
#endif
}
