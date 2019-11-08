#pragma once
#include <string>
#include <map>
#include "../core/Def.h"

struct FT_LibraryRec_;
struct FT_FaceRec_;
struct FT_BitmapGlyphRec_;

namespace nb{

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

	static FT_LibraryRec_ *getFT();

private:
	uint32_t		m_fontSize;
	std::string		m_path;
	FT_FaceRec_		*m_face;
	friend class GlyphMetrics;
};

class NB_API Fonts
{
public:
	//从名字中获取一个字体，如果没有，返回空
	//name：字体名称，形如"Microsoft YaHei", "SimSun", "STKaiti"等
	static std::shared_ptr<Font> getFont(const std::string &name);

	//获取已存在的字体
	static std::map<std::string, std::shared_ptr<Font>> systemFonts();

private:
	static void initSystemFonts();
	static std::map<std::string, std::shared_ptr<Font>> s_systemFonts;
};

}