#include "FontAtlas.h"
#include "FontFreeType.h"
#include "media/Bitmap.h"
#include <algorithm> 
using namespace nb::gl::Gles;

TextureFont::TextureFont(int fontSize)
	:m_texture(-1)
	,m_yStart(0)
	,m_xStart(0)
	,m_fontPixelY(0)
	,m_fontSize(fontSize)

{
//	m_program = GetProgramCache()->GetProgramState<FontGlesProgramState>(nbShaderType_Font);
// 	if(m_program == NULL)
// 	{
// 		GlesProgram * program = GlesProgram::CreateWithByteArrays(shader_font_vert, shader_font_frag);
// 		GetProgramCache()->AddProgram(nbShaderType_Font,program);
// 		m_program = GetProgramCache()->GetProgramState<FontGlesProgramState>(nbShaderType_Font);
// 	}
}

TextureFont::~TextureFont()
{
	if (m_texture == -1) return;
	glDeleteTextures(1, (GLuint *)&m_texture);
}

bool TextureFont::Init()
{
	glGenTextures(1, (GLuint *)&m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_ALPHA,
		m_textureWidth,
		m_textureHeight,
		0,
		GL_ALPHA,
		GL_UNSIGNED_BYTE,
		0
	);
	return true;
}

bool TextureFont::UpdateData(FontLetterDefinition& letterDefine, const FT_BitmapGlyph bimapGlyph)
{
	if(m_xStart + bimapGlyph->bitmap.width > m_textureWidth)
	{
		m_xStart = 0;
		if(m_yStart + bimapGlyph->bitmap.rows > m_textureHeight)
		{
			return false;
		}
		m_yStart += m_fontPixelY + 1;
		m_fontPixelY = 0;
	}
	if(bimapGlyph->bitmap.width > 0 && bimapGlyph->bitmap.rows > 0)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture);
		letterDefine.m_x0 = m_xStart;
		letterDefine.m_y0 = m_yStart;
		letterDefine.m_x1 = m_xStart + bimapGlyph->bitmap.width;
		letterDefine.m_y1 = m_yStart + bimapGlyph->bitmap.rows;
		letterDefine.m_offsetY = bimapGlyph->top;
		letterDefine.m_offsetX = bimapGlyph->left;
		letterDefine.m_texture = this;

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexSubImage2D(
			GL_TEXTURE_2D,
			0,
			m_xStart,
			m_yStart,
			std::max<int>(1, bimapGlyph->bitmap.width),
			std::max<int>(1, bimapGlyph->bitmap.rows),
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			bimapGlyph->bitmap.buffer
			);
		m_xStart += (bimapGlyph->bitmap.width + 1);

		m_fontPixelY = std::max<int>(m_fontPixelY, bimapGlyph->bitmap.rows);
	}
	else
	{
		char    mem[1024 * 32];
		memset(mem, 0, sizeof(mem));

		letterDefine.m_x0 = m_xStart;
		letterDefine.m_y0 = m_yStart;
		letterDefine.m_x1 = m_xStart + m_fontSize / 2 ;
		letterDefine.m_y1 = m_yStart + m_fontSize - 1;
		letterDefine.m_offsetY = m_fontSize - 1;
		letterDefine.m_offsetX = 0;	


		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexSubImage2D(
			GL_TEXTURE_2D,
			0,
			m_xStart,
			m_yStart,
			m_fontSize / 2,
			m_fontSize,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			mem
			);
		m_xStart += m_fontSize / 2;
		letterDefine.m_texture = this;
	}
	return true;
}


FontAtlas::FontAtlas(const TTFConfig* config)
: m_currentPage(0)
{
	m_pfontFreetype = FontFreeType::Create(config->m_fontFilePath, config->m_fontSize);
	m_fontSize = config->m_fontSize;
	TextureFont * texture = new TextureFont(m_fontSize);
	if(!texture->Init())
	{
		//throw an exception
		delete texture;
	}
	m_atlasTextures[m_currentPage] = texture;
}

FontAtlas::~FontAtlas(void)
{
	
}

void FontAtlas::FindNewCharacters(const std::wstring& u16Text,  std::wstring & OutNewCharCodeMap)
{
	OutNewCharCodeMap.clear();
	for(int i = 0;i < u16Text.length(); ++i)
	{
		std::map<wchar_t, FontLetterDefinition>::iterator itor = m_letterDefinitions.find(u16Text[i]);
		if(itor == m_letterDefinitions.end())
		{
			std::size_t found = OutNewCharCodeMap.find(u16Text[i]);
			if(found == std::string::npos)
			{
				OutNewCharCodeMap.push_back(u16Text[i]);
			}
		}
	}
}

const FontLetterDefinition * FontAtlas::GetLetterDefinition(wchar_t letter)
{
	std::map<wchar_t, FontLetterDefinition>::iterator itor = m_letterDefinitions.find(letter);
	if(itor != m_letterDefinitions.end())
	{
		return &(itor->second);
	}
	return NULL;
}

bool FontAtlas::PrepareLetterDefinitions(const std::wstring & utf16Text)
{
	if (m_pfontFreetype == NULL)
    {
        return false;
    } 
	std::wstring codeMapOfNewChar;
    FindNewCharacters(utf16Text, codeMapOfNewChar);
    if (codeMapOfNewChar.empty())
    {
        return false;
    }
	for(int i = 0;i < codeMapOfNewChar.length(); ++i)
	{
		const FT_BitmapGlyph bimapGlyph = m_pfontFreetype->GetGlyphBimap(codeMapOfNewChar[i]);
		FontLetterDefinition letterDefine;
		RenderBimapToTexture(letterDefine, bimapGlyph);
		m_letterDefinitions[codeMapOfNewChar[i]] = letterDefine;
		FT_Done_Glyph((FT_Glyph)bimapGlyph);
	}
	return true;
}

void FontAtlas::RenderBimapToTexture(FontLetterDefinition & letterDefine,const FT_BitmapGlyph bimapGlyph)
{
	if(!m_atlasTextures[m_currentPage]->UpdateData(letterDefine, bimapGlyph))
	{
		TextureFont * texture = new TextureFont(m_fontSize);
		if(!texture->Init())
		{
			//throw an exception
			delete texture;
		}
		++m_currentPage;
		texture->UpdateData(letterDefine, bimapGlyph);
		m_atlasTextures[m_currentPage] = texture;
	}
}
