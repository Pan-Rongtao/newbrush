#pragma once
#include "core/Def.h"
#include "gles/Display.h"
#include "gles/Configure.h"

namespace nb{
namespace gui{

class NB_API Application
{
public:
	//构建一个app，如果构建超过一次，会发出异常std::logic_error
	Application(std::shared_ptr<gl::Display> display = nullptr, std::shared_ptr<gl::Configure> configure = nullptr);
	virtual ~Application();

	//获取实例，如果未创建，将返回空
	static Application *current();

	//运行
	int run();

private:
	void render();

	static Application *g_app;
};

}}
