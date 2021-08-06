#include "PageNewRouteParkOut.h"

PageNewRouteParkOut::PageNewRouteParkOut(const Rect &rc, NBPageID id)
	: PageBase(rc, id)
{
	init();
}
PageNewRouteParkOut::PageNewRouteParkOut(float x, float y, float w, float h, NBPageID id)
	: PageBase(x, y, w, h, id)
{
	init();
}

void PageNewRouteParkOut::init()
{
	PageBase::init();
	//To Do the followings:
	//1. init Nodes
	//2. build DataTree
	//3. Others
	clearChildren();
	m_routeoutid = ROUTEOUT_ID_STARTPOINT_DRIVING;
	m_btnback = Button::createWithTextureFrameName("memory", "icon_back.png", true, 49.0f, 168.0f);
	m_btnback->Click += nbBindEventFunction(PageNewRouteParkOut::onBtnClicked);
	setBackground(SolidColorBrush::white());
	m_root = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);
	startpoint_driving();
	addChild(m_root);
	addChild(m_btnback);
}

void PageNewRouteParkOut::onBtnClicked(const EventArgs &arg)
{
	if (arg.sender == m_btnback.get())
	{
		onTriggerSwitchPage(this, NB_PAGEID_MEMORY_PARKING_ROUTE_SELECTION);
	}
	else if (arg.sender == m_btnsetend.get())
	{
	}
	else if (arg.sender == m_btnsaveroute.get())
	{
	}
	else if (arg.sender == m_btndeleteroute.get())
	{
	}
}

void PageNewRouteParkOut::onTick(const EventArgs &arg)
{
}

void PageNewRouteParkOut::onDataChanged(std::string &path, var &value)
{
}

void PageNewRouteParkOut::onTouch(const TouchEventArgs & e)
{
	if (e.action != TouchActionE::down)
		return;
	switch (m_routeoutid)
	{
	case ROUTEOUT_ID_STARTPOINT_DRIVING:
		m_routeoutid = ROUTEOUT_ID_STARTPOINT_STOP;
		startpoint_stop();
		break;
	case ROUTEOUT_ID_STARTPOINT_STOP:
		m_routeoutid = ROUTEOUT_ID_STARTPOINT_FAIL;
		startpoint_fail();
		break;
	case ROUTEOUT_ID_STARTPOINT_FAIL:
		m_routeoutid = ROUTEOUT_ID_STARTPOINT_SUCESS;
		startpoint_sucess();
		break;
	case ROUTEOUT_ID_STARTPOINT_SUCESS:
		m_routeoutid = ROUTEOUT_ID_ENDPOINT_STOP_FIRST;
		endpoint_stop_first();
		break;
	case ROUTEOUT_ID_ENDPOINT_STOP_FIRST:
		m_routeoutid = ROUTEOUT_ID_ENDPOINT_DRIVING_D;
		endpoint_driving_d();
		break;
	case ROUTEOUT_ID_ENDPOINT_DRIVING_D:
		m_routeoutid = ROUTEOUT_ID_ENDPOINT_DRIVING_R;
		endpoint_driving_r();
		break;
	case ROUTEOUT_ID_ENDPOINT_DRIVING_R:
		m_routeoutid = ROUTEOUT_ID_ENDPOINT_STOP_SECOND;
		endpoint_stop_second();
		break;
	case ROUTEOUT_ID_ENDPOINT_STOP_SECOND:
		m_routeoutid = ROUTEOUT_ID_ENDPOINT_SAVING;
		endpoint_saving();
		break;
	case ROUTEOUT_ID_ENDPOINT_SAVING:
		m_routeoutid = ROUTEOUT_ID_ENDPOINT_SAVED_FAIL;
		endpoint_saved_fail();
		break;
	case ROUTEOUT_ID_ENDPOINT_SAVED_FAIL:
		m_routeoutid = ROUTEOUT_ID_ENDPOINT_SAVED_SUCESS;
		endpoint_saved_sucess();
		break;
	case ROUTEOUT_ID_ENDPOINT_SAVED_SUCESS:
		m_routeoutid = ROUTEOUT_ID_ROUTE_SAVING;
		route_saving();
		break;
	case ROUTEOUT_ID_ROUTE_SAVING:
		m_routeoutid = ROUTEOUT_ID_ROUTE_DELETE;
		route_delete();
		break;
	case ROUTEOUT_ID_ROUTE_DELETE:
		m_routeoutid = ROUTEOUT_ID_ROUTE_DELETE;
		route_delete();
		break;
	default:
		;
	}
}

void PageNewRouteParkOut::startpoint_driving()
{
	m_root->clearChildren();

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8"设置出库起点");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_root->addChild(txttitle);

	auto bar = createRef<Node2D>(60.0f, 242.0f, 465.0f, 15.0f);
	auto texFrame0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_sel.png");
	auto texFrame1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_nor.png");
	auto bar0 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar0->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar1 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar1->setBackground(createRef<ImageBrush>(texFrame1));
	auto bar2 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar2->setBackground(createRef<ImageBrush>(texFrame1));
	bar->addChild(bar0);
	bar->addChild(bar1);
	bar->addChild(bar2);
	bar0->setHorizontalAlignment(HorizontalAlignmentE::Left);
	bar1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bar2->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_root->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8"请停车后,设置当前位置为路线起点");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_root->addChild(txtcontent);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_root->addChild(displayright);

	auto stopicon = createRef<Node2D>(100.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_stop.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_root->addChild(stopicon);

	auto park0 = createRef<Node2D>(293.0f, 530.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	park0->setTransform(createRef<RotateTransform2D>(90.0f, 50.0f, 50.0f));
	m_root->addChild(park0);

	auto car0 = createRef<Node2D>(255.0f, 550.0f, 100.0f, 220.0f);
	auto texcar0 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car0->setBackground(createRef<ImageBrush>(texcar0));
	m_root->addChild(car0);

	auto txtrouteoutstartpoint = createRef<TextBlock>(u8"出库起点");
	txtrouteoutstartpoint->setColor(Color(0, 0, 0, 255));
	txtrouteoutstartpoint->setPosition(Point(240.0f, 760.0f));
	m_root->addChild(txtrouteoutstartpoint);
}

void PageNewRouteParkOut::startpoint_stop()
{
	m_root->clearChildren();

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8"设置出库起点");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_root->addChild(txttitle);

	auto bar = createRef<Node2D>(60.0f, 242.0f, 465.0f, 15.0f);
	auto texFrame0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_sel.png");
	auto texFrame1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_nor.png");
	auto bar0 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar0->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar1 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar1->setBackground(createRef<ImageBrush>(texFrame1));
	auto bar2 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar2->setBackground(createRef<ImageBrush>(texFrame1));
	bar->addChild(bar0);
	bar->addChild(bar1);
	bar->addChild(bar2);
	bar0->setHorizontalAlignment(HorizontalAlignmentE::Left);
	bar1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bar2->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_root->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8"设置中,请稍后……");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_root->addChild(txtcontent);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_root->addChild(displayright);

	auto stopicon = createRef<Node2D>(100.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_stop.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_root->addChild(stopicon);

	auto park0 = createRef<Node2D>(293.0f, 530.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	park0->setTransform(createRef<RotateTransform2D>(90.0f, 50.0f, 50.0f));
	m_root->addChild(park0);

	auto car0 = createRef<Node2D>(255.0f, 550.0f, 100.0f, 220.0f);
	auto texcar0 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car0->setBackground(createRef<ImageBrush>(texcar0));
	m_root->addChild(car0);

	auto txtrouteoutstartpoint = createRef<TextBlock>(u8"出库起点");
	txtrouteoutstartpoint->setColor(Color(0, 0, 0, 255));
	txtrouteoutstartpoint->setPosition(Point(240.0f, 760.0f));
	m_root->addChild(txtrouteoutstartpoint);

	auto loadingicon = createRef<Node2D>(228.0f, 580.0f, 150.0f, 150.0f);
	auto texlodingicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_loading_blue_150px.png");
	loadingicon->setBackground(createRef<ImageBrush>(texlodingicon));
	m_root->addChild(loadingicon);
}

void PageNewRouteParkOut::startpoint_fail()
{
	m_root->clearChildren();

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8"设置出库起点");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_root->addChild(txttitle);

	auto bar = createRef<Node2D>(60.0f, 242.0f, 465.0f, 15.0f);
	auto texFrame0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_sel.png");
	auto texFrame1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_nor.png");
	auto bar0 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar0->setBackground(SolidColorBrush::red());
	auto bar1 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar1->setBackground(createRef<ImageBrush>(texFrame1));
	auto bar2 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar2->setBackground(createRef<ImageBrush>(texFrame1));
	bar->addChild(bar0);
	bar->addChild(bar1);
	bar->addChild(bar2);
	bar0->setHorizontalAlignment(HorizontalAlignmentE::Left);
	bar1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bar2->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_root->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8"请停车后,设置当前位置为路线起点");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_root->addChild(txtcontent);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_root->addChild(displayright);

	auto stopicon = createRef<Node2D>(100.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_stop.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_root->addChild(stopicon);

	auto park0 = createRef<Node2D>(293.0f, 530.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	park0->setTransform(createRef<RotateTransform2D>(90.0f, 50.0f, 50.0f));
	m_root->addChild(park0);

	auto car0 = createRef<Node2D>(255.0f, 550.0f, 100.0f, 220.0f);
	auto texcar0 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car0->setBackground(createRef<ImageBrush>(texcar0));
	m_root->addChild(car0);

	auto txtrouteoutstartpoint = createRef<TextBlock>(u8"出库起点");
	txtrouteoutstartpoint->setColor(Color(0, 0, 0, 255));
	txtrouteoutstartpoint->setPosition(Point(240.0f, 760.0f));
	m_root->addChild(txtrouteoutstartpoint);
}

void PageNewRouteParkOut::startpoint_sucess()
{
	m_root->clearChildren();

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置出库起点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_root->addChild(txttitle);

	auto bar = createRef<Node2D>(60.0f, 242.0f, 465.0f, 15.0f);
	auto texFrame0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_sel.png");
	auto texFrame1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_nor.png");
	auto bar0 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar0->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar1 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar1->setBackground(createRef<ImageBrush>(texFrame1));
	auto bar2 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar2->setBackground(createRef<ImageBrush>(texFrame1));
	bar->addChild(bar0);
	bar->addChild(bar1);
	bar->addChild(bar2);
	bar0->setHorizontalAlignment(HorizontalAlignmentE::Left);
	bar1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bar2->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_root->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 起点设置成功 ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_root->addChild(txtcontent);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_root->addChild(displayright);
}

void PageNewRouteParkOut::endpoint_stop_first()
{
	m_root->clearChildren();

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置出库终点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_root->addChild(txttitle);

	auto bar = createRef<Node2D>(60.0f, 242.0f, 465.0f, 15.0f);
	auto texFrame0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_sel.png");
	auto texFrame1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_nor.png");
	auto bar0 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar0->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar1 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar1->setBackground(createRef<ImageBrush>(texFrame1));
	auto bar2 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar2->setBackground(createRef<ImageBrush>(texFrame1));
	bar->addChild(bar0);
	bar->addChild(bar1);
	bar->addChild(bar2);
	bar0->setHorizontalAlignment(HorizontalAlignmentE::Left);
	bar1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bar2->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_root->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8"平缓向前行驶(<15km/h),至您方便的");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_root->addChild(txtcontent);
	auto txtcontent1 = createRef<TextBlock>(u8"上车点(距离起点<150米)后,停车设置。");
	txtcontent1->setColor(Color(0, 0, 0, 255));
	txtcontent1->setPosition(Point(69.0f, 340.0f));
	m_root->addChild(txtcontent1);

	auto txtlimit = createRef<TextBlock>(u8" 终点<150米 ");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_root->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_root->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_root->addChild(stopicon);

	auto road = createRef<Node2D>(218.0f, 438.0f, 156.0f, 500.0f);
	auto texroad = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_road.png");
	road->setBackground(createRef<ImageBrush>(texroad));
	m_root->addChild(road);

	auto park0 = createRef<Node2D>(150.0f, 800.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setTransform(createRef<RotateTransform2D>(180.0f, 50.0f, 50.0f));
	park0->setBackground(createRef<ImageBrush>(texpark0));
	m_root->addChild(park0);

	auto car0 = createRef<Node2D>(120.0f, 775.0f, 70.0f, 180.0f);
	auto texcar0 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car0->setTransform(createRef<RotateTransform2D>(90.0f, 50.0f, 50.0f));
	car0->setBackground(createRef<ImageBrush>(texcar0));
	m_root->addChild(car0);
}

void PageNewRouteParkOut::endpoint_driving_d()
{
	m_root->clearChildren();

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置出库终点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_root->addChild(txttitle);

	auto bar = createRef<Node2D>(60.0f, 242.0f, 465.0f, 15.0f);
	auto texFrame0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_sel.png");
	auto texFrame1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_nor.png");
	auto bar0 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar0->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar1 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar1->setBackground(createRef<ImageBrush>(texFrame1));
	auto bar2 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar2->setBackground(createRef<ImageBrush>(texFrame1));
	bar->addChild(bar0);
	bar->addChild(bar1);
	bar->addChild(bar2);
	bar0->setHorizontalAlignment(HorizontalAlignmentE::Left);
	bar1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bar2->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_root->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 请将车停到您方便的上车点。 ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_root->addChild(txtcontent);
	auto txtcontent1 = createRef<TextBlock>(u8" 停车后，点击下方按键设置终点。 ");
	txtcontent1->setColor(Color(0, 0, 0, 255));
	txtcontent1->setPosition(Point(69.0f, 340.0f));
	m_root->addChild(txtcontent1);

	auto txtlimit = createRef<TextBlock>(u8" 终点<150米 ");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_root->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_root->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_root->addChild(stopicon);

	auto road = createRef<Node2D>(218.0f, 438.0f, 156.0f, 500.0f);
	auto texroad = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_road.png");
	road->setBackground(createRef<ImageBrush>(texroad));
	m_root->addChild(road);

	auto park0 = createRef<Node2D>(350.0f, 650.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	m_root->addChild(park0);

	auto park1 = createRef<Node2D>(100.0f, 700.0f, 148.0f, 256.0f);
	auto texpark1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces2.png");
	park1->setBackground(createRef<ImageBrush>(texpark1));
	m_root->addChild(park1);

	auto car = createRef<Node2D>(95.0f, 520.0f, 400.0f, 220.0f);
	auto texcar = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_car02.png");
	car->setBackground(createRef<ImageBrush>(texcar));
	m_root->addChild(car);
}

void PageNewRouteParkOut::endpoint_driving_r()
{
	m_root->clearChildren();

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置出库终点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_root->addChild(txttitle);

	auto bar = createRef<Node2D>(60.0f, 242.0f, 465.0f, 15.0f);
	auto texFrame0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_sel.png");
	auto texFrame1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_nor.png");
	auto bar0 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar0->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar1 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar1->setBackground(createRef<ImageBrush>(texFrame1));
	auto bar2 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar2->setBackground(createRef<ImageBrush>(texFrame1));
	bar->addChild(bar0);
	bar->addChild(bar1);
	bar->addChild(bar2);
	bar0->setHorizontalAlignment(HorizontalAlignmentE::Left);
	bar1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bar2->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_root->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 请将车停到您方便的上车点。 ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_root->addChild(txtcontent);
	auto txtcontent1 = createRef<TextBlock>(u8" 停车后，点击下方按键设置终点。 ");
	txtcontent1->setColor(Color(0, 0, 0, 255));
	txtcontent1->setPosition(Point(69.0f, 340.0f));
	m_root->addChild(txtcontent1);

	auto txtlimit = createRef<TextBlock>(u8" 终点<150米 ");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_root->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_root->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_root->addChild(stopicon);

	auto road = createRef<Node2D>(218.0f, 438.0f, 156.0f, 500.0f);
	auto texroad = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_road.png");
	road->setBackground(createRef<ImageBrush>(texroad));
	m_root->addChild(road);

	auto park0 = createRef<Node2D>(350.0f, 650.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	m_root->addChild(park0);

	auto park1 = createRef<Node2D>(100.0f, 700.0f, 148.0f, 256.0f);
	auto texpark1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces2.png");
	park1->setBackground(createRef<ImageBrush>(texpark1));
	m_root->addChild(park1);

	auto car0 = createRef<Node2D>(260.0f, 750.0f, 70.0f, 180.0f);
	auto texcar0 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car0->setBackground(createRef<ImageBrush>(texcar0));
	m_root->addChild(car0);
}

void PageNewRouteParkOut::endpoint_stop_second()
{
	m_root->clearChildren();

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置出库终点");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_root->addChild(txttitle);

	auto bar = createRef<Node2D>(60.0f, 242.0f, 465.0f, 15.0f);
	auto texFrame0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_sel.png");
	auto texFrame1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_nor.png");
	auto bar0 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar0->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar1 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar1->setBackground(createRef<ImageBrush>(texFrame1));
	auto bar2 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar2->setBackground(createRef<ImageBrush>(texFrame1));
	bar->addChild(bar0);
	bar->addChild(bar1);
	bar->addChild(bar2);
	bar0->setHorizontalAlignment(HorizontalAlignmentE::Left);
	bar1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bar2->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_root->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8"请点击下方按键,设置终点。");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_root->addChild(txtcontent);

	auto txtlimit = createRef<TextBlock>(u8" 终点<150米 ");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_root->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_root->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_root->addChild(stopicon);

	auto park0 = createRef<Node2D>(293.0f, 630.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	park0->setTransform(createRef<RotateTransform2D>(90.0f, 50.0f, 50.0f));
	m_root->addChild(park0);

	auto car0 = createRef<Node2D>(255.0f, 650.0f, 100.0f, 220.0f);
	auto texcar0 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car0->setBackground(createRef<ImageBrush>(texcar0));
	m_root->addChild(car0);

	auto btnsetendbg = createRef<Node2D>(180.0f, 858.0f, 240.0f, 62.0f);
	auto texsetendbg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_62px_nor1.png");
	btnsetendbg->setBackground(createRef<ImageBrush>(texsetendbg));
	auto txtsetend = createRef<TextBlock>(u8" 设为终点 ");
	txtsetend->setColor(Color(0, 0, 0, 255));
	txtsetend->setPosition(Point(238.0f, 873.0f));
	m_btnsetend = createRef<Button>(180.0f, 858.0f, 240.0f, 62.0f);
	m_btnsetend->Click += nbBindEventFunction(PageNewRouteParkOut::onBtnClicked);
	m_root->addChild(btnsetendbg);
	m_root->addChild(txtsetend);
	m_root->addChild(m_btnsetend);
}

void PageNewRouteParkOut::endpoint_saving()
{
	m_root->clearChildren();

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置出库终点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_root->addChild(txttitle);

	auto bar = createRef<Node2D>(60.0f, 242.0f, 465.0f, 15.0f);
	auto texFrame0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_sel.png");
	auto texFrame1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_nor.png");
	auto bar0 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar0->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar1 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar1->setBackground(createRef<ImageBrush>(texFrame1));
	auto bar2 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar2->setBackground(createRef<ImageBrush>(texFrame1));
	bar->addChild(bar0);
	bar->addChild(bar1);
	bar->addChild(bar2);
	bar0->setHorizontalAlignment(HorizontalAlignmentE::Left);
	bar1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bar2->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_root->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 正在设置为终点，请稍后…… ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_root->addChild(txtcontent);

	auto txtlimit = createRef<TextBlock>(u8" 终点<150米 ");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_root->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_root->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_root->addChild(stopicon);

	auto park0 = createRef<Node2D>(293.0f, 630.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	park0->setTransform(createRef<RotateTransform2D>(90.0f, 50.0f, 50.0f));
	m_root->addChild(park0);

	auto car0 = createRef<Node2D>(255.0f, 650.0f, 100.0f, 220.0f);
	auto texcar0 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car0->setBackground(createRef<ImageBrush>(texcar0));
	m_root->addChild(car0);

	auto loadingicon = createRef<Node2D>(230.0f, 666.0f, 150.0f, 150.0f);
	auto texlodingicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_loading_blue_150px.png");
	loadingicon->setBackground(createRef<ImageBrush>(texlodingicon));
	m_root->addChild(loadingicon);
}

void PageNewRouteParkOut::endpoint_saved_fail()
{
	m_root->clearChildren();

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置出库终点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_root->addChild(txttitle);

	auto bar = createRef<Node2D>(60.0f, 242.0f, 465.0f, 15.0f);
	auto texFrame0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_sel.png");
	auto texFrame1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_nor.png");
	auto bar0 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar0->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar1 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar1->setBackground(SolidColorBrush::red());
	auto bar2 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar2->setBackground(createRef<ImageBrush>(texFrame1));
	bar->addChild(bar0);
	bar->addChild(bar1);
	bar->addChild(bar2);
	bar0->setHorizontalAlignment(HorizontalAlignmentE::Left);
	bar1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bar2->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_root->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 设置中，请稍后…… ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_root->addChild(txtcontent);

	auto txtlimit = createRef<TextBlock>(u8" 终点<150米 ");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_root->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_root->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_root->addChild(stopicon);

	auto park0 = createRef<Node2D>(293.0f, 630.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	park0->setTransform(createRef<RotateTransform2D>(90.0f, 50.0f, 50.0f));
	m_root->addChild(park0);

	auto car0 = createRef<Node2D>(255.0f, 650.0f, 100.0f, 220.0f);
	auto texcar0 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car0->setBackground(createRef<ImageBrush>(texcar0));
	m_root->addChild(car0);
}

void PageNewRouteParkOut::endpoint_saved_sucess()
{
	m_root->clearChildren();

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8"设置出库终点");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_root->addChild(txttitle);

	auto bar = createRef<Node2D>(60.0f, 242.0f, 465.0f, 15.0f);
	auto texFrame0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_sel.png");
	auto texFrame1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_nor.png");
	auto bar0 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar0->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar1 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar1->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar2 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar2->setBackground(createRef<ImageBrush>(texFrame1));
	bar->addChild(bar0);
	bar->addChild(bar1);
	bar->addChild(bar2);
	bar0->setHorizontalAlignment(HorizontalAlignmentE::Left);
	bar1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bar2->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_root->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8"终点设置成功");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_root->addChild(txtcontent);

	auto txtlimit = createRef<TextBlock>(u8"终点<150米");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_root->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_root->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_root->addChild(stopicon);
}

void PageNewRouteParkOut::route_saving()
{
	m_root->clearChildren();

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 保存出库路线 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_root->addChild(txttitle);

	auto bar = createRef<Node2D>(60.0f, 242.0f, 465.0f, 15.0f);
	auto texFrame0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_sel.png");
	auto texFrame1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_nor.png");
	auto bar0 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar0->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar1 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar1->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar2 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar2->setBackground(createRef<ImageBrush>(texFrame1));
	bar->addChild(bar0);
	bar->addChild(bar1);
	bar->addChild(bar2);
	bar0->setHorizontalAlignment(HorizontalAlignmentE::Left);
	bar1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bar2->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_root->addChild(bar);

	auto container = createRef<Node2D>(69.0f, 298.0f, 200.0f, 10.0f);
	auto txtcontent = createRef<TextBlock>(u8" 路线名称 ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	container->addChild(txtcontent);
	txtcontent->setHorizontalAlignment(HorizontalAlignmentE::Left);
	//txtcontent->setPosition(Point(69.0f, 298.0f));
	m_root->addChild(container);

	auto txteditbg = createRef<Node2D>(69.0f, 350.0f, 462.0f, 72.0f);
	txteditbg->setBackground(SolidColorBrush::gray());
	auto deleteicon = TextureLibrary::getFrameFromTextureAtlas("memory", "btn_delete.png");
	auto deletecontrol = createRef<Node2D>(0.0f, 0.0f, 46.0f, 46.0f);
	deletecontrol->setBackground(createRef<ImageBrush>(deleteicon));
	deletecontrol->setHorizontalAlignment(HorizontalAlignmentE::Right);
	deletecontrol->setVerticalAlignment(VerticalAlignmentE::Center);
	txteditbg->addChild(deletecontrol);
	auto txtroutename = createRef<TextBlock>(u8" 温暖的家 ");
	txtroutename->setRect({ 0,0,100,30 });
	txtroutename->setColor(Color(0, 0, 0, 255));
	txtroutename->setHorizontalAlignment(HorizontalAlignmentE::Left);
	txtroutename->setVerticalAlignment(VerticalAlignmentE::Center);
	txteditbg->addChild(txtroutename);
	m_root->addChild(txteditbg);

	auto txthomebg = createRef<Node2D>(69.0f, 430.0f, 151.0f, 42.0f);
	auto texhomebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_42px_nor.png");
	txthomebg->setBackground(createRef<ImageBrush>(texhomebg));
	auto txthomename = createRef<TextBlock>(u8" 温暖的家 ");
	txthomename->setRect({ 0,0,100,30 });
	txthomename->setColor(Color(0, 0, 0, 255));
	txthomename->setHorizontalAlignment(HorizontalAlignmentE::Left);
	txthomename->setVerticalAlignment(VerticalAlignmentE::Center);
	txthomebg->addChild(txthomename);
	m_root->addChild(txthomebg);

	auto txtcompanybg = createRef<Node2D>(230.0f, 430.0f, 175.0f, 42.0f);
	auto texcompanybg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_42px_nor.png");
	txtcompanybg->setBackground(createRef<ImageBrush>(texcompanybg));
	auto txtcompanyname = createRef<TextBlock>(u8" 奋斗的公司 ");
	txtcompanyname->setRect({ 0,0,100,30 });
	txtcompanyname->setColor(Color(0, 0, 0, 255));
	txtcompanyname->setHorizontalAlignment(HorizontalAlignmentE::Left);
	txtcompanyname->setVerticalAlignment(VerticalAlignmentE::Center);
	txtcompanybg->addChild(txtcompanyname);
	m_root->addChild(txtcompanybg);

	auto txthomebg1 = createRef<Node2D>(415.0f, 430.0f, 110.0f, 42.0f);
	auto texhomebg1 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_42px_nor.png");
	txthomebg1->setBackground(createRef<ImageBrush>(texhomebg1));
	auto txthomename1 = createRef<TextBlock>(u8" 家 ");
	txthomename1->setRect({ 0,0,50,30 });
	txthomename1->setColor(Color(0, 0, 0, 255));
	txthomename1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	txthomename1->setVerticalAlignment(VerticalAlignmentE::Center);
	txthomebg1->addChild(txthomename1);
	m_root->addChild(txthomebg1);

	m_saveroutebg = createRef<Node2D>(88.0f, 920.0f, 180.0f, 56.0f);
	auto texsaveroutebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_56px_sel.png");
	m_saveroutebg->setBackground(createRef<ImageBrush>(texsaveroutebg));
	m_btnsaveroute = createRef<Button>(88.0f, 920.0f, 180.0f, 56.0f);
	m_btnsaveroute->Click += nbBindEventFunction(PageNewRouteParkOut::onBtnClicked);
	m_saveroutebg->addChild(m_btnsaveroute);
	m_txtsaveroute = createRef<TextBlock>(u8"  保存  ");
	m_txtsaveroute->setPosition(Point(45.0f, 11.0f));
	m_saveroutebg->addChild(m_txtsaveroute);
	m_root->addChild(m_saveroutebg);

	m_deleteroutebg = createRef<Node2D>(330.0f, 920.0f, 180.0f, 56.0f);
	auto texdeleteroutebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_56px_sel.png");
	m_deleteroutebg->setBackground(createRef<ImageBrush>(texdeleteroutebg));
	m_btndeleteroute = createRef<Button>(330.0f, 920.0f, 180.0f, 56.0f);
	m_btndeleteroute->Click += nbBindEventFunction(PageNewRouteParkOut::onBtnClicked);
	m_deleteroutebg->addChild(m_btndeleteroute);
	m_txtdeleteroute = createRef<TextBlock>(u8"删除路线");
	m_txtdeleteroute->setPosition(Point(25.0f, 11.0f));
	m_deleteroutebg->addChild(m_txtdeleteroute);
	m_root->addChild(m_deleteroutebg);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_root->addChild(displayright);
}

void PageNewRouteParkOut::route_delete()
{
	m_root->clearChildren();

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_root->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 保存出库路线 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_root->addChild(txttitle);

	auto bar = createRef<Node2D>(60.0f, 242.0f, 465.0f, 15.0f);
	auto texFrame0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_sel.png");
	auto texFrame1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_process_nor.png");
	auto bar0 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar0->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar1 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar1->setBackground(createRef<ImageBrush>(texFrame0));
	auto bar2 = createRef<Node2D>(0.0f, 0.0f, 150.0f, 10.0f);
	bar2->setBackground(createRef<ImageBrush>(texFrame1));
	bar->addChild(bar0);
	bar->addChild(bar1);
	bar->addChild(bar2);
	bar0->setHorizontalAlignment(HorizontalAlignmentE::Left);
	bar1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	bar2->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_root->addChild(bar);

	auto container = createRef<Node2D>(69.0f, 298.0f, 200.0f, 10.0f);
	auto txtcontent = createRef<TextBlock>(u8" 路线名称 ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	container->addChild(txtcontent);
	txtcontent->setHorizontalAlignment(HorizontalAlignmentE::Left);
	//txtcontent->setPosition(Point(69.0f, 298.0f));
	m_root->addChild(container);

	auto txteditbg = createRef<Node2D>(69.0f, 350.0f, 462.0f, 72.0f);
	txteditbg->setBackground(SolidColorBrush::gray());
	auto deleteicon = TextureLibrary::getFrameFromTextureAtlas("memory", "btn_delete.png");
	auto deletecontrol = createRef<Node2D>(0.0f, 0.0f, 46.0f, 46.0f);
	deletecontrol->setBackground(createRef<ImageBrush>(deleteicon));
	deletecontrol->setHorizontalAlignment(HorizontalAlignmentE::Right);
	deletecontrol->setVerticalAlignment(VerticalAlignmentE::Center);
	txteditbg->addChild(deletecontrol);
	auto txtroutename = createRef<TextBlock>(u8" 温暖的家 ");
	txtroutename->setRect({ 0,0,100,30 });
	txtroutename->setColor(Color(0, 0, 0, 255));
	txtroutename->setHorizontalAlignment(HorizontalAlignmentE::Left);
	txtroutename->setVerticalAlignment(VerticalAlignmentE::Center);
	txteditbg->addChild(txtroutename);
	m_root->addChild(txteditbg);

	auto txthomebg = createRef<Node2D>(69.0f, 430.0f, 151.0f, 42.0f);
	auto texhomebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_42px_nor.png");
	txthomebg->setBackground(createRef<ImageBrush>(texhomebg));
	auto txthomename = createRef<TextBlock>(u8" 温暖的家 ");
	txthomename->setRect({ 0,0,100,30 });
	txthomename->setColor(Color(0, 0, 0, 255));
	txthomename->setHorizontalAlignment(HorizontalAlignmentE::Left);
	txthomename->setVerticalAlignment(VerticalAlignmentE::Center);
	txthomebg->addChild(txthomename);
	m_root->addChild(txthomebg);

	auto txtcompanybg = createRef<Node2D>(230.0f, 430.0f, 175.0f, 42.0f);
	auto texcompanybg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_42px_nor.png");
	txtcompanybg->setBackground(createRef<ImageBrush>(texcompanybg));
	auto txtcompanyname = createRef<TextBlock>(u8" 奋斗的公司 ");
	txtcompanyname->setRect({ 0,0,100,30 });
	txtcompanyname->setColor(Color(0, 0, 0, 255));
	txtcompanyname->setHorizontalAlignment(HorizontalAlignmentE::Left);
	txtcompanyname->setVerticalAlignment(VerticalAlignmentE::Center);
	txtcompanybg->addChild(txtcompanyname);
	m_root->addChild(txtcompanybg);

	auto txthomebg1 = createRef<Node2D>(415.0f, 430.0f, 110.0f, 42.0f);
	auto texhomebg1 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_42px_nor.png");
	txthomebg1->setBackground(createRef<ImageBrush>(texhomebg1));
	auto txthomename1 = createRef<TextBlock>(u8" 家 ");
	txthomename1->setRect({ 0,0,50,30 });
	txthomename1->setColor(Color(0, 0, 0, 255));
	txthomename1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	txthomename1->setVerticalAlignment(VerticalAlignmentE::Center);
	txthomebg1->addChild(txthomename1);
	m_root->addChild(txthomebg1);

	m_saveroutebg = createRef<Node2D>(88.0f, 920.0f, 180.0f, 56.0f);
	auto texsaveroutebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_56px_sel.png");
	m_saveroutebg->setBackground(createRef<ImageBrush>(texsaveroutebg));
	m_btnsaveroute = createRef<Button>(88.0f, 920.0f, 180.0f, 56.0f);
	m_btnsaveroute->Click += nbBindEventFunction(PageNewRouteParkOut::onBtnClicked);
	m_saveroutebg->addChild(m_btnsaveroute);
	m_txtsaveroute = createRef<TextBlock>(u8"  保存  ");
	m_txtsaveroute->setPosition(Point(45.0f, 11.0f));
	m_saveroutebg->addChild(m_txtsaveroute);
	m_root->addChild(m_saveroutebg);

	m_deleteroutebg = createRef<Node2D>(330.0f, 920.0f, 180.0f, 56.0f);
	auto texdeleteroutebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_56px_sel.png");
	m_deleteroutebg->setBackground(createRef<ImageBrush>(texdeleteroutebg));
	m_btndeleteroute = createRef<Button>(330.0f, 920.0f, 180.0f, 56.0f);
	m_btndeleteroute->Click += nbBindEventFunction(PageNewRouteParkOut::onBtnClicked);
	m_deleteroutebg->addChild(m_btndeleteroute);
	m_txtdeleteroute = createRef<TextBlock>(u8"删除路线");
	m_txtdeleteroute->setPosition(Point(25.0f, 11.0f));
	m_deleteroutebg->addChild(m_txtdeleteroute);
	m_root->addChild(m_deleteroutebg);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_root->addChild(displayright);

	auto grayforeground = createRef<Node2D>(0.0f, 100.0f, 610.0f, 900.0f);
	grayforeground->setBackground(SolidColorBrush::ghostWhite());
	grayforeground->setOpacity(0.6);
	m_root->addChild(grayforeground);

	auto popdialogbg = createRef<Node2D>(70.0f, 500.0f, 460.0f, 250.0f);
	popdialogbg->setBackground(createRef<SolidColorBrush>(Color(50.0, 50.0, 50.0, 205.0)));
	m_root->addChild(popdialogbg);
	auto seperator0 = createRef<Node2D>(0.0, 160.0, 460.0, 2.0);
	seperator0->setBackground(createRef<SolidColorBrush>(Color(229.0, 232.0, 235.0, 255.0)));
	popdialogbg->addChild(seperator0);
	auto seperator1 = createRef<Node2D>(230.0, 160.0, 2.0, 90.0);
	seperator1->setBackground(createRef<SolidColorBrush>(Color(229.0, 232.0, 235.0, 255.0)));
	popdialogbg->addChild(seperator1);
	auto popdialogtxtcontent = createRef<TextBlock>(u8"是否删除该路线?");
	popdialogtxtcontent->setPosition(Point(110,60));
	popdialogtxtcontent->setColor(Color(255,255,255,255));
	popdialogbg->addChild(popdialogtxtcontent);

	auto nodebtncancel = createRef<Node2D>(0.0, 160.0, 230.0, 90.0);
	m_btnpopdialogcancel = createRef<Button>(0.0, 160.0, 230.0, 90.0);
	m_btnpopdialogcancel->Click += nbBindEventFunction(PageNewRouteParkOut::onBtnClicked);
	nodebtncancel->addChild(m_btnpopdialogcancel);
	auto popdialogtxtcancel = createRef<TextBlock>(u8"取消");
	popdialogtxtcancel->setPosition(Point(80, 30));
	popdialogtxtcancel->setColor(Color(255, 255, 255, 255));
	nodebtncancel->addChild(popdialogtxtcancel);
	popdialogbg->addChild(nodebtncancel);

	auto nodebtndelete = createRef<Node2D>(230.0, 160.0, 230.0, 90.0);
	m_btnpopdialogdelete = createRef<Button>(230.0, 160.0, 230.0, 90.0);
	m_btnpopdialogdelete->Click += nbBindEventFunction(PageNewRouteParkOut::onBtnClicked);
	nodebtndelete->addChild(m_btnpopdialogdelete);
	auto popdialogtxtdelete = createRef<TextBlock>(u8"删除");
	popdialogtxtdelete->setPosition(Point(80, 30));
	popdialogtxtdelete->setColor(Color(255, 255, 255, 255));
	nodebtndelete->addChild(popdialogtxtdelete);
	popdialogbg->addChild(nodebtndelete);
}