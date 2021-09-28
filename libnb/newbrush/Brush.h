#pragma once
#include "newbrush/Components.h"

namespace nb
{

class NB_API Brush : public Object
{
	RTTR_ENABLE(Object)
public:
	virtual ~Brush() = default;

	float opacity;

protected:
	Brush();
};

class NB_API SolidColorBrush : public Brush
{
	RTTR_ENABLE(Brush)
public:
	SolidColorBrush();
	SolidColorBrush(const Color &_color);
	
	Color color;

public:
	static ref<SolidColorBrush> aliceBlue();
	static ref<SolidColorBrush> antiqueWhite();
	static ref<SolidColorBrush> aqua();
	static ref<SolidColorBrush> aquamarine();
	static ref<SolidColorBrush> azure();
	static ref<SolidColorBrush> beige();
	static ref<SolidColorBrush> bisque();
	static ref<SolidColorBrush> black();
	static ref<SolidColorBrush> blanchedAlmond();
	static ref<SolidColorBrush> blue();
	static ref<SolidColorBrush> blueViolet();
	static ref<SolidColorBrush> brown();
	static ref<SolidColorBrush> burlyWood();
	static ref<SolidColorBrush> cadetBlue();
	static ref<SolidColorBrush> chartreuse();
	static ref<SolidColorBrush> chocolate();
	static ref<SolidColorBrush> coral();
	static ref<SolidColorBrush> cornflowerBlue();
	static ref<SolidColorBrush> cornsilk();
	static ref<SolidColorBrush> crimson();
	static ref<SolidColorBrush> cyan();
	static ref<SolidColorBrush> darkBlue();
	static ref<SolidColorBrush> darkCyan();
	static ref<SolidColorBrush> darkGoldenrod();
	static ref<SolidColorBrush> darkGray();
	static ref<SolidColorBrush> darkGreen();
	static ref<SolidColorBrush> darkKhaki();
	static ref<SolidColorBrush> darkMagenta();
	static ref<SolidColorBrush> darkOliveGreen();
	static ref<SolidColorBrush> darkOrange();
	static ref<SolidColorBrush> darkOrchid();
	static ref<SolidColorBrush> darkRed();
	static ref<SolidColorBrush> darkSalmon();
	static ref<SolidColorBrush> darkSeaGreen();
	static ref<SolidColorBrush> darkSlateBlue();
	static ref<SolidColorBrush> darkSlateGray();
	static ref<SolidColorBrush> darkTurquoise();
	static ref<SolidColorBrush> darkViolet();
	static ref<SolidColorBrush> deepPink();
	static ref<SolidColorBrush> deepSkyBlue();
	static ref<SolidColorBrush> dimGray();
	static ref<SolidColorBrush> dodgerBlue();
	static ref<SolidColorBrush> firebrick();
	static ref<SolidColorBrush> floralWhite();
	static ref<SolidColorBrush> forestGreen();
	static ref<SolidColorBrush> fuchsia();
	static ref<SolidColorBrush> gainsboro();
	static ref<SolidColorBrush> ghostWhite();
	static ref<SolidColorBrush> gold();
	static ref<SolidColorBrush> goldenrod();
	static ref<SolidColorBrush> gray();
	static ref<SolidColorBrush> green();
	static ref<SolidColorBrush> greenYellow();
	static ref<SolidColorBrush> honeydew();
	static ref<SolidColorBrush> hotPink();
	static ref<SolidColorBrush> indianRed();
	static ref<SolidColorBrush> indigo();
	static ref<SolidColorBrush> ivory();
	static ref<SolidColorBrush> khaki();
	static ref<SolidColorBrush> lavender();
	static ref<SolidColorBrush> lavenderBlush();
	static ref<SolidColorBrush> lawnGreen();
	static ref<SolidColorBrush> lemonChiffon();
	static ref<SolidColorBrush> lightBlue();
	static ref<SolidColorBrush> lightCoral();
	static ref<SolidColorBrush> lightCyan();
	static ref<SolidColorBrush> lightGoldenrodYellow();
	static ref<SolidColorBrush> lightGray();
	static ref<SolidColorBrush> lightGreen();
	static ref<SolidColorBrush> lightPink();
	static ref<SolidColorBrush> lightSalmon();
	static ref<SolidColorBrush> lightSeaGreen();
	static ref<SolidColorBrush> lightSkyBlue();
	static ref<SolidColorBrush> lightSlateGray();
	static ref<SolidColorBrush> lightSteelBlue();
	static ref<SolidColorBrush> lightYellow();
	static ref<SolidColorBrush> lime();
	static ref<SolidColorBrush> limeGreen();
	static ref<SolidColorBrush> linen();
	static ref<SolidColorBrush> magenta();
	static ref<SolidColorBrush> maroon();
	static ref<SolidColorBrush> mediumAquamarine();
	static ref<SolidColorBrush> mediumBlue();
	static ref<SolidColorBrush> mediumOrchid();
	static ref<SolidColorBrush> mediumPurple();
	static ref<SolidColorBrush> mediumSeaGreen();
	static ref<SolidColorBrush> mediumSlateBlue();
	static ref<SolidColorBrush> mediumSpringGreen();
	static ref<SolidColorBrush> mediumTurquoise();
	static ref<SolidColorBrush> mediumVioletRed();
	static ref<SolidColorBrush> midnightBlue();
	static ref<SolidColorBrush> mintCream();
	static ref<SolidColorBrush> mistyRose();
	static ref<SolidColorBrush> moccasin();
	static ref<SolidColorBrush> navajoWhite();
	static ref<SolidColorBrush> navy();
	static ref<SolidColorBrush> oldLace();
	static ref<SolidColorBrush> olive();
	static ref<SolidColorBrush> oliveDrab();
	static ref<SolidColorBrush> orange();
	static ref<SolidColorBrush> orangeRed();
	static ref<SolidColorBrush> orchid();
	static ref<SolidColorBrush> paleGoldenrod();
	static ref<SolidColorBrush> paleGreen();
	static ref<SolidColorBrush> paleTurquoise();
	static ref<SolidColorBrush> paleVioletRed();
	static ref<SolidColorBrush> papayaWhip();
	static ref<SolidColorBrush> peachPuff();
	static ref<SolidColorBrush> peru();
	static ref<SolidColorBrush> pink();
	static ref<SolidColorBrush> plum();
	static ref<SolidColorBrush> powderBlue();
	static ref<SolidColorBrush> purple();
	static ref<SolidColorBrush> red();
	static ref<SolidColorBrush> rosyBrown();
	static ref<SolidColorBrush> royalBlue();
	static ref<SolidColorBrush> saddleBrown();
	static ref<SolidColorBrush> salmon();
	static ref<SolidColorBrush> sandyBrown();
	static ref<SolidColorBrush> seaGreen();
	static ref<SolidColorBrush> seaShell();
	static ref<SolidColorBrush> sienna();
	static ref<SolidColorBrush> silver();
	static ref<SolidColorBrush> skyBlue();
	static ref<SolidColorBrush> slateBlue();
	static ref<SolidColorBrush> slateGray();
	static ref<SolidColorBrush> snow();
	static ref<SolidColorBrush> springGreen();
	static ref<SolidColorBrush> steelBlue();
	static ref<SolidColorBrush> tan();
	static ref<SolidColorBrush> teal();
	static ref<SolidColorBrush> thistle();
	static ref<SolidColorBrush> tomato();
	static ref<SolidColorBrush> transparent();
	static ref<SolidColorBrush> turquoise();
	static ref<SolidColorBrush> violet();
	static ref<SolidColorBrush> wheat();
	static ref<SolidColorBrush> white();
	static ref<SolidColorBrush> whiteSmoke();
	static ref<SolidColorBrush> yellow();
	static ref<SolidColorBrush> yellowGreen();
};

class NB_API LinearGradientBrush : public Brush
{
public:
	LinearGradientBrush();
	LinearGradientBrush(const std::vector<GradientStop> &stops);

	bool horizontal;
	std::vector<GradientStop> gradientStops;
};

class NB_API ImageBrush : public Brush
{
	RTTR_ENABLE(Brush)
public:
	ImageBrush();
	ImageBrush(const std::string &path);
	ImageBrush(ref<Texture2D> texture);
	ImageBrush(const TextureFrame &frame);
	ImageBrush(const std::string &texAtlasKey, const std::string &frameName);

	TextureFrame frame;
};

class NB_API EffectBrush : public Brush
{
	RTTR_ENABLE(Brush)
public:
	EffectBrush();
	EffectBrush(ref<Material> material, ref<Light> light = nullptr);

	ref<Material> material;
	ref<Light> light;
};

class NB_API BrushLibrary
{
public:
	static bool add(const std::string &name, ref<Brush> brush);
	static bool addSolidColorBrush(const std::string &name, const Color &color);
	static bool addImageBrush(const std::string &name, const std::string &imagePath);
	static bool addImageBrushFromTextureAtlas(const std::string &name, const std::string &texAtlasKey, const std::string &frameName);
	static ref<Brush> get(const std::string &name);
};

#define SCBR(color)						createRef<SolidColorBrush>(color)
#define IMGBR(texAtlasKey, frameName)	createRef<ImageBrush>(texAtlasKey, frameName)

}