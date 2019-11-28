#pragma once
#include "core/Def.h"

namespace nb{
namespace gui{

class Window;
class NB_API Application
{
public:
	//构建一个app，如果构建超过一次，会发出异常std::logic_error
	Application();
	virtual ~Application();

	//获取实例，如果未创建，将返回空
	static Application *current();

	//所有窗口
	std::vector<Window *> &windows();

	//运行
	int run();

private:
	void render();

	std::vector<Window *>	m_windows;
	static Application		*g_app;
};

}}
