#pragma once
#include "../core/Def.h"
#include "../core/Property.h"
#include "../core/Size.h"
#include "../core/Rect.h"
#include "../gui/Thickness.h"
#include "../gles/RenderObject.h"

namespace nb{namespace gui{

enum class Visibility
{
	Hidden,
	Visible,
	Collapsed,
};

enum class HorizontalAlignment
{
	HorizontalAlignmentLeft = 0,
	HorizontalAlignmentCenter = 1,
	HorizontalAlignmentRight = 2,
	HorizontalAlignmentStretch = 3
};

enum class VerticalAlignment
{
	VerticalAlignmentTop = 0,
	VerticalAlignmentCenter = 1,
	VerticalAlignmentBottom = 2,
	VerticalAlignmentStretch = 3
};

enum class FlowDirection
{
	LeftToRight,
	RightToLeft,
};

enum class Orientation
{
	Horizontal,
	Vertical,
};


class NB_API UIElement
{
public:
	UIElement();
	virtual ~UIElement();

	void measure(const core::Size &availabelSize);
	void arrage(const core::Rect &finalRect);

public:
	core::Property_rw<Visibility>							Visibility;
	core::Property_rw<double>								Opacity;
	core::Property_rw<bool>									Focusable;
	core::Property_rw<double>								Width;
	core::Property_rw<double>								Height;
	core::Property_rw<double>								MinWidth;
	core::Property_rw<double>								MinHeight;
	core::Property_rw<double>								MaxWidth;
	core::Property_rw<double>								MaxHeight;
	core::Property_r<core::Size>							DesiredSize;
	core::Property_r<core::Size>							ActualSize;
	core::Property_rw<Thickness>							Margin;
	core::Property_rw<HorizontalAlignment>					HorizontalAlignment;
	core::Property_rw<VerticalAlignment>					VerticalAlignment;
	core::Property_rw<FlowDirection>						FlowDirection;
	core::Property_r<std::shared_ptr<UIElement>>			Parent;
	core::Property_r<std::shared_ptr<gl::RenderObject>>		Renderer;

	virtual void renderOverride();

protected:
	virtual core::Size measureOverride(const core::Size &availableSize) const;
	virtual core::Size arrangeOverride(const core::Size &finalSize) const;

private:
	void onVisibilityChanged(const nb::gui::Visibility &_old, const nb::gui::Visibility &_new);
	void onOpacityChanged(const double &_old, const double &_new);
	void onFocusableChanged(const bool &_old, const bool &_new);
	void onDesiredSizeChanged(const core::Size &_old, const core::Size &_new);
	void onMaginChanged(const Thickness &_old, const Thickness &_new);

private:
	nb::core::Size											m_desiredSize;
	std::shared_ptr<gl::RenderObject>						m_renderer;
};

}}
