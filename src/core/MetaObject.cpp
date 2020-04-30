#include "newbrush/core/MetaObject.h"

using namespace nb;

MetaObject::MetaObject(const Descriptor & classDescriptor, MetaObject *surrperClass)
	: m_classDescriptor(classDescriptor)
	, m_supperClass(nullptr)
{
}

const Descriptor &MetaObject::descriptor() const
{
	return m_classDescriptor;
}

const MetaObject *MetaObject::supperClass() const
{
	return m_supperClass;
}

void MetaObject::addProperty(const Descriptor &propertyDescriptor)
{
	m_propertys.push_back(propertyDescriptor);
}

const std::vector<Descriptor>& MetaObject::propertys() const
{
	return m_propertys;
}

Descriptor::Descriptor(size_t _id, const std::string & _category, const std::string & _displayName, const std::string & _description)
	: id(_id)
	, category(_category)
	, displayName(_displayName)
	, description(_description)
{
}
