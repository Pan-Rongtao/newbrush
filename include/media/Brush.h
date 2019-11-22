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
#include "../core/Point.h"
#include "../core/Color.h"
#include "../core/Property.h"
#include "../core/DependencyObject.h"
#include "../media/ImageSource.h"

namespace nb{

class NB_API Brush : public DependencyObject
{
public:
	virtual ~Brush() = default;

	Property_rw<float>			Opacity;			//不透明度
	static DependencyProperty	OpacityProperty();	//不透明度依赖属性

protected:
	Brush();

};

}
