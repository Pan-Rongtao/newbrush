#pragma once
#include "newbrush/Controls.h"
#include "newbrush/StateManager.h"

namespace nb
{

class NB_API Button : public ButtonBase
{
public:
	Button();
	Button(const Rect &rc);
	Button(float x, float y, float w, float h);

	//设置背景图
	void setBkgndNormal(ref<Brush> brush);
	void setBkgndPress(ref<Brush> brush);
	void setBkgndDisable(ref<Brush> brush);
	void setBkgndCheck(ref<Brush> brush);
	void setBkgndFocus(ref<Brush> brush);
	void setIcon(ref<Brush> normal, ref<Brush> press = nullptr, ref<Brush> check = nullptr, ref<Brush> disable = nullptr, ref<Brush> focus = nullptr);

	void setTextColor(const Color &normal, const Color &press, const Color &check, const Color &disable, const Color &focus);

	void setCheck(bool check);
	bool isChecked() const;

	static ref<Button> createWithTextureFrame(const TextureFrame &texFrame, bool useBrush = true, float x = 0.0f, float y = 0.0f);
	static ref<Button> createWithTextureFrameName(const std::string &texAtlasKey, const std::string &frameName, bool useBrush = true, float x = 0.0f, float y = 0.0f);

protected:
	virtual void onTouch(const TouchEventArgs &e) override;
	virtual void onFocusChanged(const FocusEventArgs &e) override;
	virtual void onRender() override;
	
private:
	ref<Brush> m_bkgndNormal, m_bkgndPress, m_bkgndDisable, m_bkgndCheck, m_bkgndFocus;
	ref<Brush> m_iconNormal, m_iconPress, m_iconDisable, m_iconCheck, m_iconFocus;
	Color m_clrNormal, m_clrPress, m_clrDisable, m_clrCheck, m_clrFocus;
	bool m_checked{ false };
	ref<Node2D> m_icon;
	ref<TextBlock> m_txt;
};

class NB_API ToggleButton : public ButtonBase
{
public:
	ToggleButton();
	ToggleButton(const Rect &rc);
	ToggleButton(float x, float y, float w, float h);

	void setBkgndNormal(ref<Brush> brush);
	void setBkgndPress(ref<Brush> brush);
	void setBkgndCheck(ref<Brush> brush);
	void setBkgndDisable(ref<Brush> brush);
	void setBkgndFocus(ref<Brush> brush);
	void setIcon(ref<Brush> normal, ref<Brush> press = nullptr, ref<Brush> check = nullptr, ref<Brush> disable = nullptr, ref<Brush> focus = nullptr);

	void setCheck(bool check);
	bool isChecked() const;

	void setIconOffset(const Point &offset);

	Event<EventArgs> CheckChanged;

protected:
	virtual void onRender() override;
	virtual void onClick() override;

private:
	void updateIconPositions();

	ref<Brush> m_bkgndNormal, m_bkgndPress, m_bkgndDisable, m_bkgndCheck, m_bkgndFocus;
	ref<Brush> m_iconNormal, m_iconPress, m_iconDisable, m_iconCheck, m_iconFocus;
	bool m_checked{ false };
	ref<Node2D> m_icon;
	ref<TextBlock> m_txt;
	Thickness m_iconThickness;
	Point m_iconOffset, m_iconCheckedPos, m_iconUncheckedPos;
};

class NB_API SwitchButton : public Node2D
{
public:

};

}