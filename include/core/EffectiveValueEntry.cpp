#include "EffectiveValueEntry.h"

using namespace nb;

EffectiveValueEntry::EffectiveValueEntry(const DependencyProperty & dp)
	: m_propertyIndex(dp.globalIndex())
	, m_value(nullptr)
	, m_source((FullValueSourceE)BaseValueSourceInternalE::Unknown)
{
}

EffectiveValueEntry::EffectiveValueEntry(const DependencyProperty & dp, BaseValueSourceInternalE valueSource)
	: m_propertyIndex(dp.globalIndex())
	, m_value(DependencyProperty::unsetValue())
	, m_source((FullValueSourceE)BaseValueSourceInternalE::Unknown)
{
}

EffectiveValueEntry::EffectiveValueEntry(const DependencyProperty & dp, FullValueSourceE fullValueSource)
	: m_propertyIndex(dp.globalIndex())
	, m_value(DependencyProperty::unsetValue())
	, m_source(fullValueSource)
{
}

void EffectiveValueEntry::setBaseValue(const Any & value) &
{
	auto modifiedValue = ensureModifiedValue();
	modifiedValue.BaseValue = value;
}

Any EffectiveValueEntry::baseValue() const
{
	return any_cast<ModifiedValue>(m_value).BaseValue;
}

void EffectiveValueEntry::setExpressionValue(const Any & value)
{
/*	if (value.type() == DependencyProperty::unsetValue().type())
		nbThrowException(std::runtime_error, "value can't be DependencyProperty::unsetValue()");

	auto modifiedValue = ensureModifiedValue();
	modifiedValue.AnimatedValue = value;
	m_source.addFlags(IsAnimated);*/
	//
}

void EffectiveValueEntry::setAnimatedValue(const Any & value)
{
	if (value.type() == DependencyProperty::unsetValue().type())
		nbThrowException(std::runtime_error, "value can't be DependencyProperty::unsetValue()");

	auto modifiedValue = ensureModifiedValue();
	modifiedValue.AnimatedValue = value;
	m_source.addFlags(IsAnimated);
}

void EffectiveValueEntry::setCoercedValue(const Any & value, const Any &baseValue, bool skipBaseValueChecks, bool coerceWithCurrentValue)
{
	if (value.type() == DependencyProperty::unsetValue().type())
		nbThrowException(std::runtime_error, "value can't be DependencyProperty::unsetValue()");

	auto modifiedValue = ensureModifiedValue();
	modifiedValue.BaseValue = value;
	m_source.addFlags(IsCoerced);
	if(coerceWithCurrentValue)
	{
		m_source.addFlags(IsCoercedWithCurrentValue);
	}
	else
	{
		m_source.removeFlags(IsCoercedWithCurrentValue);
	}

}

ModifiedValue EffectiveValueEntry::ensureModifiedValue()
{
	ModifiedValue modifiedValue;
	if (m_value.type() == typeid(nullptr))
	{
		m_value = modifiedValue;
	}
	else
	{
		if (m_value.type() != typeid(ModifiedValue))
		{
			(any_cast<ModifiedValue>(m_value)).BaseValue = m_value;
			m_value = modifiedValue;
		}
	}
	return modifiedValue;
}
