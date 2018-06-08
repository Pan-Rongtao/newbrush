#pragma once


#include "gui/Control.h"
#include "gui/Button.h"
#include "core/Event.h"
#include "system/Timer.h"

namespace nb
{
	namespace Gui
	{
		class NB_EXPORT RepeatButton : public Button
		{
			NB_OBJECT_TYPE_DECLARE();
		public:
			RepeatButton(void);
			virtual ~RepeatButton(void);

			
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(Delay, Core::aInt);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(Interval, Core::aInt);

			class RepeatClickEventParam : public nbEventParamT<RepeatButton>
			{
			public:
				RepeatClickEventParam(void){};
				virtual ~RepeatClickEventParam(){};
			};
		
		public:
			nbEvent<RepeatClickEventParam> RepeatClickEvent;

		protected:
			virtual void OnPointerPress(bool &handled);
			virtual void OnPointerRelease();

		private:
			void OnTimerOut(nb::System::Timer::TimeoutParam &param);
			void OnClick();

		private:
			nb::System::TimerPtr m_pRepeatTimer;
			bool m_bTriggerRepeat;

		};
	}
}

typedef nbObjectPtrDerive<nb::Gui::RepeatButton, nb::Gui::ButtonPtr> RepeatButtonPtr;
