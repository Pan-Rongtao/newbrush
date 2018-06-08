#include "RepeatButton.h"
#include "gui/Grid.h"
#include "system/ObjectBelongingFactoryCollection.h"
#include "gui/ObjectAnimation.h"
#include "gui/Image.h"
#include "gui/Rectangle.h"
#include "gui/SolidColorBrush.h"
#include "gui/TextBlock.h"

using namespace nb::Gui;

using namespace nb::Core;
using namespace nb::Media;
using namespace nb::System;


NB_OBJECT_TYPE_IMPLEMENT(RepeatButton, Button, NULL, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT(RepeatButton, Delay, aInt, NULL);
NB_X_OBJECT_PROPERTY_IMPLEMENT(RepeatButton, Interval, aInt, NULL);

RepeatButton::RepeatButton()
: m_bTriggerRepeat(false)
{
	m_pRepeatTimer = new Timer();
	m_pRepeatTimer->TimeoutEvent.Add(this, &RepeatButton::OnTimerOut);

	NameRealm *nameRealm = new NameRealm();
	ControlTemplate *pTemplate = new ControlTemplate();
	UIElementFactory *factory = new UIElementFactory(Type::GetType<Grid>());
	pTemplate->VisualTree() = factory;
	//状态管理部分
	ObjectBelongingFactory *pVisualStateManager = new ObjectBelongingFactory(Type::GetType<VisualStateManager>());
	factory->SetRefValue(UIElement::GetVisualStateMgrProperty(), pVisualStateManager);
	{
		ObjectBelongingFactory *pVisualStateGroupCollection = new ObjectBelongingFactory(Type::GetType<VisualStateGroupCollection>());
		pVisualStateManager->SetRefValue(VisualStateManager::VisualStateGroupsProperty(), pVisualStateGroupCollection);
		{
			ObjectBelongingFactory *pVisualStateGroup = new ObjectBelongingFactory(Type::GetType<VisualStateGroup>());
			pVisualStateGroupCollection->Children()->Add(pVisualStateGroup);
			nameRealm->AddObject(pVisualStateGroup, "Common");
			{
				ObjectBelongingFactory *pVisualState_Pressed = new ObjectBelongingFactory(Type::GetType<VisualState>());
				pVisualStateGroup->Children()->Add(pVisualState_Pressed);
				nameRealm->AddObject(pVisualState_Pressed, "Pressed");
				{//进入Press状态下的动画
					ObjectBelongingFactory *pPressStoryboard = new ObjectBelongingFactory(Type::GetType<Storyboard>());
					pVisualState_Pressed->SetRefValue(VisualState::GetStoryboardProperty(), pPressStoryboard);
					{
						ObjectBelongingFactory *pPressAnimation = new ObjectBelongingFactory(Type::GetType<ObjectAnimation>());
						pPressStoryboard->Children()->Add(pPressAnimation);
						{
							pPressAnimation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("NormalBkColor"));
							pPressAnimation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
							pPressAnimation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
							pPressAnimation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
							pPressAnimation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
						}

						pPressAnimation = new ObjectBelongingFactory(Type::GetType<ObjectAnimation>());
						pPressStoryboard->Children()->Add(pPressAnimation);
						{
							pPressAnimation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("PressBkColor"));
							pPressAnimation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
							pPressAnimation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
							pPressAnimation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
							pPressAnimation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
						}
					}
				}
				ObjectBelongingFactory *pVisualState_Normal = new ObjectBelongingFactory(Type::GetType<VisualState>());
				pVisualStateGroup->Children()->Add(pVisualState_Normal);
				nameRealm->AddObject(pVisualState_Normal, "Normal");
				{//进入Normal状态下的动画
					ObjectBelongingFactory *pNormalStoryboard = new ObjectBelongingFactory(Type::GetType<Storyboard>());
					pVisualState_Normal->SetRefValue(VisualState::GetStoryboardProperty(), pNormalStoryboard);
					{
						ObjectBelongingFactory *pNormalAnimation = new ObjectBelongingFactory(Type::GetType<ObjectAnimation>());
						pNormalStoryboard->Children()->Add(pNormalAnimation);
						{
							pNormalAnimation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("NormalBkColor"));
							pNormalAnimation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
							pNormalAnimation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
							pNormalAnimation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
							pNormalAnimation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
						}

						pNormalAnimation = new ObjectBelongingFactory(Type::GetType<ObjectAnimation>());
						pNormalStoryboard->Children()->Add(pNormalAnimation);
						{
							pNormalAnimation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("PressBkColor"));
							pNormalAnimation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
							pNormalAnimation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
							pNormalAnimation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
							pNormalAnimation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
						}
					}
				}
			}
		}
	}
	//视觉树部分
	ObjectBelongingFactory *pNormalBkColor = new ObjectBelongingFactory(Type::GetType<Rectangle>());
	factory->Children()->Add(pNormalBkColor);
	nameRealm->AddObject(pNormalBkColor, "NormalBkColor");
	pNormalBkColor->SetRefValue(Rectangle::FillProperty(), new nb::Media::SolidColorBrush(Color(0, 255, 0, 0)));

	ObjectBelongingFactory *pPressBkColor = new ObjectBelongingFactory(Type::GetType<Rectangle>());
	factory->Children()->Add(pPressBkColor);
	nameRealm->AddObject(pPressBkColor, "PressBkColor");
	pPressBkColor->SetRefValue(Rectangle::FillProperty(), new nb::Media::SolidColorBrush(Color(0, 0, 255, 0)));
	pPressBkColor->SetRefValue(UIElement::GetVisibilityProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
	Template = pTemplate;
}

RepeatButton::~RepeatButton()
{
}

void RepeatButton::OnPointerPress(bool &handled)
{
	Button::OnPointerPress(handled);
	handled = true;
	if(!m_pRepeatTimer->IsActive())
	{
		m_pRepeatTimer->Start((Int)Delay);
	}
}

void RepeatButton::OnPointerRelease()
{
	Button::OnPointerRelease();
	m_bTriggerRepeat = false;
	m_pRepeatTimer->Stop();
}

void RepeatButton::OnTimerOut(nb::System::Timer::TimeoutParam &param)
{
	if(m_bTriggerRepeat == false)
	{
		m_bTriggerRepeat = true;
		m_pRepeatTimer->Stop();
		m_pRepeatTimer->Start((Int)Interval);
	}
	OnClick();
}

void RepeatButton::OnClick()
{
	RepeatClickEventParam param;
	RepeatClickEvent.Dispatch(param);
}
