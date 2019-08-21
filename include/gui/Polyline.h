#pragma once
#include "../gui/Shape.h"
#include "../core/Point.h"

namespace nb { namespace gl {
	class Polyline;
}}

namespace nb{
namespace gui {

class NB_API Polyline : public Shape
{
public:
	Polyline();
	virtual ~Polyline() = default;

	Property_rw<std::vector<Point>>	Points;

	static const DependencyProperty				PointsProperty();

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}
