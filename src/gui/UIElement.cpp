#include "gui/UIElement.h"

using namespace nb::core;
using namespace nb::gl;
using namespace nb::gui;

UIElement::UIElement()
	: Visibility(Visibility)
	, Opacity(1.0)
	, Width(NB_DOUBLE_NAN)
	, Height(NB_DOUBLE_NAN)
	, MaxWidth(NB_DOUBLE_MAX)
	, MaxHeight(NB_DOUBLE_MAX)
	, HorizontalAlignment(HorizontalAlignment::HorizontalAlignmentStretch)
	, VerticalAlignment(VerticalAlignment::VerticalAlignmentStretch)
	, FlowDirection(FlowDirection::LeftToRight)
	, Renderer(std::make_shared<nb::gl::RenderObject>())
{
	DesiredSize.bind([&]()->Size& { return m_desiredSize; });
//	Renderer.bind([&]()->std::shared_ptr<RenderObject>& {return m_renderer; });
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
	if ((Visibility != Visibility::Visible))
		return;

	//减去magin计算出本来的constrainedSize
	Size constrainedSize = Size(availabelSize.width() - Margin().left() - Margin().right(), availabelSize.height() - Margin().top() - Margin().bottom());
	//如果手动设置了Width，调整constrainedSize.width()到bound(MinWidth, MaxWidth, Width)
	//否则若未手动设置Width，调整constrainedSize.width()到(MinWidth, MaxWidth, constrainedSize.width())
	//同样的规则应用于Height
	constrainedSize.width() = (float)nb::bound<double>(MinWidth, MaxWidth, (Width == NB_DOUBLE_NAN) ? constrainedSize.width() : Width);
	Width = constrainedSize.width();
	constrainedSize.height() = (float)nb::bound<double>(MinHeight, MaxHeight, (Height == NB_DOUBLE_NAN) ? constrainedSize.height() : Height);
	Height = constrainedSize.height();

	//mesure后更新了desiredSize
	//重新调整DesiredSize
	//如果手动设置了Width，调整DesiredSize.width()到(MinWidth, MaxWidth, Width)
	//否则若未手动设置
	measureOverride(constrainedSize);
	m_desiredSize.width() = (float)nb::bound<double>(MinWidth, MaxWidth, (Width == NB_DOUBLE_NAN) ? m_desiredSize.width() : Width);
	Width = m_desiredSize.width();
	m_desiredSize.height() = (float)nb::bound<double>(MinHeight, MaxHeight, (Height == NB_DOUBLE_NAN) ? m_desiredSize.height() : Height);
	Height = m_desiredSize.height();

	//由于child不关注和计算magin，因此需重新+margin
	m_desiredSize.width() += (Margin().left() + Margin().right());
	m_desiredSize.height() += (Margin().top() + Margin().bottom());
	m_desiredSize.width() = (float)nb::bound<double>(0.0, availabelSize.width(), m_desiredSize.width());
	m_desiredSize.height() = (float)nb::bound<double>(0.0, availabelSize.height(), m_desiredSize.height());
}

void UIElement::arrage(const Rect & finalRect)
{
}

Size UIElement::measureOverride(const Size & availableSize)
{
	return Size();
}

Size UIElement::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}

void UIElement::init()
{
}

void UIElement::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
}

void UIElement::onVisibilityChanged(const nb::gui::Visibility & _old, const nb::gui::Visibility & _new)
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
