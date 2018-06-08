#pragma once

#include "core/Object.h"
#include "Timeline.h"



namespace nb {

namespace Core{
class DependencyProperty;
}

namespace Gui{
class UIElement;
}

namespace Media {

class StoryboardPrivate;

class NB_EXPORT Storyboard : public Timeline, public nb::System::IHasChildrenArray
{
	NB_OBJECT_TYPE_DECLARE();

public:
	Storyboard(void);
	virtual ~Storyboard(void);

	void AddChild(Timeline *timeline);

	static void SetTarget(Timeline *timeline, Gui::UIElement *element);
	static void SetTargetProperty(Timeline *timeline, Core::DependencyProperty *prop);

	static Gui::UIElement * GetTarget(Timeline *timeline);
	static Core::DependencyProperty * GetTargetProperty(Timeline *timeline);

	StoryboardPrivate * GetPrivate() const;

	TimelineCollection *Children();

	NB_OBJECT_EXTERNAL_PROPERTY_DECLARE(Target, nbObject);
	NB_OBJECT_EXTERNAL_PROPERTY_DECLARE(TargetName, nb::System::String);
	NB_OBJECT_EXTERNAL_PROPERTY_DECLARE(TargetProperty, nb::Core::DependencyProperty);

protected:
	virtual void OnFrameChanged(const nb::System::TimeSpan &frame);
	virtual void BeginOverride();

	virtual nb::Core::InterfaceBase * GetInterfaceOverride(const std::type_info &type);

private:
	nb::System::IArray * GetChildrenArray();

	StoryboardPrivate *m_private;

	TimelineCollection m_children;
};

typedef nbObjectPtrDerive<Storyboard, TimelinePtr> StoryboardPtr;

}}
