#include "TestTextBlock.h"
#include <thread>

void TestTextBlock::test()
{
	m_window = std::make_shared<nb::gui::Window>();
	m_text = std::make_shared<TextBlock>();
	m_text->Text = "abcdefghijklmnopqrstuvwxyz德赛西威123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//	m_text->Text = "12345";
	m_text->VerticalAlignment = VerticalAlignmentE::Top;
	m_text->HorizontalAlignment = HorizontalAlignmentE::Right;
	m_text->Padding = 0.0f;
//	m_text->Width = 400;
	m_text->CharSpacing = 1.0f;
	m_text->TextWrapping = TextWrappingE::Wrap;
	m_window->Content = m_text;

	colorAni.From = m_text->Foreground();
	colorAni.To = Color(255, 0, 10);
	colorAni.Easing = std::make_shared<PowerEase>();
	colorAni.BeginTime = nb::core::TimeSpan::fromSeconds(1);
	colorAni.Duration = nb::core::TimeSpan::fromSeconds(2);
	colorAni.StateChangedEvent += std::bind(&TestTextBlock::onStateChanged, this, std::placeholders::_1);
	colorAni.ProgressEvent += std::bind(&TestTextBlock::onProgress, this, std::placeholders::_1);
	colorAni.CompleteEvent += std::bind(&TestTextBlock::onCompleted, this, std::placeholders::_1);
//	colorAni.TargetProperty = &m_text->Foreground;
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
	m_text->Text = "123";
	return;
	m_window->WindowState = WindowStateE::FullScreen;
	m_window->WindowStyle = WindowStyleE::None;
	m_window->Topmost = false;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	m_window->WindowStyle = WindowStyleE::Fixed;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	m_window->WindowStyle = WindowStyleE::None;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	m_window->WindowStyle = WindowStyleE::SizeBox;
	printf("onCompleted.\n");
}
