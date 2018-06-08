#include "core/NewBrushDef.h"

#ifdef WIN32
#include <windows.h>
#else
#endif

using namespace nb;

#ifdef WIN32
void nb::OutputDebugStringW(const wchar_t *pstr)
{
//	::OutputDebugString(pstr);
}

void nb::OutputDebugStringA(const char *pstr)
{
	::OutputDebugStringA(pstr);
}
#endif


void nbOutAssert(const char *remark, const char *fileName, int fileLine)
{
}

void nbDebugOutputString(const char *str)
{
#ifdef WIN32
	::OutputDebugStringA(str);
	::OutputDebugStringA("\n");
#endif

	printf(str, "");
	printf("\n");
}
