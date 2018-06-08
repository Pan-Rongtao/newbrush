/*******************************************************
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
#include "core/Object.h"
#include "gles/Texture.h"

namespace nb{ namespace gl{ namespace Gles{

class TextureCubemap : public Texture
{
public:
	virtual void Bind();

	//设置纹理环绕方式
	virtual void SetTextureWrapping(const TextureWrapping &wrapping);

	//设置纹理过滤方式，假若不显示设置，将采用默认的过滤方式TextureFilter::Default
	virtual void SetTextureFilter(TextureFilter filter);


public:
	TextureCubemap();
	~TextureCubemap();
};


}}}
