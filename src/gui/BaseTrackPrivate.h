#pragma once

#include "gui/BaseTrack.h"

namespace nb
{
	namespace Gui
	{
		class BaseTrackPrivate
		{
		public:
			BaseTrackPrivate(BaseTrack *owner);
			~BaseTrackPrivate();

			virtual void OnPointerPress(const nb::System::Point &point);
			virtual void OnPointerMove(const nb::System::Point &point);
			virtual void OnPointerRelease(const nb::System::Point &point);
			virtual bool IsPointerActive() const;
		private:
			BaseTrack *m_owner;
		};
	}
}
