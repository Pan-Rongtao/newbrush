#pragma once
#include "../gui/UIElement.h"

namespace nb{
class Brush;
namespace gui{

class NB_API Panel : public UIElement
{
public:
	virtual ~Panel() = default;

	Property_rw<shared_ptr<Brush>>	Background;				//±≥æ∞
	static DependencyProperty		BackgroundProperty();	//±≥æ∞µƒ“¿¿µ Ù–‘

	void setZIndex(std::shared_ptr<UIElement> element, int index);
	int getZIndex(std::shared_ptr<UIElement> element);

	virtual void onRender(Viewport2D & drawContext) override;

protected:
	Panel();
};

}}