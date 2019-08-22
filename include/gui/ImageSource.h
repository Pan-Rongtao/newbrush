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
#include "../gui/Property.h"
#include "../gui/DependencyObject.h"

namespace nb{
class Bitmap;

namespace gui{

class NB_API ImageSource : public DependencyObject
{
public:
	ImageSource();
	ImageSource(const std::string &uri);

	float width() const;
	float heigth() const;

	Property_rw<std::shared_ptr<Bitmap>> 	Bm;				//位图
	static const DependencyProperty			BmProperty();	//位图的依赖属性
	
};

}}
