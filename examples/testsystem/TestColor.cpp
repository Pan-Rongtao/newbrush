#include "TestColor.h"
#include "system/Color.h"
#include "limits.h"
#include "system/Platform.h"
using namespace nb::System;
TestColor::TestColor(void)
{
}

TestColor::~TestColor(void)
{
}

void TestColor::Test()
{
	Color c1;
	Color c2(255, 0, 0);
	Color c3(125, 0, 255, 0);
	Color c4(c1);
	c4 = c3;
	Color c5 = Color::FromInteger32(0xFF00AA77);
	Color c6 = Color::FromRgbF(0.3f, 0.5f, 1.000f);
	Color c7 = Color::FromArgbF(0.0f, 1.0f, 1.0f, 0.0f);
	bool b = c1.Equals(Color::Empty());

	bool b1 = Color::IsValidArgb(255, 255, 255, 255);
	bool b2 = Color::IsValidArgbF(1.000000000000001f, 0.0f, 0.0f, 0.0f);
	Color c8 = Color::FromArgbF(1.000000000000001f, 0.0f, 0.0f, 0.0f);
	int a = c8.GetAlpha();
	int r = c8.GetRed();
	int g = c8.GetGreen();
	int blue = c8.GetBlue();

	Color c9(125, 127, 199, 250);
	float fa = c9.GetAlphaF();
	float fr = c9.GetRedF();
	float fg = c9.GetGreenF();
	float fb = c9.GetBlueF();
	c9.SetAlpha(55);
	c9.SetRed(66);
	c9.SetGreen(77);
	c9.SetBlue(88);
	c9.SetAlphaF(0.67f);
	c9.SetRedF(0.33f);
	c9.SetGreenF(0.79f);
	c9.SetBlueF(1.000000000000001f);
	c9.SetRgb(0, 1, 2);
	c9.SetArgb(11, 22, 4, 55);
	c9.SetRgbF(0.3f, 0.7f, 0.6f);
	c9.SetArgbF(0.0f, 0.2f, 0.4f, 0.8f);

	c9.SetInteger32(0x44124366);
	unsigned int xx = c9.ToInteger32();

	bool b3 = Color(0, 0, 0, 0).IsEmpty();
	bool b4 = Color(0, 0, 0, 0) != Color::Empty();

	bool b5 = Color::IsValidHsv(360.0, 1.0, 1.0000);

	float ff = 0.0;
	float fff = 1.0f / ff;
//	for(int r = 0; r <= 255; ++r)
	{
//		for(int g = 0; g <= 255; ++g)
		{
//			for(int b = 0; b <= 255; ++b)
			{
				Color c = Color(153, 45, 2);
				float h = c.GetHue();
				float s = c.GetSaturation();
				float v = c.GetValue();
			}
		}
	}
	Color c20;
	c20.SetHsv(100, 0.11f, 0.86f);
	c20.SetHue(360);
	c20.SetSaturation(0.49f);
	c20.SetValue(0.99f);

	return;
	UInt64 n = Platform::GetTickCount();
	for(float h = 0.0; h <= 360.0f; h += 1)
	{
		for(float s = 0.0f; s <= 1.0; s += 0.01f)
		{
			for(float v = 0.0f; v <= 1.0f; v += 0.01f)
			{
				c20.SetHsv(h, s, v);
				float hh = c20.GetHue();
				float ss = c20.GetSaturation();
				float vv = c20.GetValue();
				//if(hh == 0.0 && ss == 0.0 && vv == 0.0)
				//	printf("h:%.2f, s:%.2f, v:%.2f\n", h, s, v);
			}
		}
	}
	UInt64 nn = Platform::GetTickCount() - n;
	printf("%lld\n", nn);
}