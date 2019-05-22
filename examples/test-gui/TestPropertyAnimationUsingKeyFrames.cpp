#include "TestPropertyAnimationUsingKeyFrames.h"

void TestPropertyAnimationUsingKeyFrames::test()
{
	doubleAni.BeginTime = nb::core::TimeSpan::fromSeconds(0);
	doubleAni.Duration = nb::core::TimeSpan::fromSeconds(5);
	doubleAni.StateChangedEvent += std::bind(&TestPropertyAnimationUsingKeyFrames::onStateChanged, this, std::placeholders::_1);
	doubleAni.ProgressEvent += std::bind(&TestPropertyAnimationUsingKeyFrames::onProgress, this, std::placeholders::_1);
	doubleAni.CompleteEvent += std::bind(&TestPropertyAnimationUsingKeyFrames::onCompleted, this, std::placeholders::_1);
	doubleAni.KeyFrames().insert(KeyFrame<double>(20, TimeSpan(0, 0, 1)));
	doubleAni.KeyFrames().insert(KeyFrame<double>(80, TimeSpan(0, 0, 2)));
	doubleAni.KeyFrames().insert(KeyFrame<double>(-20, TimeSpan(0, 0, 5)));
	doubleAni.TargetProperty = &Width;
	doubleAni.begin();

	while (true)
	{
		Timer::drive();
	}
}

void TestPropertyAnimationUsingKeyFrames::onStateChanged(const Timeline::StateChangedArgs & args)
{
	printf("onStateChanged:%d\n", args.state);
}

void TestPropertyAnimationUsingKeyFrames::onProgress(const Timeline::ProgressArgs & args)
{
		printf("onProgress:%f, width=%f\n", args.progress, Width());
	//printf("onProgress:%f, point=(%f, %f)\n", args.progress, Position().x(), Position().y());
	//	printf("onProgress:%f, color=(%d, %d, %d)\n", args.progress, Background().red(), Background().green(), Background().blue());
}

void TestPropertyAnimationUsingKeyFrames::onCompleted(const Timeline::CompleteArgs & args)
{
	printf("onCompleted.\n");
}
