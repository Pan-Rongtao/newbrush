/*******************************************************
**	TextureFilter
**
**	纹理纹理过滤
**	
**		纹理过滤的需要是由于纹理在映射到不同表面上，纹理尺寸与表面尺寸
**	不一致从而导致放大或缩小所参数的失真现象。
**
**		不同的情况设置恰当的过滤方式可以解决一些现实问题。
**	比如Bilinear消除马赛克现象；而需要经常做移动的表面可
**	以设置过滤方式为Trilinear，来消除闪烁问题
**	
**		过滤方式有两个维度：放大过滤和缩小过滤
**
**		潘荣涛
**	
********************************************************/

#pragma once
#include "system/Global.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT TextureFilter
{
public:
	//纹理过滤方式，依次向下，纹理细节表现质量越好，性能要求越大
	//放大过滤只支持Point和Bilinear
	//缩小过滤支持所有的过滤方式
	enum Filter
	{
		Point = 0,						//最邻近过滤，指取最接近浮点的整型像素点位置
		Bilinear,						//双线性过滤，对邻近的四个点进行线性插值算法，两个维度三次运算
		Trilinear,						//三线性过滤。三线性过滤以双线性过滤为基础。会对pixel大小与texel大小最接近的两层Mipmap level分别进行双线性过滤，然后再对两层得到的结果进生线性插值。
		Anisotropic,					//各向异性过滤，当需要贴图的三维表面平行于屏幕(viewport)，则是各向同性的。当要贴图的三维表面与屏幕有一定角度的倾斜，则是各向异性的。
	};

public:
	//构建一个纹理过滤方式，放大过滤和缩小过滤都使用Filter::Piont
	TextureFilter();

	//构建一个纹理过滤方式，放大过滤和缩小过滤都使用uniformFilter
	TextureFilter(Filter uniformFilter);

	//构建一个纹理过滤方式，放大过滤和缩小过滤都使用uniformFilter
	TextureFilter(Filter magnify, Filter narrow);

	//获取放大/缩小过滤方式
	Filter GetMagnifyFilter() const;
	Filter GetNarrowFilter() const;


public:
	//返回默认的过滤方式
	static TextureFilter Default();

	//获取gl值
	static int ToGlValue(Filter filter);

private:

	Filter	m_MagnifyFilter;
	Filter	m_NarrowFilter;
};

}}}
