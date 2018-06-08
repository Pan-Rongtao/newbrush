#include <assert.h>
#include "system/System.h"
#include "system/Color.h"

using namespace nb::System;

NB_OBJECT_TYPE_IMPLEMENT(Color, ValueObject, &ValueObject::IsEqualFun<Color>, &ValueObject::CopyFun<Color>);

Color::Color()
{
	SetArgb(255, 0, 0, 0);
}

Color::Color(int r, int g, int b)
{
	SetArgb(255, r, g, b);
}

Color::Color(int a, int r, int g, int b)
{
	SetArgb(a, r, g, b);
}

Color::Color(const Color &other)
{
	SetArgb(other.GetAlpha(), other.GetRed(), other.GetGreen(), other.GetBlue());
}

Color::~Color()
{

}

void Color::operator =(const Color &other)
{
	SetArgb(other.GetAlpha(), other.GetRed(), other.GetGreen(), other.GetBlue());
}

bool Color::operator ==(const Color &other) const
{
	return GetAlpha() == other.GetAlpha() && GetRed() == other.GetRed() && GetGreen() == other.GetGreen() && GetBlue() == other.GetBlue();
}

bool Color::operator !=(const Color &other) const
{
	return !(*this == other);
}

int Color::GetAlpha() const
{
	return m_nAlpha;
}

int Color::GetRed() const
{
	return m_nRed;
}

int Color::GetGreen() const
{
	return m_nGreen;
}

int Color::GetBlue() const
{
	return m_nBlue;
}

void Color::SetAlpha(int a)
{
	SetArgb(a, GetRed(), GetGreen(), GetBlue());
}

void Color::SetRed(int r)
{
	SetArgb(GetAlpha(), r, GetGreen(), GetBlue());
}

void Color::SetGreen(int g)
{
	SetArgb(GetAlpha(), GetRed(), g, GetBlue());
}

void Color::SetBlue(int b)
{
	SetArgb(GetAlpha(), GetRed(), GetGreen(), b);
}

void Color::SetRgb(int r, int g, int b)
{
	SetArgb(GetAlpha(), r, g, b);
}

void Color::SetArgb(int a, int r, int g, int b)
{
	//rewrite it when define assert
	assert(IsValidArgb(a, r, g, b));
	m_nAlpha = a;
	m_nRed = r;
	m_nGreen = g;
	m_nBlue = b;
}

float Color::GetAlphaF() const
{
	return Argb2ArgbF(GetAlpha());
}

float Color::GetRedF() const
{
	return Argb2ArgbF(GetRed());
}

float Color::GetGreenF() const
{
	return Argb2ArgbF(GetGreen());
}

float Color::GetBlueF() const
{
	return Argb2ArgbF(GetBlue());
}

void Color::SetAlphaF(float a)
{
	SetArgbF(a, GetRedF(), GetGreenF(), GetBlueF());
}

void Color::SetRedF(float r)
{
	SetArgbF(GetAlphaF(), r, GetGreenF(), GetBlueF());
}

void Color::SetGreenF(float g)
{
	SetArgbF(GetAlphaF(), GetRedF(), g, GetBlueF());
}

void Color::SetBlueF(float b)
{
	SetArgbF(GetAlphaF(), GetRedF(), GetGreenF(), b);
}

void Color::SetRgbF(float r, float g, float b)
{
	SetArgbF(GetAlphaF(), r, g, b);
}

void Color::SetArgbF(float a, float r, float g, float b)
{
	assert(IsValidArgbF(a, r, g, b));
	SetAlpha(ArgbF2Argb(a));
	SetRed(ArgbF2Argb(r));
	SetGreen(ArgbF2Argb(g));
	SetBlue(ArgbF2Argb(b));
}

float Color::GetHue() const
{
	float h, s, v;
	RgbF2Hsv(GetRedF(), GetGreenF(), GetBlueF(), h, s, v);
	return h;
}

float Color::GetSaturation() const
{
	float h, s, v;
	RgbF2Hsv(GetRedF(), GetGreenF(), GetBlueF(), h, s, v);
	return s;
}

float Color::GetValue() const
{
	float h, s, v;
	RgbF2Hsv(GetRedF(), GetGreenF(), GetBlueF(), h, s, v);
	return v;
}

void Color::SetHue(float h)
{
	SetHsv(h, GetSaturation(), GetValue());
}

void Color::SetSaturation(float s)
{
	SetHsv(GetHue(), s, GetValue());
}

void Color::SetValue(float v)
{
	SetHsv(GetHue(), GetSaturation(), v);
}

void Color::SetHsv(float h, float s, float v)
{
	//rewrite when define assert
	assert(IsValidHsv(h, s, v));
	float r, g, b;
	Hsv2RgbF(h, s, v, r, g, b);
	SetArgbF(GetAlphaF(), r, g, b);
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
void Color::SetInteger32(unsigned int argb)
{
	int a = (argb & 0xff000000) >> 24;
	int r = (argb & 0x00ff0000) >> 16;
	int g = (argb & 0x0000ff00) >> 8;
	int b = (argb & 0x000000ff);
	SetArgb(a, r, g, b);
}

unsigned int Color::ToInteger32() const
{
	return (GetAlpha() << 24) | (GetRed() << 16) | (GetGreen() << 8) | (GetBlue()) ;
}

bool Color::Equals(const Color &other) const
{
	return *this == other;
}

bool Color::IsEmpty() const
{
	return *this == Color::Empty();
}

bool Color::IsValidArgb(int a, int r, int g, int b)
{
	return (a >= 0 && a <= 255) && (r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255);
}

bool Color::IsValidArgbF(float a, float r, float g, float b)
{
	return (a >= 0.0 && a <= 1.0) && (r >= 0.0 && r <= 1.0) && (g >= 0.0 && g <= 1.0) && (b >= 0.0 && b <= 1.0);
}

bool Color::IsValidHsv(float h, float s, float v)
{
	return (h >= 0.0 && h <= 360.0) && (s >= 0.0 && s <= 1.0) && (v >= 0.0 && v <= 1.0);
}

Color Color::FromInteger32(unsigned int argb)
{
	Color c;
	c.SetInteger32(argb);
	return c;
}

Color Color::FromHsv(float h, float s, float v)
{
	Color c;
	c.SetHsv(h, s, v);
	return c;
}
/*
Color Color::FromCmyk(int c, int m, int y, int k)
{
	return Color();
}
*/

Color Color::FromRgbF(float r, float g, float b)
{
	return FromArgbF(1.0f, r, g, b);
}

Color Color::FromArgbF(float a, float r, float g, float b)
{
	return Color(ArgbF2Argb(a), ArgbF2Argb(r), ArgbF2Argb(g), ArgbF2Argb(b));
}

Color Color::Empty()
{
	return Color(0, 0, 0, 0);
}
/*
Color Color::FromRGBAHexString(const String &sHex)
{

}
*/
int Color::ArgbF2Argb(float f)
{
	assert(f >= 0.0 && f <= 1.0);
	return nb::System::Round(f * 255);
}

float Color::Argb2ArgbF(int n)
{
	assert(n >= 0 && n <= 255);
	return (float)n / 255.0f;
}
//以下为公式
void Color::RgbF2Hsv(float r, float g, float b, float &h, float &s, float &v)
{
	////
	assert(IsValidArgbF(1.0, r, g, b));
	float fMax = nb::System::Max(r, g, b);
	float fMin = nb::System::Min(r, g, b);
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
void Color::Hsv2RgbF(float h, float s, float v, float &r, float &g, float &b)
{
	////
	assert(IsValidHsv(h, s, v));
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
		default: assert(0);	//will never do this
		}
	}
}
