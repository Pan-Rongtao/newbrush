#pragma once
#include "newbrush/core/Object.h"

namespace nb {

class DependencyProperty;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;

class NB_API DependencyPropertyChangedEventArgs : public Object
{
public:
	DependencyPropertyChangedEventArgs(DependencyPropertyPtr dp, var oldValue, var newValue);

	DependencyPropertyPtr property() const;
	const var &oldValue() const;
	const var &newValue() const;

private:
	DependencyPropertyPtr	m_property;
	var						m_oldValue;
	var						m_newValue;
};


}