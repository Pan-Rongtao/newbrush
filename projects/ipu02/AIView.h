#pragma once
#include "../Common.h"

//自动泊车
class AutoPark : public Node2D
{
public:
	AutoPark();

	void setWarningText(const std::string & txt);
	void setTheme(int theme);
	void setLanguage(int lan);

	void start();
	void stop();

private:
	ref<NinePatchImage> m_tipBg;
	ref<TextBlock> m_tipText;
	ref<Node2D> m_car;
	ref<Node2D> m_carRadar;
	ref<Node2D> m_slot0;
	ref<TextBlock> m_tipBottom;
	FloatAnimation m_aniLadarOpacity;
	StringAnimationUsingKeyFrames m_aniTip;
};

//遥控泊车
class ControllerPark : public Node2D
{
public:
	ControllerPark();
	void start();
	void stop();
	void setTheme(int theme);
	void setLanguage(int lan);

	Event<EventArgs> Finish;

private:
	void onTick(const EventArgs &e);

	void setTextColor(const Color &clr0, const Color &clr1, const Color &clr2, const Color &clr3, const Color &clr4);

	ref<TextBlock> m_title;
	std::array<ref<Node2D>, 5> m_icons;
	std::array<ref<TextBlock>, 5> m_txts;

	Timer m_timer;
	int m_tick;
	StringAnimationUsingKeyFrames m_aniTitle;
};

class SelectPark : public Node2D
{
public:
	SelectPark();

	void start();
	void stop();
	void setTheme(int theme);
	void setLanguage(int lan);

private:
	ref<TextBlock> m_title;
	ref<TextBlock> m_warningTxt;
	ref<Node2D> m_tipBg;
	ref<Node2D> m_pause;
	ref<TextBlock> m_txt;
	ref<Button> m_btnStart;
	Timer m_timerSelTip;
};

class ControllerParkProgress : public Node2D
{
public:
	ControllerParkProgress();

	void start();
	void setTheme(int theme);
	void setLanguage(int lan);

	Event<EventArgs> Exit;

private:
	void switchState(int state);

	ref<Button> m_btnReturn;
	ref<Node2D> m_icon;
	ref<TextBlock> m_txtIng;
	ref<TextBlock> m_txtPause;
	ref<TextBlock> m_txtDone;

	Timer m_timer;
	int m_tick;
};

class AIView : public Node2D
{
public:
	AIView();
	~AIView();

	void switchToRcpProgress(bool on);
	void switchParkMode(int mode);

private:
	void onBtnClick(const EventArgs &e);
	void onSlideBtnSelectChanged(const int &e);
	void onTouch(const TouchEventArgs &e);
	void onThemeChanged(const int &theme);
	void onLanguageChanged(const int &lan);
	//
	ref<Node2D> m_parentMain;
	ref<ControllerParkProgress> m_cpProg;

	//top bar
	ref<Node2D> m_topBar;
	ref<Button> m_btnReturn;
	ref<SlideButton> m_slideBtn;
	
	//left area
	ref<Node2D> m_leftArea;
	ref<Node2D> m_selNode;
	ref<Node2D> m_nodeP;
	ref<Node2D> m_nodeR;

	//right area
	ref<Node2D> m_rightArea;
	ref<AutoPark> m_autoPark;
	ref<ControllerPark> m_controllerPark;
	ref<SelectPark> m_selectPark;

	int m_themeEventHandle;
	int m_languageEventHandle;
	Point m_ptDown{-1.0f, -1.0f};
};