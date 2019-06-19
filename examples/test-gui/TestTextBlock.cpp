#include "TestTextBlock.h"

void TestTextBlock::test()
{
	auto tb = std::make_shared<TextBlock>();
	tb->Text = "abcdefghijklmnopqrstuvwxyz德赛西威123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//	tb->Text = "12345";
	tb->VerticalAlignment = VerticalAlignmentE::Center;
//	tb->HorizontalAlignment = HorizontalAlignmentE::Right;
	tb->Padding = 0.0f;
//	tb->Width = 400;
	tb->CharSpacing = 1.0f;
	tb->TextWrapping = TextWrappingE::Wrap;
	m_window.Content = tb;
}
