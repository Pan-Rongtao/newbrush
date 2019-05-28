#include "TestWindow.h"
#include "gles/Application.h"
#include "gui/Image.h"
#include "gui/ImageSource.h"
#include "gui/Brush.h"
#include "gui/Rectangle.h"

using namespace nb::gui;
void TestWindow::test()
{
	auto rc0 = std::make_shared<Rectangle>();
	rc0->Width = 100;
	rc0->Height = 100;
	rc0->HorizontalAlignment = HorizontalAlignmentE::Left;
	this->Content = rc0;
}