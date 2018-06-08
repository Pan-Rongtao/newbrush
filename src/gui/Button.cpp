#include "gui/Button.h"
#include "gui/ControlTemplate.h"
#include "gui/UIElementFactory.h"
#include "gui/Grid.h"
#include "gui/Rectangle.h"
#include "gui/SolidColorBrush.h"
#include "gui/VisualStateGroup.h"
#include "system/ObjectBelongingFactoryCollection.h"

#include "gui/ObjectAnimation.h"
#include "system/String.h"

#include "gui/TranslateTransform.h"

using namespace nb::Gui;

using namespace nb::Core;
using namespace nb::Media;
using namespace nb::System;

NB_OBJECT_TYPE_IMPLEMENT(Button, Control, NULL, NULL);

class RefObjextTst : public OriginObject
{
public:
	RefObjextTst() {}
	RefObjextTst(const RefObjextTst &r) {}
};

Button::Button(void)
{
	RefObjextTst bb;
	RefObjextTst bb1=bb;

//	RefObjectPtr z = new RefObject();

//	RefObjectWeatPtr wx1 = z; //这里Linux编译通不过
//	RefObjectPtr x1 = z;
//	RefObject x2;
//	x2 = *z;

//	nbObject x;
//	nbObject x1 = x;

	NameRealmPtr nameRealm = new NameRealm();

	ControlTemplatePtr templ = new ControlTemplate();
	UIElementFactory *factory = new UIElementFactory(Type::GetType<Grid>());
	templ->VisualTree() = factory;

//	factory->SetRefValue(Grid::GetRowDefCollectionProperty(), new RowDefinitionCollection());
//	factory->SetRefValue(Grid::GetColDefCollectionProperty(), new ColDefinitionCollection());
	//factory->SetRefValue(Grid::GetVisualStateMgrProperty(), NULL);

//	factory->SetElementPropertyValue(Grid::GetRowDefCollectionProperty(), new ObjectFactory(Type::GetType<RowDefinitionCollection>()));
//	factory->SetElementPropertyValue(Grid::GetColDefCollectionProperty(), new ObjectFactory(Type::GetType<ColDefinitionCollection>()));

	
/*	X(factory)

		//行定义
		Property_Value(Grid::GetRowDefCollectionProperty(), new ObjectBelongingFactoryT<RowDefinitionCollection>)
			Child_Value(new ObjectBelongingFactoryT<RowDefinition>())
				Property_Value(RowDefinition::GetHeightProperty(), GridLength(0.3, GridLength::UnitType_Star)
			Child_Value()

		//列定义
		Property_Value(factory)
*/


	// 行定义
/*	ObjectBelongingFactory* rowDefCollectionFactory = new ObjectBelongingFactoryT<RowDefinitionCollection>();
	factory->SetRefValue(Grid::RowDefCollectionProperty(), rowDefCollectionFactory);

//	rowDefCollectionFactory->SetRefValue(RowDefinitionCollection::TestProperty(), new nb::Media::SolidColorBrush());

	ObjectBelongingFactory* rowDefFactory = new ObjectBelongingFactoryT<RowDefinition>();
	rowDefFactory->SetValueValue(RowDefinition::GetHeightProperty(), GridLength(0.3, GridLength::UnitType_Star));
	rowDefCollectionFactory->Children()->Add(rowDefFactory);


//	rowDefFactory = new ObjectBelongingFactoryT<RowDefinition>();
//	rowDefFactory->SetValueValue(RowDefinition::GetHeightProperty(), GridLength(0.3, GridLength::UnitType_Star));
//	rowDefCollectionFactory->Children()->Add(rowDefFactory);


	// 列定义
	ObjectBelongingFactory* colDefCollectionFactory = new ObjectBelongingFactoryT<ColDefinitionCollection>();
	factory->SetRefValue(Grid::ColDefCollectionProperty(), colDefCollectionFactory);



	// 显示状态管理器
	ObjectBelongingFactory *visualStateMgr = new ObjectBelongingFactory(Type::GetType<VisualStateManager>());
	factory->SetRefValue(UIElement::GetVisualStateMgrProperty(), visualStateMgr);
	{
		ObjectBelongingFactory *visualStateGroupColl = new ObjectBelongingFactory(Type::GetType<VisualStateGroupCollection>());
		visualStateMgr->SetRefValue(VisualStateManager::GetVisualStateGroupsProperty(), visualStateGroupColl);

		ObjectBelongingFactory *visualStateGroup = new ObjectBelongingFactory(Type::GetType<VisualStateGroup>());
		visualStateGroupColl->Children()->Add(visualStateGroup);
		nameRealm->AddObject(visualStateGroup, "Common");

		ObjectBelongingFactory *visualState = new ObjectBelongingFactory(Type::GetType<VisualState>());
		visualStateGroup->Children()->Add(visualState);
		nameRealm->AddObject(visualState, "Pressed");
		{
			ObjectBelongingFactory *s = new ObjectBelongingFactory(Type::GetType<Storyboard>());
			visualState->SetRefValue(VisualState::GetStoryboardProperty(), s);

			ObjectBelongingFactory *animation = new ObjectBelongingFactory(Type::GetType<ObjectAnimation>());
			s->Children()->Add(animation);
			{
				animation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("NormalBkgnd"));
				animation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
				animation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
				animation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
				animation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
			}

			animation = new ObjectBelongingFactory(Type::GetType<ObjectAnimation>());
			s->Children()->Add(animation);
			{
				animation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("PressBkgnd"));
				animation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
				animation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
				animation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
				animation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
			}
		}

		visualState = new ObjectBelongingFactory(Type::GetType<VisualState>());
		visualStateGroup->Children()->Add(visualState);
		nameRealm->AddObject(visualState, "Normal");
		{
			ObjectBelongingFactory *s = new ObjectBelongingFactory(Type::GetType<Storyboard>());
			visualState->SetRefValue(VisualState::GetStoryboardProperty(), s);

			ObjectBelongingFactory *animation = new ObjectBelongingFactory(Type::GetType<ObjectAnimation>());
			s->Children()->Add(animation);
			{
				animation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("PressBkgnd"));
				animation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
				animation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
				animation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
				animation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
			}

			animation = new ObjectBelongingFactory(Type::GetType<ObjectAnimation>());
			s->Children()->Add(animation);
			{
				animation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("NormalBkgnd"));
				animation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
				animation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
				animation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
				animation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
			}
		}
	}//*/


//	ObjectFactory *VisualStateGroup = new ObjectFactory(Type::GetType<nb::Gui::VisualStateGroup>());


//	factory->SetElementPropertyValue(Grid::GetVisualStateMgrProperty(), visualStateMgr);


	UIElementFactory *rect = new UIElementFactory(Type::GetType<Rectangle>());
	factory->Children()->Add(rect);
	nameRealm->AddObject(rect, "PressBkgnd");
	rect->SetRefValue(Rectangle::FillProperty(), new nb::Media::SolidColorBrush(Color(0, 190, 0)));
//	rect->SetRefValue(Rectangle::GetVisibilityProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));


	rect = new UIElementFactory(Type::GetType<Rectangle>());
	factory->Children()->Add(rect);
	nameRealm->AddObject(rect, "NormalBkgnd");
	rect->SetRefValue(Rectangle::FillProperty(), new nb::Media::SolidColorBrush(Color(100, 0, 0)));

	//TranslateTransformPtr trans = new TranslateTransform();
	rect->SetRefValue(Rectangle::RenderTransformProperty(), new TranslateTransform(20,0));
//	rect->SetExteranlSetRefValue(Grid::RowProperty(), new aInt(1));

//	Template = templ;

	Storyboard::GetTargetProperty();
}

Button::~Button(void)
{

}

void Button::OnPointerPress(bool &handled)
{
	handled = true;

	if(Content != NULL)
	{
		Content->GotoVisualState("Button", "Pressed");
	}

	GotoVisualState("Button", "Pressed");
}

void Button::OnPointerRelease()
{
	if(Content != NULL)
	{
		Content->GotoVisualState("Button", "Normal");
	}
	GotoVisualState("Button", "Normal");
}
