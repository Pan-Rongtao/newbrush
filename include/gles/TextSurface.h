#pragma once
#include <string>
#include "system/Color.h"
#include "system/Point3D.h"
#include "system/Color.h"
#include "system/Size.h"
#include "system/String.h"
#include "gles/LetterNode.h"
#include "TTFConfig.h"

namespace nb{ namespace gl{ namespace Gles{

class TextSurfacePrivate;
class TextSurfaceImp;
class NB_EXPORT TextSurface/* : public Surface*/
{
public:
	friend class TextSurfacePrivate;

	enum StretchMode
	{
		StretchHeight,
		StretchWidth
	};
	TextSurface(const TTFConfig & config);

	TextSurface(const std::wstring& sText, const nb::System::Point3D& position, const nb::System::Color& color, const TTFConfig & config);

	~TextSurface();

	void SetText(const nb::System::String& sText);

	void SetColor(const nb::System::Color& color);

	void SetPosition(const nb::System::Point3D& position);

	void SetContentSize(const nb::System::Size & size);

	void SetStretchMode(StretchMode stretchMode);

	void SetLetterSpacing(int letterSpacing);

	void SetLineSpacing(int lineSpacing);

	void SetFontSize(float fontSize);

	void SetFontName(std::string fontName);

	void SetFontNameAndSize(std::string fontName, float fontSize);

	const std::wstring & GetText();

	virtual bool IsScreenPointInSurface(int absx, int absy) { return false; }
//	virtual Point3D MapFromWindow(const Point3D& vWorldVertex){return vWorldVertex;}

	LetterNodePtr GetLetter(int iIndex);

protected:
	virtual void OnDraw(/*const Matrix4x4* matProj*/);

private: 
	TextSurfaceImp *    m_imp;
};


//typedef nbObjectPtrDerive<TextSurface, SurfacePtr> TextSurfacePtr;

}}}
