#pragma once
#include "../core/DependencyProperty.h"
#include "../core/EnumFlags.h"

namespace nb {

class ModifiedValue
{
public:
	Any		BaseValue;
	Any		AnimatedValue;
	Any		CoercedValue;
};

enum FullValueSourceE : int16_t
{
	ValueSourceMask = 0x000F,					//0000 0000 0000 1111
	ModifiersMask = 0x0070,						//0000 0000 0111 0000
	IsExpression = 0x0010,						//0000 0000 0001 0000
	IsAnimated = 0x0020,						//0000 0000 0010 0000
	IsCoerced = 0x0040,							//0000 0000 0100 0000
	IsPotentiallyADeferredReference = 0x0080,	//0000 0000 1000 0000
	HasExpressionMarker = 0x0100,				//0000 0001 0000 0000
	IsCoercedWithCurrentValue = 0x200,			//0000 0010 0000 0000
};

enum BaseValueSourceInternalE : int8_t
{
	Unknown = 0,
	Default = 1,
	Inherited = 2,
	ThemeStyle = 3,
	ThemeStyleTrigger = 4,
	Style = 5,
	TemplateTrigger = 6,
	StyleTrigger = 7,
	ImplicitReference = 8,
	ParentTemplate = 9,
	ParentTemplateTrigger = 10,
	Local = 11,
};

class EffectiveValueEntry
{
public:
	EffectiveValueEntry(const DependencyProperty &dp);
	EffectiveValueEntry(const DependencyProperty &dp, BaseValueSourceInternalE valueSource);
	EffectiveValueEntry(const DependencyProperty &dp, FullValueSourceE fullValueSource);

	void setBaseValue(const Any &value) &;
	Any baseValue() const;
	void setExpressionValue(const Any &value);
	void setAnimatedValue(const Any &value);
	void setCoercedValue(const Any &value, const Any &baseValue, bool skipBaseValueChecks, bool coerceWithCurrentValue);

private:
	ModifiedValue ensureModifiedValue();

	size_t				m_propertyIndex;
	Any					m_value;
	EnumFlags<FullValueSourceE>	m_source;
};

}