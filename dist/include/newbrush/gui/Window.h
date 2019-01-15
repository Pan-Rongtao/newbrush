#pragma once
#include "../core/Property.h"
#include "../core/Event.h"
#include "../gui/ContentControl.h"

namespace nb{ namespace gl{
	class Window;
}}

namespace nb{ namespace gui {

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
	nb::core::Property_rw<std::string>						Title;
	nb::core::Property_rw<std::shared_ptr<ImageSource>>		Icon;

private:
	std::shared_ptr<nb::gl::Window>		m_glWindow;
};

}}
