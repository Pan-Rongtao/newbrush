#include "gui/RowDefinition.h"
			
using namespace nb::Gui;

NB_OBJECT_TYPE_IMPLEMENT(RowDefinition, nbObject, NULL, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(RowDefinition, Height, GridLength, NULL);

RowDefinition::RowDefinition(void)
	: m_actualHeight(0)
{
}

RowDefinition::~RowDefinition(void)
{
}
