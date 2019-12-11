#include "gui/UIElementCollection.h"
#include "gui/UIElement.h"

using namespace nb::gui;

UIElementCollection::UIElementCollection(UIElement *logicalParent)
	: m_logicalParent(logicalParent)
{
	
}

uint32_t UIElementCollection::count() const
{
	return m_children.size();
}

void UIElementCollection::add(std::shared_ptr<UIElement> element)
{
	insert(count(), element);
}

void UIElementCollection::insert(uint32_t index, std::shared_ptr<UIElement> element)
{
	if (index > count())
		nbThrowException(std::out_of_range, "index");

	m_children.insert(m_children.begin() + index, element);
	element->setParent(m_logicalParent);
}

void UIElementCollection::remove(std::shared_ptr<UIElement> element)
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

std::shared_ptr<UIElement> UIElementCollection::childAt(uint32_t index)
{
	if (index >= count())
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d]", index, count());
	return m_children[index];
}

bool UIElementCollection::contains(std::shared_ptr<UIElement> element) const
{
	return std::find(m_children.begin(), m_children.end(), element) != m_children.end();
}
