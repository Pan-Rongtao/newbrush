#include "newbrush/core/EffectiveValueEntry.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

EffectiveValueEntry::EffectiveValueEntry(DependencyPropertyPtr dp)
	: m_propertyIndex(dp->globalIndex())
	, m_source((FullValueSourceE)BaseValueSourceInternalE::Unknown)
{
}

EffectiveValueEntry::EffectiveValueEntry(DependencyPropertyPtr dp, BaseValueSourceInternalE valueSource)
	: m_propertyIndex(dp->globalIndex())
	, m_source((FullValueSourceE)BaseValueSourceInternalE::Unknown)
{
}

EffectiveValueEntry::EffectiveValueEntry(DependencyPropertyPtr dp, FullValueSourceE fullValueSource)
	: m_propertyIndex(dp->globalIndex())
	, m_source(fullValueSource)
{
}

void EffectiveValueEntry::setBaseValue(const var & value) &
{
//	auto modifiedValue = ensureModifiedValue();
//	modifiedValue.BaseValue = value;
	BaseValue = value;
}

var EffectiveValueEntry::baseValue() const
{
//	return any_cast<ModifiedValue>(m_value).BaseValue;
	return BaseValue;
}

void EffectiveValueEntry::setExpressionValue(const var & value)
{
/*	if (value.type() == DependencyProperty::unsetValue().type())
		nbThrowException(std::runtime_error, "value can't be DependencyProperty::unsetValue()");

	auto modifiedValue = ensureModifiedValue();
	modifiedValue.AnimatedValue = value;
	m_source.addFlags(IsAnimated);*/
	//
}

void EffectiveValueEntry::setAnimatedValue(const var & value)
{
	if (value.get_type() == DependencyProperty::unsetValue().get_type())
		nbThrowException(std::runtime_error, "value can't be DependencyProperty::unsetValue()");

	auto modifiedValue = ensureModifiedValue();
	modifiedValue.AnimatedValue = value;
	m_source.set(FullValueSourceE::IsAnimated);
}

void EffectiveValueEntry::setCoercedValue(const var & value, const var &baseValue, bool skipBaseValueChecks, bool coerceWithCurrentValue)
{
	if (value.get_type() == DependencyProperty::unsetValue().get_type())
		nbThrowException(std::runtime_error, "value can't be DependencyProperty::unsetValue()");

	auto modifiedValue = ensureModifiedValue();
	modifiedValue.BaseValue = value;
	m_source.set(FullValueSourceE::IsCoerced);
	if(coerceWithCurrentValue)
	{
		m_source.set(FullValueSourceE::IsCoercedWithCurrentValue);
	}
	else
	{
		m_source.reset(FullValueSourceE::IsCoercedWithCurrentValue);
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
