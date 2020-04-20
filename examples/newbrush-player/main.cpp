#include "newbrush/gui/Application.h"
#include "newbrush/gui/Window.h"
#include "newbrush/core/Log.h"
#include "StudioCommunicationHelper.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/media/SolidColorBrush.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Parser.h"
#include "newbrush/media/EffectBrush.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/gles/RenderObject.h"

using namespace nb;

int main(int argc, char **argv)
{
	Application app;

	StudioCommunicationHelper helper;
	helper.startWorking();

	auto w = std::make_shared<Window>();
	w->setValue(Window::TitleProperty(), "nbplayer");
	w->setValue(Window::NameProperty(), "Window");
	//auto rc = std::make_shared<nb::Rectangle>();
	//rc->setValue<Thickness>(Rectangle::MarginProperty(), Thickness(20));
	//rc->setValue<BrushPtr>(Rectangle::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	//w->setValue(Window::WindowStyleProperty(), WindowStyleE::None);
	//w->setValue<std::shared_ptr<UIElement>>(Window::ContentProperty(), rc);
	/*
	rc->setValue<BrushPtr>(Rectangle::FillProperty(), std::make_shared<EffectBrush>());
	//rc->renderObject()->setProgram(program);
	rc->renderObject()->setProgram(Programs::model());
	auto sz = rc->getValue<Size>(Shape::ActualSizeProperty());
	rc->renderObject()->loadFromFile("../model/car.fbx", "../model");

	glm::mat4 model = glm::mat4(1.0f);
	auto strength = 20.0f;
	model = glm::translate(model, {400, 300, 0});
	model = glm::scale(model, glm::vec3(strength, strength, strength));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	rc->renderObject()->model()->matrix = model;
	*/

	return app.run(argc, argv);

}