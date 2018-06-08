#pragma once
#include "BaseTrack.h"
#include "core/Event.h"



namespace nb
{
	namespace Gui
	{
		enum TrackOrientation
		{
			TrackOrientation_Hor = 0x00,
			TrackOrientation_Vert,
			TrackOrientation_All
		};
		//class ISVPLineMultiItemsTrackHandleEvent;
		class LineMultiItemsTrackPrivate;
		class NB_GUI_DECLSPEC_INTERFACE LineMultiItemsTrack : public BaseTrack
		{
			NB_OBJECT_TYPE_DECLARE();

		public:
			class TrackMoveEventParam : public nbEventParamT<LineMultiItemsTrack>
			{
			public:
				int m_nFirstItem;
				float m_fFirstItemOffset;
				nb::Gui::TrackOrientation m_nTrackOrientation;
			};
			nbEvent<TrackMoveEventParam> TrackMoveEvent;

			class TrackMoveEndEventParam : public nbEventParamT<LineMultiItemsTrack>
			{
			};
			nbEvent<TrackMoveEndEventParam> TrackMoveEndEvent;
			
			class TrackFirstItemChangedEventParam : public nbEventParamT<LineMultiItemsTrack>
			{
			public:
				int m_nOldFirstItem;
				int m_nNewFirstItem;
			};
			nbEvent<TrackFirstItemChangedEventParam> TrackFirstItemChangedEvent;

			class PointerMoveEventParam : public nbEventParamT<LineMultiItemsTrack>
			{
			public:
				nb::System::Point m_ptPosition;
			};
			nbEvent<PointerMoveEventParam> PointerMoveEvent;

			class PointerReleasedEventParam : public nbEventParamT<LineMultiItemsTrack>
			{
			public:
				nb::System::Point m_ptPosition;
			};
			nbEvent<PointerReleasedEventParam> PointerReleasedEvent;

		public:

			LineMultiItemsTrack();
			virtual ~LineMultiItemsTrack();
			LineMultiItemsTrackPrivate *GetPrivate();

			//ILineMultiItemsTrackHandle Interfaces			
			//ILineMultiItemsTrackHandleEvent *SetEventInterface(ILineMultiItemsTrackHandleEvent *pEvent);

			void SetOrientation(nb::Gui::TrackOrientation nTrackOrientation = nb::Gui::TrackOrientation_Vert);
			void SetItemCount(int nCount);
			int GetItemCount() /*const*/;
			void SetItemSize(int nSize);
			int GetItemSize() /*const*/;
			void SetPageSize(int nSize);
			int GetPageSize() /*const*/;
			void SetFirstItem(int nItem);
			void SetFirstItemOffset(float fOffset);
			void ZeroItemOffset();
			void SetAccel(float fAccel);
			void SetMaxSpeed(float fSpeed);
			void SetHoldBackSpeed(float fSpeed);
			void SetReboundAccel(float fAccel);

			void SetCycMode(bool bCycMode);

			int GetFirstItem() /*const*/;
			float GetFirstItemOffset() /*const*/;

			int GetPressItem() /*const*/;

			void ScrollIncrease(int nItems, float fAccel=1000.0f);
			void ScrollDecrease(int nItems, float fAccel=1000.0f);

			void ScrollDistance(float fDistance, float fAccel=1000.0f);

			void StopScroll();

			bool IsScrolling() /*const*/;
			bool IsPointerActive() /*const*/;

			void TrackEnable(bool bEnable);

			void SetMonopolizePointer(bool bMonopolizePointer);

			void LimitScrollItems(int nItems);

			//BaseTrack methods
			virtual void OnPointerPress(const nb::System::Point &point);
			virtual void OnPointerMove(const nb::System::Point &point);
			virtual void OnPointerRelease(const nb::System::Point &point);


		public:
			void On_LineMultiItemsTrack_Move(int nFirstItem, float fFirstItemOffset, nb::Gui::TrackOrientation nTrackOrientation);
			void On_LineMultiItemsTrack_End();
			void On_LineMultiItemsTrack_FirstItemChanged(int nNewFirstItem, int nOldFirstItem);

		private:
			LineMultiItemsTrackPrivate *m_private;
		};
		typedef nbObjectPtrDerive<LineMultiItemsTrack, BaseTrackPtr> LineMultiItemsTrackPtr;
	}
}
