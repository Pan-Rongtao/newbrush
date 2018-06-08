#include "gles/TextSurface.h"
#include "gles/Model2D.h"
#include "CELLMath.hpp"
#include "FontAtlas.h"
#include "FontAtlasCache.h"
#include <GLES2/gl2.h>
#include <algorithm>

using namespace nb::System;
namespace nb{ namespace gl{ namespace Gles{

class TextSurfaceImp : public Model2D
{
public:
	TextSurfaceImp(const TTFConfig & config, TextSurface * owner)
		: m_iLetterSpacing(5)
		, m_iLineSpacing(5)
		, m_bIsInit(false)
		, m_owner(owner)
		, m_size(config.m_fontSize,config.m_fontSize)
		, m_stretchMode(TextSurface::StretchWidth)
		, m_ttfConfig(config)
		, Model2D(4, Model::Vertex_Attribute_Position)
	{
// 		m_fontAtlas = FontCache()->GetFontAtlasTTF(&config);
// 		m_program = GetProgramCache()->GetProgramState<FontGlesProgramState>(nbShaderType_Font);
// 		if(m_program == NULL)
// 		{
// 			GlesProgram * program = GlesProgram::CreateWithByteArrays(shader_font_vert, shader_font_frag);
// 			GetProgramCache()->AddProgram(nbShaderType_Font,program);
// 			m_program = GetProgramCache()->GetProgramState<FontGlesProgramState>(nbShaderType_Font);
// 		}
		glGenBuffers(1, &m_vertexVbo);
//		m_frame = new RectangleSurface();
	}

	~TextSurfaceImp()
	{
		glDeleteBuffers(1, &m_vertexVbo);
	}

	TextSurfaceImp(const std::wstring& sText, const nb::System::Point3D& position, const nb::System::Color& color, const TTFConfig & config, TextSurface * owner)
		: m_color(color)
		, m_position(position)
		, m_iLetterSpacing(5)
		, m_iLineSpacing(5)
		, m_bIsInit(false)
		, m_owner(owner)
		, m_size(100,100)
		, m_stretchMode(TextSurface::StretchWidth)
		, m_ttfConfig(config)
		, Model2D(4, Model::Vertex_Attribute_Position)
	{
// 		m_fontAtlas = FontCache()->GetFontAtlasTTF(&config);
// 		m_program = GetProgramCache()->GetProgramState<FontGlesProgramState>(nbShaderType_Font);
// 		if(m_program == NULL)
// 		{
// 			GlesProgram * program = GlesProgram::CreateWithByteArrays(shader_font_vert, shader_font_frag);
// 			GetProgramCache()->AddProgram(nbShaderType_Font,program);
// 			m_program = GetProgramCache()->GetProgramState<FontGlesProgramState>(nbShaderType_Font);
// 		}
// 		glGenBuffers(1, &m_vertexVbo);
// 		SetText(sText);
	}
	virtual void OnRender(/*const Matrix4x4* matProj*/) {}
	void OnDraw(/*const Matrix4x4* matProj*/)
	{
		//FontGlyph* fontglyph = Domain::GetInstance()->GetGlesApp()->m_pFontGlyph;
		//fontglyph->BeginText(matProj->GetPrivateData()->m_matrix);
		//fontglyph->DrawFontText(CELL::float3(m_position.GetX(), m_position.GetY(), m_position.GetZ()),
		//						CELL::Rgba4Byte(m_color.GetRed(), m_color.GetGreen(), m_color.GetBlue(), m_color.GetAlpha()),
		//						m_sText.c_str(),-1,0,0);
		//fontglyph->EndText();
		//return;
		if(!m_bIsInit)
		{
			m_bIsInit = true;
			PrepareText();
			AlignText();
		}

		if(m_letterNodes.size() <=0)
		{
			return;
		}


		glBindBuffer(GL_ARRAY_BUFFER,m_vertexVbo);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_letterNodes[0]->m_letterDefinition->m_texture->m_texture);
		m_program->Use();
		glEnableVertexAttribArray(m_program->m_position);
		glEnableVertexAttribArray(m_program->m_uv);
		glEnableVertexAttribArray(m_program->m_color);

//		Camera*	camera = Domain::GetInstance()->GetGlesApp()->m_pCamera;
		CELL::matrix4 matMVP(1.0f);
		//matMVP = matProj->GetPrivateData()->m_matrix * camera->GetViewMatrix().GetPrivateData()->m_matrix;
//		matMVP = (matProj->GetPrivateData()->m_matrix) * camera->GetViewMatrix().GetPrivateData()->m_matrix * m_owner->GetModeMatrix().GetPrivateData()->m_matrix;

		glUniformMatrix4fv(m_program->m_MVP, 1, GL_FALSE, matMVP.data());
		glUniform1i(m_program->m_texture, 0);

		glBindBuffer(GL_ARRAY_BUFFER,m_vertexVbo);
		glVertexAttribPointer(m_program->m_position, 3, GL_FLOAT, GL_FALSE, sizeof(LetterNode::FontVertex1), (void*)0);
		glVertexAttribPointer(m_program->m_uv,		  3, GL_FLOAT, GL_FALSE, sizeof(LetterNode::FontVertex1),(void*)12);
		glVertexAttribPointer(m_program->m_color,	  4, GL_UNSIGNED_BYTE, GL_TRUE,  sizeof(LetterNode::FontVertex1), (void*)24);
		glDrawArrays(GL_TRIANGLES, 0, m_fontVertex.size());
		glBindBuffer(GL_ARRAY_BUFFER,0);
/*
		m_frame->SetDrawMode(RectangleSurface::DM_LINE_RECTANGLE);
		m_frame->SetOrigin(nb::System::Point(m_position.GetX(),m_position.GetY()));
		m_frame->SetWidth(m_size.Width());
		m_frame->SetHeight(m_size.Height());
		m_frame->SetColor(nb::System::Color(255,0,0));
		m_frame->Identity();*/
//		m_frame->Transform(m_owner->GetModeMatrix());

		//m_frame->OnDraw(matProj);

	}

	void SetText(const std::wstring& sText)
	{
		m_sText = sText;
		PrepareLetterNodes();
		if(!m_bIsInit) return;
		AlignText();
	}

	inline void PrepareText()
	{
		m_fontAtlas->PrepareLetterDefinitions(m_sText);

	}

	inline void PrepareLetterNodes()
	{
		m_letterNodes.clear();
		for(int i = 0; i < m_sText.length(); i++)
		{
			LetterNodePtr letterNode = LetterNode::Create(m_sText[i]);
			m_letterNodes.push_back(letterNode);
		}
	}

	void SetContentSize(const nb::System::Size & size)
	{
		m_size = size;
		if(!m_bIsInit) return;
		AlignText();
	}

	void SetColor(const nb::System::Color& color)
	{
		m_color = color;
		if(!m_bIsInit) return;
		for(int i=0; i < m_letterNodes.size(); ++i)
		{
			m_letterNodes[i]->SetColor(color);
		}
	}

	void SetLetterSpacing(int letterSpacing)
	{
		m_iLetterSpacing = letterSpacing;
		if(!m_bIsInit) return;
		AlignText();
	}

	void SetLineSpacing(int lineSpacing)
	{
		m_iLineSpacing = lineSpacing;
		if(!m_bIsInit) return;
		AlignText();
	}

	void SetPosition(const nb::System::Point3D& position)
	{
		m_position = position;
		if(!m_bIsInit) return;
		AlignText();
	}

	std::vector<LetterNodePtr> & GetLetters()
	{
		return m_letterNodes;
	}

	const std::wstring & GetText()
	{
		return m_sText;
	}

	void AlignText()
	{
		int alignX = m_position.GetX();
		int alignY = m_position.GetY() + m_ttfConfig.m_fontSize;
		int alignZ = m_position.GetZ();
		//int lineHeight = 0;
		int lastOffset = 0;
		int maxXPos = m_position.GetX() + m_size.Width();
		m_fontVertex.clear();
		m_fontVertex.resize(m_sText.length() * 6);
		int index = 0;
		for(int i = 0; i < m_sText.length(); i++)
		{
			const FontLetterDefinition * letterDefinition = m_fontAtlas->GetLetterDefinition(m_sText[i]);

			if(m_stretchMode == TextSurface::StretchHeight)
			{
				int len = (alignX + letterDefinition->m_x1 - letterDefinition->m_x0) - m_position.GetX();
				if((alignX + letterDefinition->m_x1 - letterDefinition->m_x0) - m_position.GetX() > m_size.Width())
				{
					alignY = alignY + m_ttfConfig.m_fontSize + m_iLineSpacing;
					alignX = m_position.GetX();
					//lineHeight = 0;
				}
			}


			LetterNodePtr letterNode = m_letterNodes[i];
			if(!letterNode->IsColorInit())
			{
				letterNode->SetColor(m_color);
			}
			const nb::System::Color & letterColor = letterNode->GetColor();

			float    xStart = (float)(int)alignX;
			float    yStart = (float)(int)alignY;
			float    zStart = (float)(int)alignZ;

			float    h = float(letterDefinition->m_y1 - letterDefinition->m_y0);
			float    w = float(letterDefinition->m_x1 - letterDefinition->m_x0);
			float    offsetY = (float(h) - float(letterDefinition->m_offsetY));

			m_fontVertex[index + 0].x = xStart;
			m_fontVertex[index + 0].y = yStart  - h + offsetY;
			m_fontVertex[index + 0].z = zStart;
			m_fontVertex[index + 0].u = (float)letterDefinition->m_x0 / m_textureWidth;
			m_fontVertex[index + 0].v = (float)letterDefinition->m_y0 / m_textureHeight;
			m_fontVertex[index + 0].w = 1;
			m_fontVertex[index + 0].r = letterColor.GetRed();
			m_fontVertex[index + 0].g = letterColor.GetGreen();
			m_fontVertex[index + 0].b = letterColor.GetBlue();
			m_fontVertex[index + 0].a = letterColor.GetAlpha();
			//m_fontVertex[index + 0].color = CELL::Rgba4Byte(letterColor.GetRed(),letterColor.GetGreen(),letterColor.GetBlue(),letterColor.GetAlpha());

			m_fontVertex[index + 1].x = xStart + w;
			m_fontVertex[index + 1].y = yStart  - h + offsetY;
			m_fontVertex[index + 1].z = zStart;
			m_fontVertex[index + 1].u = (float)letterDefinition->m_x1 / m_textureWidth;
			m_fontVertex[index + 1].v = (float)letterDefinition->m_y0 / m_textureHeight;
			m_fontVertex[index + 1].w = 1;
			m_fontVertex[index + 1].r = letterColor.GetRed();
			m_fontVertex[index + 1].g = letterColor.GetGreen();
			m_fontVertex[index + 1].b = letterColor.GetBlue();
			m_fontVertex[index + 1].a = letterColor.GetAlpha();
			//m_fontVertex[index + 1].color = CELL::Rgba4Byte(letterColor.GetRed(),letterColor.GetGreen(),letterColor.GetBlue(),letterColor.GetAlpha());

			m_fontVertex[index + 2].x = xStart + w;
			m_fontVertex[index + 2].y = yStart + offsetY;
			m_fontVertex[index + 2].z = zStart;
			m_fontVertex[index + 2].u = (float)letterDefinition->m_x1 / m_textureWidth;
			m_fontVertex[index + 2].v = (float)letterDefinition->m_y1 / m_textureHeight;
			m_fontVertex[index + 2].w = 1;
			m_fontVertex[index + 2].r = letterColor.GetRed();
			m_fontVertex[index + 2].g = letterColor.GetGreen();
			m_fontVertex[index + 2].b = letterColor.GetBlue();
			m_fontVertex[index + 2].a = letterColor.GetAlpha();
			//m_fontVertex[index + 2].color =  CELL::Rgba4Byte(letterColor.GetRed(),letterColor.GetGreen(),letterColor.GetBlue(),letterColor.GetAlpha());

			m_fontVertex[index + 3].x = xStart;
			m_fontVertex[index + 3].y = yStart  - h + offsetY;
			m_fontVertex[index + 3].z = zStart;
			m_fontVertex[index + 3].u = (float)letterDefinition->m_x0 / m_textureWidth;
			m_fontVertex[index + 3].v = (float)letterDefinition->m_y0 / m_textureHeight;
			m_fontVertex[index + 3].w = 1;
			m_fontVertex[index + 3].r = letterColor.GetRed();
			m_fontVertex[index + 3].g = letterColor.GetGreen();
			m_fontVertex[index + 3].b = letterColor.GetBlue();
			m_fontVertex[index + 3].a = letterColor.GetAlpha();
			//m_fontVertex[index + 3].color =  CELL::Rgba4Byte(letterColor.GetRed(),letterColor.GetGreen(),letterColor.GetBlue(),letterColor.GetAlpha());

			m_fontVertex[index + 4].x = xStart + w;
			m_fontVertex[index + 4].y = yStart + offsetY;
			m_fontVertex[index + 4].z = zStart;
			m_fontVertex[index + 4].u = (float)letterDefinition->m_x1 / m_textureWidth;
			m_fontVertex[index + 4].v = (float)letterDefinition->m_y1 / m_textureHeight;
			m_fontVertex[index + 4].w = 1;
			m_fontVertex[index + 4].r = letterColor.GetRed();
			m_fontVertex[index + 4].g = letterColor.GetGreen();
			m_fontVertex[index + 4].b = letterColor.GetBlue();
			m_fontVertex[index + 4].a = letterColor.GetAlpha();
			//m_fontVertex[index + 4].color =  CELL::Rgba4Byte(letterColor.GetRed(),letterColor.GetGreen(),letterColor.GetBlue(),letterColor.GetAlpha());

			m_fontVertex[index + 5].x = xStart;
			m_fontVertex[index + 5].y = yStart + offsetY;
			m_fontVertex[index + 5].z = zStart;
			m_fontVertex[index + 5].u = (float)letterDefinition->m_x0 / m_textureWidth;
			m_fontVertex[index + 5].v = (float)letterDefinition->m_y1 / m_textureHeight;
			m_fontVertex[index + 5].w = 1;
			m_fontVertex[index + 5].r = letterColor.GetRed();
			m_fontVertex[index + 5].g = letterColor.GetGreen();
			m_fontVertex[index + 5].b = letterColor.GetBlue();
			m_fontVertex[index + 5].a = letterColor.GetAlpha();

			letterNode->Init(&m_fontVertex[index], letterDefinition, m_vertexVbo, index * sizeof(LetterNode::FontVertex1), sizeof(LetterNode::FontVertex1));
			index += 6;

			lastOffset = std::max<int>(lastOffset, offsetY);
			alignX += letterDefinition->m_x1 - letterDefinition->m_x0 + m_iLetterSpacing;
			if(m_stretchMode == TextSurface::StretchWidth)
			{
				maxXPos = std::max<int>(alignX, maxXPos);
			}
	
		}

		m_size.SetHeight(alignY - m_position.GetY() + lastOffset);
		m_size.SetWidth(maxXPos - m_position.GetX());
		if(m_fontVertex.size() > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER,m_vertexVbo);
			glBufferData(GL_ARRAY_BUFFER,m_fontVertex.size() * sizeof(LetterNode::FontVertex1), &m_fontVertex[0].x,GL_STREAM_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER,0);
		}
	}

	inline void SetFontSize(float fontSize)
	{
// 		m_ttfConfig.m_fontSize = fontSize;
// 		m_fontAtlas = FontCache()->GetFontAtlasTTF(&m_ttfConfig);
		if(!m_bIsInit) return;
		PrepareText();
		AlignText();
	}

	inline void SetFontName(std::string fontName)
	{
// 		m_ttfConfig.m_fontFilePath = fontName;
// 		m_fontAtlas = FontCache()->GetFontAtlasTTF(&m_ttfConfig);
		if(!m_bIsInit) return;
		PrepareText();
		AlignText();
	}

	void SetStretchMode(TextSurface::StretchMode stretchMode)
	{
		m_stretchMode = stretchMode;
	}

	void SetFontNameAndSize(std::string fontName, float fontSize)
	{
		m_ttfConfig.m_fontFilePath = fontName;
		m_ttfConfig.m_fontSize = fontSize;
//		m_fontAtlas = FontCache()->GetFontAtlasTTF(&m_ttfConfig);
		if(!m_bIsInit) return;
		PrepareText();
		AlignText();
	}

public:
	TextSurface::StretchMode m_stretchMode;
//	RectangleSurfacePtr m_frame;
	//int m_fontSize;
	TTFConfig m_ttfConfig;
	TextSurface * m_owner;
	bool m_bIsInit;
	nb::System::Size m_size;
	std::vector<LetterNode::FontVertex1> m_fontVertex;
	FontAtlasPtr m_fontAtlas;
	int m_iLetterSpacing;
	int m_iLineSpacing;
	std::wstring m_sText;
	nb::System::Color m_color;
	nb::System::Point3D m_position;
	std::vector<LetterNodePtr> m_letterNodes;
	GLuint m_vertexVbo;
	FontGlesProgramStatePtr m_program;
};


TextSurface::TextSurface(const TTFConfig & config)
{
	m_imp = new TextSurfaceImp(config, this);
}

TextSurface::TextSurface(const std::wstring& sText, const Point3D& position, const nb::System::Color& color, const TTFConfig & config)
{
	m_imp = new TextSurfaceImp(sText, position, color, config, this);
}

TextSurface::~TextSurface()
{
	delete m_imp;
}


unsigned int UTF8StrToUnicode(const char*UTF8String, unsigned int UTF8StringLength, wchar_t *OutUnicodeString, unsigned int UnicodeStringBufferSize)
{
	unsigned int UTF8Index = 0;
	unsigned int UniIndex = 0;

	while(UTF8Index < UTF8StringLength)
	{
		unsigned char UTF8Char = UTF8String[UTF8Index];
		if(UnicodeStringBufferSize != 0 && UniIndex >= UnicodeStringBufferSize)
			break;

		if((UTF8Char & 0x80) == 0) 
		{
			const unsigned int cUTF8CharRequire = 1;
			// UTF8\D7\D6\C2벻\D7\E3
			if(UTF8Index + cUTF8CharRequire > UTF8StringLength)
				break;

			if(OutUnicodeString)
			{
				wchar_t &WideChar = OutUnicodeString[UniIndex]; 
				WideChar = UTF8Char;
			}
			UTF8Index++;
		} 
		else if((UTF8Char & 0xE0) == 0xC0)  ///< 110x-xxxx 10xx-xxxx
		{
			const unsigned int cUTF8CharRequire = 2;
			// UTF8\D7\D6\C2벻\D7\E3
			if(UTF8Index + cUTF8CharRequire > UTF8StringLength)
				break;

			if(OutUnicodeString)
			{
				wchar_t &WideChar = OutUnicodeString[UniIndex]; 
				WideChar  = (UTF8String[UTF8Index + 0] & 0x3F) << 6;
				WideChar |= (UTF8String[UTF8Index + 1] & 0x3F);
			}
			UTF8Index += cUTF8CharRequire;
		}
		else if((UTF8Char & 0xF0) == 0xE0)  ///< 1110-xxxx 10xx-xxxx 10xx-xxxx
		{
			const unsigned int cUTF8CharRequire = 3;
			// UTF8\D7\D6\C2벻\D7\E3
			if(UTF8Index + cUTF8CharRequire > UTF8StringLength)
				break;

			if(OutUnicodeString)
			{
				wchar_t& WideChar = OutUnicodeString[UniIndex]; 

				WideChar  = (UTF8String[UTF8Index + 0] & 0x1F) << 12;
				WideChar |= (UTF8String[UTF8Index + 1] & 0x3F) << 6;
				WideChar |= (UTF8String[UTF8Index + 2] & 0x3F);
			}
			UTF8Index += cUTF8CharRequire;
		} 
		else if((UTF8Char & 0xF8) == 0xF0)  ///< 1111-0xxx 10xx-xxxx 10xx-xxxx 10xx-xxxx 
		{
			const unsigned int cUTF8CharRequire = 4;
			// UTF8\D7\D6\C2벻\D7\E3
			if(UTF8Index + cUTF8CharRequire > UTF8StringLength)
				break;

			if(OutUnicodeString)
			{
				wchar_t& WideChar = OutUnicodeString[UniIndex]; 

				WideChar  = (UTF8String[UTF8Index + 0] & 0x0F) << 18;
				WideChar  = (UTF8String[UTF8Index + 1] & 0x3F) << 12;
				WideChar |= (UTF8String[UTF8Index + 2] & 0x3F) << 6;
				WideChar |= (UTF8String[UTF8Index + 3] & 0x3F);
			}
			UTF8Index += cUTF8CharRequire;
		} 
		else ///< 1111-10xx 10xx-xxxx 10xx-xxxx 10xx-xxxx 10xx-xxxx 
		{
			const unsigned int cUTF8CharRequire = 5;
			// UTF8\D7\D6\C2벻\D7\E3
			if(UTF8Index + cUTF8CharRequire > UTF8StringLength)
				break;

			if(OutUnicodeString)
			{
				wchar_t& WideChar = OutUnicodeString[UniIndex]; 

				WideChar  = (UTF8String[UTF8Index + 0] & 0x07) << 24;
				WideChar  = (UTF8String[UTF8Index + 1] & 0x3F) << 18;
				WideChar  = (UTF8String[UTF8Index + 2] & 0x3F) << 12;
				WideChar |= (UTF8String[UTF8Index + 3] & 0x3F) << 6;
				WideChar |= (UTF8String[UTF8Index + 4] & 0x3F);
			}
			UTF8Index += cUTF8CharRequire;
		}
		UniIndex++;
	}

	return UniIndex;
}

std::wstring String2WString(const std::string &sString)
{
	char *pUtf8 = (char *)sString.data();
	unsigned int nUtf8Len = strlen(pUtf8);

	unsigned int nUnicodeLen = UTF8StrToUnicode(pUtf8, nUtf8Len, NULL, 0);
	wchar_t *pUnicode = new wchar_t[nUnicodeLen + 1];

	UTF8StrToUnicode(pUtf8, nUtf8Len, pUnicode, nUnicodeLen);

	pUnicode[nUnicodeLen] = 0;
	std::wstring wsRet = pUnicode;
	delete []pUnicode;

	return wsRet;
}

void TextSurface::SetText(const nb::System::String & sText)
{

	Stream stream = sText.ToUtf8();
	const char *ch = stream.GetData();
	m_imp->SetText(String2WString(ch));
}

void TextSurface::SetColor(const nb::System::Color & color)
{
	m_imp->SetColor(color);
}

void TextSurface::SetPosition(const Point3D & position)
{
	m_imp->SetPosition(position);
}

void TextSurface::OnDraw(/*const Matrix4x4 * matProj*/)
{
//	m_imp->OnDraw(matProj);
}

LetterNodePtr TextSurface::GetLetter(int iIndex)
{
	std::vector<LetterNodePtr> letters = m_imp->GetLetters();
	if(iIndex >= 0 && iIndex < letters.size())
	{
		return letters[iIndex];
	}
	//printf out error
	return NULL;
}

void TextSurface::SetStretchMode(StretchMode stretchMode)
{
	m_imp->SetStretchMode(stretchMode);
}


void TextSurface::SetContentSize(const nb::System::Size & size)
{
	m_imp->SetContentSize(size);
}

void TextSurface::SetLetterSpacing(int letterSpacing)
{
	m_imp->SetLetterSpacing(letterSpacing);
}

void TextSurface::SetLineSpacing(int lineSpacing)
{
	m_imp->SetLineSpacing(lineSpacing);
}

const std::wstring & TextSurface::GetText()
{
	return m_imp->GetText();
}

void TextSurface::SetFontSize(float fontSize)
{
	m_imp->SetFontSize(fontSize);
}

void TextSurface::SetFontName(std::string fontName)
{
	m_imp->SetFontName(fontName);
}

void TextSurface::SetFontNameAndSize(std::string fontName, float fontSize)
{
	m_imp->SetFontNameAndSize(fontName, fontSize);
}

}}}
