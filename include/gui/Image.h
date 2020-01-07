/*******************************************************
**	Image
**
**	
**	
**		提供显示图片的一种基础控件
**			
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "UIElement.h"
#include "Stretch.h"

namespace nb{
class ImageSource;
namespace gui{

class NB_API Image : public UIElement
{
public:
	Image();
	virtual ~Image() = default;

	static DependencyProperty				SourceProperty();	//源的依赖属性
	static DependencyProperty				StretchProperty();	//伸缩方式的依赖属性

	virtual void onRender(Viewport2D & drawContext) override;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;

	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	Size	m_availableSize;
};


}}
