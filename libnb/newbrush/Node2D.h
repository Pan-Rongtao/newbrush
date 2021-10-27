#pragma once
#include "newbrush/Node.h"
#include "newbrush/Brush.h"
#include "newbrush/Event.h"

namespace nb
{
		
enum class VisibilityE
{
	Hidden,		//不要显示的元素，但是，保留空间中的元素格式（参与排版策略等）
	Visible,	//显示组件
	Collapsed,	//不要显示元素，并且不希望它的保留空间
};

enum class HorizontalAlignment
{
	Left,
	Center,
	Right,
	Stretch,
};

enum class VerticalAlignment
{
	Top,
	Center,
	Bottom,
	Stretch,
};

enum class Orientation
{
	Horizontal,
	Vertical,
};

class Scene;
class NB_API Node2D : public Node
{
	RTTR_ENABLE(Node)

public:
	Node2D();
	Node2D(const Rect &rc);
	Node2D(float x, float y, float w, float h);
	Node2D(float x, float y, float w, float h, ref<Brush> background);

	float x() const;
	void setX(float x);

	float y() const;
	void setY(float y);

	void setPosition(const Point &pt);
	const Point &position() const;

	void setWidth(float width);
	float width() const;

	void setHeight(float height);
	float height() const;

	void setSize(const Size &size);
	const Size &size() const;

	void setRect(const Rect &rc);
	Rect rect() const;

	void setMargin(const Thickness &margin);
	const Thickness &margin() const;

	void setOpacity(float opacity);
	float getOpacity() const;

	void setHorizontalAlignment(HorizontalAlignment h);
	HorizontalAlignment horizontalAlignment() const;

	void setVerticalAlignment(VerticalAlignment v);
	VerticalAlignment verticalAlignment() const;

	void setAlignmentCenter();

	void setVisibility(VisibilityE visibility);
	VisibilityE visibility() const;

	void setBackground(ref<Brush> brush);
	ref<Brush> background() const;

	void setClipRect(const Rect &clipRC);
	const Rect & getClipRect() const;

	void setTransform(ref<Transform2D> transform);
	ref<Transform2D> getTransform() const;

	void setEnable(bool bEnable);
	bool isEnable() const;
	bool hasFocus() const;

	const Size &getDesiredSize() const;
	const Size &getActualSize() const;
	const Point &getOffsetToParent() const;
	Rect getRenderRect() const;

	void addChild(ref<Node2D> child);
	void insertChild(unsigned index, ref<Node2D> child);
	void removeChild(unsigned index);
	void removeChild(ref<Node2D> child);
	unsigned childCount() const;
	bool hasChild() const;
	ref<Node2D> getChildAt(unsigned index);
	void setChildAt(unsigned index, ref<Node2D> newChild);
	void clearChildren();
	const std::vector<ref<Node2D>> &children() const;
	Node2D *getParent() const;

	void setScene(ref<Scene> scene);
	ref<Scene> getScene();

	void touchThunk(const TouchEventArgs &e);
	void scrollThunk(const ScrollEventArgs &e);
	void keyThunk(const KeyEventArgs &e);

	Event<TouchEventArgs> Touch;
	Event<ScrollEventArgs> Scroll;
	Event<KeyEventArgs> Key;

public:
	void updateLayout(const Size &availabelSize);

	void measure(const Size &availabelSize);
	void arrage(const Rect &finalRect);

	virtual void onRender() override;

	bool hitTest(const Point &pt) const;

	static ref<Node2D> createWithTextureFrame(const TextureFrame &texFrame, bool useBrush, float x, float y);
	static ref<Node2D> createWithTextureFrameName(const std::string &texAtlasKey, const std::string &frameName, float x, float y);
	static ref<Node2D> createWithTextureFrameName(const std::string &texAtlasKey, const std::string &frameName, bool useBrush, float x, float y);

protected:
	virtual Size measureOverride(const Size &availableSize);
	virtual Size arrangeOverride(const Size &finalSize);
	virtual void onTouch(const TouchEventArgs &e);
	virtual void onScroll(const ScrollEventArgs &e);
	virtual void onKey(const KeyEventArgs &e);
	virtual void onFocusChanged(const FocusEventArgs &e);

	void drawBrush(ref<Brush> brush);
	void drawChildren();

private:
	Point m_position;
	Size m_size;
	float m_opacity;
	bool m_focusAble;
	bool m_hasFocus;
	Thickness m_margin;
	VisibilityE m_visibility;
	HorizontalAlignment m_horizontalAlignment;
	VerticalAlignment m_verticalAlignment;

	ref<Brush> m_background;
	ref<Transform2D> m_transform;

	Size m_desiredSize;
	Size m_actualSize;
	Point m_offsetToParent;

	bool m_isMouseOver;
	bool m_isEnable;

	Node2D *m_parent;
	std::vector<ref<Node2D>> m_children;
	ref<Scene> m_scene;
	Rect m_clipRC;
};

}