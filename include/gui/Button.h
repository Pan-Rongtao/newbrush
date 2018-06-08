#pragma once

#include "ContentControl.h"

namespace nb { namespace Gui {

class NB_EXPORT Button : public ContentControl
{
	NB_OBJECT_TYPE_DECLARE();
public:
	Button(void);
	virtual ~Button(void);

protected:
	virtual void OnPointerPress(bool &handled);
	virtual void OnPointerRelease();
};

typedef nbObjectPtrDerive<Button, ControlPtr> ButtonPtr;

}}

