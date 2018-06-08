#pragma once

#include "Object.h"
#include "Event.h"

namespace nb
{
	namespace Core
	{
		class NB_CORE_DECLSPEC_X_INTERFACE DependencyObject : public nbObject
		{
		public:
			DependencyObject(void);
			virtual ~DependencyObject(void);

			struct PropertyValueChangedEventParam : nbEventParam { };
			nbEvent<PropertyValueChangedEventParam> m_PropertyValueChangedEvent;

			nbEventTest<PropertyValueChangedEventParam> m_xfwser;
		};

		typedef nbObjectPtrDerive<nbObject, nbObjectPtr> DependencyObjectPtr;
	}
}
