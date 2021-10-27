#pragma once
#include "../Common.h"
#include "MainView.h"

using namespace nb;

#pragma region newest
#if 1
class TriangleNode : public Node3D
{
public:
	TriangleNode(Point pos, const float Side_length = 1, bool up = true);

	Point getpos();
	void startanimation();
	TimelineState isactive();
	ref<Material> getmaterial();
protected:
	virtual void onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights);

private:
	Point caltrianglepos(std::vector<Vertex> triangle);
	ref<Material> m_materials;
	ref<Mesh> m_mesh;
	Point m_pos;
	ref<Vec3Animation> m_Animation;
};

class RectangleClass : public Node3D
{
public:
	RectangleClass();
	ref<Material> getmaterial();
protected:
	virtual void onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights);

private:
	ref<Material> m_materials;
	ref<Mesh> m_mesh;
};

class HaloRectangle : public Node3D
{
	RTTR_ENABLE(Node3D)
public:
	HaloRectangle();
	ref<Material> getmaterial();
	float getVelocity();
	void setVelocity(float Velocity);
protected:
	virtual void onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights);

private:
	ref<Material> m_materials;
	ref<Mesh> m_mesh;
	float m_velocity;
};

class Trianglegroup : public Node3D
{
public:
	Trianglegroup();

	void setpos(Point pos);
	Point getpos();
protected:
	virtual void onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights);

private:
	void buildtrianglegroup();
	Point m_pos;
};
#endif
#pragma endregion


class SportNode : public Node2D
{
public:
	SportNode();

private:
	void onKey(const KeyEventArgs &e);
	void onTick(const EventArgs & e);

	void setTime(ref<Node2D> parent, int value, const std::string &imagePrefix, float space, bool useEffect, float angle);

	void moveShadowNumberCircle(ref<Node2D> node, float x, float y, float r, float angle);
	void moveEffectNumberCircle(ref<Node2D> node, float angle);

	void updatemodel();

	Timer m_timer;
	ref<Scene> m_scene;
	ref<Trianglegroup> m_Trianglegroupmodel;
	ref<RectangleClass> m_Rectangle;
	ref<HaloRectangle> m_HaloRectangle;
	FloatAnimation m_haloanimation;
	int m_lasttime = 0;
	int m_curtime = 0;
	bool m_bstartanimation = false;

	ref<Node2D> m_hourParent;
	ref<Node2D> m_minuteParent;
	ref<Node2D> m_hourShadowParent;
	ref<Node2D> m_minuteShadowParent;
};