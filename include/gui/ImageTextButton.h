#pragma once
#include "ImageButton.h"

namespace nb{ namespace gui{

class NB_API ImageTextButton : public ImageButton
{
public:
	ImageTextButton();
	virtual ~ImageTextButton();

public:
	nb::core::Property_rw<std::string>		Text;

};


}}
