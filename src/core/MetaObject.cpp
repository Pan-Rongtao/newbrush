#include "newbrush/core/MetaObject.h"

using namespace nb;

Descriptor::Descriptor(size_t _id, const std::string & _category, const std::string & _displayName, const std::string & _description)
	: id(_id)
	, category(_category)
	, displayName(_displayName)
	, description(_description)
{
}

ClassDescriptor::ClassDescriptor(size_t _id, const std::string & _category, const std::string & _displayName, const std::string & _description, MetaObject * _supperClass, std::function<std::shared_ptr<Object>()> _constructor)
	: Descriptor(_id, _category, _displayName, _description)
	, constructor(_constructor)
	, surperClass(_supperClass)
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

void MetaObject::addProperty(const Descriptor &propertyDescriptor)
{
	if (seal)
	{
		return;
	}
	m_propertys.push_back(propertyDescriptor);
}

const std::vector<Descriptor>& MetaObject::propertys() const
{
	return m_propertys;
}

std::map<size_t, std::shared_ptr<MetaObject>>	g_registeredClasses;
std::map<size_t, std::shared_ptr<MetaObject>>& MetaObject::registeredMetaObjects()
{
	return g_registeredClasses;
}
