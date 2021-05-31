#include "newbrush/Node3D.h"

using namespace nb;

void Node3D::onRender(ref<Camera> camera, const std::vector<ref<Light>>& lights)
{
}

void Node3D::addChild(ref<Node3D> child)
{
	insertChild(childCount(), child);
}

void Node3D::insertChild(unsigned index, ref<Node3D> child)
{
	nbThrowExceptionIf(!child, std::invalid_argument, "child is nullptr");
	nbThrowExceptionIf(index > childCount(), std::out_of_range, "index");

	child->m_parent = this;
	m_children.insert(m_children.begin() + index, child);
}

void Node3D::removeChild(unsigned index)
{
	nbThrowExceptionIf(index >= childCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)childCount());
	m_children.erase(m_children.begin() + index);
}

unsigned Node3D::childCount() const
{
	return m_children.size();
}

bool Node3D::hasChild() const
{
	return childCount() > 0;
}

ref<Node3D> Node3D::getChildAt(unsigned index)
{
	nbThrowExceptionIf(index >= childCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)childCount());
	return m_children[index];
}

void Node3D::clearChildren()
{
	m_children.clear();
}

const std::vector<ref<Node3D>>& Node3D::children() const
{
	return m_children;
}

Node3D * Node3D::getParent() const
{
	return m_parent;
}

void Node3D::setTransform(ref<Transform> transform)
{
	m_transform = transform;
}

ref<Transform> Node3D::getTransform() const
{
	return m_transform;
}
