#include "newbrush/core/MetaObject.h"

using namespace nb;

Descriptor::Descriptor(const std::string & _category, const std::string & _displayName, const std::string & _description)
	: category(_category)
	, displayName(_displayName)
	, description(_description)
{
}

ClassDescriptor::ClassDescriptor(std::type_index _type, const std::string & _category, const std::string & _displayName, const std::string & _description, std::shared_ptr<MetaObject> _supperClass, std::function<std::shared_ptr<Object>()> _constructor)
	: Descriptor(_category, _displayName, _description)
	, type(_type)
	, constructor(_constructor)
	, surperClass(_supperClass)
{
}

PropertyDescriptor::PropertyDescriptor(size_t _type, const std::string & _category, const std::string & _displayName, const std::string & _description, ValueType _valueType, const std::string &_extra)
	: Descriptor(_category, _displayName, _description)
	, type(_type)
	, valueType(_valueType)
	, extra(_extra)
{
}

MetaObject::MetaObject(const ClassDescriptor & classDescriptor)
	: m_classDescriptor(classDescriptor)
{
}

const ClassDescriptor &MetaObject::classDescriptor() const
{
	return m_classDescriptor;
}

void MetaObject::addProperty(const DependencyProperty &dp, const std::string &category, const std::string &description, PropertyDescriptor::ValueType valueType, const std::string &extra)
{
	if (seal)
	{
		return;
	}
	PropertyDescriptor propertyDescriptor(dp.globalIndex(), category, dp.name(), description, valueType, extra);
	m_properties.push_back(propertyDescriptor);
}

const std::vector<PropertyDescriptor>& MetaObject::properties() const
{
	return m_properties;
}

std::vector<PropertyDescriptor> MetaObject::getAllProperties() const
{
	auto &selfProperties = properties();
	std::vector<PropertyDescriptor> ret(selfProperties.begin(), selfProperties.end());
	auto p = classDescriptor().surperClass;
	while (p)
	{
		auto &superProperties = p->properties();
		ret.insert(ret.end(), superProperties.begin(), superProperties.end());
		p = p->classDescriptor().surperClass;
	}
	return ret;
}

std::shared_ptr<Object> MetaObject::makeObject(std::string id)
{
	auto iter = registeredMetaObjects().find(id);
	if (iter != registeredMetaObjects().end())
	{
		return iter->second->classDescriptor().constructor();
	}
	return nullptr;
}

std::map<std::string, std::shared_ptr<MetaObject>>	g_registeredClasses;
std::map<std::string, std::shared_ptr<MetaObject>>& MetaObject::registeredMetaObjects()
{
	return g_registeredClasses;
}
