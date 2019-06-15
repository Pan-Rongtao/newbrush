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

	nb::core::Property_rw<std::shared_ptr<ImageSource>>		Source;
	nb::core::Property_rw<nb::gui::StretchE>				Stretch;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

private:

	void onSourceChanged(const std::shared_ptr<ImageSource> &_old, const std::shared_ptr<ImageSource> &_new);
	void onStretchChanged(const nb::gui::StretchE &_old, const nb::gui::StretchE &_new);

	core::Size	m_availableSize;
};


}}
