/*******************************************************
**	VBO
**
**	vertex buffer object
**	
**	顶点缓存对象，是一种常用的提升与GPU数据通信效率的技术。它能够
**	把顶点数据缓存在GPU中以致不必每次都向GPU提交数据
**		
**		潘荣涛
**	
********************************************************/
#pragma once
#include "../core/Def.h"

namespace nb{ namespace gl{

class NB_API VBO
{
public:
	//构建一个顶点缓存对象
	//异常：
	VBO();
	~VBO();

	//激活使用VBO，表示之后传输的数据都从此缓存得到
	void active();

	//反激活VBO，表示不再由vbo缓存获得数据
	void deactive();

	//缓存一块数据至Gpu，缓冲区将拥有空间bytes大小；如果原来已经有缓存，将先清除掉原来的空间
	//异常：bytes < 0
	void cacheDataToGpu(const float *data, int bytes);

	//获取缓存空间大小
	int bytes() const;

	//更新/提交新数据到缓冲区
	//异常：size小于0或者size+cacheOffset大于缓冲区对象创建时所指定的大小
	void updateCacheData(const float *data, int cacheOffset, int size);

private:
	unsigned int	m_glHandle;
	int				m_nBytes;
};

}}
