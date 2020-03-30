#include "newbrush/gui/Window.h"
#include "newbrush/gui/Application.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/gui/Ellipse.h"
#include "newbrush/gui/Line.h"
#include "newbrush/gui/Polygon.h"
#include "newbrush/gui/Polyline.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/RotateTransform.h"
#include "newbrush/media/ScaleTransform.h"
#include "newbrush/media/TranslateTransform.h"
#include "newbrush/media/TransformGroup.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("test Transform", "[Transform]")
{
	Application app;
	auto w = std::make_shared<Window>();
	w->setValue(Window::TitleProperty(), "Rectangle");
	auto rc = std::make_shared<Rectangle>();
	rc->setValue(Rectangle::MarginProperty(), Thickness(100));
	rc->setValue<std::shared_ptr<Brush>>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	rc->setValue(Rectangle::RadiusXProperty(), 0);
	rc->setValue(Rectangle::RadiusYProperty(), 0);
	rc->setValue<std::shared_ptr<Brush>>(Rectangle::StrokeProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc->setValue(Rectangle::StrokeThicknessProperty(), 5.0f);
	rc->setValue<std::vector<float>>(Rectangle::StrokeDashArrayProperty(), {});
	rc->setValue(Rectangle::StrokeDashOffsetProperty(), 0);
	w->setValue<std::shared_ptr<UIElement>>(Window::ContentProperty(), rc);


	auto offset = rc->worldOffset();

	//rotate
	auto rotateTransformPtr = std::make_shared<RotateTransform>();
	rotateTransformPtr->setValue<float>(RotateTransform::CenterXProperty(), offset.x() + 0.0f);
	rotateTransformPtr->setValue<float>(RotateTransform::CenterYProperty(), offset.y() + 0.0f);
	rotateTransformPtr->setValue<float>(RotateTransform::AngleProperty(), 30.0f);

	//scale
	auto scaleTransformPtr = std::make_shared<ScaleTransform>();
	scaleTransformPtr->setValue<float>(ScaleTransform::CenterXProperty(), offset.x());
	scaleTransformPtr->setValue<float>(ScaleTransform::CenterYProperty(), offset.y());
	scaleTransformPtr->setValue<float>(ScaleTransform::ScaleXProperty(), 0.5f);
	scaleTransformPtr->setValue<float>(ScaleTransform::ScaleYProperty(), 0.5f);

	//translate
	auto translateTransformPtr = std::make_shared<TranslateTransform>();
	translateTransformPtr->setValue<float>(TranslateTransform::XProperty(), 100.0f);
	translateTransformPtr->setValue<float>(TranslateTransform::YProperty(), 100.0f);

	//Collection
	auto transformCollectionPtr = std::make_shared<TransformCollection>();
	transformCollectionPtr->Add(scaleTransformPtr);
	transformCollectionPtr->Add(translateTransformPtr);
	transformCollectionPtr->Add(rotateTransformPtr);

	//transformGroup
	auto transformGroupPtr = std::make_shared<TransformGroup>();
	transformGroupPtr->setValue<std::shared_ptr<TransformCollection>>(TransformGroup::ChildrenProperty(), transformCollectionPtr);

	rc->setValue<std::shared_ptr<Transform>>(Rectangle::RenderTransformProperty(), transformGroupPtr);
	app.run(0, nullptr);
}
