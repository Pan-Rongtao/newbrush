#include "gui/ColDefinition.h"
			
using namespace nb::Gui;

NB_OBJECT_TYPE_IMPLEMENT(ColDefinition, nbObject, NULL, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(ColDefinition, Width, GridLength, NULL);

ColDefinition::ColDefinition(void)
	: m_actualWidth(0)
{
}

ColDefinition::~ColDefinition(void)
{
}
