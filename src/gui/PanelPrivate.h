#pragma once

#include <vector>
#include "gui/UIElement.h"
#include "UIElementPrivate.h"
#include "ElementRender.h"
#include "gui/UIElementArray.h"

namespace nb { namespace Gui {

class Panel;
class PanelPrivate : public IElementRender
{
public:
	PanelPrivate(Panel * owner);
	virtual ~PanelPrivate(void);

//	void AddChild(UIElement *element);
//	int GetChildCount() const;
//	UIElement * GetChild(int index) const;

	UIElementArray * GetChildren() {return &m_array;}

	virtual void OnRender(float x, float y);

//	std::vector<UIElementPtr> m_childs;

	UIElementArray m_array;
private:
	Panel * m_owner;
};

}}
