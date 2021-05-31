#pragma once
#include "newbrush/Controls.h"

namespace nb
{

class NB_API Button : public ButtonBase
{
public:
	using ButtonBase::ButtonBase;

	//设置背景图
	void setBkgndNormal(ref<Brush> brush);
	void setBkgndPress(ref<Brush> brush);
	void setBkgndDisable(ref<Brush> brush);
	void setBkgndCheck(ref<Brush> brush);
	void setBkgndFocus(ref<Brush> brush);

	void setCheck(bool check);
	bool isChecked() const;

	static ref<Button> createWithTextureFrame(const TextureFrame &texFrame, bool useBrush = true, float x = 0.0f, float y = 0.0f);
	static ref<Button> createWithTextureFrameName(const std::string &texAtlasKey, const std::string &frameName, bool useBrush = true, float x = 0.0f, float y = 0.0f);

protected:
	virtual void onTouch(const TouchEventArgs &e) override;
	virtual void onFocusChanged(const FocusEventArgs &e) override;
	virtual void onRender() override;
	
private:
	ref<Brush> m_bkgndNormal;
	ref<Brush> m_bkgndPress;
	ref<Brush> m_bkgndDisable;
	ref<Brush> m_bkgndCheck;
	ref<Brush> m_bkgndFocus;
	bool m_checked{ false };
};

}