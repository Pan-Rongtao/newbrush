#pragma once
#include "core/Object.h"
#include "system/Color.h"
#include "system/Point3D.h"

namespace nb{ namespace gl{ namespace Gles{

//class LetterNodeImp;
class LetterNode;
class FontLetterDefinition;
class TextSurfaceImp;
typedef nbObjectPtrDerive<LetterNode, Core::RefObjectPtr> LetterNodePtr;


class NB_EXPORT LetterNode : public Core::RefObject
{
public:
private:
	class  FontVertex1 : public RefObject
	{
	public:
		float x, y, z;
		float u, v, w;
	    unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
	};

	friend class TextSurfaceImp;
	static LetterNodePtr Create(wchar_t letter);
public:
	void SetColor(const nb::System::Color & color);
	const nb::System::Color &  GetColor(){ return m_color; }
protected:
	LetterNode(wchar_t letter);
	void Init(FontVertex1 * vertexData, const FontLetterDefinition * letterDefinition, unsigned int vertexVbo, unsigned int offset, unsigned int stride);
	bool IsColorInit() { return m_bIsColorInit; }
	//void OnDraw(const Matrix4x4* matProj);

	~LetterNode(void);
private:
	bool m_bIsColorInit;
	bool m_bIsInit;
	nb::System::Color m_color;
	unsigned int m_stride;
	unsigned int m_offset;
	unsigned int m_vertexVbo;
	FontVertex1 * m_VertexData;
	wchar_t	m_letter;
	const FontLetterDefinition * m_letterDefinition;
	typedef nbObjectPtrDerive<FontVertex1, Core::RefObjectPtr> FontVertex1Ptr;
	//LetterNodeImp * m_imp;
};

}}}
