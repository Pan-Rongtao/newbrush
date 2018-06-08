#include "gui/Timeline.h"
#include "TimelinePrivate.h"

using namespace nb::Media;

NB_OBJECT_TYPE_IMPLEMENT(Timeline, nbObject, NULL, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT(Timeline, Duration, nb::System::TimeSpan, NULL);

Timeline::Timeline(void)
	: m_private(NULL)
{
	Duration = new nb::System::TimeSpan(0, 0, 1);
}

Timeline::~Timeline(void)
{
	delete m_private;
}

void Timeline::Begin()
{
	BeginOverride();

	GetPrivate()->Begin();
}

TimelinePrivate * Timeline::GetPrivate() const
{
	if(m_private == NULL)
	{
		Timeline *pThis = const_cast<Timeline *>(this);
		pThis->m_private = new TimelinePrivate(pThis);
	}
	return m_private;
}

void Timeline::SetCurrentFrame(const nb::System::TimeSpan &frame)
{
	GetPrivate()->SetCurrentFrame(frame);
}
