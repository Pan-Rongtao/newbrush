#pragma once

#include "PageBase.h"

using namespace nb;

enum ERRORID
{
	ERROR_ID_TERMINATE = 0,
	ERROR_ID_PAUSED_OBSTACLE,
	ERROR_ID_CONTINUE_OBSTACLE,
	ERROR_ID_PAUSED_DOOR_UNLOCKED,
	ERROR_ID_CONTINUE
};

class PageParking : public PageBase
{
	using PageBase::PageBase;
public:
	PageParking(const Rect &rc, NBPageID id);
	PageParking(float x, float y, float w, float h, NBPageID id);
	void onBtnClicked(const EventArgs &arg);

	void onTick(const EventArgs &arg);
protected:
	void init();
	void popup(ERRORID id);
	void popdown();
private:
	ref<nb::Timer> m_failed;
	ref<nb::Timer> m_success;
	ref<nb::Timer> m_paused;

	ref<Button> m_back;
	ref<TextBlock> m_type;
	ref<Node2D> m_seperator;
	ref<TextBlock> m_name;
	ref<TextBlock> m_status;

	ref<Node2D> m_tipbg;
	ref<TextBlock> m_distance;
	ref<TextBlock> m_length;

	ref<Node2D> m_houshiview;
	ref<Node2D> m_road;
	ref<Node2D> m_space1;
	ref<Node2D> m_space2;
	ref<Node2D> m_parkposition;
	ref<Node2D> m_car;

	ref<Node2D> m_pop;
	ref<TextBlock> m_poptitle;
	ref<TextBlock> m_popcontent;
	ref<Button> m_continue;
	ref<Node2D> m_recttext;
	ref<TextBlock> m_btntext;

	ref<Node2D> m_radarview;
	ref<Node2D> m_downsection1;
	ref<Node2D> m_downsection2;
	ref<Node2D> m_downsection3;
	ref<Node2D> m_downsection4;
	ref<Node2D> m_downsection5;
	ref<Node2D> m_downsection6;
	ref<Node2D> m_upsection1;
	ref<Node2D> m_upsection2;
	ref<Node2D> m_upsection3;
	ref<Node2D> m_upsection4;
	ref<Node2D> m_upsection5;
	ref<Node2D> m_upsection6;
	ref<Node2D> m_carsmall;
	ref<Node2D> m_subline;
	ref<Node2D> m_roadsmall;
	ref<Node2D> m_space1small;
	ref<Node2D> m_space2small;
	ref<Node2D> m_parkpositionsmall;

	ref<Node2D> m_videomask;
};