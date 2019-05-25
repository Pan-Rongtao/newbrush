#include "TestStoryboard.h"
#include "gui/AnimationTimeline.h"
#include "gui/PropertyAnimation.h"

void TestStoryboard::test()
{
	Property_rw<double> Width;
	auto doubleAni = std::make_shared<PropertyAnimation<double>>();
	doubleAni->From = 200;
	doubleAni->To = -122;
	doubleAni->Duration = TimeSpan(0, 0, 2);
//	doubleAni->ProgressEvent += [&](const Timeline::ProgressArgs &args)
//	{
//		printf("onProgress:%f, width=%f\n", args.progress, Width());
//	};
	doubleAni->TargetProperty = &Width;
	m_storyboard.Children().push_back(doubleAni);
	m_storyboard.Duration = TimeSpan(0, 0, 2);
	m_storyboard.begin();

	m_storyboard.ProgressEvent += [&](const Timeline::ProgressArgs &args) 
	{
		printf("onProgress1:%f, width=%f\n", args.progress, Width());
	};
	
	while (true)
	{
		Timer::drive();
	}
}