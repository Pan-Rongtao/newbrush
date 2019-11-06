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
	: GradientStopCollection(std::vector<GradientStopPtr>{})
{
}

GradientStopCollection::GradientStopCollection(const std::vector<GradientStopPtr>& gradientStops)
	: m_gradientStops(gradientStops)
{
}

void GradientStopCollection::insert(int index, GradientStopPtr value)
{
	if (index > count())
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d)", index, count());
	m_gradientStops.insert(m_gradientStops.begin() + index, value);
}

void GradientStopCollection::add(GradientStopPtr value)
{
	insert(count(), value);
}

void GradientStopCollection::remove(int index)
{
	if (index >= count())
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d)", index, count());
	m_gradientStops.erase(m_gradientStops.begin() + index);
}

bool GradientStopCollection::contains(GradientStopPtr value) const
{
	auto iter = std::find(m_gradientStops.begin(), m_gradientStops.end(), value);
	return iter != m_gradientStops.end();
}

int GradientStopCollection::count() const
{
	return m_gradientStops.size();
}

GradientStopPtr GradientStopCollection::operator[](int index)
{
	return m_gradientStops[index];
}

GradientBrush::GradientBrush()
	: GradientBrush(nullptr)
{
}

GradientBrush::GradientBrush(GradientStopCollectionPtr gradientStops)
	: GradientStops([&](GradientStopCollectionPtr v) {set(GradientStopsProperty(), v); }, [&]()->GradientStopCollectionPtr & {return get<GradientStopCollectionPtr>(GradientStopsProperty()); })
{
}

DependencyProperty GradientBrush::GradientStopsProperty()
{
	static auto dp = DependencyProperty::registerDependency<GradientBrush, GradientStopCollectionPtr>("GradientStops", nullptr);
	return dp;
}

LinearGradientBrush::LinearGradientBrush()
	: LinearGradientBrush(nullptr, Point(0.0f, 0.0f), Point(1.0f, 0.0f))
{
}

LinearGradientBrush::LinearGradientBrush(const nb::Color & startColor, const nb::Color & endColor, float angle)
	: StartPoint([&](Point v) {set(StartPointProperty(), v); }, [&]()->Point& {return get<Point>(StartPointProperty()); })
	, EndPoint([&](Point v) {set(EndPointProperty(), v); }, [&]()->Point& {return get<Point>(EndPointProperty()); })
{
	auto xDiff = 1 / std::tanf(glm::radians(angle));
	StartPoint = Point(0, 0);
	EndPoint = Point(xDiff, 1);
	GradientStops()->add(std::make_shared<GradientStop>(startColor, 0.0f));
	GradientStops()->add(std::make_shared<GradientStop>(endColor, 1.0f));
}

LinearGradientBrush::LinearGradientBrush(const nb::Color & startColor, const nb::Color & endColor, const nb::Point & startPoint, const nb::Point & endPoint)
	: StartPoint([&](Point v) {set(StartPointProperty(), v); }, [&]()->Point& {return get<Point>(StartPointProperty()); })
	, EndPoint([&](Point v) {set(EndPointProperty(), v); }, [&]()->Point& {return get<Point>(EndPointProperty()); })
{
	StartPoint = startPoint;
	EndPoint = endPoint;
	GradientStops()->add(std::make_shared<GradientStop>(startColor, 0.0f));
	GradientStops()->add(std::make_shared<GradientStop>(endColor, 1.0f));
}

LinearGradientBrush::LinearGradientBrush(GradientStopCollectionPtr gradientStops)
	: LinearGradientBrush(gradientStops, Point(0.0f, 0.0f), Point(1.0f, 0.0f))
{
}

LinearGradientBrush::LinearGradientBrush(GradientStopCollectionPtr gradientStops, float angle)
	: GradientBrush(gradientStops)
	, StartPoint([&](Point v) {set(StartPointProperty(), v); }, [&]()->Point& {return get<Point>(StartPointProperty()); })
	, EndPoint([&](Point v) {set(EndPointProperty(), v); }, [&]()->Point& {return get<Point>(EndPointProperty()); })
{
	auto xDiff = 1 / std::tanf(glm::radians(angle));
	StartPoint = Point(0, 0);
	EndPoint = Point(xDiff, 1);
}

LinearGradientBrush::LinearGradientBrush(GradientStopCollectionPtr gradientStops, const nb::Point & startPoint, const nb::Point & endPoint)
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
