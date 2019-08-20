#pragma once
#include "../gui/Shape.h"

namespace nb{ namespace gl{
	class Line;
}}

namespace nb{ namespace gui{

class NB_API Line : public Shape
{
public:
	Line();
	virtual ~Line() = default;

	Property_rw<float>				X1;
	Property_rw<float>				X2;
	Property_rw<float>				Y1;
	Property_rw<float>				Y2;

	static const DependencyProperty	X1Property();
	static const DependencyProperty	X2Property();
	static const DependencyProperty	Y1Property();
	static const DependencyProperty	Y2Property();

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

};

}}