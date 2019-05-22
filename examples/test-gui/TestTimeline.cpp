#include "TestTimeline.h"

void TestTimeline::test()
{
	Timeline tl;
	tl.BeginTime = nb::core::TimeSpan::fromSeconds(1);
	tl.Duration = nb::core::TimeSpan::fromSeconds(1);
	tl.StateChangedEvent += std::bind(&TestTimeline::onStateChanged, this, std::placeholders::_1);
	tl.ProgressEvent += std::bind(&TestTimeline::onProgress, this, std::placeholders::_1);
	tl.CompleteEvent += std::bind(&TestTimeline::onCompleted, this, std::placeholders::_1);
	tl.begin();

	while (true)
	{
		Timer::drive();
	}
}

void TestTimeline::onStateChanged(const Timeline::StateChangedArgs & args)
{
	printf("onStateChanged:%d\n", args.state);
}

void TestTimeline::onProgress(const Timeline::ProgressArgs & args)
{
	printf("onProgress:%f\n", args.progress);
}

void TestTimeline::onCompleted(const Timeline::CompleteArgs & args)
{
	printf("onCompleted.\n");
}
