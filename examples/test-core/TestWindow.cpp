#include "TestWindow.h"
#include <thread>

void TestWindow::test()
{
	Window w;
	w.ResizeEvent += std::bind(&TestWindow::OnResize, this, std::placeholders::_1);
	w.MouseEvent += std::bind(&TestWindow::OnMouseAction, this, std::placeholders::_1);
	w.KeyEvent += std::bind(&TestWindow::OnKeyAction, this, std::placeholders::_1);

	while (true)
	{
		w.pending();
	}
}

void TestWindow::OnResize(const nb::core::Window::ResizeArgs &args)
{
	printf("TestWindow::OnResize: width=%d, height=%d\n", args.width, args.height);
}

void TestWindow::OnMouseAction(const nb::core::Window::MouseEventArgs &args)
{
	printf("TestWindow::OnMouseAction: action=%d, x=%d, y=%d\n", args.action, args.x, args.y);
}

void TestWindow::OnKeyAction(const nb::core::Window::KeyEventArgs &args)
{
	printf("TestWindow::OnKeyAction: action=%d, key=%d, mask=%d\n", args.action, args.key, args.mask);
}