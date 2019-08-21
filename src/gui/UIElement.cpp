#include "gui/UIElement.h"
#include "gui/Window.h"

using namespace nb;
using namespace nb::gl;
using namespace nb::gui;

UIElement::UIElement()
	: Visibility([&](VisibilityE v) {set(VisibilityProperty(), v); }, [&]() {return get<VisibilityE>(VisibilityProperty()); })
	, Opacity([&](float v) {set(OpacityProperty(), v); }, [&]() {return get<float>(OpacityProperty()); })
	, Focusable([&](bool v) {set(FocusableProperty(), v); }, [&]() {return get<bool>(FocusableProperty()); })
	, Width([&](float v) {set(WidthProperty(), v); }, [&]() {return get<float>(WidthProperty()); })
	, Height([&](float v) {set(HeightProperty(), v); }, [&]() {return get<float>(HeightProperty()); })
	, MinWidth([&](float v) {set(MinWidthProperty(), v); }, [&]() {return get<float>(MinWidthProperty()); })
	, MinHeight([&](float v) {set(MinHeightProperty(), v); }, [&]() {return get<float>(MinHeightProperty()); })
	, MaxWidth([&](float v) {set(MaxWidthProperty(), v); }, [&]() {return get<float>(MaxWidthProperty()); })
	, MaxHeight([&](float v) {set(MaxHeightProperty(), v); }, [&]() {return get<float>(MaxHeightProperty()); })
	, DesiredSize([&]() {return get<Size>(DesiredSizeProperty()); })
	, ActualSize([&]() {return get<Size>(ActualSizeProperty()); })
	, RenderSize([&](Size v) {set(RenderSizeProperty(), v); }, [&]() {return get<Size>(RenderSizeProperty()); })
	, Offset([&](Point v) {set(OffsetProperty(), v); }, [&]() {return get<Point>(OffsetProperty()); })
	, Margin([&](Thickness v) {set(MarginProperty(), v); }, [&]() {return get<Thickness>(MarginProperty()); })
	, HorizontalAlignment([&](HorizontalAlignmentE v) {set(HorizontalAlignmentProperty(), v); }, [&]() {return get<HorizontalAlignmentE>(HorizontalAlignmentProperty()); })
	, VerticalAlignment([&](VerticalAlignmentE v) {set(VerticalAlignmentProperty(), v); }, [&]() {return get<VerticalAlignmentE>(VerticalAlignmentProperty()); })
	, FlowDirection([&](FlowDirectionE v) {set(FlowDirectionProperty(), v); }, [&]() {return get<FlowDirectionE>(FlowDirectionProperty()); })
	, Renderer([&]() {return get<shared_ptr<RenderObject>>(RendererProperty()); })
	, style([&](shared_ptr<Style> v) {set(StyleProperty(), v); }, [&]() {return get<shared_ptr<Style>>(StyleProperty()); })
	//, StateMachine([&](shared_ptr<VisualStateMachine> v) {set(StateMachineProperty(), v); }, [&]() {return get<shared_ptr<VisualStateMachine>>(StateMachineProperty()); })
{
	PropertyChanged += std::bind(&UIElement::onPropertyChanged, this, std::placeholders::_1);
}

const DependencyProperty UIElement::VisibilityProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, VisibilityE>("Visibility", VisibilityE::Visible);
	return dp;
}

const DependencyProperty UIElement::OpacityProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, float>("Opacity", 1.0f);
	return dp;
}

const DependencyProperty UIElement::FocusableProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, bool>("Focusable", true);
	return dp;
}

const DependencyProperty UIElement::WidthProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, float>("Width", NAN);
	return dp;
}

const DependencyProperty UIElement::HeightProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, float>("Height", NAN);
	return dp;
}

const DependencyProperty UIElement::MinWidthProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, float>("MinWidth", 0.0f);
	return dp;
}

const DependencyProperty UIElement::MinHeightProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, float>("MinHeight", 0.0f);
	return dp;
}

const DependencyProperty UIElement::MaxWidthProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, float>("MaxWidth", std::numeric_limits<float>::max());
	return dp;
}

const DependencyProperty UIElement::MaxHeightProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, float>("MaxHeight", std::numeric_limits<float>::max());
	return dp;
}

const DependencyProperty UIElement::DesiredSizeProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, Size>("DesiredSize", Size(0.0f, 0.0f));
	return dp;
}

const DependencyProperty UIElement::ActualSizeProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, Size>("ActualSize", Size(0.0f, 0.0f));
	return dp;
}

const DependencyProperty UIElement::RenderSizeProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, Size>("RenderSize", Size(0.0f, 0.0f));
	return dp;
}

const DependencyProperty UIElement::OffsetProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, Point>("Offset", Point(0.0f, 0.0f));
	return dp;
}

const DependencyProperty UIElement::MarginProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, Thickness>("Margin", Thickness(0.0f));
	return dp;
}

const DependencyProperty UIElement::HorizontalAlignmentProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, HorizontalAlignmentE>("HorizontalAlignment", HorizontalAlignmentE::Stretch);
	return dp;
}

const DependencyProperty UIElement::VerticalAlignmentProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, VerticalAlignmentE>("VerticalAlignment", VerticalAlignmentE::Stretch);
	return dp;
}

const DependencyProperty UIElement::FlowDirectionProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, FlowDirectionE>("FlowDirection", FlowDirectionE::LeftToRight);
	return dp;
}

const DependencyProperty UIElement::RendererProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, shared_ptr<RenderObject>>("Renderer", std::make_shared<RenderObject>());
	return dp;
}

const DependencyProperty UIElement::StyleProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, shared_ptr<Style>>("Style", std::make_shared<Style>());
	return dp;
}

const DependencyProperty UIElement::StateMachineProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<UIElement, shared_ptr<VisualStateMachine>>("StateMachine", std::make_shared<VisualStateMachine>());
	return dp;
}

uint32_t UIElement::childCount() const
{
	return m_children.size();
}

void UIElement::addChild(std::shared_ptr<UIElement> child)
{
	insertChild(childCount(), child);
}

void UIElement::insertChild(uint32_t index, std::shared_ptr<UIElement> child)
{
	if (index > childCount())
		nbThrowException(std::out_of_range, "index");

	m_children.insert(m_children.begin() + index, child);
	try {
		child->m_parent = shared_from_this();
	}catch(...){
		nbThrowException(std::runtime_error, "parent must be a std::shared object.");
	}
}

void UIElement::removeChild(std::shared_ptr<UIElement> child)
{
	auto iter = std::find(m_children.begin(), m_children.end(), child);
	if (iter != m_children.end())
	{
		m_children.erase(iter);
		return;
	}
}

void UIElement::removeChild(uint32_t index, uint32_t count)
{
	if(index >= childCount())
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d]", index, childCount());
	auto end = index + count < childCount() ? m_children.begin() + index + count : m_children.end();
	m_children.erase(m_children.begin() + index, end);
}

void UIElement::clearChild()
{
	m_children.clear();
}

std::shared_ptr<UIElement> UIElement::childAt(uint32_t index)
{
	if (index >= childCount())
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %d]", index, childCount());
	return m_children[index];
}

bool UIElement::containsChild(std::shared_ptr<UIElement> element) const
{
	return std::find(m_children.begin(), m_children.end(), element) != m_children.end();
}

std::shared_ptr<UIElement> UIElement::getRoot()
{
	try {
		std::shared_ptr<UIElement> ret = shared_from_this();
		while (ret->m_parent)
		{
			ret = ret->m_parent;
		}
		return ret;
	}
	catch (...) {
		return nullptr;
	}
}

Point UIElement::worldOffset()
{
	try {
		std::shared_ptr<UIElement> p = shared_from_this();
		Point ret;
		do {
			ret += p->Offset();
		} while ((p->m_parent) && (p = p->m_parent));
		return ret;
	}
	catch (...) {
		return Point::zero();
	}
}

void UIElement::updateLayout()
{
	auto root = getRoot();
	if (!root)	return;

	root->measure({ root->Width(), root->Height() });
	root->arrage(Rect(0, 0, root->DesiredSize()));
	root->onRender(gui::Window::drawContext);
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
	constrainedSize.width() = nb::clamp<float>(MinWidth(), MaxWidth(), std::isnan(Width()) ? constrainedSize.width() : Width());
	constrainedSize.height() = nb::clamp<float>(MinHeight(), MaxHeight(), std::isnan(Height()) ? constrainedSize.height() : Height());

	//measureOverride返回控件期望大小desiredSizeTemp，需要调整到保证在(Min, Max)区间
	//如果手动设置了Width，调整Width到(MinWidth, MaxWidth, Width)
	//否则，调整Width到(MinWidth, MaxWidth, constrainedSize.width())
	//同样的规则应用于Height
	auto desiredSizeTemp = measureOverride(constrainedSize);
	desiredSizeTemp.width() = nb::clamp<float>(MinWidth(), MaxWidth(), std::isnan(Width()) ? desiredSizeTemp.width(): Width());
	desiredSizeTemp.height() = nb::clamp<float>(MinHeight(), MaxHeight(), std::isnan(Height()) ? desiredSizeTemp.height() : Height());

	//由于child不关注和计算magin，因此需重新+margin
	desiredSizeTemp += Size(Margin().left() + Margin().right(), Margin().top() + Margin().bottom());
	//保证在（0, availabelSize)区间
	desiredSizeTemp.width() = nb::clamp<float>(0.0, availabelSize.width(), desiredSizeTemp.width());
	desiredSizeTemp.height() = nb::clamp<float>(0.0, availabelSize.height(), desiredSizeTemp.height());
	set(DesiredSizeProperty(), desiredSizeTemp);
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
	//arrangeSize.reset(std::max(DesiredSize().width(), arrangeSize.width()), std::max(DesiredSize().height(), arrangeSize.height()));
	//如果Aligment不是Stretch，直接将arrangeSize设置为DesiredSize，以保证传入arrangeOverride的arrangeSize没有Stretch
	if (HorizontalAlignment != HorizontalAlignmentE::Stretch)	arrangeSize.setWidth(DesiredSize().width());
	if (VerticalAlignment != VerticalAlignmentE::Stretch)		arrangeSize.setHeight(DesiredSize().height());

	//如果手动设置了Width，调整Width到bound(MinWidth, MaxWidth, Width)
	//否则，调整Width到(MinWidth, MaxWidth, arrangeSize.width())
	//同样的规则应用于Height
	arrangeSize.width() = nb::clamp<float>(MinWidth(), MaxWidth(), std::isnan(Width()) ? arrangeSize.width() : Width());
	arrangeSize.height() = nb::clamp<float>(MinHeight(), MaxHeight(), std::isnan(Height()) ? arrangeSize.height() : Height());

	//arrangeOverride后的RenderSize是不需要调整的非裁剪区域，而不是最终的可见区域
	auto innerInkSize = arrangeOverride(arrangeSize);
	RenderSize = innerInkSize;
	auto ss = RenderSize();
	//裁剪，保证innerInkSize在Max之内
	if (std::isnan(Width()))
		if (innerInkSize.width() > MaxWidth())	innerInkSize.width() = MaxWidth();
	if (std::isnan(Height()))
		if (innerInkSize.height() > MaxHeight())	innerInkSize.height() = MaxHeight();
	Size clipInkSize(std::min(innerInkSize.width(), Width()), std::min(innerInkSize.height(), Height()));

	float offsetX = 0.0f, offsetY = 0.0f;
	switch (HorizontalAlignment())
	{
	case HorizontalAlignmentE::Left:	offsetX = finalRect.x() + Margin().left();														break;
	case HorizontalAlignmentE::Center:	offsetX = finalRect.x() + Margin().left() + (clientSize.width() - RenderSize().width()) / 2;	break;
	case HorizontalAlignmentE::Right:	offsetX = finalRect.width() - Margin().right() - RenderSize().width();							break;
	default:							offsetX = RenderSize().width() >= clientSize.width() ? finalRect.left() + Margin().left() : finalRect.x() + Margin().left() + (clientSize.width() - RenderSize().width()) / 2;	break;
	}
	switch (VerticalAlignment())
	{
	case VerticalAlignmentE::Top:		offsetY = finalRect.y() + Margin().top();														break;
	case VerticalAlignmentE::Center:	offsetY = finalRect.y() + Margin().top() + (clientSize.height() - RenderSize().height()) / 2;	break;
	case VerticalAlignmentE::Bottom:	offsetY = finalRect.y() + (finalRect.height() - Margin().bottom() - RenderSize().height());		break;
	default:							offsetY = RenderSize().height() >= clientSize.height() ? finalRect.top() + Margin().top() : finalRect.y() + Margin().top() + (clientSize.height() - RenderSize().height()) / 2;	break;
	}
	set(OffsetProperty(), Point(offsetX, offsetY));
	set(ActualSizeProperty(), RenderSize());
	//裁剪
//	if (m_actualSize.width() > finalRect.width())	m_actualSize.width() = finalRect.width();
//	if (m_actualSize.height() > finalRect.height())	m_actualSize.height() = finalRect.height();
}

Size UIElement::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size UIElement::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}

void UIElement::onMouseEnter()
{
}

void UIElement::onMouseLeave()
{
}

void UIElement::onMouseDown()
{
}

void UIElement::onMouseUp()
{
}

void UIElement::onMouseLeftButtonDown()
{
}

void UIElement::onMouseLeftButtonUp()
{
}

void UIElement::onMouseRightButtonDown()
{
}

void UIElement::onMouseRightButtonUp()
{
}

void UIElement::onMouseMove()
{
}

void UIElement::onMouseWheel(int delta)
{
}

void UIElement::onPropertyChanged(const PropertyChangedArg & args)
{
	if (args.dp == UIElement::WidthProperty() || args.dp == UIElement::HeightProperty())
	{
		updateLayout();
	}
}

void UIElement::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
}
