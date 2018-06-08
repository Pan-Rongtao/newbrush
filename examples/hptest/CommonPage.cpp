#include "CommonPage.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/Rectangle.h"
#include "../../../Include/Gui/SolidColorBrush.h"
#include "../../../Include/Gui/VisualStateGroup.h"
#include "../../../Include/Gui/ObjectAnimation.h"
#include "../../../Include/Gui/VisualState.h"
#include "../../../Include/Gui/VisualStateStoryboard.h"

using namespace nb::Gui;
using namespace nb::Media;
using namespace nb::System;
using namespace nb::Core;

CommonPage::CommonPage(void)
{
	nb::Gui::GridPtr grid = new nb::Gui::Grid();
	SetRootPanel(grid);

//	grid->RowDefCollection = new RowDefinitionCollection();
	RowDefinitionCollection *rowColl =  grid->RowDefCollection;//->RowDefCollection()->Add(new RowDefinition());

	RowDefinition *rd = new RowDefinition();
	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0, GridLength::UnitType_Auto);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
	rowColl->Add(rd);


	//Cols
//	grid->ColDefCollection = new ColDefinitionCollection();
	ColDefinitionCollection *colColl =  grid->ColDefCollection;

	ColDefinition *cd = new ColDefinition();
	cd->Width() = GridLength(0.3, GridLength::UnitType_Star);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(0, GridLength::UnitType_Auto);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(50, GridLength::UnitType_Length);
	colColl->Add(cd);




	m_btn = new Button();
	grid->Children()->Add(m_btn);

	Grid *content = new Grid();
//	content->RowDefCollection = new RowDefinitionCollection();
//	content->ColDefCollection = new ColDefinitionCollection();
	content->Width() = 100;
	content->Height() = 50;

	nb::Gui::Rectangle *rcNormal = new nb::Gui::Rectangle();
	rcNormal->Fill = new SolidColorBrush(nb::System::Color(0, 50, 200));
	content->Children()->Add(rcNormal);

	nb::Gui::Rectangle *rcPress = new nb::Gui::Rectangle();
	rcPress->Fill = new SolidColorBrush(nb::System::Color(150, 50, 0));
	rcPress->Visibility() = ::Visibility_Collapsed;
	content->Children()->Add(rcPress);

	m_btn->Content = content;


	VisualStateManager * stateMgr = new VisualStateManager();
	content->VisualStateMgr() = stateMgr;

	VisualStateGroup * group = new VisualStateGroup("Button");
	stateMgr->AddGroup(group);

	VisualState *stateNormal = new VisualState("Normal");
	group->AddChild(stateNormal);

//	stateNormal->Target() = rcNormal;
//	stateNormal->TargetValue() = new RefEnumObject<VisibilityEnum>(Visibility_Visible);

	ObjectAnimation *animation;
//	stateNormal->Storyboard() = new Storyboard();

//	animation = new ObjectAnimation();
//	animation->From() = new RefEnumObject<VisibilityEnum>(Visibility_Collapsed);
//	animation->To() = new RefEnumObject<VisibilityEnum>(Visibility_Visible);
//	Storyboard::SetTarget(animation, rcNormal);
//	Storyboard::SetTargetProperty(animation, rcNormal->GetVisibilityProperty());

//	stateNormal->Storyboard()->AddChild(animation);

	

	VisualState *statePress = new VisualState("Pressed");
	group->AddChild(statePress);

	//statePress->Storyboard() = new Storyboard();

	VisualStateStoryboard *s = new VisualStateStoryboard();
	stateMgr->AddStoryboard(s);

	s->AddState(statePress);

	animation = new ObjectAnimation();
	animation->Duration = new TimeSpan(0, 0, 0);
	animation->From() = new RefEnumObject<VisibilityEnum>(Visibility_Visible);
	animation->To() = new RefEnumObject<VisibilityEnum>(Visibility_Collapsed);
	Storyboard::SetTarget(animation, rcNormal);
	Storyboard::SetTargetProperty(animation, rcNormal->GetVisibilityProperty());

	s->AddChild(animation);


	animation = new ObjectAnimation();
	animation->Duration = new TimeSpan(0, 0, 0);
	animation->From() = new RefEnumObject<VisibilityEnum>(Visibility_Collapsed);
	animation->To() = new RefEnumObject<VisibilityEnum>(Visibility_Visible);
	Storyboard::SetTarget(animation, rcPress);
	Storyboard::SetTargetProperty(animation, rcNormal->GetVisibilityProperty());

	s->AddChild(animation);



	s = new VisualStateStoryboard();
	stateMgr->AddStoryboard(s);

	s->AddState(stateNormal);

	animation = new ObjectAnimation();
	animation->Duration = new TimeSpan(0, 0, 0);
	animation->From() = new RefEnumObject<VisibilityEnum>(Visibility_Collapsed);
	animation->To() = new RefEnumObject<VisibilityEnum>(Visibility_Visible);
	Storyboard::SetTarget(animation, rcNormal);
	Storyboard::SetTargetProperty(animation, rcNormal->GetVisibilityProperty());

	s->AddChild(animation);


	animation = new ObjectAnimation();
	animation->Duration = new TimeSpan(0, 0, 0);
	animation->From() = new RefEnumObject<VisibilityEnum>(Visibility_Visible);
	animation->To() = new RefEnumObject<VisibilityEnum>(Visibility_Collapsed);
	Storyboard::SetTarget(animation, rcPress);
	Storyboard::SetTargetProperty(animation, rcNormal->GetVisibilityProperty());

	s->AddChild(animation);
}

CommonPage::~CommonPage(void)
{
}
