/*******************************************************
**	ImageSource
**
**		图片源
**	
**	
**		由路径加载的位图源，
**	
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "../core/Property.h"
#include "../core/DependencyObject.h"

namespace nb{
class Bitmap;

class NB_API ImageSource : public DependencyObject
{
public:
	ImageSource();
	ImageSource(const std::string &uri);

	float width() const;
	float heigth() const;

	static DependencyProperty				BmProperty();	//位图的依赖属性
	
};

}
