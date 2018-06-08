#include "BaseTrackPrivate.h"

using namespace nb::Gui;

BaseTrackPrivate::BaseTrackPrivate(BaseTrack *owner)
:m_owner(owner)
{
}

BaseTrackPrivate::~BaseTrackPrivate()
{
}

void BaseTrackPrivate::OnPointerPress(const nb::System::Point &point)
{
}

void BaseTrackPrivate::OnPointerMove(const nb::System::Point &point)
{
}

void BaseTrackPrivate::OnPointerRelease(const nb::System::Point &point)
{
}

bool BaseTrackPrivate::IsPointerActive() const
{
	return false;
}
