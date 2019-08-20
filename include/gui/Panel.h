#pragma once
#include <vector>
#include "../gui/UIElement.h"
#include "../gui/Brush.h"

namespace nb{namespace gui{

class NB_API Panel : public UIElement
{
public:
	virtual ~Panel();

	void setZIndex(std::shared_ptr<UIElement> element, int index);
	int getZIndex(std::shared_ptr<UIElement> element);

	Property_rw<shared_ptr<Brush>>	Background;
	static const DependencyProperty	BackgroundProperty();

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	Panel();
};

}}