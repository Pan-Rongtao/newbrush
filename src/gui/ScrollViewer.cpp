#include "gui/ScrollViewer.h"
#include "ElementRender.h"
#include "UIElementPrivate.h"

#include "gui/LineMultiItemsTrack.h"

using namespace nb::Gui;

namespace nb { namespace Gui {

	class ScrollViewerInternal : public IElementRender
	{
	public:
		ScrollViewerInternal(ScrollViewer *owner) : m_owner(owner)
		{
			Window *win = ((UIElement *)m_owner)->GetPrivate()->GetWindow();
		}

		virtual void OnRender(float x, float y)
		{
		}

	private:
		ScrollViewer *m_owner;
	};

}}

ScrollViewer::ScrollViewer(void)
: m_verticalOffset(0)
{
	m_internal = new ScrollViewerInternal(this);

	LineMultiItemsTrack *pTrack = new LineMultiItemsTrack();
	pTrack->SetItemCount(1);
	pTrack->SetItemSize(1000);
	pTrack->SetPageSize(400);
	//pTrack->SetAccel(1000);

//	pTrack->SetEventInterface(this);

	pTrack->TrackMoveEvent.Add(this, &ScrollViewer::OnTrackMove);

	SetTrack(pTrack);
}

ScrollViewer::~ScrollViewer(void)
{
	delete m_internal;
}

float ScrollViewer::GetExtraRenderOffsetX() const
{
	return 0;
}

float ScrollViewer::GetExtraRenderOffsetY() const
{
	return m_verticalOffset;
}

void ScrollViewer::ScrollToVerticalOffset(float offset)
{
	m_verticalOffset = offset;
}

//void ScrollViewer::On_LineMultItemsTrack_Move(ILineMultiItemsTrackHandle *pTrack, int nFirstItem, float fItemOffset, nb::Gui::ReboundScrollCtrler::EnumWorkMode nOrientation)
//{
//	ScrollToVerticalOffset(fItemOffset);
//}

void ScrollViewer::OnTrackMove(LineMultiItemsTrack::TrackMoveEventParam &pas)
{
	ScrollToVerticalOffset(pas.m_fFirstItemOffset);
}

void ScrollViewer::OnActualSizeChanged()
{
	float w = GetActualWidth();
	float h = GetActualHeight();

	LineMultiItemsTrack *pTrack = (LineMultiItemsTrack *)GetTrack();

	if(Content != NULL)
	{
		pTrack->SetItemSize(Content->GetActualHeight());
		
	}
	else
	{
		pTrack->SetItemSize(h);
	}

	UIElement *content = Content;

	pTrack->SetPageSize(h);
}
