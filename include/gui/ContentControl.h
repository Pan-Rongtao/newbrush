#pragma once
#include "Control.h"

namespace nb{
namespace gui{

class NB_API ContentControl : public Control
{
public:
	explicit ContentControl();
	virtual ~ContentControl() = default;

	Property_rw<shared_ptr<UIElement>>	Content;			//内容
	static DependencyProperty			ContentProperty();	//内容依赖属性
	
	virtual void onRender(std::shared_ptr<Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}
