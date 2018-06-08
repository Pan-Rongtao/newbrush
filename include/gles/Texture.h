/*******************************************************
**	Texture
**
**	纹理
**	
**	是所有纹理的基类。
**
**		纹理是描述不同维度数据的数据结构，比如颜色数据，
**	亮度数据等。2D纹理可简单的理解为一个2维结构的像素数组。
**	
**		一般情况下，纹理需要绑定纹理处理单元，若不指定，将
**	绑定到默认的纹理处理单元上。
**
**		纹理在映射到表面时有可能被放大或者缩小，所以可以指定
**	所采用的纹理过滤方式
**	
**	子类有2D纹理（Texture2D）和 TextureCubemap
**	
**
**		潘荣涛
**	
********************************************************/

#pragma once
#include "gles/TextureWrapping.h"
#include "gles/TextureFilter.h"
#include "media/Bitmap.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Texture
{
public:
	enum PixelFormat
	{
		Format_Bpp8_Alpha = 0,
		Format_Bpp16_Rgb565,
		Format_Bpp24_Rgb888,
		Format_Bpp32_Rgb4444,
		Format_Bpp32_Rgb5551,
		Format_Bpp32_Rgba8888,
	};

public:
	//绑定当前纹理，表示之后的gl操作都是针对当前纹理。在每次的Gles纹理操作都应该调用此函数
	virtual void Bind() = 0;

	//解除纹理绑定
	virtual void Unbind() = 0;

	//设置纹理环绕方式
	virtual void SetTextureWrapping(const TextureWrapping &wrapping) = 0;

	//获取纹理环绕方式
	TextureWrapping &GetTextureWrapping();
	const TextureWrapping &GetTextureWrapping() const;

	//设置纹理过滤方式，假若不显示设置，将采用默认的过滤方式TextureFilter::Default
	virtual void SetTextureFilter(const TextureFilter &filter) = 0;

	//获取纹理过滤方式
	TextureFilter &GetTexureFilter();
	const TextureFilter &GetTexureFilter() const;


protected:
	Texture();
	virtual ~Texture();

	void BitmapFormatToGlFormat(nb::Media::Bitmap::PixelFormat bmFormat, int &glInteralFormat, int &glPixcelDepth) const;

	TextureWrapping		m_Wrapping;
	TextureFilter		m_Filter;
	unsigned int		m_TextureHandle;
};

}}}
