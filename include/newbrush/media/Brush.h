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
#include "newbrush/core/Point.h"
#include "newbrush/media/Color.h"
#include "newbrush/core/DependencyObject.h"
#include "newbrush/media/ImageSource.h"

namespace nb{

class NB_API Brush : public DependencyObject
{
public:
	virtual ~Brush() = default;

	static DependencyPropertyPtr OpacityProperty();	//不透明度依赖属性

protected:
	Brush();

};

using BrushPtr = std::shared_ptr<Brush>;

}
