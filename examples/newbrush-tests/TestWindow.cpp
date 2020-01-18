#include "gui/Image.h"
#include "media/ImageSource.h"
#include "media/Brush.h"
#include "gui/Shape.h"
#include "gui/Rectangle.h"
#include "gui/Window.h"
#include "core/Timer.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

TEST_CASE("Test nb::Window", "[Window]")
{
	auto w = std::make_shared<Window>();
	w->set(Window::TitleProperty(), std::string("Newbrush窗口测试"));
	std::shared_ptr<UIElement> rc0 = std::make_shared<Rectangle>();
	rc0->set(UIElement::WidthProperty(), 100);
	rc0->set(UIElement::HeightProperty(), 100);
	rc0->set(UIElement::HorizontalAlignmentProperty(), HorizontalAlignmentE::Stretch);
	w->set(Window::ContentProperty(), rc0);
//	this->Topmost = true;

	/*
	doubleAni.From = this->Top();
	doubleAni.To = this->Top() + 100;
	doubleAni.Easing = std::make_shared<PowerEase>();
	doubleAni.BeginTime = TimeSpan::fromSeconds(1);
	doubleAni.Duration = TimeSpan::fromMilliseconds(200);
	doubleAni.StateChangedEvent += std::bind(&TestWindow::onStateChanged, this, std::placeholders::_1);
	doubleAni.ProgressEvent += std::bind(&TestWindow::onProgress, this, std::placeholders::_1);
	doubleAni.CompleteEvent += std::bind(&TestWindow::onCompleted, this, std::placeholders::_1);
//	doubleAni.TargetProperty = &this->Top;
	doubleAni.begin();
	*/
	Timer timer;
	timer.Tick += [&w](const EventArgs &args) {	
		static int i = 0;
		if (i == 0)
		{
			w->hide();
		}
		else if (i == 1)
		{
			w->show();
		}
		else if (i == 2)
		{
			//	w->hide();
		}
		else if (i == 3)
		{
			w->active();
		}
		else
		{
			((Timer *)(args.sender))->stop();
		}
		++i;
	};
	timer.start(1500);

	while (true)
	{
		Window::waitEvent();
		Timer::driveInLoop();
	}
}
/*
void TestWindow::onStateChanged(const Timeline::StateChangedArgs & args)
{
	printf("onStateChanged:%d\n", args.state);
}

void TestWindow::onProgress(const Timeline::ProgressArgs & args)
{
	//	printf("onProgress:%f, width=%f\n", args.progress, Width());
	//printf("onProgress:%f, point=(%f, %f)\n", args.progress, Position().x(), Position().y());
	//	printf("onProgress:%f, color=(%d, %d, %d)\n", args.progress, Background().red(), Background().green(), Background().blue());
}

void TestWindow::onCompleted(const Timeline::CompleteArgs & args)
{
	printf("onCompleted.\n");
}
*/
