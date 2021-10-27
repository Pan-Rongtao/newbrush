#pragma once
#include "../Common.h"

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
	std::array<ref<TextBlock>, 7> m_txts;
	std::array<ref<ToggleButton>, 7> m_toggles;
	ref<TextBlock> m_txtNow;
	ref<TextBlock> m_txt30Senconds;
	ref<Node2D> m_warningPedestrians;
	ref<Node2D> m_warning;
	ref<NinePatchImage> m_tipBg;
	ref<TextBlock> m_tipText;

	Timer m_timerWarning;
	
	std::array<PointAnimation, 4> m_anis;
	int m_themeEventHandle;
	int m_languageEventHandle;
	FloatAnimation m_aniShowSetting;
};