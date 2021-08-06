#include "PageNewRouteParkIn.h"

PageNewRouteParkIn::PageNewRouteParkIn(const Rect &rc, NBPageID id)
	: PageBase(rc, id)
{
	init();
}
PageNewRouteParkIn::PageNewRouteParkIn(float x, float y, float w, float h, NBPageID id)
	: PageBase(x, y, w, h, id)
{
	init();
}

void PageNewRouteParkIn::init()
{
	PageBase::init();
	//To Do the followings:
	//1. init Nodes
	//2. build DataTree
	//3. Others
	clearChildren();
	startpoint_driving();
	startpoint_stop();
	startpoint_fail();
	startpoint_sucess();
	endpoint_stop_first();
	endpoint_driving_d();
	endpoint_driving_r();
	endpoint_stop_second();
	endpoint_saving();
	endpoint_saved_fail();
	endpoint_saved_sucess();
	route_saving();
	route_delete();
	m_routeinid = ROUTEIN_ID_STARTPOINT_DRIVING;
	m_btnback = Button::createWithTextureFrameName("memory", "icon_back.png", true, 49.0f, 168.0f);
	m_btnback->Click += nbBindEventFunction(PageNewRouteParkIn::onBtnClicked);
	setBackground(SolidColorBrush::white());
	m_root = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);
	m_root = m_startpoint_driving;
	addChild(m_root);
	addChild(m_btnback);

}

void PageNewRouteParkIn::onBtnClicked(const EventArgs &arg)
{
	if (arg.sender == m_btnback.get())
	{
		onTriggerSwitchPage(this, NB_PAGEID_MEMORY_PARKING_ROUTE_SELECTION);
	}
	else if (arg.sender == m_btnsetend.get())
	{
	}
	else if (arg.sender == m_btnfixedparktype.get())
	{
	}
	else if (arg.sender == m_btnpassingdparktype.get())
	{
	}
	else if (arg.sender == m_btnsaveroute.get())
	{
	}
	else if (arg.sender == m_btndeleteroute.get())
	{
	}
}

void PageNewRouteParkIn::onTick(const EventArgs &arg)
{
}

void PageNewRouteParkIn::onDataChanged(std::string &path, var &value)
{
}

void PageNewRouteParkIn::onTouch(const TouchEventArgs & e)
{
	if (e.action != TouchActionE::down)
		return;
	switch (m_routeinid)
	{
	case ROUTEIN_ID_STARTPOINT_DRIVING:
		m_routeinid = ROUTEIN_ID_STARTPOINT_STOP;
		m_root->clearChildren();
		m_root->addChild(m_startpoint_stop);
		break;
	case ROUTEIN_ID_STARTPOINT_STOP:
		m_routeinid = ROUTEIN_ID_STARTPOINT_FAIL;
		m_root->clearChildren();
		m_root->addChild(m_startpoint_fail);
		break;
	case ROUTEIN_ID_STARTPOINT_FAIL:
		m_routeinid = ROUTEIN_ID_STARTPOINT_SUCESS;
		m_root->clearChildren();
		m_root->addChild(m_startpoint_sucess);
		break;
	case ROUTEIN_ID_STARTPOINT_SUCESS:
		m_routeinid = ROUTEIN_ID_ENDPOINT_STOP_FIRST;
		m_root->clearChildren();
		m_root->addChild(m_endpoint_stop_first);
		break;
	case ROUTEIN_ID_ENDPOINT_STOP_FIRST:
		m_routeinid = ROUTEIN_ID_ENDPOINT_DRIVING_D;
		m_root->clearChildren();
		m_root->addChild(m_endpoint_driving_d);
		break;
	case ROUTEIN_ID_ENDPOINT_DRIVING_D:
		m_routeinid = ROUTEIN_ID_ENDPOINT_DRIVING_R;
		m_root->clearChildren();
		m_root->addChild(m_endpoint_driving_r);
		break;
	case ROUTEIN_ID_ENDPOINT_DRIVING_R:
		m_routeinid = ROUTEIN_ID_ENDPOINT_STOP_SECOND;
		m_root->clearChildren();
		m_root->addChild(m_endpoint_stop_second);
		break;
	case ROUTEIN_ID_ENDPOINT_STOP_SECOND:
		m_routeinid = ROUTEIN_ID_ENDPOINT_SAVING;
		m_root->clearChildren();
		m_root->addChild(m_endpoint_saving);
		break;
	case ROUTEIN_ID_ENDPOINT_SAVING:
		m_routeinid = ROUTEIN_ID_ENDPOINT_SAVED_FAIL;
		m_root->clearChildren();
		m_root->addChild(m_endpoint_saved_fail);
		break;
	case ROUTEIN_ID_ENDPOINT_SAVED_FAIL:
		m_routeinid = ROUTEIN_ID_ENDPOINT_SAVED_SUCESS;
		m_root->clearChildren();
		m_root->addChild(m_endpoint_saved_sucess);
		break;
	case ROUTEIN_ID_ENDPOINT_SAVED_SUCESS:
		m_routeinid = ROUTEIN_ID_ROUTE_SAVING;
		m_root->clearChildren();
		m_root->addChild(m_route_saving);
		break;
	case ROUTEIN_ID_ROUTE_SAVING:
		m_routeinid = ROUTEIN_ID_ROUTE_DELETE;
		m_root->clearChildren();
		m_root->addChild(m_route_delete);
		break;
	case ROUTEIN_ID_ROUTE_DELETE:
		m_routeinid = ROUTEIN_ID_ROUTE_DELETE;
		m_root->clearChildren();
		m_root->addChild(m_route_delete);
		break;
	default:
		;
	}
}

void PageNewRouteParkIn::startpoint_driving()
{
	m_startpoint_driving = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);
	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_startpoint_driving->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_startpoint_driving->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置入库起点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_startpoint_driving->addChild(txttitle);

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
	m_startpoint_driving->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 请停车后，设置当前位置为路线起点 ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_startpoint_driving->addChild(txtcontent);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_startpoint_driving->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_stop.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_startpoint_driving->addChild(stopicon);

	auto road = createRef<Node2D>(218.0f, 438.0f, 156.0f, 500.0f);
	auto texroad = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_road.png");
	road->setBackground(createRef<ImageBrush>(texroad));
	m_startpoint_driving->addChild(road);

	auto car = createRef<Node2D>(70.0f, 666.0f, 450.0f, 240.0f);
	auto texcar = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_car02.png");
	car->setBackground(createRef<ImageBrush>(texcar));
	m_startpoint_driving->addChild(car);
}

void PageNewRouteParkIn::startpoint_stop()
{
	m_startpoint_stop = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);
	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_startpoint_stop->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_startpoint_stop->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置入库起点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_startpoint_stop->addChild(txttitle);

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
	m_startpoint_stop->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 正在设置为起点，请稍后…… ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_startpoint_stop->addChild(txtcontent);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_startpoint_stop->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_stop.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_startpoint_stop->addChild(stopicon);

	auto road = createRef<Node2D>(218.0f, 438.0f, 156.0f, 500.0f);
	auto texroad = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_road.png");
	road->setBackground(createRef<ImageBrush>(texroad));
	m_startpoint_stop->addChild(road);

	auto car = createRef<Node2D>(70.0f, 666.0f, 450.0f, 240.0f);
	auto texcar = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_car02.png");
	car->setBackground(createRef<ImageBrush>(texcar));
	m_startpoint_stop->addChild(car);

	auto loadingicon = createRef<Node2D>(220.0f, 666.0f, 150.0f, 150.0f);
	auto texlodingicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_loading_blue_150px.png");
	loadingicon->setBackground(createRef<ImageBrush>(texlodingicon));
	m_startpoint_stop->addChild(loadingicon);
}

void PageNewRouteParkIn::startpoint_fail()
{
	m_startpoint_fail = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);
	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_startpoint_fail->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_startpoint_fail->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置入库起点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_startpoint_fail->addChild(txttitle);

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
	m_startpoint_fail->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 正在设置为起点，请稍后…… ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_startpoint_fail->addChild(txtcontent);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_startpoint_fail->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_stop.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_startpoint_fail->addChild(stopicon);

	auto road = createRef<Node2D>(218.0f, 438.0f, 156.0f, 500.0f);
	auto texroad = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_road.png");
	road->setBackground(createRef<ImageBrush>(texroad));
	m_startpoint_fail->addChild(road);

	auto car = createRef<Node2D>(70.0f, 666.0f, 450.0f, 240.0f);
	auto texcar = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_car02.png");
	car->setBackground(createRef<ImageBrush>(texcar));
	m_startpoint_fail->addChild(car);
}

void PageNewRouteParkIn::startpoint_sucess()
{
	m_startpoint_sucess = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_startpoint_sucess->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_startpoint_sucess->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置入库起点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_startpoint_sucess->addChild(txttitle);

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
	m_startpoint_sucess->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 起点设置成功 ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_startpoint_sucess->addChild(txtcontent);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_startpoint_sucess->addChild(displayright);
}

void PageNewRouteParkIn::endpoint_stop_first()
{
	m_endpoint_stop_first = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_stop_first->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_stop_first->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置入库终点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_endpoint_stop_first->addChild(txttitle);

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
	m_endpoint_stop_first->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 平缓向前行驶(<15km/h),并将车泊入 ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_endpoint_stop_first->addChild(txtcontent);
	auto txtcontent1 = createRef<TextBlock>(u8" 您常用的停车位(距离起点<150米)。 ");
	txtcontent1->setColor(Color(0, 0, 0, 255));
	txtcontent1->setPosition(Point(69.0f, 340.0f));
	m_endpoint_stop_first->addChild(txtcontent1);

	auto txtlimit = createRef<TextBlock>(u8" 终点<150米 ");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_endpoint_stop_first->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_endpoint_stop_first->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_endpoint_stop_first->addChild(stopicon);

	auto road = createRef<Node2D>(218.0f, 438.0f, 156.0f, 500.0f);
	auto texroad = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_road.png");
	road->setBackground(createRef<ImageBrush>(texroad));
	m_endpoint_stop_first->addChild(road);

	auto park0 = createRef<Node2D>(350.0f, 500.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	m_endpoint_stop_first->addChild(park0);

	auto park1 = createRef<Node2D>(100.0f, 600.0f, 148.0f, 256.0f);
	auto texpark1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces2.png");
	park1->setBackground(createRef<ImageBrush>(texpark1));
	m_endpoint_stop_first->addChild(park1);

	auto car0 = createRef<Node2D>(260.0f, 750.0f, 70.0f, 180.0f);
	auto texcar0 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car0->setBackground(createRef<ImageBrush>(texcar0));
	m_endpoint_stop_first->addChild(car0);

	auto car1 = createRef<Node2D>(450.0f, 550.0f, 70.0f, 180.0f);
	auto texcar1 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car1->setBackground(createRef<ImageBrush>(texcar1));
	car1->setTransform(createRef<RotateTransform2D>(90.0f, 50.0f, 50.0f));
	m_endpoint_stop_first->addChild(car1);

	auto car2 = createRef<Node2D>(120.0f, 645.0f, 70.0f, 180.0f);
	auto texcar2 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car2->setBackground(createRef<ImageBrush>(texcar2));
	m_endpoint_stop_first->addChild(car2);
}

void PageNewRouteParkIn::endpoint_driving_d()
{
	m_endpoint_driving_d = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_driving_d->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_driving_d->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置入库终点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_endpoint_driving_d->addChild(txttitle);

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
	m_endpoint_driving_d->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 请将车泊入您常用的停车位。 ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_endpoint_driving_d->addChild(txtcontent);
	auto txtcontent1 = createRef<TextBlock>(u8" 停车后，点击下方按键设置终点。 ");
	txtcontent1->setColor(Color(0, 0, 0, 255));
	txtcontent1->setPosition(Point(69.0f, 340.0f));
	m_endpoint_driving_d->addChild(txtcontent1);

	auto txtlimit = createRef<TextBlock>(u8" 终点<150米 ");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_endpoint_driving_d->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_endpoint_driving_d->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_endpoint_driving_d->addChild(stopicon);

	auto road = createRef<Node2D>(218.0f, 438.0f, 156.0f, 500.0f);
	auto texroad = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_road.png");
	road->setBackground(createRef<ImageBrush>(texroad));
	m_endpoint_driving_d->addChild(road);

	auto park0 = createRef<Node2D>(350.0f, 650.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	m_endpoint_driving_d->addChild(park0);

	auto park1 = createRef<Node2D>(100.0f, 700.0f, 148.0f, 256.0f);
	auto texpark1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces2.png");
	park1->setBackground(createRef<ImageBrush>(texpark1));
	m_endpoint_driving_d->addChild(park1);

	auto car = createRef<Node2D>(95.0f, 520.0f, 400.0f, 220.0f);
	auto texcar = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_car02.png");
	car->setBackground(createRef<ImageBrush>(texcar));
	m_endpoint_driving_d->addChild(car);
}

void PageNewRouteParkIn::endpoint_driving_r()
{
	m_endpoint_driving_r = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_driving_r->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_driving_r->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置入库终点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_endpoint_driving_r->addChild(txttitle);

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
	m_endpoint_driving_r->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 请将车泊入您常用的停车位。 ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_endpoint_driving_r->addChild(txtcontent);
	auto txtcontent1 = createRef<TextBlock>(u8" 停车后，点击下方按键设置终点。 ");
	txtcontent1->setColor(Color(0, 0, 0, 255));
	txtcontent1->setPosition(Point(69.0f, 340.0f));
	m_endpoint_driving_r->addChild(txtcontent1);

	auto txtlimit = createRef<TextBlock>(u8" 终点<150米 ");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_endpoint_driving_r->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_endpoint_driving_r->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_endpoint_driving_r->addChild(stopicon);

	auto road = createRef<Node2D>(218.0f, 438.0f, 156.0f, 500.0f);
	auto texroad = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_road.png");
	road->setBackground(createRef<ImageBrush>(texroad));
	m_endpoint_driving_r->addChild(road);

	auto park0 = createRef<Node2D>(350.0f, 650.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	m_endpoint_driving_r->addChild(park0);

	auto park1 = createRef<Node2D>(100.0f, 700.0f, 148.0f, 256.0f);
	auto texpark1 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces2.png");
	park1->setBackground(createRef<ImageBrush>(texpark1));
	m_endpoint_driving_r->addChild(park1);

	auto car0 = createRef<Node2D>(260.0f, 750.0f, 70.0f, 180.0f);
	auto texcar0 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car0->setBackground(createRef<ImageBrush>(texcar0));
	m_endpoint_driving_r->addChild(car0);
}

void PageNewRouteParkIn::endpoint_stop_second()
{
	m_endpoint_stop_second = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);
	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_stop_second->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_stop_second->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置入库终点");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_endpoint_stop_second->addChild(txttitle);

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
	m_endpoint_stop_second->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8"请点击下方按键,设置终点。");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_endpoint_stop_second->addChild(txtcontent);

	auto txtlimit = createRef<TextBlock>(u8" 终点<150米 ");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_endpoint_stop_second->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_endpoint_stop_second->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_endpoint_stop_second->addChild(stopicon);

	auto park0 = createRef<Node2D>(293.0f, 630.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	park0->setTransform(createRef<RotateTransform2D>(90.0f, 50.0f, 50.0f));
	m_endpoint_stop_second->addChild(park0);

	auto car0 = createRef<Node2D>(255.0f, 650.0f, 100.0f, 220.0f);
	auto texcar0 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car0->setBackground(createRef<ImageBrush>(texcar0));
	m_endpoint_stop_second->addChild(car0);

	auto btnsetendbg = createRef<Node2D>(180.0f, 858.0f, 240.0f, 62.0f);
	auto texsetendbg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_62px_nor1.png");
	btnsetendbg->setBackground(createRef<ImageBrush>(texsetendbg));
	auto txtsetend = createRef<TextBlock>(u8" 设为终点 ");
	txtsetend->setColor(Color(0, 0, 0, 255));
	txtsetend->setPosition(Point(238.0f, 873.0f));
	m_btnsetend = createRef<Button>(180.0f, 858.0f, 240.0f, 62.0f);
	m_btnsetend->Click += nbBindEventFunction(PageNewRouteParkIn::onBtnClicked);
	m_endpoint_stop_second->addChild(btnsetendbg);
	m_endpoint_stop_second->addChild(txtsetend);
	m_endpoint_stop_second->addChild(m_btnsetend);
}

void PageNewRouteParkIn::endpoint_saving()
{
	m_endpoint_saving = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_saving->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_saving->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置入库终点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_endpoint_saving->addChild(txttitle);

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
	m_endpoint_saving->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 正在设置为终点，请稍后…… ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_endpoint_saving->addChild(txtcontent);

	auto txtlimit = createRef<TextBlock>(u8" 终点<150米 ");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_endpoint_saving->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_endpoint_saving->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_endpoint_saving->addChild(stopicon);

	auto park0 = createRef<Node2D>(293.0f, 630.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	park0->setTransform(createRef<RotateTransform2D>(90.0f, 50.0f, 50.0f));
	m_endpoint_saving->addChild(park0);

	auto car0 = createRef<Node2D>(255.0f, 650.0f, 100.0f, 220.0f);
	auto texcar0 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car0->setBackground(createRef<ImageBrush>(texcar0));
	m_endpoint_saving->addChild(car0);

	auto loadingicon = createRef<Node2D>(230.0f, 666.0f, 150.0f, 150.0f);
	auto texlodingicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_loading_blue_150px.png");
	loadingicon->setBackground(createRef<ImageBrush>(texlodingicon));
	m_endpoint_saving->addChild(loadingicon);
}

void PageNewRouteParkIn::endpoint_saved_fail()
{
	m_endpoint_saved_fail = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_saved_fail->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_saved_fail->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 设置入库终点 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_endpoint_saved_fail->addChild(txttitle);

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
	m_endpoint_saved_fail->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8" 设置中，请稍后…… ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_endpoint_saved_fail->addChild(txtcontent);

	auto txtlimit = createRef<TextBlock>(u8" 终点<150米 ");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_endpoint_saved_fail->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_endpoint_saved_fail->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_endpoint_saved_fail->addChild(stopicon);

	auto park0 = createRef<Node2D>(293.0f, 630.0f, 234.0f, 178.0f);
	auto texpark0 = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parking_spaces.png");
	park0->setBackground(createRef<ImageBrush>(texpark0));
	park0->setTransform(createRef<RotateTransform2D>(90.0f, 50.0f, 50.0f));
	m_endpoint_saved_fail->addChild(park0);

	auto car0 = createRef<Node2D>(255.0f, 650.0f, 100.0f, 220.0f);
	auto texcar0 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_pic_car.png");
	car0->setBackground(createRef<ImageBrush>(texcar0));
	m_endpoint_saved_fail->addChild(car0);
}

void PageNewRouteParkIn::endpoint_saved_sucess()
{
	m_endpoint_saved_sucess = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_saved_sucess->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_endpoint_saved_sucess->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8"设置入库终点");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_endpoint_saved_sucess->addChild(txttitle);

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
	m_endpoint_saved_sucess->addChild(bar);

	auto txtcontent = createRef<TextBlock>(u8"终点设置成功");
	txtcontent->setColor(Color(0, 0, 0, 255));
	txtcontent->setPosition(Point(69.0f, 298.0f));
	m_endpoint_saved_sucess->addChild(txtcontent);

	auto txtlimit = createRef<TextBlock>(u8"终点<150米");
	txtlimit->setColor(Color(0, 0, 0, 255));
	txtlimit->setPosition(Point(400.0f, 430.0f));
	m_endpoint_saved_sucess->addChild(txtlimit);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_endpoint_saved_sucess->addChild(displayright);

	auto stopicon = createRef<Node2D>(47.0f, 441.0f, 100.0f, 100.0f);
	auto texstopicon = TextureLibrary::getFrameFromTextureAtlas("memory", "icon_speedalert.png");
	stopicon->setBackground(createRef<ImageBrush>(texstopicon));
	m_endpoint_saved_sucess->addChild(stopicon);
}

void PageNewRouteParkIn::route_saving()
{
	m_route_saving = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_route_saving->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_route_saving->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 保存入库路线 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_route_saving->addChild(txttitle);

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
	m_route_saving->addChild(bar);

	auto container = createRef<Node2D>(69.0f, 298.0f, 200.0f, 10.0f);
	auto txtcontent = createRef<TextBlock>(u8" 路线名称 ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	container->addChild(txtcontent);
	txtcontent->setHorizontalAlignment(HorizontalAlignmentE::Left);
	//txtcontent->setPosition(Point(69.0f, 298.0f));
	m_route_saving->addChild(container);

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
	m_route_saving->addChild(txteditbg);

	auto txthomebg = createRef<Node2D>(69.0f, 430.0f, 151.0f, 42.0f);
	auto texhomebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_42px_nor.png");
	txthomebg->setBackground(createRef<ImageBrush>(texhomebg));
	auto txthomename = createRef<TextBlock>(u8" 温暖的家 ");
	txthomename->setRect({ 0,0,100,30 });
	txthomename->setColor(Color(0, 0, 0, 255));
	txthomename->setHorizontalAlignment(HorizontalAlignmentE::Left);
	txthomename->setVerticalAlignment(VerticalAlignmentE::Center);
	txthomebg->addChild(txthomename);
	m_route_saving->addChild(txthomebg);

	auto txtcompanybg = createRef<Node2D>(230.0f, 430.0f, 175.0f, 42.0f);
	auto texcompanybg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_42px_nor.png");
	txtcompanybg->setBackground(createRef<ImageBrush>(texcompanybg));
	auto txtcompanyname = createRef<TextBlock>(u8" 奋斗的公司 ");
	txtcompanyname->setRect({ 0,0,100,30 });
	txtcompanyname->setColor(Color(0, 0, 0, 255));
	txtcompanyname->setHorizontalAlignment(HorizontalAlignmentE::Left);
	txtcompanyname->setVerticalAlignment(VerticalAlignmentE::Center);
	txtcompanybg->addChild(txtcompanyname);
	m_route_saving->addChild(txtcompanybg);

	auto txthomebg1 = createRef<Node2D>(415.0f, 430.0f, 110.0f, 42.0f);
	auto texhomebg1 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_42px_nor.png");
	txthomebg1->setBackground(createRef<ImageBrush>(texhomebg1));
	auto txthomename1 = createRef<TextBlock>(u8" 家 ");
	txthomename1->setRect({ 0,0,50,30 });
	txthomename1->setColor(Color(0, 0, 0, 255));
	txthomename1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	txthomename1->setVerticalAlignment(VerticalAlignmentE::Center);
	txthomebg1->addChild(txthomename1);
	m_route_saving->addChild(txthomebg1);

	auto txparktype = createRef<TextBlock>(u8" 车位类型 ");
	txparktype->setColor(Color(0, 0, 0, 255));
	txparktype->setPosition(Point(69.0f, 505.0f));
	m_route_saving->addChild(txparktype);

	m_fixedparktypebg = createRef<Node2D>(69.0f, 557.0f, 216.0f, 360.0f);
	auto texfixedparktypebg = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parkingspace1.png");
	m_fixedparktypebg->setBackground(createRef<ImageBrush>(texfixedparktypebg));
	m_btnfixedparktype = createRef<Button>(69.0f, 557.0f, 216.0f, 360.0f);
	m_btnfixedparktype->Click += nbBindEventFunction(PageNewRouteParkIn::onBtnClicked);
	m_fixedparktypebg->addChild(m_btnfixedparktype);
	m_txtfixedparktype = createRef<TextBlock>(u8"  固定车位  ");
	m_txtfixedparktype->setPosition(Point(28.0f,239.0f));
	m_fixedparktypebg->addChild(m_txtfixedparktype);
	m_route_saving->addChild(m_fixedparktypebg);

	m_passingparktypebg = createRef<Node2D>(315.0f, 557.0f, 216.0f, 360.0f);
	auto texpassingparktypebg = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parkingspace2.png");
	m_passingparktypebg->setBackground(createRef<ImageBrush>(texpassingparktypebg));
	m_btnpassingdparktype = createRef<Button>(315.0f, 557.0f, 216.0f, 360.0f);
	m_btnpassingdparktype->Click += nbBindEventFunction(PageNewRouteParkIn::onBtnClicked);
	m_passingparktypebg->addChild(m_btnpassingdparktype);
	m_txtpassingparktype = createRef<TextBlock>(u8"  途径车位  ");
	m_txtpassingparktype->setPosition(Point(28.0f, 239.0f));
	m_passingparktypebg->addChild(m_txtpassingparktype);
	m_route_saving->addChild(m_passingparktypebg);
	
	m_saveroutebg = createRef<Node2D>(88.0f, 920.0f, 180.0f, 56.0f);
	auto texsaveroutebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_56px_sel.png");
	m_saveroutebg->setBackground(createRef<ImageBrush>(texsaveroutebg));
	m_btnsaveroute = createRef<Button>(88.0f, 920.0f, 180.0f, 56.0f);
	m_btnsaveroute->Click += nbBindEventFunction(PageNewRouteParkIn::onBtnClicked);
	m_saveroutebg->addChild(m_btnsaveroute);
	m_txtsaveroute = createRef<TextBlock>(u8"  保存  ");
	m_txtsaveroute->setPosition(Point(45.0f, 11.0f));
	m_saveroutebg->addChild(m_txtsaveroute);
	m_route_saving->addChild(m_saveroutebg);

	m_deleteroutebg = createRef<Node2D>(330.0f, 920.0f, 180.0f, 56.0f);
	auto texdeleteroutebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_56px_sel.png");
	m_deleteroutebg->setBackground(createRef<ImageBrush>(texdeleteroutebg));
	m_btndeleteroute = createRef<Button>(330.0f, 920.0f, 180.0f, 56.0f);
	m_btndeleteroute->Click += nbBindEventFunction(PageNewRouteParkIn::onBtnClicked);
	m_deleteroutebg->addChild(m_btndeleteroute);
	m_txtdeleteroute = createRef<TextBlock>(u8"删除路线");
	m_txtdeleteroute->setPosition(Point(25.0f, 11.0f));
	m_deleteroutebg->addChild(m_txtdeleteroute);
	m_route_saving->addChild(m_deleteroutebg);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_route_saving->addChild(displayright);
}

void PageNewRouteParkIn::route_delete()
{
	m_route_delete = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);

	auto topbg = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	topbg->setBackground(SolidColorBrush::ghostWhite());
	m_route_delete->addChild(topbg);
	auto bottombg = createRef<Node2D>(0.0f, 980.0f, 1920.0f, 112.0f);
	bottombg->setBackground(SolidColorBrush::ghostWhite());
	m_route_delete->addChild(bottombg);

	auto txttitle = createRef<TextBlock>(u8" 保存入库路线 ");
	txttitle->setColor(Color(0, 0, 0, 255));
	txttitle->setPosition(Point(165.0f, 182.0f));
	m_route_delete->addChild(txttitle);

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
	m_route_delete->addChild(bar);

	auto container = createRef<Node2D>(69.0f, 298.0f, 200.0f, 10.0f);
	auto txtcontent = createRef<TextBlock>(u8" 路线名称 ");
	txtcontent->setColor(Color(0, 0, 0, 255));
	container->addChild(txtcontent);
	txtcontent->setHorizontalAlignment(HorizontalAlignmentE::Left);
	//txtcontent->setPosition(Point(69.0f, 298.0f));
	m_route_delete->addChild(container);

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
	m_route_delete->addChild(txteditbg);

	auto txthomebg = createRef<Node2D>(69.0f, 430.0f, 151.0f, 42.0f);
	auto texhomebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_42px_nor.png");
	txthomebg->setBackground(createRef<ImageBrush>(texhomebg));
	auto txthomename = createRef<TextBlock>(u8" 温暖的家 ");
	txthomename->setRect({ 0,0,100,30 });
	txthomename->setColor(Color(0, 0, 0, 255));
	txthomename->setHorizontalAlignment(HorizontalAlignmentE::Left);
	txthomename->setVerticalAlignment(VerticalAlignmentE::Center);
	txthomebg->addChild(txthomename);
	m_route_delete->addChild(txthomebg);

	auto txtcompanybg = createRef<Node2D>(230.0f, 430.0f, 175.0f, 42.0f);
	auto texcompanybg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_42px_nor.png");
	txtcompanybg->setBackground(createRef<ImageBrush>(texcompanybg));
	auto txtcompanyname = createRef<TextBlock>(u8" 奋斗的公司 ");
	txtcompanyname->setRect({ 0,0,100,30 });
	txtcompanyname->setColor(Color(0, 0, 0, 255));
	txtcompanyname->setHorizontalAlignment(HorizontalAlignmentE::Left);
	txtcompanyname->setVerticalAlignment(VerticalAlignmentE::Center);
	txtcompanybg->addChild(txtcompanyname);
	m_route_delete->addChild(txtcompanybg);

	auto txthomebg1 = createRef<Node2D>(415.0f, 430.0f, 110.0f, 42.0f);
	auto texhomebg1 = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_42px_nor.png");
	txthomebg1->setBackground(createRef<ImageBrush>(texhomebg1));
	auto txthomename1 = createRef<TextBlock>(u8" 家 ");
	txthomename1->setRect({ 0,0,50,30 });
	txthomename1->setColor(Color(0, 0, 0, 255));
	txthomename1->setHorizontalAlignment(HorizontalAlignmentE::Center);
	txthomename1->setVerticalAlignment(VerticalAlignmentE::Center);
	txthomebg1->addChild(txthomename1);
	m_route_delete->addChild(txthomebg1);

	auto txparktype = createRef<TextBlock>(u8" 车位类型 ");
	txparktype->setColor(Color(0, 0, 0, 255));
	txparktype->setPosition(Point(69.0f, 505.0f));
	m_route_delete->addChild(txparktype);

	m_fixedparktypebg = createRef<Node2D>(69.0f, 557.0f, 216.0f, 360.0f);
	auto texfixedparktypebg = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parkingspace1.png");
	m_fixedparktypebg->setBackground(createRef<ImageBrush>(texfixedparktypebg));
	m_btnfixedparktype = createRef<Button>(69.0f, 557.0f, 216.0f, 360.0f);
	m_btnfixedparktype->Click += nbBindEventFunction(PageNewRouteParkIn::onBtnClicked);
	m_fixedparktypebg->addChild(m_btnfixedparktype);
	m_txtfixedparktype = createRef<TextBlock>(u8"  固定车位  ");
	m_txtfixedparktype->setPosition(Point(28.0f, 239.0f));
	m_fixedparktypebg->addChild(m_txtfixedparktype);
	m_route_delete->addChild(m_fixedparktypebg);

	m_passingparktypebg = createRef<Node2D>(315.0f, 557.0f, 216.0f, 360.0f);
	auto texpassingparktypebg = TextureLibrary::getFrameFromTextureAtlas("memory", "pic_parkingspace2.png");
	m_passingparktypebg->setBackground(createRef<ImageBrush>(texpassingparktypebg));
	m_btnpassingdparktype = createRef<Button>(315.0f, 557.0f, 216.0f, 360.0f);
	m_btnpassingdparktype->Click += nbBindEventFunction(PageNewRouteParkIn::onBtnClicked);
	m_passingparktypebg->addChild(m_btnpassingdparktype);
	m_txtpassingparktype = createRef<TextBlock>(u8"  途径车位  ");
	m_txtpassingparktype->setPosition(Point(28.0f, 239.0f));
	m_passingparktypebg->addChild(m_txtpassingparktype);
	m_route_delete->addChild(m_passingparktypebg);

	m_saveroutebg = createRef<Node2D>(88.0f, 920.0f, 180.0f, 56.0f);
	auto texsaveroutebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_56px_sel.png");
	m_saveroutebg->setBackground(createRef<ImageBrush>(texsaveroutebg));
	m_btnsaveroute = createRef<Button>(88.0f, 920.0f, 180.0f, 56.0f);
	m_btnsaveroute->Click += nbBindEventFunction(PageNewRouteParkIn::onBtnClicked);
	m_saveroutebg->addChild(m_btnsaveroute);
	m_txtsaveroute = createRef<TextBlock>(u8"  保存  ");
	m_txtsaveroute->setPosition(Point(45.0f, 11.0f));
	m_saveroutebg->addChild(m_txtsaveroute);
	m_route_delete->addChild(m_saveroutebg);

	m_deleteroutebg = createRef<Node2D>(330.0f, 920.0f, 180.0f, 56.0f);
	auto texdeleteroutebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_56px_sel.png");
	m_deleteroutebg->setBackground(createRef<ImageBrush>(texdeleteroutebg));
	m_btndeleteroute = createRef<Button>(330.0f, 920.0f, 180.0f, 56.0f);
	m_btndeleteroute->Click += nbBindEventFunction(PageNewRouteParkIn::onBtnClicked);
	m_deleteroutebg->addChild(m_btndeleteroute);
	m_txtdeleteroute = createRef<TextBlock>(u8"删除路线");
	m_txtdeleteroute->setPosition(Point(25.0f, 11.0f));
	m_deleteroutebg->addChild(m_txtdeleteroute);
	m_route_delete->addChild(m_deleteroutebg);

	auto displayright = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	auto rightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	displayright->setBackground(createRef<ImageBrush>(rightpbg));
	m_route_delete->addChild(displayright);

	auto grayforeground = createRef<Node2D>(0.0f, 100.0f, 610.0f, 900.0f);
	grayforeground->setBackground(SolidColorBrush::ghostWhite());
	grayforeground->setOpacity(0.6);
	m_route_delete->addChild(grayforeground);

	auto popdialogbg = createRef<Node2D>(70.0f, 500.0f, 460.0f, 250.0f);
	popdialogbg->setBackground(createRef<SolidColorBrush>(Color(50.0, 50.0, 50.0, 205.0)));
	m_route_delete->addChild(popdialogbg);
	auto seperator0 = createRef<Node2D>(0.0, 160.0, 460.0, 2.0);
	seperator0->setBackground(createRef<SolidColorBrush>(Color(229.0, 232.0, 235.0, 255.0)));
	popdialogbg->addChild(seperator0);
	auto seperator1 = createRef<Node2D>(230.0, 160.0, 2.0, 90.0);
	seperator1->setBackground(createRef<SolidColorBrush>(Color(229.0, 232.0, 235.0, 255.0)));
	popdialogbg->addChild(seperator1);
	auto popdialogtxtcontent = createRef<TextBlock>(u8"是否删除该路线?");
	popdialogtxtcontent->setPosition(Point(110, 60));
	popdialogtxtcontent->setColor(Color(255, 255, 255, 255));
	popdialogbg->addChild(popdialogtxtcontent);

	auto nodebtncancel = createRef<Node2D>(0.0, 160.0, 230.0, 90.0);
	m_btnpopdialogcancel = createRef<Button>(0.0, 160.0, 230.0, 90.0);
	m_btnpopdialogcancel->Click += nbBindEventFunction(PageNewRouteParkIn::onBtnClicked);
	nodebtncancel->addChild(m_btnpopdialogcancel);
	auto popdialogtxtcancel = createRef<TextBlock>(u8"取消");
	popdialogtxtcancel->setPosition(Point(80, 30));
	popdialogtxtcancel->setColor(Color(255, 255, 255, 255));
	nodebtncancel->addChild(popdialogtxtcancel);
	popdialogbg->addChild(nodebtncancel);

	auto nodebtndelete = createRef<Node2D>(230.0, 160.0, 230.0, 90.0);
	m_btnpopdialogdelete = createRef<Button>(230.0, 160.0, 230.0, 90.0);
	m_btnpopdialogdelete->Click += nbBindEventFunction(PageNewRouteParkIn::onBtnClicked);
	nodebtndelete->addChild(m_btnpopdialogdelete);
	auto popdialogtxtdelete = createRef<TextBlock>(u8"删除");
	popdialogtxtdelete->setPosition(Point(80, 30));
	popdialogtxtdelete->setColor(Color(255, 255, 255, 255));
	nodebtndelete->addChild(popdialogtxtdelete);
	popdialogbg->addChild(nodebtndelete);
}