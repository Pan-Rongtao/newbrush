#include "gui/VisualState.h"
#include "gui/VisualStateGroup.h"

using namespace nb::Gui;
using namespace nb::Media;

NB_OBJECT_TYPE_IMPLEMENT(VisualState, nbObject, NULL, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(VisualState, Target, nbObject, NULL);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(VisualState, TargetProperty, nb::Core::DependencyProperty, NULL);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(VisualState, TargetValue, nb::Core::aInt, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(VisualState, Storyboard, nb::Media::Storyboard, NULL);

VisualState::VisualState(const char *name)
	: m_name(name)
{
	
}

VisualState::~VisualState(void)
{
}
