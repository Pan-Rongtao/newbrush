#include "PageParking.h"

PageParking::PageParking(const Rect &rc, NBPageID id)
	: PageBase(rc, id)
{
	init();
}
PageParking::PageParking(float x, float y, float w, float h, NBPageID id)
	: PageBase(x, y, w, h, id)
{
	init();
}

void PageParking::init()
{
	PageBase::init();
	//To Do the followings:
	//1. init Nodes
	//2. build DataTree
	//3. Others
	BrushLibrary::addImageBrush("carsmall", RES_DIR"ipu02/memory/autopark_pic_car_small.png");
	m_back = Button::createWithTextureFrameName("memory", "icon_back.png", true, 49.0, 168.0);
	m_back->setName("back");
	m_back->Click += nbBindEventFunction(PageParking::onBtnClicked);
	m_type = createRef<TextBlock>(155.0, 168.0 + 12.0, 92.0, 60.0);
	m_type->setText(u8"入库");
	m_seperator = createRef<Node2D>(257.0, 181.0, 3.0, 34.0);
	m_seperator->setBackground(createRef<SolidColorBrush>(Color(204.0, 204.0, 204.0, 255.0)));
	m_name = createRef<TextBlock>(280.0, 168.0 + 12.0, 270.0, 60.0);
	m_name->setText(u8"温暖的家");
	m_status = createRef<TextBlock>(69.0, 274.0 + 51.0, 462.0, 138.0);
	m_status->setText(u8"记忆泊车中，请稍候......");

	m_tipbg = Node2D::createWithTextureFrameName("memory", "dialog3_nor.png", true, 153.0, 463.0);
	m_tipbg->setRect(Rect(153.0, 463.0, 306.0, 96.0));
	m_distance = createRef<TextBlock>(20.0, 20.0 + 8.0 + 2.0, 76.0, 40.0);
	m_distance->setText(u8"90米");
	m_tipbg->addChild(m_distance);
	auto seperator = createRef<Node2D>(101.0, 21.0, 2.0, 54.0);
	seperator->setBackground(createRef<SolidColorBrush>(Color(229.0, 232.0, 235.0, 255.0)));
	m_tipbg->addChild(seperator);
	m_length = createRef<TextBlock>(118.0, 32.0, 125.0, 32.0);
	m_length->setText(u8"终点=150米");
	m_tipbg->addChild(m_length);


	m_houshiview = createRef<Node2D>(0.0, 438.0, 600.0, 500.0);
	addChild(m_houshiview);
	m_road = Node2D::createWithTextureFrameName("memory", "pic_parking_road.png", true, 222.0, /*438.0 + */0.0);
	m_car = Node2D::createWithTextureFrameName("memory", "autopark_pic_car.png", true, 230.0, /*438.0 + */180.0);
	m_space1 = Node2D::createWithTextureFrameName("memory", "pic_parking_spaces.png", true, 350.0, /*438.0 + */144.0);
	m_space2 = Node2D::createWithTextureFrameName("memory", "pic_parking_spaces2.png", true, 95.0, /*438.0 + */242.0);
	m_parkposition = Node2D::createWithTextureFrameName("memory", "icon_angelp_sel.png", true, 350.0 + 82.0, /*438.0 + */184.0);
	m_houshiview->addChild(m_road);
	m_houshiview->addChild(m_car);
	m_houshiview->addChild(m_space1);
	m_houshiview->addChild(m_space2);
	m_houshiview->addChild(m_parkposition);


	m_pop = createRef<Node2D>(0.0, 100.0, 600.0, 880.0);
	m_pop->setBackground(createRef<SolidColorBrush>(Color(255.0, 255.0, 255.0, 255.0*0.9)));
	auto title = createRef<Node2D>(60.0, 429.0, 480.0, 60.0);
	m_poptitle = createRef <TextBlock>(0.0, 0.0, 300.0, 60.0);
	m_poptitle->setHorizontalAlignment(HorizontalAlignmentE::Center);
	title->addChild(m_poptitle);
	m_pop->addChild(title);
	auto content = createRef<Node2D>(60.0, 504.0, 480.0, 92.0);
	m_popcontent = createRef<TextBlock>(0.0, 0.0, 480.0, 92.0);
	m_popcontent->setHorizontalAlignment(HorizontalAlignmentE::Center);
	content->addChild(m_popcontent);
	m_pop->addChild(content);
	m_continue = Button::createWithTextureFrameName("memory", "autopark_btn_62px_sel.png");
	m_continue->setRect(Rect(180.0, 756.0, 240.0, 62.0));
	m_continue->setName("continue");
	m_continue->Click += nbBindEventFunction(PageParking::onBtnClicked);
	m_btntext = createRef<TextBlock>(0.0, 13.0, 160.0, 36.0);
	m_btntext->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_recttext = createRef<Node2D>(180.0, 756.0, 240.0, 62.0);
	m_recttext->addChild(m_btntext);
	m_pop->addChild(m_continue);
	m_pop->addChild(m_recttext);


	m_radarview = createRef<Node2D>(0.0, 438.0, 600.0, 500.0);
	m_radarview->setVisibility(VisibilityE::Hidden);
	BrushLibrary::addImageBrush("radar_downsection11", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_reddown_11.png");
	BrushLibrary::addImageBrush("radar_downsection12", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_reddown_12.png");
	BrushLibrary::addImageBrush("radar_downsection13", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_reddown_13.png");
	BrushLibrary::addImageBrush("radar_downsection14", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_reddown_14.png");
	BrushLibrary::addImageBrush("radar_downsection15", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_reddown_15.png");
	BrushLibrary::addImageBrush("radar_downsection16", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_reddown_16.png");
	BrushLibrary::addImageBrush("radar_downsection21", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_reddown_21.png");
	BrushLibrary::addImageBrush("radar_downsection22", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_reddown_22.png");
	BrushLibrary::addImageBrush("radar_downsection23", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_reddown_23.png");
	BrushLibrary::addImageBrush("radar_downsection24", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_reddown_24.png");
	BrushLibrary::addImageBrush("radar_downsection25", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_reddown_25.png");
	BrushLibrary::addImageBrush("radar_downsection26", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_reddown_26.png");
	BrushLibrary::addImageBrush("radar_upsection11", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_redup_11.png");
	BrushLibrary::addImageBrush("radar_upsection12", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_redup_12.png");
	BrushLibrary::addImageBrush("radar_upsection13", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_redup_13.png");
	BrushLibrary::addImageBrush("radar_upsection14", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_redup_14.png");
	BrushLibrary::addImageBrush("radar_upsection15", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_redup_15.png");
	BrushLibrary::addImageBrush("radar_upsection16", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_redup_16.png");
	BrushLibrary::addImageBrush("radar_upsection21", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_redup_21.png");
	BrushLibrary::addImageBrush("radar_upsection22", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_redup_22.png");
	BrushLibrary::addImageBrush("radar_upsection23", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_redup_23.png");
	BrushLibrary::addImageBrush("radar_upsection24", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_redup_24.png");
	BrushLibrary::addImageBrush("radar_upsection25", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_redup_25.png");
	BrushLibrary::addImageBrush("radar_upsection26", RES_DIR"ipu02/memory/radar_topversion/autopark_pic_redup_26.png");
	m_downsection1 = createRef<Node2D>(230.0, /*438.0 + */180.0 - 174.0, 150.0, 335.0);
	m_downsection1->setBackground(BrushLibrary::get("radar_downsection11"));
	m_downsection2 = createRef<Node2D>(230.0, /*438.0 + */180.0 - 174.0, 150.0, 335.0);
	m_downsection2->setBackground(BrushLibrary::get("radar_downsection12"));
	m_downsection3 = createRef<Node2D>(230.0, /*438.0 + */180.0 - 174.0, 150.0, 335.0);
	m_downsection3->setBackground(BrushLibrary::get("radar_downsection13"));
	m_downsection4 = createRef<Node2D>(230.0, /*438.0 + */180.0 - 174.0, 150.0, 335.0);
	m_downsection4->setBackground(BrushLibrary::get("radar_downsection14"));
	m_downsection5 = createRef<Node2D>(230.0, /*438.0 + */180.0 - 174.0, 150.0, 335.0);
	m_downsection5->setBackground(BrushLibrary::get("radar_downsection15"));
	m_downsection6 = createRef<Node2D>(230.0, /*438.0 + */180.0 - 174.0, 150.0, 335.0);
	m_downsection6->setBackground(BrushLibrary::get("radar_downsection16"));
	m_upsection1 = createRef<Node2D>(230.0, /*438.0 + */180.0 - 174.0, 150.0, 335.0);
	m_upsection1->setBackground(BrushLibrary::get("radar_upsection11"));
	m_upsection2 = createRef<Node2D>(230.0, /*438.0 + */180.0 - 174.0, 150.0, 335.0);
	m_upsection2->setBackground(BrushLibrary::get("radar_upsection12"));
	m_upsection3 = createRef<Node2D>(230.0, /*438.0 + */180.0 - 174.0, 150.0, 335.0);
	m_upsection3->setBackground(BrushLibrary::get("radar_upsection13"));
	m_upsection4 = createRef<Node2D>(230.0, /*438.0 + */180.0 - 174.0, 150.0, 335.0);
	m_upsection4->setBackground(BrushLibrary::get("radar_upsection14"));
	m_upsection5 = createRef<Node2D>(230.0, /*438.0 + */180.0 - 174.0, 150.0, 335.0);
	m_upsection5->setBackground(BrushLibrary::get("radar_upsection15"));
	m_upsection6 = createRef<Node2D>(230.0, /*438.0 + */180.0 - 174.0, 150.0, 335.0);
	m_upsection6->setBackground(BrushLibrary::get("radar_upsection16"));
	m_carsmall = createRef<Node2D>(263.0, 258.0 - 174.0, 85.0, 178.0);
	m_carsmall->setBackground(BrushLibrary::get("carsmall"));
	m_subline = Node2D::createWithTextureFrameName("memory", "autopark_pic_subline.png", true, 263.0, 436.0 - 174.0);
	m_roadsmall = Node2D::createWithTextureFrameName("memory", "pic_parking_road.png", true, 222.0, /*438.0 + */0.0);
	m_space1small = Node2D::createWithTextureFrameName("memory", "pic_parking_spaces.png", true, 350.0, /*438.0 + */144.0+154.0);
	m_space2small = Node2D::createWithTextureFrameName("memory", "pic_parking_spaces2.png", true, 95.0, /*438.0 + */242.0);
	m_parkpositionsmall = Node2D::createWithTextureFrameName("memory", "icon_angelp_sel.png", true, 350.0 + 82.0, /*438.0 + */184.0 + 154.0);
	m_radarview->addChild(m_roadsmall);
	m_radarview->addChild(m_space1small);
	m_radarview->addChild(m_space2small);
	m_radarview->addChild(m_parkpositionsmall);
	m_radarview->addChild(m_downsection1);
	m_radarview->addChild(m_downsection2);
	m_radarview->addChild(m_downsection3);
	m_radarview->addChild(m_downsection4);
	m_radarview->addChild(m_downsection5);
	m_radarview->addChild(m_downsection6);
	m_radarview->addChild(m_upsection1);
	m_radarview->addChild(m_upsection2);
	m_radarview->addChild(m_upsection3);
	m_radarview->addChild(m_upsection4);
	m_radarview->addChild(m_upsection5);
	m_radarview->addChild(m_upsection6);
	m_radarview->addChild(m_subline);
	m_radarview->addChild(m_carsmall);

	addChild(m_radarview);

	//addChild(m_road);
	//addChild(m_space1);
	//addChild(m_space2);
	//addChild(m_parkposition);
	//addChild(m_car);
	addChild(m_tipbg);
	addChild(m_status);
	addChild(m_seperator);
	addChild(m_name);
	addChild(m_type);
	addChild(m_back);
	addChild(m_pop);

	BrushLibrary::addImageBrush("video_mask", RES_DIR"ipu02/memory/video_mask.png");
	m_videomask = createRef<Node2D>(610.0, 100.0, 1311.0, 880.0);
	m_videomask->setBackground(BrushLibrary::get("video_mask"));
	addChild(m_videomask);
	auto btn_success = createRef<Button>(0.0, 0.0, 100.0, 50.0);
	btn_success->setName("success");
	btn_success->setBkgndNormal(SolidColorBrush::whiteSmoke());
	btn_success->Click += nbBindEventFunction(PageParking::onBtnClicked);
	m_videomask->addChild(btn_success);

	auto btn_r = createRef<Button>(105.0, 0.0, 100.0, 50.0);
	btn_r->setName("r");
	btn_r->setBkgndNormal(SolidColorBrush::whiteSmoke());
	btn_r->Click += nbBindEventFunction(PageParking::onBtnClicked);
	m_videomask->addChild(btn_r);
	auto btn_houshi = createRef<Button>(210.0, 0.0, 100.0, 50.0);
	btn_houshi->setName("houshi");
	btn_houshi->setBkgndNormal(SolidColorBrush::whiteSmoke());
	btn_houshi->Click += nbBindEventFunction(PageParking::onBtnClicked);
	m_videomask->addChild(btn_houshi);

	auto btn_obstacle = createRef<Button>(315, 0.0, 100.0, 50.0);
	btn_obstacle->setName("obstacle");
	btn_obstacle->setBkgndNormal(SolidColorBrush::whiteSmoke());
	btn_obstacle->Click += nbBindEventFunction(PageParking::onBtnClicked);
	m_videomask->addChild(btn_obstacle);

	auto btn_doorunlock = createRef<Button>(420, 0.0, 100.0, 50.0);
	btn_doorunlock->setName("doorunlock");
	btn_doorunlock->setBkgndNormal(SolidColorBrush::whiteSmoke());
	btn_doorunlock->Click += nbBindEventFunction(PageParking::onBtnClicked);
	m_videomask->addChild(btn_doorunlock);

	auto btn_continue = createRef<Button>(525, 0.0, 100.0, 50.0);
	btn_continue->setName("pop_continue");
	btn_continue->setBkgndNormal(SolidColorBrush::whiteSmoke());
	btn_continue->Click += nbBindEventFunction(PageParking::onBtnClicked);
	m_videomask->addChild(btn_continue);

	auto btn_terminate = createRef<Button>(630, 0.0, 100.0, 50.0);
	btn_terminate->setName("terminate");
	btn_terminate->setBkgndNormal(SolidColorBrush::whiteSmoke());
	btn_terminate->Click += nbBindEventFunction(PageParking::onBtnClicked);
	m_videomask->addChild(btn_terminate);

	m_success = createRef<Timer>(5 * 1000, true);
	m_success->Tick += nbBindEventFunction(PageParking::onTick);
	m_paused = createRef<Timer>(2 * 60 * 1000, true);
	m_paused->Tick += nbBindEventFunction(PageParking::onTick);
	m_failed = createRef<Timer>(2 * 60 * 1000, true);
	m_failed->Tick += nbBindEventFunction(PageParking::onTick);

	popup(ERRORID::ERROR_ID_PAUSED_OBSTACLE);
	popdown();
}

void PageParking::onBtnClicked(const EventArgs &arg)
{
	Button *sender = as<Button>(arg.sender);
	if (sender == NULL) return;
	std::string name = sender->getName();
	if (name == "back")
	{
		SwitchPageEventArgs arg;
		arg.m_id = NBPageID::NB_PAGEID_MEMORY_PARKING_ROUTE_SELECTION;
		SwitchPageEvent.invoke(arg);
	}
	else if (name == "continue")
	{
		popdown();
	}
	else if (name == "success")
	{
		m_status->setText(u8"泊车已完成，已为您挂至P档。5S后将自动退出。");
		//m_success->start();
	}
	else if (name == "r")
	{
		m_radarview->setVisibility(VisibilityE::Visible);
		m_houshiview->setVisibility(VisibilityE::Hidden);
	}
	else if (name == "houshi")
	{
		m_radarview->setVisibility(VisibilityE::Hidden);
		m_houshiview->setVisibility(VisibilityE::Visible);
	}
	else if (name == "obstacle")
	{
		popup(ERRORID::ERROR_ID_PAUSED_OBSTACLE);
	}
	else if (name == "doorunlock")
	{
		popup(ERRORID::ERROR_ID_PAUSED_DOOR_UNLOCKED);
	}
	else if (name == "pop_continue")
	{
		popup(ERRORID::ERROR_ID_CONTINUE);
	}
	else if (name == "terminate")
	{
		popup(ERRORID::ERROR_ID_TERMINATE);
	}
	else
	{
	}
}

void PageParking::onTick(const EventArgs &arg)
{
	nb::Timer *timer = as<Timer>(arg.sender);
	if (timer == NULL) return;
	if (timer == m_success.get())
	{
	}
	else if (timer == m_failed.get())
	{
		SwitchPageEventArgs arg;
		arg.m_id = NBPageID::NB_PAGEID_MEMORY_PARKING_ROUTE_SELECTION;
		SwitchPageEvent.invoke(arg);
	}
	else if (timer == m_paused.get())
	{
	}
	else
	{
	}
}

void PageParking::popup(ERRORID id)
{
	m_failed->stop();
	m_success->stop();
	m_failed->stop();
	switch (id)
	{
	case ERROR_ID_TERMINATE:
		{
			m_poptitle->setText(u8"泊车功能已终止!");
			m_popcontent->setText(u8"不可恢复的报错文案");
			m_btntext->setText(u8"退出(120s)");
			m_btntext->setColor(Color(255.0, 255.0, 255.0, 255.0));
			m_recttext->setVisibility(VisibilityE::Visible);
			m_continue->setBkgndNormal(createRef<ImageBrush>("memory", "autopark_btn_62px_sel.png"));
			m_continue->setVisibility(VisibilityE::Visible);
			m_pop->setVisibility(VisibilityE::Visible);
			//m_failed->start();
		}
		break;
	case ERROR_ID_PAUSED_OBSTACLE:
		{
			m_poptitle->setText(u8"泊车功能暂停!");
			m_popcontent->setText(u8"前方障碍物，请在两分钟内移除障碍物后，继续泊车");
			m_continue->setVisibility(VisibilityE::Hidden);
			m_recttext->setVisibility(VisibilityE::Hidden);
			m_pop->setVisibility(VisibilityE::Visible);
		}
		break;
	case ERROR_ID_CONTINUE_OBSTACLE:
		{
			m_poptitle->setText(u8"泊车功能已恢复!");
			m_popcontent->setText(u8"障碍物已移除，泊车流程继续");
			m_continue->setVisibility(VisibilityE::Hidden);
			m_recttext->setVisibility(VisibilityE::Hidden);
			m_pop->setVisibility(VisibilityE::Visible);
		}
		break;
	case ERROR_ID_PAUSED_DOOR_UNLOCKED:
		{
			m_poptitle->setText(u8"泊车功能暂停");
			m_popcontent->setText(u8"车门未关，请关闭车门后，继续泊车流程");
			m_continue->setBkgndNormal(createRef<ImageBrush>("memory", "autopark_btn_62px_nor.png"));
			m_btntext->setColor(Color(0.0, 0.0, 0.0, 255.0));
			m_btntext->setText(u8"继续泊车");
			m_pop->setVisibility(VisibilityE::Visible);
			m_continue->setVisibility(VisibilityE::Visible);
			m_recttext->setVisibility(VisibilityE::Visible);
		}
		break;
	case ERROR_ID_CONTINUE:
		{
			m_poptitle->setText(u8"泊车功能已恢复!");
			m_popcontent->setText(u8"请点击按钮继续泊车");
			m_btntext->setText(u8"继续(120s)");
			m_btntext->setColor(Color(255.0, 255.0, 255.0, 255.0));
			m_recttext->setVisibility(VisibilityE::Visible);
			m_continue->setBkgndNormal(createRef<ImageBrush>("memory", "autopark_btn_62px_sel.png"));
			m_continue->setVisibility(VisibilityE::Visible);
			m_pop->setVisibility(VisibilityE::Visible);
		}
		break;
	default:
		break;
	}
}

void PageParking::popdown()
{
	if (m_pop != NULL)
	{
		m_pop->setVisibility(VisibilityE::Hidden);
	}
}
