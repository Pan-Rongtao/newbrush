/*******************************************************
**	TextureUnit
**
**	纹理（处理）单元
**	
**	纹理处理单元并不是纹理，它是处理GPU处理纹理贴图的模块
**		数量取决于显卡
**	
**	一般情况下，纹理不需要绑定多个纹理处理单元对象；
**	除非需要同时进行多纹理的采样
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "system/Global.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT TextureUnit
{
public:
	//构建一个默认纹理处理单元，GL_TEXTURE0
	TextureUnit();

	//根据编号返回，有效编号为0 ~ MaxCount-1
	explicit TextureUnit(int index);
	~TextureUnit();

	//纹理单元下标
	int GetIndex() const;

	//纹理单元地址
	int GlAddress() const;

	//激活当前纹理单元
	void Activate();

public:
	//返回纹理单元的最大数量，取决于显卡
	static int MaxCount();

	//返回默认的纹理单元对象
	static TextureUnit Default();

	//返回一个纹理单元有效编号为0 ~ MaxCount-1
	static TextureUnit FromIndex(int index);

	//构建一个纹理单元，glEnumUnitAddress传入GL_TEXTURE0~GL_TEXTURE31
	static TextureUnit FromGlAddress(int glEnumUnitAddress);

	//返回当前活动的纹理单元对象
	static TextureUnit Activated();

private:
	int		m_nAddress;
};
	
}}}
