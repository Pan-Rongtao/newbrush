#include "TestWindow.h"
#include "gles/Application.h"
#include "gui/Image.h"
#include "media/ImageSource.h"
#include "media/Brush.h"
#include "gui/Shape.h"
#include "gui/Rectangle.h"

using namespace nb::gui;
void TestWindow::test()
{
	Title = "Newbrush´°¿Ú²âÊÔ";
	auto rc0 = std::make_shared<Rectangle>();
	rc0->Width = 100;
	rc0->Height = 100;
	rc0->HorizontalAlignment = HorizontalAlignmentE::Stretch;
	this->Content = rc0;
//	this->Topmost = true;


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

	m_timer.TickEvent.addHandler(std::bind(&TestWindow::onTick, this, std::placeholders::_1));
	m_timer.start(1500);
}

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

void TestWindow::onTick(const Timer::TickArgs & args)
{
	static int i = 0;
	if (i == 0)
	{
		this->hide();
	}
	else if(i == 1)
	{
		this->show();
	}
	else if (i == 2)
	{
	//	this->hide();
	}
	else if (i == 3)
	{
		this->active();
	}
	else
	{
		m_timer.stop();
	}
	++i;
}
