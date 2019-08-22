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
#include "../core/Color.h"
#include "../gui/Property.h"
#include "../gui/ImageSource.h"
#include "../gui/DependencyObject.h"

namespace nb{
namespace gui{

//class Brush
class NB_API Brush : public DependencyObject
{
protected:
	Brush();
	Brush(float opacity);
	virtual ~Brush() = default;

	Property_rw<float>			Opacity;			//不透明度
	static DependencyProperty	OpacityProperty();	//不透明度依赖属性

private:
	Brush(const Brush &other) = delete;
	void operator = (const Brush &other) = delete;

};

//class SolidColorBrush
class NB_API SolidColorBrush : public Brush
{
public:
	SolidColorBrush();
	explicit SolidColorBrush(const nb::Color &color);

	Property_rw<nb::Color>		Color;				//颜色
	static DependencyProperty	ColorProperty();	//颜色依赖属性
};

//class ImageBrush
class NB_API ImageBrush : public Brush
{
public:
	ImageBrush();
	explicit ImageBrush(std::shared_ptr<ImageSource> imgSource);

	Property_rw<std::shared_ptr<ImageSource>>	Source;				//源
	static DependencyProperty					SourceProperty();	//源依赖属性
};

}}
