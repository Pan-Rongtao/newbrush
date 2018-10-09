#pragma once
#include "../core/Def.h"
#include "../core/Property.h"
#include "../core/Size.h"
#include "../core/Rect.h"
#include "../gui/Thickness.h"

namespace nb{namespace gui{

enum Visibility
{
	Hidden,
	Visible,
	Collapsed,
};

enum HorizontalAlignment
{
	HorizontalAlignmentLeft = 0,
	HorizontalAlignmentCenter = 1,
	HorizontalAlignmentRight = 2,
	HorizontalAlignmentStretch = 3
};

enum VerticalAlignment
{
	VerticalAlignmentTop = 0,
	VerticalAlignmentCenter = 1,
	VerticalAlignmentBottom = 2,
	VerticalAlignmentStretch = 3
};

enum FlowDirection
{
	LeftToRight,
	RightToLeft,
};

enum Orientation
{
	Horizontal,
	Vertical,
};


class NB_API UIElement
{
public:
	UIElement();
	virtual ~UIElement();

	void measure(const nb::core::Size &availabelSize);
	void arrage(const nb::core::Rect &finalRect);

public:
	nb::core::Property_rw<Visibility>			Visibility;
	nb::core::Property_rw<double>				Opacity;
	nb::core::Property_rw<bool>					Focusable;
	nb::core::Property_rw<double>				Width;
	nb::core::Property_rw<double>				Height;
	nb::core::Property_rw<double>				MinWidth;
	nb::core::Property_rw<double>				MinHeight;
	nb::core::Property_rw<double>				MaxWidth;
	nb::core::Property_rw<double>				MaxHeight;
	nb::core::Property_rw<nb::core::Size>		DesiredSize;
	nb::core::Property_r<nb::core::Size>		ActualSize;
	nb::core::Property_rw<Thickness>			Magin;
	nb::core::Property_rw<HorizontalAlignment>	HorizontalAlignment;
	nb::core::Property_rw<VerticalAlignment>	VerticalAlignment;
	nb::core::Property_rw<FlowDirection>		FlowDirection;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) const;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) const;

private:
	void onVisibilityChanged(const bool &_old, const bool &_new);
	void onOpacityChanged(const double &_old, const double &_new);
	void onFocusableChanged(const bool &_old, const bool &_new);
	void onDesiredSizeChanged(const nb::core::Size &_old, const nb::core::Size &_new);
	void onMaginChanged(const Thickness &_old, const Thickness &_new);


};

}}