#pragma once

#include "Button.h"
#include "ImageSource.h"

class NB_EXPORT ImageButton : public nb::Gui::Button
{
	NB_OBJECT_TYPE_DECLARE();

public:
	ImageButton(void);
	virtual ~ImageButton(void);

	NB_X_OBJECT_PROPERTY_DECLARE(NormalImage, nb::Media::ImageSource);
	NB_X_OBJECT_PROPERTY_DECLARE(PressImage, nb::Media::ImageSource);

//	ImageSource * m_x;

private:
	void OnNormalImageChanged(nb::Core::PropertyValueChangedEventArgs &args);
	void OnPressImageChanged(nb::Core::PropertyValueChangedEventArgs &args);

};

typedef nbObjectPtrDerive<ImageButton, nb::Gui::ButtonPtr> ImageButtonPtr;
