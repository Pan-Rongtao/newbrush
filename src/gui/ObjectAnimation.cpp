#include "gui/ObjectAnimation.h"
#include "gui/UIElement.h"
#include "gui/Storyboard.h"
#include "gui/NameRealm.h"
#include "system/String.h"

using namespace nb::Core;
using namespace nb::Media;
using namespace nb::Gui;

NB_OBJECT_TYPE_IMPLEMENT(ObjectAnimation, AnimationTimeline, NULL, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(ObjectAnimation, From, RefObject, NULL);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(ObjectAnimation, To, RefObject, NULL);

ObjectAnimation::ObjectAnimation(void)
{
}

ObjectAnimation::~ObjectAnimation(void)
{
}

void ObjectAnimation::OnFrameChanged(const nb::System::TimeSpan &frame)
{
	UIElement *element = Storyboard::GetTarget(this);
	if(element == NULL)
	{
		nb::System::String *str = dynamic_cast<nb::System::String *>(GetRefValue(Storyboard::GetTargetNameProperty()));
		if(str == NULL) return;
		
		NameRealm *nr;
		nb::System::String *n;
		if(!NameRealm::FindNameRealm(this, nr, n)) return;

		element = dynamic_cast<UIElement *>(nr->FindObject(str->ToUtf8().GetData()));
		if(element == NULL) return;
	}

	DependencyProperty *prop = Storyboard::GetTargetProperty(this);
	if(prop == NULL) return;

	float v = GetFrameValue(frame);

	RefObject *object;
	if(v <= 0.5)
	{
		object = From();
	}
	else
	{
		object = To();
	}


	if(object == NULL)
	{
		element->SetRefValue(prop, object);
	}
	else
	{
		//if(prop->GetElementType() == 
		element->SetRefValue(prop, object);
	}
}

