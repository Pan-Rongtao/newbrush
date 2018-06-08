#include "gui/Storyboard.h"
#include "gui/UIElement.h"
#include "core/TypesPropertyValuesStore.h"
#include "system/String.h"
#include "StoryboardPrivate.h"

using namespace nb::Media;

using namespace nb::Core;
using namespace nb::Gui;

NB_OBJECT_TYPE_IMPLEMENT(Storyboard, nbObject, NULL, NULL);

NB_OBJECT_EXTERNAL_PROPERTY_IMPLEMENT(Storyboard, Target, nbObject);
NB_OBJECT_EXTERNAL_PROPERTY_IMPLEMENT(Storyboard, TargetName, nb::System::String);
NB_OBJECT_EXTERNAL_PROPERTY_IMPLEMENT(Storyboard, TargetProperty, DependencyProperty);

namespace nb { namespace Media {
class StoryboardTypeProperties
{
public:
	StoryboardTypeProperties()
	{
//		nbDependencyProperty::PrepareExternalProperty("Target", typeid(Storyboard), typeid(Timeline), NULL);
//		nbDependencyProperty::PrepareExternalProperty("TargetProperty", typeid(Storyboard), typeid(nbDependencyProperty), NULL);
	}
} s_StoryboardTypeProperties;
}}

Storyboard::Storyboard(void)
	: m_private(NULL)
{
}

Storyboard::~Storyboard(void)
{
	delete m_private;
}

void Storyboard::AddChild(Timeline *timeline)
{
	GetPrivate()->AddChild(timeline);
}

void Storyboard::SetTarget(Timeline *timeline, UIElement *element)
{
//	nbType *pType = nbType::GetType<Storyboard>();
//	timeline->GetTypesPropertyValuesStore()->SaveRefValue(pType, pType->GetExternalProperty("Target"), element);

	timeline->SetRefValue(GetTargetProperty(), element);
}

void Storyboard::SetTargetProperty(Timeline *timeline, DependencyProperty *prop)
{
//	nbType *pType = nbType::GetType<Storyboard>();
//	timeline->GetTypesPropertyValuesStore()->SaveRefValue(pType, pType->GetExternalProperty("TargetProperty"), prop);

	timeline->SetRefValue(GetTargetPropertyProperty(), prop);
}

UIElement * Storyboard::GetTarget(Timeline *timeline)
{
//	nbType *pType = nbType::GetType<Storyboard>();
//	return dynamic_cast<UIElement *>(timeline->GetTypesPropertyValuesStore()->GetRefValue(pType, pType->GetExternalProperty("Target")));

	return dynamic_cast<UIElement *>(timeline->GetRefValue(GetTargetProperty()));
}

DependencyProperty * Storyboard::GetTargetProperty(Timeline *timeline)
{
//	nbType *pType = nbType::GetType<Storyboard>();
//	return dynamic_cast<nbDependencyProperty *>(timeline->GetTypesPropertyValuesStore()->GetRefValue(pType, pType->GetExternalProperty("TargetProperty")));

	return dynamic_cast<DependencyProperty *>(timeline->GetRefValue(GetTargetPropertyProperty()));
}

StoryboardPrivate * Storyboard::GetPrivate() const
{
	if(m_private == NULL)
	{
		Storyboard *pThis = const_cast<Storyboard *>(this);
		pThis->m_private = new StoryboardPrivate(pThis);
	}

	return m_private;
}

void Storyboard::OnFrameChanged(const nb::System::TimeSpan &frame)
{
	GetPrivate()->OnFrameChanged(frame);
}

void Storyboard::BeginOverride()
{
	nb::System::TimeSpanPtr dur = new nb::System::TimeSpan();

	int count = Children()->GetCount();
	for(int i=0; i<count; i++)
	{
		nb::System::TimeSpan *x = Children()->GetAt(i)->Duration;
		if(x != NULL && *x > *dur)
		{
			*dur = *x;
		}
	}

	Duration = dur;

	GetPrivate()->BeginOverride();
}

TimelineCollection *Storyboard::Children()
{
	return &m_children;
}

nb::Core::InterfaceBase * Storyboard::GetInterfaceOverride(const std::type_info &type)
{
	std::string typeName = type.name();

	if(typeName == typeid(nb::System::IHasChildrenArray).name())
	{
		return dynamic_cast<nb::System::IHasChildrenArray *>(this);
	}
	else
	{
		return NULL;
	}
}

nb::System::IArray * Storyboard::GetChildrenArray()
{
	return &m_children;
}

