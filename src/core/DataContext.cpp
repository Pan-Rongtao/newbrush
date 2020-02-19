#include "newbrush/core/DataContext.h"

using namespace nb;

DataContext * DataContext::getRoot() const
{
	auto p = const_cast<DataContext *>(this);
	do
	{
	} while (p->parent && (p = p->parent));
	return dynamic_cast<DataContext *>(p);
}

std::string DataContext::getAbsPath() const
{
	auto p = this;
	std::string path;
	do
	{
		path = p->name + "." + path;
	} while (p->parent && (p = p->parent));
	path.pop_back();
	return path;
}

std::string DataContext::getPath() const
{
	auto p = this;
	std::string path;
	do
	{
		path = p->name + "." + path;
	} while (p->parent && p->parent->parent && (p = p->parent));
	path.pop_back();
	return path;
}

void DataContext::set(const Var &value) &
{
}

Var DataContext::get() const
{
	return Var();
}

std::shared_ptr<DataContext> DataContext::lookup(const std::string & path) const
{
	return nullptr;
}

const std::type_info & DataContext::type() const
{
	return typeid(DataContext);
}

DataContext::DataContext(const std::string & _name)
	: name(_name)
	, parent(nullptr)
{
}

DataObject::DataObject(const std::string &name)
	: DataContext(name)
{
}

void DataObject::add(std::shared_ptr<DataContext> child) &
{
	if (!child)
	{
		nbThrowException(std::invalid_argument, "child is nullptr.");
	}

	auto ret = m_children.insert(std::make_pair(child->name, child));
	if (!ret.second)
	{
		nbThrowException(std::runtime_error, "[%s] is already exists in [%s]", child->name.data(), this->name.data());
	}
	child->parent = this;
}

void DataObject::remove(const std::string & childName) &
{
	auto iter = m_children.find(childName);
	if (iter != m_children.end())
	{
		m_children.erase(iter);
	}
}

bool DataObject::has(const std::string & childName) const
{
	return m_children.find(childName) != m_children.end();
}

std::shared_ptr<DataContext> DataObject::get(const std::string & childName) const
{
	auto iter = m_children.find(childName);
	return iter == m_children.end() ? nullptr : iter->second;
}

std::shared_ptr<DataObject> DataObject::getObject(const std::string & childName) const
{
	auto x = get(childName);
	auto p = std::dynamic_pointer_cast<DataObject>(x);
	return p;
}

std::shared_ptr<DataContext> DataObject::lookup(const std::string & path) const
{
	auto pathSegments = nb::stringSplit(path, ".", false);
	auto obj = this;
	for (int32_t i = 0; i != pathSegments.size(); ++i)
	{
		const std::string &sKey = pathSegments[i];
		if (i == pathSegments.size() - 1)
		{
			return obj->get(sKey);
		}
		else
		{
			obj = obj->getObject(sKey).get();
			if (!obj)
				return nullptr;
		}
	}
	return nullptr;
}

const std::type_info & DataObject::type() const
{
	return typeid(DataObject);
}

std::shared_ptr<DataObject> DataObject::gen(const std::string & name)
{
	return std::make_shared<DataObject>(name);
}

DataArray::DataArray(const std::string & name)
	: DataContext(name)
{
}

void DataArray::setTemplate(std::shared_ptr<DataObject> temp)
{
	if (!temp)
	{
		nbThrowException(std::invalid_argument, "temp is nullptr.");
	}

	m_template = temp;
}

const std::shared_ptr<DataObject> &DataArray::getTemplate() const
{
	return m_template;
}

void DataArray::addItem(std::shared_ptr<DataObject> item)
{
	m_items.push_back(item);
}

void DataArray::removeItem(std::size_t index)
{
	if (index >= itemCount())
	{
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d)", index, itemCount());
	}
	m_items.erase(m_items.begin() + index);
}

std::shared_ptr<DataObject> DataArray::item(std::size_t index)
{
	if (index >= itemCount())
		return nullptr;
	return m_items[index];
}

size_t DataArray::itemCount() const
{
	return m_items.size();
}

std::shared_ptr<DataArray> DataArray::gen(const std::string & name)
{
	return std::make_shared<DataArray>(name);
}
