#pragma once

#include "../Common.h"

using namespace nb;
enum NBPageID
{
	NB_PAGEID_MEMORY_PARKING_START = 0,
	NB_PAGEID_MEMORY_PARKING_CLAIM,
	NB_PAGEID_MEMORY_PARKING_COURSE,
	NB_PAGEID_MEMORY_PARKING_ROUTE_SELECTION,
	NB_PAGEID_MEMORY_PARKING_CONDITION_DETECTION,
	NB_PAGEID_MEMORY_PARKING,
	NB_PAGEID_MEMORY_PARKING_IN_NEW_ROUTE,
	NB_PAGEID_MEMORY_PARKING_OUT_NEW_ROUTE,
	NB_PAGEID_MEMORY_PARKING_END
};

class PageBase : public nb::Node2D
{
public:
	PageBase(const Rect &rc, NBPageID id);
	PageBase(float x, float y, float w, float h, NBPageID id);

	NBPageID id();
	void onTriggerSwitchPage(Object *obj,NBPageID id);

	class SwitchPageEventArgs : public EventArgs
	{
	public:
		NBPageID m_id;
	};
	nb::Event<SwitchPageEventArgs> SwitchPageEvent;
protected:
	void init();

protected:
	ref<DataContext> m_data;
	NBPageID m_id;
};