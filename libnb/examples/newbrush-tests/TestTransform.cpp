#include "newbrush/gui/Window.h"
#include "newbrush/gui/Application.h"
#include "newbrush/gui/shapes/Rectangle.h"
#include "newbrush/gui/shapes/Ellipse.h"
#include "newbrush/gui/shapes/Line.h"
#include "newbrush/gui/shapes/Polygon.h"
#include "newbrush/gui/shapes/Polyline.h"
#include "newbrush/core/media/SolidColorBrush.h"
#include "newbrush/core/media/GradientBrush.h"
#include "newbrush/core/media/ImageBrush.h"
#include "newbrush/core/media/RotateTransform.h"
#include "newbrush/core/media/ScaleTransform.h"
#include "newbrush/core/media/TranslateTransform.h"
#include "newbrush/core/media/TransformGroup.h"
#include "catch2/catch.hpp"
#include "newbrush/core/base/Thickness.h"

using namespace nb;

TEST_CASE("test Transform", "[Transform]")
{
	Application app;
	auto w = std::make_shared<Window>();
	w->setValue(Window::TitleProperty(), "Rectangle");
	
	auto rc = std::make_shared<Rectangle>();
	//设置元素的外边距
	rc->setValue(Rectangle::MarginProperty(), Thickness(200));
	rc->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	rc->setValue(Rectangle::RadiusXProperty(), 0);
	rc->setValue(Rectangle::RadiusYProperty(), 0);
	rc->setValue<BrushPtr>(Rectangle::StrokeProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc->setValue(Rectangle::StrokeThicknessProperty(), 5.0f);
	rc->setValue<std::vector<float>>(Rectangle::StrokeDashArrayProperty(), {});
	rc->setValue(Rectangle::StrokeDashOffsetProperty(), 0);
	w->setValue<UIElementPtr>(Window::ContentProperty(), rc);

	auto offset = rc->worldOffset();
	//scale
	auto scaleTransformPtr = std::make_shared<ScaleTransform>();
	scaleTransformPtr->setValue<float>(ScaleTransform::CenterXProperty(), offset.x());
	scaleTransformPtr->setValue<float>(ScaleTransform::CenterYProperty(), offset.y());
	scaleTransformPtr->setValue<float>(ScaleTransform::ScaleXProperty(), 0.7f);
	scaleTransformPtr->setValue<float>(ScaleTransform::ScaleYProperty(), 0.7f);

	//translate
	auto translateTransformPtr = std::make_shared<TranslateTransform>();
	translateTransformPtr->setValue<float>(TranslateTransform::XProperty(), 100.0f);
	translateTransformPtr->setValue<float>(TranslateTransform::YProperty(), 100.0f);

	//rotate
	auto rotateTransformPtr = std::make_shared<RotateTransform>();
	rotateTransformPtr->setValue<float>(RotateTransform::CenterXProperty(), offset.x() + 0.0f);
	rotateTransformPtr->setValue<float>(RotateTransform::CenterYProperty(), offset.y() + 0.0f);
	rotateTransformPtr->setValue<float>(RotateTransform::AngleProperty(), 15.0f);

	//Collection
	auto transformCollectionPtr = std::make_shared<TransformCollection>();
	transformCollectionPtr->push_back(scaleTransformPtr);
	transformCollectionPtr->push_back(translateTransformPtr);
	transformCollectionPtr->push_back(rotateTransformPtr);

	//transformGroup
	auto transformGroupPtr = std::make_shared<TransformGroup>();
	transformGroupPtr->setValue<TransformCollectionPtr>(TransformGroup::ChildrenProperty(), transformCollectionPtr);

	rc->setValue<TransformPtr>(Rectangle::RenderTransformProperty(), transformGroupPtr);
	app.run(0, nullptr);
}
