#pragma once

#include "PageBase.h"

using namespace nb;

enum RouteInID
{
	ROUTEIN_ID_STARTPOINT_DRIVING = 0,
	ROUTEIN_ID_STARTPOINT_STOP,
	ROUTEIN_ID_STARTPOINT_FAIL,
	ROUTEIN_ID_STARTPOINT_SUCESS,
	ROUTEIN_ID_ENDPOINT_STOP_FIRST,
	ROUTEIN_ID_ENDPOINT_DRIVING_D,
	ROUTEIN_ID_ENDPOINT_DRIVING_R,
	ROUTEIN_ID_ENDPOINT_STOP_SECOND,
	ROUTEIN_ID_ENDPOINT_SAVING,
	ROUTEIN_ID_ENDPOINT_SAVED_FAIL,
	ROUTEIN_ID_ENDPOINT_SAVED_SUCESS,
	ROUTEIN_ID_ROUTE_SAVING,
	ROUTEIN_ID_ROUTE_DELETE,
};

class PageNewRouteParkIn : public PageBase
{
	using PageBase::PageBase;
public:
	PageNewRouteParkIn(const Rect &rc, NBPageID id);
	PageNewRouteParkIn(float x, float y, float w, float h, NBPageID id);
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

	RouteInID m_routeinid;
	ref<Button> m_btnsetend;


	ref<Node2D> m_fixedparktypebg;
	ref<Button> m_btnfixedparktype;
	ref<TextBlock> m_txtfixedparktype;

	ref<Node2D> m_passingparktypebg;
	ref<Button> m_btnpassingdparktype;
	ref<TextBlock> m_txtpassingparktype;

	ref<Node2D> m_saveroutebg;
	ref<Button> m_btnsaveroute;
	ref<TextBlock> m_txtsaveroute;

	ref<Node2D> m_deleteroutebg;
	ref<Button> m_btndeleteroute;
	ref<TextBlock> m_txtdeleteroute;

	ref<Button> m_btnpopdialogcancel;
	ref<Button> m_btnpopdialogdelete;

	ref<Node2D> m_startpoint_driving;
	ref<Node2D> m_startpoint_stop;
	ref<Node2D> m_startpoint_fail;
	ref<Node2D> m_startpoint_sucess;
	ref<Node2D> m_endpoint_stop_first;
	ref<Node2D> m_endpoint_driving_d;
	ref<Node2D> m_endpoint_driving_r;
	ref<Node2D> m_endpoint_stop_second;
	ref<Node2D> m_endpoint_saving;
	ref<Node2D> m_endpoint_saved_fail;
	ref<Node2D> m_endpoint_saved_sucess;
	ref<Node2D> m_route_saving;
	ref<Node2D> m_route_delete;
};				 