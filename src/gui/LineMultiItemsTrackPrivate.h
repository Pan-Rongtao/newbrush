#pragma once

#include "gui/LineMultiItemsTrack.h"
#include "ReboundScrollCtrler.h"

namespace nb
{
	namespace Gui
	{
		class LineMultiItemsTrackPrivate : public nbObject
		{
		public:
			LineMultiItemsTrackPrivate(LineMultiItemsTrack *owner);
			virtual ~LineMultiItemsTrackPrivate();
			
			//ILineMultiItemsTrackHandle Interfaces			
			//virtual ILineMultiItemsTrackHandleEvent *SetEventInterface(ILineMultiItemsTrackHandleEvent *pEvent);

			virtual void SetOrientation(nb::Gui::TrackOrientation nTrackOrientation = nb::Gui::TrackOrientation_Vert);
			virtual void SetItemCount(int nCount);
			virtual int GetItemCount() /*const*/;
			virtual void SetItemSize(int nSize);
			virtual int GetItemSize() /*const*/;
			virtual void SetPageSize(int nSize);
			virtual int GetPageSize() /*const*/;
			virtual void SetFirstItem(int nItem);
			virtual void SetFirstItemOffset(float fOffset);
			virtual void ZeroItemOffset();
			virtual void SetAccel(float fAccel);
			virtual void SetMaxSpeed(float fSpeed);
			virtual void SetHoldBackSpeed(float fSpeed);
			virtual void SetReboundAccel(float fAccel);

			virtual void SetCycMode(bool bCycMode);

			virtual int GetFirstItem() /*const*/;
			virtual float GetFirstItemOffset() /*const*/;

			virtual int GetPressItem() /*const*/;

			virtual void ScrollIncrease(int nItems, float fAccel=1000.0f);
			virtual void ScrollDecrease(int nItems, float fAccel=1000.0f);

			virtual void ScrollDistance(float fDistance, float fAccel=1000.0f);

			virtual void StopScroll();

			virtual bool IsScrolling() /*const*/;
			virtual bool IsPointerActive() /*const*/;

			virtual void LimitScrollItems(int nItems);

			//BaseTrack methods
			virtual void OnPointerPress(const nb::System::Point &point);
			virtual void OnPointerMove(const nb::System::Point &point);
			virtual void OnPointerRelease(const nb::System::Point &point);

		private:
			void OnScrollCtrlerScroll(nb::Gui::ReboundScrollCtrler::ScrollEventParam &param);
			void OnScrollCtrlerScrollEnd(nb::Gui::ReboundScrollCtrler::ScrollEndEventParam &param);
			void OnScrollCtrlerFirstItemChanged(nb::Gui::ReboundScrollCtrler::FirstItemChangedEventParam &param);
		private:
			LineMultiItemsTrack *m_owner;
			ReboundScrollCtrlerPtr m_pRSC;
			//ILineMultiItemsTrackHandleEvent *m_pEvent;
			int m_nLimitScrollItems;
		};
	}
}
