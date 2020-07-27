#include <thread>
#include "newbrush/gui/Window.h"
#include "newbrush/gui/controls/TextBlock.h"
#include "catch2/catch.hpp"
#include "newbrush/core/media/Media.h"

using namespace nb;

TEST_CASE("Test nb::TextBlock", "[TextBlock]")
{
	auto m_window = std::make_shared<Window>();
	auto m_text = std::make_shared<TextBlock>();
	m_text->setValue(TextBlock::TextProperty(), std::string("abcdefghijklmnopqrstuvwxyz德赛西威123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
//	m_text->Text = "12345";
	m_text->setValue(TextBlock::VerticalAlignmentProperty(), VerticalAlignmentE::Top);
	m_text->setValue(TextBlock::HorizontalAlignmentProperty(), HorizontalAlignmentE::Right);
	m_text->setValue(TextBlock::PaddingProperty(), 0.0f);
//	m_text->Width = 400;
	m_text->setValue(TextBlock::CharSpacingProperty(), 1.0f);
	m_text->setValue(TextBlock::TextWrappingProperty(), TextWrappingE::Wrap);
	m_window->setValue(Window::ContentProperty(), m_text);

//	colorAni.From = m_text->Foreground();
//	colorAni.To = Color(255, 0, 10);
//	colorAni.Easing = std::make_shared<PowerEase>();
//	colorAni.BeginTime = TimeSpan::fromSeconds(1);
//	colorAni.Duration = TimeSpan::fromSeconds(2);
//	colorAni.StateChangedEvent += std::bind(&TestTextBlock::onStateChanged, this, std::placeholders::_1);
//	colorAni.ProgressEvent += std::bind(&TestTextBlock::onProgress, this, std::placeholders::_1);
//	colorAni.CompleteEvent += std::bind(&TestTextBlock::onCompleted, this, std::placeholders::_1);
////	colorAni.TargetProperty = &m_text->Foreground;
//	colorAni.begin();
}
/*
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
}
*/