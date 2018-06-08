#pragma once

#ifdef WIN32

#ifdef NB_GUI_EXPORTS
#define NB_GUI_DECLSPEC_INTERFACE	__declspec(dllexport)
#else
#define NB_GUI_DECLSPEC_INTERFACE	__declspec(dllimport)
#endif

#else 
#define NB_GUI_DECLSPEC_INTERFACE
#endif