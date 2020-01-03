#pragma once
#include "../core/Property.h"
#include "../core/DependencyObject.h"
#include "../core/Size.h"
#include "../core/Rect.h"
#include "../gui/Thickness.h"
#include "../gles/RenderObject.h"
#include "../gui/Style.h"
#include "../gui/VisualStateMachine.h"
#include "../core/RoutedEvent.h"

namespace nb{
	class Viewport2D;
}

namespace nb{
namespace gui{

enum class VisibilityE
{
	Hidden,		//不要显示的元素，但是，保留空间中的元素格式（参与排版策略等）
	Visible,	//显示组件
	Collapsed,	//不要显示元素，并且不希望它的保留空间
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

class NB_API UIElement : public DependencyObject, public std::enable_shared_from_this<UIElement>
{
public:
	UIElement();
	virtual ~UIElement() = default;

	Property_rw<VisibilityE>					Visibility;				//可视
	Property_rw<float>							Opacity;				//不透明度
	Property_rw<bool>							Focusable;				//是否可用焦点
	Property_rw<bool>							IsFocused;				//是否具有焦点
	Property_rw<float>							Width;					//设定宽
	Property_rw<float>							Height;					//设定高
	Property_rw<float>							MinWidth;				//最小宽
	Property_rw<float>							MinHeight;				//最小高
	Property_rw<float>							MaxWidth;				//最大宽
	Property_rw<float>							MaxHeight;				//最大高
	Property_r<Size>							DesiredSize;			//期望尺寸
	Property_r<Size>							ActualSize;				//实际尺寸
	Property_rw<Size>							RenderSize;				//渲染尺寸
	Property_rw<Point>							Offset;					//相对父偏移量
	Property_rw<Thickness>						Margin;					//边缘
	Property_rw<HorizontalAlignmentE>			HorizontalAlignment;	//横向对齐方式
	Property_rw<VerticalAlignmentE>				VerticalAlignment;		//纵向对齐方式
	Property_rw<FlowDirectionE>					FlowDirection;			//
	Property_r<std::shared_ptr<RenderObject>>		Renderer;				//渲染物
	Property_rw<std::shared_ptr<Style>>				style;					//风格
	Property_rw<std::shared_ptr<VisualStateMachine>>	StateMachine;

	static DependencyProperty					VisibilityProperty();	//可视的依赖属性
	static DependencyProperty					OpacityProperty();		//不透明度的依赖属性
	static DependencyProperty					FocusableProperty();	//是否可用焦点的依赖属性
	static DependencyProperty					IsFocusedProperty();	//是否可用焦点的依赖属性
	static DependencyProperty 					WidthProperty();		//设定宽的依赖属性
	static DependencyProperty 					HeightProperty();		//设定高的依赖属性
	static DependencyProperty 					MinWidthProperty();		//最小宽的依赖属性
	static DependencyProperty 					MinHeightProperty();	//最小高的依赖属性
	static DependencyProperty 					MaxWidthProperty();		//最大宽的依赖属性
	static DependencyProperty 					MaxHeightProperty();	//最大高的依赖属性
	static DependencyProperty 					DesiredSizeProperty();	//期望尺寸的依赖属性
	static DependencyProperty 					ActualSizeProperty();	//实际尺寸的依赖属性
	static DependencyProperty 					RenderSizeProperty();	//渲染尺寸的依赖属性
	static DependencyProperty 					OffsetProperty();		//相对父偏移量的依赖属性
	static DependencyProperty 					MarginProperty();		//边缘的依赖属性
	static DependencyProperty 					HorizontalAlignmentProperty();	//横向对齐方式的依赖属性
	static DependencyProperty 					VerticalAlignmentProperty();	//纵向对齐方式的依赖属性
	static DependencyProperty 					FlowDirectionProperty();		//
	static DependencyProperty 					RendererProperty();		//渲染物的依赖属性
	static DependencyProperty 					StyleProperty();		//风格的依赖属性
	static DependencyProperty 					StateMachineProperty();	//状态机的依赖属性

	Event<EventArgs>							Initialized;
	Event<RoutedEventArgs>						Loaded;
	Event<RoutedEventArgs>						Unloaded;
	Event<SizeChangedEventArgs>					SizeChanged;

	Event<DependencyPropertyChangedEventArgs>	IsEnableChanged;
	Event<DependencyPropertyChangedEventArgs>	IsHitTestVisibleChanged;
	Event<DependencyPropertyChangedEventArgs>	IsVisibleChanged;
	Event<EventArgs>							LayoutUpdated;
	Event<MouseEventArgs>						GotMouseCapture;
	Event<MouseEventArgs>						LostMouseCapture;
	Event<TouchEventArgs>						GotTouchCapture;
	Event<TouchEventArgs>						LostTouchCapture;
	Event<DependencyPropertyChangedEventArgs>	FocusableChanged;
	Event<RoutedEventArgs>						LostFocus;
	Event<RoutedEventArgs>						GotFocus;
	Event<DragEventArgs>						PreviewDragEnter;
	Event<DragEventArgs>						DragEnter;
	Event<DragEventArgs>						PreviewDragLeave;
	Event<DragEventArgs>						DragLeave;
	Event<DragEventArgs>						PreviewDragOver;
	Event<DragEventArgs>						DragOver;
	Event<DragEventArgs>						PreviewDrop;
	Event<DragEventArgs>						Drop;
	Event<DependencyPropertyChangedEventArgs>	IsKeyboardFocusedChanged;
	Event<KeyboardFocusChangedEventArgs>		PreviewGotKeyboardFocus;
	Event<KeyboardFocusChangedEventArgs>		GotKeyboardFocus;
	Event<KeyboardFocusChangedEventArgs>		PreviewLostKeyboardFocus;
	Event<KeyboardFocusChangedEventArgs>		LostKeyboardFocus;
	Event<KeyEventArgs>							PreviewKeyDown;
	Event<KeyEventArgs>							KeyDown;
	Event<KeyEventArgs>							PreviewKeyUp;
	Event<KeyEventArgs>							KeyUp;
	Event<MouseEventArgs>						MouseEnter;
	Event<MouseEventArgs>						MouseLeave;
	Event<MouseButtonEventArgs>					PreviewMouseDown;
	Event<MouseButtonEventArgs>					MouseDown;
	Event<MouseButtonEventArgs>					PreviewMouseLeftButtonDown;
	Event<MouseButtonEventArgs>					MouseLeftButtonDown;
	Event<MouseButtonEventArgs>					PreviewMouseLeftButtonUp;
	Event<MouseButtonEventArgs>					MouseLeftButtonUp;
	Event<MouseEventArgs>						PreviewMouseMove;
	Event<MouseEventArgs>						MouseMove;
	Event<MouseButtonEventArgs>					PreviewMouseRightButtonDown;
	Event<MouseButtonEventArgs>					MouseRightButtonDown;
	Event<MouseButtonEventArgs>					PreviewMouseRightButtonUp;
	Event<MouseButtonEventArgs>					MouseRightButtonUp;
	Event<MouseButtonEventArgs>					PreviewMouseUp;
	Event<MouseButtonEventArgs>					MouseUp;
	Event<MouseWheelEventArgs>					PreviewMouseWheel;
	Event<MouseWheelEventArgs>					MouseWheel;
	Event<TouchEventArgs>						PreviewTouchEnter;
	Event<TouchEventArgs>						TouchEnter;
	Event<TouchEventArgs>						PreviewTouchLeave;
	Event<TouchEventArgs>						TouchLeave;
	Event<TouchEventArgs>						PreviewTouchDown;
	Event<TouchEventArgs>						TouchDown;
	Event<TouchEventArgs>						PreviewTouchMove;
	Event<TouchEventArgs>						TouchMove;
	Event<TouchEventArgs>						PreviewTouchUp;
	Event<TouchEventArgs>						TouchUp;

	static RoutedEvent							LoadedEvent();
	static RoutedEvent							UnloadedEvent();
	static RoutedEvent							SizeChangedEvent();
	static RoutedEvent							DragEnterEvent();
	static RoutedEvent							DragLeaveEvent();
	static RoutedEvent							DragOverEvent();
	static RoutedEvent							DropEvent();
	static RoutedEvent							GotFocusEvent();
	static RoutedEvent							GotKeyboardFocusEvent();
	static RoutedEvent							GotMouseCaptureEvent();
	static RoutedEvent							KeyDownEvent();
	static RoutedEvent							KeyUpEvent();
	static RoutedEvent							LostFocusEvent();
	static RoutedEvent							LostKeyboardFocusEvent();
	static RoutedEvent							LostMouseCaptureEvent();
	static RoutedEvent							LostTouchCaptureEvent();
	static RoutedEvent							MouseDownEvent();
	static RoutedEvent							MouseEnterEvent();
	static RoutedEvent							MouseLeaveEvent();
	static RoutedEvent							MouseLeftButtonDownEvent();
	static RoutedEvent							MouseLeftButtonUpEvent();
	static RoutedEvent							MouseMoveEvent();
	static RoutedEvent							MouseRightButtonDownEvent();
	static RoutedEvent							MouseRightButtonUpEvent();
	static RoutedEvent							MouseUpEvent();
	static RoutedEvent							MouseWheelEvent();
	static RoutedEvent							PreviewDragEnterEvent();
	static RoutedEvent							PreviewDragLeaveEvent();
	static RoutedEvent							PreviewDragOverEvent();
	static RoutedEvent							PreviewDropEvent();
	static RoutedEvent							PreviewGotKeyboardFocusEvent();
	static RoutedEvent							PreviewKeyDownEvent();
	static RoutedEvent							PreviewKeyUpEvent();
	static RoutedEvent							PreviewLostKeyboardFocusEvent();
	static RoutedEvent							PreviewMouseDownEvent();
	static RoutedEvent							PreviewMouseLeftButtonDownEvent();
	static RoutedEvent							PreviewMouseLeftButtonUpEvent();
	static RoutedEvent							PreviewMouseMoveEvent();
	static RoutedEvent							PreviewMouseRightButtonDownEvent();
	static RoutedEvent							PreviewMouseRightButtonUpEvent();
	static RoutedEvent							PreviewMouseUpEvent();
	static RoutedEvent							PreviewMouseWheelEvent();
	static RoutedEvent							PreviewTouchDownEvent();
	static RoutedEvent							PreviewTouchMoveEvent();
	static RoutedEvent							PreviewTouchUpEvent();
	static RoutedEvent							TouchDownEvent();
	static RoutedEvent							TouchEnterEvent();
	static RoutedEvent							TouchLeaveEvent();
	static RoutedEvent							TouchMoveEvent();
	static RoutedEvent							TouchUpEvent();

	void setParent(UIElement *element);
	UIElement *getRoot();
	Point worldOffset();
	void updateLayout();

	void measure(const Size &availabelSize);
	void arrage(const Rect &finalRect);
	virtual void onRender(Viewport2D & drawContext);
	template<class ArgsT>
	void addHandler(const RoutedEvent &event, const RoutedEventHandler<ArgsT> &handler)
	{
		if (event.argsType() != typeid(ArgsT))
			nbThrowException(std::logic_error, "[%s]'s args type should be [%s]", event.name().data(), event.argsType().name());
		m_eventHandlers[event.hash()].push_back(handler);
	}
	template<class ArgsT>
	void removeHandler(const RoutedEvent &event, const RoutedEventHandler<ArgsT> handler)
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
	template<class ArgsT>
	void raiseEvent(const ArgsT &args)
	{
		auto iter = m_eventHandlers.find(args.Event.hash());
		if (iter != m_eventHandlers.end())
		{
			for (auto &h : iter->second)
			{
				RoutedEventHandler<ArgsT> hxx(nullptr);
				try {
					auto hx = any_cast<RoutedEventHandler<ArgsT>>(h);
				}
				catch (...) {
					nbThrowException(std::logic_error, "[%s]'s args type should be [%s]", args.Event.name().data(), args.Event.argsType().name());
				}
				hx.invoke(args);
			}
		}
	}
	
public:
	virtual Size measureOverride(const Size &availableSize);
	virtual Size arrangeOverride(const Size &finalSize);

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;

	virtual void onDragEnter(const DragEventArgs &args);
	virtual void onDragLeave(const DragEventArgs &args);
	virtual void onDragOver(const DragEventArgs &args);
	virtual void onDrop(const DragEventArgs &args);
	virtual void onGotFocus(const RoutedEventArgs &args);
	virtual void onGotKeyboardFocus(const KeyboardFocusChangedEventArgs &args);
	virtual void onGotMouseCapture(const MouseEventArgs &args);
	virtual void onGotTouchCapture(const TouchEventArgs &args);
	virtual void onKeyDown(const KeyEventArgs &args);
	virtual void onKeyUp(const KeyEventArgs &args);
	virtual void onLostFocus(const RoutedEventArgs &args);
	virtual void onLostKeyboardFocus(const KeyboardFocusChangedEventArgs &args);
	virtual void onLostMouseCapture(const MouseEventArgs &args);
	virtual void onLostTouchCapture(const TouchEventArgs &args);
	virtual void onMouseEnter(const MouseEventArgs &args);
	virtual void onMouseLeave(const MouseEventArgs &args);
	virtual void onMouseDown(const MouseButtonEventArgs &args);
	virtual void onMouseUp(const MouseButtonEventArgs &args);
	virtual void onMouseLeftButtonDown(const MouseButtonEventArgs &args);
	virtual void onMouseLeftButtonUp(const MouseButtonEventArgs &args);
	virtual void onMouseRightButtonDown(const MouseButtonEventArgs &args);
	virtual void onMouseRightButtonUp(const MouseButtonEventArgs &args);
	virtual void onMouseMove(const MouseButtonEventArgs &args);
	virtual void onMouseWheel(const MouseWheelEventArgs &args);
	virtual void onTouchDown(const TouchEventArgs &args);
	virtual void onTouchEnter(const TouchEventArgs &args);
	virtual void onTouchLeave(const TouchEventArgs &args);
	virtual void onTouchMove(const TouchEventArgs &args);
	virtual void onTouchUp(const TouchEventArgs &args);
	//preview
	virtual void onPreviewDragEnter(const DragEventArgs &args);
	virtual void onPreviewDragLeave(const DragEventArgs &args);
	virtual void onPreviewDragOver(const DragEventArgs &args);
	virtual void onPreviewDrop(const DragEventArgs &args);
	virtual void onPreviewGotKeyboardFocus(const KeyboardFocusChangedEventArgs &args);
	virtual void onPreviewKeyDown(const KeyEventArgs &args);
	virtual void onPreviewKeyUp(const KeyEventArgs &args);
	virtual void onPreviewLostKeyboardFocus(const KeyboardFocusChangedEventArgs &args);
	virtual void onPreviewMouseDown(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseUp(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseLeftButtonDown(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseLeftButtonUp(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseRightButtonDown(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseRightButtonUp(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseMove(const MouseButtonEventArgs &args);
	virtual void onPreviewMouseWheel(const MouseWheelEventArgs &args);
	virtual void onPreviewTouchDown(const TouchEventArgs &args);
	virtual void onPreviewTouchEnter(const TouchEventArgs &args);
	virtual void onPreviewTouchLeave(const TouchEventArgs &args);
	virtual void onPreviewTouchMove(const TouchEventArgs &args);
	virtual void onPreviewTouchUp(const TouchEventArgs &args);

	UIElement	*m_parent;

private:

//	std::map<size_t, std::vector<RoutedEventHandler>>	m_eventHandlers;
};

using UIElementPtr = std::shared_ptr<UIElement>;

}
}
