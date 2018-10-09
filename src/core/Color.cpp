#include <algorithm>
#include "core/Color.h"
#include "core/Exception.h"

using namespace nb::core;

Color::Color()
{
	setArgb(255, 0, 0, 0);
}

Color::Color(uint8_t r, uint8_t g, uint8_t b)
{
	setArgb(255, r, g, b);
}

Color::Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
	setArgb(a, r, g, b);
}

Color::Color(const Color &other)
{
	setArgb(other.alpha(), other.red(), other.green(), other.blue());
}

Color::~Color()
{

}

void Color::operator =(const Color &other)
{
	setArgb(other.alpha(), other.red(), other.green(), other.blue());
}

bool Color::operator ==(const Color &other) const
{
	return alpha() == other.alpha() && red() == other.red() && green() == other.green() && blue() == other.blue();
}

bool Color::operator !=(const Color &other) const
{
	return !(*this == other);
}

uint8_t &Color::alpha()
{
	return m_Alpha;
}

uint8_t Color::alpha() const
{
	return m_Alpha;
}

uint8_t &Color::red()
{
	return m_Red;
}

uint8_t Color::red() const
{
	return m_Red;
}

uint8_t &Color::green()
{
	return m_Green;
}

uint8_t Color::green() const
{
	return m_Green;
}

uint8_t &Color::blue()
{
	return m_Blue;
}

uint8_t Color::blue() const
{
	return m_Blue;
}

void Color::setAlpha(uint8_t a)
{
	setArgb(a, red(), green(), blue());
}

void Color::setRed(uint8_t r)
{
	setArgb(alpha(), r, green(), blue());
}

void Color::setGreen(uint8_t g)
{
	setArgb(alpha(), red(), g, blue());
}

void Color::setBlue(uint8_t b)
{
	setArgb(alpha(), red(), green(), b);
}

void Color::setRgb(uint8_t r, uint8_t g, uint8_t b)
{
	setArgb(alpha(), r, g, b);
}

void Color::setArgb(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
	if (!isValidArgb(a, r, g, b))	throw ArgumentException("argb", __FILE__, __LINE__);
	m_Alpha = a;
	m_Red = r;
	m_Green = g;
	m_Blue = b;
}

float Color::alphaF() const
{
	return argb2ArgbF(alpha());
}

float Color::redF() const
{
	return argb2ArgbF(red());
}

float Color::greenF() const
{
	return argb2ArgbF(green());
}

float Color::blueF() const
{
	return argb2ArgbF(blue());
}

void Color::setAlphaF(float a)
{
	setArgbF(a, redF(), greenF(), blueF());
}

void Color::setRedF(float r)
{
	setArgbF(alphaF(), r, greenF(), blueF());
}

void Color::setGreenF(float g)
{
	setArgbF(alphaF(), redF(), g, blueF());
}

void Color::setBlueF(float b)
{
	setArgbF(alphaF(), redF(), greenF(), b);
}

void Color::setRgbF(float r, float g, float b)
{
	setArgbF(alphaF(), r, g, b);
}

void Color::setArgbF(float a, float r, float g, float b)
{
	if (!isValidArgbF(a, r, g, b))	throw ArgumentException("argb", __FILE__, __LINE__);
	setAlpha(argbF2Argb(a));
	setRed(argbF2Argb(r));
	setGreen(argbF2Argb(g));
	setBlue(argbF2Argb(b));
}

float Color::hue() const
{
	float h, s, v;
	rgbF2Hsv(redF(), greenF(), blueF(), h, s, v);
	return h;
}

float Color::saturation() const
{
	float h, s, v;
	rgbF2Hsv(redF(), greenF(), blueF(), h, s, v);
	return s;
}

float Color::value() const
{
	float h, s, v;
	rgbF2Hsv(redF(), greenF(), blueF(), h, s, v);
	return v;
}

void Color::setHue(float h)
{
	setHsv(h, saturation(), value());
}

void Color::setSaturation(float s)
{
	setHsv(hue(), s, value());
}

void Color::setValue(float v)
{
	setHsv(hue(), saturation(), v);
}

void Color::setHsv(float h, float s, float v)
{
	if (!isValidHsv(h, s, v))	throw ArgumentException("hsv", __FILE__, __LINE__);
	float r, g, b;
	hsv2RgbF(h, s, v, r, g, b);
	setArgbF(alphaF(), r, g, b);
}

////屏蔽cmyk格式
/*
void Color::SetCmyk(int c, int m, int y, int k)
{

}

void Color::GetCmyk(int *c, int *m, int *y, int *k)
{

}
*/
void Color::setInteger32(uint32_t argb)
{
	int a = (argb & 0xff000000) >> 24;
	int r = (argb & 0x00ff0000) >> 16;
	int g = (argb & 0x0000ff00) >> 8;
	int b = (argb & 0x000000ff);
	setArgb(a, r, g, b);
}

uint32_t Color::toInteger32() const
{
	return (alpha() << 24) | (red() << 16) | (green() << 8) | (blue()) ;
}

bool Color::equals(const Color &other) const
{
	return *this == other;
}

bool Color::isValidArgb(int a, int r, int g, int b)
{
	return (a >= 0 && a <= 255) && (r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255);
}

bool Color::isValidArgbF(float a, float r, float g, float b)
{
	return (a >= 0.0 && a <= 1.0) && (r >= 0.0 && r <= 1.0) && (g >= 0.0 && g <= 1.0) && (b >= 0.0 && b <= 1.0);
}

bool Color::isValidHsv(float h, float s, float v)
{
	return (h >= 0.0 && h <= 360.0) && (s >= 0.0 && s <= 1.0) && (v >= 0.0 && v <= 1.0);
}

Color Color::fromInteger32(unsigned int argb)
{
	Color c;
	c.setInteger32(argb);
	return c;
}

Color Color::fromHsv(float h, float s, float v)
{
	Color c;
	c.setHsv(h, s, v);
	return c;
}
/*
Color Color::FromCmyk(int c, int m, int y, int k)
{
	return Color();
}
*/

Color Color::fromRgbF(float r, float g, float b)
{
	return fromArgbF(1.0f, r, g, b);
}

Color Color::fromArgbF(float a, float r, float g, float b)
{
	return Color(argbF2Argb(a), argbF2Argb(r), argbF2Argb(g), argbF2Argb(b));
}

/*
Color Color::FromRGBAHexString(const String &sHex)
{

}
*/
uint8_t Color::argbF2Argb(float f)
{
	if (f < 0.0 || f > 1.0)		throw ArgumentOutOfRangeException("f", 0.0, 1.0, f, __FILE__, __LINE__);
	return (uint8_t)std::round(f * 255);
}

float Color::argb2ArgbF(uint8_t n)
{
	if (n < 0 && n > 255)
		throw ArgumentOutOfRangeException("n", 0, 255, n, __FILE__, __LINE__);
	return (float)n / 255.0f;
}
//以下为公式
void Color::rgbF2Hsv(float r, float g, float b, float &h, float &s, float &v)
{
	if (!isValidArgbF(1.0, r, g, b))
		throw ArgumentException("rgb", __FILE__, __LINE__);
	float fMax = std::max(std::max(r, g), b);
	float fMin = std::min(std::min(r, g), b);
	v = fMax;

	if(fMax == 0.0)
	{
		s = 0.0;
		h = 0.0;
	}
	else
	{
		s = (fMax - fMin) / fMax;
		if(fMax == fMin)
		{
			h = 0.0;
		}
		else
		{
			if(r == fMax)
				h = (g - b) / (fMax - fMin);
			else if(g == fMax)
				h = 2 + (b - r) / (fMax - fMin); 
			else if(b == fMax)
				h = 4 + (r - g) / (fMax - fMin);

			h *= 60;
			if(h < 0)
				h += 360; 
		}
	} 

}
//以下为公式
void Color::hsv2RgbF(float h, float s, float v, float &r, float &g, float &b)
{
	////
	if (!isValidHsv(h, s, v))	throw ArgumentException("hsv", __FILE__, __LINE__);
	if(s == 0.0)
	{
		r = g = b = v;
	}
	else
	{
		if(h == 360.0)
			h = 0.0;
		h /= 60;
		int i = (int)h;
		float f = h - i;
		float x = v * (1 - s);
		float y = v * (1 - s * f);
		float z = v * (1 - s * (1 - f));
		switch(i)
		{
		case 0: r = v; g = z; b = x; break;
		case 1: r = y; g = v; b = x; break;
		case 2: r = x; g = v; b = z; break;
		case 3: r = x; g = y; b = v; break;
		case 4: r = z; g = x; b = v; break;
		case 5: r = v; g = x; b = y; break;
		default:					 break;
		}
	}
}

Color Color::aliceBlue()
{
	return Color(240, 248, 255);
}

Color Color::antiqueWhite()
{
	return Color(250, 235, 215);
}

Color Color::aqua()
{
	return Color(0, 255, 255);
}

Color Color::aquamarine()
{
	return Color(127, 255, 212);
}

Color Color::azure()
{
	return Color(240, 255, 255);
}

Color Color::beige()
{
	return Color(245, 245, 220);
}

Color Color::bisque()
{
	return Color(255, 228, 196);
}

Color Color::black()
{
	return Color(0, 0, 0);
}

Color Color::blanchedAlmond()
{
	return Color(255, 255, 205);
}

Color Color::bluePure()
{
	return Color(0, 0, 255);
}

Color Color::blueViolet()
{
	return Color(138, 43, 226);
}

Color Color::brown()
{
	return Color(165, 42, 42);
}

Color Color::burlyWood()
{
	return Color(222, 184, 135);
}

Color Color::cadetBlue()
{
	return Color(95, 158, 160);
}

Color Color::chartreuse()
{
	return Color(127, 255, 0);
}

Color Color::chocolate()
{
	return Color(210, 105, 30);
}

Color Color::coral()
{
	return Color(255, 127, 80);
}

Color Color::cornflowerBlue()
{
	return Color(100, 149, 237);
}

Color Color::cornsilk()
{
	return Color(255, 248, 220);
}

Color Color::crimson()
{
	return Color(220, 20, 60);
}

Color Color::cyan()
{
	return Color(0, 255, 255);
}

Color Color::darkBlue()
{
	return Color(0, 0, 139);
}

Color Color::darkCyan()
{
	return Color(0, 139, 139);
}

Color Color::darkGoldenrod()
{
	return Color(184, 134, 11);
}

Color Color::darkGray()
{
	return Color(169, 169, 169);
}

Color Color::darkGreen()
{
	return Color(0, 100, 0);
}

Color Color::darkKhaki()
{
	return Color(189, 183, 107);
}

Color Color::darkMagenta()
{
	return Color(139, 0, 139);
}

Color Color::darkOliveGreen()
{
	return Color(85, 107, 47);
}

Color Color::darkOrange()
{
	return Color(255, 140, 0);
}

Color Color::darkOrchid()
{
	return Color(153, 50, 204);
}

Color Color::darkRed()
{
	return Color(139, 0, 0);
}

Color Color::darkSalmon()
{
	return Color(233, 150, 122);
}

Color Color::darkSeaGreen()
{
	return Color(143, 188, 143);
}

Color Color::darkSlateBlue()
{
	return Color(72, 61, 139);
}

Color Color::darkSlateGray()
{
	return Color(40, 79, 79);
}

Color Color::darkTurquoise()
{
	return Color(0, 206, 209);
}

Color Color::darkViolet()
{
	return Color(148, 0, 211);
}

Color Color::deepPink()
{
	return Color(255, 20, 147);
}

Color Color::deepSkyBlue()
{
	return Color(0, 191, 255);
}

Color Color::dimGray()
{
	return Color(105, 105, 105);
}

Color Color::dodgerBlue()
{
	return Color(30, 144, 255);
}

Color Color::firebrick()
{
	return Color(178, 34, 34);
}

Color Color::floralWhite()
{
	return Color(255, 250, 240);
}

Color Color::forestGreen()
{
	return Color(34, 139, 34);
}

Color Color::fuchsia()
{
	return Color(255, 0, 255);
}

Color Color::gainsboro()
{
	return Color(220, 220, 220);
}

Color Color::ghostWhite()
{
	return Color(248, 248, 255);
}

Color Color::gold()
{
	return Color(255, 215, 0);
}

Color Color::goldenrod()
{
	return Color(218, 165, 32);
}

Color Color::gray()
{
	return Color(128, 128, 128);
}

Color Color::greenPure()
{
	return Color(0, 128, 0);
}

Color Color::greenYellow()
{
	return Color(173, 255, 47);
}

Color Color::honeydew()
{
	return Color(240, 255, 240);
}

Color Color::hotPink()
{
	return Color(255, 105, 180);
}

Color Color::indianRed()
{
	return Color(205, 92, 92);
}

Color Color::indigo()
{
	return Color(75, 0, 130);
}

Color Color::ivory()
{
	return Color(255, 240, 240);
}

Color Color::khaki()
{
	return Color(240, 230, 140);
}

Color Color::lavender()
{
	return Color(230, 230, 250);
}

Color Color::lavenderBlush()
{
	return Color(255, 240, 245);
}

Color Color::lawnGreen()
{
	return Color(124, 252, 0);
}

Color Color::lemonChiffon()
{
	return Color(255, 250, 205);
}

Color Color::lightBlue()
{
	return Color(173, 216, 230);
}

Color Color::lightCoral()
{
	return Color(240, 128, 128);
}

Color Color::lightCyan()
{
	return Color(224, 255, 255);
}

Color Color::lightGoldenrodYellow()
{
	return Color(250, 250, 210);
}

Color Color::lightGray()
{
	return Color(211, 211, 211);
}

Color Color::lightGreen()
{
	return Color(144, 238, 144);
}

Color Color::lightPink()
{
	return Color(255, 182, 193);
}

Color Color::lightSalmon()
{
	return Color(255, 160, 122);
}

Color Color::lightSeaGreen()
{
	return Color(32, 178, 170);
}

Color Color::lightSkyBlue()
{
	return Color(135, 206, 250);
}

Color Color::lightSlateGray()
{
	return Color(119, 136, 153);
}

Color Color::lightSteelBlue()
{
	return Color(176, 196, 222);
}

Color Color::lightYellow()
{
	return Color(255, 255, 224);
}

Color Color::lime()
{
	return Color(0, 255, 0);
}

Color Color::limeGreen()
{
	return Color(50, 205, 50);
}

Color Color::linen()
{
	return Color(250, 240, 230);
}

Color Color::magenta()
{
	return Color(255, 0, 255);
}

Color Color::maroon()
{
	return Color(128, 0, 0);
}

Color Color::mediumAquamarine()
{
	return Color(102, 205, 170);
}

Color Color::mediumBlue()
{
	return Color(0, 0, 205);
}

Color Color::mediumOrchid()
{
	return Color(186, 85, 211);
}

Color Color::mediumPurple()
{
	return Color(147, 112, 219);
}

Color Color::mediumSeaGreen()
{
	return Color(60, 179, 113);
}

Color Color::mediumSlateBlue()
{
	return Color(123, 104, 238);
}

Color Color::mediumSpringGreen()
{
	return Color(0, 250, 154);
}

Color Color::mediumTurquoise()
{
	return Color(72, 209, 204);
}

Color Color::mediumVioletRed()
{
	return Color(199, 21, 112);
}

Color Color::midnightBlue()
{
	return Color(25, 25, 112);
}

Color Color::mintCream()
{
	return Color(245, 255, 250);
}

Color Color::mistyRose()
{
	return Color(255, 228, 225);
}

Color Color::moccasin()
{
	return Color(255, 228, 181);
}

Color Color::navajoWhite()
{
	return Color(255, 222, 173);
}

Color Color::navy()
{
	return Color(0, 0, 128);
}

Color Color::oldLace()
{
	return Color(253, 245, 230);
}

Color Color::olive()
{
	return Color(128, 128, 0);
}

Color Color::oliveDrab()
{
	return Color(107, 142, 45);
}

Color Color::orange()
{
	return Color(255, 165, 0);
}

Color Color::orangeRed()
{
	return Color(255, 69, 0);
}

Color Color::orchid()
{
	return Color(218, 112, 214);
}

Color Color::paleGoldenrod()
{
	return Color(238, 232, 170);
}

Color Color::paleGreen()
{
	return Color(152, 251, 152);
}

Color Color::paleTurquoise()
{
	return Color(175, 238, 238);
}

Color Color::paleVioletRed()
{
	return Color(219, 112, 147);
}

Color Color::papayaWhip()
{
	return Color(255, 239, 213);
}

Color Color::peachPuff()
{
	return Color(255, 218, 155);
}

Color Color::peru()
{
	return Color(205, 133, 63);
}

Color Color::pink()
{
	return Color(255, 192, 203);
}

Color Color::plum()
{
	return Color(221, 160, 221);
}

Color Color::powderBlue()
{
	return Color(176, 224, 230);
}

Color Color::purple()
{
	return Color(128, 0, 128);
}

Color Color::redPure()
{
	return Color(255, 0, 0);
}

Color Color::rosyBrown()
{
	return Color(188, 143, 143);
}

Color Color::royalBlue()
{
	return Color(65, 105, 225);
}

Color Color::saddleBrown()
{
	return Color(139, 69, 19);
}

Color Color::salmon()
{
	return Color(250, 128, 114);
}

Color Color::sandyBrown()
{
	return Color(244, 164, 96);
}

Color Color::seaGreen()
{
	return Color(46, 139, 87);
}

Color Color::seaShell()
{
	return Color(255, 245, 238);
}

Color Color::sienna()
{
	return Color(160, 82, 45);
}

Color Color::silver()
{
	return Color(192, 192, 192);
}

Color Color::skyBlue()
{
	return Color(135, 206, 235);
}

Color Color::slateBlue()
{
	return Color(106, 90, 205);
}

Color Color::slateGray()
{
	return Color(112, 128, 144);
}

Color Color::snow()
{
	return Color(255, 250, 250);
}

Color Color::springGreen()
{
	return Color(0, 255, 127);
}

Color Color::steelBlue()
{
	return Color(70, 130, 180);
}

Color Color::tan()
{
	return Color(210, 180, 140);
}

Color Color::teal()
{
	return Color(0, 128, 128);
}

Color Color::thistle()
{
	return Color(216, 191, 216);
}

Color Color::tomato()
{
	return Color(253, 99, 71);
}

Color Color::transparent()
{
	return Color(0, 255, 255, 255);
}

Color Color::turquoise()
{
	return Color(64, 224, 208);
}

Color Color::violet()
{
	return Color(238, 130, 238);
}

Color Color::wheat()
{
	return Color(245, 222, 179);
}

Color Color::white()
{
	return Color(255, 255, 255);
}

Color Color::whiteSmoke()
{
	return Color(245, 245, 245);
}

Color Color::yellow()
{
	return Color(255, 255, 0);
}

Color Color::yellowGreen()
{
	return Color(154, 205, 50);
}
