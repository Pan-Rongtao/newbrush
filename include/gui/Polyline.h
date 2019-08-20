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

	core::Property_rw<std::vector<core::Point>>	Points;

	static const DependencyProperty				PointsProperty();

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

};

}}
