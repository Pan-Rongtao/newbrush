#pragma once
#include "../Common.h"

using namespace nb;

class RectangleObj : public Node3D
{
public:
	RectangleObj(glm::vec2 pos,float w,float h, glm::mat4 matrix);
	ref<Material> getmaterial();

protected:
	virtual void onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights);

private:
	ref<Material> m_materials;
	ref<Mesh> m_mesh;
};

class dotPanel3D : public Node3D
{
public:
	dotPanel3D();

protected:
	virtual void onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights);

private:
	void builddotPanel3D();
};

class MixMaterial : public Material
{
public:
	MixMaterial(ref<Texture2D> texture0, ref<Texture2D> texture1);
	virtual void uploadUniform(ref<Camera> camera) override;

	ref<Texture2D> texture0;
	ref<Texture2D> texture1;
	float angle;
};

class halo : public Node3D
{
public:
	halo();
	ref<Material> getmaterial();
protected:
	virtual void onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights);

private:
	ref<Material> m_materials;
	ref<Mesh> m_mesh;
};

class SecondMaterial : public Material
{
public:
	SecondMaterial(ref<Texture2D> texture0);
	virtual void uploadUniform(ref<Camera> camera) override;

	ref<Texture2D> texture0;
	float Opacity;
};

class secondpoint : public Node3D
{
	RTTR_ENABLE(Node3D)
public:
	secondpoint();
	secondpoint(glm::vec2 pos, float w, float h);
	float getOpacity();
	void setOpacity(float Opacity);
	ref<Material> getmaterial();
protected:
	virtual void onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights);

private:
	ref<Material> m_materials;
	ref<Mesh> m_mesh;
	float m_Opacity;
};

class ShrinkRectangle : public Node3D
{
	RTTR_ENABLE(Node3D)
public:
	ShrinkRectangle();
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

class NormalNode : public Node2D
{
public:
	NormalNode();

	void setTime(ref<Node2D> parent, int value, const std::string &imagePrefix, float space, bool useEffect, float angle);

private:
	void onKey(const KeyEventArgs &e);
	void onTick(const EventArgs & e);

	void moveShadowNumberCircle(ref<Node2D> node, float x, float y, float r, float angle);
	void moveEffectNumberCircle(ref<Node2D> node, float angle);

	void setSecondPointer(float angle);


	ref<Node2D> m_hourParent;
	ref<Node2D> m_minuteParent;
	ref<Node2D> m_hourShadowParent;
	ref<Node2D> m_minuteShadowParent;
	ref<Node2D> m_hourShadow;
	ref<Node2D> m_minuteShadow;

	Timer m_timer;



	ref<Scene> m_scene;
	ref<dotPanel3D> m_dotPanel3D;
	ref<secondpoint> m_point;
	FloatAnimation m_pointanimation;
	ref<halo> m_halo;
	ref<ShrinkRectangle>m_shrinkrect;
	FloatAnimation m_shrinkanimation;
	int lasttime = 0;
	int curtime = 0;
	bool startanimation = false;
};