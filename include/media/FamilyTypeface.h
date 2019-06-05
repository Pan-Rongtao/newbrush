#pragma once
#include <string>
#include "../core/Def.h"

struct FT_FaceRec_;
struct FT_BitmapGlyphRec_;

namespace nb{ namespace media{

class NB_API FamilyTypeface
{
public:
	FamilyTypeface(const std::string &fontPath);
	~FamilyTypeface();

	//字体名字
	std::string getFontName() const;

	//字体大小，范围[8, 72]，越界将产生异常
	void setFontSize(uint32_t fontSize);
	int getFontSize() const;

	FT_BitmapGlyphRec_ *loadChar(wchar_t unicode);

	FT_FaceRec_ *get();

private:
	int				m_fontSize;
	
	FT_FaceRec_		*m_face;
};

} }