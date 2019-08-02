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

namespace nb{ namespace gui {

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

public:
	nb::core::Property_rw<core::WindowStateE>				WindowState;
	nb::core::Property_rw<core::WindowStyleE>				WindowStyle;
	nb::core::Property_rw<bool>								Topmost;
	nb::core::Property_rw<float>							Left;
	nb::core::Property_rw<float>							Top;
	nb::core::Property_rw<std::string>						Title;
	nb::core::Property_rw<std::shared_ptr<ImageSource>>		Icon;	//未实现，难点
	static nb::core::Property_rw<std::shared_ptr<nb::gl::Context>>	DrawContext;
	nb::core::Property_rw<std::shared_ptr<nb::gl::Surface>>	DrawSurface;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

private:
	std::vector<UIElement *> hitElements(int x, int y) const;

	void onWindowStateChanged(const core::WindowStateE &_old, const core::WindowStateE &_new);
	void onWindowStyleChanged(const core::WindowStyleE &_old, const core::WindowStyleE &_new);
	void onTopmostChanged(const bool &_old, const bool &_new);
	void onLeftChanged(const float &_old, const float &_new);
	void onTopChanged(const float &_old, const float &_new);
	void onTitleChanged(const std::string &_old, const std::string &_new);
	void onIconChanged(const std::shared_ptr<ImageSource> &_old, const std::shared_ptr<ImageSource> &_new);
	void onWidthChanged(const float &_old, const float &_new);
	void onHeightChanged(const float &_old, const float &_new);

	void onNativeWindowResize(const core::Window::ResizeArgs &args);
	void onNativeWindowMouseEnter(const core::Window::MouseEnterEventArgs &args);
	void onNativeWindowMouseLeave(const core::Window::MouseLeaveEventArgs &args);
	void onNativeWindowMouseMove(const core::Window::MouseMoveEventArgs &args);
	void onNativeWindowMouseLeftButton(const core::Window::MouseLeftButtonEventArgs &args);
	void onNativeWindowMouseRightButton(const core::Window::MouseRightButtonEventArgs &args);
	void onNativeWindowMouseMiddleButton(const core::Window::MouseMiddleButtonEventArgs &args);
	void onNativeWindowMouseWheel(const core::Window::MouseWheelEventArgs &args);
	void onNativeWindowKeyAction(const core::Window::KeyEventArgs &args);

	std::shared_ptr<nb::gl::Window>		m_glWindow;
};

}}
