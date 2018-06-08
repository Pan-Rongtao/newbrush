#include "FontGlyph.h"
#include <assert.h>
#include <GLES2/gl2.h>
#include <algorithm>
#include "GlesProgramState.h"
#include "GlesProgramCache.h"
#include "Shader_Font.frag"
#include "Shader_Font.vert"
#include "GlesProgram.h"

using namespace nb::gl::Gles;


FontGlyph::FontGlyph()
{
	/**
	*    初始化字体库
	*/
	_library = 0;
	_face = 0;
	_fontBuffer = 0;
	_fontSize = 0;
	_fontPixelX = 0;
	_fontPixelY = 0;
	_xStart = 0;
	_yStart = 0;
	_textureWidth = 512;
	_textureHeight = 512;
	_sysFontTexture = -1;
	memset(_character, 0, sizeof(_character));
	FT_Init_FreeType((FT_Library*)&_library);
	assert(_library != 0);
	glEnable(GL_TEXTURE_2D);


// 	m_program = GetProgramCache()->GetProgramState<FontGlesProgramState>(nbShaderType_Font);
// 	if(m_program == NULL)
// 	{
// 		GlesProgram * program = GlesProgram::CreateWithByteArrays(shader_font_vert, shader_font_frag);
// 		GetProgramCache()->AddProgram(nbShaderType_Font,program);
// 		m_program = GetProgramCache()->GetProgramState<FontGlesProgramState>(nbShaderType_Font);
// 	}

}

char* FontGlyph::ReadFile(const char* fileName, unsigned& length)
{
	FILE*   pFile = fopen(fileName, "rb");
	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		length = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);
		char* buffer = new char[length + 1];
		fread(buffer, 1, length, pFile);
		buffer[length] = 0;
		fclose(pFile);
		return  buffer;
	}
	else
	{
		char    buffer[256];
		sprintf(buffer, "read %s  failed", fileName);
		assert(pFile != 0 && buffer);
	}
	return  0;

}

/**
*   建立字体系统
*/
void    FontGlyph::BuildSystemFont(const char* font, int fontSize)
{

	unsigned    length = 0;
	_fontBuffer = ReadFile(font, length);

	/**
	*   保存字体的大小
	*/
	_fontSize = fontSize;
	/**
	*   已经创建了字体则销毁
	*   支持多次调用
	*/
	if (_face)
	{
		FT_Done_Face(FT_Face(_face));
		_xStart = 0;
		_yStart = 0;
		memset(_character, 0, sizeof(_character));
	}
	/**
	*   销毁字体
	*/
	if (_sysFontTexture != -1)
	{
		glDeleteTextures(1, &_sysFontTexture);
	}

	glGenTextures(1, &_sysFontTexture);
	/**
	*   使用这个纹理id,或者叫绑定(关联)
	*/
	glBindTexture(GL_TEXTURE_2D, _sysFontTexture);
	/**
	*   指定纹理的放大,缩小滤波，使用线性方式，即当图片放大的时候插值方式
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(
		GL_TEXTURE_2D,      //! 指定是二维图片
		0,                  //! 指定为第一级别，纹理可以做mipmap,即lod,离近的就采用级别大的，远则使用较小的纹理
		GL_ALPHA,           //! 纹理的使用的存储格式
		_textureWidth,
		_textureHeight,
		0,                  //! 是否的边
		GL_ALPHA,           //! 数据的格式，bmp中，windows,操作系统中存储的数据是bgr格式
		GL_UNSIGNED_BYTE,   //! 数据是8bit数据
		0
		);
	FT_New_Memory_Face((FT_Library)_library, (const FT_Byte *)_fontBuffer, length, 0, (FT_Face*)&_face);

	FT_F26Dot6 ftSize = (FT_F26Dot6)(fontSize * (1 << 6));

	FT_Set_Char_Size((FT_Face)_face, ftSize, 0, 72, 72);

	assert(_face != 0);

}

FontGlyph::~FontGlyph()
{
	/**
	*   释放字体库
	*/
	if (_sysFontTexture != -1)
	{
		glDeleteTextures(1, &_sysFontTexture);
		_sysFontTexture = -1;
	}
	if (_face)
	{
		FT_Done_Face(FT_Face(_face));
		_xStart = 0;
		_yStart = 0;
		_face = 0;
		memset(_character, 0, sizeof(_character));
	}
	if (_fontBuffer)
	{
		delete[]_fontBuffer;
		_fontBuffer = 0;
	}

	/**
	*   释放字体库
	*/
	if (_library)
	{
		FT_Done_FreeType((FT_Library)_library);
		_library = 0;
	}
}


Character FontGlyph::GetCharacter(wchar_t ch)
{

	if (_character[ch].x0 == 0 &&
		_character[ch].x0 == 0 &&
		_character[ch].x1 == 0 &&
		_character[ch].y1 == 0
		)
	{

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		if (_xStart + std::max<int>(_fontPixelX, _fontSize) > _textureWidth)
		{
			/**
			*   写满一行,从新开始
			*/
			_xStart = 0;
			/**
			*   y开始位置要增加
			*/
			_yStart += std::max<int>(_fontPixelY, _fontSize);
		}
		FT_Load_Glyph((FT_Face)_face, FT_Get_Char_Index((FT_Face)_face, ch), FT_LOAD_DEFAULT);
		FT_Glyph glyph;
		FT_Get_Glyph(FT_Face(_face)->glyph, &glyph);

		/**
		*   根据字体的大小决定是否使用反锯齿绘制模式
		*   当字体比较小的是说建议使用ft_render_mode_mono
		*   当字体比较大的情况下12以上，建议使用ft_render_mode_normal模式
		*/
		if (_fontSize >= 16)
		{
			FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
		}
		else
		{
			FT_Glyph_To_Bitmap(&glyph, ft_render_mode_mono, 0, 1);
		}

		FT_BitmapGlyph  bitmap_glyph = (FT_BitmapGlyph)glyph;
		FT_Bitmap&      bitmap = bitmap_glyph->bitmap;
		FT_Bitmap       ftBitmap;
		FT_Bitmap_New(&ftBitmap);

		if (bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
		{
			if (FT_Bitmap_Convert((FT_Library)_library, &bitmap, &ftBitmap, 1) == 0)
			{
				/**
				*   Go through the bitmap and convert all of the nonzero values to 0xFF (white).
				*/
				for (unsigned char* p = ftBitmap.buffer, *endP = p + ftBitmap.width * ftBitmap.rows; p != endP; ++p)
					*p ^= -*p ^ *p;
				bitmap = ftBitmap;
			}
		}
		/**
		*   如果没有数据，则不写，直接过去
		*/
		if (bitmap.width == 0 || bitmap.rows == 0)
		{

			char    mem[1024 * 32];
			memset(mem, 0, sizeof(mem));

			_character[ch].x0 = _xStart;
			_character[ch].y0 = _yStart;
			_character[ch].x1 = _xStart + _fontSize / 2;
			_character[ch].y1 = _yStart + _fontSize - 1;
			_character[ch].offsetY = _fontSize - 1;
			_character[ch].offsetX = 0;



			glBindTexture(GL_TEXTURE_2D, _sysFontTexture);

			glTexSubImage2D(
				GL_TEXTURE_2D,
				0,
				_xStart,
				_yStart,
				_fontSize / 2,
				_fontSize,
				GL_ALPHA,
				GL_UNSIGNED_BYTE,
				mem
				);
			_xStart += _fontSize / 2;


		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, _sysFontTexture);

			_character[ch].x0 = _xStart;
			_character[ch].y0 = _yStart;
			_character[ch].x1 = _xStart + bitmap.width;
			_character[ch].y1 = _yStart + bitmap.rows;

			_character[ch].offsetY = bitmap_glyph->top;
			_character[ch].offsetX = bitmap_glyph->left;

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexSubImage2D(
				GL_TEXTURE_2D,
				0,
				_xStart,
				_yStart,
				std::max<int>(1, bitmap.width),
				std::max<int>(1, bitmap.rows),
				GL_ALPHA,
				GL_UNSIGNED_BYTE,
				bitmap.buffer
				);
			_xStart += (bitmap.width + 1);
			_fontPixelY = std::max<int>(_fontPixelY, bitmap.rows);
			_fontPixelX = std::max<int>(_fontPixelX, bitmap.width);
		}

		FT_Bitmap_Done((FT_Library)_library, &ftBitmap);
	}
	return  _character[ch];
}


void FontGlyph::BeginText(const CELL::matrix4& proj)
{
//	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _sysFontTexture);

	m_program->Use();
	glEnableVertexAttribArray(m_program->m_position);
	glEnableVertexAttribArray(m_program->m_uv);
	glEnableVertexAttribArray(m_program->m_color);
	/**
	*   绑定程序数据
	*/
//	Camera*	camera = Domain::GetInstance()->GetGlesApp()->m_pCamera;
	CELL::matrix4 matMVP(1.0f);
//	matMVP = proj* camera->GetViewMatrix().GetPrivateData()->m_matrix;

	glUniformMatrix4fv(m_program->m_MVP, 1, GL_FALSE, matMVP.data());
	glUniform1i(m_program->m_texture, 0);
}

void FontGlyph::EndText()
{
	glDisable(GL_BLEND);
	m_program->UnUse();
	glDisableVertexAttribArray(m_program->m_position);
	glDisableVertexAttribArray(m_program->m_uv);
	glDisableVertexAttribArray(m_program->m_color);
}

CELL::float2 FontGlyph::DrawFontText(
	const CELL::float3& pos,
	const CELL::Rgba4Byte& color,//rgba
	const wchar_t* text,
	size_t length /*= -1 */,
	FontVertex**  vertexs/* = 0*/,
	size_t* vertexLength/* = 0*/)
{
	static      FontVertex  vert[1024];

	float       texWidth = (float)_textureWidth;
	float       texHeight = (float)_textureHeight;
	float       xStart = (float)(int)pos.x;
	float       yStart = (float)(int)pos.y + _fontSize;
	float       zStart = pos.z;
	unsigned    index = 0;
	unsigned    size = length == -1 ? wcslen(text) : length;
	CELL::float2   vSize(0, 0);


	if (size == 0)
	{
		return  vSize;
	}

	for (unsigned i = 0; i < size; ++i)
	{
		Character   ch = GetCharacter(text[i]);

		float       h = float(ch.y1 - ch.y0);
		float       w = float(ch.x1 - ch.x0);
		float       offsetY = (float(h) - float(ch.offsetY));
		/**
		*   第一个点
		*/
		vert[index + 0].x = xStart;
		vert[index + 0].y = yStart - h + offsetY;
		vert[index + 0].z = zStart;
		vert[index + 0].u = ch.x0 / texWidth;
		vert[index + 0].v = ch.y0 / texHeight;
		vert[index + 0].w = 1;
		vert[index + 0].color = color;
		/**
		*   第二个点
		*/
		vert[index + 1].x = xStart + w;
		vert[index + 1].y = yStart - h + offsetY;
		vert[index + 1].z = zStart;
		vert[index + 1].u = ch.x1 / texWidth;
		vert[index + 1].v = ch.y0 / texHeight;
		vert[index + 1].w = 1;
		vert[index + 1].color = color;
		/**
		*   第三个点
		*/
		vert[index + 2].x = xStart + w;
		vert[index + 2].y = yStart + offsetY;
		vert[index + 2].z = zStart;
		vert[index + 2].u = ch.x1 / texWidth;
		vert[index + 2].v = ch.y1 / texHeight;
		vert[index + 2].w = 1;
		vert[index + 2].color = color;



		/**
		*   第一个点
		*/
		vert[index + 3].x = xStart;
		vert[index + 3].y = yStart - h + offsetY;
		vert[index + 3].z = zStart;
		vert[index + 3].u = ch.x0 / texWidth;
		vert[index + 3].v = ch.y0 / texHeight;
		vert[index + 3].w = 1;
		vert[index + 3].color = color;

		/**
		*   第三个点
		*/
		vert[index + 4].x = xStart + w;
		vert[index + 4].y = yStart + offsetY;
		vert[index + 4].z = zStart;
		vert[index + 4].u = ch.x1 / texWidth;
		vert[index + 4].v = ch.y1 / texHeight;
		vert[index + 4].w = 1;
		vert[index + 4].color = color;


		/**
		*   第四个点
		*/
		vert[index + 5].x = xStart;
		vert[index + 5].y = yStart + offsetY;
		vert[index + 5].z = zStart;
		vert[index + 5].u = ch.x0 / texWidth;
		vert[index + 5].v = ch.y1 / texHeight;
		vert[index + 5].w = 1;
		vert[index + 5].color = color;

		index += 6;
		xStart += w + (ch.offsetX + 1);

		vSize.x += w + (ch.offsetX + 1);
		vSize.y = std::max<float>(h + offsetY, vSize.y);

	}
	//struct VerText
	//{
	//	CELL::float3 pos;
	//	CELL::float3 uv;
	//	CELL::Rgba4Byte color;
	//};
	//VerText vt[] = 
	//{
	//	CELL::float3(0,0,0), CELL::float3(0,0,1) ,CELL::Rgba4Byte(255,141,21,255),
	//	CELL::float3(512,0,0), CELL::float3(1,0,1) ,CELL::Rgba4Byte(255,141,21,255),
	//	CELL::float3(0,512,0), CELL::float3(0,1,1) ,CELL::Rgba4Byte(255,141,21,255),
	//	CELL::float3(512,512,0), CELL::float3(1,1,1) ,CELL::Rgba4Byte(255,141,21,255)
	//};

	//glVertexAttribPointer(m_program->m_position, 3, GL_FLOAT, GL_FALSE, sizeof(VerText), vt);
	//glVertexAttribPointer(m_program->m_uv,		  3, GL_FLOAT, GL_FALSE, sizeof(FontVertex), &vt[0].uv);
	//glVertexAttribPointer(m_program->m_color,	  4, GL_UNSIGNED_BYTE, GL_TRUE,  sizeof(FontVertex), &vt[0].color);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	int a = sizeof(FontVertex);
	//FontShader* fontshader = Domain::GetInstance()->GetGlesApp()->m_pFontShader;
	glVertexAttribPointer(m_program->m_position, 3, GL_FLOAT, GL_FALSE, sizeof(FontVertex), vert);
	glVertexAttribPointer(m_program->m_uv,		  3, GL_FLOAT, GL_FALSE, sizeof(FontVertex), &vert[0].u);
	glVertexAttribPointer(m_program->m_color,	  4, GL_UNSIGNED_BYTE, GL_TRUE,  sizeof(FontVertex), &vert[0].color);
	glDrawArrays(GL_TRIANGLES, 0, index);
	/**
	*   向外输出顶点数据.
	*/
	if (vertexs)
	{
		*vertexs = vert;
	}
	if (vertexLength)
	{
		*vertexLength = index;
	}
	return  vSize;
}


CELL::float2 FontGlyph::DrawTextToBuffer(
	const CELL::float3& pos,
	const CELL::Rgba4Byte& color,//rgba
	const wchar_t* text,
	size_t length /*= -1 */,
	FontVertex**  vertexs/* = 0*/,
	size_t* vertexLength/* = 0*/)
{

	*vertexs = 0;
	*vertexLength = 0;

	static      FontVertex  vert[1024];

	float       texWidth = (float)_textureWidth;
	float       texHeight = (float)_textureHeight;
	float       xStart = (float)int(pos.x);
	float       yStart = (float)int(pos.y + _fontSize);
	float       zStart = pos.z;
	unsigned    index = 0;
	unsigned    size = length == -1 ? wcslen(text) : length;
	CELL::float2      vSize(0, 0);


	if (size == 0)
	{
		return  vSize;
	}

	for (unsigned i = 0; i < size; ++i)
	{
		Character   ch = GetCharacter(text[i]);

		float       h = float(ch.y1 - ch.y0);
		float       w = float(ch.x1 - ch.x0);
		float       offsetY = (float(h) - float(ch.offsetY));
		/**
		*   第一个点
		*/
		vert[index + 0].x = xStart;
		vert[index + 0].y = yStart - h + offsetY;
		vert[index + 0].z = zStart;
		vert[index + 0].u = ch.x0 / texWidth;
		vert[index + 0].v = ch.y0 / texHeight;
		vert[index + 0].w = 1;
		vert[index + 0].color = color;
		/**
		*   第二个点
		*/
		vert[index + 1].x = xStart + w;
		vert[index + 1].y = yStart - h + offsetY;
		vert[index + 1].z = zStart;
		vert[index + 1].u = ch.x1 / texWidth;
		vert[index + 1].v = ch.y0 / texHeight;
		vert[index + 1].w = 1;
		vert[index + 1].color = color;
		/**
		*   第三个点
		*/
		vert[index + 2].x = xStart + w;
		vert[index + 2].y = yStart + offsetY;
		vert[index + 2].z = zStart;
		vert[index + 2].u = ch.x1 / texWidth;
		vert[index + 2].v = ch.y1 / texHeight;
		vert[index + 2].w = 1;
		vert[index + 2].color = color;

		/**
		*   第一个点
		*/
		vert[index + 3].x = xStart;
		vert[index + 3].y = yStart - h + offsetY;
		vert[index + 3].z = zStart;
		vert[index + 3].u = ch.x0 / texWidth;
		vert[index + 3].v = ch.y0 / texHeight;
		vert[index + 3].w = 1;
		vert[index + 3].color = color;

		/**
		*   第三个点
		*/
		vert[index + 4].x = xStart + w;
		vert[index + 4].y = yStart + offsetY;
		vert[index + 4].z = zStart;
		vert[index + 4].u = ch.x1 / texWidth;
		vert[index + 4].v = ch.y1 / texHeight;
		vert[index + 4].w = 1;
		vert[index + 4].color = color;
		/**
		*   第四个点
		*/
		vert[index + 5].x = xStart;
		vert[index + 5].y = yStart + offsetY;
		vert[index + 5].z = zStart;
		vert[index + 5].u = ch.x0 / texWidth;
		vert[index + 5].v = ch.y1 / texHeight;
		vert[index + 5].w = 1;
		vert[index + 5].color = color;

		index += 6;
		xStart += w + (ch.offsetX + 1);

		vSize.x += w + (ch.offsetX + 1);

		vSize.y = std::max<float>((h + offsetY), vSize.y);
	}

	/**
	*   向外输出顶点数据.
	*/
	if (vertexs)
	{
		*vertexs = vert;
	}
	if (vertexLength)
	{
		*vertexLength = index;
	}
	return  vSize;
}
