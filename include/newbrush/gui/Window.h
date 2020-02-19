#pragma once
#include "newbrush/core/Property.h"
#include "newbrush/core/Event.h"
#include "newbrush/core/EventArgs.h"
#include "newbrush/gui/ContentControl.h"
#include "newbrush/gles/Viewport2D.h"

struct GLFWwindow;
namespace nb{
namespace gui {
	
enum class WindowStateE
{
	Normal,		//还原
	Maximized,	//最大化
	Minimized,	//最小化
};

enum class WindowStyleE
{
	None,		//仅工作区可见
	Fixed,		//
	SizeBox,
};

class NB_API Window : public ContentControl
{
public:
	Window();
	virtual ~Window();

	//显示并激活窗口到前台
	void active();

	//使Visibility变成Visible，但不保证激活到前台。比如当窗口处于最小化状态时
	void show();

	//隐藏窗口
	void hide();

	//关闭/销毁窗口
	void close();

	static DependencyProperty				WindowStateProperty();	//窗口状态的依赖属性
	static DependencyProperty				WindowStyleProperty();	//窗口样式的依赖属性
	static DependencyProperty				TopmostProperty();		//置顶的依赖属性
	static DependencyProperty				LeftProperty();			//左位置的依赖属性
	static DependencyProperty				TopProperty();			//顶位置的依赖属性
	static DependencyProperty				TitleProperty();		//标题的依赖属性
	static DependencyProperty				IconProperty();			//图标的依赖属性

	Event<EventArgs>						Activated;				//当窗口成为前台窗口时发生
	Event<EventArgs>						Deactivated;			//当窗口成为后台窗口时发生
	Event<EventArgs>						Closed;					//当窗口将关闭时发生
	Event<CancelEventArgs>					Closing;				//调用close后发生，可取消关闭窗口
	Event<EventArgs>						LocationChanged;		//位置发生变化时发生
	Event<EventArgs>						StateChanged;			//WindowState更改时发生
	Event<EventArgs>						SourceInitiallized;		//资源初始化完成时发生，可在此获得该窗体的句柄用来与Win32交互
	Event<EventArgs>						ContentRendered;		//当窗口的内容呈现后发生
	
	void swapBuffers() const;
	static void waitEvent();

	static Viewport2D drawContext;

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;

	virtual void onActivated(const EventArgs &args);
	virtual void onDeactivated(const EventArgs &args);
	virtual void onClosed(const EventArgs &args);
	virtual void onClosing(const CancelEventArgs &args);
	virtual void onLocationChanged(const EventArgs &args);
	virtual void onStateChanged(const EventArgs &args);
	virtual void onSourceInitiallized(const EventArgs &args);
	virtual void onContentRendered(const EventArgs &args);

	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	void _close(bool eraseFromCollection);
	std::vector<UIElement *> hitElements(int x, int y) const;

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
	void maximizeCallback(GLFWwindow* window, int maximized);

	static void init();
	static void deinit();

	void destroyWindow();

	GLFWwindow		*m_implWindow;
	bool			m_onDispatching{ false };

	friend class Application;
};

}}
