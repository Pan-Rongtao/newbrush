#pragma once
#include "../../../Include/Gui/ImageButton.h"
#include "../../../Include/System/String.h"


class NB_EXPORT ListItem : public ImageButton
{
	NB_OBJECT_TYPE_DECLARE();
public:
	ListItem(void);
	virtual ~ListItem(void);

	NB_X_OBJECT_PROPERTY_DECLARE(Text, nb::System::String);
	NB_X_OBJECT_PROPERTY_DECLARE(TopLineImage, nb::Media::ImageSource);
	NB_X_OBJECT_PROPERTY_DECLARE(BottomLineImage, nb::Media::ImageSource);

public:
	void OnTextChanged(nb::Core::PropertyValueChangedEventArgs &args);
	void OnTopLineImageChanged(nb::Core::PropertyValueChangedEventArgs &args);
	void OnBottomLineImageChanged(nb::Core::PropertyValueChangedEventArgs &args);


};
typedef nbObjectPtrDerive<ListItem, ImageButtonPtr> ListItemPtr;
