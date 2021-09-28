#pragma once
#include "../Common.h"

enum class PAPScene
{
	Scene_None,
	Scene_Hello,
	Scene_Tutorial,
	Scene_Main,
	Scene_Ruku,
	Scene_Chuku,
};

class HelloScene;
class TutorialScene;
class MainScene;
class RukuScene;
class PAPView : public Node2D
{
public:
	PAPView();
	~PAPView();

	void switchScene(PAPScene scene);

private:
	void onLanguageChanged(const int & lan);
	void onSlideBtnSelectChanged(const int &e);

	ref<SlideButton> m_slideBtn; 
	ref<HelloScene> m_helloScene;
	ref<TutorialScene> m_tutoialScene;
	ref<MainScene> m_mainScene;
	ref<RukuScene> m_rukuScene;
	PAPScene m_curScene;
	int m_languageEventHandle;
};

class HelloScene : public Node2D
{
public:
	HelloScene();
	void setLanguage(int lan);

	Event<EventArgs> Start;

private:
	ref<Node2D> m_img;
	ref<Button> m_btnAgree;
	ref<Button> m_btnStart;
};

class TutorialScene : public Node2D
{
public:
	TutorialScene();
	void setLanguage(int lan);

	Event<EventArgs> Skip;
private:
	ref<Button> m_btnSkip;
	ref<DotListCtrl> m_dotListCtrl;
};

class MainScene : public Node2D
{
public:
	MainScene();
	void setLanguage(int lan);
	
	Event<EventArgs> ToTutorial;

private:
	void onBtnClick(const EventArgs &e);

	ref<TextBlock> m_txtTop;
	ref<TextBlock> m_txtPathChoose;
	ref<Button> m_btnToTutorial;
};

class RukuScene : public Node2D
{
public:
	enum Step
	{
		StopToSetOrign,
		SettingOrign,
		SetOrignFailWithDoorOpen,
		SetOrignSuccess,

		StopToSetEnd,
		SettingEnd,
		SetEndSuccess,

		SavePath,
	};

	RukuScene();
	void gotoStep(Step step);

	Event<EventArgs> BackToMain;
	Event<EventArgs> Save;

private:

	ref<Node2D> m_left;
	ref<Button> m_btnBackToMain;
	ref<TextBlock> m_txtTitle;
	std::array<ref<Node2D>, 3> m_icons;
	ref<TextBlock> m_txtTip;
	ref<Node2D> m_iconStop;
	ref<Button> m_btnSet;
	ref<Node2D> m_iconLoading;

	ref<Node2D> m_editBg;
	ref<TextBlock> m_txtPathName;
	ref<Button> m_btnDel;
	ref<Button> m_btnCandidateHome0;
	ref<Button> m_btnCandidateOffice;
	ref<Button> m_btnCandidateHome1;
	ref<Button> m_btnSave;

	ref<Node2D> m_tip;
	ref<TextBlock> m_txtTipTitle;
	ref<TextBlock> m_txtTipContent;
	ref<Button> m_btnRetry;
	ref<Button> m_btnExit;
	ref<Node2D> m_rukuImg;
	bool m_bRetried;

	ref<Node2D> m_right;

	Step m_curStep;

	Timer m_timerToNextStep;
	FloatAnimation m_aniSettingOrigin;
};