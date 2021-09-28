#pragma once
#include "newbrush/Controls.h"
#include "newbrush/StateManager.h"
#include "newbrush/Animation.h"

namespace nb
{

class NB_API Button : public ButtonBase
{
	RTTR_ENABLE(ButtonBase)
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

	void setText(const std::string &text);
	const std::string &text() const;

	void setTextColor(const Color &normal, const Color &press, const Color &check = Colors::black, const Color &disable = Colors::black, const Color &focus = Colors::black);

	void setIconOffset(const Point &offset);
	void setTextOffset(const Point &offset);
	void setIconTextOffset(const Point &iconOffset, const Point &textOffset);
	void setFont(ref<Font> font);

	void setCheck(bool check);
	bool isChecked() const;

	static ref<Button> createWithTextureFrame(const TextureFrame &texFrame, bool useBrush, float x, float y);
	static ref<Button> createWithTextureFrameName(const std::string &texAtlasKey, const std::string &frameName, float x, float y);
	static ref<Button> createWithTextureFrameName(const std::string &texAtlasKey, const std::string &frameName, bool useBrush, float x, float y);

protected:
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
	ToggleButton(float x, float y, float w, float h, ref<Brush> iconNormal, ref<Brush> iconCheck);

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

class NB_API NinePatchImage : public Node2D
{
public:
	using Node2D::Node2D;

	void setImages(ref<ImageBrush> left, ref<ImageBrush> leftTop, ref<ImageBrush> top, ref<ImageBrush> rightTop,
		ref<ImageBrush> right, ref<ImageBrush> rightBottom, ref<ImageBrush> bottom, ref<ImageBrush> leftBottom, ref<ImageBrush> center);
	void setImages(ref<ImageBrush> leftTop, ref<ImageBrush> rightTop, ref<ImageBrush> rightBottom, ref<ImageBrush> leftBottom, ref<ImageBrush> ltrb, ref<ImageBrush> center);
	void setImages(ref<ImageBrush> leftTop, ref<ImageBrush> rightTop, ref<ImageBrush> rightBottom, ref<ImageBrush> leftBottom, ref<ImageBrush> ltrbc);

protected:
	virtual void onRender() override;

private:
	ref<ImageBrush> m_left;
	ref<ImageBrush> m_leftTop;
	ref<ImageBrush> m_top;
	ref<ImageBrush> m_rightTop;
	ref<ImageBrush> m_right;
	ref<ImageBrush> m_rightBottom;
	ref<ImageBrush> m_bottom;
	ref<ImageBrush> m_leftBottom;
	ref<ImageBrush> m_center;
};

class NB_API MovieImage :public Node2D
{
public:
	MovieImage();
	MovieImage(const Rect &rc);
	MovieImage(float x, float y, float w, float h);

	//添加一帧图像
	void addFrame(ref<Texture2D> tex);

	//设置两帧之间的播放间隔时间（毫秒）
	void setInterval(int nInterval);

	//开始动画
	void startMovie(int nInterval);
	void startMovie();

	//停止动画
	void stopMovie(void);

	//当播放到nFrame帧时自动停止动画
	void stopMovieInFrame(int nFrame);

	//跳到指定的帧
	void gotoFrame(int nFrame);

	//设置是否反向播放
	void setReverse(bool reverse = false);

	//获取是否反向播放信息
	bool getReverse();

	virtual void onRender() override;

private:
	//默认播放时间间隔
	void init(void);

	//播放下一帧
	void onTick(const EventArgs & e);

	//下一帧。bCyc=true时，表明当翻过最后一帧时，回到第一帧；否则保持最后一帧
	void nextFrame(bool bCyc = true);

	//前一帧。bCyc=true时，表明当翻过最前一帧时，跳到最后一帧；否则保持第一帧
	void prevFrame(bool bCyc = true);

private:
	Timer m_timer;
	int m_nCurrFrame;
	int m_nStopMovieInFrame;
	std::vector<ref<Texture2D>> m_vecTex;
	//std::vector<ref<ImageBrush>> m_vecBrush;
	ref<ImageBrush> m_CurImageBrush;
	Event<EventArgs> MovieCompleteEvent;
	bool m_reverse;
};

class NB_API SlideButton : public Node2D
{
public:
	SlideButton();
	SlideButton(const Rect &rc);
	SlideButton(float x, float y, float w, float h);

	void setBtn(ref<ImageBrush> normal);
	void setTextColor(const Color &normal, const Color &select, const Color &disable);
	void addItem(const std::string &txt);
	void setItemText(uint32_t index, const std::string &txt);

	void setCurSel(int index);
	int getCurSel() const;

	void enableItem(uint32_t index, bool enable);
	bool isItemEnable(uint32_t index) const;
	
	Event<int> SelectChanged;

protected:
	virtual void onTouch(const TouchEventArgs &e) override;
	virtual void onRender() override;

private:
	enum class ItemState
	{
		State_Normal,
		State_Select,
		State_Disable,
	};

	struct ItemInfo
	{
		std::string text;
		ItemState state;
	};

	int findItemByPos(float x, float y);

	ref<ImageBrush> m_btnNormal;
	Color m_clrTxtNormal;
	Color m_clrTxtSelect;
	Color m_clrTxtDisable;
	int m_curSel;
	std::vector<ItemInfo> m_items;
};

class NB_API DotListCtrl : public Node2D
{
public:
	DotListCtrl();
	DotListCtrl(const Rect &rc);
	DotListCtrl(float x, float y, float w, float h);

	void setDotCount(int count);
	int dotCount();

	void setDotImage(ref<ImageBrush> normal, ref<ImageBrush> sel);

	void setCurSel(int index);
	int getCurSel() const;

protected:
	virtual void onRender() override;

private:
	void updatePositions();

	int m_nCurSel;
	int m_nDotCount;
	OrientationE m_eOrientation;
	ref<ImageBrush> m_normalBrush;
	ref<ImageBrush> m_selectBrush;
	std::vector<Point> m_vtPoints;
	bool m_bNeedUpdatePositions;
};

}