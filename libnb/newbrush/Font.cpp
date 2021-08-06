#include "newbrush/Font.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_truetype.h"
#include "stb/stb_image_write.h"

using namespace nb;

//https://www.zhihu.com/search?type=content&q=stb_truetype
//https://blog.csdn.net/finewind/article/details/38009731

//int func()
//{
//	/* 加载字体（.ttf）文件 */
//	long int size = 0;
//	unsigned char *fontBuffer = NULL;
//
//	FILE *fontFile = fopen("../resource/fonts/siyuanheiti.otf", "rb");
//	if (fontFile == NULL)
//	{
//		printf("Can not open font file!\n");
//		return 0;
//	}
//	fseek(fontFile, 0, SEEK_END); /* 设置文件指针到文件尾，基于文件尾偏移0字节 */
//	size = ftell(fontFile);       /* 获取文件大小（文件尾 - 文件头  单位：字节） */
//	fseek(fontFile, 0, SEEK_SET); /* 重新设置文件指针到文件头 */
//
//	fontBuffer = (unsigned char*)calloc(size, sizeof(unsigned char));
//	fread(fontBuffer, size, 1, fontFile);
//	fclose(fontFile);
//
//	/* 初始化字体 */
//	stbtt_fontinfo info;
//	if (!stbtt_InitFont(&info, fontBuffer, 0))
//	{
//		printf("stb init font failed\n");
//	}
//
//	/* 创建位图 */
//	int bitmap_w = 512; /* 位图的宽 */
//	int bitmap_h = 128; /* 位图的高 */
//	unsigned char *bitmap = (unsigned char*)calloc(bitmap_w * bitmap_h, sizeof(unsigned char));
//
//	/* "STB"的 unicode 编码 */
//	char word[20] = { 'O', 'p', 'e', 'n', 'G', 'L' };
//
//	/* 计算字体缩放 */
//	float pixels = 64.0;                                    /* 字体大小（字号） */
//	float scale = stbtt_ScaleForPixelHeight(&info, pixels); /* scale = pixels / (ascent - descent) */
//
//															/**
//															* 获取垂直方向上的度量
//															* ascent：字体从基线到顶部的高度；
//															* descent：基线到底部的高度，通常为负值；
//															* lineGap：两个字体之间的间距；
//															* 行间距为：ascent - descent + lineGap。
//															*/
//	int ascent = 0;
//	int descent = 0;
//	int lineGap = 0;
//	stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);
//
//	/* 根据缩放调整字高 */
//	ascent = roundf(ascent * scale);
//	descent = roundf(descent * scale);
//
//	int x = 0; /*位图的x*/
//
//			   /* 循环加载word中每个字符 */
//	for (int i = 0; i < strlen(word); ++i)
//	{
//		/**
//		* 获取水平方向上的度量
//		* advanceWidth：字宽；
//		* leftSideBearing：左侧位置；
//		*/
//		int advanceWidth = 0;
//		int leftSideBearing = 0;
//		stbtt_GetCodepointHMetrics(&info, word[i], &advanceWidth, &leftSideBearing);
//
//		/* 获取字符的边框（边界） */
//		int c_x1, c_y1, c_x2, c_y2;
//		stbtt_GetCodepointBitmapBox(&info, word[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);
//
//		/* 计算位图的y (不同字符的高度不同） */
//		int y = ascent + c_y1;
//
//		/* 渲染字符 */
//		int byteOffset = x + roundf(leftSideBearing * scale) + (y * bitmap_w);
//		stbtt_MakeCodepointBitmap(&info, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, bitmap_w, scale, scale, word[i]);
//
//		/* 调整x */
//		x += roundf(advanceWidth * scale);
//
//		/* 调整字距 */
//		int kern;
//		kern = stbtt_GetCodepointKernAdvance(&info, word[i], word[i + 1]);
//		x += roundf(kern * scale);
//	}
//
//	/* 将位图数据保存到1通道的png图像中 */
//	stbi_write_png("STB.png", bitmap_w, bitmap_h, 1, bitmap, bitmap_w);
//
//	free(fontBuffer);
//	free(bitmap);
//
//	return 0;
//}

Font::Font(const std::string & path, uint32_t size)
	: m_ttFontInfo(new stbtt_fontinfo())
	, m_size(0.0f)
	, m_scale(0.0f)
{
	FILE *f = fopen(path.data(), "rb");
	nbThrowExceptionIf(!f, std::runtime_error, "can't open font file [%s]", path.data());

	fseek(f, 0, SEEK_END);
	auto fileSize = ftell(f);
	fseek(f, 0, SEEK_SET);
	unsigned char *buffer = new unsigned char[fileSize];
	auto n = fread(buffer, fileSize, 1, f);

	if (!stbtt_InitFont(m_ttFontInfo, buffer, 0))
	{
		nbThrowException(std::runtime_error, "fail to init font [%s]", path.data())
	}

	m_scale = stbtt_ScaleForPixelHeight(m_ttFontInfo, (float)size);
	m_size = (float)size;
	/**
	* 获取垂直方向上的度量
	* ascent：字体从基线到顶部的高度；
	* descent：基线到底部的高度，通常为负值；
	* lineGap：两个字体之间的间距；
	*/
	stbtt_GetFontVMetrics(m_ttFontInfo, &m_ascent, &m_descent, &m_lineGap);
	m_ascent = (int)roundf((float)m_ascent * m_scale);
	m_descent = (int)roundf((float)m_descent * m_scale);
}

Font::~Font()
{
	delete m_ttFontInfo;
}

float Font::getBaseline() const
{
	return m_ascent * m_scale;
}

//行间距为：ascent - descent + lineGap。
float Font::getLineHeight() const
{
	return m_ascent - m_descent + m_lineGap * m_scale;
}

FontBm Font::getBitmap(wchar_t unicode) const
{
	FontBm fontBM;

	int advanceX, bearingX;
	stbtt_GetCodepointHMetrics(m_ttFontInfo, unicode, &advanceX, &bearingX);

	int x0, y0, x1, y1, w, h;
	stbtt_GetCodepointBitmapBox(m_ttFontInfo, unicode, m_scale, m_scale, &x0, &y0, &x1, &y1);
	auto bitmap = stbtt_GetCodepointBitmap(m_ttFontInfo, 0, stbtt_ScaleForPixelHeight(m_ttFontInfo, m_size), unicode, &w, &h, 0, 0);

	int y = m_ascent + y0;
	fontBM.rc = Rect((float)x0, (float)y, (float)w, (float)h);
	fontBM.advanceX = advanceX * m_scale;
	fontBM.bm.assign(bitmap, bitmap + w * h);

	//stbi_write_png("d:/STB.png", w, h, 1, bitmap, w);
	return fontBM;
}

void Font::saveTextBitmap(const std::string & path, const std::string & text)
{
	//func();
	/* 创建位图 */
	int bitmap_w = 512; /* 位图的宽 */
	int bitmap_h = 128; /* 位图的高 */
	auto bitmap = new unsigned char[bitmap_w * bitmap_h];
	memset(bitmap, 0, bitmap_w * bitmap_h); 
	//unsigned char *bitmap = (unsigned char*)calloc(bitmap_w * bitmap_h, sizeof(unsigned char));

	int x = 0;
	for (int i = 0; i != text.size(); ++i)
	{
		auto word = text[i];
		int advanceWidth = 0;
		int leftSideBearing = 0;
		stbtt_GetCodepointHMetrics(m_ttFontInfo, word, &advanceWidth, &leftSideBearing);

		/* 获取字符的边框（边界） */
		int c_x1, c_y1, c_x2, c_y2;
		stbtt_GetCodepointBitmapBox(m_ttFontInfo, word, m_scale, m_scale, &c_x1, &c_y1, &c_x2, &c_y2);

		/* 计算位图的y (不同字符的高度不同） */
		int y = m_ascent + c_y1;

		/* 渲染字符 */
		int byteOffset = x + (int)roundf(leftSideBearing * m_scale) + (y * bitmap_w);
		stbtt_MakeCodepointBitmap(m_ttFontInfo, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, bitmap_w, m_scale, m_scale, word);

		/* 调整x */
		x += (int)roundf(advanceWidth * m_scale);

		/* 调整字距 */
		int kern;
		kern = stbtt_GetCodepointKernAdvance(m_ttFontInfo, word, i + 1 < (int)text.size() ? text[i + 1] : 0);
		x += (int)roundf(kern * m_scale);
	}

	/* 将位图数据保存到1通道的png图像中 */
	stbi_write_png(path.data(), bitmap_w, bitmap_h, 1, bitmap, bitmap_w);

	delete[]bitmap;
}

/**************************************
*	FontAtlas供内部使用
*	同一行的字会无缝隙挨近，行距为font.lineHeight
***************************************/
class NB_API FontAtlas : public Texture2D, public std::enable_shared_from_this<FontAtlas>
{
public:
	FontAtlas(ref<Font> font, float width, float height);

	ref<Glyph> getGlyph(wchar_t unicode);

private:
	ref<Glyph> appendChar(wchar_t unicode);

	ref<Font> m_font;
	std::map<wchar_t, ref<Glyph>> m_glyphs;
	float m_x, m_y;
};

//使用RGBA格式可以使用render2d一样的shader，满足修改文本颜色的需求
FontAtlas::FontAtlas(ref<Font> font, float width, float height)
	: m_font(font)
	, m_x(0.0f)
	, m_y(0.0f)
{
	m_width = width;
	m_height = height;
	m_channels = 4;
	bind();
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, (int)width, (int)height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)width, (int)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	unbind();
}

//获取一个字符的信息
//如果存在返回存在的字形，否则新建一个新字形，并存储下来；
//倘若FontAtlas已满则不允许新建，返回空
ref<Glyph> FontAtlas::getGlyph(wchar_t unicode)
{
	auto iter = m_glyphs.find(unicode);
	return (iter != m_glyphs.end()) ? iter->second : appendChar(unicode);
}

#define IM_COL32(R,G,B,A)	(((uint32_t)(A)<<24) | ((uint32_t)(B)<<16) | ((uint32_t)(G)<<8) | ((uint32_t)(R)<<0))

std::string getTexDataAsRGBA32(const FontBm &fbm)
{
	auto pixels = (int)fbm.rc.width() * (int)fbm.rc.height();
	unsigned char* p = (unsigned char*)malloc(pixels * 4);
	const char* src = fbm.bm.data();
	unsigned int* dst = (unsigned int *)p;
	for (int n = pixels; n > 0; n--)
		*dst++ = IM_COL32(255, 255, 255, (unsigned int)(*src++));
	std::string buf(p, p + pixels * 4);
	free(p);
	return buf;
}

//从左下角开始
//*(0) *(1)
//*(3) *(2)
ref<Glyph> FontAtlas::appendChar(wchar_t unicode)
{
	auto fontBM = m_font->getBitmap(unicode);
	if ((m_x + fontBM.rc.width() > m_width) && (m_y + fontBM.rc.height() > m_height))
		return nullptr;

	auto glyph = createRef<Glyph>();
	glyph->texture = shared_from_this();
	glyph->rc = fontBM.rc;
	glyph->advanceX = fontBM.advanceX;

	auto dataRGBA32 = getTexDataAsRGBA32(fontBM);
	bind();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (m_x + fontBM.rc.width() <= m_width)
	{
		//glTexSubImage2D(GL_TEXTURE_2D, 0, (int)m_x, (int)m_y, (int)fontBM.rc.width(), (int)fontBM.rc.height(), GL_ALPHA, GL_UNSIGNED_BYTE, fontBM.bm.data());
		glTexSubImage2D(GL_TEXTURE_2D, 0, (int)m_x, (int)m_y, (int)fontBM.rc.width(), (int)fontBM.rc.height(), GL_RGBA, GL_UNSIGNED_BYTE, dataRGBA32.data());
		glyph->uv[0] = { m_x / m_width, (m_y + fontBM.rc.height()) / m_height };
		glyph->uv[1] = { (m_x + fontBM.rc.width()) / m_width, (m_y + fontBM.rc.height()) / m_height };
		glyph->uv[2] = { (m_x + fontBM.rc.width()) / m_width, m_y / m_height };
		glyph->uv[3] = { m_x / m_width, m_y / m_height };
		m_x += fontBM.rc.width();
	}
	else
	{
		m_x = (float)(fontBM.rc.width());
		m_y += m_font->getLineHeight();
		//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, (int)m_y, (int)fontBM.rc.width(), (int)fontBM.rc.height(), GL_ALPHA, GL_UNSIGNED_BYTE, fontBM.bm.data());
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, (int)m_y, (int)fontBM.rc.width(), (int)fontBM.rc.height(), GL_RGBA, GL_UNSIGNED_BYTE, dataRGBA32.data());
		glyph->uv[0] = { 0.0f, (m_y + fontBM.rc.height()) / m_height };
		glyph->uv[1] = { fontBM.rc.width() / m_width, (m_y + fontBM.rc.height()) / m_height };
		glyph->uv[2] = { fontBM.rc.width() / m_width, m_y / m_height };
		glyph->uv[3] = { 0.0f, m_y / m_height };
	}
	unbind();

	m_glyphs[unicode] = glyph;
	//save("test.png");
	return glyph;
}

//查找font对应的FontAtlas，如果找到且未满，返回找到Glyph
//否则新建一个FontAtlas
static std::map<ref<Font>, ref<FontAtlas>> g_FontAtlas;
ref<Glyph> nb::getGlyph(ref<Font> font, wchar_t unicode)
{
	auto iter = g_FontAtlas.find(font);
	if (iter != g_FontAtlas.end())
	{
		auto glyph = iter->second->getGlyph(unicode);
		if (glyph)
			return glyph;
	}

	auto newFontAtlas = createRef<FontAtlas>(font, 1024.0f, 1024.0f);
	g_FontAtlas[font] = newFontAtlas;
	return newFontAtlas->getGlyph(unicode);
}

static std::set<ref<Font>> g_fonts;
ref<Font> FontLibrary::addFont(const std::string & path, uint32_t size)
{
	auto font = createRef<Font>(path, size);
	g_fonts.insert(font);
	return font;
}

ref<Font> FontLibrary::getDefaultFont()
{
	static ref<Font> g_defaultFont;
	if (!g_defaultFont)
	{
		g_defaultFont = createRef<Font>(RES_DIR"fonts/siyuanheiti.otf", 32);
	}
	return g_defaultFont;
}
