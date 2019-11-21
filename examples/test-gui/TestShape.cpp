#include "TestShape.h"
#include "gui/Shape.h"
#include "gui/Ellipse.h"

void TestShape::test()
{
	m_window = std::make_shared<nb::gui::Window>();
#if 1
	auto image = std::make_shared<Ellipse>();
	image->Margin = Thickness(20);
	image->Stretch = StretchE::Uniform;
	m_window->Content = image;
#endif

}
