#include "Thumb.h"
using namespace nb::Gui;


Thumb::Thumb()
{
}

Thumb::~Thumb()
{
}

void Thumb::OnPointerPress(bool &handled)
{
	handled = true;
	DragStartedEventParam param;
	float fThumbX = GetX();
	float fThumbY = GetY();
	/*
	 *在这时设置param.m_fHorizontalOffset和param.m_fVerticalOffset
	 */
	DragStartedEvent.Dispatch(param);
}

void Thumb::OnPointerRelease()
{
	DragCompletedEventParam param;
	param.m_bCanceled = false;
	/*
	 *在这时设置param.m_fHorizontalChange和param.m_fVerticalChange
	 */
	DragCompletedEvent.Dispatch(param);
}

void Thumb::CancelDrag()
{
	DragCompletedEventParam param;
	param.m_bCanceled = true;
	/*
	 *在这时设置param.m_fHorizontalChange和param.m_fVerticalChange
	 */
	DragCompletedEvent.Dispatch(param);
}