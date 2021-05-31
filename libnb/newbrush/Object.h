#pragma once
#include "newbrush/Types.h"
#include "rttr/registration.h"
using namespace rttr;
using var = rttr::variant;

namespace nb
{

class NB_API Object
{
	RTTR_ENABLE()
public:
	virtual ~Object() = default;

	//异常：std::logic_error
	void setValue(const property &prop, const var &value);
	void setValue(const std::string &propName, const var &value);

	template<class T>
	void setValue(const property &prop, const T &value) 
	{
		setValue(prop, var(value)); 
	}

	template<class T>
	void setValue(const std::string &propName, const T &value) 
	{
		setValue(propName, var(value)); 
	}
	
	//获取属性值
	var getValue(const property &prop) const;

	template<class T>
	const T &getValue(const property &prop) const
	{
		nbThrowExceptionIf(prop.get_type() != type::get<T>(), std::logic_error, "should use get<%s> instead of get<%s> for [%s]", 
			prop.get_type().get_name().data(), typeid(T).name(), prop.get_name().data());
		return getValue(prop).get_value<T>();
	}

	property prop(const std::string &propName) const
	{
		return this->get_type().get_property(propName.data());
	}

protected:
	Object() = default;
};

template<class ObjectT>
NB_API property prop(const std::string &propName)
{
	return type::get<ObjectT>().get_property(propName);
}

NB_API void setValue(const instance &ins, const property &prop, const var &value);
NB_API void setValue(const instance &ins, const std::string &propName, const var &value);
NB_API void setGlobalValue(const property &prop, const var &value);
NB_API void setGlobalValue(const std::string &propName, const var &value);

template<class PropertyT>
bool addGlobalProperty(const std::string &name, const PropertyT &value)
{
	static std::map<std::string, var> gProperties;
	auto ret = gProperties.insert({name, value});
	bool success = ret.second;
	if (success)
	{
		registration::property(name, &ret.first->second);
	}
	return success;
}

struct ObjectTriplet
{
	ref<Object> object;
	property prop;
	var value;
};

}