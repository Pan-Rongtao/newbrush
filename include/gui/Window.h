#pragma once
#include "../core/Property.h"
#include "../core/Event.h"
#include "../gui/ContentControl.h"
#include "../gles/Context.h"

namespace nb{ namespace gl{
	class Window;
	class Context;
	class Surface;
}}

namespace nb{ namespace gui {

enum class WindowState
{
	Normal,
	Maximized,
	Minimized
};


class NB_API Window : public ContentControl
{
public:
	Window();
	virtual ~Window();

	//显示并激活
	void active();

	//显示隐藏
	void show();
	void hide();

	//关闭
	void close();

public:
	nb::core::Property_rw<gui::WindowState>					WindowState;
	nb::core::Property_rw<bool>								Topmost;
	nb::core::Property_rw<double>							Left;
	nb::core::Property_rw<double>							Top;
	nb::core::Property_rw<std::string>						Title;
	nb::core::Property_rw<std::shared_ptr<ImageSource>>		Icon;
	nb::core::Property_rw<std::shared_ptr<nb::gl::Context>>	DrawContext;
	nb::core::Property_rw<std::shared_ptr<nb::gl::Surface>>	DrawSurface;

private:
	void onWindowStateChanged(const gui::WindowState &_old, const gui::WindowState &_new);
	void onTopmostChanged(const bool &_old, const bool &_new);
	void onLeftChanged(const double &_old, const double &_new);
	void onTopChanged(const double &_old, const double &_new);
	void onWidthChanged(const double &_old, const double &_new);
	void onHeightChanged(const double &_old, const double &_new);
	void onTitleChanged(const std::string &_old, const std::string &_new);
	void onIconChanged(const std::shared_ptr<ImageSource> &_old, const std::shared_ptr<ImageSource> &_new);

	std::shared_ptr<nb::gl::Window>		m_glWindow;
};

}}
