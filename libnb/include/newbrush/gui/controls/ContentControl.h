﻿#pragma once
#include "newbrush/gui/controls/Control.h"

namespace nb{

class NB_API ContentControl : public Control
{
	RTTR_ENABLE(Control)
public:
	explicit ContentControl() = default;
	virtual ~ContentControl() = default;

	static DependencyPropertyPtr ContentProperty();	//内容依赖属性
	
	virtual void onRender(DrawingContextPtr dc) override;

	virtual uint32_t childrenCount() const;

	virtual UIElement *getChild(uint32_t index);

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;

	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}