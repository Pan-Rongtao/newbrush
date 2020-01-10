#include "gui/DataContext.h"

using namespace nb;
using namespace nb::gui;

DataObject::DataObject(const std::string & name)
	: m_name(name)
{
}

void DataObject::setName(const std::string &name) &
{
	m_name = name;
}

std::string DataObject::name() const
{
	return m_name;
}

DataVar DataObject::get(const std::string & key) const
{
	return m_obj.get(key).extract<DataVar>();
}

void DataObject::getKeys(std::vector<std::string>& keys) const
{
	m_obj.getNames(keys);
}

std::vector<std::string> DataObject::getKeys() const
{
	return m_obj.getNames();
}

bool DataObject::has(const std::string & key) const
{
	return m_obj.has(key);
}

std::size_t DataObject::childCount() const
{
	return m_obj.size();
}

void DataObject::set(const std::string & key, const DataVar & value) &
{
	auto x = m_obj.set(key, value);
	m_obj.get(key).extract<DataVar>().parent = this;
}

void DataObject::remove(const std::string & key) &
{
	m_obj.remove(key);
}

void ObjectData::insertChild(DataContextPtr child)
{
	m_children.insert(std::make_pair(child->name(), child));
	child->m_parent = shared_from_this();
}

void ObjectData::removeChild(const std::string & childName)
{
	auto iter = m_children.find(childName);
	if (iter != m_children.end())
		m_children.erase(iter);
}

bool ObjectData::hasChild(const std::string & childName) &
{
	return m_children.find(childName) != m_children.end();
}

DataContextPtr ObjectData::getChild(const std::string & childName)
{
	auto iter = m_children.find(childName);
	return iter == m_children.end() ? nullptr : iter->second;
}

DataContextPtr ObjectData::lookup(const std::string & path)
{
	auto pathSegments = nb::stringSplit(path, ".", false);
	auto obj = shared_from_this();
	for (int32_t i = 0; i != pathSegments.size(); ++i)
	{
		const std::string &sKey = pathSegments[i];
		if (i == pathSegments.size() - 1)
		{
			return obj->getChild(sKey);
		}
		else
		{
			auto child = obj->getChild(sKey);
			obj = std::dynamic_pointer_cast<ObjectData>(child);
			if (!obj)
				return nullptr;
		}
	}
	return nullptr;
}

DataContextPtr ObjectData::operator [](const std::string &name)
{
	return getChild(name);
}
