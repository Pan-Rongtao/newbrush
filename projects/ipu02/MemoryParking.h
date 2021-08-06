#pragma once
#include "../Common.h"
#include "PageBase.h"
#include "MainView.h"
#include "IntelligentParkingView.h"

class MemoryParking : public Node2D
{
public:
	MemoryParking();

	void onSwitchPage(const PageBase::SwitchPageEventArgs &args);
	void showPage(NBPageID id);
protected:
	void onBtnClicked(const EventArgs &arg);

private:
	ref<PageBase> m_claim;
	ref<PageBase> m_course;
	ref<PageBase> m_conditiondetection;
	ref<PageBase> m_routeselection;
	ref<PageBase> m_newroutein;
	ref<PageBase> m_newrouteout;
	ref<PageBase> m_parking;

	ref<Button> m_home;
	ref<Button> m_menu;
	ref<Button> m_drive;
	ref<Button> m_down0;
	ref<Button> m_up0;
	ref<Button> m_wind;
	ref<Button> m_down1;
	ref<Button> m_up1;
	ref<Button> m_winpeople;
	ref<Button> m_circule;
	ref<Button> m_left;
	ref<Button> m_right;
	ref<Node2D> m_bottombar;

	ref<Button> m_btnexit;
	ref<Node2D> m_topbar;
};