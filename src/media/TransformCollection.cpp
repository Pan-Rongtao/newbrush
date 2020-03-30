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

size_t TransformCollection::Count()
{
	return m_collection.size();
}

void TransformCollection::Add(std::shared_ptr<Transform> value)
{
	m_collection.push_back(value);
}

void TransformCollection::Clear()
{
	m_collection.clear();
}

bool TransformCollection::Contains(std::shared_ptr<Transform> value)
{
	return std::count(m_collection.begin(), m_collection.end(), value);
}

int TransformCollection::IndexOf(std::shared_ptr<Transform> value)
{
	auto  iter = std::find(m_collection.begin(), m_collection.end(), value);

	return iter != m_collection.end() ? iter - m_collection.begin() : -1;
}

void TransformCollection::Insert(size_t index, std::shared_ptr<Transform> value)
{
	m_collection.insert(m_collection.begin() + index, value);
}

bool TransformCollection::Remove(std::shared_ptr<Transform> value)
{
	auto  iter = std::find(m_collection.begin(), m_collection.end(), value);

	if (iter != m_collection.end())
	{
		m_collection.erase(iter);
		return true;
	}
	return false;
}

void TransformCollection::RemoveAt(size_t index)
{
	if (index >= Count())
	{
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d)", index, Count());
	}
	m_collection.erase(m_collection.begin() + index);
}

std::shared_ptr<Transform> TransformCollection::GetItem(size_t i)
{
	if (i >= Count())
	{
		return nullptr;
	}

	return m_collection[i];
}
