/*******************************************************
**	Configure
**
**	GL配置类
**		Configure是描述OpenGL渲染上下文
**	颜色通道属性、位深、以及采样属性的数据结构
**	
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "../core/Def.h"

namespace nb{ namespace gl{

class NB_API Configure
{
public:
	//构建一个配置，它基于display，属性为attributes
	Configure(const int *attributes);

	//获取属性
	int *attributes() const;

	//句柄
	void *handle() const;

public:
	//系统推荐的配置最大数
	static uint32_t systemRecommendMaxSupportCount();

	//从系统推荐中构建
	static Configure fromSystemRecommend(uint32_t index);

private:
	Configure();
	void						*m_handle;
};

}}
