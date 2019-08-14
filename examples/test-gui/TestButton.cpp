#include "TestButton.h"
#include "gui/Image.h"
#include "gui/Rectangle.h"
#include "gui/PropertyAnimation.h"

Storyboard	m_storyboard;
std::shared_ptr<VisualState> state_normal;
void TestButton::test()
{ 
	m_btn = std::make_shared<Button>();
	m_btn->MouseLeftButtonDown += std::bind(&TestButton::onBtnMouseLeftButtonDown, this, std::placeholders::_1);
	m_btn->MouseLeftButtonUp += std::bind(&TestButton::onBtnMouseLeftButtonUp, this, std::placeholders::_1);
	m_btn->Click += std::bind(&TestButton::onBtnClick, this, std::placeholders::_1);
	auto rc = std::make_shared<Rectangle>();
	rc->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	//rc->Width = 100;
	//auto image = std::make_shared<Image>();
	//image->Source = std::make_shared<ImageSource>("e:/Pics/5.jpg");
	//m_btn->Content = image;
	m_btn->Content = rc;
	m_btn->Margin = Thickness(10);
/*	auto doubleAni = std::make_shared<PropertyAnimation<float>>(100);
	doubleAni->Duration = TimeSpan::fromSeconds(1);
	doubleAni->TargetProperty = &m_btn->Width;
	m_storyboard.Children().push_back(doubleAni);
	m_storyboard.Duration = TimeSpan::fromSeconds(1);
	m_storyboard.begin();
	m_storyboard.ProgressEvent += [&](const Timeline::ProgressArgs &args)
	{
		printf("onProgress1:%f, width=%f\n", args.progress, m_btn->Width());
	};*/
	/*
	auto stateMachine = std::make_shared<VisualStateMachine>();
	m_btn->StateMachine = stateMachine;
	auto group = std::make_shared<VisualStateGroup>();
	group->Name = "BtnStateGroup";
	stateMachine->addGroup(group);
	*/
	state_normal = std::make_shared<VisualState>();
	state_normal->Name = "NormalState";

	auto doubleAni = std::make_shared<PropertyAnimation<float>>(100.0f); 
	doubleAni->Duration = TimeSpan::fromSeconds(1); 
	doubleAni->TargetProperty = &m_btn->Width;
	state_normal->Storyboard = std::make_shared<Storyboard>();
	state_normal->Storyboard()->Duration = TimeSpan::fromMilliseconds(1000);
	state_normal->Storyboard()->Children().push_back(doubleAni);
	//state_normal->Storyboard()->begin();
	state_normal->Storyboard()->ProgressEvent += [&](const Timeline::ProgressArgs &args)
	{
		printf("onProgress1:%f, width=%f\n", args.progress, m_btn->Width());
	};
	/*
	auto state_press = std::make_shared<VisualState>();
	state_press->Name = "PressState";
	state_press->Storyboard = std::make_shared<Storyboard>();
	state_press->Storyboard()->Duration = TimeSpan::fromSeconds(2);
	auto ani1 = std::make_shared<PropertyAnimation<float>>(100.0f);
	ani1->TargetProperty = &m_btn->Width;
	//auto c = std::dynamic_pointer_cast<SolidColorBrush>(rc->Fill())->Color;
	state_press->Storyboard()->Children().push_back(ani1);
	state_press->Storyboard()->StateChangedEvent += [&](const Timeline::StateChangedArgs &args)
	{
		printf("state=%d\n", args.state);
	};
	state_press->Storyboard()->ProgressEvent += [&](const Timeline::ProgressArgs &args)
	{
	//	auto c = ani1->TargetProperty->operator()();
	//	auto c = (std::dynamic_pointer_cast<SolidColorBrush>(rc->Fill())->Color);
		printf("onProgress:%f/\n", args.progress);
	};
	ani1->begin();

	auto state_mouseover = std::make_shared<VisualState>();
	state_mouseover->Name = "MouseOverState";
	state_mouseover->Storyboard = std::make_shared<Storyboard>();
	state_mouseover->Storyboard()->Duration = TimeSpan::fromMilliseconds(0);
	auto ani2 = std::make_shared<PropertyAnimation<float>>(200.0f);
	ani2->TargetProperty = &m_btn->Width;// &(std::dynamic_pointer_cast<SolidColorBrush>(rc->Fill())->Color);
	state_mouseover->Storyboard()->Children().push_back(ani2);

	group->States().push_back(state_normal);
	group->States().push_back(state_press);
	group->States().push_back(state_mouseover);
	*/
	m_window = std::make_shared<nb::gui::Window>();
	m_window->Content = m_btn;
//	m_btn->Width = 100;
}

void TestButton::onBtnMouseLeftButtonDown(const Button::MouseLeftButtonDownArgs & args)
{
	printf("onBtnMouseLeftButtonDown\n");
	//m_btn->StateMachine()->gotoState("BtnStateGroup", "PressState", false);
	m_btn->Width = 100;
}

void TestButton::onBtnMouseLeftButtonUp(const Button::MouseLeftButtonUpArgs & args)
{
	printf("onBtnMouseLeftButtonUp\n");
	m_btn->Width = 300;
	//m_btn->StateMachine()->gotoState("BtnStateGroup", "NormalState", false);
}

void TestButton::onBtnClick(const Button::ClickEventArgs & args)
{
	//m_btn->StateMachine()->gotoState("BtnStateGroup", "PressState", false);
	printf("onBtnClick\n");
	//auto rcBtn = Rect( m_btn->worldOffset(), m_btn->ActualSize);
	//auto rcRect = Rect(m_btn->Content()->worldOffset(), m_btn->Content()->ActualSize);
	//printf("rcBtn{%d, %d, %d, %d}\n", (int)rcBtn.left(), (int)rcBtn.top(), (int)rcBtn.width(), (int)rcBtn.height());
	//printf("rcRect{%d, %d, %d, %d\n}", (int)rcRect.left(), (int)rcRect.top(), (int)rcRect.width(), (int)rcRect.height());
}
