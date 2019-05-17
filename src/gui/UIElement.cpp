#include "gui/UIElement.h"

using namespace nb::core;
using namespace nb::gl;
using namespace nb::gui;

UIElement::UIElement()
	: Visibility(VisibilityE::Visible)
	, Opacity(1.0)
	, Width(NB_DOUBLE_NAN)
	, Height(NB_DOUBLE_NAN)
	, MaxWidth(NB_DOUBLE_MAX)
	, MaxHeight(NB_DOUBLE_MAX)
	, HorizontalAlignment(HorizontalAlignmentE::HorizontalAlignmentStretch)
	, VerticalAlignment(VerticalAlignmentE::VerticalAlignmentStretch)
	, FlowDirection(FlowDirectionE::LeftToRight)
	, Renderer(std::make_shared<nb::gl::RenderObject>())
{
	DesiredSize.getter([&]()->Size& { return m_desiredSize; });
	ActualSize.getter([&]()->Size& {return m_actualSize; });
	Visibility.notify(std::bind(&UIElement::onVisibilityChanged, this, std::placeholders::_1, std::placeholders::_2));
	Opacity.notify(std::bind(&UIElement::onOpacityChanged, this, std::placeholders::_1, std::placeholders::_2));
	Focusable.notify(std::bind(&UIElement::onFocusableChanged, this, std::placeholders::_1, std::placeholders::_2));
	Margin.notify(std::bind(&UIElement::onMaginChanged, this, std::placeholders::_1, std::placeholders::_2));
}

UIElement::~UIElement()
{
}

void UIElement::measure(const Size & availabelSize)
{
	//如果不可见或两次measure参数一致，忽略
	if ((Visibility != VisibilityE::Visible))
		return;

	//减去magin计算出本来的constrainedSize
	auto constrainedSize = Size(availabelSize.width() - Margin().left() - Margin().right(), availabelSize.height() - Margin().top() - Margin().bottom());
	//如果手动设置了Width，调整Width到bound(MinWidth, MaxWidth, Width)
	//否则，调整Width到(MinWidth, MaxWidth, constrainedSize.width())
	//同样的规则应用于Height
	Width = (float)nb::bound<double>(MinWidth, MaxWidth, (Width != NB_DOUBLE_NAN) ? Width : constrainedSize.width());
	Height = (float)nb::bound<double>(MinHeight, MaxHeight, (Height != NB_DOUBLE_NAN) ? Height : constrainedSize.height());
	constrainedSize.reset((float)Width, (float)Height);

	//measureOverride返回控件期望大小desiredSizeTemp，需要调整到保证在(Min, Max)区间
	//如果手动设置了Width，调整Width到(MinWidth, MaxWidth, Width)
	//否则，调整Width到(MinWidth, MaxWidth, constrainedSize.width())
	//同样的规则应用于Height
	auto desiredSizeTemp = measureOverride(constrainedSize);
	Width = (float)nb::bound<double>(MinWidth, MaxWidth, (Width != NB_DOUBLE_NAN) ? Width : desiredSizeTemp.width());
	Height = (float)nb::bound<double>(MinHeight, MaxHeight, (Height != NB_DOUBLE_NAN) ? Height : desiredSizeTemp.height());
	desiredSizeTemp.reset(Width, Height);

	//由于child不关注和计算magin，因此需重新+margin
	desiredSizeTemp += Size(Margin().left() + Margin().right(), Margin().top() + Margin().bottom());
	//保证在（0, availabelSize)区间
	desiredSizeTemp.width() = (float)nb::bound<double>(0.0, availabelSize.width(), desiredSizeTemp.width());
	desiredSizeTemp.height() = (float)nb::bound<double>(0.0, availabelSize.height(), desiredSizeTemp.height());
	m_desiredSize = desiredSizeTemp;
}

void UIElement::arrage(const Rect & finalRect)
{
	//如果不可见或两次arrage参数一致，忽略
	if ((Visibility != VisibilityE::Visible))
		return;

	//减去magin计算出本来的arrangeSize以及clientSize
	auto arrangeSize = Size(finalRect.width() - Margin().left() - Margin().right(), finalRect.height() - Margin().top() - Margin().bottom());
	auto clientSize = arrangeSize;
	//调整arrange大于DesiredSize
	arrangeSize.reset(std::max(DesiredSize().width(), arrangeSize.width()), std::max(DesiredSize().height(), arrangeSize.height()));
	//如果Aligment不是Stretch，直接将arrangeSize设置为DesiredSize，以保证传入arrangeOverride的arrangeSize没有Stretch
	if (HorizontalAlignment != HorizontalAlignmentE::HorizontalAlignmentStretch)
		arrangeSize.setWidth(DesiredSize().width());
	if (VerticalAlignment != VerticalAlignmentE::VerticalAlignmentStretch)
		arrangeSize.setHeight(DesiredSize().height());

	//如果手动设置了Width，调整Width到bound(MinWidth, MaxWidth, Width)
	//否则，调整Width到(MinWidth, MaxWidth, arrangeSize.width())
	//同样的规则应用于Height
	Width = (float)nb::bound<double>(MinWidth, MaxWidth, (Width != NB_DOUBLE_NAN) ? Width : arrangeSize.width());
	Height = (float)nb::bound<double>(MinHeight, MaxHeight, (Height != NB_DOUBLE_NAN) ? Height : arrangeSize.height());
	arrangeSize.reset((float)Width, (float)Height);

	//arrangeOverride后的RenderSize是不需要调整的非裁剪区域，而不是最终的可见区域
	auto innerInkSize = arrangeOverride(arrangeSize);
	RenderSize = innerInkSize;
	//裁剪，保证innerInkSize在Max之内
	if (Width == NB_DOUBLE_NAN)
		if (innerInkSize.width() > MaxWidth)	innerInkSize.width() = (float)MaxWidth;
	if (Height == NB_DOUBLE_NAN)
		if (innerInkSize.height() > MaxHeight)	innerInkSize.height() = (float)MaxHeight;
	Size clipInkSize(std::min((double)innerInkSize.width(), Width()), std::min((double)innerInkSize.height(), Height()));

	switch (HorizontalAlignment)
	{
	case HorizontalAlignmentE::HorizontalAlignmentLeft:		Offset().x() = finalRect.x() + Margin().left();														break;
	case HorizontalAlignmentE::HorizontalAlignmentCenter:	Offset().x() = finalRect.x() + Margin().left() + (clientSize.width() - RenderSize().width()) / 2;	break;
	case HorizontalAlignmentE::HorizontalAlignmentRight:	Offset().x() = finalRect.width() - Margin().right() - RenderSize().width();							break;
	default:
	{
		if (RenderSize().width() >= clientSize.width())
		{
			Offset().x() = finalRect.left() + Margin().left();
		}
		else
		{
			Offset().x() = finalRect.x() + Margin().left() + (clientSize.width() - RenderSize().width()) / 2;
		}
	}
		break;
	}

	switch (VerticalAlignment)
	{
	case VerticalAlignmentE::VerticalAlignmentTop:		Offset().y() = finalRect.top() + Margin().top();														break;
	case VerticalAlignmentE::VerticalAlignmentCenter:	Offset().y() = finalRect.top() + Margin().top() + (clientSize.height() - RenderSize().height()) / 2;	break;
	case VerticalAlignmentE::VerticalAlignmentBottom:	Offset().y() = finalRect.height() - Margin().bottom() - RenderSize().height();							break;
	default:
	{
		if (RenderSize().height() >= clientSize.height())
		{
			Offset().y() = finalRect.top() + Margin().top();
		}
		else
		{
			Offset().x() = finalRect.x() + Margin().left() + (clientSize.width() - RenderSize().width()) / 2;
		}
	}
		break;
	}
	m_actualSize = RenderSize;
}

Size UIElement::measureOverride(const Size & availableSize)
{
	return Size();
}

Size UIElement::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}

void UIElement::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
}

void UIElement::onVisibilityChanged(const nb::gui::VisibilityE & _old, const nb::gui::VisibilityE & _new)
{

}

void UIElement::onOpacityChanged(const double & _old, const double & _new)
{
}

void UIElement::onFocusableChanged(const bool & _old, const bool & _new)
{
}

void UIElement::onDesiredSizeChanged(const Size & _old, const Size & _new)
{
}

void UIElement::onMaginChanged(const Thickness & _old, const Thickness & _new)
{
}
