#pragma once
#include "../core/Event.h"
#include "../core/EventArgs.h"
#include "../gui/WindowCollection.h"

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

	//关闭模式
	void setShutdownMode(ShutdownModeE mode);
	ShutdownModeE shutdownMode() const;

	//所有窗口
	const WindowCollection &windows() const;

	//主窗口（默认为第一个窗口）
	void setMainWindow(Window *w);
	Window *mainWindow();

	//运行
	//返回值：退出码，默认情况下为0
	int run(int argc, char *argv[]);

	//关闭应用程序
	//exitCode：关闭码（即应用程序返回值）
	void shutdown();
	void shutdown(int exitCode);

	Event<EventArgs>						Activated;				//当应用程序成为前台应用程序，发生
	Event<EventArgs>						Deactivated;			//当应用程序不再是前台应用程序，发生
	Event<UnhandledExceptionEventArgs>		UnhandledException;		//如果异常是由应用程序引发，且继承于std::exception，异常未处理时发生
	Event<EventArgs>						UnhandledExtraException;//如果异常是由应用程序引发，但自定义的异常，异常未处理时发生
	Event<ExitEventArgs>					Exit;					//关闭过程的最后通知
	Event<EventArgs>						LoadCompleted;			//加载完成并呈现时发生
	Event<SessionEndingCancelEventArgs>		SessionEnding;			//用户在注销或关闭操作系统时发生
	Event<StartupEventArgs>					Startup;				//当启动时发生

protected:
	virtual void onActivated(const EventArgs &args);
	virtual void onDeactivated(EventArgs &args);
	virtual void onExit(const ExitEventArgs &args);
	virtual void onLoadCompleted(const EventArgs &args);
	virtual void onSessionEnding(const SessionEndingCancelEventArgs &args);
	virtual void onStartUp(const StartupEventArgs &args);

private:
	void render();
	void onWindowClosed(const WindowCollection::WindowClosedEventArgs &args);

	ShutdownModeE		m_shutdownMode;
	bool				m_exitFlag;
	static Application	*g_app;
};

}}
