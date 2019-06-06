#pragma once
#include <string>
#include "../core/Def.h"

struct FT_FaceRec_;
struct FT_BitmapGlyphRec_;

namespace nb{ namespace media{

	struct GlyphInfo
	{
		int				left;
		int				top;
		int				advancex;
		int				advancey;
		unsigned int    bm_width;
		unsigned int    bm_height;
		int             bm_pitch;
		unsigned char*  bm_buffer;
	};

class NB_API Font
{
public:
	//构建一个字体，路径为fontPath，尺寸为16
	Font(const std::string &fontPath);

	//构建一个字体，路径为fontPath，尺寸为fontSize
	Font(const std::string &fontPath, uint32_t fontSize);
	~Font();

	//字体名字
	std::string name() const;

	//字体大小，范围[8, 72]，越界将产生异常
	void setSize(uint32_t fontSize);
	uint32_t size() const;

	GlyphInfo getGlyphInfo(wchar_t unicode);

private:
	uint32_t		m_fontSize;
	FT_FaceRec_		*m_face;
};

} }