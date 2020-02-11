#pragma once
#include <vector>
#include "newbrush/core/Def.h"

namespace nb {
namespace gui {

class UIElement;
class NB_API UIElementCollection
{
public:
	UIElementCollection(UIElement *logicalParent);

	void add(std::shared_ptr<UIElement> element);

	void insert(uint32_t index, std::shared_ptr<UIElement> child);

	uint32_t count() const;

	void remove(std::shared_ptr<UIElement> child);

	void removeAt(uint32_t index);

	void removeRange(uint32_t index, uint32_t count);

	void clear();

	std::shared_ptr<UIElement> childAt(uint32_t index);

	bool contains(std::shared_ptr<UIElement> element) const;

private:
	std::vector<std::shared_ptr<UIElement>>	m_children;
	UIElement				*m_logicalParent;
};

}}