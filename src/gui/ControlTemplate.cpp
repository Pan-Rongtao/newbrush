#include "gui/ControlTemplate.h"

using namespace nb::Gui;

NB_OBJECT_TYPE_IMPLEMENT(ControlTemplate, nbObject, NULL, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(ControlTemplate, VisualTree, UIElementFactory, NULL);

ControlTemplate::ControlTemplate(void)
{
}

ControlTemplate::~ControlTemplate(void)
{
}
