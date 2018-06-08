#pragma once
#include "core/Object.h"
#include "CELLMath.hpp"
#include <ft2build.h>
#include FT_GLYPH_H
#include FT_TRUETYPE_TABLES_H
#include FT_BITMAP_H
#include FT_WINFONTS_H
#include "FontGlesProgramState.h"

namespace nb{ namespace gl{ namespace Gles{

struct  FontVertex
{
	float       x, y, z;
	float       u, v, w;
	CELL::Rgba4Byte   color;//rgba Rgba4Byte
};

class Character
{
public:
	Character()
	{
		x0 = 0;
		y0 = 0;
		x1 = 0;
		y1 = 0;
		offsetX = 0;
		offsetY = 0;
	}
	/**
	*   存储当前字符在纹理上的坐标位置
	*   采用1024大小的纹理，可以存常用的汉字(16像素)
	*/
	unsigned int   x0 : 10;
	unsigned int   y0 : 10;
	unsigned int   x1 : 10;
	unsigned int   y1 : 10;
	//! 字体的偏移x方向
	unsigned int   offsetX : 8;
	//! 字体的偏移y方向
	unsigned int   offsetY : 8;
	//! 纹理的所有，最大256个
	unsigned int   texIndex : 8;
};

class FontGlyph : public nbObject
{
public:
	FontGlyph();

	char * ReadFile(const char * fileName, unsigned & length);

	~FontGlyph();

	Character GetCharacter(wchar_t ch);

	void BeginText(const CELL::matrix4& proj);

	void EndText();

	CELL::float2 DrawFontText(const CELL::float3& pos, const CELL::Rgba4Byte& color, const wchar_t * text, size_t length, FontVertex ** vertexs, size_t * vertexLength);

	CELL::float2 DrawTextToBuffer(const CELL::float3& pos, const CELL::Rgba4Byte& color, const wchar_t * text, size_t length, FontVertex ** vertexs, size_t * vertexLength);

	void BuildSystemFont(const char* font, int fontSize);

	unsigned int GetTexture()
	{
		return _sysFontTexture;
	}
private:
	unsigned    _sysFontTexture;
	Character   _character[1 << 16];
	void*       _library;
	void*       _face;
	char*       _fontBuffer;
	int         _textureWidth;
	int         _textureHeight;
	int         _yStart;
	int         _xStart;
	int         _fontSize;
	int         _fontPixelX;
	int         _fontPixelY;
	FontGlesProgramStatePtr m_program;
};

}}}
