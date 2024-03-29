#include "newbrush/gui/controls/Image.h"
#include "newbrush/core/media/Brush.h"
#include "newbrush/gui/shapes/Shape.h"
#include "newbrush/gui/shapes/Rectangle.h"
#include "newbrush/gui/Window.h"
#include "newbrush/core/Timer.h"
#include "newbrush/core/Log.h"
#include "catch2/catch.hpp"
#include "newbrush/core/media/SolidColorBrush.h"

using namespace nb;

TEST_CASE("Test nb::Window", "[Window]")
{
	auto w = std::make_shared<Window>();
	w->setValue(Window::TitleProperty(), std::string("Newbrush窗口测试"));
	auto img = std::make_shared<ImageSource>("../images/nb0.png");
	w->setValue(Window::IconProperty(), img);
	w->setValue(Window::WindowStyleProperty(), WindowStyleE::SizeBox);
	w->setValue<BrushPtr>(Window::BackgroundProperty(), std::make_shared<SolidColorBrush>(Colors::red()));

	w->Activated += [](const EventArgs &args) {
		Log::info("on activated");
	};

	w->Closing += [](CancelEventArgs &args) {
		args.cancel = false;
		Log::info("%s close", args.cancel ? "cancel" : "affirm");
	};

	w->Closed += [](const EventArgs &args) {
		Log::info("on closed");
	};

	w->StateChanged += [w](const EventArgs &args) {
		auto state = w->getValue<WindowStateE>(Window::WindowStateProperty());
		Log::info("on state changed:%d", state);
	};

	//w->setValue(Window::WindowStateProperty(), 1);
	//w->setValue(Window::WindowStateProperty(), WindowStateE::Minimized);
	//w->setValue(Window::WindowStateProperty(), WindowStateE::Normal);
	Timer timer;
	timer.Tick += [w](const EventArgs &args) {
		static int i = 0;
		std::string sTitle;
		switch (i)
		{
		case 0: w->hide();																sTitle = "hide";					break;
		case 1: w->show();																sTitle = "show";					break;
		case 2: w->hide();																sTitle = "hide";					break;
		case 3: w->setValue(Window::WindowStateProperty(), WindowStateE::Maximized);	sTitle = "WindowStateE::Maximized";	break;
		case 4: w->setValue(Window::WindowStateProperty(), WindowStateE::Minimized);	sTitle = "WindowStateE::Minimized";	break;
		case 5: w->setValue(Window::WindowStateProperty(), WindowStateE::Normal);		sTitle = "WindowStateE::Normal";	break;
		case 6: w->setValue(Window::WindowStyleProperty(), WindowStyleE::None);			sTitle = "WindowStyleE::None";		break;
		case 7: w->setValue(Window::WindowStyleProperty(), WindowStyleE::Fixed);		sTitle = "WindowStyleE::Fixed";		break;
		case 8: w->setValue(Window::WindowStyleProperty(), WindowStyleE::SizeBox);		sTitle = "WindowStyleE::SizeBox";	break;
		case 9: w->setValue(Window::WindowStateProperty(), WindowStateE::Normal);		sTitle = "WindowStateE::Normal";	break;
		case 10: w->setValue(Window::TopmostProperty(), true);							sTitle = "TopmostProperty:true";	break;
		case 11: w->setValue(Window::TopmostProperty(), false);							sTitle = "TopmostProperty:false";	break;
		case 12: w->setValue(Window::LeftProperty(), 100);								sTitle = "LeftProperty:100";		break;
		case 13: w->setValue(Window::TopProperty(), 100);								sTitle = "TopProperty:100";			break;
		default: ((Timer *)(args.sender))->stop(); w->close();																break;
		}
		++i;
		w->setValue(Window::TitleProperty(), sTitle);
		printf("done:%s\n", sTitle.data());
	};
	//timer.start(2000);

	while (true)
	{
		Timer::driveInLoop();
		Window::pollEvents();
	}
}
