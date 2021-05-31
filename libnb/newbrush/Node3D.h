#pragma once
#include "newbrush/Node.h"
#include "newbrush/Components.h"
#include "newbrush/Transform.h"

namespace nb{

class NB_API Node3D : public Node
{
public:
	virtual void onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights);

	void addChild(ref<Node3D> child);
	void insertChild(unsigned index, ref<Node3D> child);
	void removeChild(unsigned index);
	unsigned childCount() const;
	bool hasChild() const;
	ref<Node3D> getChildAt(unsigned index);
	void clearChildren();
	const std::vector<ref<Node3D>> &children() const;
	Node3D *getParent() const;

	void setTransform(ref<Transform> transform);
	ref<Transform> getTransform() const;

private:
	Node3D *m_parent;
	std::vector<ref<Node3D>> m_children;
	ref<Transform> m_transform;
};

}