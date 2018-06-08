#pragma once

#ifdef WIN32

#ifdef NB_NETWORK_EXPORTS
#define NB_NETWORK_DECLSPEC_INTERFACE	__declspec(dllexport)
#else
#define NB_NETWORK_DECLSPEC_INTERFACE	__declspec(dllimport)
#endif

#else 
#define NB_NETWORK_DECLSPEC_INTERFACE
#endif