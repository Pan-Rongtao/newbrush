#pragma once

#ifdef WIN32

#ifdef NB_SYSTEM_EXPORTS
#define NB_SYSTEM_DECLSPEC_INTERFACE	__declspec(dllexport)
#else
#define NB_SYSTEM_DECLSPEC_INTERFACE	__declspec(dllimport)
#endif

#else 
#define NB_SYSTEM_DECLSPEC_INTERFACE
#endif