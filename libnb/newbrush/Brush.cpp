#include "newbrush/Brush.h"

using namespace nb;

Brush::Brush()
	: opacity(1.0f)
{}

SolidColorBrush::SolidColorBrush()
	: SolidColorBrush(Color())
{}

SolidColorBrush::SolidColorBrush(const Color &_color)
	: color(_color)
{}

#define RETURN_SOLIDCOLOR_RGB(r, g, b) \
static auto x = createRef<SolidColorBrush>(Color(r, g, b));\
return x;

#define RETURN_SOLIDCOLOR_RGBA(r, g, b, a)\
static auto x = createRef<SolidColorBrush>(Color(r, g, b, a));\
return x;

ref<SolidColorBrush> SolidColorBrush::aliceBlue()
{
	RETURN_SOLIDCOLOR_RGB(240, 248, 255);
}

ref<SolidColorBrush> SolidColorBrush::antiqueWhite()
{
	RETURN_SOLIDCOLOR_RGB(250, 235, 215);
}

ref<SolidColorBrush> SolidColorBrush::aqua()
{
	RETURN_SOLIDCOLOR_RGB(0, 255, 255);
}

ref<SolidColorBrush> SolidColorBrush::aquamarine()
{
	RETURN_SOLIDCOLOR_RGB(127, 255, 212);
}

ref<SolidColorBrush> SolidColorBrush::azure()
{
	RETURN_SOLIDCOLOR_RGB(240, 255, 255);
}

ref<SolidColorBrush> SolidColorBrush::beige()
{
	RETURN_SOLIDCOLOR_RGB(245, 245, 220);
}

ref<SolidColorBrush> SolidColorBrush::bisque()
{
	RETURN_SOLIDCOLOR_RGB(255, 228, 196);
}

ref<SolidColorBrush> SolidColorBrush::black()
{
	RETURN_SOLIDCOLOR_RGB(0, 0, 0);
}

ref<SolidColorBrush> SolidColorBrush::blanchedAlmond()
{
	RETURN_SOLIDCOLOR_RGB(255, 255, 205);
}

ref<SolidColorBrush> SolidColorBrush::blue()
{
	RETURN_SOLIDCOLOR_RGB(0, 0, 255);
}

ref<SolidColorBrush> SolidColorBrush::blueViolet()
{
	RETURN_SOLIDCOLOR_RGB(138, 43, 226);
}

ref<SolidColorBrush> SolidColorBrush::brown()
{
	RETURN_SOLIDCOLOR_RGB(165, 42, 42);
}

ref<SolidColorBrush> SolidColorBrush::burlyWood()
{
	RETURN_SOLIDCOLOR_RGB(222, 184, 135);
}

ref<SolidColorBrush> SolidColorBrush::cadetBlue()
{
	RETURN_SOLIDCOLOR_RGB(95, 158, 160);
}

ref<SolidColorBrush> SolidColorBrush::chartreuse()
{
	RETURN_SOLIDCOLOR_RGB(127, 255, 0);
}

ref<SolidColorBrush> SolidColorBrush::chocolate()
{
	RETURN_SOLIDCOLOR_RGB(210, 105, 30);
}

ref<SolidColorBrush> SolidColorBrush::coral()
{
	RETURN_SOLIDCOLOR_RGB(255, 127, 80);
}

ref<SolidColorBrush> SolidColorBrush::cornflowerBlue()
{
	RETURN_SOLIDCOLOR_RGB(100, 149, 237);
}

ref<SolidColorBrush> SolidColorBrush::cornsilk()
{
	RETURN_SOLIDCOLOR_RGB(255, 248, 220);
}

ref<SolidColorBrush> SolidColorBrush::crimson()
{
	RETURN_SOLIDCOLOR_RGB(220, 20, 60);
}

ref<SolidColorBrush> SolidColorBrush::cyan()
{
	RETURN_SOLIDCOLOR_RGB(0, 255, 255);
}

ref<SolidColorBrush> SolidColorBrush::darkBlue()
{
	RETURN_SOLIDCOLOR_RGB(0, 0, 139);
}

ref<SolidColorBrush> SolidColorBrush::darkCyan()
{
	RETURN_SOLIDCOLOR_RGB(0, 139, 139);
}

ref<SolidColorBrush> SolidColorBrush::darkGoldenrod()
{
	RETURN_SOLIDCOLOR_RGB(184, 134, 11);
}

ref<SolidColorBrush> SolidColorBrush::darkGray()
{
	RETURN_SOLIDCOLOR_RGB(169, 169, 169);
}

ref<SolidColorBrush> SolidColorBrush::darkGreen()
{
	RETURN_SOLIDCOLOR_RGB(0, 100, 0);
}

ref<SolidColorBrush> SolidColorBrush::darkKhaki()
{
	RETURN_SOLIDCOLOR_RGB(189, 183, 107);
}

ref<SolidColorBrush> SolidColorBrush::darkMagenta()
{
	RETURN_SOLIDCOLOR_RGB(139, 0, 139);
}

ref<SolidColorBrush> SolidColorBrush::darkOliveGreen()
{
	RETURN_SOLIDCOLOR_RGB(85, 107, 47);
}

ref<SolidColorBrush> SolidColorBrush::darkOrange()
{
	RETURN_SOLIDCOLOR_RGB(255, 140, 0);
}

ref<SolidColorBrush> SolidColorBrush::darkOrchid()
{
	RETURN_SOLIDCOLOR_RGB(153, 50, 204);
}

ref<SolidColorBrush> SolidColorBrush::darkRed()
{
	RETURN_SOLIDCOLOR_RGB(139, 0, 0);
}

ref<SolidColorBrush> SolidColorBrush::darkSalmon()
{
	RETURN_SOLIDCOLOR_RGB(233, 150, 122);
}

ref<SolidColorBrush> SolidColorBrush::darkSeaGreen()
{
	RETURN_SOLIDCOLOR_RGB(143, 188, 143);
}

ref<SolidColorBrush> SolidColorBrush::darkSlateBlue()
{
	RETURN_SOLIDCOLOR_RGB(72, 61, 139);
}

ref<SolidColorBrush> SolidColorBrush::darkSlateGray()
{
	RETURN_SOLIDCOLOR_RGB(40, 79, 79);
}

ref<SolidColorBrush> SolidColorBrush::darkTurquoise()
{
	RETURN_SOLIDCOLOR_RGB(0, 206, 209);
}

ref<SolidColorBrush> SolidColorBrush::darkViolet()
{
	RETURN_SOLIDCOLOR_RGB(148, 0, 211);
}

ref<SolidColorBrush> SolidColorBrush::deepPink()
{
	RETURN_SOLIDCOLOR_RGB(255, 20, 147);
}

ref<SolidColorBrush> SolidColorBrush::deepSkyBlue()
{
	RETURN_SOLIDCOLOR_RGB(0, 191, 255);
}

ref<SolidColorBrush> SolidColorBrush::dimGray()
{
	RETURN_SOLIDCOLOR_RGB(105, 105, 105);
}

ref<SolidColorBrush> SolidColorBrush::dodgerBlue()
{
	RETURN_SOLIDCOLOR_RGB(30, 144, 255);
}

ref<SolidColorBrush> SolidColorBrush::firebrick()
{
	RETURN_SOLIDCOLOR_RGB(178, 34, 34);
}

ref<SolidColorBrush> SolidColorBrush::floralWhite()
{
	RETURN_SOLIDCOLOR_RGB(255, 250, 240);
}

ref<SolidColorBrush> SolidColorBrush::forestGreen()
{
	RETURN_SOLIDCOLOR_RGB(34, 139, 34);
}

ref<SolidColorBrush> SolidColorBrush::fuchsia()
{
	RETURN_SOLIDCOLOR_RGB(255, 0, 255);
}

ref<SolidColorBrush> SolidColorBrush::gainsboro()
{
	RETURN_SOLIDCOLOR_RGB(220, 220, 220);
}

ref<SolidColorBrush> SolidColorBrush::ghostWhite()
{
	RETURN_SOLIDCOLOR_RGB(248, 248, 255);
}

ref<SolidColorBrush> SolidColorBrush::gold()
{
	RETURN_SOLIDCOLOR_RGB(255, 215, 0);
}

ref<SolidColorBrush> SolidColorBrush::goldenrod()
{
	RETURN_SOLIDCOLOR_RGB(218, 165, 32);
}

ref<SolidColorBrush> SolidColorBrush::gray()
{
	RETURN_SOLIDCOLOR_RGB(128, 128, 128);
}

ref<SolidColorBrush> SolidColorBrush::green()
{
	RETURN_SOLIDCOLOR_RGB(0, 128, 0);
}

ref<SolidColorBrush> SolidColorBrush::greenYellow()
{
	RETURN_SOLIDCOLOR_RGB(173, 255, 47);
}

ref<SolidColorBrush> SolidColorBrush::honeydew()
{
	RETURN_SOLIDCOLOR_RGB(240, 255, 240);
}

ref<SolidColorBrush> SolidColorBrush::hotPink()
{
	RETURN_SOLIDCOLOR_RGB(255, 105, 180);
}

ref<SolidColorBrush> SolidColorBrush::indianRed()
{
	RETURN_SOLIDCOLOR_RGB(205, 92, 92);
}

ref<SolidColorBrush> SolidColorBrush::indigo()
{
	RETURN_SOLIDCOLOR_RGB(75, 0, 130);
}

ref<SolidColorBrush> SolidColorBrush::ivory()
{
	RETURN_SOLIDCOLOR_RGB(255, 240, 240);
}

ref<SolidColorBrush> SolidColorBrush::khaki()
{
	RETURN_SOLIDCOLOR_RGB(240, 230, 140);
}

ref<SolidColorBrush> SolidColorBrush::lavender()
{
	RETURN_SOLIDCOLOR_RGB(230, 230, 250);
}

ref<SolidColorBrush> SolidColorBrush::lavenderBlush()
{
	RETURN_SOLIDCOLOR_RGB(255, 240, 245);
}

ref<SolidColorBrush> SolidColorBrush::lawnGreen()
{
	RETURN_SOLIDCOLOR_RGB(124, 252, 0);
}

ref<SolidColorBrush> SolidColorBrush::lemonChiffon()
{
	RETURN_SOLIDCOLOR_RGB(255, 250, 205);
}

ref<SolidColorBrush> SolidColorBrush::lightBlue()
{
	RETURN_SOLIDCOLOR_RGB(173, 216, 230);
}

ref<SolidColorBrush> SolidColorBrush::lightCoral()
{
	RETURN_SOLIDCOLOR_RGB(240, 128, 128);
}

ref<SolidColorBrush> SolidColorBrush::lightCyan()
{
	RETURN_SOLIDCOLOR_RGB(224, 255, 255);
}

ref<SolidColorBrush> SolidColorBrush::lightGoldenrodYellow()
{
	RETURN_SOLIDCOLOR_RGB(250, 250, 210);
}

ref<SolidColorBrush> SolidColorBrush::lightGray()
{
	RETURN_SOLIDCOLOR_RGB(211, 211, 211);
}

ref<SolidColorBrush> SolidColorBrush::lightGreen()
{
	RETURN_SOLIDCOLOR_RGB(144, 238, 144);
}

ref<SolidColorBrush> SolidColorBrush::lightPink()
{
	RETURN_SOLIDCOLOR_RGB(255, 182, 193);
}

ref<SolidColorBrush> SolidColorBrush::lightSalmon()
{
	RETURN_SOLIDCOLOR_RGB(255, 160, 122);
}

ref<SolidColorBrush> SolidColorBrush::lightSeaGreen()
{
	RETURN_SOLIDCOLOR_RGB(32, 178, 170);
}

ref<SolidColorBrush> SolidColorBrush::lightSkyBlue()
{
	RETURN_SOLIDCOLOR_RGB(135, 206, 250);
}

ref<SolidColorBrush> SolidColorBrush::lightSlateGray()
{
	RETURN_SOLIDCOLOR_RGB(119, 136, 153);
}

ref<SolidColorBrush> SolidColorBrush::lightSteelBlue()
{
	RETURN_SOLIDCOLOR_RGB(176, 196, 222);
}

ref<SolidColorBrush> SolidColorBrush::lightYellow()
{
	RETURN_SOLIDCOLOR_RGB(255, 255, 224);
}

ref<SolidColorBrush> SolidColorBrush::lime()
{
	RETURN_SOLIDCOLOR_RGB(0, 255, 0);
}

ref<SolidColorBrush> SolidColorBrush::limeGreen()
{
	RETURN_SOLIDCOLOR_RGB(50, 205, 50);
}

ref<SolidColorBrush> SolidColorBrush::linen()
{
	RETURN_SOLIDCOLOR_RGB(250, 240, 230);
}

ref<SolidColorBrush> SolidColorBrush::magenta()
{
	RETURN_SOLIDCOLOR_RGB(255, 0, 255);
}

ref<SolidColorBrush> SolidColorBrush::maroon()
{
	RETURN_SOLIDCOLOR_RGB(128, 0, 0);
}

ref<SolidColorBrush> SolidColorBrush::mediumAquamarine()
{
	RETURN_SOLIDCOLOR_RGB(102, 205, 170);
}

ref<SolidColorBrush> SolidColorBrush::mediumBlue()
{
	RETURN_SOLIDCOLOR_RGB(0, 0, 205);
}

ref<SolidColorBrush> SolidColorBrush::mediumOrchid()
{
	RETURN_SOLIDCOLOR_RGB(186, 85, 211);
}

ref<SolidColorBrush> SolidColorBrush::mediumPurple()
{
	RETURN_SOLIDCOLOR_RGB(147, 112, 219);
}

ref<SolidColorBrush> SolidColorBrush::mediumSeaGreen()
{
	RETURN_SOLIDCOLOR_RGB(60, 179, 113);
}

ref<SolidColorBrush> SolidColorBrush::mediumSlateBlue()
{
	RETURN_SOLIDCOLOR_RGB(123, 104, 238);
}

ref<SolidColorBrush> SolidColorBrush::mediumSpringGreen()
{
	RETURN_SOLIDCOLOR_RGB(0, 250, 154);
}

ref<SolidColorBrush> SolidColorBrush::mediumTurquoise()
{
	RETURN_SOLIDCOLOR_RGB(72, 209, 204);
}

ref<SolidColorBrush> SolidColorBrush::mediumVioletRed()
{
	RETURN_SOLIDCOLOR_RGB(199, 21, 112);
}

ref<SolidColorBrush> SolidColorBrush::midnightBlue()
{
	RETURN_SOLIDCOLOR_RGB(25, 25, 112);
}

ref<SolidColorBrush> SolidColorBrush::mintCream()
{
	RETURN_SOLIDCOLOR_RGB(245, 255, 250);
}

ref<SolidColorBrush> SolidColorBrush::mistyRose()
{
	RETURN_SOLIDCOLOR_RGB(255, 228, 225);
}

ref<SolidColorBrush> SolidColorBrush::moccasin()
{
	RETURN_SOLIDCOLOR_RGB(255, 228, 181);
}

ref<SolidColorBrush> SolidColorBrush::navajoWhite()
{
	RETURN_SOLIDCOLOR_RGB(255, 222, 173);
}

ref<SolidColorBrush> SolidColorBrush::navy()
{
	RETURN_SOLIDCOLOR_RGB(0, 0, 128);
}

ref<SolidColorBrush> SolidColorBrush::oldLace()
{
	RETURN_SOLIDCOLOR_RGB(253, 245, 230);
}

ref<SolidColorBrush> SolidColorBrush::olive()
{
	RETURN_SOLIDCOLOR_RGB(128, 128, 0);
}

ref<SolidColorBrush> SolidColorBrush::oliveDrab()
{
	RETURN_SOLIDCOLOR_RGB(107, 142, 45);
}

ref<SolidColorBrush> SolidColorBrush::orange()
{
	RETURN_SOLIDCOLOR_RGB(255, 165, 0);
}

ref<SolidColorBrush> SolidColorBrush::orangeRed()
{
	RETURN_SOLIDCOLOR_RGB(255, 69, 0);
}

ref<SolidColorBrush> SolidColorBrush::orchid()
{
	RETURN_SOLIDCOLOR_RGB(218, 112, 214);
}

ref<SolidColorBrush> SolidColorBrush::paleGoldenrod()
{
	RETURN_SOLIDCOLOR_RGB(238, 232, 170);
}

ref<SolidColorBrush> SolidColorBrush::paleGreen()
{
	RETURN_SOLIDCOLOR_RGB(152, 251, 152);
}

ref<SolidColorBrush> SolidColorBrush::paleTurquoise()
{
	RETURN_SOLIDCOLOR_RGB(175, 238, 238);
}

ref<SolidColorBrush> SolidColorBrush::paleVioletRed()
{
	RETURN_SOLIDCOLOR_RGB(219, 112, 147);
}

ref<SolidColorBrush> SolidColorBrush::papayaWhip()
{
	RETURN_SOLIDCOLOR_RGB(255, 239, 213);
}

ref<SolidColorBrush> SolidColorBrush::peachPuff()
{
	RETURN_SOLIDCOLOR_RGB(255, 218, 155);
}

ref<SolidColorBrush> SolidColorBrush::peru()
{
	RETURN_SOLIDCOLOR_RGB(205, 133, 63);
}

ref<SolidColorBrush> SolidColorBrush::pink()
{
	RETURN_SOLIDCOLOR_RGB(255, 192, 203);
}

ref<SolidColorBrush> SolidColorBrush::plum()
{
	RETURN_SOLIDCOLOR_RGB(221, 160, 221);
}

ref<SolidColorBrush> SolidColorBrush::powderBlue()
{
	RETURN_SOLIDCOLOR_RGB(176, 224, 230);
}

ref<SolidColorBrush> SolidColorBrush::purple()
{
	RETURN_SOLIDCOLOR_RGB(128, 0, 128);
}

ref<SolidColorBrush> SolidColorBrush::red()
{
	RETURN_SOLIDCOLOR_RGB(255, 0, 0);
}

ref<SolidColorBrush> SolidColorBrush::rosyBrown()
{
	RETURN_SOLIDCOLOR_RGB(188, 143, 143);
}

ref<SolidColorBrush> SolidColorBrush::royalBlue()
{
	RETURN_SOLIDCOLOR_RGB(65, 105, 225);
}

ref<SolidColorBrush> SolidColorBrush::saddleBrown()
{
	RETURN_SOLIDCOLOR_RGB(139, 69, 19);
}

ref<SolidColorBrush> SolidColorBrush::salmon()
{
	RETURN_SOLIDCOLOR_RGB(250, 128, 114);
}

ref<SolidColorBrush> SolidColorBrush::sandyBrown()
{
	RETURN_SOLIDCOLOR_RGB(244, 164, 96);
}

ref<SolidColorBrush> SolidColorBrush::seaGreen()
{
	RETURN_SOLIDCOLOR_RGB(46, 139, 87);
}

ref<SolidColorBrush> SolidColorBrush::seaShell()
{
	RETURN_SOLIDCOLOR_RGB(255, 245, 238);
}

ref<SolidColorBrush> SolidColorBrush::sienna()
{
	RETURN_SOLIDCOLOR_RGB(160, 82, 45);
}

ref<SolidColorBrush> SolidColorBrush::silver()
{
	RETURN_SOLIDCOLOR_RGB(192, 192, 192);
}

ref<SolidColorBrush> SolidColorBrush::skyBlue()
{
	RETURN_SOLIDCOLOR_RGB(135, 206, 235);
}

ref<SolidColorBrush> SolidColorBrush::slateBlue()
{
	RETURN_SOLIDCOLOR_RGB(106, 90, 205);
}

ref<SolidColorBrush> SolidColorBrush::slateGray()
{
	RETURN_SOLIDCOLOR_RGB(112, 128, 144);
}

ref<SolidColorBrush> SolidColorBrush::snow()
{
	RETURN_SOLIDCOLOR_RGB(255, 250, 250);
}

ref<SolidColorBrush> SolidColorBrush::springGreen()
{
	RETURN_SOLIDCOLOR_RGB(0, 255, 127);
}

ref<SolidColorBrush> SolidColorBrush::steelBlue()
{
	RETURN_SOLIDCOLOR_RGB(70, 130, 180);
}

ref<SolidColorBrush> SolidColorBrush::tan()
{
	RETURN_SOLIDCOLOR_RGB(210, 180, 140);
}

ref<SolidColorBrush> SolidColorBrush::teal()
{
	RETURN_SOLIDCOLOR_RGB(0, 128, 128);
}

ref<SolidColorBrush> SolidColorBrush::thistle()
{
	RETURN_SOLIDCOLOR_RGB(216, 191, 216);
}

ref<SolidColorBrush> SolidColorBrush::tomato()
{
	RETURN_SOLIDCOLOR_RGB(253, 99, 71);
}

ref<SolidColorBrush> SolidColorBrush::transparent()
{
	RETURN_SOLIDCOLOR_RGBA(255, 255, 255, 0);
}

ref<SolidColorBrush> SolidColorBrush::turquoise()
{
	RETURN_SOLIDCOLOR_RGB(64, 224, 208);
}

ref<SolidColorBrush> SolidColorBrush::violet()
{
	RETURN_SOLIDCOLOR_RGB(238, 130, 238);
}

ref<SolidColorBrush> SolidColorBrush::wheat()
{
	RETURN_SOLIDCOLOR_RGB(245, 222, 179);
}

ref<SolidColorBrush> SolidColorBrush::white()
{
	RETURN_SOLIDCOLOR_RGB(255, 255, 255);
}

ref<SolidColorBrush> SolidColorBrush::whiteSmoke()
{
	RETURN_SOLIDCOLOR_RGB(245, 245, 245);
}

ref<SolidColorBrush> SolidColorBrush::yellow()
{
	RETURN_SOLIDCOLOR_RGB(255, 255, 0);
}

ref<SolidColorBrush> SolidColorBrush::yellowGreen()
{
	RETURN_SOLIDCOLOR_RGB(154, 205, 50);
}

LinearGradientBrush::LinearGradientBrush()
	: LinearGradientBrush(std::vector<GradientStop>{})
{}

LinearGradientBrush::LinearGradientBrush(const std::vector<GradientStop> &stops)
	: gradientStops(stops)
	, horizontal(true)
{}

ImageBrush::ImageBrush()
{}

ImageBrush::ImageBrush(const std::string &path)
	: ImageBrush(createRef<Texture2D>(path))
{}

ImageBrush::ImageBrush(ref<Texture2D> texture)
	: frame(texture)
{}

ImageBrush::ImageBrush(const TextureFrame & _frame)
	: frame(_frame)
{}

ImageBrush::ImageBrush(const std::string & texAtlasKey, const std::string & frameName)
	: frame(TextureLibrary::getFrameFromTextureAtlas(texAtlasKey, frameName))
{}

EffectBrush::EffectBrush()
	: EffectBrush(nullptr, nullptr)
{
}

EffectBrush::EffectBrush(ref<Material> _material, ref<Light> _light)
	: material(_material)
	, light(_light)
{
}

static std::map<std::string, ref<Brush>> g_brushes;
bool BrushLibrary::add(const std::string & name, ref<Brush> brush)
{
	auto ret = g_brushes.insert({ name, brush });
	return ret.second;
}

bool BrushLibrary::addSolidColorBrush(const std::string & name, const Color & color)
{
	return add(name, createRef<SolidColorBrush>(color));
}

bool BrushLibrary::addImageBrush(const std::string & name, const std::string & imagePath)
{
	return add(name, createRef<ImageBrush>(createRef<Texture2D>(imagePath)));
}

bool BrushLibrary::addImageBrushFromTextureAtlas(const std::string &name, const std::string &texAtlasKey, const std::string &frameName)
{
	return add(name, createRef<ImageBrush>(texAtlasKey, frameName));
}

ref<Brush> BrushLibrary::get(const std::string & name)
{
	auto iter = g_brushes.find(name);
	return iter == g_brushes.end() ? nullptr : iter->second;
}
