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
#include "core/Object.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT VBO
{
public:
	//构建一个顶点缓存对象
	//异常：
	VBO();
	~VBO();

	//激活使用VBO，表示之后传输的数据都从此缓存得到
	void Active();

	//反激活VBO，表示不再由vbo缓存获得数据
	void Deactive();

	//缓存一块数据至Gpu，缓冲区将拥有空间bytes大小；如果原来已经有缓存，将先清除掉原来的空间
	//异常：bytes < 0
	void CacheDataToGpu(const float *data, int bytes);

	//获取缓存空间大小
	int GetBytes() const;

	//更新/提交新数据到缓冲区
	//异常：bytes小于0或者bytes+cacheOffset大于缓冲区对象创建时所指定的大小
	void UpdateCacheData(const float *data, int cacheOffset, int bytes);

private:
	unsigned int	m_glHandle;
	int				m_nBytes;
};

}}}
