#pragma once
#include <string>
#include "newbrush/Object.h"
#include "newbrush/Event.h"
#include "newbrush/Types.h"

struct GLFWwindow;
namespace nb 
{

enum class WindowStateE
{
	Normal,		//还原
	Maximized,	//最大化
	Minimized,	//最小化
};

enum class WindowStyleE
{
	None,		//仅工作区可见
	Fixed,		//不可改变尺寸
	SizeBox,	//有边框（默认）
};

class Node2D;
class NB_API Window : public Object
{
public:
	Window();
	Window(float width, float heith);
	Window(const std::string &title);
	Window(float width, float height, const std::string &title);
	~Window();

	//标题
	void setTitle(const std::string &title);
	const std::string &title() const;

	void setPosition(float x, float y);

	//宽高
	void setWidth(float width);
	void setHeight(float height);
	float width() const;
	float height() const;

	//显示并激活窗口到前台
	void active();

	//关闭/销毁窗口
	void close();

	//使Visibility变成Visible，但不保证激活到前台。
	//比如当窗口处于最小化状态时
	void show(bool bShow);
	bool isShow() const;

	//窗口状态
	void setWindowState(WindowStateE state);
	WindowStateE windowState() const;

	//窗口样式
	void setWindowsStyle(WindowStyleE style);
	WindowStyleE windowStyle() const;

	//窗口置顶
	void setTopmost(bool topmost);
	bool topmost() const;

	//获取鼠标位置
	Point getMousePosition() const;

	ref<Node2D> root;

	Event<KeyEventArgs>			Key;
	Event<TouchEventArgs>		Touch;
	Event<ScrollEventArgs>		Scroll;
	Event<EventArgs>			Activated;				//当窗口成为前台窗口时发生
	Event<EventArgs>			Deactivated;			//当窗口成为后台窗口时发生
	Event<EventArgs>			Closed;					//当窗口将关闭时发生
	Event<CancelEventArgs>		Closing;				//调用close后发生，可取消关闭窗口
	Event<EventArgs>			LocationChanged;		//位置发生变化时发生
	Event<EventArgs>			StateChanged;			//WindowState更改时发生
	Event<EventArgs>			SourceInitiallized;		//资源初始化完成时发生，可在此获得该窗体的句柄用来与Win32交互
	Event<EventArgs>			ContentRendered;		//当窗口的内容呈现后发生

private:
	void _close(bool eraseFromCollection);

	void posCallback(int x, int y);
	void sizeCallback(int width, int height);
	void frameBufferSizeCallback(int width, int height);
	void mouseButtonCallback(int button, int action, int mods);
	void cusorPosCallback(double x, double y);
	void cusorPosEnterCallback(int entered);
	void scrollCallback(double x, double y);
	void keyCallback(int key, int scancode, int action, int mods);
	void focusCallback(int focused);
	void refreshCallback();
	void closeCallback();
	void iconifyCallback(int iconified);
	void maximizeCallback(int maximized);

	void destroyWindow();
	void render();

	static void init();
	static void deinit();
	static void pollEvents();

#if NB_OS != NB_OS_ANDROID
	GLFWwindow		*m_implWindow;
#endif
	bool			m_dispatchingCloseEvent;
	bool			m_processingCallback;
	bool			m_processingWindowStateChanged;
	WindowStateE	m_lastWindowState;
	std::string		m_title;
	friend class Application;
};

class WindowCollection : public Object
{
public:
	static WindowCollection *get();

	size_t count() const;

	Window * operator[](size_t index);

private:
	void push(Window *w);
	void erase(Window *w);
	std::vector<Window *> &windows();

	void setMainWindow(Window *w);
	Window *mainWindow();

	Event<bool>	WindowClosed;
	Event<bool>	WindowFocus;

	std::vector<Window *>	m_windows;
	Window					*m_mainWindow;

	friend class Window;
	friend class Application;
};

}

