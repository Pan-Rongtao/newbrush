#pragma once
#include "newbrush/Object.h"

using namespace nb;

enum class Enum
{
	v0,
	v1,
	v2,
};

class RttrObject : public Object
{
	RTTR_ENABLE(Object)
public:
	bool			bool_p = false;
	char			char_p = 0;
	signed char		schar_p = 0;
	unsigned char	uchar_p = 0;
	wchar_t			wchar_p = 0;
	char16_t		char16_p = 0;
	char32_t		char32_p = 0;
	short			short_p = 0;
	unsigned short	ushort_p = 0;
	int				int32_p = 0;
	unsigned int	uint32_p = 0;
	long			long_p = 0;
	unsigned long	ulong_p = 0;
	long long		longlong_p = 0;
	unsigned		ulonglong_p = 0;
	float			float_p = 0;
	double			double_p = 0;
	long double		longdouble_p = 0;
	std::string		string_p = "";
	std::wstring	wstring_p = L"";
	Enum			enum_p = Enum::v0;
	Point			point_p = 0.0f;
	Point3D			point3d_p = 0.0f;
	Size			size_p = 0.0f;
	Rect			rect_p;
	Color			color_p;
	ref<Color>		colorptr_p = nullptr;
	Thickness		thickness_p;
	TimeSpan		timespan_p;
	Date			date_p;
	Time			time_p;
	glm::vec2		vec2_p{ 0.0f };
	glm::vec3		vec3_p{ 0.0f };
	glm::vec4		vec4_p{ 0.0f };

	int				int32_p1 = 0;
	int				int32_p2 = 0;
	std::string		string_p1 = "";
};

RTTR_REGISTRATION
{
	registration::class_<RttrObject>("RttrObject")(policy::ctor::as_std_shared_ptr)
	.property("bool_p", &RttrObject::bool_p)
	.property("char_p", &RttrObject::char_p)
	.property("schar_p", &RttrObject::schar_p)
	.property("uchar_p", &RttrObject::uchar_p)
	.property("wchar_p", &RttrObject::wchar_p)
	.property("char16_p", &RttrObject::char16_p)
	.property("char32_p", &RttrObject::char32_p)
	.property("short_p", &RttrObject::short_p)
	.property("string_p", &RttrObject::string_p)
	.property("ushort_p", &RttrObject::ushort_p)
	.property("int32_p", &RttrObject::int32_p)
	.property("uint32_p", &RttrObject::uint32_p)
	.property("long_p", &RttrObject::long_p)
	.property("ulong_p", &RttrObject::ulong_p)
	.property("longlong_p", &RttrObject::longlong_p)
	.property("ulonglong_p", &RttrObject::ulonglong_p)
	.property("float_p", &RttrObject::float_p)
	.property("double_p", &RttrObject::double_p)
	.property("longdouble_p", &RttrObject::longdouble_p)
	.property("string_p", &RttrObject::string_p)
	.property("wstring_p", &RttrObject::wstring_p)
	.property("enum_p", &RttrObject::enum_p)
	.property("point_p", &RttrObject::point_p)
	.property("point3d_p", &RttrObject::point3d_p)
	.property("size_p", &RttrObject::size_p)
	.property("rect_p", &RttrObject::rect_p)
	.property("color_p", &RttrObject::color_p)
	.property("colorptr_p", &RttrObject::colorptr_p)
	.property("thickness_p", &RttrObject::thickness_p)
	.property("timespan_p", &RttrObject::timespan_p)
	.property("date_p", &RttrObject::date_p)
	.property("time_p", &RttrObject::time_p)
	.property("vec2_p", &RttrObject::vec2_p)
	.property("vec3_p", &RttrObject::vec3_p)
	.property("vec4_p", &RttrObject::vec4_p)

	.property("int32_p1", &RttrObject::int32_p1)
	.property("int32_p2", &RttrObject::int32_p2)
	.property("string_p1", &RttrObject::string_p1)
	;

}
