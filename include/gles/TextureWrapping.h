#pragma once
#include "math/Vec4.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT TextureWrapping
{
public:
	//纹理环绕方式
	enum WrappingMode
	{
		WrappingMode_Repeat,			//重复
		WrappingMode_Mirrored_Repeat,	//镜像重复
		WrappingMode_Clamp_To_Edge,		//边缘延伸
		WrappingMode_Clamp_To_Border,	//用户颜色边缘延伸
	};

public:
	//构建一个纹理环绕方式，它的S轴和T轴都是WrappingMode_Repeat
	TextureWrapping();

	//构建一个纹理环绕方式，它的S轴为s，它的T轴为t
	TextureWrapping(WrappingMode s, WrappingMode t);

	//构建一个纹理环绕方式，它的S轴是s，它的T轴是t，它的用户颜色边缘延伸是borderColor
	TextureWrapping(WrappingMode s, WrappingMode t, const nb::Math::Vec4 &borderColor);

	//获取S轴
	WrappingMode GetS() const;

	//获取T轴
	WrappingMode GetT() const;

public:
	//转到gl的值
	static int ToGlValue(WrappingMode wrapping);

private:
	WrappingMode	m_s;
	WrappingMode	m_t;
	nb::Math::Vec4	m_BorderColor;
};


}}}
