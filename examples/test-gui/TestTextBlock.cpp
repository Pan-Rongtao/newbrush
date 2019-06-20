#include "TestTextBlock.h"

void TestTextBlock::test()
{
	auto tb = std::make_shared<TextBlock>();
	tb->Text = "abcdefghijklmnopqrstuvwxyz德赛西威123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//	tb->Text = "12345";
	tb->VerticalAlignment = VerticalAlignmentE::Top;
	tb->HorizontalAlignment = HorizontalAlignmentE::Right;
	tb->Padding = 0.0f;
//	tb->Width = 400;
	tb->CharSpacing = 1.0f;
	tb->TextWrapping = TextWrappingE::NoWrap;
	m_window.Content = tb;


	colorAni.From = tb->Foreground;
	colorAni.To = Color(255, 0, 10);
	colorAni.Easing = std::make_shared<PowerEase>();
	colorAni.BeginTime = nb::core::TimeSpan::fromSeconds(1);
	colorAni.Duration = nb::core::TimeSpan::fromSeconds(2);
	colorAni.StateChangedEvent += std::bind(&TestTextBlock::onStateChanged, this, std::placeholders::_1);
	colorAni.ProgressEvent += std::bind(&TestTextBlock::onProgress, this, std::placeholders::_1);
	colorAni.CompleteEvent += std::bind(&TestTextBlock::onCompleted, this, std::placeholders::_1);
	colorAni.TargetProperty = &tb->Foreground;
	colorAni.begin();
}

void TestTextBlock::onStateChanged(const Timeline::StateChangedArgs & args)
{
	printf("onStateChanged:%d\n", args.state);
}

void TestTextBlock::onProgress(const Timeline::ProgressArgs & args)
{
	//	printf("onProgress:%f, width=%f\n", args.progress, Width());
	//printf("onProgress:%f, point=(%f, %f)\n", args.progress, Position().x(), Position().y());
	//	printf("onProgress:%f, color=(%d, %d, %d)\n", args.progress, Background().red(), Background().green(), Background().blue());
}

void TestTextBlock::onCompleted(const Timeline::CompleteArgs & args)
{
	printf("onCompleted.\n");
}
