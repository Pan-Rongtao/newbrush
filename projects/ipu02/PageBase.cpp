#include "PageBase.h"

PageBase::PageBase(const Rect &rc, NBPageID id)
	: Node2D(rc)
	, m_id(id)
{
}

PageBase::PageBase(float x, float y, float w, float h, NBPageID id)
	: Node2D(x, y, w, h)
	, m_id(id)
{
}

NBPageID PageBase::id()
{
	return m_id;
}

void PageBase::init()
{
}

void PageBase::onTriggerSwitchPage(Object *obj,NBPageID id)
{
	SwitchPageEventArgs e;
	e.sender = obj;
	e.m_id = id;
	SwitchPageEvent.invoke(e);
}