#include "core/DependencyObject.h"

using namespace nb;

void DependencyObject::set(const DependencyProperty & dp, const Var &value)
{
	auto propertyType = dp.propertyType();
	Var fixSetValue;
	try {
		if (propertyType == value.type())
		{
			fixSetValue = value;
		}
		else if (propertyType == typeid(bool))
		{
			fixSetValue = value.convert<bool>();
		}
		else if (propertyType == typeid(double))
		{
			fixSetValue = value.convert<double>();
		}
		else if (propertyType == typeid(float))
		{
			fixSetValue = value.convert<float>();
		}
		else if (propertyType == typeid(int))
		{
			fixSetValue = value.extract<int>();
		}
		else if (propertyType == typeid(unsigned int))
		{
			fixSetValue = value.extract<unsigned int>();
		}
		else if (propertyType == typeid(std::string))
		{
			fixSetValue = value.extract<std::string>();
		}
		else if (propertyType == typeid(std::wstring))
		{
			fixSetValue = value.extract<std::wstring>();
		}
		else if (propertyType == typeid(short))
		{
			fixSetValue = value.extract<short>();
		}
		else if (propertyType == typeid(unsigned short))
		{
			fixSetValue = value.extract<unsigned short>();
		}
		else if (propertyType == typeid(char))
		{
			fixSetValue = value.extract<char>();
		}
		else if (propertyType == typeid(signed char))
		{
			fixSetValue = value.extract<signed char>();
		}
		else if (propertyType == typeid(unsigned char))
		{
			fixSetValue = value.extract<unsigned char>();
		}
		else if (propertyType == typeid(wchar_t))
		{
			fixSetValue = value.extract<wchar_t>();
		}
		else if (propertyType == typeid(char16_t))
		{
			fixSetValue = value.extract<char16_t>();
		}
		else if (propertyType == typeid(char32_t))
		{
			fixSetValue = value.extract<char32_t>();
		}
		else if (propertyType == typeid(long))
		{
			fixSetValue = value.extract<long>();
		}
		else if (propertyType == typeid(unsigned long))
		{
			fixSetValue = value.extract<unsigned long>();
		}
		else if (propertyType == typeid(long long))
		{
			fixSetValue = value.extract<unsigned long long>();
		}
		else if (propertyType == typeid(long double))
		{
			fixSetValue = value.extract<long double>();
		}
		else
		{
			fixSetValue = value;
		//	nbThrowException(std::logic_error, "set value for [%s] must be a [%s] type instead of [%s]", dp.name().data(), dp.propertyType().name(), value.type().name());
		}
	}
	catch (...)
	{
		nbThrowException(std::logic_error, "set value for [%s] must be a [%s] type instead of [%s]", dp.name().data(), dp.propertyType().name(), value.type().name());
	}

	auto defaultValue = dp.defaultMetadata()->defaultValue();
	_set(dp, defaultValue, fixSetValue);
}

Var DependencyObject::get(const DependencyProperty & dp) const
{
	auto iter = m_valueEntrys.find(dp.globalIndex());
	if (iter == m_valueEntrys.end())
	{
		return dp.defaultMetadata()->defaultValue();
	}
	else
	{
		auto x = iter->second.baseValue();
		return x;
	}
}

void DependencyObject::_set(const DependencyProperty & dp, const Var & defaultValue, const Var & setValue)
{
	bool equalDefault = false;
	try {
		equalDefault = setValue == defaultValue;
	}
	catch (...) {}	//异常表示无法比较，则视为非普通类型
	
	auto iterFind = m_valueEntrys.find(dp.globalIndex());
	if (iterFind == m_valueEntrys.end())
	{
		if (!equalDefault)
		{
			EffectiveValueEntry newEntry(dp);
			newEntry.setBaseValue(setValue);
			m_valueEntrys.insert({ dp.globalIndex(), newEntry });
			onPropertyChanged({ dp, defaultValue, setValue });
		}
	}
	else
	{
		if (equalDefault)
		{
			m_valueEntrys.erase(iterFind);
		}
		else
		{
			auto changed = true;
			try {
				changed = iterFind->second.baseValue() != setValue;
			}
			catch (...) {}	//异常表示无法比较，则视为非普通类型

			if (changed)
			{
				iterFind->second.setBaseValue(setValue);
				onPropertyChanged({ dp, defaultValue, setValue });
			}
		}
	}
}

void DependencyObject::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
}
