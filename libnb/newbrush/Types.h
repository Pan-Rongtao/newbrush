#pragma once
#include <regex>
#include <ratio>
#include "newbrush/Core.h"
#include "glm/gtx/color_space.hpp"

namespace nb
{

class NB_API Point
{
public:
	Point() : Point(0.0f, 0.0f)				{}
	Point(float n) : x(n), y(n)				{}
	Point(float _x, float _y) : x(_x), y(_y){}

	void operator = (const Point &p) &		{ x = p.x; y = p.y; }
	bool operator == (const Point &p) const	{ return !(operator != (p)); }
	bool operator != (const Point &p) const	{ return x != p.x || y != p.y; }
	Point operator + (const Point &p) const	{ return Point(x + p.x, y + p.y); }
	Point operator + (float f) const		{ return Point(x + f, y + f); }
	Point operator - (const Point &p) const	{ return Point(x - p.x, y - p.y); }
	Point operator - (float f) const		{ return Point(x - f, y - f); }
	Point operator * (float f) const		{ return Point(x * f, y * f); }
	Point operator / (float f) const		{ return Point(x / f, y / f); }
	void operator += (const Point &p) &		{ *this = (operator +(p)); }
	void operator += (float f) &			{ *this = (operator +(f)); }
	void operator -= (const Point &p) &		{ *this = (operator -(p)); }
	void operator -= (float f) &			{ *this = (operator -(f)); }
	void operator *= (float f) &			{ *this = (operator *(f)); }
	void operator /= (float f) &			{ *this = (operator /(f)); }

	bool epsilonEqual(const Point &p) const { return !nb::epsilonEqual(x, p.x) || !nb::epsilonEqual(y, p.y); }

	float x,y;
};

class NB_API Point3D
{
public:
	Point3D() : Point3D(0.0f, 0.0f, 0.0f)						{}
	Point3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z)	{}

	void operator = (const Point3D &p) &				{ x = p.x; y = p.y; z = p.z; }
	bool operator == (const Point3D &p) const			{ return !(operator !=(p)); }
	bool operator != (const Point3D &p) const			{ return x != p.x || y != p.y || z != p.z; }
	Point3D operator + (const Point3D &p) const			{ return Point3D(x + p.x, y + p.y, z + p.z); }
	Point3D operator + (float f) const					{ return Point3D(x + f, y + f, z + f); }
	Point3D operator - (const Point3D &p) const			{ return Point3D(x - p.x, y - p.y, z - p.z); }
	Point3D operator - (float f) const					{ return Point3D(x - f, y - f, z - f); }
	Point3D operator * (float f) const					{ return Point3D(x * f, y * f, z * f); }
	Point3D operator / (float f) const					{ return Point3D(x / f, y / f, z / f); }
	void operator += (const Point3D &p) &				{ return *this = (operator + (p)); }
	void operator += (float f) &						{ return *this = (operator + (f)); }
	void operator -= (const Point3D &p) &				{ return *this = (operator - (p)); }
	void operator -= (float f) &						{ return *this = (operator - (f)); }
	void operator *= (float f) &						{ return *this = (operator * (f)); }
	void operator /= (float f) &						{ return *this = (operator / (f)); }

	bool epsilonEqual(const Point3D &p) const			{ return !nb::epsilonEqual(x, p.x) || !nb::epsilonEqual(y, p.y) || !nb::epsilonEqual(z, p.z); }

	float x,y,z;
};

class NB_API Size
{
public:
	Size() : Size(0.0f, 0.0f)							{}
	Size(float w, float h) : width(w), height(h)		{}

	void operator = (const Size &s) &					{ width = s.width; height = s.height; }
	bool operator == (const Size &s) const				{ return !(operator !=(s)); }
	bool operator != (const Size &s) const				{ return width != s.width || height != s.height; }
	Size operator + (const Size &s) const				{ return Size(width + s.width, height + s.height); }
	Size operator + (float f) const						{ return Size(width + f, height + f); }
	Size operator - (const Size &s) const				{ return Size(width - s.width, height - s.height); }
	Size operator - (float f) const						{ return Size(width - f, height - f); }
	Size operator * (float f) const						{ return Size(width * f, height * f); }
	Size operator / (float f) const						{ return Size(width / f, height / f); }
	void operator += (const Size &s) &					{ *this = (operator +(s)); }
	void operator += (float f) &						{ *this = (operator +(f)); }
	void operator -= (const Size &s) &					{ *this = (operator -(s)); }
	void operator -= (float f) &						{ *this = (operator -(f)); }
	void operator *= (float f) &						{ *this = (operator *(f)); }
	void operator /= (float f) &						{ *this = (operator /(f)); }

	bool isZero() const									{ return *this == Size(0.0, 0.0); }
	bool epsilonEqual(const Size &p) const				{ return !nb::epsilonEqual(width, p.width) || !nb::epsilonEqual(height, p.height); }

	float width,height;
};

class NB_API Rect
{
public:
	Rect() : Rect(0.0f, 0.0f, 0.0f, 0.0f) {}
	Rect(float x, float y, float w, float h) : m_x(x), m_y(y), m_width(w), m_height(h) {}
	Rect(float x, float y, const Size &s) : Rect(x, y, s.width, s.height)		{}
	Rect(const Point &lt, float w, float h) : Rect(lt.x, lt.y, w, h)	{}
	Rect(const Point &lt, const Size &s) : Rect(lt.x, lt.y, s.width, s.height) {}
	Rect(const Point &lt, const Point &rb) : Rect(lt.x, lt.y, rb.x - lt.x, rb.y - lt.y) {}
	Rect(const Rect &other) : Rect(other.x(), other.y(), other.width(), other.height()) {}

	float x() const										{ return m_x; }
	float y() const										{ return m_y; }
	float left() const									{ return m_x; }
	float top() const									{ return m_y; }
	float width() const									{ return m_width; }
	float height() const								{ return m_height; }
	void setX(float x)									{ auto offset = x - m_x; m_x = x; m_width -= offset; }
	void setY(float y)									{ auto offset = y - m_y; m_y = y; m_height -= offset; }
	void setWidth(float width)							{ m_width = width; }
	void setHeight(float height)						{ m_height = height; }
	void reset(float x, float y, float w, float h)		{ m_x = x; m_y = y; m_width = w; m_height = h; }

	Size size() const									{ return Size(m_width, m_height); }
	void resize(float w, float h)						{ m_width = w; m_height = h; }
	void resize(const Size &s)							{ m_width = s.width; m_height = s.height; }

	float right() const									{ return m_x + m_width; }
	float bottom() const								{ return m_y + m_height; }
	Point leftTop() const								{ return Point(m_x, m_y); }
	Point leftBottom() const							{ return Point(m_x, m_y + m_height); }
	Point rightTop() const								{ return Point(m_x + m_width, m_y); }
	Point rightBottom() const							{ return Point(m_x + m_width, m_y + m_height); }
	Point center() const								{ return Point(m_x + m_width / 2, m_y + m_height / 2); }
	void setRight(float right)							{ m_width = right - m_x; }
	void setBottom(float bottom)						{ m_height = bottom - m_y; }
	void setLeftTop(float left, float top)				{ setX(left); setY(top);}
	void setRightTop(float right, float top)			{ setRight(right); setY(top); }
	void setLeftBottom(float left, float bottom)		{ setX(left); setBottom(bottom); }
	void setRightBottom(float right, float bottom)		{ setRight(right); setBottom(bottom); }

	bool contains(const Point &p) const { return contains(p.x, p.y); }
	bool contains(float x, float y) const;

private:
	float m_x,m_y,m_width,m_height;
};

inline bool Rect::contains(float x, float y) const
{
	bool bHorizontal = width() >= 0.0f ? (x >= left() && x < right()) : (x <= left() && x > right());
	bool bVertical = height() >= 0.0f ? (y >= top() && y < bottom()) : (y <= top() && y > bottom());
	return bHorizontal && bVertical;
}

enum class Colors
{
	aliceBlue				= 0xF0F8FF,	// rgb(240,248,255)
	antiqueWhite			= 0xFAEBD7,	// rgb(250,235,215)
	aqua					= 0x00FFFF,	// rgb(0,255,255)
	aquamarine				= 0x7FFFD4,	// rgb(127,255,212)
	azure					= 0xF0FFFF,	// rgb(240,255,255)
	beige					= 0xF5F5DC,	// rgb(245,245,220)
	bisque					= 0xFFE4C4,	// rgb(255,228,196)
	black					= 0x000000,	// rgb(0,0,0)
	blanchedAlmond			= 0xFFEBCD,	// rgb(255,235,205)
	blue					= 0x0000FF,	// rgb(0,0,255)
	blueViolet				= 0x8A2BE2,	// rgb(138,43,226)
	brown					= 0xA52A2A,	// rgb(165,42,42)
	burlyWood				= 0xDEB887,	// rgb(222,184,135)
	cadetBlue				= 0x5F9EA0,	// rgb(95,158,160)
	chartreuse				= 0x7FFF00,	// rgb(127,255,0)
	chocolate				= 0xD2691E,	// rgb(210,105,30)
	coral					= 0xFF7F50,	// rgb(255,127,80)
	cornflowerBlue			= 0x6495ED,	// rgb(100,149,237)
	cornsilk				= 0xFFF8DC,	// rgb(255,248,220)
	crimson					= 0xDC143C,	// rgb(220,20,60)
	cyan					= 0x00FFFF,	// rgb(0,255,255)
	darkBlue				= 0x00008B,	// rgb(0,0,139)
	darkCyan				= 0x008B8B,	// rgb(0,139,139)
	darkGoldenRod			= 0xB8860B,	// rgb(184,134,11)
	darkGray				= 0xA9A9A9,	// rgb(169,169,169)
	darkGreen				= 0x006400,	// rgb(0,100,0)
	darkKhaki				= 0xBDB76B,	// rgb(189,183,107)
	darkMagenta				= 0x8B008B,	// rgb(139,0,139)
	darkOliveGreen			= 0x556B2F,	// rgb(85,107,47)
	darkOrange				= 0xFF8C00,	// rgb(255,140,0)
	darkOrchid				= 0x9932CC,	// rgb(153,50,204)
	darkRed					= 0x8B0000,	// rgb(139,0,0)
	darkSalmon				= 0xE9967A,	// rgb(233,150,122)
	darkSeaGreen			= 0x8FBC8F,	// rgb(143,188,143)
	darkSlateBlue			= 0x483D8B,	// rgb(72,61,139)
	darkSlateGray			= 0x2F4F4F,	// rgb(47,79,79)
	darkTurquoise			= 0x00CED1,	// rgb(0,206,209)
	darkViolet				= 0x9400D3,	// rgb(148,0,211)
	deepPink				= 0xFF1493,	// rgb(255,20,147)
	deepSkyBlue				= 0x00BFFF,	// rgb(0,191,255)
	dimGray					= 0x696969,	// rgb(105,105,105)
	dodgerBlue				= 0x1E90FF,	// rgb(30,144,255)
	fireBrick				= 0xB22222,	// rgb(178,34,34)
	floralWhite				= 0xFFFAF0,	// rgb(255,250,240)
	forestGreen				= 0x228B22,	// rgb(34,139,34)
	fuchsia					= 0xFF00FF,	// rgb(255,0,255)
	gainsboro				= 0xDCDCDC,	// rgb(220,220,220)
	ghostWhite				= 0xF8F8FF,	// rgb(248,248,255)
	gold					= 0xFFD700,	// rgb(255,215,0)
	goldenRod				= 0xDAA520,	// rgb(218,165,32)
	gray					= 0x808080,	// rgb(128,128,128)
	green					= 0x008000,	// rgb(0,128,0)
	greenYellow				= 0xADFF2F,	// rgb(173,255,47)
	honeyDew				= 0xF0FFF0,	// rgb(240,255,240)
	hotPink					= 0xFF69B4,	// rgb(255,105,180)
	indianRed				= 0xCD5C5C,	// rgb(205,92,92)
	indigo					= 0x4B0082,	// rgb(75,0,130)
	ivory					= 0xFFFFF0,	// rgb(255,255,240)
	khaki					= 0xF0E68C,	// rgb(240,230,140)
	lavender				= 0xE6E6FA,	// rgb(230,230,250)
	lavenderBlush			= 0xFFF0F5,	// rgb(255,240,245)
	lawnGreen				= 0x7CFC00,	// rgb(124,252,0)
	lemonChiffon			= 0xFFFACD,	// rgb(255,250,205)
	lightBlue				= 0xADD8E6,	// rgb(173,216,230)
	lightCoral				= 0xF08080,	// rgb(240,128,128)
	lightCyan				= 0xE0FFFF,	// rgb(224,255,255)
	lightGoldenRodYellow	= 0xFAFAD2,	// rgb(250,250,210)
	lightGray				= 0xD3D3D3,	// rgb(211,211,211)
	lightGreen				= 0x90EE90,	// rgb(144,238,144)
	lightPink				= 0xFFB6C1,	// rgb(255,182,193)
	lightSalmon				= 0xFFA07A,	// rgb(255,160,122)
	lightSeaGreen			= 0x20B2AA,	// rgb(32,178,170)
	lightSkyBlue			= 0x87CEFA,	// rgb(135,206,250)
	lightSlateGray			= 0x778899,	// rgb(119,136,153)
	lightSteelBlue			= 0xB0C4DE,	// rgb(176,196,222)
	lightYellow				= 0xFFFFE0,	// rgb(255,255,224)
	lime					= 0x00FF00,	// rgb(0,255,0)
	limeGreen				= 0x32CD32,	// rgb(50,205,50)
	linen					= 0xFAF0E6,	// rgb(250,240,230)
	magenta					= 0xFF00FF,	// rgb(255,0,255)
	maroon					= 0x800000,	// rgb(128,0,0)
	mediumAquamarine		= 0x66CDAA,	// rgb(102,205,170)
	mediumBlue				= 0x0000CD,	// rgb(0,0,205)
	mediumOrchid			= 0xBA55D3,	// rgb(186,85,211)
	mediumPurple			= 0x9370DB,	// rgb(147,112,219)
	mediumSeaGreen			= 0x3CB371,	// rgb(60,179,113)
	mediumSlateBlue			= 0x7B68EE,	// rgb(123,104,238)
	mediumSpringGreen		= 0x00FA9A,	// rgb(0,250,154)
	mediumTurquoise			= 0x48D1CC,	// rgb(72,209,204)
	mediumVioletRed			= 0xC71585,	// rgb(199,21,133)
	midnightBlue			= 0x191970,	// rgb(25,25,112)
	mintCream				= 0xF5FFFA,	// rgb(245,255,250)
	mistyRose				= 0xFFE4E1,	// rgb(255,228,225)
	moccasin				= 0xFFE4B5,	// rgb(255,228,181)
	navajoWhite				= 0xFFDEAD,	// rgb(255,222,173)
	navy					= 0x000080,	// rgb(0,0,128)
	oldLace					= 0xFDF5E6,	// rgb(253,245,230)
	olive					= 0x808000,	// rgb(128,128,0)
	oliveDrab				= 0x6B8E23,	// rgb(107,142,35)
	orange					= 0xFFA500,	// rgb(255,165,0)
	orangeRed				= 0xFF4500,	// rgb(255,69,0)
	orchid					= 0xDA70D6,	// rgb(218,112,214)
	paleGoldenRod			= 0xEEE8AA,	// rgb(238,232,170)
	paleGreen				= 0x98FB98,	// rgb(152,251,152)
	paleTurquoise			= 0xAFEEEE,	// rgb(175,238,238)
	paleVioletRed			= 0xDB7093,	// rgb(219,112,147)
	papayaWhip				= 0xFFEFD5,	// rgb(255,239,213)
	peachPuff				= 0xFFDAB9,	// rgb(255,218,185)
	peru					= 0xCD853F,	// rgb(205,133,63)
	pink					= 0xFFC0CB,	// rgb(255,192,203)
	plum					= 0xDDA0DD,	// rgb(221,160,221)
	powderBlue				= 0xB0E0E6,	// rgb(176,224,230)
	purple					= 0x800080,	// rgb(128,0,128)
	rebeccaPurple			= 0x663399,	// rgb(102,51,153)
	red						= 0xFF0000,	// rgb(255,0,0)
	rosyBrown				= 0xBC8F8F,	// rgb(188,143,143)
	royalBlue				= 0x4169E1,	// rgb(65,105,225)
	saddleBrown				= 0x8B4513,	// rgb(139,69,19)
	salmon					= 0xFA8072,	// rgb(250,128,114)
	sandyBrown				= 0xF4A460,	// rgb(244,164,96)
	seaGreen				= 0x2E8B57,	// rgb(46,139,87)
	seaShell				= 0xFFF5EE,	// rgb(255,245,238)
	sienna					= 0xA0522D,	// rgb(160,82,45)
	silver					= 0xC0C0C0,	// rgb(192,192,192)
	skyBlue					= 0x87CEEB,	// rgb(135,206,235)
	slateBlue				= 0x6A5ACD,	// rgb(106,90,205)
	slateBray				= 0x708090,	// rgb(112,128,144)
	snow					= 0xFFFAFA,	// rgb(255,250,250)
	springGreen				= 0x00FF7F,	// rgb(0,255,127)
	steelBlue				= 0x4682B4,	// rgb(70,130,180)
	tan						= 0xD2B48C,	// rgb(210,180,140)
	teal					= 0x008080,	// rgb(0,128,128)
	thistle					= 0xD8BFD8,	// rgb(216,191,216)
	tomato					= 0xFF6347,	// rgb(255,99,71)
	turquoise				= 0x40E0D0,	// rgb(64,224,208)
	violet					= 0xEE82EE,	// rgb(238,130,238)
	wheat					= 0xF5DEB3,	// rgb(245,222,179)
	white					= 0xFFFFFF,	// rgb(255,255,255)
	whiteSmoke				= 0xF5F5F5,	// rgb(245,245,245)
	yellow					= 0xFFFF00,	// rgb(255,255,0)
	yellowGreen				= 0x9ACD32	// rgb(154,205,50)
};

class NB_API Color
{
public:
	Color() : Color(255, 0, 0, 0) {}
	Color(uint8_t _r, uint8_t _g, uint8_t _b) : Color(255, _r, _g, _b) {}
	Color(uint8_t _a, uint8_t _r, uint8_t _g, uint8_t _b) : a(_a), r(_r), g(_g), b(_b) {}
	Color(uint32_t argb) : a((argb & 0xFF000000) >> 24), r((argb & 0x00FF0000) >> 16), g((argb & 0x0000FF00) >> 8), b(argb & 0x000000FF){}
	Color(Colors c) : Color((uint32_t)c | 0xFF000000) { }

	static Color fromArgbF(float af, float rf, float gf, float bf)	{ Color c; c.setArgbf(af, rf, gf, bf); return c; }
	static Color fromRgbF(float rf, float gf, float bf)				{ return fromArgbF(1.0f, rf, gf, bf); }

	bool operator ==(const Color &c) const					{ return !(operator!=(c)); }
	bool operator !=(const Color &c) const					{ return (a != c.a) || (r != c.r || g != c.g) || (b != c.b); }

	//浮点形式（0.0-1.0)
	void setArgbf(float af, float rf, float gf, float bf)	{ setaf(af); setrf(rf); setgf(gf); setbf(bf); }
	void setRgbf(float rf, float gf, float bf)				{ setrf(rf); setgf(gf); setbf(bf); }
	void setaf(float af)									{ a = (uint8_t)std::round(nb::clamp(af, 0.0f, 1.0f) * 255); }
	void setrf(float rf)									{ r = (uint8_t)std::round(nb::clamp(rf, 0.0f, 1.0f) * 255); }
	void setgf(float gf)									{ g = (uint8_t)std::round(nb::clamp(gf, 0.0f, 1.0f) * 255); }
	void setbf(float bf)									{ b = (uint8_t)std::round(nb::clamp(bf, 0.0f, 1.0f) * 255); }
	float af() const										{ return a / 255.0f; }
	float rf() const										{ return r / 255.0f; }
	float gf() const										{ return g / 255.0f; }
	float bf() const										{ return b / 255.0f; }

	//色调/饱和度/亮度
	void setHsv(const glm::vec3 &hsv) &						{ auto rgbf = glm::rgbColor(hsv); setrf(rgbf.x); setrf(rgbf.y); setrf(rgbf.z); }
	glm::vec3 hsv() const									{ return glm::hsvColor(glm::vec3(rf(), gf(), bf())); }

	//整数
	void setIntegerArgb(uint32_t argb)						{ a = (argb & 0xFF000000) >> 24; r = (argb & 0x00FF0000) >> 16; g = (argb & 0x0000FF00) >> 8; b = (argb & 0x000000FF); }
	void setIntegerRgb(uint32_t rgb)						{ setIntegerArgb(rgb | 0xFF000000); }
	uint32_t integerArgb() const							{ return (a << 24) | integerRgb(); }
	uint32_t integerRgb() const								{ return (r << 16) | (g << 8) | (b); }

	//转换为字符串RGB，形如#FFFFFF
	void setStringValue(const std::string &sHex);
	std::string stringValue() const							{ char arr[10] = { 0 }; snprintf(arr, sizeof(arr), "#%6X", integerRgb()); return arr; }

	uint8_t a,r,g,b;
};

class NB_API Thickness
{
public:
	Thickness() : Thickness(0, 0, 0, 0) {}
	Thickness(float uniform) : Thickness(uniform, uniform, uniform, uniform) {}
	Thickness(float _left, float _top, float _right, float _bottom) : left(_left) , top(_top) , right(_right) , bottom(_bottom) {}

	bool operator == (const Thickness &other) const			{ return left == other.left && top == other.top && right == other.right && bottom == other.bottom; }
	bool operator != (const Thickness &other) const			{ return !(*this == other); }
	Thickness operator - (float f) const					{ return Thickness(left - f, top - f, right - f, bottom - f); }
	void operator -= (float f)								{ operator = (operator -(f)); }
	Thickness operator + (float f) const					{ return Thickness(left + f, top + f, right + f, bottom + f); }
	void operator += (float f)								{ operator = (operator +(f)); }
	Thickness operator * (float f) const					{ return Thickness(left * f, top * f, right * f, bottom * f); }
	void operator *= (float f)								{ operator = (operator *(f)); }

	float left,top,right,bottom;
};

inline void Color::setStringValue(const std::string &sHex)
{
	std::regex reg("^#[0-9A-Za-z]{6}$");
	nbThrowExceptionIf(!std::regex_match(sHex, reg), std::invalid_argument, "sHex[%s] is not match '#FFFFFF'", sHex.data());

	try { setIntegerRgb(std::stoi("0x" + sHex.substr(1), 0, 16)); }
	catch (...) { nbThrowException(std::invalid_argument, "sHex[%s] is not match color format string", sHex.data()); }
}

class NB_API TimeSpan
{
public:
	//构建一个时间间隔TimeSpan，0
	TimeSpan() : TimeSpan(0, 0, 0, 0, 0, 0) {}
	TimeSpan(int hours, int minutes, int seconds) : TimeSpan(0, hours, minutes, seconds, 0, 0) {}
	TimeSpan(int hours, int minutes, int seconds, int milliseconds) : TimeSpan(0, hours, minutes, seconds, milliseconds, 0) {}
	TimeSpan(int hours, int minutes, int seconds, int milliseconds, int64_t microseconds) : TimeSpan(0, hours, minutes, seconds, milliseconds, microseconds) {}
	TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds, int64_t microseconds) : m_micros(days * 86400000000 + hours * (int64_t)3600000000 + minutes * (int64_t)60000000 + seconds * std::micro::den + milliseconds * std::milli::den + microseconds) {}

	//从天、时、分、秒、毫秒构建TimeSpan
	static TimeSpan fromDays(int days)						{ return TimeSpan(days, 0, 0, 0, 0, 0); }
	static TimeSpan fromHours(int hours)					{ return TimeSpan(0, hours, 0, 0, 0, 0); }
	static TimeSpan fromMinutes(int minutes)				{ return TimeSpan(0, 0, minutes, 0, 0, 0); }
	static TimeSpan fromSeconds(int seconds)				{ return TimeSpan(0, 0, 0, seconds, 0, 0); }
	static TimeSpan fromMilliseconds(int milliseconds)		{ return TimeSpan(0, 0, 0, 0, milliseconds, 0); }
	static TimeSpan fromMicroseconds(int64_t microseconds)	{ return TimeSpan(0, 0, 0, 0, 0, microseconds); }
	static TimeSpan zero()									{ return TimeSpan(0, 0, 0, 0, 0, 0); }

	void operator =(const TimeSpan &other) &				{ m_micros = other.m_micros; }
	TimeSpan operator -() const								{ return TimeSpan::fromMicroseconds(-m_micros); }
	bool operator !=(const TimeSpan &other) const			{ return m_micros != other.m_micros; }
	bool operator <(const TimeSpan &other) const			{ return m_micros < other.m_micros; }
	bool operator >(const TimeSpan &other) const			{ return other < *this; }
	bool operator ==(const TimeSpan &other) const			{ return !(*this != other); }
	bool operator <=(const TimeSpan &other) const			{ return !(*this > other); }
	bool operator >=(const TimeSpan &other) const			{ return !(*this < other); }
	TimeSpan operator +(const TimeSpan &other) const		{ return TimeSpan::fromMicroseconds(m_micros + other.m_micros); }
	void operator +=(const TimeSpan &other) &				{ operator =(operator +(other)); }
	TimeSpan operator -(const TimeSpan &other) const		{ return operator+(-other); }
	void operator -=(const TimeSpan &other) &				{ operator = (operator -(other)); }

	//天数、小时数（-23到23）、分钟数（-59到59）、秒数（-59到59）、毫秒数（-999到999）、微秒数（-999到999）
	int days() const										{ return (int)(totalMicroseconds() / 86400000000); }
	int hours() const										{ return (int)(totalMicroseconds() % 86400000000 / 3600000000); }
	int minutes() const										{ return (int)(totalMicroseconds() % 86400000000 % 3600000000 / 60000000); }
	int seconds() const										{ return (int)(totalMicroseconds() % 86400000000 % 3600000000 % 60000000 / std::micro::den); }
	int milliseconds() const								{ return (int)(totalMicroseconds() % 86400000000 % 3600000000 % 60000000 % std::micro::den / std::milli::den); }
	int microseconds() const								{ return (int)(totalMicroseconds() % 86400000000 % 3600000000 % 60000000 % std::micro::den % std::milli::den); }

	//转换成相应的天数、时数、分数、秒数、毫秒数、微秒数
	double totalDays() const								{ return (double)totalMicroseconds() / 86400000000; }
	double totalHours() const								{ return (double)totalMicroseconds() / 3600000000; }
	double totalMinutes() const								{ return (double)totalMicroseconds() / 60000000; }
	double totalSeconds() const								{ return (double)totalMicroseconds() / std::micro::den; }
	double totalMilliseconds() const						{ return (double)totalMicroseconds() / std::milli::den; }
	int64_t totalMicroseconds() const						{ return m_micros; }

	std::string toString() const
	{
		char buf[128] = {0};
		sprintf(buf, "%s%d.%02d:%02d:%02d.%03d.%03d",
			*this < TimeSpan::zero() ? "-" : "", std::abs(days()), std::abs(hours()), 
			std::abs(minutes()), std::abs(seconds()), std::abs(milliseconds()), std::abs(microseconds()));
		return buf;
	}

private:
	int64_t	m_micros;
};

}