#include "TestTextBlock.h"

void TestTextBlock::test()
{
	auto tb = std::make_shared<TextBlock>();
	tb->Text = "abcdefghijklmnopqrstuvwxyz德赛西威123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//	tb->Padding = 100.0f;
	m_window.Content = tb;
}
