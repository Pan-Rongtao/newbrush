#include "gui/BaseTrack.h"
#include "BaseTrackPrivate.h"

using namespace nb::Gui;
using namespace nb::Core;

NB_OBJECT_TYPE_IMPLEMENT(BaseTrack, nbObject, NULL, NULL);


NB_OBJECT_PROPERTY_IMPLEMENT_EX(BaseTrack, Enable, Boolx, NULL);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(BaseTrack, MonopolizePointer, Boolx, NULL);

BaseTrack::BaseTrack()
{
	Enable() = true;
	MonopolizePointer() = true;
	m_private = new BaseTrackPrivate(this);
}

BaseTrack::~BaseTrack()
{
	delete m_private;
}

BaseTrackPrivate *BaseTrack::GetPrivate()
{
	return m_private;
}
void BaseTrack::OnPointerPress(const nb::System::Point &point)
{
	GetPrivate()->OnPointerPress(point);
}

void BaseTrack::OnPointerMove(const nb::System::Point &point)
{
	GetPrivate()->OnPointerMove(point);
}

void BaseTrack::OnPointerRelease(const nb::System::Point &point)
{
	GetPrivate()->OnPointerRelease(point);
}

bool BaseTrack::IsPointerActive() /*const*/
{
	return GetPrivate()->IsPointerActive();
}
