#pragma once
#include "../core/Def.h"
#include "../core/Property.h"
#include "../core/Size.h"
#include "../core/Rect.h"
#include "../gui/Thickness.h"
#include "../gles/RenderObject.h"
#include "../gui/AnimationTimeline.h"

namespace nb{ namespace gl{
	class Context;
}}

namespace nb{namespace gui{

enum class VisibilityE
{
	Hidden,
	Visible,
	Collapsed,
};

enum class HorizontalAlignmentE
{
	Left,
	Center,
	Right,
	Stretch,
};

enum class VerticalAlignmentE
{
	Top,
	Center,
	Bottom,
	Stretch,
};

enum class FlowDirectionE
{
	LeftToRight,
	RightToLeft,
};

enum class OrientationE
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
	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext);


public:
	core::Property_rw<VisibilityE>							Visibility;
	core::Property_rw<float>								Opacity;
	core::Property_rw<bool>									Focusable;
	core::Property_rw<float>								Width;
	core::Property_rw<float>								Height;
	core::Property_rw<float>								MinWidth;
	core::Property_rw<float>								MinHeight;
	core::Property_rw<float>								MaxWidth;
	core::Property_rw<float>								MaxHeight;
	core::Property_r<core::Size>							DesiredSize;
	core::Property_r<core::Size>							ActualSize;
	core::Property_rw<core::Size>							RenderSize;
	core::Property_rw<core::Point>							Offset;
	core::Property_rw<Thickness>							Margin;
	core::Property_rw<HorizontalAlignmentE>					HorizontalAlignment;
	core::Property_rw<VerticalAlignmentE>					VerticalAlignment;
	core::Property_rw<FlowDirectionE>						FlowDirection;
	core::Property_r<std::shared_ptr<UIElement>>			Parent;
	core::Property_r<std::shared_ptr<gl::RenderObject>>		Renderer;
	
protected:
	virtual core::Size measureOverride(const core::Size &availableSize);
	virtual core::Size arrangeOverride(const core::Size &finalSize);

private:
	void onVisibilityChanged(const gui::VisibilityE &_old, const gui::VisibilityE &_new);
	void onOpacityChanged(const float &_old, const float &_new);
	void onFocusableChanged(const bool &_old, const bool &_new);
	void onDesiredSizeChanged(const core::Size &_old, const core::Size &_new);
	void onMaginChanged(const Thickness &_old, const Thickness &_new);

	nb::core::Size											m_desiredSize;
	nb::core::Size											m_actualSize;
	std::shared_ptr<gl::RenderObject>						m_renderer;
};

}

}
