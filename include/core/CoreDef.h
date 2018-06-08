#pragma once

#ifdef WIN32

#ifdef NB_CORE_EXPORTS
#define NB_CORE_DECLSPEC_INTERFACE	__declspec(dllexport)
#define NB_CORE_DECLSPEC_X_INTERFACE	__declspec(dllexport)
#else
#define NB_CORE_DECLSPEC_INTERFACE
#define NB_CORE_DECLSPEC_X_INTERFACE	__declspec(dllimport)
#endif

#else 
#define NB_CORE_DECLSPEC_INTERFACE
#define NB_CORE_DECLSPEC_X_INTERFACE
#endif