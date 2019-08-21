#pragma once
#include "../gui/Shape.h"

namespace nb { namespace gui {

class NB_API Rectangle : public Shape
{
public:
	Rectangle();
	virtual ~Rectangle() = default;

	Property_rw<float>					RadiusX;
	Property_rw<float>					RadiusY;

	static const DependencyProperty		RadiusXProperty();
	static const DependencyProperty		RadiusYProperty();

	virtual void onRender(std::shared_ptr<gl::Context> drawContext);

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

	Size	m_availableSize;
};

}}
