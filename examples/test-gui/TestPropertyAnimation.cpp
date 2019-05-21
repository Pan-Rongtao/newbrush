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
	doubleAni.beginAinimation(&Width);

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
	printf("onProgress:%f, width=%f\n", args.progress, Width());
}

void TestPropertyAnimation::onCompleted(const Timeline::CompleteArgs & args)
{
	printf("onCompleted.\n");
}
