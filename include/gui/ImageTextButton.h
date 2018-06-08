#pragma once
#include "ImageButton.h"
#include "system/String.h"

class NB_EXPORT ImageTextButton : public ImageButton
{
	NB_OBJECT_TYPE_DECLARE();
public:
	ImageTextButton(void);
	virtual ~ImageTextButton(void);

	NB_X_OBJECT_PROPERTY_DECLARE(Text, nb::System::String);

public:
	void OnTextChanged(nb::Core::PropertyValueChangedEventArgs &args);

	typedef nbObjectPtrDerive<ImageTextButton, ImageButtonPtr> ImageTextButtonPtr;

};
typedef nbObjectPtrDerive<ImageTextButton, ImageButtonPtr> ImageTextButtonPtr;
