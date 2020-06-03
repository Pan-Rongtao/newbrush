#pragma once
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/UIElementCollection.h"

namespace nb{

class NB_API Panel : public UIElement
{
	RTTR_ENABLE(UIElement)
public:
	Panel(const Panel &other);
	Panel(const Panel &&other);
	Panel &operator =(const Panel &other);
	Panel &operator =(const Panel &&other);
	virtual ~Panel() = default;

	static DependencyPropertyPtr BackgroundProperty();	//±≥æ∞µƒ“¿¿µ Ù–‘

	UIElementCollection &children();

	void setZIndex(std::shared_ptr<UIElement> element, int index);
	int getZIndex(std::shared_ptr<UIElement> element);

	virtual void onRender(Viewport2D & drawContext) override;

	virtual uint32_t childrenCount() const;

	virtual UIElement *getChild(uint32_t index);

protected:
	Panel();

	UIElementCollection	m_children;
};

}