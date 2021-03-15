#pragma once
#include "newbrush/Node.h"
#include "newbrush/Brush.h"
#include "newbrush/Event.h"
#include "newbrush/Transform.h"

namespace nb
{
		
enum class VisibilityE
{
	Hidden,		//不要显示的元素，但是，保留空间中的元素格式（参与排版策略等）
	Visible,	//显示组件
	Collapsed,	//不要显示元素，并且不希望它的保留空间
};

enum class HorizontalAlignmentE
{
	Left,
	Center,
	Right,
	Stretch,
};

enum class VerticalAlignmentE
{
	Top,
	Center,
	Bottom,
	Stretch,
};

enum class FlowDirectionE
{
	LeftToRight,
	RightToLeft,
};

enum class OrientationE
{
	Horizontal,
	Vertical,
};

class NB_API Node2D : public Node
{
	RTTR_ENABLE(Node)

public:
	Node2D();
	Node2D(const Rect &rc);
	Node2D(float x, float y, float w, float h);

	float x() const;
	void setX(float x);

	float y() const;
	void setY(float y);

	void setPosition(const Point &pt);
	Point position() const;

	void setWidth(float width);
	float width() const;

	void setHeight(float height);
	float height() const;

	void setSize(const Size &size);
	Size size() const;

	void setMargin(const Thickness &margin);
	const Thickness &margin() const;

	void setOpacity(float opacity);
	float getOpacity() const;

	void setHorizontalAlignment(HorizontalAlignmentE h);
	HorizontalAlignmentE horizontalAlignment() const;

	void setVerticalAlignment(VerticalAlignmentE v);
	VerticalAlignmentE verticalAlignment() const;

	void setAlignmentCenter();

	void setVisibility(VisibilityE visibility);
	VisibilityE visibility() const;

	void setBackground(ref<Brush> brush);
	ref<Brush> background() const;

	void setTransform(ref<Transform2D> transform);
	ref<Transform2D> getTransform() const;

	glm::mat4 getRenderTransform() const;

	void setEnable(bool bEnable);
	bool isEnable() const;
	bool hasFocus() const;

	const Size &getDesiredSize() const;
	const Size &getActualSize() const;
	const Point &getOffsetToParent() const;
	Rect getRenderRect() const;

	void touchThunk(const TouchEventArgs &e);

public:
	void updateLayout(const Size &availabelSize);

	void measure(const Size &availabelSize);
	void arrage(const Rect &finalRect);

	virtual void onRender() override;

	bool hitTest(const Point &pt) const;

	static ref<Node2D> createWithTextureFrame(const TextureFrame &texFrame, bool useBrush = true, float x = 0.0f, float y = 0.0f);
	static ref<Node2D> createWithTextureFrameName(const std::string &texAtlasKey, const std::string &frameName, bool useBrush = true, float x = 0.0f, float y = 0.0f);

protected:
	virtual Size measureOverride(const Size &availableSize);
	virtual Size arrangeOverride(const Size &finalSize);
	virtual void onTouch(const TouchEventArgs &e);
	virtual void onFocusChanged(const FocusEventArgs &e);

	void drawBrush(ref<Brush> brush);

private:
	Point m_position;
	float m_width;
	float m_height;
	float m_opacity;
	bool m_focusAble;
	bool m_hasFocus;
	Thickness m_margin;
	VisibilityE m_visibility;
	HorizontalAlignmentE m_horizontalAlignment;
	VerticalAlignmentE m_verticalAlignment;

	ref<Brush> m_background;
	ref<Transform2D> m_transform;

	Size m_desiredSize;
	Size m_actualSize;
	Point m_offsetToParent;

	bool m_isMouseOver;
	bool m_isEnable;
};

}