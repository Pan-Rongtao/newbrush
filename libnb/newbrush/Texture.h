#pragma once
#include "newbrush/Bitmap.h"
#include "glm/glm.hpp"

namespace nb
{
//纹理环绕方式
enum class TextureWrappingE
{
	Repeat			= 0x2901,	//重复
	MirroredRepeat	= 0x8370,	//镜像重复
	ClampToEdge		= 0x812F,	//边缘延伸
	ClampToBorder	= 0xFFFF,	//用户颜色边缘延伸
};

//纹理过滤方式，依次向下，纹理细节表现质量越好，性能要求越大
//放大过滤只支持Point和Bilinear
//缩小过滤支持所有的过滤方式
enum class TextureFilterE
{
	Point			= 0x2600,	//最邻近过滤，指取最接近浮点的整型像素点位置
	Bilinear		= 0x2601,	//双线性过滤，对邻近的四个点进行线性插值算法，两个维度三次运算
	Trilinear		= 0x2703,	//三线性过滤。三线性过滤以双线性过滤为基础。会对pixel大小与texel大小最接近的两层Mipmap level分别进行双线性过滤，然后再对两层得到的结果进生线性插值。
	Anisotropic		= 0xFFFF,	//各向异性过滤，当需要贴图的三维表面平行于屏幕(viewport)，则是各向同性的。当要贴图的三维表面与屏幕有一定角度的倾斜，则是各向异性的。
};

//class Texture
class NB_API Texture
{
public:
	virtual ~Texture();

	unsigned id() const;

	//激活当前采用单元
	void active();

	//纹理采样单元，默认0
	void setSamplerUnit(unsigned unit);
	unsigned samplerUnit();

	//绑定/解除当前纹理
	virtual void bind() = 0;
	virtual void unbind() = 0;

	void activeAndBind();

	//设置纹理环绕方式
	virtual void setWrappingS(TextureWrappingE wrapping) = 0;
	virtual void setWrappingT(TextureWrappingE wrapping) = 0;
	virtual TextureWrappingE wrappingS() const = 0;
	virtual TextureWrappingE wrappingT() const = 0;

	//纹理过滤方式
	virtual void setMagnifyFilter(TextureFilterE filter) = 0;
	virtual void setNarrowFilter(TextureFilterE filter) = 0;
	virtual TextureFilterE magnifyFilter() const = 0;
	virtual TextureFilterE narrowFilter() const = 0;

protected:
	Texture();

	unsigned m_samplerUnit;
	unsigned m_handle;
};

///////////////////
class NB_API Texture2D : public Texture
{
public:
	Texture2D();
	Texture2D(const std::string &path);

	virtual ~Texture2D() = default;

	virtual void bind() override;
	virtual void unbind() override;
	virtual void setWrappingS(TextureWrappingE wrapping) override;
	virtual void setWrappingT(TextureWrappingE wrapping) override;
	virtual TextureWrappingE wrappingS() const override;
	virtual TextureWrappingE wrappingT() const override;
	virtual void setMagnifyFilter(TextureFilterE filter) override;
	virtual void setNarrowFilter(TextureFilterE filter) override;
	virtual TextureFilterE magnifyFilter() const override;
	virtual TextureFilterE narrowFilter() const override;

	//上传数据到GPU
	void update(const std::string &path);
	void update(ref<Bitmap> bm);

	void genMipmap();

	float width() const;
	float height() const;

private:
	float m_width;
	float m_height;
};

/////////////////////
class NB_API TextureCubemap : public Texture
{
public:
	//构建一个空的Cubmap
	TextureCubemap();
	~TextureCubemap() = default;

	virtual void bind() override;
	virtual void unbind() override;
	virtual void setWrappingS(TextureWrappingE wrapping) override;
	virtual void setWrappingT(TextureWrappingE wrapping) override;
	virtual TextureWrappingE wrappingS() const override;
	virtual TextureWrappingE wrappingT() const override;
	virtual void setMagnifyFilter(TextureFilterE filter) override;
	virtual void setNarrowFilter(TextureFilterE filter) override;
	virtual TextureFilterE magnifyFilter() const override;
	virtual TextureFilterE narrowFilter() const override;

	//更新六面数据(右、左、底、顶、后、前)
	void update(const std::string & top, const std::string & bottom, const std::string & left, const std::string & right, const std::string & front, const std::string & back);

};

struct NB_API TextureFrame
{
	ref<Texture2D> texture;
	glm::vec2 offset;
	glm::vec2 size;
	bool rotated;
	glm::vec2 trimmedSize;
};

class NB_API TextureLibrary
{
public:
	static ref<Texture2D> addTexture2D(const std::string &name, const std::string &imagePath);
	static void addTextureAtlas(const std::string &name, const std::string &imagePath, const std::string &cfgPath);
	static void addTextureCubemap(const std::string &name, const std::string & top, const std::string & bottom, const std::string & left, const std::string & right, const std::string & front, const std::string & back);

	static ref<Texture2D> getTexture2D(const std::string &name);
	static const TextureFrame &getFrameFromTextureAtlas(const std::string &name, const std::string &frameName);
	static ref<TextureCubemap> getTextureCubemap(const std::string &name);

};


}
