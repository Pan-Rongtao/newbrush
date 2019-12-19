#include "gui/UIElement.h"
#include "gui/Window.h"

using namespace nb;
using namespace nb::gui;

UIElement::UIElement()
	: Visibility([&](VisibilityE v) {set(VisibilityProperty(), v); }, [&]()->VisibilityE& {return get<VisibilityE>(VisibilityProperty()); })
	, Opacity([&](float v) {set(OpacityProperty(), v); }, [&]()->float& {return get<float>(OpacityProperty()); })
	, Focusable([&](bool v) {set(FocusableProperty(), v); }, [&]()->bool& {return get<bool>(FocusableProperty()); })
	, IsFocused([&](bool v) {set(IsFocusedProperty(), v); }, [&]()->bool& {return get<bool>(IsFocusedProperty()); })
	, Width([&](float v) {set(WidthProperty(), v); }, [&]()->float& {return get<float>(WidthProperty()); })
	, Height([&](float v) {set(HeightProperty(), v); }, [&]()->float& {return get<float>(HeightProperty()); })
	, MinWidth([&](float v) {set(MinWidthProperty(), v); }, [&]()->float& {return get<float>(MinWidthProperty()); })
	, MinHeight([&](float v) {set(MinHeightProperty(), v); }, [&]()->float& {return get<float>(MinHeightProperty()); })
	, MaxWidth([&](float v) {set(MaxWidthProperty(), v); }, [&]()->float& {return get<float>(MaxWidthProperty()); })
	, MaxHeight([&](float v) {set(MaxHeightProperty(), v); }, [&]()->float& {return get<float>(MaxHeightProperty()); })
	, DesiredSize([&]() {return get<Size>(DesiredSizeProperty()); })
	, ActualSize([&]() {return get<Size>(ActualSizeProperty()); })
	, RenderSize([&](Size v) {set(RenderSizeProperty(), v); }, [&]()->Size& {return get<Size>(RenderSizeProperty()); })
	, Offset([&](Point v) {set(OffsetProperty(), v); }, [&]()->Point& {return get<Point>(OffsetProperty()); })
	, Margin([&](Thickness v) {set(MarginProperty(), v); }, [&]()->Thickness& {return get<Thickness>(MarginProperty()); })
	, HorizontalAlignment([&](HorizontalAlignmentE v) {set(HorizontalAlignmentProperty(), v); }, [&]()->HorizontalAlignmentE& {return get<HorizontalAlignmentE>(HorizontalAlignmentProperty()); })
	, VerticalAlignment([&](VerticalAlignmentE v) {set(VerticalAlignmentProperty(), v); }, [&]()->VerticalAlignmentE& {return get<VerticalAlignmentE>(VerticalAlignmentProperty()); })
	, FlowDirection([&](FlowDirectionE v) {set(FlowDirectionProperty(), v); }, [&]()->FlowDirectionE& {return get<FlowDirectionE>(FlowDirectionProperty()); })
	, Renderer([&]() {return get<shared_ptr<RenderObject>>(RendererProperty()); })
	, style([&](shared_ptr<Style> v) {set(StyleProperty(), v); }, [&]()->shared_ptr<Style>& {return get<shared_ptr<Style>>(StyleProperty()); })
	, StateMachine([&](shared_ptr<VisualStateMachine> v) {set(StateMachineProperty(), v); }, [&]()->shared_ptr<VisualStateMachine>& {return get<shared_ptr<VisualStateMachine>>(StateMachineProperty()); })
	, m_parent(nullptr)
{
	set(RendererProperty(), std::make_shared<RenderObject>());
	PropertyChanged += std::bind(&UIElement::onPropertyChanged, this, std::placeholders::_1);
}

DependencyProperty UIElement::VisibilityProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, VisibilityE>("Visibility", VisibilityE::Visible);
	return dp;
}

DependencyProperty UIElement::OpacityProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("Opacity", 1.0f);
	return dp;
}

DependencyProperty UIElement::FocusableProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, bool>("Focusable", true);
	return dp;
}

DependencyProperty UIElement::IsFocusedProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, bool>("IsFocused", false);
	return dp;
}

DependencyProperty UIElement::WidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("Width", NAN);
	return dp;
}

DependencyProperty UIElement::HeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("Height", NAN);
	return dp;
}

DependencyProperty UIElement::MinWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("MinWidth", 0.0f);
	return dp;
}

DependencyProperty UIElement::MinHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("MinHeight", 0.0f);
	return dp;
}

DependencyProperty UIElement::MaxWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("MaxWidth", std::numeric_limits<float>::max());
	return dp;
}

DependencyProperty UIElement::MaxHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("MaxHeight", std::numeric_limits<float>::max());
	return dp;
}

DependencyProperty UIElement::DesiredSizeProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, Size>("DesiredSize", Size());
	return dp;
}

DependencyProperty UIElement::ActualSizeProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, Size>("ActualSize", Size());
	return dp;
}

DependencyProperty UIElement::RenderSizeProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, Size>("RenderSize", Size());
	return dp;
}

DependencyProperty UIElement::OffsetProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, Point>("Offset", Point());
	return dp;
}

DependencyProperty UIElement::MarginProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, Thickness>("Margin", Thickness());
	return dp;
}

DependencyProperty UIElement::HorizontalAlignmentProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, HorizontalAlignmentE>("HorizontalAlignment", HorizontalAlignmentE::Stretch);
	return dp;
}

DependencyProperty UIElement::VerticalAlignmentProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, VerticalAlignmentE>("VerticalAlignment", VerticalAlignmentE::Stretch);
	return dp;
}

DependencyProperty UIElement::FlowDirectionProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, FlowDirectionE>("FlowDirection", FlowDirectionE::LeftToRight);
	return dp;
}

DependencyProperty UIElement::RendererProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, shared_ptr<RenderObject>>("Renderer", nullptr);
	return dp;
}

DependencyProperty UIElement::StyleProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, shared_ptr<Style>>("Style", std::make_shared<Style>());
	return dp;
}

DependencyProperty UIElement::StateMachineProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, shared_ptr<VisualStateMachine>>("StateMachine", std::make_shared<VisualStateMachine>());
	return dp;
}

void UIElement::setParent(UIElement *element)
{
	m_parent = element;
}

UIElement *UIElement::getRoot()
{
	try {
		auto ret = this;
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
		auto p = this;
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

void UIElement::onDragEnter(const DragEventArgs & args)
{
	DragEnter.invoke(args);
}

void UIElement::onDragLeave(const DragEventArgs & args)
{
	DragLeave.invoke(args);
}

void UIElement::onDragOver(const DragEventArgs & args)
{
	DragOver.invoke(args);
}

void UIElement::onDrop(const DragEventArgs & args)
{
	Drop.invoke(args);
}

void UIElement::onGotFocus(const RoutedEventArgs & args)
{
	GotFocus.invoke(args);
}

void UIElement::onGotKeyboardFocus(const KeyboardFocusChangedEventArgs & args)
{
	GotKeyboardFocus.invoke(args);
}

void UIElement::onGotMouseCapture(const MouseEventArgs & args)
{
	GotMouseCapture.invoke(args);
}

void UIElement::onGotTouchCapture(const TouchEventArgs & args)
{
	GotTouchCapture.invoke(args);
}

void UIElement::onKeyDown(const KeyEventArgs & args)
{
	KeyDown.invoke(args);
}

void UIElement::onKeyUp(const KeyEventArgs & args)
{
	KeyUp.invoke(args);
}

void UIElement::onLostFocus(const RoutedEventArgs & args)
{
	LostFocus.invoke(args);
}

void UIElement::onLostKeyboardFocus(const KeyboardFocusChangedEventArgs & args)
{
	LostKeyboardFocus.invoke(args);
}

void UIElement::onLostMouseCapture(const MouseEventArgs & args)
{
	LostMouseCapture.invoke(args);
}

void UIElement::onLostTouchCapture(const TouchEventArgs & args)
{
	LostTouchCapture.invoke(args);
}

void UIElement::onMouseEnter(const MouseEventArgs & args)
{
	MouseEnter.invoke(args);
}

void UIElement::onMouseLeave(const MouseEventArgs & args)
{
	MouseLeave.invoke(args);
}

void UIElement::onMouseDown(const MouseButtonEventArgs & args)
{
	MouseDown.invoke(args);
}

void UIElement::onMouseUp(const MouseButtonEventArgs & args)
{
	MouseUp.invoke(args);
}

void UIElement::onMouseLeftButtonDown(const MouseButtonEventArgs & args)
{
	MouseLeftButtonDown.invoke(args);
}

void UIElement::onMouseLeftButtonUp(const MouseButtonEventArgs & args)
{
	MouseLeftButtonUp.invoke(args);
}

void UIElement::onMouseRightButtonDown(const MouseButtonEventArgs & args)
{
	MouseRightButtonDown.invoke(args);
}

void UIElement::onMouseRightButtonUp(const MouseButtonEventArgs & args)
{
	MouseRightButtonUp.invoke(args);
}

void UIElement::onMouseMove(const MouseButtonEventArgs & args)
{
	MouseMove.invoke(args);
}

void UIElement::onMouseWheel(const MouseWheelEventArgs & args)
{
	MouseWheel.invoke(args);
}

void UIElement::onTouchDown(const TouchEventArgs & args)
{
	TouchDown.invoke(args);
}

void UIElement::onTouchEnter(const TouchEventArgs & args)
{
	TouchEnter.invoke(args);
}

void UIElement::onTouchLeave(const TouchEventArgs & args)
{
	TouchLeave.invoke(args);
}

void UIElement::onTouchMove(const TouchEventArgs & args)
{
	TouchMove.invoke(args);
}

void UIElement::onTouchUp(const TouchEventArgs & args)
{
	TouchUp.invoke(args);
}

void UIElement::onPreviewDragEnter(const DragEventArgs & args)
{
	PreviewDragEnter.invoke(args);
}

void UIElement::onPreviewDragLeave(const DragEventArgs & args)
{
	PreviewDragLeave.invoke(args);
}

void UIElement::onPreviewDragOver(const DragEventArgs & args)
{
	PreviewDragOver.invoke(args);
}

void UIElement::onPreviewDrop(const DragEventArgs & args)
{
	PreviewDrop.invoke(args);
}

void UIElement::onPreviewGotKeyboardFocus(const KeyboardFocusChangedEventArgs & args)
{
	PreviewGotKeyboardFocus.invoke(args);
}

void UIElement::onPreviewKeyDown(const KeyEventArgs & args)
{
	PreviewKeyDown.invoke(args);
}

void UIElement::onPreviewKeyUp(const KeyEventArgs & args)
{
	PreviewKeyUp.invoke(args);
}

void UIElement::onPreviewLostKeyboardFocus(const KeyboardFocusChangedEventArgs & args)
{
	PreviewLostKeyboardFocus.invoke(args);
}

void UIElement::onPreviewMouseDown(const MouseButtonEventArgs & args)
{
	PreviewMouseDown.invoke(args);
}

void UIElement::onPreviewMouseUp(const MouseButtonEventArgs & args)
{
	PreviewMouseUp.invoke(args);
}

void UIElement::onPreviewMouseLeftButtonDown(const MouseButtonEventArgs & args)
{
	PreviewMouseLeftButtonDown.invoke(args);
}

void UIElement::onPreviewMouseLeftButtonUp(const MouseButtonEventArgs & args)
{
	PreviewMouseLeftButtonUp.invoke(args);
}

void UIElement::onPreviewMouseRightButtonDown(const MouseButtonEventArgs & args)
{
	PreviewMouseRightButtonDown.invoke(args);
}

void UIElement::onPreviewMouseRightButtonUp(const MouseButtonEventArgs & args)
{
	PreviewMouseRightButtonUp.invoke(args);
}

void UIElement::onPreviewMouseMove(const MouseButtonEventArgs & args)
{
	PreviewMouseMove.invoke(args);
}

void UIElement::onPreviewMouseWheel(const MouseWheelEventArgs & args)
{
	PreviewMouseWheel.invoke(args);
}

void UIElement::onPreviewTouchDown(const TouchEventArgs & args)
{
	PreviewTouchDown.invoke(args);
}

void UIElement::onPreviewTouchEnter(const TouchEventArgs & args)
{
	PreviewTouchEnter.invoke(args);
}

void UIElement::onPreviewTouchLeave(const TouchEventArgs & args)
{
	PreviewTouchLeave.invoke(args);
}

void UIElement::onPreviewTouchMove(const TouchEventArgs & args)
{
	PreviewTouchMove.invoke(args);
}

void UIElement::onPreviewTouchUp(const TouchEventArgs & args)
{
	PreviewTouchUp.invoke(args);
}

void UIElement::onPropertyChanged(const PropertyChangedArgs & args)
{
	if (args.dp == UIElement::WidthProperty() || args.dp == UIElement::HeightProperty())
	{
		updateLayout();
	}
}

void UIElement::onRender(Viewport2D & drawContext)
{
}

RoutedEvent UIElement::LoadedEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, RoutedEventArgs>("Loaded", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::UnloadedEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, RoutedEventArgs>("Unloaded", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::SizeChangedEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, SizeChangedEventArgs>("SizeChanged", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::DragEnterEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, DragEventArgs>("DragEnter", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::DragLeaveEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, DragEventArgs>("DragLeave", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::DragOverEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, DragEventArgs>("DragOver", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::DropEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, DragEventArgs>("Drop", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::GotFocusEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, RoutedEventArgs>("GotFocus", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::GotKeyboardFocusEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, KeyboardFocusChangedEventArgs>("GotKeyboardFocus", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::LostKeyboardFocusEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, KeyboardFocusChangedEventArgs>("LostKeyboardFocus", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::GotMouseCaptureEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseEventArgs>("GotMouseCapture", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::KeyDownEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, KeyEventArgs>("KeyDown", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::KeyUpEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, KeyEventArgs>("KeyUp", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::LostFocusEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, RoutedEventArgs>("LostFocus", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::LostMouseCaptureEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseEventArgs>("LostMouseCapture", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::LostTouchCaptureEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, TouchEventArgs>("LostTouchCapture", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::MouseDownEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseButtonEventArgs>("MouseDown", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::MouseEnterEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseEventArgs>("MouseEnter", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::MouseLeaveEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseEventArgs>("MouseLeave", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::MouseLeftButtonDownEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseButtonEventArgs>("MouseLeftButtonDown", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::MouseLeftButtonUpEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseButtonEventArgs>("MouseLeftButtonUp", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::MouseMoveEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseEventArgs>("MouseLeftButtonUp", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::MouseRightButtonDownEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseButtonEventArgs>("MouseRightButtonDown", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::MouseRightButtonUpEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseButtonEventArgs>("MouseRightButtonUp", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::MouseUpEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseButtonEventArgs>("MouseUp", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::MouseWheelEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseWheelEventArgs>("MouseWheel", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::PreviewDragEnterEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, DragEventArgs>("PreviewDragEnter", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewDragLeaveEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, DragEventArgs>("PreviewDragLeave", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewDragOverEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, DragEventArgs>("PreviewDragOver", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewDropEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, DragEventArgs>("PreviewDrop", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewGotKeyboardFocusEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, KeyboardFocusChangedEventArgs>("PreviewGotKeyboardFocus", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewLostKeyboardFocusEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, KeyboardFocusChangedEventArgs>("PreviewLostKeyboardFocus", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewKeyDownEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, KeyEventArgs>("PreviewKeyDown", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewKeyUpEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, KeyEventArgs>("PreviewKeyUp", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewMouseDownEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseButtonEventArgs>("PreviewMouseDown", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewMouseLeftButtonDownEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseButtonEventArgs>("PreviewMouseLeftButtonDown", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewMouseLeftButtonUpEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseButtonEventArgs>("PreviewMouseLeftButtonUp", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewMouseMoveEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseEventArgs>("PreviewMouseMove", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewMouseRightButtonDownEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseButtonEventArgs>("PreviewMouseRightButtonDown", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewMouseRightButtonUpEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseButtonEventArgs>("PreviewMouseRightButtonUp", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewMouseUpEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseButtonEventArgs>("PreviewMouseUp", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewMouseWheelEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseWheelEventArgs>("PreviewMouseWheel", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewTouchDownEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, TouchEventArgs>("PreviewTouchDown", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewTouchMoveEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, TouchEventArgs>("PreviewTouchMove", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::PreviewTouchUpEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, TouchEventArgs>("PreviewTouchUp", RoutingStrategyE::tunnel);
	return e;
}

RoutedEvent UIElement::TouchDownEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, TouchEventArgs>("TouchDown", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::TouchEnterEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, TouchEventArgs>("TouchEnter", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::TouchLeaveEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, TouchEventArgs>("TouchLeave", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::TouchMoveEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, TouchEventArgs>("TouchMove", RoutingStrategyE::bubble);
	return e;
}

RoutedEvent UIElement::TouchUpEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, TouchEventArgs>("TouchUp", RoutingStrategyE::bubble);
	return e;
}
