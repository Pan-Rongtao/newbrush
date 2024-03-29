﻿#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/VisualTreeHelper.h"
#include "newbrush/core/media/Transform.h"
#include "newbrush/core/base/Thickness.h"

using namespace nb;

UIElement::UIElement()
	: m_parent(nullptr)
	, m_lastMesaaeAvailabelSize(-1, -1)
	, m_measureInProgress(false)
{
}

DependencyPropertyPtr UIElement::NameProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, std::string>("Name", "", nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::VisibilityProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, VisibilityE>("Visibility", VisibilityE::Visible, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::OpacityProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("Opacity", 1.0f, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::FocusableProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, bool>("Focusable", true, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::IsFocusedProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, bool>("IsFocused", false);
	return dp;
}

DependencyPropertyPtr UIElement::WidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("Width", NAN, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::HeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("Height", NAN, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::MinWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("MinWidth", 0.0f, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::MinHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("MinHeight", 0.0f, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::MaxWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("MaxWidth", std::numeric_limits<float>::max(), nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::MaxHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, float>("MaxHeight", std::numeric_limits<float>::max(), nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::ActualSizeProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, Size>("ActualSize", Size());
	return dp;
}

DependencyPropertyPtr UIElement::MarginProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, Thickness>("Margin", Thickness(), nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::HorizontalAlignmentProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, HorizontalAlignmentE>("HorizontalAlignment", HorizontalAlignmentE::Stretch, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::VerticalAlignmentProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, VerticalAlignmentE>("VerticalAlignment", VerticalAlignmentE::Stretch, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::FlowDirectionProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, FlowDirectionE>("FlowDirection", FlowDirectionE::LeftToRight, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr UIElement::StyleProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, StylePtr>("Style", nullptr, [](DependencyObject *object, const DependencyPropertyChangedEventArgs &args) {
		auto e = dynamic_cast<UIElement *>(object);

		auto oldStyle = args.oldValue().get_value<StylePtr>();
		auto newStyle = args.newValue().get_value<StylePtr>();
		//由于style类型每次set都会触发changed，因此设置统一style也会进入此回调函数，应判断newStyle == oldStyle
		if (newStyle == oldStyle)
			return;
		
		if (newStyle)
		{
			/*
			newStyle->StyleDataTrigger += [e](const Style::StyleDataTriggerArgs &args) {
				args.dataTrigger->processSetters(e, args.dataTrigger->setters);
			};
			newStyle->StyleMultiDataTrigger += [e](const Style::StyleMultiDataTriggerArgs &args) {
				args.multiDataTrigger->processSetters(e, args.multiDataTrigger->setters);
			};*/
			newStyle->attach(e);
		}
	});
	return dp;
}

DependencyPropertyPtr UIElement::StateMachineProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, VisualStateMachinePtr>("StateMachine", std::make_shared<VisualStateMachine>());
	return dp;
}

DependencyPropertyPtr UIElement::IsMouseOverProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, bool>("IsMouseOver", false);
	return dp;
}

DependencyPropertyPtr UIElement::RenderTransformProperty()
{
	static auto dp = DependencyProperty::registerDependency<UIElement, TransformPtr>("RenderTransform", std::make_shared<Transform>(), nullptr, nullptr, nullptr);
	return dp;
}

uint32_t UIElement::childrenCount() const
{
	return 0;
}

UIElement *UIElement::getChild(uint32_t index)
{
	nbThrowException(std::out_of_range, "index[%d] is out of range[0, 0)", index);
}

void UIElement::setParent(UIElement *element)
{
	m_parent = element;
}

UIElement * UIElement::getParent()
{
	return m_parent;
}

UIElement *UIElement::getRoot()
{
	auto ret = this;
	while (ret->m_parent)
	{
		ret = ret->m_parent;
	}
	return ret;
}

Point UIElement::worldOffset() const
{
	Point ret;
	auto p = this;
	do {
		auto offset = p->m_offsetToParent;
		ret += offset;
	} while ((p->m_parent) && (p = p->m_parent));
	return ret;
}

void UIElement::updateLayout()
{
	auto root = getRoot();
	if (!root)	return;

	auto w = nb::as<Window>(root);
	if (!w)
	{
		return;
	}

	auto rootWidth = root->getValue<float>(WidthProperty());
	auto rootHeight = root->getValue<float>(HeightProperty());
	auto const &rootDesiredSize = root->desiredSize();

	root->measure({ rootWidth, rootHeight });
	root->arrage(Rect(0, 0, rootDesiredSize));
	root->onRender(w->m_drawContext);
}

//直接忽略返回的情况
//1、如果不可见
//2、与上次measure参数一致
//3、已经在处理measure中，防止measure函数内有某种操作导致重新进入measure函数（比如设置某些属性）
//4、child不脏（还未了解）
//该函数是为了确认DesiredSize
void UIElement::measure(const Size & availabelSize)
{
	auto visibility = getValue<VisibilityE>(VisibilityProperty());
	if (m_measureInProgress || visibility != VisibilityE::Visible)
	{
		return;
	}

	m_lastMesaaeAvailabelSize = availabelSize;

	auto const &margin = getValue<Thickness>(MarginProperty());
	auto const &width = getValue<float>(WidthProperty());
	auto const &height = getValue<float>(HeightProperty());
	auto const &minWidth = getValue<float>(MinWidthProperty());
	auto const &minHeight = getValue<float>(MinHeightProperty());
	auto const &maxWidth = getValue<float>(MaxWidthProperty());
	auto const &maxHeight = getValue<float>(MaxHeightProperty());
	//减去magin计算出本来的constrainedSize
	auto constrainedSize = Size(availabelSize.width() - margin.left - margin.right, availabelSize.height() - margin.top - margin.bottom);
	//如果手动设置了Width，调整Width到bound(MinWidth, MaxWidth, Width)
	//否则，调整Width到(MinWidth, MaxWidth, constrainedSize.width())
	//同样的规则应用于Height
	constrainedSize.width() = nb::clamp<float>(minWidth, maxWidth, std::isnan(width) ? constrainedSize.width() : width);
	constrainedSize.height() = nb::clamp<float>(minHeight, maxHeight, std::isnan(height) ? constrainedSize.height() : height);

	//measureOverride返回控件期望大小desiredSizeTemp，需要调整到保证在(Min, Max)区间
	//如果手动设置了Width，调整Width到(MinWidth, MaxWidth, Width)
	//否则，调整Width到(MinWidth, MaxWidth, constrainedSize.width())
	//同样的规则应用于Height
	auto desiredSizeTemp = measureOverride(constrainedSize);
	desiredSizeTemp.width() = nb::clamp<float>(minWidth, maxWidth, std::isnan(width) ? desiredSizeTemp.width(): width);
	desiredSizeTemp.height() = nb::clamp<float>(minHeight, maxHeight, std::isnan(height) ? desiredSizeTemp.height() : height);

	//由于child不关注和计算magin，因此需重新+margin
	desiredSizeTemp += Size(margin.left + margin.right, margin.top + margin.bottom);
	//保证在（0, availabelSize)区间
	desiredSizeTemp.width() = nb::clamp<float>(0.0, availabelSize.width(), desiredSizeTemp.width());
	desiredSizeTemp.height() = nb::clamp<float>(0.0, availabelSize.height(), desiredSizeTemp.height());
	m_desiredSize = desiredSizeTemp;

	m_measureInProgress = false;
}

void UIElement::arrage(const Rect & finalRect)
{
	//如果不可见或两次arrage参数一致，忽略
	auto visibility = getValue<VisibilityE>(VisibilityProperty());
	if (visibility != VisibilityE::Visible)
		return;

	auto const &margin = getValue<Thickness>(MarginProperty());
	auto const &width = getValue<float>(WidthProperty());
	auto const &height = getValue<float>(HeightProperty());
	auto const &minWidth = getValue<float>(MinWidthProperty());
	auto const &minHeight = getValue<float>(MinHeightProperty());
	auto const &maxWidth = getValue<float>(MaxWidthProperty());
	auto const &maxHeight = getValue<float>(MaxHeightProperty());
	//减去magin计算出本来的arrangeSize以及clientSize
	auto arrangeSize = Size(finalRect.width() - margin.left - margin.right, finalRect.height() - margin.top - margin.bottom);
	auto clientSize = arrangeSize;
	//调整arrange大于DesiredSize
	//arrangeSize.reset(std::max(DesiredSize().width(), arrangeSize.width()), std::max(DesiredSize().height(), arrangeSize.height()));
	//如果Aligment不是Stretch，直接将arrangeSize设置为DesiredSize，以保证传入arrangeOverride的arrangeSize没有Stretch
	auto const &horizontalAlignment = getValue<HorizontalAlignmentE>(HorizontalAlignmentProperty());
	auto const &verticalAlignment = getValue<VerticalAlignmentE>(VerticalAlignmentProperty());
	if (horizontalAlignment != HorizontalAlignmentE::Stretch)	arrangeSize.setWidth(m_desiredSize.width());
	if (verticalAlignment != VerticalAlignmentE::Stretch)		arrangeSize.setHeight(m_desiredSize.height());

	//如果手动设置了Width，调整Width到bound(MinWidth, MaxWidth, Width)
	//否则，调整Width到(MinWidth, MaxWidth, arrangeSize.width())
	//同样的规则应用于Height
	arrangeSize.width() = nb::clamp<float>(minWidth, maxWidth, std::isnan(width) ? arrangeSize.width() : width);
	arrangeSize.height() = nb::clamp<float>(minHeight, maxHeight, std::isnan(height) ? arrangeSize.height() : height);

	//arrangeOverride后的RenderSize是不需要调整的非裁剪区域，而不是最终的可见区域
	auto innerInkSize = arrangeOverride(arrangeSize);
	m_renderSize = innerInkSize;
	//裁剪，保证innerInkSize在Max之内
	if (std::isnan(width))
		if (innerInkSize.width() > maxWidth)	innerInkSize.width() = maxWidth;
	if (std::isnan(height))
		if (innerInkSize.height() > maxHeight)	innerInkSize.height() = maxHeight;
	Size clipInkSize(std::min(innerInkSize.width(), width), std::min(innerInkSize.height(), height));

	float offsetX = 0.0f, offsetY = 0.0f;
	switch (horizontalAlignment)
	{
	case HorizontalAlignmentE::Left:	offsetX = finalRect.x() + margin.left;													break;
	case HorizontalAlignmentE::Center:	offsetX = finalRect.x() + margin.left + (clientSize.width() - m_renderSize.width()) / 2;	break;
	case HorizontalAlignmentE::Right:	offsetX = finalRect.width() - margin.right - m_renderSize.width();							break;
	default:							offsetX = m_renderSize.width() >= clientSize.width() ? finalRect.left() + margin.left : finalRect.x() + margin.left + (clientSize.width() - m_renderSize.width()) / 2;	break;
	}
	switch (verticalAlignment)
	{
	case VerticalAlignmentE::Top:		offsetY = finalRect.y() + margin.top;														break;
	case VerticalAlignmentE::Center:	offsetY = finalRect.y() + margin.top + (clientSize.height() - m_renderSize.height()) / 2;	break;
	case VerticalAlignmentE::Bottom:	offsetY = finalRect.y() + (finalRect.height() - margin.bottom - m_renderSize.height());		break;
	default:							offsetY = m_renderSize.height() >= clientSize.height() ? finalRect.top() + margin.top : finalRect.y() + margin.top + (clientSize.height() - m_renderSize.height()) / 2;	break;
	}
	m_offsetToParent.reset(offsetX, offsetY);
	setValue(ActualSizeProperty(), m_renderSize);
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

void UIElement::addLogicalChild(UIElementPtr child)
{
	child->changedLogicParent(this);
}

void UIElement::removeLogicalChild(UIElementPtr child)
{
	child->changedLogicParent(nullptr);
}

void UIElement::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	if (args.property() == UIElement::WidthProperty() || args.property() == UIElement::HeightProperty() || args.property() == MarginProperty())
	{
		updateLayout();
	}
	auto style = getValue<StylePtr>(StyleProperty());
	if (style)
	{
		style->handlePropertyChanged(this, args.property(), args.newValue());
	}
}

void UIElement::onStyleChanged(StylePtr oldStyle, StylePtr newStyle)
{
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

void UIElement::onMouseMove(const MouseEventArgs & args)
{
	MouseMove.invoke(args);
	auto e = std::make_shared<MouseEventArgs>(args);
	e->Event = MouseMoveEvent();
	raiseEvent(e);
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

void UIElement::changedLogicParent(UIElement * parent)
{
	m_parent = parent;
}

void UIElement::onMouseMoveThunk(const MouseEventArgs &e, const Point &pt)
{
	auto hit = VisualTreeHelper::hitTest(this, pt);
	auto isMouseOver = getValue<bool>(IsMouseOverProperty());
	if (hit)
	{
		if (!isMouseOver)
		{
			onMouseEnter(e);
			setValue(IsMouseOverProperty(), true);
		}
		onMouseMove(e);
	}
	else
	{
		if (isMouseOver)
		{
			onMouseLeave(e);
			setValue(IsMouseOverProperty(), false);
		}
	}
}

void UIElement::onMouseButtonThunk(const MouseButtonEventArgs & e, const Point & pt)
{
	auto hit = VisualTreeHelper::hitTest(this, pt);

	if (e.ButtonState == MouseButtonStateE::Pressed)
	{
		if (!hit)	return;
		if (e.ChangedButton == MouseButtonE::Left)
		{
			onMouseLeftButtonDown(e);
			m_flags.set(IsLeftButtonDownCache);
		}
		else
		{
			onMouseRightButtonDown(e);
			m_flags.set(IsRightButtonDownCache);
		}
		onMouseDown(e);
	}
	else
	{
		if (hit)
		{
			if (e.ChangedButton == MouseButtonE::Left)
			{
				onMouseLeftButtonUp(e);
				m_flags.reset(IsLeftButtonDownCache);
			}
			else
			{
				onMouseRightButtonUp(e);
				m_flags.reset(IsRightButtonDownCache);
			}
			onMouseUp(e);
		}
		else
		{
			if (e.ChangedButton == MouseButtonE::Left && m_flags.test(IsLeftButtonDownCache))
			{
				onMouseLeftButtonUp(e);
				m_flags.reset(IsLeftButtonDownCache);
			}
			else if (e.ChangedButton == MouseButtonE::Right && m_flags.test(IsRightButtonDownCache))
			{
				onMouseRightButtonUp(e);
				m_flags.reset(IsRightButtonDownCache);
			}
			onMouseUp(e);
		}
	}
}

void UIElement::onRender(DrawingContextPtr dc)
{
}

void UIElement::addHandler(const RoutedEvent & event, const RoutedEventHandler & handler)
{
	m_eventHandlers[event.hash()].push_back(handler);
}

void UIElement::removeHandler(const RoutedEvent & event, const RoutedEventHandler & handler)
{
	auto iter = m_eventHandlers.find(event.hash());
	if (iter != m_eventHandlers.end())
	{
		auto &handlers = iter->second;
		auto iterHandler = std::find(handlers.begin(), handlers.end(), handler);
		if (iterHandler != handlers.end())
			handlers.erase(iterHandler);
	}
}

void UIElement::raiseEvent(RoutedEventArgsPtr args)
{
	auto fireElementEvents = [&args](UIElement *element) {
		auto const &eventHandles = element->m_eventHandlers;
		auto iter = eventHandles.find(args->Event.hash());
		if (iter != eventHandles.end())
		{
			for (auto const &h : iter->second)
			{
				h.invoke(args);
			}
		}
	};

	if (args->Event.routingStrategy() == RoutingStrategyE::bubble)
	{
		auto pElement = this;
		do {
			fireElementEvents(pElement);
		} while ((pElement->m_parent) && (pElement = pElement->m_parent));
	}
	else if (args->Event.routingStrategy() == RoutingStrategyE::tunnel)
	{

	}
	else
	{
		fireElementEvents(this);
	}
}

bool UIElement::hitTestCore(const Point &pt) const
{
	auto offset = worldOffset();
	auto const &actualSize = getValue<Size>(ActualSizeProperty());
	Rect rc(offset.x(), offset.y(), actualSize);
	return rc.contains(pt);
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
	static auto e = RoutedEventManager::registerRoutedEvent<UIElement, MouseEventArgs>("MouseEnter", RoutingStrategyE::direct);
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

const Size &UIElement::desiredSize() const
{
	return m_desiredSize;
}

UIElementPtr UIElement::clone() const
{
	return std::make_shared<UIElement>(*this);
}
