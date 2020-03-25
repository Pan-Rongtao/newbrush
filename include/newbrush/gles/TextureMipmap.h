/*******************************************************
**	TextureMipmap
**
**	多级别纹理
**	
**		一种描述多种level层级集合的纹理对象。假设纹理源图像宽高为
**	32x16，则会保存32x16，16x8，8x4，4x2，2x1,1x1六种纹理。
**
**		对外部使用来说，不必考虑内部纹理内部选择的细节。
**	OpengGL会自动选择最为接近的尺寸，并按照指定的纹理过滤方式进行过滤
**
**	
**	该类型纹理在处理缩小纹理特别有用，可保证图像不过于失真；
**	或避免移动闪烁
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "newbrush/gles/Texture2D.h"

namespace nb{

class NB_API TextureMipmap : public Texture2D
{
public:
	//构建多级纹理
	void generate();

public:
	TextureMipmap(const Bitmap &bm);
	~TextureMipmap();
};

}