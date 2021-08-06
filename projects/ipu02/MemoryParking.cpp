#include "MemoryParking.h"
#include "PageClaim.h"
#include "PageConditionDetection.h"
#include "PageCourse.h"
#include "PageNewRouteParkIn.h"
#include "PageNewRouteParkOut.h"
#include "PageParking.h"
#include "PageRouteSelection.h"

MemoryParking::MemoryParking()
{
	TextureLibrary::addTextureAtlas("memory", RES_DIR"ipu02/memory.png", RES_DIR"ipu02/memory.txt");
	
	float width = 1920.0;
	float height = 1080.0;
	m_claim = createRef<PageClaim>(nb::Rect(0.0, 0.0, width, height), NBPageID::NB_PAGEID_MEMORY_PARKING_CLAIM);
	m_claim->SwitchPageEvent += nbBindEventFunction(MemoryParking::onSwitchPage);
	//m_claim->init();
	m_course = createRef<PageCourse>(nb::Rect(0.0, 0.0, width, height), NBPageID::NB_PAGEID_MEMORY_PARKING_COURSE);
	m_course->SwitchPageEvent += nbBindEventFunction(MemoryParking::onSwitchPage);
	//m_course->init();
	m_conditiondetection = createRef<PageConditionDetection>(nb::Rect(0.0, 0.0, width, height), NBPageID::NB_PAGEID_MEMORY_PARKING_CONDITION_DETECTION);
	m_conditiondetection->SwitchPageEvent += nbBindEventFunction(MemoryParking::onSwitchPage);
	//m_conditiondetection->init();
	m_routeselection = createRef<PageRouteSelection>(nb::Rect(0.0, 0.0, width, height), NBPageID::NB_PAGEID_MEMORY_PARKING_ROUTE_SELECTION);
	m_routeselection->SwitchPageEvent += nbBindEventFunction(MemoryParking::onSwitchPage);
	//m_routeselection->init();
	m_newroutein = createRef<PageNewRouteParkIn>(nb::Rect(0.0, 0.0, width, height), NBPageID::NB_PAGEID_MEMORY_PARKING_IN_NEW_ROUTE);
	m_newroutein->SwitchPageEvent += nbBindEventFunction(MemoryParking::onSwitchPage);
	//m_newroutein->init();
	m_newrouteout = createRef<PageNewRouteParkOut>(nb::Rect(0.0, 0.0, width, height), NBPageID::NB_PAGEID_MEMORY_PARKING_OUT_NEW_ROUTE);
	m_newrouteout->SwitchPageEvent += nbBindEventFunction(MemoryParking::onSwitchPage);
	//m_newrouteout->init();
	m_parking = createRef<PageParking>(nb::Rect(0.0, 0.0, width, height), NBPageID::NB_PAGEID_MEMORY_PARKING);
	m_parking->SwitchPageEvent += nbBindEventFunction(MemoryParking::onSwitchPage);
	//m_parking->init();

	m_topbar = createRef<Node2D>(0.0, 0.0, 1920.0, 100.0);
	m_btnexit = Button::createWithTextureFrameName("memory", "autopark_btn_back.png", true, 40.0f, 27.0f);
	m_topbar->addChild(m_btnexit);
	m_btnexit->Click += nbBindEventFunction(MemoryParking::onBtnClicked);

	m_bottombar = createRef<Node2D>(0.0, 968.0, 1920.0, 112.0);
	m_home = Button::createWithTextureFrameName("memory", "bottom/HOME.png", true, 52.0, 34.0);
	m_bottombar->addChild(m_home);
	m_menu = Button::createWithTextureFrameName("memory", "bottom/ALL MENU.png", true, 194.0, 34.0);
	m_bottombar->addChild(m_menu);
	m_drive = Button::createWithTextureFrameName("memory", "bottom/DRIVE MODE.png", true, 339.0, 34.0);
	m_bottombar->addChild(m_drive);
	m_down0 = Button::createWithTextureFrameName("memory", "bottom/DOWN.png", true, 488.0, 34.0);
	m_bottombar->addChild(m_down0);
	m_up0 = Button::createWithTextureFrameName("memory", "bottom/UP.png", true, 744.0, 34.0);
	m_bottombar->addChild(m_up0);
	m_wind = Button::createWithTextureFrameName("memory", "bottom/WIND.png", true, 852.0, 34.0);
	m_bottombar->addChild(m_wind);
	m_down1 = Button::createWithTextureFrameName("memory", "bottom/DOWN.png", true, 1014.0, 34.0);
	m_bottombar->addChild(m_down1);
	m_up1 = Button::createWithTextureFrameName("memory", "bottom/UP.png", true, 1270.0, 34.0);
	m_bottombar->addChild(m_up1);
	m_winpeople = Button::createWithTextureFrameName("memory", "bottom/WIND_PEOPLE.png", true, 1405.0, 34.0);
	m_bottombar->addChild(m_winpeople);
	m_circule = Button::createWithTextureFrameName("memory", "bottom/CIRCULE.png", true, 1587.0, 34.0);
	m_bottombar->addChild(m_circule);
	m_left = Button::createWithTextureFrameName("memory", "bottom/left.png", true, 1751.0, 34.0);
	m_bottombar->addChild(m_left);
	m_right = Button::createWithTextureFrameName("memory", "bottom/right.png", true, 1812.0, 34.0);
	m_bottombar->addChild(m_right);

	addChild(m_claim);
	addChild(m_course);
	addChild(m_conditiondetection);
	addChild(m_routeselection);
	addChild(m_newroutein);
	addChild(m_newrouteout);
	addChild(m_parking);
	addChild(m_bottombar);
	addChild(m_topbar);
	showPage(NBPageID::NB_PAGEID_MEMORY_PARKING_CLAIM);
}

void MemoryParking::onSwitchPage(const PageBase::SwitchPageEventArgs &args)
{
	showPage(args.m_id);
}

void MemoryParking::showPage(NBPageID id)
{
	int count = childCount();

	std::vector<ref<Node2D>> childs = children();
	ref<Node2D> child;
	bool bPageExist = false;
	for (int i = 0; i < count; i++)
	{
		child = childs.at(i);
		ref<PageBase> page = as<PageBase>(child);
		if (page != NULL)
		{
			NBPageID page_id = page->id();
			if (id == page_id)
			{
				page->setVisibility(VisibilityE::Visible);
				bPageExist = true;
			}
			else
			{
				page->setVisibility(VisibilityE::Hidden);
			}
		}
	}

	if (bPageExist == false)
	{
		Log::warn("Page with id [%d] not exist", id);
	}
}

void MemoryParking::onBtnClicked(const EventArgs &arg)
{
	if (arg.sender == m_btnexit.get())
	{
		MainView::get()->switchView<IntelligentParkingView>();
	}
}