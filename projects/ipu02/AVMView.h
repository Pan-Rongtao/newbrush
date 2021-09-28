#pragma once
#include "../Common.h"

#define AVM	"avm"
#define AP	"ap_day"

class AVMView : public Node2D
{
	RTTR_ENABLE(Node2D);
public:
	AVMView();
	~AVMView();

private:
	enum CameraState
	{
		Hide,
		Show_2D,
		Show_3D,
	};

	void showSetting(bool show);
	void switchCameraState(CameraState state);
	void switchCamera(int index);
	void setWarningText(const std::string &txt);
	void showLardar(bool show);
	void showLardarWarn(bool show);

	void onBtnClick(const EventArgs &e);
	void onToggleButton(const EventArgs &e);
	void onThemeChanged(const int &theme);
	void onLanguageChanged(const int &lan);
	void onTick(const EventArgs & e);

	//top bar
	ref<Node2D> m_topBar;
	ref<Button> m_btnReturn;
	ref<Button> m_btnSwithToAutoPark;
	ref<ToggleButton> m_toggleShowMirror;
	ref<ToggleButton> m_toggleShowRadar;
	ref<ToggleButton> m_toggle2D3D;
	ref<ToggleButton> m_toggleShowSubline;
	ref<ToggleButton> m_toggleSetting;

	//left area
	ref<Node2D> m_leftArea;
	ref<Node2D> m_cameraParent;
	std::array<ref<Button>, 10> m_btnCameras;	//前4个2D，后6个3D
	ref<Node2D> m_car;
	ref<TextBlock> m_txtDis;
	std::array<ref<Node2D>, 6> m_arrows;
	std::array<ref<Node2D>, 12> m_warns;

	//right area
	ref<Node2D> m_rightArea;
	ref<Node2D> m_carView;
	ref<Node2D> m_setting;
	ref<Button> m_btnSettingExit;
	ref<TextBlock> m_settingTitle;
	ref<TextBlock> m_txt0;
	ref<TextBlock> m_txt1;
	ref<TextBlock> m_txt2;
	ref<TextBlock> m_txt3;
	ref<TextBlock> m_txt4;
	ref<TextBlock> m_txt5;
	ref<TextBlock> m_txt6;
	ref<TextBlock> m_txtNow;
	ref<TextBlock> m_txt30Senconds;
	ref<ToggleButton> m_toggleTrajectory;
	ref<ToggleButton> m_toggleP;
	ref<ToggleButton> m_toggleChassis;
	ref<ToggleButton> m_toggleRadarFullView;
	ref<ToggleButton> m_toggleIndicatorFullView;
	ref<ToggleButton> m_toggleLan, m_toggleTheme;
	ref<Node2D> m_warningPedestrians;
	ref<Node2D> m_warning;
	ref<NinePatchImage> m_tipBg;
	ref<TextBlock> m_tipText;

	ref<StateManager> m_smWarning;
	Timer m_timerWarning;
	
	std::array<PointAnimation, 4> m_anis;
	int m_themeEventHandle;
	int m_languageEventHandle;
	FloatAnimation m_aniShowSetting;
};