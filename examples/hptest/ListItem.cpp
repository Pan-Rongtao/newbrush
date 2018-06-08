#include "ListItem.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/System/ObjectBelongingFactoryCollection.h"
#include "../../../Include/Gui/ObjectAnimation.h"
#include "../../../Include/Gui/Image.h"
#include "../../../Include/Gui/TextBlock.h"
#include "../../../Include/Gui/StackPanel.h"
#include "../../../Include/Gui/Rectangle.h"
#include "../../../Include/Gui/SolidColorBrush.h"


using namespace nb::Core;
using namespace nb::Gui;
using namespace nb::Media;
using namespace nb::System;

NB_OBJECT_TYPE_IMPLEMENT(ListItem, ImageButton, NULL, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT(ListItem, Text, nb::System::String, &ListItem::OnTextChanged);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ListItem, TopLineImage, ImageSource, &ListItem::OnTopLineImageChanged);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ListItem, BottomLineImage, ImageSource, &ListItem::OnBottomLineImageChanged);

ListItem::ListItem(void)
{
//	return ;
	NameRealm *nameRealm = new NameRealm();

	ControlTemplate *templ = new ControlTemplate();
//	templ->SetNameRealm(m_nameRealm);
	UIElementFactory *factory = new UIElementFactory(Type::GetType<Grid>());
	templ->VisualTree() = factory;

	// 行定义
	ObjectBelongingFactory* rowDefCollectionFactory = new ObjectBelongingFactoryT<RowDefinitionCollection>();
	factory->SetRefValue(Grid::RowDefCollectionProperty(), rowDefCollectionFactory);

//	rowDefCollectionFactory->SetRefValue(RowDefinitionCollection::TestProperty(), new nb::Media::SolidColorBrush());

//	ObjectBelongingFactory* rowDefFactory = new ObjectBelongingFactoryT<RowDefinition>();
//	rowDefFactory->SetValueValue(RowDefinition::GetHeightProperty(), GridLength(0.3, GridLength::UnitType_Star));
//	rowDefCollectionFactory->Children()->Add(rowDefFactory);


//	rowDefFactory = new ObjectBelongingFactoryT<RowDefinition>();
//	rowDefFactory->SetValueValue(RowDefinition::GetHeightProperty(), GridLength(0.3, GridLength::UnitType_Star));
//	rowDefCollectionFactory->Children()->Add(rowDefFactory);


	// 列定义
	ObjectBelongingFactory* colDefCollectionFactory = new ObjectBelongingFactoryT<ColDefinitionCollection>();
	factory->SetRefValue(Grid::ColDefCollectionProperty(), colDefCollectionFactory);


	ObjectBelongingFactory* colDefFactory = new ObjectBelongingFactoryT<ColDefinition>();
	colDefFactory->SetValueValue(ColDefinition::GetWidthProperty(), GridLength(0.3, GridLength::UnitType_Star));
	colDefCollectionFactory->Children()->Add(colDefFactory);
	
//*/

	// 显示状态管理器
	ObjectBelongingFactory *visualStateMgr = new ObjectBelongingFactory(Type::GetType<VisualStateManager>());
	factory->SetRefValue(UIElement::GetVisualStateMgrProperty(), visualStateMgr);
	{
		ObjectBelongingFactory *visualStateGroupColl = new ObjectBelongingFactory(Type::GetType<VisualStateGroupCollection>());
		visualStateMgr->SetRefValue(VisualStateManager::VisualStateGroupsProperty(), visualStateGroupColl);

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
				animation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("NormalImage"));
				animation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
				animation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
				animation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
				animation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
			}


			animation = new ObjectBelongingFactory(Type::GetType<ObjectAnimation>());
			s->Children()->Add(animation);
			{
				animation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("PressImage"));
				animation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
				animation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
				animation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
				animation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
			}
			
			animation = new ObjectBelongingFactory(Type::GetType<ObjectAnimation>());
			s->Children()->Add(animation);
			{

				animation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("NormalBkgndColor"));
				animation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
				animation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
				animation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
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
				animation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("PressImage"));
				animation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
				animation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
				animation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
				animation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
			}

			animation = new ObjectBelongingFactory(Type::GetType<ObjectAnimation>());
			s->Children()->Add(animation);
			{
				animation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("NormalImage"));
				animation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
				animation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
				animation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
				animation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
			}
			
			animation = new ObjectBelongingFactory(Type::GetType<ObjectAnimation>());
			s->Children()->Add(animation);
			{
				animation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("NormalBkgndColor"));
				animation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
				animation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
				animation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
				animation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
			}
		}
	}//*/


	UIElementFactory *panel = new UIElementFactory(Type::GetType<StackPanel>());
	factory->Children()->Add(panel);
	nameRealm->AddObject(panel, "LayoutPanel");
	panel->SetRefValue(StackPanel::GetOrientationProperty(), new RefEnumObject<nb::Gui::Orientation>(nb::Gui::Orientation_Vert));

	UIElementFactory *pTopLineImage = new UIElementFactory(Type::GetType<Image>());
	panel->Children()->Add(pTopLineImage);
	nameRealm->AddObject(pTopLineImage, "TopLineImage");
	pTopLineImage->SetRefValue(Image::SourceProperty(), TopLineImage);
	pTopLineImage->SetRefValue(UIElement::GetVisibilityProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));

	UIElementFactory *ChildPanel = new UIElementFactory(Type::GetType<Grid>());
	panel->Children()->Add(ChildPanel);
	nameRealm->AddObject(ChildPanel, "ChildLayoutPanel");

	UIElementFactory *image = new UIElementFactory(Type::GetType<Image>());
	ChildPanel->Children()->Add(image);
	nameRealm->AddObject(image, "PressImage");
	//image->SetRefValue(Rectangle::FillProperty(), new nb::Media::SolidColorBrush(Color(0, 190, 0)));
	image->SetRefValue(UIElement::GetVisibilityProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
	ImageSource *s = NormalImage;
	image->SetRefValue(Image::SourceProperty(), s);


	image = new UIElementFactory(Type::GetType<Image>());
	ChildPanel->Children()->Add(image);
	nameRealm->AddObject(image, "NormalImage");
	s = PressImage;
	image->SetRefValue(Image::SourceProperty(), s);

	UIElementFactory *rect = new UIElementFactory(Type::GetType<nb::Gui::Rectangle>());
	ChildPanel->Children()->Add(rect);
	nameRealm->AddObject(rect, "NormalBkgndColor");
	rect->SetRefValue(Rectangle::FillProperty(), new nb::Media::SolidColorBrush(Color(100, 255, 255, 255)));

	
	UIElementFactory *pBottomLineImage = new UIElementFactory(Type::GetType<Image>());
	panel->Children()->Add(pBottomLineImage);
	nameRealm->AddObject(pBottomLineImage, "BottomLineImage");
	pBottomLineImage->SetRefValue(Image::SourceProperty(), BottomLineImage);
	pBottomLineImage->SetRefValue(UIElement::GetVisibilityProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));

	
	UIElementFactory *pTextBlock = new UIElementFactory(Type::GetType<TextBlock>());
	factory->Children()->Add(pTextBlock);
	nameRealm->AddObject(pTextBlock, "Text");
	pTextBlock->SetRefValue(TextBlock::TextProperty(), new nb::System::String("default"));


//	pTextBlock->SetRefValue(TextBlock::GetColorProperty(), new nb::System::Color(255, 255, 0, 0));


//	RefObject *x = image->GetRefValue(Image::SourceProperty());
	//rect->SetRefValue(Rectangle::FillProperty(), new nb::Media::SolidColorBrush(Color(100, 0, 0)));

	//TranslateTransformPtr trans = new TranslateTransform();
//	image->SetRefValue(Rectangle::RenderTransformProperty(), new TranslateTransform(20,0));
//	rect->SetExteranlSetRefValue(Grid::RowProperty(), new aInt(1));

	Template = templ;
}

ListItem::~ListItem(void)
{
}

void ListItem::OnTextChanged(PropertyValueChangedEventArgs &args)
{
	NameRealm *nr = GetTemplateInstanceNameRealm();
	if(nr != NULL)
	{
		TextBlock *text = dynamic_cast<TextBlock *>(nr->FindObject("Text"));
		if(text != NULL)
		{
			text->Text = dynamic_cast<nb::System::String *>(args.m_newObject);

			text->InvalidateMeasure();
			text->InvalidateArrange();
		}

	}
}

void ListItem::OnTopLineImageChanged(PropertyValueChangedEventArgs &args)
{
	NameRealm *nr = GetTemplateInstanceNameRealm();
	if(nr != NULL)
	{
		Image *image = dynamic_cast<Image *>(nr->FindObject("TopLineImage"));
		if(image != NULL)
		{
			image->Source = dynamic_cast<ImageSource *>(args.m_newObject);

			InvalidateMeasure();
			InvalidateArrange();
		}

	}
}

void ListItem::OnBottomLineImageChanged(PropertyValueChangedEventArgs &args)
{
	NameRealm *nr = GetTemplateInstanceNameRealm();
	if(nr != NULL)
	{
		Image *image = dynamic_cast<Image *>(nr->FindObject("BottomLineImage"));
		if(image != NULL)
		{
			image->Source = dynamic_cast<ImageSource *>(args.m_newObject);

			InvalidateMeasure();
			InvalidateArrange();
		}

	}
}