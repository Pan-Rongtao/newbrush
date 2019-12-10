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

	Property_rw<shared_ptr<ImageSource>>	Source;				//源
	Property_rw<StretchE>					Stretch;			//伸缩方式
	static DependencyProperty				SourceProperty();	//源的依赖属性
	static DependencyProperty				StretchProperty();	//伸缩方式的依赖属性

	virtual void onRender(std::shared_ptr<Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	Size	m_availableSize;
};


}}
