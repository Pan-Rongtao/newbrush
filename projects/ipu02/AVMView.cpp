#include "AVMView.h"
#include "MainView.h"
#include "AIView.h"
#include "Tr.h"

//所有的节点初始化应当只做一遍，主题切换只切换相应的属性即可
AVMView::AVMView()
{
	TextureLibrary::addTextureAtlas(AVM, RES_DIR"ipu02/AVM.png", RES_DIR"ipu02/AVM.txt");

	//顶部栏初始化开始
	m_topBar = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 100.0f);
	//m_topBar->setBackground(SolidColorBrush::red());
	m_btnReturn = createRef<Button>(40.0f, 0.0f, 140.0f, 100.0f);
	m_btnReturn->setIcon(IMGBR(AVM, "day/topbar/icon_topbar_back.png"));
	m_btnReturn->setText(u8"退出");
	m_btnReturn->setIconTextOffset({6.0f, 27.0f}, { 60.0f, 35.0f });
	m_btnReturn->setTextColor(Colors::black, Color(0, 0, 0, 150));
	m_btnSwithToAutoPark = Button::createWithTextureFrameName(AVM, "day/topbar/autopark_btn_park_nor.png", 621.0f, 0.0f);
	m_btnSwithToAutoPark->setBkgndPress(IMGBR(AVM, "day/topbar/autopark_btn_park_sel.png"));
	m_toggleShowMirror = createRef<ToggleButton>(765.0f, 0.0f, 100.0f, 100.0f, IMGBR(AVM, "day/topbar/autopark_btn_mirror_nor.png"), IMGBR(AVM, "day/topbar/autopark_btn_mirror_sel.png"));
	m_toggleShowRadar = createRef<ToggleButton>(909.0f, 0.0f, 100.0f, 100.0f, IMGBR(AVM, "day/topbar/autopark_btn_radar_nor.png"), IMGBR(AVM, "day/topbar/autopark_btn_radar_sel.png"));
	m_toggleShowSubline = createRef<ToggleButton>(1521.0f, 0.0f, 100.0f, 100.0f, IMGBR(AVM, "day/topbar/btn_backline_nor.png"), IMGBR(AVM, "day/topbar/btn_backline_sel.png"));
	m_toggleSetting = createRef<ToggleButton>(1665.0f, 0.0f, 100.0f, 100.0f, IMGBR(AVM, "day/topbar/autopark_btn_set_nor.png"), IMGBR(AVM, "day/topbar/autopark_btn_set_sel.png"));

	m_toggle2D3D = createRef<ToggleButton>(1065.0f, 19.0f, 400.0f, 62.0f, IMGBR(AVM, "day/topbar/autopark_btn_23d_62px_nor.png"), IMGBR(AVM, "day/topbar/autopark_btn_23d_62px_nor.png"));
	m_toggle2D3D->setBkgndNormal(IMGBR(AVM, "day/topbar/autopark_btn_23d_62px_nor.png"));
	m_toggle2D3D->setIcon(IMGBR(AVM, "day/topbar/autopark_btn_23d_62px_sel.png"));
	auto icon0 = Node2D::createWithTextureFrameName(AVM, "day/topbar/autopark_text_2d-sel.png", 0.0f, 0.0f);
	auto icon1 = Node2D::createWithTextureFrameName(AVM, "day/topbar/autopark_text_3d-sel.png", 200.0f, 0.0f);
	m_toggle2D3D->addChild(icon0);
	m_toggle2D3D->addChild(icon1);

	m_btnSwithToAutoPark->Click += nbBindEventFunction(AVMView::onBtnClick);
	m_toggleShowMirror->CheckChanged += nbBindEventFunction(AVMView::onToggleButton);
	m_toggleShowRadar->CheckChanged += nbBindEventFunction(AVMView::onToggleButton);
	m_toggleShowSubline->CheckChanged += nbBindEventFunction(AVMView::onToggleButton);
	m_toggleSetting->CheckChanged += nbBindEventFunction(AVMView::onToggleButton);
	m_toggle2D3D->CheckChanged += nbBindEventFunction(AVMView::onToggleButton);

	m_topBar->addChild(m_btnReturn);
	m_topBar->addChild(m_btnSwithToAutoPark);
	m_topBar->addChild(m_toggleShowMirror);
	m_topBar->addChild(m_toggleShowRadar);
	m_topBar->addChild(m_toggleShowSubline);
	m_topBar->addChild(m_toggleSetting);
	m_topBar->addChild(m_toggle2D3D);

	//顶部栏初始化结束

	//左区域开始
	m_leftArea = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f);
	//m_leftArea->setBackground(SolidColorBrush::blue());
	m_cameraParent = createRef<Node2D>();
	m_btnCameras[0] = Button::createWithTextureFrameName(AVM, "day/cam/0_n.png", 52.0f, 403.0f);
	m_btnCameras[0]->setBkgndPress(IMGBR(AVM, "day/cam/0_p.png"));
	m_btnCameras[0]->setBkgndCheck(IMGBR(AVM, "day/cam/0_p.png"));
	m_btnCameras[1] = Button::createWithTextureFrameName(AVM, "day/cam/2_n.png", 250.0f, 44.0f);
	m_btnCameras[1]->setBkgndPress(IMGBR(AVM, "day/cam/2_p.png"));
	m_btnCameras[1]->setBkgndCheck(IMGBR(AVM, "day/cam/2_p.png"));
	m_btnCameras[2] = Button::createWithTextureFrameName(AVM, "day/cam/4_n.png", 448.0f, 403.0f);
	m_btnCameras[2]->setBkgndPress(IMGBR(AVM, "day/cam/4_p.png"));
	m_btnCameras[2]->setBkgndDisable(IMGBR(AVM, "day/cam/4_d.png"));
	m_btnCameras[2]->setEnable(false);
	m_btnCameras[3] = Button::createWithTextureFrameName(AVM, "day/cam/6_n.png", 250.0f, 736.0f);
	m_btnCameras[3]->setBkgndPress(IMGBR(AVM, "day/cam/6_p.png"));
	m_btnCameras[3]->setBkgndCheck(IMGBR(AVM, "day/cam/6_p.png"));
	m_btnCameras[4] = Button::createWithTextureFrameName(AVM, "day/cam/1_n.png", 64.0f, 44.0f);
	m_btnCameras[4]->setBkgndPress(IMGBR(AVM, "day/cam/1_p.png"));
	m_btnCameras[4]->setBkgndCheck(IMGBR(AVM, "day/cam/1_p.png"));
	m_btnCameras[5] = Button::createWithTextureFrameName(AVM, "day/cam/6_n.png", 250.0f, 44.0f);
	m_btnCameras[5]->setBkgndPress(IMGBR(AVM, "day/cam/6_p.png"));
	m_btnCameras[5]->setBkgndCheck(IMGBR(AVM, "day/cam/6_p.png"));
	m_btnCameras[6] = Button::createWithTextureFrameName(AVM, "day/cam/3_n.png", 436.0f, 44.0f);
	m_btnCameras[6]->setBkgndPress(IMGBR(AVM, "day/cam/3_p.png"));
	m_btnCameras[6]->setBkgndCheck(IMGBR(AVM, "day/cam/3_p.png"));
	m_btnCameras[7] = Button::createWithTextureFrameName(AVM, "day/cam/5_n.png", 436.0f, 736.0f);
	m_btnCameras[7]->setBkgndPress(IMGBR(AVM, "day/cam/5_p.png"));
	m_btnCameras[7]->setBkgndCheck(IMGBR(AVM, "day/cam/5_p.png"));
	m_btnCameras[8] = Button::createWithTextureFrameName(AVM, "day/cam/2_n.png", 250.0f, 736.0f);
	m_btnCameras[8]->setBkgndPress(IMGBR(AVM, "day/cam/2_p.png"));
	m_btnCameras[8]->setBkgndCheck(IMGBR(AVM, "day/cam/2_p.png"));
	m_btnCameras[9] = Button::createWithTextureFrameName(AVM, "day/cam/7_n.png", 64.0f, 736.0f);
	m_btnCameras[9]->setBkgndPress(IMGBR(AVM, "day/cam/7_p.png"));
	m_btnCameras[9]->setBkgndCheck(IMGBR(AVM, "day/cam/7_p.png"));
	for (auto node : m_btnCameras)	m_cameraParent->addChild(node);

	m_car = Node2D::createWithTextureFrameName(AVM, "day/car/autopark_pic_car.png", 0.0f, 0.0f);
	m_car->setAlignmentCenter();

	for (auto btn : m_btnCameras)
	{
		btn->Click += nbBindEventFunction(AVMView::onBtnClick);
	}

	auto car = Node2D::createWithTextureFrameName(AVM, "day/pic_backline.png", 25.0f, 830.0f);
	m_txtDis = createRef<TextBlock>(62.0f, 840.0f, 0.0f, 0.0f, u8"50米");

	m_arrows[0] = Node2D::createWithTextureFrameName(AVM, "day/pic_warning_left1.png", 35.0f, 33.0f);
	m_arrows[1] = Node2D::createWithTextureFrameName(AVM, "day/pic_warning_left1_1.png", 462.0f, 33.0f);
	m_arrows[2] = Node2D::createWithTextureFrameName(AVM, "day/pic_warning_left1.png", 35.0f, 751.0f);
	m_arrows[3] = Node2D::createWithTextureFrameName(AVM, "day/pic_warning_left1_1.png", 462.0f, 751.0f);
	m_arrows[4] = Node2D::createWithTextureFrameName(AVM, "day/pic_warning_left2.png", 140.0f, 559.0f);
	m_arrows[5] = Node2D::createWithTextureFrameName(AVM, "day/pic_warning_left2_1.png", 944.0f, 556.0f);

	m_warns[0] = Node2D::createWithTextureFrameName(AVM, "day/radar_warn/0.png", 151.0f, 103.0f);
	m_warns[1] = Node2D::createWithTextureFrameName(AVM, "day/radar_warn/1.png", 151.0f, 103.0f);
	m_warns[2] = Node2D::createWithTextureFrameName(AVM, "day/radar_warn/2.png", 151.0f, 103.0f);
	m_warns[3] = Node2D::createWithTextureFrameName(AVM, "day/radar_warn/3.png", 151.0f, 103.0f);
	m_warns[4] = Node2D::createWithTextureFrameName(AVM, "day/radar_warn/4.png", 151.0f, 103.0f);
	m_warns[5] = Node2D::createWithTextureFrameName(AVM, "day/radar_warn/5.png", 151.0f, 103.0f);
	m_warns[6] = Node2D::createWithTextureFrameName(AVM, "day/radar_warn/6.png", 151.0f, 103.0f);
	m_warns[7] = Node2D::createWithTextureFrameName(AVM, "day/radar_warn/7.png", 151.0f, 103.0f);
	m_warns[8] = Node2D::createWithTextureFrameName(AVM, "day/radar_warn/8.png", 151.0f, 103.0f);
	m_warns[9] = Node2D::createWithTextureFrameName(AVM, "day/radar_warn/9.png", 151.0f, 103.0f);
	m_warns[10] = Node2D::createWithTextureFrameName(AVM, "day/radar_warn/a.png", 151.0f, 103.0f);
	m_warns[11] = Node2D::createWithTextureFrameName(AVM, "day/radar_warn/b.png", 151.0f, 103.0f);

	m_leftArea->addChild(m_car);
	m_leftArea->addChild(m_cameraParent);
	m_leftArea->addChild(car);
	m_leftArea->addChild(m_txtDis);
	m_leftArea->addChild(m_arrows[0]);
	m_leftArea->addChild(m_arrows[1]);
	m_leftArea->addChild(m_arrows[2]);
	m_leftArea->addChild(m_arrows[3]);
	for (auto node : m_warns)
	{
		m_leftArea->addChild(node);
	}
	//左区域结束

	//右区域
	m_rightArea = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	//m_rightArea->setBackground(SolidColorBrush::blue());
	m_carView = Node2D::createWithTextureFrameName(AVM, "day/icon_carview/icon_view_car.png", 12.0f, 0.0f);
	for (char i = 'a'; i <= 'j'; ++i)
	{
		auto node = Node2D::createWithTextureFrameName(AVM, std::string("day/icon_carview/") + std::string(1, i) + ".png", 0.0f, 0.0f);
		m_carView->addChild(node);
	}
	m_warningPedestrians = Node2D::createWithTextureFrameName(AVM, "day/icon_throughalert.png", 32.0f, 150.0f);
	m_warning = Node2D::createWithTextureFrameName(AVM, "day/icon_alert2.png", 32.0f, 260.0f);
	m_setting = createRef<Node2D>(0.0f, 120.0f, 1040.0f, 705.0f, SCBR(Color(251, 252, 254, 220)));
	m_setting->setHorizontalAlignment(HorizontalAlignmentE::Center);
	//m_setting->setAlignmentCenter();
	m_settingTitle = createRef<TextBlock>(483.0f, 46.0f, 75.0f, 36.0f, u8"设置");
	m_btnSettingExit = Button::createWithTextureFrameName(AVM, "day/autopark_btn_close_nor.png", 941.0f, 38.0f);
	m_btnSettingExit->Click += nbBindEventFunction(AVMView::onBtnClick);
	auto line0 = createRef<Node2D>(60.0f, 215.0f, 920.0f, 2.0f, SCBR(Color(227, 227, 228)));
	auto line1 = createRef<Node2D>(60.0f, 329.0f, 920.0f, 2.0f, SCBR(Color(227, 227, 228)));
	auto line2 = createRef<Node2D>(60.0f, 443.0f, 920.0f, 2.0f, SCBR(Color(227, 227, 228)));
	auto line3 = createRef<Node2D>(60.0f, 557.0f, 920.0f, 2.0f, SCBR(Color(227, 227, 228)));
	m_txt0 = createRef<TextBlock>(60.0f, 141.0f, 0.0f, 0.0f, u8"轨迹线");
	m_txt1 = createRef<TextBlock>(60.0f, 256.0f, 0.0f, 0.0f, u8"P档退出");
	m_txt2 = createRef<TextBlock>(60.0f, 371.0f, 0.0f, 0.0f, u8"透明底盘");
	m_txt3 = createRef<TextBlock>(60.0f, 484.0f, 0.0f, 0.0f, u8"雷达激活全景");
	m_txt4 = createRef<TextBlock>(60.0f, 599.0f, 0.0f, 0.0f, u8"转向灯激活全景");
	m_txt5 = createRef<TextBlock>(60.0f, 650.0f, 0.0f, 0.0f, u8"切换语言");
	m_txt6 = createRef<TextBlock>(700.0f, 650.0f, 0.0f, 0.0f, u8"切换主题");

	auto ticonNormal = IMGBR(AVM, "day/autopark_btn_changbutton_56px_sel.png");
	auto bkgCheck = IMGBR(AVM, "day/autopark_btn_button_sel.png");
	auto iconNormal = IMGBR(AVM, "day/autopark_btn_button_dot.png");
	m_toggleTrajectory = createRef<ToggleButton>(897.0f, 140.0f, 84.0f, 46.0f);
	m_toggleTrajectory->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_button_nor.png"));
	m_toggleTrajectory->setBkgndCheck(bkgCheck);
	m_toggleTrajectory->setIcon(iconNormal);
	m_toggleTrajectory->setIconOffset({ -10.0f, -5.0f });
	m_toggleTrajectory->CheckChanged += nbBindEventFunction(AVMView::onToggleButton);
	m_toggleP = createRef<ToggleButton>(640.0f, 245.0f, 320.0f, 56.0f);
	m_toggleP->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_changbutton_56px_nor.png"));
	m_toggleP->setBkgndCheck(IMGBR(AVM, "day/autopark_btn_changbutton_56px_nor.png"));
	m_toggleP->setIcon(ticonNormal);
	m_toggleP->setIconOffset({ 0.0f, 0.0f });
	m_toggleP->CheckChanged += nbBindEventFunction(AVMView::onToggleButton);
	m_txtNow = createRef<TextBlock>(53.0f, 14.0f, 0.0f, 0.0f, u8"立刻");
	m_txt30Senconds = createRef<TextBlock>(194.0f, 14.0f, 0.0f, 0.0f, u8"30秒后");
	m_toggleP->addChild(m_txtNow);
	m_toggleP->addChild(m_txt30Senconds);
	m_toggleChassis = createRef<ToggleButton>(897.0f, 368.0f, 84.0f, 46.0f);
	m_toggleChassis->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_button_nor.png"));
	m_toggleChassis->setBkgndCheck(bkgCheck);
	m_toggleChassis->setIcon(iconNormal);
	m_toggleChassis->setIconOffset({ -10.0f, -5.0f });
	m_toggleChassis->CheckChanged += nbBindEventFunction(AVMView::onToggleButton);
	m_toggleRadarFullView = createRef<ToggleButton>(897.0f, 482.0f, 84.0f, 46.0f);
	m_toggleRadarFullView->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_button_nor.png"));
	m_toggleRadarFullView->setBkgndCheck(bkgCheck);
	m_toggleRadarFullView->setIcon(iconNormal);
	m_toggleRadarFullView->setIconOffset({ -10.0f, -5.0f });
	m_toggleRadarFullView->CheckChanged += nbBindEventFunction(AVMView::onToggleButton);
	m_toggleIndicatorFullView = createRef<ToggleButton>(897.0f, 595.0f, 84.0f, 46.0f);
	m_toggleIndicatorFullView->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_button_nor.png"));
	m_toggleIndicatorFullView->setBkgndCheck(bkgCheck);
	m_toggleIndicatorFullView->setIcon(iconNormal);
	m_toggleIndicatorFullView->setIconOffset({ -10.0f, -5.0f });
	m_toggleIndicatorFullView->CheckChanged += nbBindEventFunction(AVMView::onToggleButton);
	m_toggleLan = createRef<ToggleButton>(250.0f, 645.0f, 84.0f, 46.0f);
	m_toggleLan->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_button_nor.png"));
	m_toggleLan->setBkgndCheck(bkgCheck);
	m_toggleLan->setIcon(iconNormal);
	m_toggleLan->setIconOffset({ -10.0f, -5.0f });
	m_toggleLan->CheckChanged += nbBindEventFunction(AVMView::onToggleButton);
	m_toggleTheme = createRef<ToggleButton>(897.0f, 645.0f, 84.0f, 46.0f);
	m_toggleTheme->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_button_nor.png"));
	m_toggleTheme->setBkgndCheck(bkgCheck);
	m_toggleTheme->setIcon(iconNormal);
	m_toggleTheme->setIconOffset({ -10.0f, -5.0f });
	m_toggleTheme->CheckChanged += nbBindEventFunction(AVMView::onToggleButton);
		
	m_setting->addChild(m_settingTitle);
	m_setting->addChild(m_btnSettingExit);
	m_setting->addChild(line0);
	m_setting->addChild(line1);
	m_setting->addChild(line2);
	m_setting->addChild(line3);
	m_setting->addChild(m_txt0);
	m_setting->addChild(m_txt1);
	m_setting->addChild(m_txt2);
	m_setting->addChild(m_txt3); 
	m_setting->addChild(m_txt4);
	m_setting->addChild(m_txt5);
	m_setting->addChild(m_txt6);
	m_setting->addChild(m_toggleTrajectory);
	m_setting->addChild(m_toggleP);
	m_setting->addChild(m_toggleChassis);
	m_setting->addChild(m_toggleRadarFullView);
	m_setting->addChild(m_toggleIndicatorFullView);
	m_setting->addChild(m_toggleLan);
	m_setting->addChild(m_toggleTheme);

	m_tipBg = createRef<NinePatchImage>(0.0f, 20.0f, 584.0f, 86.0f);
	m_tipBg->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_tipText = createRef<TextBlock>(u8"");
	m_tipText->setAlignmentCenter();
	m_tipBg->addChild(m_tipText);
	
	m_rightArea->addChild(m_carView);
	m_rightArea->addChild(m_warningPedestrians);
	m_rightArea->addChild(m_warning);
	m_rightArea->addChild(m_arrows[4]);
	m_rightArea->addChild(m_arrows[5]);
	m_rightArea->addChild(m_setting);
	m_rightArea->addChild(m_tipBg);

	//右区域结束

	addChild(m_topBar); 
	addChild(m_leftArea);
	addChild(m_rightArea);

	switchCameraState(CameraState::Show_2D);

	m_timerWarning.Tick += nbBindEventFunction(AVMView::onTick);
	m_timerWarning.start(500);

	m_smWarning = createRef<StateManager>(2);
	(*m_smWarning)[0]->assignProperty(m_warningPedestrians, nb::prop<Node2D>("Background"), IMGBR(AVM, ""));
	(*m_smWarning)[1]->assignProperty(m_warningPedestrians, nb::prop<Node2D>("Background"), IMGBR(AVM, "day/icon_throughalert.png"));
	m_smWarning->gotoState(0);

	m_themeEventHandle = ThemeManager::ThemeChanged() += nbBindEventFunction(AVMView::onThemeChanged);
	onThemeChanged(ThemeManager::getTheme());
	m_languageEventHandle = LanguageManager::LanguageChanged() += nbBindEventFunction(AVMView::onLanguageChanged);

	setWarningText(TR(LanguageManager::getLanguage(), TID_Tip0));
	
	m_anis[0].setFrom({ 35.0f, 33.0f });
	m_anis[0].setTo({ 35.0f + 50.0f, 33.0f });
	m_anis[0].setTarget(m_arrows[0]);
	m_anis[0].setTargetPropertyName("Position");
	m_anis[0].duration = TimeSpan::fromMilliseconds(500);
	m_anis[0].autoReverse = true;
	m_anis[0].repeatBehavior = RepeatBehavior::forever();

	m_anis[1].setFrom({ 462.0f, 33.0f });
	m_anis[1].setTo({ 462.0f - 50.0f, 33.0f });
	m_anis[1].setTarget(m_arrows[1]);
	m_anis[1].setTargetPropertyName("Position");
	m_anis[1].duration = TimeSpan::fromMilliseconds(500);
	m_anis[1].autoReverse = true;
	m_anis[1].repeatBehavior = RepeatBehavior::forever();

	m_anis[2].setFrom({ 35.0f, 751.0f });
	m_anis[2].setTo({ 35.0f + 50.0f, 751.0f });
	m_anis[2].setTarget(m_arrows[2]);
	m_anis[2].setTargetPropertyName("Position");
	m_anis[2].duration = TimeSpan::fromMilliseconds(500);
	m_anis[2].autoReverse = true;
	m_anis[2].repeatBehavior = RepeatBehavior::forever();

	m_anis[3].setFrom({ 462.0f, 751.0f });
	m_anis[3].setTo({ 462.0f - 50.0f, 751.0f });
	m_anis[3].setTarget(m_arrows[3]);
	m_anis[3].setTargetPropertyName("Position");
	m_anis[3].duration = TimeSpan::fromMilliseconds(500);
	m_anis[3].autoReverse = true;
	m_anis[3].repeatBehavior = RepeatBehavior::forever();

	m_aniShowSetting.setFrom(0.0f);
	m_aniShowSetting.setTo(1.0f);
	m_aniShowSetting.setTarget(m_setting);
	m_aniShowSetting.setTargetPropertyName("Opacity");
	m_aniShowSetting.duration = TimeSpan::fromMilliseconds(250);
	m_aniShowSetting.Completed += [&](const EventArgs &e)
	{
		m_setting->setVisibility(m_aniShowSetting.reverse ? VisibilityE::Hidden : VisibilityE::Visible);
	};

	showLardar(false);
	showLardarWarn(false);
	m_setting->setVisibility(VisibilityE::Hidden);
}

AVMView::~AVMView()
{
	ThemeManager::ThemeChanged() -= m_themeEventHandle;
	LanguageManager::LanguageChanged() -= m_languageEventHandle;
}

void AVMView::showSetting(bool show)
{
	if (show)
	{
		m_setting->setVisibility(VisibilityE::Visible);
		m_setting->setOpacity(0.0f);
		m_aniShowSetting.reverse = false;
	}
	else
	{
		m_setting->setVisibility(VisibilityE::Visible);
		m_setting->setOpacity(1.0f);
		m_aniShowSetting.reverse = true;
	}
	m_aniShowSetting.begin();
}

void AVMView::switchCameraState(CameraState state)
{
	if(state == CameraState::Hide)
	{
		for (auto child : m_cameraParent->children())	child->setVisibility(VisibilityE::Hidden);
	}
	else
	{
		for (int i = 0; i < 4; ++i)		m_cameraParent->getChildAt(i)->setVisibility(state == CameraState::Show_2D ? VisibilityE::Visible : VisibilityE::Hidden);
		for (int i = 4; i < 10; ++i)	m_cameraParent->getChildAt(i)->setVisibility(state != CameraState::Show_2D ? VisibilityE::Visible : VisibilityE::Hidden);

		switchCamera(state == CameraState::Show_2D ? 1 : 5);
	}

	m_toggleShowMirror->setCheck(state != Hide);
}

void AVMView::switchCamera(int index)
{
	for (auto child : m_carView->children())
		child->setVisibility(VisibilityE::Hidden);

	m_carView->getChildAt(index)->setVisibility(VisibilityE::Visible);
	
	int cameraClickIndex = -1;
	for (uint32_t i = 0; i < m_cameraParent->childCount(); ++i)
	{
		auto btn = as<Button>(m_cameraParent->getChildAt(i));
		auto icon = m_carView->getChildAt(i);
		btn->setCheck(i == index);
		icon->setVisibility(i == index ? VisibilityE::Visible : VisibilityE::Hidden);
	}
}

void AVMView::setWarningText(const std::string & txt)
{
	m_tipText->setText(txt);
	auto w = m_tipText->getActualFont()->measure(txt).width;
	m_tipBg->setWidth((int)w + 100.0f);
}

void AVMView::showLardar(bool show)
{
	m_toggleShowRadar->setCheck(show);
	for (auto arrow : m_arrows)
	{
		arrow->setVisibility(show ? VisibilityE::Visible : VisibilityE::Hidden);
	}
	for (auto &ani : m_anis)
	{
		show ? ani.begin() : ani.stop();
	}
}

void AVMView::showLardarWarn(bool show)
{
	m_toggleShowSubline->setCheck(show);
	for (auto node : m_warns)
	{
		node->setVisibility(show ? VisibilityE::Visible : VisibilityE::Hidden);
	}
}

void AVMView::onBtnClick(const EventArgs & e)
{
	if (e.sender == m_btnReturn.get())
	{

	}
	else if (e.sender == m_btnSwithToAutoPark.get())
	{
		MainView::get()->switchView<AIView>();
	}
	else if (e.sender == m_btnSettingExit.get())
	{
		showSetting(false);
	}
	else
	{
		int cameraClickIndex = -1;
		for (uint32_t i = 0; i < m_cameraParent->childCount(); ++i)
		{
			if (m_cameraParent->getChildAt(i).get() == e.sender)
			{
				cameraClickIndex = i;
				break;
			}
		}
		if (cameraClickIndex != -1)
		{
			switchCamera(cameraClickIndex);
		}
	}
}

void AVMView::onToggleButton(const EventArgs & e)
{
	if (e.sender == m_toggleShowMirror.get())
	{
		switchCameraState(m_toggleShowMirror->isChecked() ? (m_toggle2D3D->isChecked() ? CameraState::Show_3D : CameraState::Show_2D): CameraState::Hide);
	}
	else if (e.sender == m_toggleShowRadar.get())
	{
		showLardar(m_toggleShowRadar->isChecked());
	}
	else if (e.sender == m_toggle2D3D.get())
	{
		switchCameraState(m_toggleShowMirror->isChecked() ? (m_toggle2D3D->isChecked() ? CameraState::Show_3D : CameraState::Show_2D) : CameraState::Hide);
	}
	else if (e.sender == m_toggleShowSubline.get())
	{
		showLardarWarn(m_toggleShowSubline->isChecked());
	}
	else if (e.sender == m_toggleSetting.get())
	{
		showSetting(m_toggleSetting->isChecked());
	}
	else if (e.sender == m_toggleChassis.get())
	{
		auto img = m_toggleChassis->isChecked() ? IMGBR(AVM, "day/car/autopark_pic_car2.png") : IMGBR(AVM, "day/car/autopark_pic_car.png");
		m_car->setBackground(img);
	}
	else if (e.sender == m_toggleLan.get())
	{
		LanguageManager::setLanguage(m_toggleLan->isChecked());
	}
	else if (e.sender == m_toggleTheme.get())
	{
		ThemeManager::setTheme(m_toggleTheme->isChecked());
	}
}

void AVMView::onThemeChanged(const int &theme)
{
	if (theme == 0)
	{
		m_btnReturn->setIcon(IMGBR(AVM, "day/topbar/icon_topbar_back.png"));
		m_btnReturn->setTextColor(Colors::black, Color(0, 0, 0, 150));
		m_btnSwithToAutoPark->setBkgndNormal(IMGBR(AVM, "day/topbar/autopark_btn_park_nor.png"));
		m_btnSwithToAutoPark->setBkgndPress(IMGBR(AVM, "day/topbar/autopark_btn_park_sel.png"));
		m_toggleShowMirror->setIcon(IMGBR(AVM, "day/topbar/autopark_btn_mirror_nor.png"), nullptr, IMGBR(AVM, "day/topbar/autopark_btn_mirror_sel.png"));
		m_toggleShowRadar->setIcon(IMGBR(AVM, "day/topbar/autopark_btn_radar_nor.png"), nullptr, IMGBR(AVM, "day/topbar/autopark_btn_radar_sel.png"));
		m_toggleShowSubline->setIcon(IMGBR(AVM, "day/topbar/btn_backline_nor.png"), nullptr, IMGBR(AVM, "day/topbar/btn_backline_sel.png"));
		m_toggleSetting->setIcon(IMGBR(AVM, "day/topbar/autopark_btn_set_nor.png"), nullptr, IMGBR(AVM, "day/topbar/autopark_btn_set_sel.png"));
		m_toggle2D3D->setBkgndNormal(IMGBR(AVM, "day/topbar/autopark_btn_23d_62px_nor.png"));

		m_txtDis->setColor(Colors::black);

		m_tipBg->setImages(IMGBR(AVM, "nine0.png"), IMGBR(AVM, "nine2.png"), IMGBR(AVM, "nine3.png"), IMGBR(AVM, "nine1.png"), IMGBR(AVM, "nine4.png"));
		m_tipText->setColor(Colors::black);
		m_setting->setBackground(SCBR(Color(251, 252, 254, 220)));
		m_settingTitle->setColor(Colors::black);
		m_btnSettingExit->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_close_nor.png"));
		m_txt0->setColor(Colors::black);
		m_txt1->setColor(Colors::black);
		m_txt2->setColor(Colors::black);
		m_txt3->setColor(Colors::black);
		m_txt4->setColor(Colors::black);
		m_txt5->setColor(Colors::black);
		m_txt6->setColor(Colors::black);
		m_txtNow->setColor(Colors::black);
		m_txt30Senconds->setColor(Colors::black);
		m_toggleP->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_changbutton_56px_nor.png"));
		m_toggleTrajectory->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_button_nor.png"));
		m_toggleChassis->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_button_nor.png"));
		m_toggleRadarFullView->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_button_nor.png"));
		m_toggleIndicatorFullView->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_button_nor.png"));
		m_toggleLan->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_button_nor.png"));
		m_toggleTheme->setBkgndNormal(IMGBR(AVM, "day/autopark_btn_button_nor.png"));
	}
	else
	{
		m_btnReturn->setIcon(IMGBR(AVM, "night/icon_topbar_back.png"));
		m_btnReturn->setTextColor(Colors::white, Color(255, 255, 255, 150));
		m_btnSwithToAutoPark->setBkgndNormal(IMGBR(AVM, "night/autopark_btn_park_nor.png"));
		m_btnSwithToAutoPark->setBkgndPress(IMGBR(AVM, "night/autopark_btn_park_sel.png"));
		m_toggleShowMirror->setIcon(IMGBR(AVM, "night/autopark_btn_mirror_nor.png"), nullptr, IMGBR(AVM, "night/autopark_btn_mirror_sel.png"));
		m_toggleShowRadar->setIcon(IMGBR(AVM, "night/autopark_btn_radar_nor.png"), nullptr, IMGBR(AVM, "night/autopark_btn_radar_sel.png"));
		m_toggleShowSubline->setIcon(IMGBR(AVM, "night/btn_backline_nor.png"), nullptr, IMGBR(AVM, "night/btn_backline_sel.png"));
		m_toggleSetting->setIcon(IMGBR(AVM, "night/autopark_btn_set_nor.png"), nullptr, IMGBR(AVM, "night/autopark_btn_set_sel.png"));
		m_toggle2D3D->setBkgndNormal(IMGBR(AVM, "night/autopark_btn_23d_62px_nor.png"));

		m_txtDis->setColor(Colors::white);

		m_tipBg->setImages(IMGBR(AVM, "nine00.png"), IMGBR(AVM, "nine22.png"), IMGBR(AVM, "nine33.png"), IMGBR(AVM, "nine11.png"), IMGBR(AVM, "nine44.png"));
		m_tipText->setColor(Colors::white);
		m_setting->setBackground(SCBR(Color(5, 6, 5, 220)));
		m_settingTitle->setColor(Colors::white);
		m_btnSettingExit->setBkgndNormal(IMGBR(AVM, "night/autopark_btn_close_nor.png"));
		m_txt0->setColor(Colors::white);
		m_txt1->setColor(Colors::white);
		m_txt2->setColor(Colors::white);
		m_txt3->setColor(Colors::white);
		m_txt4->setColor(Colors::white);
		m_txt5->setColor(Colors::white);
		m_txt6->setColor(Colors::white);
		m_txtNow->setColor(Colors::white);
		m_txt30Senconds->setColor(Colors::white);
		m_toggleP->setBkgndNormal(IMGBR(AVM, "night/autopark_btn_changbutton_56px_nor.png"));
		m_toggleTrajectory->setBkgndNormal(IMGBR(AVM, "night/autopark_btn_button_nor.png"));
		m_toggleChassis->setBkgndNormal(IMGBR(AVM, "night/autopark_btn_button_nor.png"));
		m_toggleRadarFullView->setBkgndNormal(IMGBR(AVM, "night/autopark_btn_button_nor.png"));
		m_toggleIndicatorFullView->setBkgndNormal(IMGBR(AVM, "night/autopark_btn_button_nor.png"));
		m_toggleLan->setBkgndNormal(IMGBR(AVM, "night/autopark_btn_button_nor.png"));
		m_toggleTheme->setBkgndNormal(IMGBR(AVM, "night/autopark_btn_button_nor.png"));
	}
}

void AVMView::onLanguageChanged(const int & lan)
{
	m_btnReturn->setText(TR(lan, TID_Exit));
	m_settingTitle->setText(TR(lan, TID_Setting));
	m_txt0->setText(TR(lan, TID_Trajectory));
	m_txt1->setText(TR(lan, TID_P));
	m_txt2->setText(TR(lan, TID_Chassis));
	m_txt3->setText(TR(lan, TID_RadarFullView));
	m_txt4->setText(TR(lan, TID_IndicatorFullView));
	m_txt5->setText(TR(lan, TID_Language));
	m_txt6->setText(TR(lan, TID_Theme));
	m_txtNow->setText(TR(lan, TID_Now));
	m_txt30Senconds->setText(TR(lan, TID_30S));
	setWarningText(TR(lan, TID_Tip0));
}

void AVMView::onTick(const EventArgs & e)
{
	if (e.sender == &m_timerWarning)
	{
		m_smWarning->gotoNextState();
	}
}