#include "TestWindow.h"
#include <thread>

void TestWindow::test()
{
	Window w;
	w.ResizeEvent += std::bind(&TestWindow::onResize, this, std::placeholders::_1);
	w.MouseEnterEvent += std::bind(&TestWindow::onMouseEnter, this, std::placeholders::_1);
	w.MouseLeaveEvent += std::bind(&TestWindow::onMouseLeave, this, std::placeholders::_1);
	w.MouseMoveEvent += std::bind(&TestWindow::onMouseMove, this, std::placeholders::_1);
	w.MouseLeftButtonEvent += std::bind(&TestWindow::onMouseLeftButton, this, std::placeholders::_1);
	w.MouseRightButtonEvent += std::bind(&TestWindow::onMouseRightButton, this, std::placeholders::_1);
	w.MouseMiddleButtonEvent += std::bind(&TestWindow::onMouseMiddleButton, this, std::placeholders::_1);
	w.MouseWheelEvent += std::bind(&TestWindow::onMouseWheel, this, std::placeholders::_1);
	w.KeyEvent += std::bind(&TestWindow::onKeyAction, this, std::placeholders::_1);

	Window w1;
	w1.ResizeEvent += std::bind(&TestWindow::onResize, this, std::placeholders::_1);
	w1.MouseEnterEvent += std::bind(&TestWindow::onMouseEnter, this, std::placeholders::_1);
	w1.MouseLeaveEvent += std::bind(&TestWindow::onMouseLeave, this, std::placeholders::_1);
	w1.MouseMoveEvent += std::bind(&TestWindow::onMouseMove, this, std::placeholders::_1);
	w1.MouseLeftButtonEvent += std::bind(&TestWindow::onMouseLeftButton, this, std::placeholders::_1);
	w1.MouseRightButtonEvent += std::bind(&TestWindow::onMouseRightButton, this, std::placeholders::_1);
	w1.MouseMiddleButtonEvent += std::bind(&TestWindow::onMouseMiddleButton, this, std::placeholders::_1);
	w1.MouseWheelEvent += std::bind(&TestWindow::onMouseWheel, this, std::placeholders::_1);
	w1.KeyEvent += std::bind(&TestWindow::onKeyAction, this, std::placeholders::_1);

	while (true)
	{
		w.pending();
	}
}

void TestWindow::onResize(const Window::ResizeArgs &args)
{
	printf("TestWindow::OnResize: width=%d, height=%d\n", args.width, args.height);
}

void TestWindow::onMouseEnter(const Window::MouseEnterEventArgs & args)
{
	printf("TestWindow::onMouseEnter\n");
}

void TestWindow::onMouseLeave(const Window::MouseLeaveEventArgs & args)
{
	printf("TestWindow::onMouseLeave\n");
}

void TestWindow::onMouseMove(const Window::MouseMoveEventArgs & args)
{
	printf("TestWindow::onMouseMove x=%d, y=%d\n", args.x, args.y);
}

void TestWindow::onMouseLeftButton(const Window::MouseLeftButtonEventArgs & args)
{
	printf("TestWindow::onMouseLeftButton %s x=%d, y=%d\n", args.pressed ? "down" : "up", args.x, args.y);
}

void TestWindow::onMouseRightButton(const Window::MouseRightButtonEventArgs & args)
{
	printf("TestWindow::onMouseRightButton %s x=%d, y=%d\n", args.pressed ? "down" : "up", args.x, args.y);
}

void TestWindow::onMouseMiddleButton(const Window::MouseMiddleButtonEventArgs & args)
{
	printf("TestWindow::onMouseMiddleButton %s x=%d, y=%d\n", args.pressed ? "down" : "up", args.x, args.y);
}

void TestWindow::onMouseWheel(const Window::MouseWheelEventArgs & args)
{
	printf("TestWindow::onMouseWheel delta=%d\n", args.delta);
}

void TestWindow::onKeyAction(const Window::KeyEventArgs &args)
{
	printf("TestWindow::OnKeyAction %s, key=%d, mask=%d\n", args.down ? "down" : "up", args.key, args.mask);
}