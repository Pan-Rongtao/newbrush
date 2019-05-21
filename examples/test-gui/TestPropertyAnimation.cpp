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

	colorAni.From = Colors::red();
	colorAni.To = Colors::blue();
	colorAni.BeginTime = nb::core::TimeSpan::fromSeconds(0);
	colorAni.Duration = nb::core::TimeSpan::fromSeconds(1);
	colorAni.StateChangedEvent += std::bind(&TestPropertyAnimation::onStateChanged, this, std::placeholders::_1);
	colorAni.ProgressEvent += std::bind(&TestPropertyAnimation::onProgress, this, std::placeholders::_1);
	colorAni.CompleteEvent += std::bind(&TestPropertyAnimation::onCompleted, this, std::placeholders::_1);
	colorAni.beginAinimation(&Background);

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
	printf("onProgress:%f, color=(%d, %d, %d)\n", args.progress, Background().red(), Background().green(), Background().blue());
}

void TestPropertyAnimation::onCompleted(const Timeline::CompleteArgs & args)
{
	printf("onCompleted.\n");
}
