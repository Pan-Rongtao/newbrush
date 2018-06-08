#pragma once

#include "system/TimeSpan.h"
#include "core/Object.h"
#include "system/Array.h"
#include "GuiDef.h"

namespace nb { namespace Media
{
class TimelinePrivate;
class NB_GUI_DECLSPEC_INTERFACE Timeline : public nbObject
{
	NB_OBJECT_TYPE_DECLARE();

	friend class TimelinePrivate;

public:
	Timeline(void);
	virtual ~Timeline(void);

	virtual float GetFrameValue(const nb::System::TimeSpan &frame) {return 0;}

	void Begin();

	void SetCurrentFrame(const nb::System::TimeSpan &frame);

	TimelinePrivate * GetPrivate() const;

	NB_X_OBJECT_PROPERTY_DECLARE(Duration, nb::System::TimeSpan);

protected:
	virtual void BeginOverride() {}
	virtual void OnFrameChanged(const nb::System::TimeSpan &frame) {}

private:
	nb::System::TimeSpan m_duration;
	nb::System::TimeSpan m_beginTime;

//	nb::Gui::Timer m_timer;

	TimelinePrivate * m_private;
};

class NB_GUI_DECLSPEC_INTERFACE TimelineCollection : public System::ObjectArray<Timeline>
{
};

typedef nbObjectPtrDerive<Timeline, nbObjectPtr> TimelinePtr;

}}
