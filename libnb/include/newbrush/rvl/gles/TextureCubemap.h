﻿/*******************************************************
**	TextureMipmap
**
**	立方体映射纹理
**	
**		一种用于立方体坐标映射的纹理，需要指定六面数据。
**
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include <string>
#include "newbrush/rvl/gles/Texture.h"

namespace nb{

class NB_API TextureCubemap : public Texture
{
public:
	//构建一个空的Cubmap
	TextureCubemap();
	~TextureCubemap() = default;

	//重写bind/unbind
	virtual void bind() override;
	virtual void unbind() override;

	//设置纹理环绕方式
	virtual void setWrapping(const TextureWrapping &wrapping) override;

	//设置纹理过滤方式，假若不显示设置，将采用默认的过滤方式TextureFilter::Default
	virtual void setFilter(const TextureFilter &filter) override;

	//更新六面数据
	//右、左、底、顶、后、前
	//异常：index >= 6
	void update(unsigned int index, const unsigned char *data, int width, int height, int glFormat, int glType);

};


}