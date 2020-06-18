#pragma once
#include "newbrush/core/Event.h"
#include "newbrush/core/EventArgs.h"
#include "newbrush/gui/ContentControl.h"
#include "newbrush/gles/Viewport2D.h"

struct GLFWwindow;
namespace nb{
	
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

class NB_API Window : public ContentControl
{
	RTTR_ENABLE(ContentControl)
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

	Point getMousePosition() const;
	static void pollEvents();
	static Viewport2D drawContext;

	static DependencyPropertyPtr WindowStateProperty();	//窗口状态的依赖属性（WindowStateE）
	static DependencyPropertyPtr WindowStyleProperty();	//窗口样式的依赖属性（WindowStyle）
	static DependencyPropertyPtr TopmostProperty();		//置顶的依赖属性（bool）
	static DependencyPropertyPtr LeftProperty();		//左位置的依赖属性（float）
	static DependencyPropertyPtr TopProperty();			//顶位置的依赖属性（float）
	static DependencyPropertyPtr TitleProperty();		//标题的依赖属性（std::string）
	static DependencyPropertyPtr IconProperty();		//图标的依赖属性（std::shared_ptr<ImageSource>）

	Event<EventArgs>			Activated;				//当窗口成为前台窗口时发生
	Event<EventArgs>			Deactivated;			//当窗口成为后台窗口时发生
	Event<EventArgs>			Closed;					//当窗口将关闭时发生
	Event<CancelEventArgs>		Closing;				//调用close后发生，可取消关闭窗口
	Event<EventArgs>			LocationChanged;		//位置发生变化时发生
	Event<EventArgs>			StateChanged;			//WindowState更改时发生
	Event<EventArgs>			SourceInitiallized;		//资源初始化完成时发生，可在此获得该窗体的句柄用来与Win32交互
	Event<EventArgs>			ContentRendered;		//当窗口的内容呈现后发生

protected:
	virtual void onRender(Viewport2D & drawContext) override;
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

	static void init();
	static void deinit();

	void destroyWindow();
	void render();

	static void onWindowStatePropertyChanged(DependencyObject *obj, DependencyPropertyChangedEventArgs *args);
	static void onWindowStyleChanged(DependencyObject *obj, DependencyPropertyChangedEventArgs *args);
	static void onTopmostPropertyChanged(DependencyObject *obj, DependencyPropertyChangedEventArgs *args);
	static void onLeftPropertyChanged(DependencyObject *obj, DependencyPropertyChangedEventArgs *args);
	static void onTopPropertyChanged(DependencyObject *obj, DependencyPropertyChangedEventArgs *args);
	static void onTitlePropertyChanged(DependencyObject *obj, DependencyPropertyChangedEventArgs *args);
	static void onIconPropertyChanged(DependencyObject *obj, DependencyPropertyChangedEventArgs *args);
	
	GLFWwindow		*m_implWindow;
	bool			m_dispatchingCloseEvent;
	bool			m_processingCallback;
	bool			m_processingWindowStateChanged;
	WindowStateE	m_lastWindowState;

	friend class Application;

};

}
