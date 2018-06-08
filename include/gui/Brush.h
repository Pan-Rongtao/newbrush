/*******************************************************
**	Brush
**
**	画刷
**	
**	是所有画刷的基类
**	
**	子类有纯色画刷、渐变画刷、纹理画刷等
**	
**
**		潘荣涛
**	
********************************************************/

#pragma once
#include "core/Object.h"

namespace nb{ namespace Media{

class NB_EXPORT Brush : public nbObject
{
	NB_OBJECT_TYPE_DECLARE();

//public funs.
public:
	//设置透明度，范围为0.0~1.0，假如不在范围内，将取校正值
	void SetOpacity(float opacity);

	//获取透明度
	float GetOpacity() const;

	//矩阵变换相关
	

protected:
	Brush();
	Brush(float opacity);
	virtual ~Brush();

private:


	float	m_fOpacity;
};

typedef nbObjectPtrDerive<Brush, nbObjectPtr> BrushPtr;

}}
