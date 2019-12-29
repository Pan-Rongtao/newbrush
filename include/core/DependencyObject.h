#pragma once
#include "../core/Event.h"
#include "../core/Any.h"
#include "../core/DependencyProperty.h"

namespace nb {

using std::shared_ptr;

class NB_API DependencyObject
{
public:
	void setValue(const DependencyObject &dp, const Any &value);
	Any getValue(const DependencyObject &dp) const;

private:
	std::map<size_t, std::pair<Any, bool>>	m_propertys;
};

using DependencyObjectPtr = std::shared_ptr<DependencyObject>;

}