#include "newbrush/core/EffectiveValueEntry.h"

using namespace nb;

EffectiveValueEntry::EffectiveValueEntry(const DependencyProperty & dp)
	: m_propertyIndex(dp.globalIndex())
	, m_source((FullValueSourceE)BaseValueSourceInternalE::Unknown)
{
}

EffectiveValueEntry::EffectiveValueEntry(const DependencyProperty & dp, BaseValueSourceInternalE valueSource)
	: m_propertyIndex(dp.globalIndex())
	, m_source((FullValueSourceE)BaseValueSourceInternalE::Unknown)
{
}

EffectiveValueEntry::EffectiveValueEntry(const DependencyProperty & dp, FullValueSourceE fullValueSource)
	: m_propertyIndex(dp.globalIndex())
	, m_source(fullValueSource)
{
}

void EffectiveValueEntry::setBaseValue(const Var & value) &
{
//	auto modifiedValue = ensureModifiedValue();
//	modifiedValue.BaseValue = value;
	BaseValue = value;
}

Var EffectiveValueEntry::baseValue() const
{
//	return any_cast<ModifiedValue>(m_value).BaseValue;
	return BaseValue;
}

void EffectiveValueEntry::setExpressionValue(const Var & value)
{
/*	if (value.type() == DependencyProperty::unsetValue().type())
		nbThrowException(std::runtime_error, "value can't be DependencyProperty::unsetValue()");

	auto modifiedValue = ensureModifiedValue();
	modifiedValue.AnimatedValue = value;
	m_source.addFlags(IsAnimated);*/
	//
}

void EffectiveValueEntry::setAnimatedValue(const Var & value)
{
	if (value.type() == DependencyProperty::unsetValue().type())
		nbThrowException(std::runtime_error, "value can't be DependencyProperty::unsetValue()");

	auto modifiedValue = ensureModifiedValue();
	modifiedValue.AnimatedValue = value;
	m_source.addFlags(FullValueSourceE::IsAnimated);
}

void EffectiveValueEntry::setCoercedValue(const Var & value, const Var &baseValue, bool skipBaseValueChecks, bool coerceWithCurrentValue)
{
	if (value.type() == DependencyProperty::unsetValue().type())
		nbThrowException(std::runtime_error, "value can't be DependencyProperty::unsetValue()");

	auto modifiedValue = ensureModifiedValue();
	modifiedValue.BaseValue = value;
	m_source.addFlags(FullValueSourceE::IsCoerced);
	if(coerceWithCurrentValue)
	{
		m_source.addFlags(FullValueSourceE::IsCoercedWithCurrentValue);
	}
	else
	{
		m_source.removeFlags(FullValueSourceE::IsCoercedWithCurrentValue);
	}

}

ModifiedValue EffectiveValueEntry::ensureModifiedValue()
{
	ModifiedValue modifiedValue;
/*	if (m_value.type() == typeid(nullptr))
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
	}*/
	return modifiedValue;
}
