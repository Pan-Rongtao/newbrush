#pragma once
#include <vector>
#include "newbrush/core/Def.h"

namespace nb {

class UIElement;
using UIElementPtr = std::shared_ptr<UIElement>;
class NB_API UIElementCollection
{
public:
	UIElementCollection(UIElement *logicalParent);

	void changeLogicalParent(UIElement *logicalParent);

	void add(UIElementPtr element);

	void insert(uint32_t index, UIElementPtr child);

	uint32_t count() const;

	void remove(UIElementPtr child);

	void removeAt(uint32_t index);

	void removeRange(uint32_t index, uint32_t count);

	void clear();

	UIElementPtr childAt(uint32_t index);

	bool contains(UIElementPtr element) const;

private:
	std::vector<UIElementPtr>	m_children;
	UIElement					*m_logicalParent;
};

}