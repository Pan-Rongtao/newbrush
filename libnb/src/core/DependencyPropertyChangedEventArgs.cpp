#include "newbrush/core/DependencyPropertyChangedEventArgs.h"

using namespace nb;

DependencyPropertyChangedEventArgs::DependencyPropertyChangedEventArgs(DependencyPropertyPtr dp, var oldValue, var newValue)
	: m_property(dp)
	, m_oldValue(oldValue)
	, m_newValue(newValue)
{
}

DependencyPropertyPtr DependencyPropertyChangedEventArgs::property() const
{
	return m_property;
}

const var &DependencyPropertyChangedEventArgs::oldValue() const
{
	return m_oldValue;
}

const var &DependencyPropertyChangedEventArgs::newValue() const
{
	return m_newValue;
}
