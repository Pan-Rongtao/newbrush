#pragma once
#include "../core/Event.h"
#include "../core/Any.h"
#include "DependencyProperty.h"

namespace nb {
namespace gui{

class NB_API DependencyObject
{
public:
	template<class T>
	void set(const DependencyProperty &dp, const T &value)
	{
		if (dp.defaultValue().type() != typeid(value))
			nbThrowException(std::logic_error, "value must be type of [%s]", dp.defaultValue().type().name());

		if (!m_propertys)
			m_propertys = std::make_shared<std::map<size_t, std::pair<Any, bool>>>();

		auto iter = std::find_if(m_propertys->begin(), m_propertys->end(), [&dp](const std::pair<size_t, std::pair<Any, bool>> &p) {
			return p.first == dp.hash(); });

		const T &defaultV = any_cast<T>(dp.defaultValue());
		if (iter == m_propertys->end())
		{
			if (value != defaultV)
			{
				m_propertys->insert({ dp.hash(),{ value, false } });
				PropertyChanged.dispatch({ dp, value });
			}
		}
		else
		{
			if (value != any_cast<T>(iter->second.first))
			{
				iter->second.first = value;
				PropertyChanged.dispatch({ dp, value });
			}
		}
	}

	template<class T>
	T get(const DependencyProperty &dp) const
	{
		if (!m_propertys)
		{
			return any_cast<T>(dp.defaultValue());
		}
		auto iter = std::find_if(m_propertys->begin(), m_propertys->end(), [&dp](const std::pair<size_t, std::pair<Any, bool>> &p) { return p.first == dp.hash(); });
		return iter == m_propertys->end() ? any_cast<T>(dp.defaultValue()) : any_cast<T>(iter->second.first);
	}

	struct PropertyChangedArg { DependencyProperty dp; Any value; };
	Event<PropertyChangedArg>							PropertyChanged;

private:
	std::shared_ptr<std::map<size_t, std::pair<Any, bool>>>	m_propertys;
};


}
}