#include "AVMView.h"
#include "MainView.h"
#include "AIView.h"
#include "Tr.h"

//所有的节点初始化应当只做一遍，主题切换只切换相应的属性即可
AVMView::AVMView()
{
	MainView::get()->topbar()->switchState(TopBar::State::AVM_Bar);
	MainView::get()->topbar()->ShowMirror.clear();
	MainView::get()->topbar()->ShowRadar.clear();
	MainView::get()->topbar()->Switch2D3D.clear();
	MainView::get()->topbar()->ShowSubline.clear();
	MainView::get()->topbar()->ShowSetting.clear();
	MainView::get()->topbar()->ShowMirror += [&](const bool &e) { switchCameraState(e ? (MainView::get()->topbar()->isToggle2D3DChecked() ? CameraState::Show_3D : CameraState::Show_2D) : CameraState::Hide); };
	MainView::get()->topbar()->ShowRadar += [&](const bool &e) { showLardar(e); };
	MainView::get()->topbar()->Switch2D3D += [&](const bool &e) { switchCameraState(MainView::get()->topbar()->isToggleShowMirrorChecked() ? (e ? CameraState::Show_3D : CameraState::Show_2D) : CameraState::Hide); };
	MainView::get()->topbar()->ShowSubline += [&](const bool &e) { showLardarWarn(e); };
	MainView::get()->topbar()->ShowSetting += [&](const bool &e) { showSetting(e); };

	//左区域开始
	m_leftArea = createRef<Node2D>(0.0f, 100.0f, 600.0f, 880.0f);
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
	for (auto btn : m_btnCameras) { m_cameraParent->addChild(btn); btn->Click += nbBindEventFunction(AVMView::onBtnClick); }

	m_car = Node2D::createWithTextureFrameName(AVM, "day/car/autopark_pic_car.png", 0.0f, 0.0f);
	m_car->setAlignmentCenter();

	auto car = Node2D::createWithTextureFrameName(AVM, "day/pic_backline.png", 25.0f, 830.0f);
	m_txtDis = createRef<TextBlock>(62.0f, 840.0f, 0.0f, 0.0f);
	m_txtDis->setFontSize(32);

	m_arrows[0] = Node2D::createWithTextureFrameName(AVM, "day/pic_warning_left1.png", 35.0f, 33.0f);
	m_arrows[1] = Node2D::createWithTextureFrameName(AVM, "day/pic_warning_left1_1.png", 462.0f, 33.0f);
	m_arrows[2] = Node2D::createWithTextureFrameName(AVM, "day/pic_warning_left1.png", 35.0f, 751.0f);
	m_arrows[3] = Node2D::createWithTextureFrameName(AVM, "day/pic_warning_left1_1.png", 462.0f, 751.0f);
	m_arrows[4] = Node2D::createWithTextureFrameName(AVM, "day/pic_warning_left2.png", 140.0f, 559.0f);
	m_arrows[5] = Node2D::createWithTextureFrameName(AVM, "day/pic_warning_left2_1.png", 944.0f, 556.0f);

	for (auto i = 0u; i != m_warns.size(); ++i)
	{
		auto imgPath = std::string("day/radar_warn/") + std::to_string(i) + ".png";
		m_warns[i] = Node2D::createWithTextureFrameName(AVM, imgPath, 151.0f, 103.0f);
		m_leftArea->addChild(m_warns[i]);
	}

	m_leftArea->addChild(m_car);
	m_leftArea->addChild(m_cameraParent);
	m_leftArea->addChild(car);
	m_leftArea->addChild(m_txtDis);
	for(auto i = 0u; i <= 3; ++i)	m_leftArea->addChild(m_arrows[i]);
	//左区域结束

	//右区域
	m_rightArea = createRef<Node2D>(610.0f, 100.0f, 1310.0f, 880.0f);
	m_carView = Node2D::createWithTextureFrameName(AVM, "day/icon_carview/icon_view_car.png", 12.0f, 0.0f);
	for (char i = 'a'; i <= 'j'; ++i)
	{
		auto node = Node2D::createWithTextureFrameName(AVM, std::string("day/icon_carview/") + std::string(1, i) + ".png", 0.0f, 0.0f);
		m_carView->addChild(node);
	}
	m_warningPedestrians = Node2D::createWithTextureFrameName(AVM, "day/icon_throughalert.png", 32.0f, 150.0f);
	m_warning = Node2D::createWithTextureFrameName(AVM, "day/icon_alert2.png", 32.0f, 260.0f);
	m_setting = createRef<Node2D>(0.0f, 120.0f, 1040.0f, 705.0f, SCBR(Color(251, 252, 254, 220)));
	m_setting->setHorizontalAlignment(HorizontalAlignment::Center);
	m_setting->setVisibility(VisibilityE::Hidden);
	m_settingTitle = createRef<TextBlock>(483.0f, 46.0f, 75.0f, 36.0f);
	m_btnSettingExit = Button::createWithTextureFrameName(AVM, "day/autopark_btn_close_nor.png", 941.0f, 38.0f);
	m_btnSettingExit->Click += nbBindEventFunction(AVMView::onBtnClick);
	for (auto i = 0; i < 4; ++i)
	{
		auto line = createRef<Node2D>(60.0f, 215.0f + 115.0f * i, 920.0f, 2.0f, SCBR(Color(227, 227, 228)));
		m_setting->addChild(line);
	}
	for (auto i = 0u; i < m_txts.size(); ++i)
	{
		m_txts[i] = createRef<TextBlock>(60.0f, 148.0f + 115.0f * i, 0.0f, 0.0f);
		m_txts[i]->setFontSize(32);
		m_setting->addChild(m_txts[i]);
	}
	m_txts[5]->setPosition({ 60.0f, 660.0f });
	m_txts[6]->setPosition({ 700.0f, m_txts[5]->y() });

	auto ticonNormal = IMGBR(AVM, "day/autopark_btn_changbutton_56px_sel.png");
	auto bkgCheck = IMGBR(AVM, "day/autopark_btn_button_sel.png");
	auto iconNormal = IMGBR(AVM, "day/autopark_btn_button_dot.png");
	for (auto i = 0u; i < m_toggles.size(); ++i)
	{
		m_toggles[i] = createRef<ToggleButton>(i == 1 ? 660.0f : 897.0f, 140.0f + 115.0f * i, i == 1 ? 320.0f : 84.0f, i == 1 ? 56.0f : 46.0f);
		m_toggles[i]->setBkgndNormal(IMGBR(AVM, i == 1 ? "day/autopark_btn_changbutton_56px_nor.png" :"day/autopark_btn_button_nor.png"));
		m_toggles[i]->setBkgndCheck(i == 1 ? IMGBR(AVM, "day/autopark_btn_changbutton_56px_nor.png") : bkgCheck);
		m_toggles[i]->setIcon(i == 1 ? ticonNormal : iconNormal);
		m_toggles[i]->setIconOffset(i == 1 ? Point{ 0.0f, 0.0f } : Point{ -10.0f, -5.0f });
		m_toggles[i]->CheckChanged += nbBindEventFunction(AVMView::onToggleButton);
		m_setting->addChild(m_toggles[i]);
	}
	m_toggles[5]->setPosition({ 250.0f, m_txts[5]->y() - 5.0f });
	m_toggles[6]->setPosition({ 897.0f, m_toggles[5]->y() });
	m_txtNow = createRef<TextBlock>(53.0f, 14.0f, 0.0f, 0.0f);
	m_txtNow->setFontSize(28);
	m_txt30Senconds = createRef<TextBlock>(194.0f, 14.0f, 0.0f, 0.0f);
	m_txt30Senconds->setFontSize(28);
	m_toggles[1]->addChild(m_txtNow);
	m_toggles[1]->addChild(m_txt30Senconds);

	m_setting->addChild(m_settingTitle);
	m_setting->addChild(m_btnSettingExit);

	m_tipBg = createRef<NinePatchImage>(0.0f, 20.0f, 584.0f, 86.0f);
	m_tipBg->setHorizontalAlignment(HorizontalAlignment::Center);
	m_tipText = createRef<TextBlock>(30.0f, 0.0f, 0.0f, 0.0f);
	m_tipText->setAlignmentCenter();
	m_tipText->setFontSize(32);
	auto icon = Node2D::createWithTextureFrameName(AVM, "day/icon_alert.png", 50.0f, 0.0f);
	icon->setVerticalAlignment(VerticalAlignment::Center);
	m_tipBg->addChild(icon);
	m_tipBg->addChild(m_tipText);
	
	m_rightArea->addChild(m_carView);
	m_rightArea->addChild(m_warningPedestrians);
	m_rightArea->addChild(m_warning);
	m_rightArea->addChild(m_arrows[4]);
	m_rightArea->addChild(m_arrows[5]);
	m_rightArea->addChild(m_setting);
	m_rightArea->addChild(m_tipBg);
	//右区域结束

	addChild(m_leftArea);
	addChild(m_rightArea);

	m_timerWarning.Tick += nbBindEventFunction(AVMView::onTick);
	m_timerWarning.start(500);
	
	m_anis[0].setFrom({ 35.0f, 33.0f });
	m_anis[0].setTo({ 35.0f + 50.0f, 33.0f });
	m_anis[1].setFrom({ 462.0f, 33.0f });
	m_anis[1].setTo({ 462.0f - 50.0f, 33.0f });
	m_anis[1].setFrom({ 462.0f, 33.0f });
	m_anis[1].setTo({ 462.0f - 50.0f, 33.0f });
	m_anis[2].setFrom({ 35.0f, 751.0f });
	m_anis[2].setTo({ 35.0f + 50.0f, 751.0f });
	m_anis[3].setFrom({ 462.0f, 751.0f });
	m_anis[3].setTo({ 462.0f - 50.0f, 751.0f });
	for (auto i = 0u; i != m_anis.size(); ++i)
	{
		m_anis[i].setTarget(m_arrows[i]);
		m_anis[i].setTargetPropertyName("Position");
		m_anis[i].duration = TimeSpan::fromMilliseconds(500);
		m_anis[i].autoReverse = true;
		m_anis[i].repeatBehavior = RepeatBehavior::forever();
	}

	m_aniShowSetting.setFrom(0.0f);
	m_aniShowSetting.setTo(1.0f);
	m_aniShowSetting.setTarget(m_setting);
	m_aniShowSetting.setTargetPropertyName("Opacity");
	m_aniShowSetting.duration = TimeSpan::fromMilliseconds(250);
	m_aniShowSetting.Completed += [&](const EventArgs &e) { m_setting->setVisibility(m_aniShowSetting.reverse ? VisibilityE::Hidden : VisibilityE::Visible); };

	m_themeEventHandle = ThemeManager::ThemeChanged() += nbBindEventFunction(AVMView::onThemeChanged);
	m_languageEventHandle = LanguageManager::LanguageChanged() += nbBindEventFunction(AVMView::onLanguageChanged);
	onThemeChanged(ThemeManager::getTheme());
	onLanguageChanged(LanguageManager::getLanguage());

	showLardar(false);
	showLardarWarn(false);
	switchCameraState(CameraState::Show_2D);
	setWarningText(TR(LanguageManager::getLanguage(), TID_Tip0));
}

AVMView::~AVMView()
{
	ThemeManager::ThemeChanged() -= m_themeEventHandle;
	LanguageManager::LanguageChanged() -= m_languageEventHandle;
}

void AVMView::showSetting(bool show)
{
	m_setting->setVisibility(VisibilityE::Visible);
	m_setting->setOpacity(show ? 0.0f : 1.0f);
	m_aniShowSetting.reverse = !show;
	m_aniShowSetting.begin();
}

void AVMView::switchCameraState(CameraState state)
{
	if(state == CameraState::Hide)
	{
		for (auto child : m_cameraParent->children())
			child->setVisibility(VisibilityE::Hidden);
	}
	else
	{
		for (int i = 0; i < 4; ++i)		m_cameraParent->getChildAt(i)->setVisibility(state == CameraState::Show_2D ? VisibilityE::Visible : VisibilityE::Hidden);
		for (int i = 4; i < 10; ++i)	m_cameraParent->getChildAt(i)->setVisibility(state != CameraState::Show_2D ? VisibilityE::Visible : VisibilityE::Hidden);
		switchCamera(state == CameraState::Show_2D ? 1 : 5);
	}
	MainView::get()->topbar()->setToggleShowMirror(state != Hide);
}

void AVMView::switchCamera(int index)
{
	for (auto child : m_carView->children())
		child->setVisibility(VisibilityE::Hidden);

	m_carView->getChildAt(index)->setVisibility(VisibilityE::Visible);
	
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
	m_tipBg->setWidth((int)w + 150.0f);
}

void AVMView::showLardar(bool show)
{
	MainView::get()->topbar()->setToggleShowRadar(show);
	for (auto &arrow : m_arrows)
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
	MainView::get()->topbar()->setToggleShowSubline(show);
	for (auto &node : m_warns)
	{
		node->setVisibility(show ? VisibilityE::Visible : VisibilityE::Hidden);
	}
}

void AVMView::onBtnClick(const EventArgs & e)
{
	if (e.sender == m_btnSettingExit.get())
	{
		showSetting(false);
		MainView::get()->topbar()->setToggleSetting(false);
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
	if (e.sender == m_toggles[2].get())
	{
		auto img = m_toggles[2]->isChecked() ? IMGBR(AVM, "day/car/autopark_pic_car2.png") : IMGBR(AVM, "day/car/autopark_pic_car.png");
		m_car->setBackground(img);
	}
	else if (e.sender == m_toggles[5].get())
	{
		LanguageManager::setLanguage(m_toggles[5]->isChecked());
	}
	else if (e.sender == m_toggles[6].get())
	{
		ThemeManager::setTheme(m_toggles[6]->isChecked());
	}
}

void AVMView::onThemeChanged(const int &theme)
{
	for (auto i = 0; i != m_toggles.size(); ++i)
	{
		std::string s = theme == 0 ? "day" : "night";
		m_toggles[i]->setBkgndNormal(IMGBR(AVM, s + (i == 1 ? "/autopark_btn_changbutton_56px_nor.png" : "/autopark_btn_button_nor.png")));
	}
	m_txtDis->setColor(theme == 0 ? Colors::black : Colors::white);
	m_tipText->setColor(theme == 0 ? Colors::black : Colors::white);
	m_setting->setBackground(theme == 0 ? SCBR(Color(251, 252, 254, 220)) : SCBR(Color(5, 6, 5, 220)));
	m_settingTitle->setColor(theme == 0 ? Colors::black : Colors::white);
	m_btnSettingExit->setBkgndNormal(IMGBR(AVM, theme == 0 ? "day/autopark_btn_close_nor.png" : "night/autopark_btn_close_nor.png"));
	m_txtNow->setColor(theme == 0 ? Colors::black : Colors::white);
	m_txt30Senconds->setColor(theme == 0 ? Colors::black : Colors::white);
	m_tipBg->setImages(IMGBR(AVM, theme == 0 ? "nine0.png" : "nine00.png"), IMGBR(AVM, theme == 0 ? "nine2.png" : "nine22.png"),
		IMGBR(AVM, theme == 0 ? "nine3.png" : "nine33.png"), IMGBR(AVM, theme == 0 ? "nine1.png" : "nine11.png"), IMGBR(AVM, theme == 0 ? "nine4.png" : "nine44.png"));
	for (auto i = 0u; i < m_txts.size(); ++i)
		m_txts[i]->setColor(theme == 0 ? Colors::black : Colors::white);

	m_toggles[6]->setCheck(theme ? true : false);
}

void AVMView::onLanguageChanged(const int & lan)
{
	m_settingTitle->setText(TR(lan, TID_Setting));
	m_txts[0]->setText(TR(lan, TID_Trajectory));
	m_txts[1]->setText(TR(lan, TID_P));
	m_txts[2]->setText(TR(lan, TID_Chassis));
	m_txts[3]->setText(TR(lan, TID_RadarFullView));
	m_txts[4]->setText(TR(lan, TID_IndicatorFullView));
	m_txts[5]->setText(TR(lan, TID_Language));
	m_txts[6]->setText(TR(lan, TID_Theme));
	m_txtNow->setText(TR(lan, TID_Now));
	m_txt30Senconds->setText(TR(lan, TID_30S));
	m_txtDis->setText(TR(lan, TID_DIS));
	m_toggles[5]->setCheck(lan ? true : false);
	setWarningText(TR(lan, TID_Tip0));
}

void AVMView::onTick(const EventArgs & e)
{
	if (e.sender == &m_timerWarning)
	{
		m_warningPedestrians->setVisibility(m_warningPedestrians->visibility() == VisibilityE::Visible ? VisibilityE::Hidden: VisibilityE::Visible);
	}
}