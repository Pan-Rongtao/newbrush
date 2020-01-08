#include "TestBrush.h"
#include "media/SolidColorBrush.h"
#include "media/GradientBrush.h"
#include "media/ImageBrush.h"

void TestBrush::test()
{
	m_window = std::make_shared<nb::gui::Window>();
	auto rc = std::make_shared<Rectangle>();
	auto linearBrush = std::make_shared<LinearGradientBrush>();
	auto stops = std::vector<GradientStop>();
	auto gs0 = std::make_shared<GradientStop>(Color(255, 255, 255, 255), 0.0f);
	auto gs1 = std::make_shared<GradientStop>(Color(255, 255, 0, 0), 0.33f);
	auto gs2 = std::make_shared<GradientStop>(Color(255, 0, 0, 255), 0.66f);
	auto gs3 = std::make_shared<GradientStop>(Color(255, 0, 125, 0), 1.0f);
	auto gradientStops = std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{ gs0, gs1, gs2, gs3 });
	linearBrush->set(LinearGradientBrush::GradientStopsProperty(), gradientStops);
//	rc->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	rc->set(Rectangle::FillProperty(), std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/Pics/3.jpg")));
	rc->set(Rectangle::RadiusXProperty(), 50);
	rc->set(Rectangle::RadiusYProperty(), 50);
	rc->set(Rectangle::MarginProperty(), Thickness(50));
	rc->set(Rectangle::StrokeProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	rc->set(Rectangle::StrokeThicknessProperty(), 30);
	rc->set(Rectangle::StrokeDashArrayProperty(), std::vector<float>{3.0f, 3.0f});
	rc->set(Rectangle::StrokeDashOffsetProperty(), 2);
	rc->set(Rectangle::StrokeThicknessProperty(), 30);
	m_window->set(Window::ContentProperty(), rc);
	
//	rc->Fill = linearBrush;
//	rc->Stroke = linearBrush;
//	rc->Stroke = std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/Pics/5.jpg"));
}
