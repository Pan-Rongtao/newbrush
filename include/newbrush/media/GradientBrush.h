#pragma once
#include "newbrush/media/Brush.h"

namespace nb{

class NB_API GradientStop : public DependencyObject
{
public:
	GradientStop();
	GradientStop(const nb::Color &color, float offset);

	static DependencyPropertyPtr ColorProperty();
	static DependencyPropertyPtr OffsetPropert();
};
using GradientStopPtr = std::shared_ptr<GradientStop>;

class NB_API GradientStopCollection
{
public:
	GradientStopCollection();
	GradientStopCollection(const std::vector<GradientStopPtr> &gradientStops);

	void insert(int index, GradientStopPtr value);
	void add(GradientStopPtr value);
	void remove(int index);
	bool contains(GradientStopPtr value) const;
	int count() const;
	GradientStopPtr operator[](int index);

private:
	std::vector<GradientStopPtr>	m_gradientStops;
};
using GradientStopCollectionPtr = std::shared_ptr<GradientStopCollection>;
	
class NB_API GradientBrush : public Brush
{
public:
	static DependencyPropertyPtr GradientStopsProperty();

protected:
	GradientBrush();
	GradientBrush(GradientStopCollectionPtr gradientStops);

};
using GradientBrushPtr = std::shared_ptr<GradientBrush>;


//class LinearGradientBrush
class NB_API LinearGradientBrush : public GradientBrush
{
public:
	LinearGradientBrush();
	LinearGradientBrush(const nb::Color &startColor, const nb::Color &endColor, float angle);
	LinearGradientBrush(const nb::Color &startColor, const nb::Color &endColor, const nb::Point &startPoint, const nb::Point &endPoint);
	LinearGradientBrush(GradientStopCollectionPtr gradientStops);
	LinearGradientBrush(GradientStopCollectionPtr gradientStops, float angle);
	LinearGradientBrush(GradientStopCollectionPtr gradientStops, const nb::Point &startPoint, const nb::Point &endPoint);

	static DependencyPropertyPtr StartPointProperty();
	static DependencyPropertyPtr EndPointProperty();
};
using LinearGradientBrushPtr = std::shared_ptr<LinearGradientBrush>;

}