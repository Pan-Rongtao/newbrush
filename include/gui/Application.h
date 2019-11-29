#pragma once
#include "core/Property.h"

namespace nb{
namespace gui{

enum class ShutdownModeE : uint8_t
{
	OnExplicitShutdown,		//仅调用shutdown时关闭应用程序
	OnLastWindowClose,		//最后一个窗口关闭或调用shutdown时关闭应用程序
	OnMainWindowClose,		//主窗口关闭或调用shutdown时关闭应用程序
};

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

	//主窗口（默认为第一个窗口）
	void setMainWindow(Window *w);
	Window *mainWindow();

	//运行
	//返回值：退出码，默认情况下为0
	int run();

	//关闭
	//exitCode：关闭码（即应用程序返回值）
	void shutdown();
	void shutdown(int exitCode);

protected:


private:
	void render();

	std::vector<Window *>	m_windows;
	Window					*m_mainWindow;
	static Application		*g_app;
};

}}
