#include "StoryboardPrivate.h"
#include "gui/Storyboard.h"

using namespace nb::Media;
using namespace nb::System;

StoryboardPrivate::StoryboardPrivate(Storyboard *owner)
	: m_owner(owner)
{
	m_durationLock = m_owner->LockPropertyValue(m_owner->DurationProperty());
}

StoryboardPrivate::~StoryboardPrivate(void)
{
}

void StoryboardPrivate::AddChild(Timeline *timeline)
{
	//不适用了
	/*
	m_childs.push_back(timeline);

	TimeSpan span;
	if(!m_owner->Duration().IsNull()) span = m_owner->Duration();

	if(span < timeline->Duration())
	{
		span = timeline->Duration();
//不适用了		m_owner->SetRefValue(m_owner->GetDurationProperty(), span, m_durationLock);
	}*/
}

void StoryboardPrivate::OnFrameChanged(const nb::System::TimeSpan &frame)
{
//	int count = m_childs.size();

//	std::vector<TimelinePtr>::iterator itor = m_childs.begin();
//	for(; itor < m_childs.end(); itor++)
//	{
//		Timeline *tl = *itor;
//	//	double rate = frame.GetMilliSeconds() / tl->Duration()->GetMilliSeconds();
//	//	if(rate >= 0 && rate <= 1)
//		{
//	//		tl->GetFrameValue(frame);
//			tl->SetCurrentFrame(frame);
//		}
//	}

	TimelineCollection *children = m_owner->Children();
	int count = children->GetCount();
	for(int i=0; i<count; i++)
	{
		Timeline *tl = children->GetAt(i);
		tl->SetCurrentFrame(frame);
	}
}

void StoryboardPrivate::BeginOverride()
{
}

