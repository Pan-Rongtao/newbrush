#pragma once

namespace nb{ namespace gui{

class Window;
class WindowManager
{
public:
	//
	static void Push(nb::gui::Window *window);

	//
	static void Erease(nb::gui::Window *window);

	//获取窗口个数
	static int GetCount();

	//查找一个窗口
	static nb::gui::Window *At(int index);
};

}}
