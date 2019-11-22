#pragma once
#include "../core/Property.h"
#include "../core/Event.h"
#include "../gui/ContentControl.h"
#include "../gles/Context.h"
#include "../core/Window.h"

namespace nb{ namespace gl{
	class Window;
	class Context;
	class Surface;
}}

namespace nb{
class ImageSource;
namespace gui {

class NB_API Window : public ContentControl
{
public:
	Window();
	virtual ~Window();

	//激活，针对未显示的窗口不产生影响
	void active();

	//显示，并不保证激活到前台
	void show();

	//隐藏
	void hide();

	//关闭/销毁窗口
	void close();

	Property_rw<WindowStateE>				WindowState;			//窗口状态
	Property_rw<WindowStyleE>				WindowStyle;			//窗口样式
	Property_rw<bool>						Topmost;				//置顶
	Property_rw<float>						Left;					//左位置
	Property_rw<float>						Top;					//顶位置
	Property_rw<std::string>				Title;					//标题
	Property_rw<shared_ptr<ImageSource>>	Icon;					//图标（未实现，难点）
	Property_rw<shared_ptr<gl::Surface>>	DrawSurface;			//
	static DependencyProperty				WindowStateProperty();	//窗口状态的依赖属性
	static DependencyProperty				WindowStyleProperty();	//窗口样式的依赖属性
	static DependencyProperty				TopmostProperty();		//置顶的依赖属性
	static DependencyProperty				LeftProperty();			//左位置的依赖属性
	static DependencyProperty				TopProperty();			//顶位置的依赖属性
	static DependencyProperty				TitleProperty();		//标题的依赖属性
	static DependencyProperty				IconProperty();			//图标的依赖属性
	static DependencyProperty				DrawSurfaceProperty();	//

	static shared_ptr<gl::Context>			drawContext;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	std::vector<UIElement *> hitElements(int x, int y) const;

	void onWindowStateChanged(const WindowStateE &_old, const WindowStateE &_new);
	void onWindowStyleChanged(const WindowStyleE &_old, const WindowStyleE &_new);
	void onTopmostChanged(const bool &_old, const bool &_new);
	void onLeftChanged(const float &_old, const float &_new);
	void onTopChanged(const float &_old, const float &_new);
	void onTitleChanged(const std::string &_old, const std::string &_new);
	void onIconChanged(const std::shared_ptr<ImageSource> &_old, const std::shared_ptr<ImageSource> &_new);
	void onWidthChanged(const float &_old, const float &_new);
	void onHeightChanged(const float &_old, const float &_new);

	void onNativeWindowResize(const nb::Window::ResizeArgs &args);
	void onNativeWindowMouseEnter(const nb::Window::MouseEnterEventArgs &args);
	void onNativeWindowMouseLeave(const nb::Window::MouseLeaveEventArgs &args);
	void onNativeWindowMouseMove(const nb::Window::MouseMoveEventArgs &args);
	void onNativeWindowMouseLeftButton(const nb::Window::MouseLeftButtonEventArgs &args);
	void onNativeWindowMouseRightButton(const nb::Window::MouseRightButtonEventArgs &args);
	void onNativeWindowMouseMiddleButton(const nb::Window::MouseMiddleButtonEventArgs &args);
	void onNativeWindowMouseWheel(const nb::Window::MouseWheelEventArgs &args);
	void onNativeWindowKeyAction(const nb::Window::KeyEventArgs &args);

	std::shared_ptr<nb::gl::Window>		m_glWindow;
};

}}
