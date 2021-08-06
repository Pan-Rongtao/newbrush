#pragma once
#include "newbrush/Node2D.h"
#include "newbrush/Node3D.h"
#include "newbrush/Components.h"
#include "newbrush/Font.h"

namespace nb
{

enum class StretchE
{
	Origion			= 0,	//保持原内容大小
	Fill			= 1,	//不保持内容纵横比，调节内容大小以完全且刚好填充目标尺寸
	Uniform			= 2,	//保持内容纵横比，同时调节大小以适应目标尺寸
	UniformToFill	= 3,	//保持内容纵横比，同时调节大小以填充目标尺寸
};

/*****************************************************
*	面板
*
*	堆栈容器类 StackPanel
*	自动换行布局容器类 WrapPanel
*
******************************************************/
class NB_API Panel : public Node2D
{
protected:
	Panel() = default;
	virtual void onRender() override;
};

class NB_API WrapPanel : public Panel
{
public:
	WrapPanel();
	WrapPanel(OrientationE orientation);

	void setOrientation(OrientationE orientation);
	OrientationE orientation() const;

	void setItemWidth(float width);
	float itemWidth() const;

	void setItemHeight(float height);
	float itemHeight() const;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	OrientationE m_orientation;
	float m_itemWidth;
	float m_itemHeight;
};

/*****************************************************
*	形状
*
*	多线段类 Polyline
*	多边形类 Polygon
*
******************************************************/
class NB_API Polyline : public Node2D
{
public:
	Polyline();
	Polyline(const std::vector<glm::vec2> &points, float size);

	void setPoints(const std::vector<glm::vec2> &points);
	const std::vector<glm::vec2> &points() const;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;
	virtual void onRender() override;

private:
	std::vector<glm::vec2> m_points;
	float m_size;
	glm::vec4 m_box;
};

class NB_API Polygon : public Node2D
{
public:
	Polygon();
	Polygon(const std::vector<glm::vec2> &points);

	void setPoints(const std::vector<glm::vec2> &points);
	const std::vector<glm::vec2> &points() const;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;
	virtual void onRender() override;

private:
	std::vector<glm::vec2> m_points;
	glm::vec4 m_box;
};

class NB_API Image : public Node2D
{
public:
	Image();

	void setStretch(const StretchE &stretch);
	const StretchE &stretch() const;

	void setTexture(ref<Texture2D> texture);
	ref<Texture2D> texture() const;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;
	virtual void onRender() override;

private:
	StretchE m_stretch;
	ref<Texture2D> m_texture;
	Size m_availableSize;
};

class NB_API TextBlock : public Node2D
{
public:
	using Node2D::Node2D;
	TextBlock(const std::string &text);

	void setText(const std::string &text);
	const std::string &text() const;

	void setColor(const Color &color);
	const Color &color() const;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;
	virtual void onRender() override;

private:
	ref<Font> m_font;
	std::string m_text;
	Color m_color;
};

class NB_API ButtonBase : public Node2D
{
public:
	using Node2D::Node2D;

	bool isPressed() const;

	Event<EventArgs> Click;

protected:
	virtual void onTouch(const TouchEventArgs &e) override;
	virtual void onClick();

private:
	bool m_isPressed{ false };
	bool m_leaveWithPressed{ false };
};

/*****************************************************
*	3D
*
*	堆栈容器类 Cube
*	天空盒类 SkyBox
*
******************************************************/
class NB_API Visual3D : public Node3D
{
	RTTR_ENABLE(Node3D)
public:
	void setMaterial(ref<Material> material);
	ref<Material> material() const;

protected:
	ref<Mesh> m_mesh;
};

class NB_API Cube : public Visual3D
{
public:
	Cube();
	Cube(const glm::vec3 &center, float uniformLenght);
	Cube(const glm::vec3 &center, float lenght, float width, float height);
	
protected:
	virtual void onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights) override;

};

class NB_API SkyBox : public Visual3D
{
public:
	SkyBox();

protected:
	virtual void onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights) override;

};

}