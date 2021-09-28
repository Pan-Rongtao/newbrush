#include "AIView.h"
#include "MainView.h"
#include "AVMView.h"
#include "PAPView.h"
#include "Tr.h"

AutoPark::AutoPark()
{
	setBackground(IMGBR(AP, "autopark_pic_bgroad.png"));
	m_tipBg = createRef<NinePatchImage>(0.0f, 20.0f, 584.0f, 86.0f);
	m_tipBg->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_tipText = createRef<TextBlock>(u8"");
	m_tipText->setAlignmentCenter();
	m_tipBg->addChild(m_tipText);
	m_car = Node2D::createWithTextureFrameName(AP, "pic_car03.png", 0.0f, 0.0f);
	m_car->setAlignmentCenter();
	m_carRadar = Node2D::createWithTextureFrameName(AP, "pic_radar.png", 0.0f, 0.0f);
	m_carRadar->setAlignmentCenter();
	m_slot0 = Node2D::createWithTextureFrameName(AP, "parking sapce_rightview/autopark_pic_parkright1_nor.png", 880.0f, 300.0f);
	m_slot0->setTransform(createRef<RotateTransform2D>(-10.0f, 132.0f, 50.0f));
	m_tipBottom = createRef<TextBlock>(0.0f, 720.0f, 0.0f, 0.0f, u8"");
	m_tipBottom->setHorizontalAlignment(HorizontalAlignmentE::Center);

	addChild(m_tipBg);
	addChild(m_carRadar);
	addChild(m_car);
	addChild(m_slot0);
	addChild(m_tipBottom);

	setWarningText(u8"搜索到车位，请停车");

	m_aniLadarOpacity.setFrom(0.1f);
	m_aniLadarOpacity.setTo(1.0f);
	m_aniLadarOpacity.setTarget(m_carRadar);
	m_aniLadarOpacity.setTargetPropertyName("Opacity");
	m_aniLadarOpacity.duration = TimeSpan::fromMilliseconds(200);
	m_aniLadarOpacity.autoReverse = true;
	m_aniLadarOpacity.repeatBehavior = RepeatBehavior::forever();

	std::set<StringKeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromSeconds(0), u8"车位搜索中，请低速前进" });
	keyFrames.insert({ TimeSpan::fromSeconds(2), u8"未搜索到车位，请继续等待" });
	keyFrames.insert({ TimeSpan::fromSeconds(4), u8"搜索到车位，请停车" });
	keyFrames.insert({ TimeSpan::fromSeconds(6), u8"请保持刹车，点击开始按钮" });
	keyFrames.insert({ TimeSpan::fromSeconds(8), u8"点击按钮，开始泊车" });
	m_aniTip.setTarget(m_tipText);
	m_aniTip.setTargetPropertyName("Text");
	m_aniTip.duration = TimeSpan::fromSeconds(10);
	m_aniTip.setKeyFrames(keyFrames);
}

void AutoPark::setWarningText(const std::string & txt)
{
	m_tipText->setText(txt);
	auto w = m_tipText->getActualFont()->measure(txt).width;
	m_tipBg->setWidth((int)w + 100.0f);
}

void AutoPark::setTheme(int theme)
{
	if(theme == 0)
	{
		m_tipBg->setImages(IMGBR(AVM, "nine0.png"), IMGBR(AVM, "nine2.png"), IMGBR(AVM, "nine3.png"), IMGBR(AVM, "nine1.png"), IMGBR(AVM, "nine4.png"));
		m_tipText->setColor(Colors::black);
		m_tipBottom->setColor(Colors::black);
	}
	else
	{
		m_tipBg->setImages(IMGBR(AVM, "nine00.png"), IMGBR(AVM, "nine22.png"), IMGBR(AVM, "nine33.png"), IMGBR(AVM, "nine11.png"), IMGBR(AVM, "nine44.png"));
		m_tipText->setColor(Colors::white);
		m_tipBottom->setColor(Colors::gray);
	}
}

void AutoPark::setLanguage(int lan)
{
	m_tipBottom->setText(TR(lan, TID_AutoTip));
}

void AutoPark::start()
{
	m_aniLadarOpacity.begin();
	m_aniTip.begin();
}

void AutoPark::stop()
{
	m_aniLadarOpacity.stop();
	m_aniTip.stop();
}

//////////
ControllerPark::ControllerPark()
	: m_tick(0)
{
	auto x = 450.0f;
	auto y = 230.0f;
	auto l = 60.0f;
	glm::vec2 space = { 60.0f, 7.0f };
	m_title = createRef<TextBlock>(600.0f, y, 0.0f, 0.0f, u8"条件检测中...");
	m_title->setHorizontalAlignment(HorizontalAlignmentE::Left);
	y += 80.0f;
	m_icons[0] = Node2D::createWithTextureFrameName(AP, "number/1_d.png", x, y + l * 0);
	m_icons[1] = Node2D::createWithTextureFrameName(AP, "number/2_d.png", x, y + l * 1);
	m_icons[2] = Node2D::createWithTextureFrameName(AP, "number/3_d.png", x, y + l * 2);
	m_icons[3] = Node2D::createWithTextureFrameName(AP, "number/4_d.png", x, y + l * 3);
	m_icons[4] = Node2D::createWithTextureFrameName(AP, "number/5_d.png", x, y + l * 4);
	m_txts[0] = createRef<TextBlock>(x + space.x, y + l * 0 + space.y, 0.0f, 0.0f, u8"请挂至P档");
	m_txts[1] = createRef<TextBlock>(x + space.x, y + l * 1 + space.y, 0.0f, 0.0f, u8"请挂至请打开车联助手APP");
	m_txts[2] = createRef<TextBlock>(x + space.x, y + l * 2 + space.y, 0.0f, 0.0f, u8"请保持手机蓝牙连接");
	m_txts[3] = createRef<TextBlock>(x + space.x, y + l * 3 + space.y, 0.0f, 0.0f, u8"请关闭车门、后备箱、引擎盖");
	m_txts[4] = createRef<TextBlock>(x + space.x, y + l * 4 + space.y, 0.0f, 0.0f, u8"钥匙不在车内");

	addChild(m_title);
	for (auto node : m_icons)	addChild(node);
	addChild(m_txts[0]);
	addChild(m_txts[1]);
	addChild(m_txts[2]);
	addChild(m_txts[3]);
	addChild(m_txts[4]);

	m_timer.Tick += nbBindEventFunction(ControllerPark::onTick);
	std::set<StringKeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromMilliseconds(0), u8"条件检测中" });
	keyFrames.insert({ TimeSpan::fromMilliseconds(200), u8"条件检测中." });
	keyFrames.insert({ TimeSpan::fromMilliseconds(400), u8"条件检测中.." });
	keyFrames.insert({ TimeSpan::fromMilliseconds(600), u8"条件检测中..." });
	m_aniTitle.setTarget(m_title);
	m_aniTitle.setTargetPropertyName("Text");
	m_aniTitle.duration = TimeSpan::fromMilliseconds(800);
	m_aniTitle.repeatBehavior = RepeatBehavior::forever();
	m_aniTitle.setKeyFrames(keyFrames);
}

void ControllerPark::start()
{
	m_timer.start(700);
	m_aniTitle.begin();
	m_tick = 0;
}

void ControllerPark::stop()
{
	m_timer.stop();
	m_aniTitle.stop();
}

void ControllerPark::setTheme(int theme)
{
	if (theme == 0)
	{
		m_title->setColor(Colors::black);
		for (auto i = 0u; i < m_icons.size(); ++i)
		{
			m_icons[i]->setBackground(IMGBR(AP, std::string("number/") + std::to_string(i + 1) + "_d.png"));
		}
	}
	else
	{
		m_title->setColor(Colors::white);
		for (auto i = 0u; i < m_icons.size(); ++i)
		{
			m_icons[i]->setBackground(IMGBR(AP, std::string("number/") + std::to_string(i + 1) + "_n.png"));
		}
	}
}

void ControllerPark::setLanguage(int lan)
{
	std::set<StringKeyFrame> keyFrames;
	keyFrames.insert({ TimeSpan::fromMilliseconds(0), TR(lan, TID_Control_Title0) });
	keyFrames.insert({ TimeSpan::fromMilliseconds(200), TR(lan, TID_Control_Title1) });
	keyFrames.insert({ TimeSpan::fromMilliseconds(400), TR(lan, TID_Control_Title2) });
	keyFrames.insert({ TimeSpan::fromMilliseconds(600), TR(lan, TID_Control_Title3) });
	m_aniTitle.setKeyFrames(keyFrames);
	m_title->setText(TR(lan, TID_Control_Title0));
	m_txts[0]->setText(TR(lan, TID_Control_Txt0));
	m_txts[1]->setText(TR(lan, TID_Control_Txt1));
	m_txts[2]->setText(TR(lan, TID_Control_Txt2));
	m_txts[3]->setText(TR(lan, TID_Control_Txt3));
	m_txts[4]->setText(TR(lan, TID_Control_Txt4));
}

void ControllerPark::onTick(const EventArgs & e)
{
	auto normalColor = ThemeManager::getTheme() == 0 ? Colors::black : Colors::white;
	if (e.sender == &m_timer)
	{
		if (m_tick == 0)		setTextColor(normalColor, normalColor, normalColor, normalColor, normalColor);
		else if (m_tick == 1)	setTextColor(Colors::green, normalColor, normalColor, normalColor, normalColor);
		else if (m_tick == 2)	setTextColor(Colors::green, Colors::green, normalColor, normalColor, normalColor);
		else if (m_tick == 3)	setTextColor(Colors::green, Colors::green, Colors::red, normalColor, normalColor);
		else if (m_tick == 4)	setTextColor(Colors::green, Colors::green, Colors::green, normalColor, normalColor);
		else if (m_tick == 5)	setTextColor(Colors::green, Colors::green, Colors::green, Colors::green, normalColor);
		else if (m_tick == 6)	setTextColor(Colors::green, Colors::green, Colors::green, Colors::green, Colors::green);
		else
		{
			m_tick = -1;
			stop();
			Finish.invoke({});
		}
		++m_tick;
	}
}

void ControllerPark::setTextColor(const Color & clr0, const Color & clr1, const Color & clr2, const Color & clr3, const Color & clr4)
{
	m_txts[0]->setColor(clr0);
	m_txts[1]->setColor(clr1);
	m_txts[2]->setColor(clr2);
	m_txts[3]->setColor(clr3);
	m_txts[4]->setColor(clr4);
}
///////////////////

ControllerParkProgress::ControllerParkProgress()
{
	//BrushLibrary::addImageBrush("Ing", RES_DIR"ipu02/ap/autopark_pic.png");

	m_btnReturn = createRef<Button>(40.0f, 0.0f, 140.0f, 100.0f);
	m_btnReturn->setIcon(IMGBR(AVM, "day/topbar/icon_topbar_back.png"));
	m_btnReturn->setText(u8"退出");
	m_btnReturn->setIconTextOffset({ 6.0f, 27.0f }, { 60.0f, 35.0f });
	m_btnReturn->setTextColor(Colors::black, Color(0, 0, 0, 150));
	m_btnReturn->Click += [&](const EventArgs &e) { Exit.invoke(e); };

	m_icon = createRef<Node2D>();
	m_icon->setY(-30.0f);
	m_icon->setAlignmentCenter();

	m_txtIng = createRef<TextBlock>(0.0f, 650.0f, 0.0f, 0.0f, u8"遥控泊车进行中......");
	m_txtIng->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_txtPause = createRef<TextBlock>(0.0f, 650.0f, 0.0f, 0.0f, u8"遥控泊车暂停");
	m_txtPause->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_txtDone = createRef<TextBlock>(0.0f, 650.0f, 0.0f, 0.0f, u8"遥控泊车完成");
	m_txtDone->setHorizontalAlignment(HorizontalAlignmentE::Center);

	addChild(m_icon);
	addChild(m_btnReturn);
	addChild(m_txtIng);
	addChild(m_txtPause);
	addChild(m_txtDone);
	
	m_timer.Tick += [&](const EventArgs & e)
	{
		if (m_tick <= 2)	switchState(m_tick);
		else				m_timer.stop();

		++m_tick;
	};
}

void ControllerParkProgress::start()
{
	m_timer.start(1200);
	switchState(0);
	m_tick = 0;
}

void ControllerParkProgress::setTheme(int theme)
{
	if (theme == 0)
	{
		m_btnReturn->setIcon(IMGBR(AVM, "day/topbar/icon_topbar_back.png"));
		m_btnReturn->setTextColor(Colors::black, Color(0, 0, 0, 150));
		m_txtIng->setColor(Colors::black);
		m_txtPause->setColor(Colors::black);
		m_txtDone->setColor(Colors::black);
	}
	else
	{
		m_btnReturn->setIcon(IMGBR(AVM, "night/icon_topbar_back.png"));
		m_btnReturn->setTextColor(Colors::white, Color(255, 255, 255, 150));
		m_txtIng->setColor(Colors::white);
		m_txtPause->setColor(Colors::white);
		m_txtDone->setColor(Colors::white);
	}
}

void ControllerParkProgress::setLanguage(int lan)
{
	m_btnReturn->setText(TR(lan, TID_Exit));
	m_txtIng->setText(TR(lan, TID_Progress_Txt0));
	m_txtPause->setText(TR(lan, TID_Progress_Txt1));
	m_txtDone->setText(TR(lan, TID_Progress_Txt2));
}

void ControllerParkProgress::switchState(int state)
{
	if (state == 0)
	{
		m_icon->setSize({/*NAN, NAN*/240.0f, 240.0f });
		m_icon->setBackground(/*BrushLibrary::get("Ing")*/IMGBR(AP, "autopark_pic_alert.png"));
	}
	else if (state == 1)
	{
		m_icon->setSize({ 240.0f, 240.0f });
		m_icon->setBackground(IMGBR(AP, "autopark_pic_pause.png"));
	}
	else if (state == 2)
	{
		m_icon->setSize({ 240.0f, 240.0f });
		m_icon->setBackground(IMGBR(AP, "autopark_pic_compete.png"));
	}
	m_txtIng->setVisibility(state == 0 ? VisibilityE::Visible : VisibilityE::Hidden);
	m_txtPause->setVisibility(state == 1 ? VisibilityE::Visible : VisibilityE::Hidden);
	m_txtDone->setVisibility(state == 2 ? VisibilityE::Visible : VisibilityE::Hidden);
}
///////////////////

SelectPark::SelectPark()
{
	m_title = createRef<TextBlock>(0.0f, 200.0f, 0.0f, 0.0f, u8"温馨提醒");
	m_title->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_warningTxt = createRef<TextBlock>(0.0f, 280.0f, 650.0f, 200.0f, u8"");
	m_warningTxt->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_warningTxt->setWrap(true);
	//m_warningTxt->setBackground(SolidColorBrush::red());
	m_tipBg = createRef<Node2D>(0.0f, 0.0f, 1040.0f, 477.0f, SolidColorBrush::white());
	m_tipBg->setAlignmentCenter();
	m_pause = Node2D::createWithTextureFrameName(AP, "pic_parkpause.png", 0.0f, 52.0f);
	m_txt = createRef<TextBlock>(0.0f, 272.0f, 0.0f, 0.0f, u8"拖动全景中的车位完成定位，通过车位角度按钮微调角度");
	m_txt->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_btnStart = Button::createWithTextureFrameName(AP, "btn_62px_sel.9.png", 0.0f, 355.0f);
	m_btnStart->setText(u8"开始泊入");
	m_btnStart->setTextColor(Colors::white, Color(255, 255, 255, 150));
	m_pause->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_btnStart->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_tipBg->addChild(m_pause);
	m_tipBg->addChild(m_txt);
	m_tipBg->addChild(m_btnStart);
	addChild(m_title);
	addChild(m_warningTxt);
	addChild(m_tipBg);

	m_timerSelTip.setSingleShot(true);
	m_timerSelTip.Tick += [&](const EventArgs &e)
	{
		m_tipBg->setVisibility(VisibilityE::Visible);
	};
}

void SelectPark::start()
{
	m_tipBg->setVisibility(VisibilityE::Hidden);
	m_timerSelTip.start(3000);
}

void SelectPark::stop()
{
	m_timerSelTip.stop();
}

void SelectPark::setTheme(int theme)
{
	if (theme == 0)
	{
		m_title->setColor(Colors::black);
		m_warningTxt->setColor(Colors::black);
		m_tipBg->setBackground(SolidColorBrush::white());
		m_txt->setColor(Colors::black);
		m_btnStart->setTextColor(Colors::white, Color(255, 255, 255, 150));
	}
	else
	{
		m_title->setColor(Colors::white);
		m_warningTxt->setColor(Colors::white);
		m_tipBg->setBackground(SCBR(Color(9, 12, 15, 255)));
		m_txt->setColor(Colors::white);
		m_btnStart->setTextColor(Colors::black, Color(0, 0, 0, 150));
	}
}

void SelectPark::setLanguage(int lan)
{
	m_title->setText(TR(lan, TID_Select_Title));
	m_warningTxt->setText(TR(lan, TID_Select_Tip));
	m_txt->setText(TR(lan, TID_Select_Txt0));
	m_btnStart->setText(TR(lan, TID_Select_Txt1));
	if (lan == 0)
	{
		m_warningTxt->setWidth(650.0f);
	}
	else
	{
		m_warningTxt->setWidth(800.0f);
	}
}

//////////////////
AIView::AIView()
{
	TextureLibrary::addTextureAtlas(AP, RES_DIR"ipu02/ap_day.png", RES_DIR"ipu02/ap_day.txt");

	m_parentMain = createRef<Node2D>();
	m_cpProg = createRef<ControllerParkProgress>();
	m_cpProg->Exit += [&](const EventArgs &e) { switchToRcpProgress(false); };

	//顶部栏
	m_topBar = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	//m_topBar->setBackground(SolidColorBrush::red());
	m_btnReturn = createRef<Button>(40.0f, 0.0f, 140.0f, 100.0f);
	m_btnReturn->setIcon(IMGBR(AVM, "topbar/icon_topbar_back.png"));
	m_btnReturn->setText(u8"退出");
	m_btnReturn->setIconTextOffset({ 6.0f, 27.0f }, { 60.0f, 35.0f });
	m_btnReturn->setTextColor(Colors::black, Color(0, 0, 0, 150));
	m_btnReturn->Click += [](const EventArgs &e) {MainView::get()->switchView<AVMView>(); };
	m_slideBtn = createRef<SlideButton>(660.0f, 19.0f, 800.0f, 62.0f);
	m_slideBtn->setBackground(IMGBR("ap_day", "btn_62px_nor.9.png"));
	m_slideBtn->setBtn(IMGBR("ap_day", "btn_62px_sel.9.png"));
	m_slideBtn->addItem(u8"自动泊车");
	m_slideBtn->addItem(u8"遥控泊车");
	m_slideBtn->addItem(u8"自选车位");
	m_slideBtn->addItem(u8"记忆泊车");
	m_slideBtn->setTextColor(Colors::black, Colors::white, Colors::gray);
	m_slideBtn->SelectChanged += nbBindEventFunction(AIView::onSlideBtnSelectChanged);
	m_slideBtn->setCurSel(0);

	m_topBar->addChild(m_btnReturn);
	m_topBar->addChild(m_slideBtn);

	//左区域
	m_leftArea = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f);
	//m_leftArea->setBackground(SolidColorBrush::blue());
	m_selNode = Node2D::createWithTextureFrameName(AP, "parking sapce_leftview/parkingspace_fault.png", 100.0f, 100.0f);
	m_selNode->Touch += nbBindEventFunction(AIView::onTouch);
	m_nodeP = Node2D::createWithTextureFrameName(AP, "parking sapce_leftview/icon_p_fault.png", 0.0f, 0.0f);
	m_nodeP->setAlignmentCenter();
	m_nodeR = Node2D::createWithTextureFrameName(AP, "parking sapce_leftview/btn_rotate.png", 22.0f, 22.0f);
	m_nodeR->setHorizontalAlignment(HorizontalAlignmentE::Right);
	m_nodeR->setVerticalAlignment(VerticalAlignmentE::Bottom);
	m_nodeR->Touch += nbBindEventFunction(AIView::onTouch);
	m_selNode->setClipRect(m_leftArea->rect());
	m_selNode->setTransform(createRef<RotateTransform2D>(0.0f, 151.0f, 81.0f));
	m_nodeP->setTransform(createRef<RotateTransform2D>(0.0f, 30.0f, 30.0f));
	m_nodeR->setTransform(createRef<RotateTransform2D>(0.0f, -120.0f, -55.0f));
	m_nodeP->setClipRect(m_leftArea->rect());
	m_nodeR->setClipRect(m_leftArea->rect());
	m_selNode->setVisibility(VisibilityE::Hidden);
	m_selNode->addChild(m_nodeP);
	m_selNode->addChild(m_nodeR);
	m_leftArea->addChild(m_selNode);

	//右区域
	m_rightArea = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	m_autoPark = createRef<AutoPark>();
	m_controllerPark = createRef<ControllerPark>();
	m_controllerPark->Finish += [&](const EventArgs &e) { switchToRcpProgress(true); };
	m_selectPark = createRef<SelectPark>();
	//m_rcp->setBackground(SolidColorBrush::red());

	switchToRcpProgress(false);
	switchParkMode(0);

	m_parentMain->addChild(m_topBar);
	m_parentMain->addChild(m_leftArea);
	m_parentMain->addChild(m_rightArea);
	
	m_themeEventHandle = ThemeManager::ThemeChanged() += nbBindEventFunction(AIView::onThemeChanged);
	m_languageEventHandle = LanguageManager::LanguageChanged() += nbBindEventFunction(AIView::onLanguageChanged);
	onThemeChanged(ThemeManager::getTheme());
	onLanguageChanged(LanguageManager::getLanguage());
}

AIView::~AIView()
{
	ThemeManager::ThemeChanged() -= m_themeEventHandle;
	LanguageManager::LanguageChanged() -= m_languageEventHandle;
}

void AIView::switchToRcpProgress(bool on)
{
	clearChildren();
	addChild(on ? m_cpProg : m_parentMain);
	if(on)
		m_cpProg->start();
}

void AIView::switchParkMode(int mode)
{
	m_rightArea->clearChildren();
	switch (mode)
	{
	case 0: m_rightArea->addChild(m_autoPark);			m_autoPark->start(); m_controllerPark->stop();	break;
	case 1: m_rightArea->addChild(m_controllerPark);	m_autoPark->stop(); m_controllerPark->start();	break;
	case 2: m_rightArea->addChild(m_selectPark);		m_selectPark->start(); m_autoPark->stop(); m_controllerPark->stop();	break;
	default:																							break;
	}
	m_selNode->setVisibility(mode == 2 ? VisibilityE::Visible : VisibilityE::Hidden);
}

void AIView::onThemeChanged(const int &theme)
{
	if (theme == 0)
	{
		m_btnReturn->setIcon(IMGBR(AVM, "day/topbar/icon_topbar_back.png"));
		m_btnReturn->setTextColor(Colors::black, Color(0, 0, 0, 150));
		m_slideBtn->setBackground(createRef<ImageBrush>("ap_day", "btn_62px_nor.9.png"));
		m_slideBtn->setTextColor(Colors::black, Colors::white, Colors::gray);
	}
	else
	{
		m_btnReturn->setIcon(IMGBR(AVM, "night/icon_topbar_back.png"));
		m_btnReturn->setTextColor(Colors::white, Color(255, 255, 255, 150));
		m_slideBtn->setBackground(createRef<ImageBrush>("ap_day", "btn_62px_nor.9_night.png"));
		m_slideBtn->setTextColor(Colors::white, Colors::black, Colors::gray);
	}
	m_autoPark->setTheme(theme);
	m_controllerPark->setTheme(theme);
	m_cpProg->setTheme(theme);
	m_selectPark->setTheme(theme);
}

void AIView::onLanguageChanged(const int & lan)
{
	m_btnReturn->setText(TR(lan, TID_Exit));
	m_slideBtn->setItemText(0, TR(lan, TID_Auto));
	m_slideBtn->setItemText(1, TR(lan, TID_Control));
	m_slideBtn->setItemText(2, TR(lan, TID_Select));
	m_slideBtn->setItemText(3, TR(lan, TID_HPA));
	m_autoPark->setLanguage(lan);
	m_controllerPark->setLanguage(lan);
	m_cpProg->setLanguage(lan);
	m_selectPark->setLanguage(lan);
}

void AIView::onBtnClick(const EventArgs & e)
{
}

void AIView::onSlideBtnSelectChanged(const int & e)
{
	switchParkMode(e);
	if (e == 3)
	{
		MainView::get()->switchView<PAPView>();
	}
}

bool m_pressed = false;
Point m_pressedPoint;
void AIView::onTouch(const TouchEventArgs & e)
{
	if (e.sender == m_selNode.get())
	{
		if (e.action == TouchActionE::down)
		{
			auto rc = m_selNode->getRenderRect();
			m_ptDown = Point{ e.x - rc.x(), e.y - rc.y() };
		}
		else if (e.action == TouchActionE::move)
		{
			if (m_ptDown.x != -1.0f)
			{
				auto parentRc = m_leftArea->getRenderRect();
				Point newPt = Point(e.x, e.y) - m_ptDown - parentRc.leftTop();
				m_selNode->setPosition(newPt);
			}
		}
		else if (e.action == TouchActionE::up)
		{
			m_ptDown = { -1.0f, -1.0f };
		}
	}
	else if (e.sender == m_nodeR.get() && m_ptDown.x == -1.0f)
	{
		Point p = { e.x, e.y };
		if (e.action == TouchActionE::down)
		{
			m_pressed = true;
			m_pressedPoint = p;
		}
		else if (e.action == TouchActionE::move)
		{
			if (!m_pressed) return;

			Point ptOffset = { p.x - m_pressedPoint.x, m_pressedPoint.y - p.y };
			m_pressedPoint = p;
			auto rotate = nb::as<RotateTransform2D>(m_selNode->getTransform())->getAngle();
			rotate -= ptOffset.x;
			nb::as<RotateTransform2D>(m_selNode->getTransform())->setAngle(rotate);
			nb::as<RotateTransform2D>(m_nodeP->getTransform())->setAngle(rotate);
			nb::as<RotateTransform2D>(m_nodeR->getTransform())->setAngle(rotate);
		}
		else if (e.action == TouchActionE::up)
		{
			m_pressed = false;
		}
	}
}
