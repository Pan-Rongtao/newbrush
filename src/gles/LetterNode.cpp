#include "gles/LetterNode.h"
#include "CELLMath.hpp"
#include "FontAtlas.h"
namespace nb{ namespace gl{ namespace Gles{

LetterNode::LetterNode(wchar_t letter)
: m_VertexData(NULL)
, m_letter(letter)
, m_letterDefinition(NULL)
, m_vertexVbo(0)
, m_offset(0)
, m_stride(0)
, m_bIsColorInit(false)
, m_bIsInit(false)
{
	//m_imp = new LetterNodeImp(letter, color, position, letterDefinition);
}

LetterNode::~LetterNode(void)
{
	//delete m_imp;
}

void LetterNode::SetColor(const nb::System::Color & color)
{
	m_color = color;
	m_bIsColorInit = true;

	if(!m_bIsInit) return;

	unsigned char newColor[] = 
	{
		color.GetRed(),
		color.GetGreen(),
		color.GetBlue(),
		color.GetAlpha()
	};
	glBindBuffer(GL_ARRAY_BUFFER,m_vertexVbo);
	for(int i = 0; i < 6; ++i)
	{
		glBufferSubData(GL_ARRAY_BUFFER,m_offset + sizeof(float) * 6 + i * m_stride, 4 * sizeof(unsigned char),newColor);
	}
	
	//m_imp->SetColor(color);
}

void LetterNode::Init(FontVertex1 * vertexData, const FontLetterDefinition * letterDefinition, unsigned int vertexVbo, unsigned int offset, unsigned int stride)
{
	m_VertexData = vertexData;
	m_letterDefinition = letterDefinition;
	m_vertexVbo = vertexVbo;
	m_offset = offset;
	m_stride = stride;
	m_bIsInit = true;
}

LetterNodePtr LetterNode::Create(wchar_t letter)
{
	LetterNode * letterNode = new LetterNode(letter);
	return letterNode;
}


}}}
