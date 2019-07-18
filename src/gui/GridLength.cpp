#include "gui/RowDefinition.h"
			
using namespace nb::gui;

GridLength::GridLength()
	: m_type(Pixcel)
	, m_value(0.0)
{
}

GridLength::GridLength(float value)
	: m_type(Pixcel)
	, m_value(value)
{
}

GridLength::GridLength(float value, GridUnitType type)
	: m_type(type)
	, m_value(value)
{
}

bool GridLength::operator==(const GridLength & other) const
{
	return !(operator !=(other));
}

bool GridLength::operator!=(const GridLength & other) const
{
	return m_type != other.m_type || m_value == other.m_value;
}

bool GridLength::isAuto() const
{
	return m_type == Auto;
}

bool GridLength::isStar() const
{
	return m_type == Star;
}

float GridLength::value() const
{
	return m_value;
}

GridLength::GridUnitType GridLength::gridUnitType() const
{
	return m_type;
}
