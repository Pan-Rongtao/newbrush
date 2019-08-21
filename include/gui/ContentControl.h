#pragma once
#include "Control.h"

namespace nb{
namespace gui{

class NB_API ContentControl : public Control
{
public:
	explicit ContentControl(std::shared_ptr<UIElement> content = nullptr);
	virtual ~ContentControl() = default;

	Property_rw<std::shared_ptr<UIElement>>	Content;

	static const DependencyProperty			ContentProperty();
	
	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}
