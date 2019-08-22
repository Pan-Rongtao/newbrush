#pragma once
#include "../gles/Application.h"

namespace nb{
namespace gui{

class NB_API Application : public gl::Application
{
public:
	//构建一个app，如果构建超过一次，会发出异常std::logic_error
	Application();
	virtual ~Application();

	//获取实例，如果未创建，将返回空
	static Application *current();

	//运行
	int run();

protected:
	virtual void preRender() override;

private:
	static Application *g_app;
};

}}
