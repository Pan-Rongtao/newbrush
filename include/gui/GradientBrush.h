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

class NB_API GradientStopCollection
{
public:
	GradientStopCollection();
	GradientStopCollection(const std::vector<GradientStop> &gradientStops);

	void insert(int index, const GradientStop &value);
	void add(const GradientStop &value);
	void remove(int index);
	bool contains(const GradientStop &value) const;
	int count() const;

	bool operator != (const GradientStopCollection &other) const { return true; }

private:
	std::vector<GradientStop>	m_gradientStops;
};
	
class NB_API GradientBrush : public Brush
{
public:
	Property_rw<GradientStopCollection>		GradientStops;
	static DependencyProperty				GradientStopsProperty();

protected:
	GradientBrush();
	GradientBrush(const GradientStopCollection &gradientStops);

};


//class LinearGradientBrush
class NB_API LinearGradientBrush : public GradientBrush
{
public:
	LinearGradientBrush();
	LinearGradientBrush(const nb::Color &startColor, const nb::Color &endColor, float angle);
	LinearGradientBrush(const nb::Color &startColor, const nb::Color &endColor, const nb::Point &startPoint, const nb::Point &endPoint);
	LinearGradientBrush(const GradientStopCollection &gradientStops);
	LinearGradientBrush(const GradientStopCollection &gradientStops, float angle);
	LinearGradientBrush(const GradientStopCollection &gradientStops, const nb::Point &startPoint, const nb::Point &endPoint);

	Property_rw<Point>			StartPoint;
	Property_rw<Point>			EndPoint;
	static DependencyProperty	StartPointProperty();
	static DependencyProperty	EndPointProperty();
};

}}