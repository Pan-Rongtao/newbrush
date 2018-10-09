#pragma once
#include "Button.h"
#include "ImageSource.h"

namespace nb{namespace gui{

class NB_API ImageButton : public nb::gui::Button
{
public:
	ImageButton();
	virtual ~ImageButton();

	nb::core::Property_rw<std::shared_ptr<ImageSource>>				NormalImage;
	nb::core::Property_rw<std::shared_ptr<nb::gui::ImageSource>>	PressImage;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) const;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) const;

private:

};

}}