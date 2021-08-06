#pragma once

#include "PageBase.h"

using namespace nb;

enum RouteOutID
{
	ROUTEOUT_ID_STARTPOINT_DRIVING = 0,
	ROUTEOUT_ID_STARTPOINT_STOP,
	ROUTEOUT_ID_STARTPOINT_FAIL,
	ROUTEOUT_ID_STARTPOINT_SUCESS,
	ROUTEOUT_ID_ENDPOINT_STOP_FIRST,
	ROUTEOUT_ID_ENDPOINT_DRIVING_D,
	ROUTEOUT_ID_ENDPOINT_DRIVING_R,
	ROUTEOUT_ID_ENDPOINT_STOP_SECOND,
	ROUTEOUT_ID_ENDPOINT_SAVING,
	ROUTEOUT_ID_ENDPOINT_SAVED_FAIL,
	ROUTEOUT_ID_ENDPOINT_SAVED_SUCESS,
	ROUTEOUT_ID_ROUTE_SAVING,
	ROUTEOUT_ID_ROUTE_DELETE,
};

class PageNewRouteParkOut : public PageBase
{
	using PageBase::PageBase;
public:
	PageNewRouteParkOut(const Rect &rc, NBPageID id);
	PageNewRouteParkOut(float x, float y, float w, float h, NBPageID id);
	void onBtnClicked(const EventArgs &arg);
	void onTick(const EventArgs &arg);
	void onDataChanged(std::string &path, var &value);
	void onTouch(const TouchEventArgs & e);
protected:
	void init();
private:
	ref<nb::Timer> m_failed;
	ref<nb::Timer> m_successStartPoint;

	ref<Button> m_btnback;
	ref<Node2D> m_root;

	void startpoint_driving();
	void startpoint_stop();
	void startpoint_fail();
	void startpoint_sucess();
	void endpoint_stop_first();
	void endpoint_driving_d();
	void endpoint_driving_r();
	void endpoint_stop_second();
	void endpoint_saving();
	void endpoint_saved_fail();
	void endpoint_saved_sucess();
	void route_saving();
	void route_delete();

	RouteOutID m_routeoutid;
	ref<Button> m_btnsetend;

	ref<Node2D> m_saveroutebg;
	ref<Button> m_btnsaveroute;
	ref<TextBlock> m_txtsaveroute;

	ref<Node2D> m_deleteroutebg;
	ref<Button> m_btndeleteroute;
	ref<TextBlock> m_txtdeleteroute;

	ref<Button> m_btnpopdialogcancel;
	ref<Button> m_btnpopdialogdelete;
};