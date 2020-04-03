#include "newbrush/media/TransformCollection.h"
#include "newbrush/core/Def.h"

using namespace nb;

TransformCollection::TransformCollection()
{
	m_collection.clear();
}

TransformCollection::TransformCollection(std::vector<std::shared_ptr<Transform>> collection)
{
	m_collection.clear();
	m_collection = collection;
}

TransformCollection::TransformCollection(size_t capacity)
{
	m_collection.clear();
	m_collection.resize(capacity);
}

size_t TransformCollection::count()
{
	return m_collection.size();
}

void TransformCollection::add(std::shared_ptr<Transform> value)
{
	m_collection.push_back(value);
}

void TransformCollection::clear()
{
	m_collection.clear();
}

bool TransformCollection::contains(std::shared_ptr<Transform> value)
{
	auto iter = std::find(m_collection.begin(), m_collection.end(), value);
	
	return iter != m_collection.end() ? true : false;
}

int TransformCollection::indexOf(std::shared_ptr<Transform> value)
{
	auto  iter = std::find(m_collection.begin(), m_collection.end(), value);

	return iter != m_collection.end() ? iter - m_collection.begin() : -1;
}

void TransformCollection::insert(size_t index, std::shared_ptr<Transform> value)
{
	m_collection.insert(m_collection.begin() + index, value);
}

bool TransformCollection::remove(std::shared_ptr<Transform> value)
{
	auto  iter = std::find(m_collection.begin(), m_collection.end(), value);

	if (iter != m_collection.end())
	{
		m_collection.erase(iter);
		return true;
	}
	return false;
}

void TransformCollection::removeAt(size_t index)
{
	if (index >= count())
	{
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d)", index, count());
	}
	m_collection.erase(m_collection.begin() + index);
}

std::shared_ptr<Transform> TransformCollection::getItem(size_t i)
{
	if (i >= count())
	{
		return nullptr;
	}
	return m_collection[i];
}
