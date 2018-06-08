#include "gui/Slider.h"
#include "gui/Grid.h"
#include "gui/SolidColorBrush.h"

using namespace nb::Gui;

using namespace nb::Core;
using namespace nb::System;
using namespace nb::Media;

NB_OBJECT_TYPE_IMPLEMENT(Slider, RangeBase, NULL, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT(Slider, Delay, aInt, &Slider::OnDelayChanged);
NB_X_OBJECT_PROPERTY_IMPLEMENT(Slider, Interval, aInt, &Slider::OnIntervalChanged);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(Slider, Orientation, nb::Core::EnumObject, &Slider::OnOrientationChanged);
NB_X_OBJECT_PROPERTY_IMPLEMENT(Slider, IsDirectionReversed, aBool, &Slider::OnDirectionReversedChanged);


NB_OBJECT_PROPERTY_IMPLEMENT_EX(Slider, TestFGColor, nb::Media::Brush, NULL);

Slider::Slider()
: m_private(NULL)
{
	IsDirectionReversed = false;
	Orientation() = nb::Gui::Orientation_Hor;
	Delay = 0;
	Interval = 1000;
	Maximum = 100.0f;
	Minimum = 0.0f;
	Value = 0.0f;
	Width() = 100.0f;
	Height() = 20.0f;
	TestFGColor() = new nb::Media::SolidColorBrush(nb::System::Color(255, 0, 100));
	m_private = new SliderPrivate(this);
	Grid *pBody = (Grid *)GetBody();
}

Slider::~Slider()
{
	delete m_private;
}

SliderPrivate *Slider::GetPrivate()
{
	return m_private;
}

void Slider::OnValueChanged(float fOldValue, float fNewValue)
{
	if(m_private)
	{
		m_private->OnValueChanged(fOldValue, fNewValue);
	}
}

void Slider::OnPointerPress(bool &handled)
{
	if(m_private)
	{
		m_private->OnPointerPress(handled);
	}
}

void Slider::OnPointerRelease()
{
	if(m_private)
	{
		m_private->OnPointerRelease();
	}
}

void Slider::OnDelayChanged(nb::Core::PropertyValueChangedEventArgs &args)
{
	if(m_private)
	{
		m_private->OnDelayChanged();
	}
}

void Slider::OnIntervalChanged(nb::Core::PropertyValueChangedEventArgs &args)
{
	if(m_private)
	{
		m_private->OnIntervalChanged();
	}
}

void Slider::OnOrientationChanged(nb::Core::PropertyValueChangedEventArgs &args)
{
	if(m_private)
	{
		m_private->OnOrientationChanged();
	}
}

void Slider::OnDirectionReversedChanged(nb::Core::PropertyValueChangedEventArgs &args)
{
	if(m_private)
	{
		m_private->OnDirectionReversedChanged();
	}
}

nb::System::Size Slider::MeasureOverride(const nb::System::Size &availableSize)
{
	if(m_private)
	{
		return m_private->MeasureWork(availableSize);
	}
}
nb::System::Size Slider::ArrangeOverride(const nb::System::Size &finalSize)
{
	if(m_private)
	{
		return m_private->ArrangeWork(finalSize);
	}
}
