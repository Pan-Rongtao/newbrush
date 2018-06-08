#pragma once

#include <vector>
#include "gui/UIElement.h"
#include "UIElementPrivate.h"

namespace nb { namespace Gui {

class UIElementArrayPrivate
{
public:
	UIElementArrayPrivate(void);
	virtual ~UIElementArrayPrivate(void);

	inline void Add(UIElement *value)
	{
		m_elements.push_back(value);
		value->GetPrivate()->SetParent(m_parentElement);

		if(m_parentElement != NULL)
		{
			m_parentElement->InvalidateMeasure();
			m_parentElement->InvalidateArrange();
		}

		value->InvalidateMeasure();
		value->InvalidateArrange();
	}

	inline void Clear()
	{
		int count = m_elements.size();
		for(int i=0; i<count; i++)
		{
			m_elements[i]->GetPrivate()->SetParent(NULL);
		}
		m_elements.clear();

		if(m_parentElement != NULL)
		{
			m_parentElement->InvalidateMeasure();
			m_parentElement->InvalidateArrange();
		}
	}

	inline void Insert(int index, UIElement *value)
	{
		m_elements.insert(m_elements.begin() + index, value);
		value->GetPrivate()->SetParent(m_parentElement);

		if(m_parentElement != NULL)
		{
			m_parentElement->InvalidateMeasure();
			m_parentElement->InvalidateArrange();
		}

		value->InvalidateMeasure();
		value->InvalidateArrange();
	}

	inline void RemoveAt(int index) {m_elements.erase(m_elements.begin() + index);}
	inline UIElement * GetAt(int index) const {return m_elements[index];}
	inline int GetCount() const{return m_elements.size();}

	inline void SetParentElement(UIElement *parent) {m_parentElement = parent;}
private:
	std::vector<UIElementPtr> m_elements;
	UIElement *m_parentElement;
};

}}
