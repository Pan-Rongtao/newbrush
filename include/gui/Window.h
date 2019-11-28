#pragma once
#include "../core/Property.h"
#include "../core/Event.h"
#include "../gui/ContentControl.h"
#include "../gles/Context.h"
#include "../gui/Gui.h"

struct GLFWwindow;
namespace nb{
class ImageSource;
namespace gui {

class NB_API Window : public ContentControl
{
public:
	Window();
	virtual ~Window();

	//激活，针对未显示的窗口不产生影响
	void active();

	//显示，并不保证激活到前台
	void show();

	//隐藏
	void hide();

	//关闭/销毁窗口
	void close();

	Property_rw<WindowStateE>				WindowState;			//窗口状态
	Property_rw<WindowStyleE>				WindowStyle;			//窗口样式
	Property_rw<bool>						Topmost;				//置顶
	Property_rw<float>						Left;					//左位置
	Property_rw<float>						Top;					//顶位置
	Property_rw<std::string>				Title;					//标题
	Property_rw<shared_ptr<ImageSource>>	Icon;					//图标（未实现，难点）
	static DependencyProperty				WindowStateProperty();	//窗口状态的依赖属性
	static DependencyProperty				WindowStyleProperty();	//窗口样式的依赖属性
	static DependencyProperty				TopmostProperty();		//置顶的依赖属性
	static DependencyProperty				LeftProperty();			//左位置的依赖属性
	static DependencyProperty				TopProperty();			//顶位置的依赖属性
	static DependencyProperty				TitleProperty();		//标题的依赖属性
	static DependencyProperty				IconProperty();			//图标的依赖属性

	static shared_ptr<gl::Context>			drawContext;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	std::vector<UIElement *> hitElements(int x, int y) const;

	void onWindowStateChanged(const WindowStateE &_old, const WindowStateE &_new);
	void onWindowStyleChanged(const WindowStyleE &_old, const WindowStyleE &_new);
	void onTopmostChanged(const bool &_old, const bool &_new);
	void onLeftChanged(const float &_old, const float &_new);
	void onTopChanged(const float &_old, const float &_new);
	void onTitleChanged(const std::string &_old, const std::string &_new);
	void onIconChanged(const std::shared_ptr<ImageSource> &_old, const std::shared_ptr<ImageSource> &_new);
	void onWidthChanged(const float &_old, const float &_new);
	void onHeightChanged(const float &_old, const float &_new);

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

	static void init();
	static void deinit();
	bool shouldClose() const;
	void swapBuffers() const;
	static void waitEvent();
	GLFWwindow		*m_implWindow;
	friend class Application;
};

}}
