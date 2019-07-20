#include "TestWindow.h"
#include <thread>

void TestWindow::test()
{
	Window w;
	w.setX(0);
	w.setY(0);
	//auto width = w.width();
	//auto h = w.height();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	w.setWidth(800);
	w.setHeight(480);

	while (true)
	{
		w.pending();
	}
}