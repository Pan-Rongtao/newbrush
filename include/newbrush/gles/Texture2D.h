/*******************************************************
**	Texture2D
**
**	2D纹理
**	
**	是所有2D纹理的基类，2D纹理应用于2D坐标映射。
**	
**	子类有TextureMipmap、CompressedTexture和 BlendTexture
**	
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include <string>
#include "newbrush/gles/Texture.h"

namespace nb{

class NB_API Texture2D : public Texture
{
public:
	//构建一个2D纹理对象，它不包含任何数据，
	//它的纹理环绕方式为WrappingMode::WrappingMode_Repeat，它的纹理过滤方式为TextureFilter::Point
	Texture2D();

	//从一个以存在的id构建Texture2D，必须保证id未被释放
	Texture2D(uint32_t id);

	//构建一个2D纹理对象，它的宽高为width, height
	Texture2D(unsigned int width, unsigned int height);

	virtual ~Texture2D() = default;

	//激活当前纹理，在调用Gles Api的前置动作，
	//表示之后的gl操作都是针对当前纹理。在每次的Gles纹理操作都应该调用此函数
	virtual void bind() override;
	virtual void unbind() override;

	//设置纹理环绕方式
	virtual void setWrapping(const TextureWrapping &wrapping) override;

	//设置纹理过滤方式，假若不显示设置，将采用默认的过滤方式TextureFilter::Default
	virtual void setFilter(const TextureFilter &filter) override;

	//上传数据到GPU
	//glFormat：GL_ALPHA,GL_RGB,GL_RGBA,GL_LUMINANCE, GL_LUMINANCE_ALPHA等
	//glType：GL_UNSIGNED_BYTE,GL_UNSIGNED_SHORT_5_6_5,GL_UNSIGNED_SHORT_4_4_4_4,GL_UNSIGNED_SHORT_5_5_5_1等
	void update(const unsigned char *data, int width, int height, int glFormat, int glType);

	//纹理支持的最大尺寸，不同的GPU将返回不同的值；MaxWidth和MaxHeight一般是一样的值
	//注意：此接口依赖于egl的初始化，需在egl初始化完成后才能够得到正确的值，不然将返回0
	static int maxWidthSupported();
	static int maxHeightSupported();

	//获取像素高
	unsigned int width() const;

	//获取像素宽
	unsigned int height() const;

private:
	unsigned int		m_width;
	unsigned int		m_height;
};

}
