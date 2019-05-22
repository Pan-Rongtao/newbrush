#include "TestPropertyAnimation.h"

void TestPropertyAnimation::test()
{
	doubleAni.From = 100;
	doubleAni.To = 200;
	doubleAni.Easing = std::make_shared<ElasticEase>();
	doubleAni.BeginTime = nb::core::TimeSpan::fromSeconds(1);
	doubleAni.Duration = nb::core::TimeSpan::fromSeconds(1);
	doubleAni.StateChangedEvent += std::bind(&TestPropertyAnimation::onStateChanged, this, std::placeholders::_1);
	doubleAni.ProgressEvent += std::bind(&TestPropertyAnimation::onProgress, this, std::placeholders::_1);
	doubleAni.CompleteEvent += std::bind(&TestPropertyAnimation::onCompleted, this, std::placeholders::_1);
//	doubleAni.beginAinimation(&Width);

	piontAni.From = Point(100, 100);
	piontAni.To = Point(200, 500);
	piontAni.Easing = std::make_shared<LinearEase>();
	piontAni.BeginTime = nb::core::TimeSpan::fromSeconds(1);
	piontAni.Duration = nb::core::TimeSpan::fromSeconds(1);
	piontAni.StateChangedEvent += std::bind(&TestPropertyAnimation::onStateChanged, this, std::placeholders::_1);
	piontAni.ProgressEvent += std::bind(&TestPropertyAnimation::onProgress, this, std::placeholders::_1);
	piontAni.CompleteEvent += std::bind(&TestPropertyAnimation::onCompleted, this, std::placeholders::_1);
	piontAni.beginAinimation(&Position);
	
	colorAni.From = Color(220, 100, 40);
	colorAni.To = Color(80, 200, 10);
	colorAni.BeginTime = nb::core::TimeSpan::fromSeconds(0);
	colorAni.Duration = nb::core::TimeSpan::fromSeconds(1);
	colorAni.StateChangedEvent += std::bind(&TestPropertyAnimation::onStateChanged, this, std::placeholders::_1);
	colorAni.ProgressEvent += std::bind(&TestPropertyAnimation::onProgress, this, std::placeholders::_1);
	colorAni.CompleteEvent += std::bind(&TestPropertyAnimation::onCompleted, this, std::placeholders::_1);
//	colorAni.beginAinimation(&Background);
	
	while (true)
	{
		Timer::drive();
	}
}

void TestPropertyAnimation::onStateChanged(const Timeline::StateChangedArgs & args)
{
	printf("onStateChanged:%d\n", args.state);
}

void TestPropertyAnimation::onProgress(const Timeline::ProgressArgs & args)
{
//	printf("onProgress:%f, width=%f\n", args.progress, Width());
	printf("onProgress:%f, point=(%f, %f)\n", args.progress, Position().x(), Position().y());
//	printf("onProgress:%f, color=(%d, %d, %d)\n", args.progress, Background().red(), Background().green(), Background().blue());
}

void TestPropertyAnimation::onCompleted(const Timeline::CompleteArgs & args)
{
	printf("onCompleted.\n");
}
