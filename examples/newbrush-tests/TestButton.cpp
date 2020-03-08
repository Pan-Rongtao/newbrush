#include "newbrush/gui/Image.h"
#include "newbrush/gui/Shape.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/gui/Button.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Application.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test nb::Button", "[Button]")
{
	Application app;
	std::shared_ptr<Window> w = std::make_shared<Window>();
	auto btn = std::make_shared<Button>();
	w->setValue(Window::ContentProperty(), std::dynamic_pointer_cast<UIElement>(btn));

	auto rc = std::make_shared<Rectangle>();
	rc->setValue<BrushPtr>(Rectangle::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	btn->setValue<UIElementPtr>(Button::ContentProperty(), rc);
	btn->setValue(Button::MarginProperty(), Thickness(50));

	app.run(0, nullptr);
/*	m_btn = std::make_shared<Button>();
	m_btn->MouseLeftButtonDown += std::bind(&TestButton::onBtnMouseLeftButtonDown, this, std::placeholders::_1);
	m_btn->MouseLeftButtonUp += std::bind(&TestButton::onBtnMouseLeftButtonUp, this, std::placeholders::_1);
	m_btn->Click += std::bind(&TestButton::onBtnClick, this, std::placeholders::_1);
	auto rc = std::make_shared<Rectangle>();
	rc->set(Rectangle::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	//auto image = std::make_shared<Image>();
	//image->Source = std::make_shared<ImageSource>("e:/Pics/5.jpg");
	//m_btn->Content = image;
	m_btn->set(Button::ContentProperty(), rc);
	m_btn->set(Button::MarginProperty(), Thickness(10));
/*
	auto stateMachine = std::make_shared<VisualStateMachine>();
	m_btn->StateMachine = stateMachine;
	auto group = std::make_shared<VisualStateGroup>("BtnStateGroup");
	stateMachine->addGroup(group);
	
	auto state_normal = std::make_shared<VisualState>("NormalState");
	auto normalAni = std::make_shared<PropertyAnimation<float>>(0.0f, 200.0f, TimeSpan::zero(), &m_btn->Width);
	state_normal->Storyboard = std::make_shared<Storyboard>(TimeSpan::zero(), std::vector<std::shared_ptr<Timeline>>{normalAni});

	auto state_press = std::make_shared<VisualState>("PressState");
	auto pressAni = std::make_shared<PropertyAnimation<float>>(0.0f, 100.0f, TimeSpan::zero(), &m_btn->Width);
	state_press->Storyboard = std::make_shared<Storyboard>(TimeSpan::zero(), std::vector<std::shared_ptr<Timeline>>{pressAni});

	auto state_mouseover = std::make_shared<VisualState>("MouseOverState");
	auto mouseoverAni = std::make_shared<PropertyAnimation<float>>();
	state_mouseover->Storyboard = std::make_shared<Storyboard>(TimeSpan::zero(), std::vector<std::shared_ptr<Timeline>>{mouseoverAni});
	
	group->States().push_back(state_normal);
	group->States().push_back(state_press);
	group->States().push_back(state_mouseover);
	
	m_window = std::make_shared<Window>();
	m_window->Content = m_btn;*/
//	m_btn->Width = 100;
}
