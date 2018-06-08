#pragma once

#include "ContentControl.h"

#include "gui/LineMultiItemsTrack.h" // 暂时使用

namespace nb { namespace Gui {

	class ScrollViewerInternal;
	class NB_EXPORT ScrollViewer : public ContentControl
	{
	public:
		ScrollViewer(void);
		virtual ~ScrollViewer(void);

		ScrollViewerInternal * GetInternal() const {return m_internal;}

		void ScrollToVerticalOffset(float offset);

	protected:
		float GetExtraRenderOffsetX() const;
		float GetExtraRenderOffsetY() const;

		virtual System::Size MeasureOverride(const System::Size &availableSize) {return System::Size(0, 0);}

		virtual void OnActualSizeChanged();

	private:
//		void On_LineMultItemsTrack_Move(ILineMultiItemsTrackHandle *pTrack, int nFirstItem, float fItemOffset, nb::Gui::ReboundScrollCtrler::EnumWorkMode nOrientation);

		void OnTrackMove(LineMultiItemsTrack::TrackMoveEventParam &pas);

	private:
		ScrollViewerInternal * m_internal;
		float m_verticalOffset;
	};

	typedef nbObjectPtrDerive<ScrollViewer, ContentControlPtr> ScrollViewerPtr;

}}
