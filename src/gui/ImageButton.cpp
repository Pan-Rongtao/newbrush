#include "gui/ImageButton.h"
#include "gui/Grid.h"
#include "system/ObjectBelongingFactoryCollection.h"
#include "gui/ObjectAnimation.h"
#include "gui/Image.h"

using namespace nb::Core;
using namespace nb::Gui;
using namespace nb::Media;
using namespace nb::System;

NB_OBJECT_TYPE_IMPLEMENT(ImageButton, Button, NULL, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT(ImageButton, NormalImage, ImageSource, &ImageButton::OnNormalImageChanged);
NB_X_OBJECT_PROPERTY_IMPLEMENT(ImageButton, PressImage, ImageSource, &ImageButton::OnPressImageChanged);

ImageButton::ImageButton(void)
{
//	return ;
	NameRealm *nameRealm = new NameRealm();

	ControlTemplate *templ = new ControlTemplate();
//	templ->SetNameRealm(m_nameRealm);
	UIElementFactory *factory = new UIElementFactory(Type::GetType<Grid>());
	templ->VisualTree() = factory;

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
		}
	}//*/


	UIElementFactory *image = new UIElementFactory(Type::GetType<Image>());
	factory->Children()->Add(image);
	nameRealm->AddObject(image, "PressImage");
	//image->SetRefValue(Rectangle::FillProperty(), new nb::Media::SolidColorBrush(Color(0, 190, 0)));
	image->SetRefValue(UIElement::GetVisibilityProperty(), new RefEnumObject<VisibilityEnum>(Visibility_Collapsed));
	ImageSource *s = PressImage;
	image->SetRefValue(Image::SourceProperty(), s);


	image = new UIElementFactory(Type::GetType<Image>());
	factory->Children()->Add(image);
	nameRealm->AddObject(image, "NormalImage");
	s =  NormalImage;
	image->SetRefValue(Image::SourceProperty(), s);

//	RefObject *x = image->GetRefValue(Image::SourceProperty());
	//rect->SetRefValue(Rectangle::FillProperty(), new nb::Media::SolidColorBrush(Color(100, 0, 0)));

	//TranslateTransformPtr trans = new TranslateTransform();
//	image->SetRefValue(Rectangle::RenderTransformProperty(), new TranslateTransform(20,0));
//	rect->SetExteranlSetRefValue(Grid::RowProperty(), new aInt(1));

	Template = templ;
}

ImageButton::~ImageButton(void)
{
}

void ImageButton::OnNormalImageChanged(PropertyValueChangedEventArgs &args)
{
	NameRealm *nr = GetTemplateInstanceNameRealm();
	if(nr != NULL)
	{
		Image *image = dynamic_cast<Image *>(nr->FindObject("NormalImage"));
		if(image != NULL)
		{
			image->Source = dynamic_cast<ImageSource *>(args.m_newObject);

			InvalidateMeasure();
			InvalidateArrange();
		}

	}
}


void ImageButton::OnPressImageChanged(PropertyValueChangedEventArgs &args)
{
	NameRealm *nr = GetTemplateInstanceNameRealm();
	if(nr != NULL)
	{
		Image *image = dynamic_cast<Image *>(nr->FindObject("PressImage"));
		if(image != NULL)
		{
			image->Source = dynamic_cast<ImageSource *>(args.m_newObject);
			InvalidateMeasure();
			InvalidateArrange();
		}
	}
}
