#pragma once

#include "gui/WrapPanel.h"
#include "../../src/gui/RangeBase.h"
#include "../../src/gui/SliderPrivate.h"
#include "gui/Brush.h"

namespace nb
{
	namespace Gui
	{
		class NB_EXPORT Slider : public RangeBase
		{
			friend class SliderPrivate;
			NB_OBJECT_TYPE_DECLARE();
		public:
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(Delay, Core::aInt);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(Interval, Core::aInt);
			NB_OBJECT_ENUM_PROPERTY_DECLARE(Orientation, nb::Gui::Orientation);
			NB_X_ROCK_OBJECT_PROPERTY_DECLARE(IsDirectionReversed, Core::aBool);
			NB_OBJECT_PROPERTY_DECLARE(TestFGColor, nb::Media::Brush);
			/*
			 *nb::Gui::Orientation_Hor时，正常方向为从左到右增大
			 *nb::Gui::Orientation_Vert时，正常方向为从下到上增大
			 *当IsDirectionReversed=true时，上面两种情况反过来
			 */

		public:
			Slider(void);
			virtual ~Slider(void);

			SliderPrivate *GetPrivate();
		protected:
			virtual void OnPointerPress(bool &handled);
			virtual void OnPointerRelease();

			void OnValueChanged(float fOldValue, float fNewValue);

			
			virtual System::Size MeasureOverride(const System::Size &availableSize);
			virtual System::Size ArrangeOverride(const nb::System::Size &finalSize);

		private:
			SliderPrivate *m_private;
			void OnDelayChanged(nb::Core::PropertyValueChangedEventArgs &args);
			void OnIntervalChanged(nb::Core::PropertyValueChangedEventArgs &args);
			void OnOrientationChanged(nb::Core::PropertyValueChangedEventArgs &args);
			void OnDirectionReversedChanged(nb::Core::PropertyValueChangedEventArgs &args);
		};
		typedef nbObjectPtrDerive<Slider, RangeBasePtr> SliderPtr;
	}
}
