#pragma once
#include "newbrush/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#if defined(__ANDROID__)
#include "spdlog/sinks/android_sink.h"
#endif
#include "newbrush/Types.h"
#include "spdlog/fmt/ostr.h"

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

FMT_BEGIN_NAMESPACE
template<> struct formatter<nb::Point>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const nb::Point& v, FormatContext& ctx)-> decltype(ctx.out()) { return format_to(ctx.out(), "[{}, {}]", v.x, v.y); }
};

template<> struct formatter<nb::Point3D>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const nb::Point3D& v, FormatContext& ctx)-> decltype(ctx.out()) { return format_to(ctx.out(), "[{}, {}, {}]", v.x, v.y, v.z); }
};

template<> struct formatter<nb::Size>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const nb::Size& v, FormatContext& ctx)-> decltype(ctx.out()) { return format_to(ctx.out(), "[{}, {}]", v.width, v.height); }
};

template<> struct formatter<nb::Rect>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const nb::Rect& v, FormatContext& ctx)-> decltype(ctx.out()) { return format_to(ctx.out(), "[{}, {}, {}, {}]", v.x(), v.y(), v.width(), v.height()); }
};

template<> struct formatter<nb::Color>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const nb::Color& v, FormatContext& ctx)-> decltype(ctx.out()) { return format_to(ctx.out(), "[{}, {}, {}, {}]", v.r, v.g, v.b, v.a); }
};

template<> struct formatter<nb::Thickness>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const nb::Thickness& v, FormatContext& ctx)-> decltype(ctx.out()) { return format_to(ctx.out(), "[{}, {}, {}, {}]", v.left, v.top, v.right, v.bottom); }
};

template<> struct formatter<nb::TimeSpan>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const nb::TimeSpan& v, FormatContext& ctx)-> decltype(ctx.out())
	{
		return format_to(ctx.out(), "[{}{}.{:02d}:{:02d}:{:02d}.{:03d}.{:03d}]", v == nb::TimeSpan::zero() ? "-" : "", std::abs(v.days()), std::abs(v.hours()), std::abs(v.minutes()), std::abs(v.seconds()), std::abs(v.milliseconds()), std::abs(v.microseconds()));
	}
};

template<> struct formatter<nb::Date>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const nb::Date& v, FormatContext& ctx)-> decltype(ctx.out()) { return format_to(ctx.out(), "[{}/{:02d}/{:02d}]", v.year(), v.month(), v.day()); }
};

template<> struct formatter<nb::Time>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const nb::Time& v, FormatContext& ctx)-> decltype(ctx.out()) { return format_to(ctx.out(), "[{:02d}:{:02d}:{:02d}]", v.hour(), v.minute(), v.second()); }
};

template<> struct formatter<nb::DateTime>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const nb::DateTime& v, FormatContext& ctx)-> decltype(ctx.out()) { return format_to(ctx.out(), "[{}/{:02d}/{:02d} {:02d}:{:02d}:{:02d}]", v.year(), v.month(), v.day(), v.hour(), v.minute(), v.second()); }
};

template<> struct formatter<glm::vec2>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const glm::vec2& v, FormatContext& ctx)-> decltype(ctx.out()) { return format_to(ctx.out(), "[{}, {}]", v.x, v.y); }
};

template<> struct formatter<glm::vec3>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const glm::vec3& v, FormatContext& ctx)-> decltype(ctx.out()) { return format_to(ctx.out(), "[{}, {}, {}]", v.x, v.y, v.z); }
};

template<> struct formatter<glm::vec4>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const glm::vec4& v, FormatContext& ctx)-> decltype(ctx.out()) { return format_to(ctx.out(), "[{}, {}, {}, {}]", v.x, v.y, v.z, v.w); }
};

template<> struct formatter<glm::mat4>
{
	auto parse(format_parse_context& ctx)->decltype(ctx.begin()) { return ctx.begin(); }
	template <typename FormatContext> auto format(const glm::mat4& v, FormatContext& ctx)-> decltype(ctx.out()) { 
		return format_to(ctx.out(), "\n[{}, {}, {}, {}\n {}, {}, {}, {}\n {}, {}, {}, {}\n {}, {}, {}, {}]", 
			v[0][0], v[0][1], v[0][2], v[0][3],
			v[1][0], v[1][1], v[1][2], v[1][3],
			v[2][0], v[2][1], v[2][2], v[2][3],
			v[3][0], v[3][1], v[3][2], v[3][3]);
	}
};
FMT_END_NAMESPACE
