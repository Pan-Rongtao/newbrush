#pragma once
#include <string>
#include <map>
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
	//构建一个字体，路径为path，尺寸为16
	Font(const std::string &path);

	//构建一个字体，路径为path，尺寸为fontSize
	Font(const std::string &path, uint32_t fontSize);
	~Font();

	//
	std::string path() const;

	//字体名字
	std::string familyName() const;

	//字体大小，范围[8, 72]，越界将产生异常
	void setSize(uint32_t fontSize);
	uint32_t size() const;

	GlyphInfo getGlyphInfo(wchar_t unicode);

private:
	uint32_t		m_fontSize;
	std::string		m_path;
	FT_FaceRec_		*m_face;
};


class NB_API Fonts
{
public:
	static constexpr char *MicrosoftYaHei		= "Microsoft YaHei";	//微软雅黑
	static constexpr char *SimSun				= "SimSun";				//宋体
	static constexpr char *STKaiti				= "STKaiti";			//华文楷体

	//从名字中获取一个字体，如果没有，返回空
	static std::shared_ptr<Font> getFont(const std::string &name);

	//获取已存在的字体
	static std::map<std::string, std::shared_ptr<Font>> systemFonts();

};

} }