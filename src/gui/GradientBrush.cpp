#include "gui/GradientBrush.h"
#include <algorithm>
#include "glm/glm.hpp"

using namespace nb;
using namespace nb::gui;

GradientStop::GradientStop()
	: GradientStop(nb::Color(), 0.0f)
{
}

GradientStop::GradientStop(const nb::Color & color, float offset)
	: Color([&](nb::Color v) {set(ColorProperty(), v); }, [&]()->nb::Color& {return get<nb::Color>(ColorProperty()); })
	, Offset([&](float v) {set(OffsetPropert(), v); }, [&]()->float& {return get<float>(OffsetPropert()); })
{
	Color = color;
	Offset = offset;
}

DependencyProperty GradientStop::ColorProperty()
{
	static auto dp = DependencyProperty::registerDependency<GradientStop, nb::Color>("Color", nb::Color(), false);
	return dp;
}

DependencyProperty GradientStop::OffsetPropert()
{
	static auto dp = DependencyProperty::registerDependency<GradientStop, float>("Offset", 0.0f, false);
	return dp;
}

GradientStopCollection::GradientStopCollection()
	: GradientStopCollection(std::vector<GradientStop>{})
{
}

GradientStopCollection::GradientStopCollection(const std::vector<GradientStop>& gradientStops)
	: m_gradientStops(gradientStops)
{
}

void GradientStopCollection::insert(int index, const GradientStop & value)
{
	if (index > count())
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d)", index, count());
	m_gradientStops.insert(m_gradientStops.begin() + index, value);
}

void GradientStopCollection::add(const GradientStop & value)
{
	insert(count(), value);
}

void GradientStopCollection::remove(int index)
{
	if (index >= count())
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d)", index, count());
	m_gradientStops.erase(m_gradientStops.begin() + index);
}

bool GradientStopCollection::contains(const GradientStop & value) const
{
	auto iter = std::find_if(m_gradientStops.begin(), m_gradientStops.end(), [&value](const GradientStop &gs) {
		return false;// gs.Color() == value.Color() && gs.Offset() == value.Offset();
	});
	return iter != m_gradientStops.end();
}

int GradientStopCollection::count() const
{
	return m_gradientStops.size();
}

GradientStop &GradientStopCollection::operator[](int index)
{
	return m_gradientStops[index];
}

const GradientStop &GradientStopCollection::operator[](int index) const
{
	return m_gradientStops[index];
}

GradientBrush::GradientBrush()
	: GradientBrush(GradientStopCollection())
{
}

GradientBrush::GradientBrush(const GradientStopCollection & gradientStops)
	: GradientStops([&](GradientStopCollection v) {set(GradientStopsProperty(), v); }, [&]()->GradientStopCollection & {return get<GradientStopCollection>(GradientStopsProperty()); })
{
}

DependencyProperty GradientBrush::GradientStopsProperty()
{
	static auto dp = DependencyProperty::registerDependency<GradientBrush, GradientStopCollection>("GradientStops", GradientStopCollection());
	return dp;
}

LinearGradientBrush::LinearGradientBrush()
	: LinearGradientBrush(GradientStopCollection(), Point(0.0f, 0.0f), Point(1.0f, 0.0f))
{
}

LinearGradientBrush::LinearGradientBrush(const nb::Color & startColor, const nb::Color & endColor, float angle)
	: StartPoint([&](Point v) {set(StartPointProperty(), v); }, [&]()->Point& {return get<Point>(StartPointProperty()); })
	, EndPoint([&](Point v) {set(EndPointProperty(), v); }, [&]()->Point& {return get<Point>(EndPointProperty()); })
{
	auto xDiff = 1 / std::tanf(glm::radians(angle));
	StartPoint = Point(0, 0);
	EndPoint = Point(xDiff, 1);
	GradientStops().add(GradientStop(startColor, 0.0));
	GradientStops().add(GradientStop(endColor, 1.0));
}

LinearGradientBrush::LinearGradientBrush(const nb::Color & startColor, const nb::Color & endColor, const nb::Point & startPoint, const nb::Point & endPoint)
	: StartPoint([&](Point v) {set(StartPointProperty(), v); }, [&]()->Point& {return get<Point>(StartPointProperty()); })
	, EndPoint([&](Point v) {set(EndPointProperty(), v); }, [&]()->Point& {return get<Point>(EndPointProperty()); })
{
	StartPoint = startPoint;
	EndPoint = endPoint;
	GradientStops().add(GradientStop(startColor, 0.0));
	GradientStops().add(GradientStop(endColor, 1.0));
}

LinearGradientBrush::LinearGradientBrush(const GradientStopCollection & gradientStops)
	: LinearGradientBrush(gradientStops, Point(0.0f, 0.0f), Point(1.0f, 0.0f))
{
}

LinearGradientBrush::LinearGradientBrush(const GradientStopCollection & gradientStops, float angle)
	: GradientBrush(gradientStops)
	, StartPoint([&](Point v) {set(StartPointProperty(), v); }, [&]()->Point& {return get<Point>(StartPointProperty()); })
	, EndPoint([&](Point v) {set(EndPointProperty(), v); }, [&]()->Point& {return get<Point>(EndPointProperty()); })
{
	auto xDiff = 1 / std::tanf(glm::radians(angle));
	StartPoint = Point(0, 0);
	EndPoint = Point(xDiff, 1);
}

LinearGradientBrush::LinearGradientBrush(const GradientStopCollection & gradientStops, const nb::Point & startPoint, const nb::Point & endPoint)
	: GradientBrush(gradientStops)
	, StartPoint([&](Point v) {set(StartPointProperty(), v); }, [&]()->Point& {return get<Point>(StartPointProperty()); })
	, EndPoint([&](Point v) {set(EndPointProperty(), v); }, [&]()->Point& {return get<Point>(EndPointProperty()); })
{
	StartPoint = startPoint;
	EndPoint = endPoint;
}

DependencyProperty LinearGradientBrush::StartPointProperty()
{
	static auto dp = DependencyProperty::registerDependency<LinearGradientBrush, Point>("StartPoint", Point());
	return dp;
}

DependencyProperty LinearGradientBrush::EndPointProperty()
{
	static auto dp = DependencyProperty::registerDependency<LinearGradientBrush, Point>("EndPoint", Point(1.0f, 0.0f));
	return dp;
}
