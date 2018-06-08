#pragma once

namespace nb{ namespace Gui{

class Window;
class WindowManager
{
public:
	//
	static void Push(nb::Gui::Window *window);

	//
	static void Erease(nb::Gui::Window *window);

	//获取窗口个数
	static int GetCount();

	//查找一个窗口
	static nb::Gui::Window *At(int index);
};

}}
