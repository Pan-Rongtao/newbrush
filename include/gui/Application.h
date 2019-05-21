﻿#pragma once
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

	//获取实例，如果为创建，将返回空
	static std::shared_ptr<Application> current();

	//运行
	int run();

protected:
	virtual void PreRenderOverride() override;

};

}}
