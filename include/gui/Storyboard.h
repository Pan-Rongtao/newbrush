#pragma once
#include "../gui/Timeline.h"

namespace nb { namespace gui {

class UIElement;

class NB_API Storyboard : public Timeline
{
public:
	Storyboard();
	virtual ~Storyboard();

	void AddChild(Timeline *timeline);

	static void SetTarget(Timeline *timeline, gui::UIElement *element);

	static gui::UIElement * GetTarget(Timeline *timeline);
	//TimelineCollection *Children();

//	nb::core::Property_rw<>			Target;
//	nb::core::Property_rw<>(TargetName, nb::System::String);
//	NB_OBJECT_EXTERNAL_PROPERTY_DECLARE(TargetProperty, nb::core::DependencyProperty);

protected:
	virtual void OnFrameChanged(const nb::core::TimeSpan &frame) {}
	virtual void BeginOverride() {}

};

}}
