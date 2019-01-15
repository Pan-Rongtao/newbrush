#pragma once
#include <vector>
#include "../gles/Application.h"
#include "../core/Property.h"

namespace nb{ namespace gui{

class Window;
class NB_API Application : public nb::gl::Application
{
public:
	//构建一个app，如果构建超过一次，会发出异常：nb::core::LogicException
	Application();
	virtual ~Application();

	//单例
	static std::shared_ptr<Application> current();

	//运行
	int run();

public:
	nb::core::Property_rw<std::shared_ptr<Window>>					MainWindow;
	nb::core::Property_r<std::vector<std::shared_ptr<Window>>>		Windows;

private:
	std::vector<std::shared_ptr<Window>>	m_windows;
};

}}
