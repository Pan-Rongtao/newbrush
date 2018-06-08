#include "TestWindow.h"
#include "gles/Application.h"
#include "gui/Image.h"
#include "gui/ImageSource.h"
#include "gui/SolidColorBrush.h"
#include "gui/ImageBrush.h"
#include "gui/Rectangle.h"

using nb::Gui::Image;
using nb::Gui::Rectangle;
using nb::Media::ImageSource;
using nb::Media::Brush;
using nb::Media::ImageBrush;
using nb::Media::SolidColorBrush;

TestWindow::TestWindow()
{
	m_RootPage = new TestPageBase();
	this->SetPage(m_RootPage);

	RectanglePtr rc = new Rectangle();
	m_RootPage->GetRootGrid()->Children()->Add(rc);
	rc->Fill = new SolidColorBrush(nb::System::Color(255, 0, 0, 255));

	ImagePtr img = new Image(new ImageSource("f:/pics/3.jpg"));
	m_RootPage->GetRootGrid()->Children()->Add(img);
	img->Stretch() = nb::Media::Uniform;

}

TestWindow::~TestWindow()
{

}

void TestWindow::Test()
{
//	nb::gl::Gles::Application app;
//	nb::Gui::Window w;
//	app.Run();

}