#pragma once
#include "../Common.h"

//3D Button
class Button3D : public Node3D
{
	RTTR_ENABLE(Node)
public:
	Button3D(float x, float y, float width, float height, ref<ImageBrush> normal, ref<ImageBrush> check);

	void setCheck(bool check);
	bool isCheck() const;

protected:
	virtual void onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights);

private:
	ref<Mesh> makeMesh(ref<ImageBrush> brush);

	bool m_checked;
	ref<ImageBrush> m_normal;
	ref<ImageBrush> m_check;
	ref<Mesh> m_mesh;
	Rect m_rc;
};

//自动泊车
class AutoParkScene : public Node2D
{
public:
	enum class Step
	{
		Searching,
		NotFound,
		SearchedAndPickSlot,
		ToStart,
		RealseTheBrakeAndWheel,
		Parking,
		WatchoutEnv,
		GetBarrier,
		RemoveBarrier,
		Continue,
		Done,

		Max,
	};

	AutoParkScene();

	void start();
	void stop();

	void setTheme(int theme);
	void setLanguage(int lan);

private:
	void onTimeLineProgress(const EventArgs & e);
	void onTick(const EventArgs & e);

	void gotoStep(AutoParkScene::Step step);
	void setTopTipText(const std::string & txt);
	std::string getTopTipText(AutoParkScene::Step step) const;
	
	ref<Node2D> m_leftArea;
	ref<Node2D> m_rightSearchingParent;
	ref<Node2D> m_rightTopTipParent;
	ref<Node2D> m_rightParkDoneParent;
	ref<NinePatchImage> m_topTipBg;
	ref<TextBlock> m_txtTopTip;
	ref<Node2D> m_car;
	ref<Button3D> m_3dbtn0;
	ref<Button3D> m_3dbtn1;
	ref<Button> m_btnStartPark;
	ref<TextBlock> m_txtBottomTip;
	ref<Node2D> m_parkDoneTipBg;
	ref<TextBlock> m_txtParkDone;

	Step m_curStep;

	FloatAnimation m_aniLadarOpacity;
	float m_aniFrom;
	float m_aniTo;
	Timeline m_tlSearching;
	Timer m_timer;
};

//遥控泊车
class ControllerParkScene : public Node2D
{
public:
	enum class Step
	{
		CheckInit,
		CheckP,
		CheckApp,
		CheckBT_Fail,
		CheckBT_Success,
		CheckDoorWindow,
		CheckKeyInCar,

		ParkingIng,
		ParkingPause,
		ParkingDone,

		Max,
	};

	ControllerParkScene();

	void gotoStep(Step step);

	void start();
	void stop();

	void setTheme(int theme);
	void setLanguage(int lan);
	
private:
	void onTick(const EventArgs &e);
	void setTextColor(const Color &clr0, const Color &clr1, const Color &clr2, const Color &clr3, const Color &clr4);

	ref<Node2D> m_leftArea;
	ref<Node2D> m_rightArea;
	ref<TextBlock> m_txtTitle;
	std::array<ref<Node2D>, 5> m_icons;
	std::array<ref<TextBlock>, 5> m_txts;
	ref<Node2D> m_iconParkingState;
	ref<TextBlock> m_txtparkingState;

	Timer m_timer;
	StringAnimationUsingKeyFrames m_aniTitle;
	Step m_curStep;
};

//自选车位
class SelectParkScene : public Node2D
{
public:
	SelectParkScene();

	void start();
	void stop();

	void setTheme(int theme);
	void setLanguage(int lan);

private:
	void onTouch(const TouchEventArgs & e);

	ref<Node2D> m_leftArea;
	ref<Node2D> m_selNode;
	ref<Node2D> m_nodeP;
	ref<Node2D> m_nodeR;

	ref<Node2D> m_rightArea;
	ref<TextBlock> m_txtTitle;
	ref<TextBlock> m_txtWarning;
	ref<Node2D> m_tipBg;
	ref<TextBlock> m_txtTip;
	ref<Button> m_btnStart;
	Timer m_timerShowTip;
	Timer m_timerSetClip;

	Point m_ptPressOnSelectNode{ -1.0f, -1.0f };
	Point m_ptPressedOnRNode{ -1.0f, -1.0f };
};

//智能泊车
enum class AIViewScene
{
	Auto,
	Control,
	Select,
};

class AIView : public Node2D
{
public:
	AIView();
	~AIView();

	void switchScene(AIViewScene scene);
	ref<Node2D> currentScene();

private:
	void onThemeChanged(const int &theme);
	void onLanguageChanged(const int &lan);

	ref<AutoParkScene> m_autoParkScene;
	ref<ControllerParkScene> m_controllerParkScene;
	ref<SelectParkScene> m_selectParkScene;
	ref<Node2D> m_curScene;

	int m_themeEventHandle;
	int m_languageEventHandle;
};