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
	Image(const std::shared_ptr<ImageSource> &source);
	Image(const std::shared_ptr<ImageSource> &source, nb::gui::Stretch stretch);
	virtual ~Image();

public:
	nb::core::Property_rw<std::shared_ptr<ImageSource>>		Source;
	nb::core::Property_rw<nb::gui::Stretch>					Stretch;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) const;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) const;

private:
	Image(const Image &other); //hp暂时改为公有的
	void operator = (const Image &other);

	void onSourceChanged(const std::shared_ptr<ImageSource> &_old, const std::shared_ptr<ImageSource> &_new);
	void onStretchChanged(const nb::gui::Stretch &_old, const nb::gui::Stretch &_new);
};


}}
