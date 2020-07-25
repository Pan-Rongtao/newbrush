#include "newbrush/core/media/GradientBrush.h"
#include <algorithm>
#include "glm/glm.hpp"

using namespace nb;

GradientStop::GradientStop()
	: GradientStop(Color(), 0.0f)
{
}

GradientStop::GradientStop(const Color & color, float offset)
{
	setValue(ColorProperty(), color);
	setValue(OffsetPropert(), offset);
}

DependencyPropertyPtr GradientStop::ColorProperty()
{
	static auto dp = DependencyProperty::registerDependency<GradientStop, Color>("Color", Color());
	return dp;
}

DependencyPropertyPtr GradientStop::OffsetPropert()
{
	static auto dp = DependencyProperty::registerDependency<GradientStop, float>("Offset", 0.0f);
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
{
}

DependencyPropertyPtr GradientBrush::GradientStopsProperty()
{
	static auto dp = DependencyProperty::registerDependency<GradientBrush, GradientStopCollectionPtr>("GradientStops", nullptr);
	return dp;
}

LinearGradientBrush::LinearGradientBrush()
	: LinearGradientBrush(nullptr, Point(0.0f, 0.0f), Point(1.0f, 0.0f))
{
}

LinearGradientBrush::LinearGradientBrush(const Color & startColor, const Color & endColor, float angle)
{
	auto xDiff = 1 / std::tanf(glm::radians(angle));
	setValue(StartPointProperty(), Point(0, 0));
	setValue(EndPointProperty(), Point(xDiff, 1));
	setValue(GradientStopsProperty(), std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{ 
		std::make_shared<GradientStop>(startColor, 0.0f),  std::make_shared<GradientStop>(endColor, 1.0f) 
	}) );
}

LinearGradientBrush::LinearGradientBrush(const Color & startColor, const Color & endColor, const Point & startPoint, const Point & endPoint)
{
	setValue(StartPointProperty(), startPoint);
	setValue(EndPointProperty(), endPoint);
	setValue(GradientStopsProperty(), std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{
		std::make_shared<GradientStop>(startColor, 0.0f), std::make_shared<GradientStop>(endColor, 1.0f)
	}));
}

LinearGradientBrush::LinearGradientBrush(GradientStopCollectionPtr gradientStops)
	: LinearGradientBrush(gradientStops, Point(0.0f, 0.0f), Point(1.0f, 0.0f))
{
}

LinearGradientBrush::LinearGradientBrush(GradientStopCollectionPtr gradientStops, float angle)
	: GradientBrush(gradientStops)
{
	auto xDiff = 1 / std::tanf(glm::radians(angle));
	setValue(StartPointProperty(), Point(0, 0));
	setValue(EndPointProperty(), Point(xDiff, 1));
}

LinearGradientBrush::LinearGradientBrush(GradientStopCollectionPtr gradientStops, const Point & startPoint, const Point & endPoint)
	: GradientBrush(gradientStops)
{
	setValue(StartPointProperty(), startPoint);
	setValue(EndPointProperty(), endPoint);
}

DependencyPropertyPtr LinearGradientBrush::StartPointProperty()
{
	static auto dp = DependencyProperty::registerDependency<LinearGradientBrush, Point>("StartPoint", Point());
	return dp;
}

DependencyPropertyPtr LinearGradientBrush::EndPointProperty()
{
	static auto dp = DependencyProperty::registerDependency<LinearGradientBrush, Point>("EndPoint", Point(1.0f, 0.0f));
	return dp;
}
