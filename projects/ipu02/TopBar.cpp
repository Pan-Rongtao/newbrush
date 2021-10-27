#include "TopBar.h"
#include "Tr.h"
#include "MainView.h"
#include "HPAView.h"
#include "AVMView.h"
#include "AIView.h"

TopBar::TopBar()
{
	TextureLibrary::addTextureAtlas(AVM, RES_DIR"ipu02/avm.png", RES_DIR"ipu02/avm.txt");
	setRect({ 0.0f, 0.0f, 1920.0f, 100.0f });

	/*avm״̬*/
	m_btnReturn = createRef<Button>(40.0f, 0.0f, 140.0f, 100.0f);
	m_btnReturn->setIcon(IMGBR(AVM, "day/topbar/icon_topbar_back.png"));
	m_btnReturn->setIconTextOffset({ 6.0f, 27.0f }, { 60.0f, 35.0f });
	m_btnReturn->setTextColor(Colors::black, Color(0, 0, 0, 150));
	m_btnReturn->setFontSize(32);
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

	m_btnReturn->Click += nbBindEventFunction(TopBar::onBtnClick);
	m_btnSwithToAutoPark->Click += nbBindEventFunction(TopBar::onBtnClick);
	m_toggleShowMirror->CheckChanged += nbBindEventFunction(TopBar::onToggleButton);
	m_toggleShowRadar->CheckChanged += nbBindEventFunction(TopBar::onToggleButton);
	m_toggleShowSubline->CheckChanged += nbBindEventFunction(TopBar::onToggleButton);
	m_toggleSetting->CheckChanged += nbBindEventFunction(TopBar::onToggleButton);
	m_toggle2D3D->CheckChanged += nbBindEventFunction(TopBar::onToggleButton);

	addChild(m_btnReturn);
	addChild(m_btnSwithToAutoPark);
	addChild(m_toggleShowMirror);
	addChild(m_toggleShowRadar);
	addChild(m_toggleShowSubline);
	addChild(m_toggleSetting);
	addChild(m_toggle2D3D);

	m_slideBtn = createRef<SlideButton>(0.0f, 19.0f, 800.0f, 62.0f);
	m_slideBtn->setHorizontalAlignment(HorizontalAlignment::Center);
	m_slideBtn->setBackground(IMGBR(AVM, "btn_62px_nor.9.png"));
	m_slideBtn->setBtn(IMGBR(AVM, "day/topbar/autopark_btn_23d_62px_sel.png"));
	m_slideBtn->addItem(u8"");
	m_slideBtn->addItem(u8"");
	m_slideBtn->addItem(u8"");
	m_slideBtn->addItem(u8"");
	m_slideBtn->setTextColor(Colors::black, Colors::white, Colors::gray);
	//m_slideBtn->setFontSize(28);
	m_slideBtn->SelectChanged += nbBindEventFunction(TopBar::onSlideBtnSelectChanged);
	m_slideBtn->setCurSel(0);
	addChild(m_slideBtn);

	switchState(State::AVM_Bar);

	m_themeEventHandle = ThemeManager::ThemeChanged() += nbBindEventFunction(TopBar::onThemeChanged);
	m_languageEventHandle = LanguageManager::LanguageChanged() += nbBindEventFunction(TopBar::onLanguageChanged);

	onLanguageChanged(LanguageManager::getLanguage());
}

TopBar::~TopBar()
{
	ThemeManager::ThemeChanged() -= m_themeEventHandle;
	LanguageManager::LanguageChanged() -= m_languageEventHandle;
}

void TopBar::switchState(State state)
{
	m_btnSwithToAutoPark->setVisibility(state == State::AVM_Bar ? VisibilityE::Visible : VisibilityE::Hidden);
	m_toggleShowMirror->setVisibility(state == State::AVM_Bar ? VisibilityE::Visible : VisibilityE::Hidden);
	m_toggleShowRadar->setVisibility(state == State::AVM_Bar ? VisibilityE::Visible : VisibilityE::Hidden);
	m_toggleShowSubline->setVisibility(state == State::AVM_Bar ? VisibilityE::Visible : VisibilityE::Hidden);
	m_toggleSetting->setVisibility(state == State::AVM_Bar ? VisibilityE::Visible : VisibilityE::Hidden);
	m_toggle2D3D->setVisibility(state == State::AVM_Bar ? VisibilityE::Visible : VisibilityE::Hidden);

	m_slideBtn->setVisibility(state == State::AI_HPA_Bar ? VisibilityE::Visible : VisibilityE::Hidden);

	m_state = state;
}

TopBar::State TopBar::getCurrentState() const
{
	return m_state;
}

void TopBar::switchSlideButton(int mode, bool invokeEvent)
{
	m_bInvoke = invokeEvent;
	m_slideBtn->setCurSel(mode);
	m_bInvoke = true;
}

void TopBar::setToggleShowMirror(bool checked)
{
	m_toggleShowMirror->setCheck(checked);
}

void TopBar::setToggleShowRadar(bool checked)
{
	m_toggleShowRadar->setCheck(checked);
}

void TopBar::setToggle2D3D(bool checked)
{
	m_toggle2D3D->setCheck(checked);
}

void TopBar::setToggleShowSubline(bool checked)
{
	m_toggleShowSubline->setCheck(checked);
}

void TopBar::setToggleSetting(bool checked)
{
	m_toggleSetting->setCheck(checked);
}

bool TopBar::isToggleShowMirrorChecked() const
{
	return m_toggleShowMirror->isChecked();
}

bool TopBar::isToggleShowRadarChecked() const
{
	return m_toggleShowRadar->isChecked();
}

bool TopBar::isToggle2D3DChecked() const
{
	return m_toggle2D3D->isChecked();
}

bool TopBar::isToggleShowSublineChecked() const
{
	return m_toggleShowSubline->isChecked();
}

bool TopBar::isToggleSettingChecked() const
{
	return m_toggleSetting->isChecked();
}

void TopBar::onBtnClick(const EventArgs & e)
{
	if (e.sender == m_btnReturn.get())
	{
		if (m_state == State::Exit_Only)
		{
			auto view = MainView::get()->getCurrentView();
			auto curScene = as<AIView>(view)->currentScene();
			as<ControllerParkScene>(curScene)->gotoStep(ControllerParkScene::Step::CheckInit);
		}
		else
		{
			MainView::get()->switchView<AVMView>();
		}
	}
	else if (e.sender == m_btnSwithToAutoPark.get())
	{
		MainView::get()->switchView<AIView>();
	}
}

void TopBar::onToggleButton(const EventArgs & e)
{
	if (e.sender == m_toggleShowMirror.get())		ShowMirror.invoke(m_toggleShowMirror->isChecked());
	else if (e.sender == m_toggleShowRadar.get())	ShowRadar.invoke(m_toggleShowRadar->isChecked());
	else if (e.sender == m_toggle2D3D.get())		Switch2D3D.invoke(m_toggle2D3D->isChecked());
	else if (e.sender == m_toggleShowSubline.get()) ShowSubline.invoke(m_toggleShowSubline->isChecked());
	else if (e.sender == m_toggleSetting.get())		ShowSetting.invoke(m_toggleSetting->isChecked());
}

void TopBar::onSlideBtnSelectChanged(const int & e)
{
	if (!m_bInvoke)
		return;

	if (e == 3)
	{
		MainView::get()->switchView<HPAView>();
	}
	else
	{
		auto view = MainView::get()->getCurrentView();
		if(!is<AIView>(view))
			MainView::get()->switchView<AIView>();
		as<AIView>(MainView::get()->getCurrentView())->switchScene((AIViewScene)e);
	}
}

void TopBar::onThemeChanged(const int & theme)
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

		m_slideBtn->setBackground(createRef<ImageBrush>(AVM, "btn_62px_nor.9.png"));
		m_slideBtn->setTextColor(Colors::black, Colors::white, Colors::gray);
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

		m_slideBtn->setBackground(createRef<ImageBrush>(AVM, "btn_62px_nor.9_night.png"));
		m_slideBtn->setTextColor(Colors::white, Colors::black, Colors::gray);
	}
}

void TopBar::onLanguageChanged(const int & lan)
{
	m_btnReturn->setText(TR(lan, TID_Exit));
	m_slideBtn->setItemText(0, TR(lan, TID_Auto));
	m_slideBtn->setItemText(1, TR(lan, TID_Control));
	m_slideBtn->setItemText(2, TR(lan, TID_Select));
	m_slideBtn->setItemText(3, TR(lan, TID_HPA));
}
