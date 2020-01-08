#include "core/DependencyObject.h"

using namespace nb;

void DependencyObject::set(const DependencyProperty & dp, const Var &value)
{
	auto defaultValue = dp.defaultMetadata()->defaultValue();
	auto defaultValueType = std::type_index(defaultValue.type());
	auto setValueType = std::type_index(value.type());
	Var fixSetValue;
	try {
		if (defaultValueType == typeid(bool))
		{
			fixSetValue = value.extract<bool>();
		}
		else if (defaultValueType == typeid(double))
		{
			fixSetValue = value.extract<float>();
		}
		else if (defaultValueType == typeid(float))
		{
			fixSetValue = value.extract<float>();
		}
		else if (defaultValueType == typeid(int))
		{
			fixSetValue = value.extract<int>();
		}
		else if (defaultValueType == typeid(unsigned int))
		{
			fixSetValue = value.extract<unsigned int>();
		}
		else if (defaultValue.isString())
		{
			fixSetValue = value.extract<std::string>();
		}
		else if (defaultValueType == typeid(short))
		{
			fixSetValue = value.extract<short>();
		}
		else if (defaultValueType == typeid(unsigned short))
		{
			fixSetValue = value.extract<unsigned short>();
		}
		else if (defaultValueType == typeid(char))
		{
			fixSetValue = value.extract<char>();
		}
		else if (defaultValueType == typeid(signed char))
		{
			fixSetValue = value.extract<signed char>();
		}
		else if (defaultValueType == typeid(unsigned char))
		{
			fixSetValue = value.extract<unsigned char>();
		}
		else if (defaultValueType == typeid(wchar_t))
		{
			fixSetValue = value.extract<wchar_t>();
		}
		else if (defaultValueType == typeid(char16_t))
		{
			fixSetValue = value.extract<char16_t>();
		}
		else if (defaultValueType == typeid(char32_t))
		{
			fixSetValue = value.extract<char32_t>();
		}
		else if (defaultValueType == typeid(long))
		{
			fixSetValue = value.extract<long>();
		}
		else if (defaultValueType == typeid(unsigned long))
		{
			fixSetValue = value.extract<unsigned long>();
		}
		else if (defaultValueType == typeid(long long))
		{
			fixSetValue = value.extract<unsigned long long>();
		}
		else if (defaultValueType == typeid(long double))
		{
			fixSetValue = value.extract<long double>();
		}
		else
		{
			if (dp.propertyType() != typeid(value))
			{
				nbThrowException(std::logic_error, "set value for [%s] must be a [%s] type instead of [%s]", dp.name().data(), dp.propertyType().name(), typeid(value).name());
			}
		}
	}
	catch (...)
	{
		nbThrowException(std::logic_error, "set value for [%s] must be a [%s] type instead of [%s]", dp.name().data(), dp.propertyType().name(), typeid(value).name());
	}

	bool isValueChanged = fixSetValue == defaultValue;
	_set(dp, defaultValue, fixSetValue, isValueChanged);
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

void DependencyObject::_set(const DependencyProperty & dp, const Var & defaultValue, const Var & setValue, bool isValueChanged)
{
	auto iterFind = m_valueEntrys.find(dp.globalIndex());
	if (iterFind == m_valueEntrys.end())
	{
		if (!isValueChanged)
		{
			EffectiveValueEntry newEntry(dp);
			newEntry.setBaseValue(setValue);
			m_valueEntrys.insert({ dp.globalIndex(), newEntry });
			onPropertyChanged({ dp, defaultValue, setValue });
		}
	}
	else
	{
		if (isValueChanged)
		{
			m_valueEntrys.erase(iterFind);
		}
		else
		{
			iterFind->second.setBaseValue(setValue);
			onPropertyChanged({ dp, defaultValue, setValue });
		}
	}
}

void DependencyObject::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
}
