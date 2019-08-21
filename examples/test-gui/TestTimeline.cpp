#include "TestTimeline.h"

void TestTimeline::test()
{
	m_tl.BeginTime = TimeSpan::fromSeconds(1);
	m_tl.Duration = TimeSpan::fromSeconds(1);
	m_tl.StateChangedEvent += std::bind(&TestTimeline::onStateChanged, this, std::placeholders::_1);
	m_tl.ProgressEvent += std::bind(&TestTimeline::onProgress, this, std::placeholders::_1);
	m_tl.CompleteEvent += std::bind(&TestTimeline::onCompleted, this, std::placeholders::_1);
	m_tl.begin();

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
