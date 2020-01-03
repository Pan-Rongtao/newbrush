#pragma once
#include "../gui/UIElement.h"
#include "../gui/UIElementCollection.h"

namespace nb{
class Brush;
namespace gui{

class NB_API Panel : public UIElement
{
public:
	virtual ~Panel() = default;

	Property_rw<std::shared_ptr<Brush>>	Background;				//背景
	Property_rw<UIElementCollection>	Children;				//子元素集合
	static DependencyProperty		BackgroundProperty();	//背景的依赖属性

	void setZIndex(std::shared_ptr<UIElement> element, int index);
	int getZIndex(std::shared_ptr<UIElement> element);

	virtual void onRender(Viewport2D & drawContext) override;

protected:
	Panel();

	UIElementCollection	m_children;
};

}}