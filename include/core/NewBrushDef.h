#pragma once
#include <stdio.h>
#include <string>
#include <string.h>


//inline void* __cdecl operator new(size_t nSize, const char * lpszFileName, int nLine)
inline void* operator new(size_t nSize, const char * lpszFileName, int nLine) throw()
{
	return operator new(nSize);
}

inline void* operator new [] (size_t nSize, const char * lpszFileName, int nLine) throw()
{
	return operator new [] (nSize);
}

inline void operator delete(void* pData, const char * /* lpszFileName */,
	int /* nLine */)
{
	::operator delete(pData);
}


#define DEBUG_NEW new(__FILE__, __LINE__)
#define DEBUG_DELETE delete



#ifdef WIN32
#define NB_EXPORT	__declspec(dllexport)
#define NB_IMPORT	__declspec(dllimport)
#define NB_LINUX_STD
#else 
#define NB_EXPORT
#define NB_IMPORT
#define NB_LINUX_STD typename
#endif

#define NB_EXPORT_NO

#ifndef NULL
#define NULL 0
#endif 


namespace nb
{
#ifdef WIN32
	NB_EXPORT void OutputDebugStringW(const wchar_t *pstr);
	NB_EXPORT void OutputDebugStringA(const char *pstr);
#endif
}

NB_EXPORT void nbDebugOutputString(const char *str);
NB_EXPORT void nbOutAssert(const char *remark, const char *fileName, int fileLine);

#ifdef WIN32
typedef wchar_t NB_CHAR;
#define NB_CS(str) L##str
#define NB_SNPRINTF	_snprintf_s
#define nbSnprintf _snprintf_s
#define NB_OUT(str) nb::OutputDebugStringW(str); nb::OutputDebugStringW(L"\n"); printf(str); printf("\n");
#define NB_OUTA(str) nb::OutputDebugStringA(str); nb::OutputDebugStringA("\n"); printf(str); printf("\n");
#else
typedef char NB_CHAR;
#define NB_CS(str) str
#define NB_SNPRINTF	snprintf
#define nbSnprintf snprintf
inline void NB_OUT(const char *str){printf(str, ""); printf("\n");}	// 为避开Linux下的编译警告，改为内联函数
#define NB_OUTA(str) NB_OUT(str)
#endif

#define NB_ASSERT_R(x, remark) \
if(!(x))\
{ \
	nbDebugOutputString(" ");	\
	nbDebugOutputString("################ ################    UI ASSERT   ################ ################");	\
	nbDebugOutputString("#");	\
	char ui_assert_r_c[1024];\
	NB_SNPRINTF(ui_assert_r_c, 1023, "# on line:  %d", __LINE__);\
	nbDebugOutputString(ui_assert_r_c);\
	NB_SNPRINTF(ui_assert_r_c, 1023, "# in file:  %s", __FILE__);\
	nbDebugOutputString(ui_assert_r_c);\
	NB_SNPRINTF(ui_assert_r_c, 1023, "# remark :  %s", remark);\
	nbDebugOutputString(ui_assert_r_c);\
	nbDebugOutputString("#");	\
	nbDebugOutputString("################ ################       END      ################ ################");	\
	nbDebugOutputString(" ");	\
} \


#define NB_ASSERT(x) NB_ASSERT_R(x, "")


#define NB_THROW_EXCEPTION(content) throw nb::Core::ExceptionPtr::GetPtrInstance(content, __FILE__, __LINE__); 


enum KeyType
{
	NB_KEY_UNKNOWN           = -1,

	/* Printable keys */
	NB_KEY_SPACE             = 32,
	NB_KEY_APOSTROPHE        = 39,  /* ' */
	NB_KEY_COMMA             = 44,  /* , */
	NB_KEY_MINUS             = 45,  /* - */
	NB_KEY_PERIOD            = 46,  /* . */
	NB_KEY_SLASH             = 47,  /* / */
	NB_KEY_0                 = 48,
	NB_KEY_1                 = 49,
	NB_KEY_2                 = 50,
	NB_KEY_3                 = 51,
	NB_KEY_4                 = 52,
	NB_KEY_5                 = 53,
	NB_KEY_6                 = 54,
	NB_KEY_7                 = 55,
	NB_KEY_8                 = 56,
	NB_KEY_9                 = 57,
	NB_KEY_SEMICOLON         = 59,  /* ; */
	NB_KEY_EQUAL             = 61,  /* = */
	NB_KEY_A                 = 65,
	NB_KEY_B                 = 66,
	NB_KEY_C                 = 67,
	NB_KEY_D                 = 68,
	NB_KEY_E                 = 69,
	NB_KEY_F                 = 70,
	NB_KEY_G                 = 71,
	NB_KEY_H                 = 72,
	NB_KEY_I                 = 73,
	NB_KEY_J                 = 74,
	NB_KEY_K                 = 75,
	NB_KEY_L                 = 76,
	NB_KEY_M                 = 77,
	NB_KEY_N                 = 78,
	NB_KEY_O                 = 79,
	NB_KEY_P                 = 80,
	NB_KEY_Q                 = 81,
	NB_KEY_R                 = 82,
	NB_KEY_S                 = 83,
	NB_KEY_T                 = 84,
	NB_KEY_U                 = 85,
	NB_KEY_V                 = 86,
	NB_KEY_W                 = 87,
	NB_KEY_X                 = 88,
	NB_KEY_Y                 = 89,
	NB_KEY_Z                 = 90,
	NB_KEY_LEFT_BRACKET      = 91,  /* [ */
	NB_KEY_BACKSLASH         = 92,  /* \ */
	NB_KEY_RIGHT_BRACKET     = 93,  /* ] */
	NB_KEY_GRAVE_ACCENT      = 96,  /* ` */
	NB_KEY_WORLD_1           = 161, /* non-US #1 */
	NB_KEY_WORLD_2           = 162, /* non-US #2 */
};