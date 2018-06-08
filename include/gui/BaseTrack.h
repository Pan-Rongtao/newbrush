#pragma once
#include "core/Object.h"
#include "system/Point.h"
#include "GuiDef.h"

namespace nb
{
	namespace Gui
	{
		class BaseTrackPrivate;
		class NB_GUI_DECLSPEC_INTERFACE BaseTrack : public nbObject
		{
			NB_OBJECT_TYPE_DECLARE();
		public:
			BaseTrack();
			virtual ~BaseTrack();
			NB_OBJECT_VALUE_PROPERTY_DECLARE(Enable, Core::Boolx);
			NB_OBJECT_VALUE_PROPERTY_DECLARE(MonopolizePointer, Core::Boolx);
			virtual void OnPointerPress(const nb::System::Point &point);
			virtual void OnPointerMove(const nb::System::Point &point);
			virtual void OnPointerRelease(const nb::System::Point &point);
			virtual bool IsPointerActive() /*const*/;
			BaseTrackPrivate *GetPrivate();
		private:
			BaseTrackPrivate *m_private;
		};
		typedef nbObjectPtrDerive<BaseTrack, nbObjectPtr> BaseTrackPtr;
	}
}
