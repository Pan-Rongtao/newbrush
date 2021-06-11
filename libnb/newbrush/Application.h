#pragma once
#include <queue>
#include <mutex>
#include "newbrush/ResourceDictionary.h"
#include "newbrush/Window.h"

namespace nb{
	
enum class ShutdownModeE : uint8_t
{
	OnExplicitShutdown,		//仅调用shutdown时关闭应用程序
	OnLastWindowClose,		//最后一个窗口关闭或调用shutdown时关闭应用程序
	OnMainWindowClose,		//主窗口关闭或调用shutdown时关闭应用程序
};

class NB_API MessageQueue
{
public:
	using Task = std::function<void(void)>;

	void post(const Task &task);
	Task pick();

private:
	std::mutex m_mutex;
	std::queue<Task> m_msgQueue;
};

class NB_API Application : public Object
{
public:
	//构建一个app，如果构建超过一次，会发出异常std::logic_error
	Application();
	virtual ~Application() = default;

	//获取app实例，如果未创建，将返回空
	static Application *get();

	//关闭模式
	void setShutdownMode(ShutdownModeE mode);
	ShutdownModeE shutdownMode() const;

	//窗口
	const WindowCollection &windows() const;
	void setMainWindow(Window *w);
	Window *mainWindow();

	//资源
	ref<ResourceDictionary> resources();

	//运行
	//返回值：退出码，默认情况下为0
	int run(int argc = 0, char *argv[] = nullptr);

	//关闭应用程序
	//exitCode：关闭码（即应用程序返回值）
	void shutdown(int exitCode = 0);

	//向主线程抛入任务
	void post(const MessageQueue::Task &task);

	//注册插件
	template<class PluginT>
	void registerStudioPlugin()
	{
		_registerPlugin(createRef<PluginT>());
	}

	Event<EventArgs>						Activated;				//当应用程序成为前台应用程序，发生
	Event<EventArgs>						Deactivated;			//当应用程序不再是前台应用程序，发生
	Event<ExitEventArgs>					Exit;					//关闭过程的最后通知
	Event<EventArgs>						LoadCompleted;			//加载完成并呈现时发生
	Event<StartupEventArgs>					Startup;				//当启动时发生

protected:
	virtual void onActivated(const EventArgs &args);
	virtual void onDeactivated(EventArgs &args);
	virtual void onExit(const ExitEventArgs &args);
	virtual void onLoadCompleted(const EventArgs &args);
	virtual void onStartUp(const StartupEventArgs &args);

private:
	void onWindowClosed(const bool &isMain);
	void onWindowFocused(const bool &focused);

	bool m_exitFlag;
	ShutdownModeE m_shutdownMode;
	ref<ResourceDictionary> m_resources;
	MessageQueue m_msgQueue;
};

}
