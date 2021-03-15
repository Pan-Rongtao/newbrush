#include "newbrush/Object.h"

using namespace nb;

void Object::setValue(const property &prop, const var & value)
{
	auto p = (Object *)(this);
	nb::setValue(p, prop, value);
}

void Object::setValue(const std::string &propName, const var &value)
{
	auto prop = this->get_type().get_property(propName.data());
	setValue(prop, value);
}

var Object::getValue(const property &prop) const
{
	auto p = (Object *)(this);
	return prop.get_value(p);
}

void nb::setValue(const instance &ins, const property &prop, const var &value)
{
	nbThrowExceptionIf(!ins, std::runtime_error, "instance is nullptr.");
	nbThrowExceptionIf(!prop, std::runtime_error, "property[%s] is not registered for [%s].", prop.get_name().data(), ins.get_type().get_name().data());
	nbThrowExceptionIf(prop.is_readonly(), std::runtime_error, "property[%s] is readonly.", prop.get_name().data());

	auto propertyType = prop.get_type();
	auto valueType = value.get_type();
	var &fixSetValue = const_cast<var&>(value);
	bool ok = fixSetValue.convert(type(propertyType));
	nbThrowExceptionIf(!ok, std::logic_error, "setValueNodes for [%s.%s] must be type [%s] instead of [%s], or check if has a converter from [%s] to [%s].",
		ins.get_type().get_name().data(), prop.get_name().data(), propertyType.get_name().data(), valueType.get_name().data(), valueType.get_name().data(), propertyType.get_name().data());

	prop.set_value(ins, fixSetValue);
}

void nb::setValue(const instance &ins, const std::string &propName, const var &value)
{
	auto prop = ins.get_wrapped_instance().get_type().get_property(propName);
	nb::setValue(ins, prop, value);
}

void nb::setGlobalValue(const property & prop, const var & value)
{
	nb::setValue(instance(), prop, value);
}

void nb::setGlobalValue(const std::string & propName, const var & value)
{
	setGlobalValue(type::get_global_property(propName), value);
}
