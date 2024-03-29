﻿#include "newbrush/gui/UIElementCollection.h"

using namespace nb;

UIElementCollection::UIElementCollection(UIElement *logicalParent)
	: m_logicalParent(logicalParent)
{
	
}

void UIElementCollection::changeLogicalParent(UIElement * logicalParent)
{
	m_logicalParent = logicalParent;
	for (auto const child : m_children)
	{
		m_logicalParent->addLogicalChild(child);
	}
}

uint32_t UIElementCollection::count() const
{
	return m_children.size();
}

void UIElementCollection::add(UIElementPtr element)
{
	insert(count(), element);
}

void UIElementCollection::insert(uint32_t index, UIElementPtr element)
{
	if (index > count())
		nbThrowException(std::out_of_range, "index");

	m_children.insert(m_children.begin() + index, element);
	m_logicalParent->addLogicalChild(element);
}

void UIElementCollection::remove(UIElementPtr element)
{
	auto iter = std::find(m_children.begin(), m_children.end(), element);
	if (iter != m_children.end())
	{
		m_children.erase(iter);
		return;
	}
}

void UIElementCollection::removeAt(uint32_t index)
{
	if (index >= this->count())
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d)", index, this->count());
	m_children.erase(m_children.begin() + index);
}

void UIElementCollection::removeRange(uint32_t index, uint32_t count)
{
	if (index >= this->count())
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d)", index, this->count());
	auto end = index + count < this->count() ? m_children.begin() + index + count : m_children.end();
	m_children.erase(m_children.begin() + index, end);
}

void UIElementCollection::clear()
{
	m_children.clear();
}

UIElementPtr UIElementCollection::childAt(uint32_t index)
{
	if (index >= count())
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d]", index, count());
	return m_children[index];
}

bool UIElementCollection::contains(UIElementPtr element) const
{
	return std::find(m_children.begin(), m_children.end(), element) != m_children.end();
}
