#pragma once
#include "../core/Event.h"
#include "../core/Any.h"
#include "../core/DependencyProperty.h"

namespace nb {

using std::shared_ptr;

class NB_API DependencyObject
{
public:
	template<class T>
	void set(const DependencyProperty &dp, const T &value) &
	{
		if (dp.defaultValue().type() != typeid(value))
		{
			nbThrowException(std::logic_error, "value must be type of [%s]", dp.defaultValue().type().name());
		}

		auto iter = std::find_if(m_propertys.begin(), m_propertys.end(), [&dp](const std::pair<size_t, std::pair<Any, bool>> &p) { return p.first == dp.hash(); });
		if (iter == m_propertys.end())
		{
			m_propertys[dp.hash()] = { value, false };
			if (value != any_cast<T>(dp.defaultValue()))
			{
				PropertyChanged.invoke({ dp, value });
			}
		}
		else
		{
			if (value != any_cast<T>(iter->second.first))
			{
				iter->second.first = value;
				PropertyChanged.invoke({ dp, value });
			}
		}
	}

	void set(const DependencyProperty &dp, const Any &value) &
	{
		if (dp.defaultValue().type() != value.type())
		{
			nbThrowException(std::logic_error, "value must be type of [%s]", dp.defaultValue().type().name());
		}

		auto iter = std::find_if(m_propertys.begin(), m_propertys.end(), [&dp](const std::pair<size_t, std::pair<Any, bool>> &p) { return p.first == dp.hash(); });
		if (iter == m_propertys.end())
		{
			m_propertys[dp.hash()] = { value, false };
			PropertyChanged.invoke({ dp, value });
		}
		else
		{
			iter->second.first = value;
			PropertyChanged.invoke({ dp, value });
		}
	}

	template<class T>
	T &get(const DependencyProperty &dp)
	{
		auto iter = std::find_if(m_propertys.begin(), m_propertys.end(), [&dp](const std::pair<size_t, std::pair<Any, bool>> &p) { return p.first == dp.hash(); });
		if (iter == m_propertys.end())
		{
			m_propertys[dp.hash()] = { dp.defaultValue(), false };
		}
		return any_cast<T>(m_propertys[dp.hash()].first);
	}
	
	struct PropertyChangedArgs { DependencyProperty dp; Any value; };
	Event<PropertyChangedArgs>							PropertyChanged;

private:
	std::map<size_t, std::pair<Any, bool>>	m_propertys;
};

using DependencyObjectPtr = std::shared_ptr<DependencyObject>;

}