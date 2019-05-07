#include "TestColor.h"
#include "core/Color.h"
#include "limits.h"

using namespace nb::core;
void TestColor::test()
{
	Color c1;
	Color c2(255, 0, 0);
	Color c3(125, 0, 255, 0);
	Color c4(c1);
	c4 = c3;
	Color c5 = Color::fromIntegerArgb(0xFF00AA77);
	c5 = Color::fromIntegerRgb(0x00aa88);
	Color c6 = Color::fromRgbF(0.3f, 0.5f, 1.000f);
	Color c7 = Color::fromArgbF(0.0f, 1.0f, 1.0f, 0.0f);

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

	c9.setIntegerArgb(0x44124366);
	unsigned int xx = c9.toIntegerArgb();

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

	Color c21 = Color(255, 150, 221);
	auto xxx = c21.toIntegerArgb();
	xxx = c21.toIntegerRgb();
	std::string s = c21.toString();

	return;
	uint64_t n = NB_GET_TICK_COUT;
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
	uint64_t nn = NB_GET_TICK_COUT - n;
	printf("%lld\n", nn);

	Color c = Colors::aliceBlue();
	c = Colors::antiqueWhite();
	c = Colors::aqua();
	c = Colors::aquamarine();
	c = Colors::azure();
	c = Colors::beige();
	c = Colors::bisque();
	c = Colors::black();
	c = Colors::blanchedAlmond();
	c = Colors::blue();
	c = Colors::blueViolet();
	c = Colors::brown();
	c = Colors::burlyWood();
	c = Colors::cadetBlue();
	c = Colors::chartreuse();
	c = Colors::chocolate();
	c = Colors::coral();
	c = Colors::cornflowerBlue();
	c = Colors::cornsilk();
	c = Colors::crimson();
	c = Colors::cyan();
	c = Colors::darkBlue();
	c = Colors::darkCyan();
	c = Colors::darkGoldenrod();
	c = Colors::darkGray();
	c = Colors::darkGreen();
	c = Colors::darkKhaki();
	c = Colors::darkMagenta();
	c = Colors::darkOliveGreen();
	c = Colors::darkOrange();
	c = Colors::darkOrchid();
	c = Colors::darkRed();
	c = Colors::darkSalmon();
	c = Colors::darkSeaGreen();
	c = Colors::darkSlateBlue();
	c = Colors::darkSlateGray();
	c = Colors::darkTurquoise();
	c = Colors::darkViolet();
	c = Colors::deepPink();
	c = Colors::deepSkyBlue();
	c = Colors::dimGray();
	c = Colors::dodgerBlue();
	c = Colors::firebrick();
	c = Colors::floralWhite();
	c = Colors::forestGreen();
	c = Colors::fuchsia();
	c = Colors::gainsboro();
	c = Colors::ghostWhite();
	c = Colors::gold();
	c = Colors::goldenrod();
	c = Colors::gray();
	c = Colors::green();
	c = Colors::greenYellow();
	c = Colors::honeydew();
	c = Colors::hotPink();
	c = Colors::indianRed();
	c = Colors::indigo();
	c = Colors::ivory();
	c = Colors::khaki();
	c = Colors::lavender();
	c = Colors::lavenderBlush();
	c = Colors::lawnGreen();
	c = Colors::lemonChiffon();
	c = Colors::lightBlue();
	c = Colors::lightCoral();
	c = Colors::lightCyan();
	c = Colors::lightGoldenrodYellow();
	c = Colors::lightGray();
	c = Colors::lightGreen();
	c = Colors::lightPink();
	c = Colors::lightSalmon();
	c = Colors::lightSeaGreen();
	c = Colors::lightSkyBlue();
	c = Colors::lightSlateGray();
	c = Colors::lightSteelBlue();
	c = Colors::lightYellow();
	c = Colors::lime();
	c = Colors::limeGreen();
	c = Colors::linen();
	c = Colors::magenta();
	c = Colors::maroon();
	c = Colors::mediumAquamarine();
	c = Colors::mediumBlue();
	c = Colors::mediumOrchid();
	c = Colors::mediumPurple();
	c = Colors::mediumSeaGreen();
	c = Colors::mediumSlateBlue();
	c = Colors::mediumSpringGreen();
	c = Colors::mediumTurquoise();
	c = Colors::mediumVioletRed();
	c = Colors::midnightBlue();
	c = Colors::mintCream();
	c = Colors::mistyRose();
	c = Colors::moccasin();
	c = Colors::navajoWhite();
	c = Colors::navy();
	c = Colors::oldLace();
	c = Colors::olive();
	c = Colors::oliveDrab();
	c = Colors::orange();
	c = Colors::orangeRed();
	c = Colors::orchid();
	c = Colors::paleGoldenrod();
	c = Colors::paleGreen();
	c = Colors::paleTurquoise();
	c = Colors::paleVioletRed();
	c = Colors::papayaWhip();
	c = Colors::peachPuff();
	c = Colors::peru();
	c = Colors::pink();
	c = Colors::plum();
	c = Colors::powderBlue();
	c = Colors::purple();
	c = Colors::red();
	c = Colors::rosyBrown();
	c = Colors::royalBlue();
	c = Colors::saddleBrown();
	c = Colors::salmon();
	c = Colors::sandyBrown();
	c = Colors::seaGreen();
	c = Colors::seaShell();
	c = Colors::sienna();
	c = Colors::silver();
	c = Colors::skyBlue();
	c = Colors::slateBlue();
	c = Colors::slateGray();
	c = Colors::snow();
	c = Colors::springGreen();
	c = Colors::steelBlue();
	c = Colors::tan();
	c = Colors::teal();
	c = Colors::thistle();
	c = Colors::tomato();
	c = Colors::transparent();
	c = Colors::turquoise();
	c = Colors::violet();
	c = Colors::wheat();
	c = Colors::white();
	c = Colors::whiteSmoke();
	c = Colors::yellow();
	c = Colors::yellowGreen();

}