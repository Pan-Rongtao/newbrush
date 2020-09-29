#include "newbrush/model/Object.h"

using namespace nb;

void Object::setValue(const property &prop, const var & value)
{
	if (!prop)				nbThrowException(std::runtime_error, "property[%s] is not registered for [%s].", prop.get_name().data(), this->get_type().get_name().data());
	if (prop.is_readonly())	nbThrowException(std::runtime_error, "property[%s] is readonly.", prop.get_name().data());

	auto propertyType = prop.get_type();
	auto valueType = value.get_type();
	var fixSetValue = value;
	bool isDerived = (valueType.get_wrapped_type().is_valid() && propertyType.get_wrapped_type().is_valid())
		&& (valueType.get_wrapped_type().is_derived_from(propertyType.get_wrapped_type()));
	if (propertyType != valueType && !isDerived)
	{
		bool ok = fixSetValue.convert(type(propertyType));
		if (!ok)
		{
			nbThrowException(std::logic_error, "setValue for [%s.%s] must be type [%s] instead of [%s], or check if has a converter from [%s] to [%s].", 
				this->get_type().get_name().data(), prop.get_name().data(), propertyType.get_name().data(), valueType.get_name().data(), valueType.get_name().data(), propertyType.get_name().data());
		}
	}
	prop.set_value(this, fixSetValue);
}

void Object::setValue(const std::string & propName, const var & value)
{
	auto prop = this->get_type().get_property(propName.data());
	setValue(prop, value);
}

var Object::getValue(const property &prop) const
{
	return prop.get_value(this);
}

void nb::setValue(const instance &ins, const property &prop, const var &value)
{
	if (!ins)				nbThrowException(std::runtime_error, "instance is nullptr.");
	if (!prop)				nbThrowException(std::runtime_error, "property[%s] is not registered for [%s].", prop.get_name().data(), ins.get_type().get_name().data());
	if (prop.is_readonly())	nbThrowException(std::runtime_error, "property[%s] is readonly.", prop.get_name().data());

	auto propertyType = prop.get_type();
	auto valueType = value.get_type();
	var fixSetValue = value;	
	if (propertyType != valueType)
	{
		bool ok = fixSetValue.convert(type(propertyType));
		if (!ok)
		{
			nbThrowException(std::logic_error, "setValue for [%s.%s] must be type [%s] instead of [%s], or check if has a converter from [%s] to [%s].", 
				ins.get_type().get_name().data(), prop.get_name().data(), propertyType.get_name().data(), valueType.get_name().data(), valueType.get_name().data(), propertyType.get_name().data());
		}
	}
	prop.set_value(ins, fixSetValue);
}

void nb::setValue(const instance &ins, const std::string &propName, const var &value)
{
	auto prop = ins.get_wrapped_instance().get_type().get_property(propName);
	nb::setValue(ins, prop, value);
}