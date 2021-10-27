#pragma once
#include "../Common.h"

class TopBar : public Node2D
{
public:
	enum class State
	{
		Exit_Only,
		AVM_Bar,
		AI_HPA_Bar,
	};

public:
	TopBar();
	~TopBar();

	void switchState(State state);
	State getCurrentState() const;

	void switchSlideButton(int mode, bool invokeEvent);

	void setToggleShowMirror(bool checked);
	void setToggleShowRadar(bool checked);
	void setToggle2D3D(bool checked);
	void setToggleShowSubline(bool checked);
	void setToggleSetting(bool checked);
	bool isToggleShowMirrorChecked() const;
	bool isToggleShowRadarChecked() const;
	bool isToggle2D3DChecked() const;
	bool isToggleShowSublineChecked() const;
	bool isToggleSettingChecked() const;

	Event<bool> ShowMirror;
	Event<bool> ShowRadar;
	Event<bool> Switch2D3D;
	Event<bool> ShowSubline;
	Event<bool> ShowSetting;
	
private:
	void onBtnClick(const EventArgs &e);
	void onToggleButton(const EventArgs &e);
	void onSlideBtnSelectChanged(const int &e);
	void onThemeChanged(const int &theme);
	void onLanguageChanged(const int &lan);

	ref<Button> m_btnReturn;
	ref<Button> m_btnSwithToAutoPark;
	ref<ToggleButton> m_toggleShowMirror;
	ref<ToggleButton> m_toggleShowRadar;
	ref<ToggleButton> m_toggle2D3D;
	ref<ToggleButton> m_toggleShowSubline;
	ref<ToggleButton> m_toggleSetting;
	
	ref<SlideButton> m_slideBtn;

	State m_state;
	int m_themeEventHandle;
	int m_languageEventHandle;
	bool m_bInvoke{true};
};