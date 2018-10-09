#pragma once
#include "Object.h"
#include "Event.h"

namespace nb{ namespace core{

class NB_API DependencyObject : public nbObject
{
public:
	DependencyObject(void);
	virtual ~DependencyObject(void);

	struct PropertyValueChangedEventParam : nbEventParam { };
	nbEvent<PropertyValueChangedEventParam> m_PropertyValueChangedEvent;
};

typedef nbObjectPtrDerive<nbObject, nbObjectPtr> DependencyObjectPtr;

}}
