#include "newbrush/gui/Setter.h"
#include "newbrush/gui/UIElement.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

void SetterBase::attach(UIElement* uie)
{
}

Setter::Setter()
{
}

Setter::Setter(DependencyPropertyPtr dp, const var & v)
	: Setter(dp, v, "")
{
}

Setter::Setter(DependencyPropertyPtr dp, const var &v, const std::string &targetName)
	: m_targetName(targetName)
{
	setProperty(dp);
	setValue(v);
}

void Setter::setProperty(DependencyPropertyPtr dp)
{
	if (!dp)
	{
		nbThrowException(std::invalid_argument, "dp is null");
	}

	if (dp->readOnly())
	{
		nbThrowException(std::invalid_argument, "dp is readonly");
	}

	//todo
	//dp与value不匹配（抛出异常）

	m_property = dp;
}

DependencyPropertyPtr Setter::property() const
{
	return m_property;
}

void Setter::setValue(const var & v)
{
	if (!v.is_valid())
	{
		nbThrowException(std::invalid_argument, "v is invalid");
	}
	m_value = v;
}

const var & Setter::value() const
{
	return m_value;
}

void Setter::setTargetName(const std::string & name)
{
	m_targetName = name;
}

const std::string & Setter::targetName() const
{
	return m_targetName;
}

void Setter::attach(UIElement* uie)
{
	uie->setValue(property(), value());
}

void EventSetter::attach(UIElement* uie)
{
	uie->addHandler(event, handler);
}
