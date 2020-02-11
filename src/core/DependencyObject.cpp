#include "newbrush/core/DependencyObject.h"

using namespace nb;

//如果未存储有该属性的值，则当value与defaultValue不相等时，插入新存储
//反之已经存储该属性的值，当value与defaultValue相等，移除该存储，否则更新该值
//wchar_t、chart16_t、long double等这些不被视为number，所以无法转成number类型（bool、char、int、short、float、double等）
//因此wchar_t这些类型都是用extract而不是convert
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
			fixSetValue = value.convert<int>();
		}
		else if (propertyType == typeid(unsigned int))
		{
			fixSetValue = value.convert<unsigned int>();
		}
		else if (propertyType == typeid(std::string))
		{
			fixSetValue = value.convert<std::string>();
		}
		else if (propertyType == typeid(std::wstring))
		{
			fixSetValue = value.convert<std::wstring>();
		}
		else if (propertyType == typeid(short))
		{
			fixSetValue = value.convert<short>();
		}
		else if (propertyType == typeid(unsigned short))
		{
			fixSetValue = value.convert<unsigned short>();
		}
		else if (propertyType == typeid(char))
		{
			fixSetValue = value.convert<char>();
		}
		else if (propertyType == typeid(signed char))
		{
			fixSetValue = value.convert<signed char>();
		}
		else if (propertyType == typeid(unsigned char))
		{
			fixSetValue = value.convert<unsigned char>();
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
			fixSetValue = value.convert<long>();
		}
		else if (propertyType == typeid(unsigned long))
		{
			fixSetValue = value.convert<unsigned long>();
		}
		else if (propertyType == typeid(long long))
		{
			fixSetValue = value.convert<long long>();
		}
		else if (propertyType == typeid(unsigned long long))
		{
			fixSetValue = value.convert<unsigned long long>();
		}
		else if (propertyType == typeid(long double))
		{
			fixSetValue = value.extract<long double>();
		}
	}
	catch (...)
	{
		nbThrowException(std::logic_error, "set value for [%s] must be a [%s] type instead of [%s]", dp.name().data(), dp.propertyType().name(), value.type().name());
	}

	if(fixSetValue.isEmpty())
	{
		nbThrowException(std::logic_error, "set value for [%s] must be a [%s] type instead of [%s]", dp.name().data(), dp.propertyType().name(), value.type().name());
	}

	auto defaultValue = dp.defaultMetadata()->defaultValue();
	_set(dp, defaultValue, fixSetValue);
}

//如果未存储有该属性的值，则返回defaultValue
//反之，返回该存储值
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
		auto changed = true;
		auto oldValue = iterFind->second.baseValue();
		try {
			changed = oldValue != setValue;
		}
		catch (...) {}	//异常表示无法比较，则视为非普通类型

		if (equalDefault)
		{
			m_valueEntrys.erase(iterFind);
		}
		else
		{
			iterFind->second.setBaseValue(setValue);
		}

		if (changed)
		{
			onPropertyChanged({ dp, oldValue, setValue });
		}
	}
}

void DependencyObject::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	auto metadata = args.property.defaultMetadata();
	if (metadata->propertyChangedCallback())
	{
		DependencyPropertyChangedEventArgs *p = const_cast<DependencyPropertyChangedEventArgs *>(&args);
		metadata->propertyChangedCallback()(this, p);
	}
}
