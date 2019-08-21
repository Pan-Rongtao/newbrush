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
#include "ImageSource.h"
#include "Stretch.h"

namespace nb{ namespace gui {

class NB_API Image : public UIElement
{
public:
	Image();
	virtual ~Image() = default;
	Image(const Image &other) = delete;
	void operator = (const Image &other) = delete;

public:
	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

	Property_rw<shared_ptr<ImageSource>>	Source;
	Property_rw<StretchE>					Stretch;

	static const DependencyProperty			SourceProperty();
	static const DependencyProperty			StretchProperty();


protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	Size	m_availableSize;
};


}}
