#include "TestButton.h"
#include "gui/Image.h"
#include "gui/Shape.h"
#include "media/SolidColorBrush.h"
#include "media/GradientBrush.h"
#include "media/ImageBrush.h"
#include "gui/Rectangle.h"
#include "media/PropertyAnimation.h"

void TestButton::test()
{
	m_btn = std::make_shared<Button>();
	m_btn->MouseLeftButtonDown += std::bind(&TestButton::onBtnMouseLeftButtonDown, this, std::placeholders::_1);
	m_btn->MouseLeftButtonUp += std::bind(&TestButton::onBtnMouseLeftButtonUp, this, std::placeholders::_1);
	m_btn->Click += std::bind(&TestButton::onBtnClick, this, std::placeholders::_1);
	auto rc = std::make_shared<Rectangle>();
	rc->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	//auto image = std::make_shared<Image>();
	//image->Source = std::make_shared<ImageSource>("e:/Pics/5.jpg");
	//m_btn->Content = image;
	m_btn->Content = rc;
	m_btn->Margin = Thickness(10);

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
	auto mouseoverAni = std::make_shared<PropertyAnimation<float>>(/*0.0f, 100.0f, TimeSpan::zero(), &m_btn->Width*/);
	state_mouseover->Storyboard = std::make_shared<Storyboard>(TimeSpan::zero(), std::vector<std::shared_ptr<Timeline>>{mouseoverAni});
	
	group->States().push_back(state_normal);
	group->States().push_back(state_press);
	group->States().push_back(state_mouseover);
	
	m_window = std::make_shared<nb::gui::Window>();
	m_window->Content = m_btn;
//	m_btn->Width = 100;
}

void TestButton::onBtnMouseLeftButtonDown(const MouseButtonEventArgs & args)
{
	printf("onBtnMouseLeftButtonDown\n");
	m_btn->StateMachine()->gotoState("BtnStateGroup", "PressState", false);
}

void TestButton::onBtnMouseLeftButtonUp(const MouseButtonEventArgs & args)
{
	printf("onBtnMouseLeftButtonUp\n");
	m_btn->StateMachine()->gotoState("BtnStateGroup", "NormalState", false);
}

void TestButton::onBtnClick(const Button::ClickArgs & args)
{
	//m_btn->StateMachine()->gotoState("BtnStateGroup", "PressState", false);
	printf("onBtnClick\n");
	//auto rcBtn = Rect( m_btn->worldOffset(), m_btn->ActualSize);
	//auto rcRect = Rect(m_btn->Content()->worldOffset(), m_btn->Content()->ActualSize);
	//printf("rcBtn{%d, %d, %d, %d}\n", (int)rcBtn.left(), (int)rcBtn.top(), (int)rcBtn.width(), (int)rcBtn.height());
	//printf("rcRect{%d, %d, %d, %d\n}", (int)rcRect.left(), (int)rcRect.top(), (int)rcRect.width(), (int)rcRect.height());
}
