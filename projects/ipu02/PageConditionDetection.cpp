#include "PageConditionDetection.h"

PageConditionDetection::PageConditionDetection(const Rect &rc, NBPageID id)
	: PageBase(rc, id)
{
	init();
}
PageConditionDetection::PageConditionDetection(float x, float y, float w, float h, NBPageID id)
	: PageBase(x, y, w, h, id)
{
	init();
}

void PageConditionDetection::init()
{
	PageBase::init();
	//To Do the followings:
	//1. init Nodes
	//2. build DataTree
	//3. Others

	m_status = DETECTIONSTATUS::STATUS_INITIAL;
	m_rectstatus = createRef<Node2D>(800.0, 534.0, 320.0, 54.0);
	m_textstatus = createRef<TextBlock>(0.0, 0.0, 200.0, 54.0);
	m_textstatus->setAlignmentCenter();
	m_textstatus->setText(u8"条件检测中...");
	m_rectstatus->addChild(m_textstatus);

	m_resultbg = Node2D::createWithTextureFrameName("memory", "stagelight_nor.png", true, 804.0, 210.0);
	//m_resultbg->setSize(Size(320.0, 320.0));
	m_car = Node2D::createWithTextureFrameName("memory", "autopark_pic_car.png", true, 896.0, 210.0);
	//m_car->setSize(Size(128.0, 256.0));

	m_conditions = createRef<Node2D>(0.0, 0.0, 1920.0, 1080.0);
	m_iconP = Node2D::createWithTextureFrameName("memory", "icon_pass.png", true, 750.0, 639.0);
	auto rectP = createRef<Node2D>(810.0, 632.0, 500.0, 54.0);
	m_textP = createRef<TextBlock>(0.0, 9.0, 500.0, 54.0);
	rectP->addChild(m_textP);
	m_textP->setHorizontalAlignment(HorizontalAlignmentE::Left);
	m_textP->setVerticalAlignment(VerticalAlignmentE::Center);
	m_textP->setText(u8"已挂入P档");

	m_icondoors = Node2D::createWithTextureFrameName("memory", "icon_pass.png", true, 750.0, 693.0);
	auto rectdoors = createRef<Node2D>(810.0, 686.0, 500.0, 54.0);
	m_textdoors = createRef<TextBlock>(0.0, 9.0, 500.0, 54.0);
	m_textdoors->setHorizontalAlignment(HorizontalAlignmentE::Left);
	m_textdoors->setVerticalAlignment(VerticalAlignmentE::Center);
	rectdoors->addChild(m_textdoors);
	m_textdoors->setText(u8"车门、后尾门、引擎盖已关闭");

	m_iconcharge = Node2D::createWithTextureFrameName("memory", "icon_error.png", true, 750.0, 747.0);
	auto rectcharge = createRef<Node2D>(810.0, 740.0, 500.0, 54.0);
	m_textcharge = createRef<TextBlock>(0.0, 9.0, 500.0, 54.0);
	m_textcharge->setHorizontalAlignment(HorizontalAlignmentE::Left);
	m_textcharge->setVerticalAlignment(VerticalAlignmentE::Center);
	rectcharge->addChild(m_textcharge);
	m_textcharge->setText(u8"充电枪已断开");
	
	m_iconbelt= Node2D::createWithTextureFrameName("memory", "icon_loading.png", true, 750.0, 801.0);
	auto rectbelt = createRef<Node2D>(810.0, 794.0, 500.0, 54.0);
	m_textbelt = createRef<TextBlock>(0.0, 9.0, 500.0, 54.0);
	m_textbelt->setHorizontalAlignment(HorizontalAlignmentE::Left);
	m_textbelt->setVerticalAlignment(VerticalAlignmentE::Center);
	rectbelt->addChild(m_textbelt);
	m_textbelt->setText(u8"安全带是否已系好");

	m_iconroute = Node2D::createWithTextureFrameName("memory", "icon_loading.png", true, 750.0, 855.0);
	auto rectroute = createRef<Node2D>(810.0, 848.0, 500.0, 54.0);
	m_textroute = createRef<TextBlock>(0.0, 9.0, 500.0, 54.0);
	m_textroute->setHorizontalAlignment(HorizontalAlignmentE::Left);
	m_textroute->setVerticalAlignment(VerticalAlignmentE::Center);
	rectroute->addChild(m_textroute);
	m_textroute->setText(u8"路径匹配已完成");


	m_failed = createRef<Node2D>(710.0, 632.0, 500.0, 286.0);
	m_failedtext = createRef<TextBlock>(0.0, 0.0, 500, 162.0);
	m_failed->addChild(m_failedtext);
	m_failedtext->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_failedtext->setText(u8"失败原因方案,失败原因方案,失败原因方案");
	m_retry = Button::createWithTextureFrameName("memory", "autopark_btn_62px_sel.png", true, 20.0, 224.0);
	m_retry->Click += nbBindEventFunction(PageConditionDetection::onBtnClicked);
	auto rectretry = createRef<Node2D>(30.0, 235.0, 120.0, 40.0);
	auto textretry = createRef<TextBlock>(0.0, 7.0, 40.0, 40.0);
	textretry->setAlignmentCenter();
	textretry->setText(u8"重试");
	rectretry->addChild(textretry);


	m_changeroute = Button::createWithTextureFrameName("memory", "autopark_btn_62px_sel.png", true, 280.0, 224.0);
	m_changeroute->Click += nbBindEventFunction(PageConditionDetection::onBtnClicked);
	auto rectchangeroute = createRef<Node2D>(320.0, 235.0, 120.0, 40.0);
	auto textchangeroute = createRef<TextBlock>(0.0, 7.0, 120.0, 40.0);
	textchangeroute->setAlignmentCenter();
	textchangeroute->setText(u8"更换路线");
	rectchangeroute->addChild(textchangeroute);
	m_failed->addChild(m_retry);
	m_failed->addChild(rectretry);
	m_failed->addChild(m_changeroute);
	m_failed->addChild(rectchangeroute);
	m_failed->setVisibility(VisibilityE::Hidden);

	m_start = Button::createWithTextureFrameName("memory", "autopark_btn_62px_sel.png", true, 860.0, 856.0);
	m_start->Click += nbBindEventFunction(PageConditionDetection::onBtnClicked);
	m_start->setVisibility(VisibilityE::Hidden);
	m_rectstart = createRef<Node2D>(900.0, 867.0, 120.0, 40.0);
	m_textstart = createRef<TextBlock>(0.0, 7.0, 120.0, 40.0);
	m_rectstart->addChild(m_textstart);
	m_textstart->setAlignmentCenter();
	m_textstart->setText(u8"开始泊车");
	m_rectstart->setVisibility(VisibilityE::Hidden);



	addChild(m_rectstatus);
	addChild(m_resultbg);
	addChild(m_car);
	m_conditions->addChild(m_iconP);
	m_conditions->addChild(rectP);
	m_conditions->addChild(m_icondoors);
	m_conditions->addChild(rectdoors);
	m_conditions->addChild(m_iconcharge);
	m_conditions->addChild(rectcharge);
	m_conditions->addChild(m_iconbelt);
	m_conditions->addChild(rectbelt);
	m_conditions->addChild(m_iconroute);
	m_conditions->addChild(rectroute);
	addChild(m_conditions);
	addChild(m_failed);
	addChild(m_start);
	addChild(m_rectstart);

	updateStatus(DETECTIONSTATUS::STATUS_DETECTING);

	
	btn_detecting = createRef<Button>(1800.0, 110.0, 100.0, 50.0);
	btn_detecting->setBkgndNormal(SolidColorBrush::whiteSmoke());
	btn_detecting->Click += nbBindEventFunction(PageConditionDetection::onBtnClicked);

	btn_failed = createRef<Button>(1800.0, 170.0, 100.0, 50.0);
	btn_failed->setBkgndNormal(SolidColorBrush::whiteSmoke());
	btn_failed->Click += nbBindEventFunction(PageConditionDetection::onBtnClicked);

	btn_finished = createRef<Button>(1800.0, 230.0, 100.0, 50.0);
	btn_finished->setBkgndNormal(SolidColorBrush::whiteSmoke());
	btn_finished->Click += nbBindEventFunction(PageConditionDetection::onBtnClicked);
	addChild(btn_detecting);
	addChild(btn_failed);
	addChild(btn_finished);
}

void PageConditionDetection::updateStatus(DETECTIONSTATUS status)
{
	if (status == m_status) return;
	m_status = status;
	switch (m_status)
	{
	case DETECTIONSTATUS::STATUS_FINISHED:
	{
		m_start->setVisibility(VisibilityE::Visible);
		m_rectstart->setVisibility(VisibilityE::Visible);
		m_conditions->setVisibility(VisibilityE::Hidden);
		m_failed->setVisibility(VisibilityE::Hidden);
		m_textstatus->setText(u8"条件检测完成");
		m_textstatus->setColor(Color(30.0, 164.0, 51.0, 255.0));
		m_rectstatus->setPosition(Point(800.0, 638.0));
		m_resultbg->setPosition(Point(804.0, 314.0));
		m_resultbg->setBackground(createRef<ImageBrush>(TextureLibrary::getFrameFromTextureAtlas("memory", "stagelight_right.png")));
		m_car->setPosition(Point(896.0, 314.0/*341.0*/));
	}
		break;
	case DETECTIONSTATUS::STATUS_DETECTING:
	{
		m_start->setVisibility(VisibilityE::Hidden);
		m_rectstart->setVisibility(VisibilityE::Hidden);
		m_conditions->setVisibility(VisibilityE::Visible);
		m_failed->setVisibility(VisibilityE::Hidden);
		m_textstatus->setText(u8"条件检测中...");
		m_textstatus->setColor(Color(0.0, 0.0, 0.0, 255.0));
		m_rectstatus->setPosition(Point(800.0, 534.0));
		m_resultbg->setPosition(Point(804.0, 210.0));
		m_resultbg->setBackground(createRef<ImageBrush>(TextureLibrary::getFrameFromTextureAtlas("memory", "stagelight_nor.png")));
		m_car->setPosition(Point(896.0, 210.0/*237.0*/));
	}
		break;
	case DETECTIONSTATUS::STATUS_FAILED:
	{
		m_start->setVisibility(VisibilityE::Hidden);
		m_rectstart->setVisibility(VisibilityE::Hidden);
		m_conditions->setVisibility(VisibilityE::Hidden);
		m_failed->setVisibility(VisibilityE::Visible);
		m_textstatus->setText(u8"条件检测失败");
		m_textstatus->setColor(Color(255.0, 0.0, 0.0, 255.0));
		m_rectstatus->setPosition(Point(800.0, 534.0));
		m_resultbg->setPosition(Point(804.0, 210.0));
		m_resultbg->setBackground(createRef<ImageBrush>(TextureLibrary::getFrameFromTextureAtlas("memory", "stagelight_fault.png")));
		m_car->setPosition(Point(896.0, 210.0/*237.0*/));
	}
		break;
	default:
		break;
	}
}

void PageConditionDetection::onBtnClicked(const EventArgs &arg)
{
	Button *sender = as<Button>(arg.sender);
	if (sender == NULL) return;
	if (sender == m_start.get())
	{
		SwitchPageEventArgs arg;
		arg.m_id = NBPageID::NB_PAGEID_MEMORY_PARKING;
		SwitchPageEvent.invoke(arg);
	}
	else if (sender == m_retry.get())
	{
		updateStatus(DETECTIONSTATUS::STATUS_DETECTING);
	}
	else if (sender == m_changeroute.get())
	{
		SwitchPageEventArgs arg;
		arg.m_id = NBPageID::NB_PAGEID_MEMORY_PARKING_ROUTE_SELECTION;
		SwitchPageEvent.invoke(arg);
	}
	else if (sender == btn_detecting.get())
	{
		updateStatus(DETECTIONSTATUS::STATUS_DETECTING);
	}
	else if (sender == btn_failed.get())
	{
		updateStatus(DETECTIONSTATUS::STATUS_FAILED);
	}
	else if (sender == btn_finished.get())
	{
		updateStatus(DETECTIONSTATUS::STATUS_FINISHED);
	}
}