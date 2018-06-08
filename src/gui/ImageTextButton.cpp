#include "gui/ImageTextButton.h"
#include "gui/Grid.h"
#include "system/ObjectBelongingFactoryCollection.h"
#include "gui/ObjectAnimation.h"
#include "gui/Image.h"
#include "gui/TextBlock.h"


using namespace nb::Gui;

using namespace nb::Core;
using namespace nb::Media;
using namespace nb::System;

NB_OBJECT_TYPE_IMPLEMENT(ImageTextButton, ImageButton, NULL, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT(ImageTextButton, Text, nb::System::String, &ImageTextButton::OnTextChanged);

ImageTextButton::ImageTextButton(void)
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

				animation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("Text"));
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
				animation->SetRefValue(Storyboard::GetTargetNameProperty(), new nb::System::String("Text"));
				animation->SetRefValue(Storyboard::GetTargetPropertyProperty(), UIElement::GetVisibilityProperty());
				animation->SetRefValue(ObjectAnimation::GetFromProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
				animation->SetRefValue(ObjectAnimation::GetToProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Visible));
				animation->SetRefValue(ObjectAnimation::DurationProperty(), new TimeSpan(0, 0, 0));
			}
		}
	}//*/


	UIElementFactory *image = new UIElementFactory(Type::GetType<Image>());
	factory->Children()->Add(image);
	nameRealm->AddObject(image, "PressImage");
	//image->SetRefValue(Rectangle::FillProperty(), new nb::Media::SolidColorBrush(Color(0, 190, 0)));
	image->SetRefValue(UIElement::GetVisibilityProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
	ImageSource *s = NormalImage;
	image->SetRefValue(Image::SourceProperty(), s);


	image = new UIElementFactory(Type::GetType<Image>());
	factory->Children()->Add(image);
	nameRealm->AddObject(image, "NormalImage");
	s = PressImage;
	image->SetRefValue(Image::SourceProperty(), s);

	
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

ImageTextButton::~ImageTextButton(void)
{
}

void ImageTextButton::OnTextChanged(PropertyValueChangedEventArgs &args)
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
