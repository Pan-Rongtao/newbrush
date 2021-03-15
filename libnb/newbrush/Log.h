#pragma once
#include "newbrush/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#if defined(__ANDROID__)
#include "spdlog/sinks/android_sink.h"
#endif

namespace nb 
{

class NB_API Log
{
public:
	void setLevel(spdlog::level::level_enum level)
	{
		nbLogger()->set_level(level);
	}

	template<typename FormatString, typename... Args>
	static void trace(const FormatString &fmt, const Args &... args)
	{
		nbLogger()->trace(fmt, args...);
	}

	template<typename FormatString, typename... Args>
	static void debug(const FormatString &fmt, const Args &... args)
	{
		nbLogger()->debug(fmt, args...);
	}

	template<typename FormatString, typename... Args>
	static void info(const FormatString &fmt, const Args &... args)
	{
		nbLogger()->info(fmt, args...);
	}

	template<typename FormatString, typename... Args>
	static void warn(const FormatString &fmt, const Args &... args)
	{
		nbLogger()->warn(fmt, args...);
	}

	template<typename FormatString, typename... Args>
	static void error(const FormatString &fmt, const Args &... args)
	{
		nbLogger()->error(fmt, args...);
	}

	template<typename FormatString, typename... Args>
	static void critical(const FormatString &fmt, const Args &... args)
	{
		nbLogger()->critical(fmt, args...);
	}

private:
	static ref<spdlog::logger> nbLogger()
	{
		static ref<spdlog::logger> g_nbLogger;
		if (!g_nbLogger)
		{
#if defined(__ANDROID__)
			g_nbLogger = spdlog::android_logger_mt("nb", "");
#else
			auto sink = createRef<spdlog::sinks::stdout_color_sink_mt>();
			g_nbLogger = createRef<spdlog::logger>("nb", sink);
			//g_nbLogger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");
#endif
		}
		return g_nbLogger;
	}
};


}