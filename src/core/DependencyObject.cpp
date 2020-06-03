#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;
using namespace rttr;

//如果使用Poco::Var，如果未存储有该属性的值，则当value与defaultValue不相等时，插入新存储
//反之已经存储该属性的值，当value与defaultValue相等，移除该存储，否则更新该值
//wchar_t、chart16_t、long double等这些不被视为number，所以无法转成number类型（bool、char、int、short、float、double等）
//因此wchar_t这些类型都是用extract而不是convert
void DependencyObject::setValue(DependencyPropertyPtr dp, const var &value)
{
	auto propertyType = dp->propertyType();
	var fixSetValue = value;
	if (propertyType != value.get_type())
	{
		bool ok = fixSetValue.convert(rttr::type(propertyType));
		if (!ok)
		{
			nbThrowException(std::logic_error, "set value for [%s] must be a [%s] type instead of [%s]", dp->name().data(), dp->propertyType().get_name().data(), value.get_type().get_name().data());
		}
	}

	auto defaultValue = dp->defaultMetadata()->defaultValue();
	_set(dp, defaultValue, fixSetValue);
}

//如果未存储有该属性的值，则返回defaultValue
//反之，返回该存储值
var DependencyObject::getValue(DependencyPropertyPtr dp) const
{
	auto iter = m_valueEntrys.find(dp->globalIndex());
	if (iter == m_valueEntrys.end())
	{
		return dp->defaultMetadata()->defaultValue();
	}
	else
	{
		auto x = iter->second.baseValue();
		return x;
	}
}

void DependencyObject::_set(DependencyPropertyPtr dp, const var & defaultValue, const var & setValue)
{
	auto coerceValue = setValue;
	auto coerce = dp->defaultMetadata()->coerceValueCallback();
	if (coerce)
	{
		coerceValue = coerce(this, setValue);
	}

	bool equalDefault = false;
	try {
		equalDefault = coerceValue == defaultValue;
	}
	catch (...) {}	//异常表示无法比较，则视为非普通类型
	
	auto iterFind = m_valueEntrys.find(dp->globalIndex());
	if (iterFind == m_valueEntrys.end())
	{
		if (!equalDefault)
		{
			EffectiveValueEntry newEntry(dp);
			newEntry.setBaseValue(coerceValue);
			m_valueEntrys.insert({ dp->globalIndex(), newEntry });
			DependencyPropertyChangedEventArgs args{ dp, defaultValue, coerceValue };
			invokePropertyCallback(args);
			onPropertyChanged(args);
		}
	}
	else
	{
		auto changed = true;
		auto oldValue = iterFind->second.baseValue();
		try {
			changed = oldValue != coerceValue;
		}
		catch (...) {}	//异常表示无法比较，则视为非普通类型

		if (equalDefault)
		{
			m_valueEntrys.erase(iterFind);
		}
		else
		{
			iterFind->second.setBaseValue(coerceValue);
		}

		if (changed)
		{
			DependencyPropertyChangedEventArgs args{ dp, oldValue, coerceValue };
			invokePropertyCallback(args);
			onPropertyChanged(args);
		}
	}
}

void DependencyObject::_checkType(DependencyPropertyPtr dp, rttr::type getType) const
{
	if (dp->propertyType() != getType)
	{
		nbThrowException(std::logic_error, "should use get<%s> instead of get<%s> for [%s]", dp->propertyType().get_name().data(), getType.get_name().data(), dp->name().data());
	}
}

void DependencyObject::invokePropertyCallback(const DependencyPropertyChangedEventArgs & args)
{
	auto metadata = args.property->defaultMetadata();
	if (metadata->propertyChangedCallback())
	{
		DependencyPropertyChangedEventArgs *p = const_cast<DependencyPropertyChangedEventArgs *>(&args);
		metadata->propertyChangedCallback()(this, p);
	}
}

void DependencyObject::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
}
