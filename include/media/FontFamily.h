#pragma once
#include <string>
#include "../core/Def.h"

struct FT_LibraryRec_;
namespace nb{ namespace media{

class NB_API FontFamily
{
public:
	//构建一个FontFamily，它的路径为fontPath;
	FontFamily(const std::string &fontPath);

	//基准线
	void setBaseline(int bl);
	int getBaseline() const;

	//行间距
	void setLineSpacing(int ls);
	int getLineSpacing() const;

	static FT_LibraryRec_ *getFT();

private:
	int		m_baseline;
	int		m_lineSpacing;
};

}}