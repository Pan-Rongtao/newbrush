#include "TestColor.h"
#include "core/Color.h"
#include "limits.h"

using namespace nb::core;

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
	Color c5 = Color::fromInteger32(0xFF00AA77);
	Color c6 = Color::fromRgbF(0.3f, 0.5f, 1.000f);
	Color c7 = Color::fromArgbF(0.0f, 1.0f, 1.0f, 0.0f);

	bool b1 = Color::isValidArgb(255, 255, 255, 255);
	bool b2 = Color::isValidArgbF(1.000000000000001f, 0.0f, 0.0f, 0.0f);
	Color c8 = Color::fromArgbF(1.000000000000001f, 0.0f, 0.0f, 0.0f);
	int a = c8.alpha();
	int r = c8.red();
	int g = c8.green();
	int blue = c8.blue();

	Color c9(125, 127, 199, 250);
	float fa = c9.alphaF();
	float fr = c9.redF();
	float fg = c9.greenF();
	float fb = c9.blueF();
	c9.setAlpha(55);
	c9.setRed(66);
	c9.setGreen(77);
	c9.setBlue(88);
	c9.setAlphaF(0.67f);
	c9.setRedF(0.33f);
	c9.setGreenF(0.79f);
	c9.setBlueF(1.000000000000001f);
	c9.setRgb(0, 1, 2);
	c9.setArgb(11, 22, 4, 55);
	c9.setRgbF(0.3f, 0.7f, 0.6f);
	c9.setArgbF(0.0f, 0.2f, 0.4f, 0.8f);

	c9.setInteger32(0x44124366);
	unsigned int xx = c9.toInteger32();

	bool b5 = Color::isValidHsv(360.0, 1.0, 1.0000);

	float ff = 0.0;
	float fff = 1.0f / ff;
//	for(int r = 0; r <= 255; ++r)
	{
//		for(int g = 0; g <= 255; ++g)
		{
//			for(int b = 0; b <= 255; ++b)
			{
				Color c = Color(153, 45, 2);
				float h = c.hue();
				float s = c.saturation();
				float v = c.value();
			}
		}
	}
	Color c20;
	c20.setHsv(100, 0.11f, 0.86f);
	c20.setHue(360);
	c20.setSaturation(0.49f);
	c20.setValue(0.99f);

	return;
	uint64_t n = nb::getTickCount();
	for(float h = 0.0; h <= 360.0f; h += 1)
	{
		for(float s = 0.0f; s <= 1.0; s += 0.01f)
		{
			for(float v = 0.0f; v <= 1.0f; v += 0.01f)
			{
				c20.setHsv(h, s, v);
				float hh = c20.hue();
				float ss = c20.saturation();
				float vv = c20.value();
				//if(hh == 0.0 && ss == 0.0 && vv == 0.0)
				//	printf("h:%.2f, s:%.2f, v:%.2f\n", h, s, v);
			}
		}
	}
	uint64_t nn = nb::getTickCount() - n;
	printf("%lld\n", nn);

	Color c = Color::aliceBlue();
	c = Color::antiqueWhite();
	c = Color::aqua();
	c = Color::aquamarine();
	c = Color::azure();
	c = Color::beige();
	c = Color::bisque();
	c = Color::black();
	c = Color::blanchedAlmond();
	c = Color::bluePure();
	c = Color::blueViolet();
	c = Color::brown();
	c = Color::burlyWood();
	c = Color::cadetBlue();
	c = Color::chartreuse();
	c = Color::chocolate();
	c = Color::coral();
	c = Color::cornflowerBlue();
	c = Color::cornsilk();
	c = Color::crimson();
	c = Color::cyan();
	c = Color::darkBlue();
	c = Color::darkCyan();
	c = Color::darkGoldenrod();
	c = Color::darkGray();
	c = Color::darkGreen();
	c = Color::darkKhaki();
	c = Color::darkMagenta();
	c = Color::darkOliveGreen();
	c = Color::darkOrange();
	c = Color::darkOrchid();
	c = Color::darkRed();
	c = Color::darkSalmon();
	c = Color::darkSeaGreen();
	c = Color::darkSlateBlue();
	c = Color::darkSlateGray();
	c = Color::darkTurquoise();
	c = Color::darkViolet();
	c = Color::deepPink();
	c = Color::deepSkyBlue();
	c = Color::dimGray();
	c = Color::dodgerBlue();
	c = Color::firebrick();
	c = Color::floralWhite();
	c = Color::forestGreen();
	c = Color::fuchsia();
	c = Color::gainsboro();
	c = Color::ghostWhite();
	c = Color::gold();
	c = Color::goldenrod();
	c = Color::gray();
	c = Color::greenPure();
	c = Color::greenYellow();
	c = Color::honeydew();
	c = Color::hotPink();
	c = Color::indianRed();
	c = Color::indigo();
	c = Color::ivory();
	c = Color::khaki();
	c = Color::lavender();
	c = Color::lavenderBlush();
	c = Color::lawnGreen();
	c = Color::lemonChiffon();
	c = Color::lightBlue();
	c = Color::lightCoral();
	c = Color::lightCyan();
	c = Color::lightGoldenrodYellow();
	c = Color::lightGray();
	c = Color::lightGreen();
	c = Color::lightPink();
	c = Color::lightSalmon();
	c = Color::lightSeaGreen();
	c = Color::lightSkyBlue();
	c = Color::lightSlateGray();
	c = Color::lightSteelBlue();
	c = Color::lightYellow();
	c = Color::lime();
	c = Color::limeGreen();
	c = Color::linen();
	c = Color::magenta();
	c = Color::maroon();
	c = Color::mediumAquamarine();
	c = Color::mediumBlue();
	c = Color::mediumOrchid();
	c = Color::mediumPurple();
	c = Color::mediumSeaGreen();
	c = Color::mediumSlateBlue();
	c = Color::mediumSpringGreen();
	c = Color::mediumTurquoise();
	c = Color::mediumVioletRed();
	c = Color::midnightBlue();
	c = Color::mintCream();
	c = Color::mistyRose();
	c = Color::moccasin();
	c = Color::navajoWhite();
	c = Color::navy();
	c = Color::oldLace();
	c = Color::olive();
	c = Color::oliveDrab();
	c = Color::orange();
	c = Color::orangeRed();
	c = Color::orchid();
	c = Color::paleGoldenrod();
	c = Color::paleGreen();
	c = Color::paleTurquoise();
	c = Color::paleVioletRed();
	c = Color::papayaWhip();
	c = Color::peachPuff();
	c = Color::peru();
	c = Color::pink();
	c = Color::plum();
	c = Color::powderBlue();
	c = Color::purple();
	c = Color::redPure();
	c = Color::rosyBrown();
	c = Color::royalBlue();
	c = Color::saddleBrown();
	c = Color::salmon();
	c = Color::sandyBrown();
	c = Color::seaGreen();
	c = Color::seaShell();
	c = Color::sienna();
	c = Color::silver();
	c = Color::skyBlue();
	c = Color::slateBlue();
	c = Color::slateGray();
	c = Color::snow();
	c = Color::springGreen();
	c = Color::steelBlue();
	c = Color::tan();
	c = Color::teal();
	c = Color::thistle();
	c = Color::tomato();
	c = Color::transparent();
	c = Color::turquoise();
	c = Color::violet();
	c = Color::wheat();
	c = Color::white();
	c = Color::whiteSmoke();
	c = Color::yellow();
	c = Color::yellowGreen();

}