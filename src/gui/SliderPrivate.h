#pragma once

#include "RepeatButton.h"
#include "Thumb.h"
#include "system/Size.h"

namespace nb
{
	namespace Gui
	{
		class Slider;
		class SliderPrivate : public nbObject
		{
		public:
			SliderPrivate(Slider *owner);
			virtual ~SliderPrivate(void);
			void OnPointerPress(bool &handled);
			void OnPointerRelease();
			void OnValueChanged(float fOldValue, float fNewValue);

			void OnDelayChanged();
			void OnIntervalChanged();
			void OnOrientationChanged();
			void OnDirectionReversedChanged();

			
			nb::System::Size ArrangeWork(const nb::System::Size &finalSize);
			nb::System::Size MeasureWork(const nb::System::Size &availableSize);
		private:
			void OnLTRepeatButtonClick(nb::Gui::RepeatButton::RepeatClickEventParam &param);
			void OnRBRepeatButtonClick(nb::Gui::RepeatButton::RepeatClickEventParam &param);
			void Init();
			void UpdateLayout();
			void Update();
		private:
			Slider *m_owner;
		};
	}
}
