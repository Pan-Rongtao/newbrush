#pragma once
#include "Brush.h"

namespace nb{
namespace gui{

class NB_API GradientStop : public DependencyObject
{
public:
	GradientStop();
	GradientStop(const nb::Color &color, float offset);

	Property_rw<nb::Color>		Color;
	Property_rw<float>			Offset;
	static DependencyProperty	ColorProperty();
	static DependencyProperty	OffsetPropert();
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
	Property_rw<GradientStopCollectionPtr>		GradientStops;
	static DependencyProperty				GradientStopsProperty();

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

	Property_rw<Point>			StartPoint;
	Property_rw<Point>			EndPoint;
	static DependencyProperty	StartPointProperty();
	static DependencyProperty	EndPointProperty();
};
using LinearGradientBrushPtr = std::shared_ptr<LinearGradientBrush>;

}}