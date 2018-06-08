#pragma once
#include "gui/UseControl.h"
#include "core/Event.h"

namespace nb
{
	namespace Gui
	{
		class NB_EXPORT RangeBase : public UseControl
		{
			
			NB_OBJECT_TYPE_DECLARE();

		public:
			RangeBase(void);
			virtual ~RangeBase(void);

			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(Value, Core::aFloat);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(Maximum, Core::aFloat);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(Minimum, Core::aFloat);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(SmallChange, Core::aFloat);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(LargeChange, Core::aFloat);
			
			class ValueChangedEventParam : public nbEventParamT<RangeBase>
			{
			public:
				ValueChangedEventParam():m_fOldValue(0.0f), m_fNewValue(0.0f){}
				virtual ~ValueChangedEventParam(void){};
			public:
				float m_fOldValue;
				float m_fNewValue;
			};
		public:
			nbEvent<ValueChangedEventParam> ValueChangedEvent;
		private:
			nbEvent<ValueChangedEventParam> MaximumChangedEvent;
			nbEvent<ValueChangedEventParam> MinimumChangedEvent;

		protected:
			virtual void OnValueChanged(float fOldValue, float fNewValue);
			virtual void OnMaximumChanged(float fOldValue, float fNewValue);
			virtual void OnMinimumChanged(float fOldValue, float fNewValue);
		private:
			void OnValueChangedEvent(ValueChangedEventParam &param);
			void OnMaximumChangedEvent(ValueChangedEventParam &param);
			void OnMinimumChangedEvent(ValueChangedEventParam &param);
		};
		typedef nbObjectPtrDerive<RangeBase, ControlPtr> RangeBasePtr;
	}
}
