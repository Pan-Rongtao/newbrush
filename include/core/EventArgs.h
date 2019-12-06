#pragma once
#include "../core/Def.h"

namespace nb {
	
enum class ReasonSessionEnding
{
	Logoff,					//由于用户注销引发的会话终止
	Shutdown,				//由于用户关机引发的会话终止
};

struct EventArgs{};
struct UnhandledExceptionEventArgs { std::exception e; };
struct ExitEventArgs { int exitCode; };
struct CancelEventArgs : public EventArgs { bool cancel{false}; };
struct SessionEndingCancelEventArgs : public CancelEventArgs { ReasonSessionEnding reason; };
struct StartupEventArgs { std::vector<std::string> args; };


}