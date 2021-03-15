#include "newbrush/Node.h"
#include "newbrush/Mesh.h"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/matrix_query.hpp"
#include "glm/gtx/euler_angles.hpp"

using namespace nb;

Node::Node()
	: Node("")
{}

Node::Node(const std::string &name)
	: m_name(name)
	, m_parent(nullptr)
	, m_translate(0.0)
	, m_rotate(0.0)
	, m_scale(1.0)
	, m_renderTransform(1.0)
{
	updateRenderTransform();
}

const std::vector<ref<Node>>& Node::children() const
{
	return m_children;
}

unsigned Node::childCount() const
{
	return m_children.size();
}

ref<Node> Node::getChildAt(unsigned index)
{
	nbThrowExceptionIf(index >= childCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)childCount());
	return m_children[index];
}

void Node::clearChildren()
{
	m_children.clear();
}

void Node::removeChild(unsigned index)
{
	nbThrowExceptionIf(index >= childCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)childCount());
	m_children.erase(m_children.begin() + index);
}

void Node::setName(const std::string & name)
{
	m_name = name;
}

const std::string & Node::getName() const
{
	return m_name;
}

void Node::addChild(ref<Node> child)
{
	nbThrowExceptionIf(!child, std::invalid_argument, "child is nullptr");
	child->m_parent = this;
	m_children.push_back(child);
}

const glm::mat4 &Node::getRenderTransform() const
{
	return m_renderTransform;
}

Node *Node::getParent() const
{
	return m_parent;
}

void Node::setMesh(ref<Mesh> mesh)
{
	m_mesh = mesh;
}

ref<Mesh> Node::mesh() const
{
	return m_mesh;
}

void Node::setTransform(const glm::mat4 & matrix)
{
	glm::vec3 skew;
	glm::quat orientation;
	glm::vec4 perspective;
	//分解为scale、orientation四元素和position
	glm::decompose(matrix, m_scale, orientation, m_translate, skew, perspective);

	//四元素转旋转矩阵
	auto rMatrix = glm::mat4_cast(orientation);

	//旋转矩阵提取欧拉角
	glm::extractEulerAngleYXZ(rMatrix, m_rotate.y, m_rotate.x, m_rotate.z);

	updateRenderTransform();
}

glm::mat4 Node::getTransform() const
{
	auto translateMatrix = glm::translate(glm::mat4x4(1.0f), m_translate);
	//旋转	HPB{朝向，仰俯，侧倾}，或者YPR ： yaw(航向) pitch(仰俯) roll(滚转)，分别对应YXZ轴旋转
	auto rotateMatrix = glm::yawPitchRoll(m_rotate.y, m_rotate.x, m_rotate.z);
	auto scaleMatrix = glm::scale(glm::mat4x4(1.0f), m_scale);
	auto transform = translateMatrix * rotateMatrix * scaleMatrix;
	return transform;
}

void Node::setTranslate(const glm::vec3 &translate)
{
	m_translate = translate;
	updateRenderTransform();
}

void Node::setRotate(const glm::vec3 &rotate)
{
	m_rotate = rotate;
	updateRenderTransform();
}

void Node::setScale(const glm::vec3 &scale)
{
	m_scale = scale;
	updateRenderTransform();
}

const glm::vec3 &Node::getTranslate() const
{
	return m_translate;
}

const glm::vec3 &Node::getRotate() const
{
	return m_rotate;
}

const glm::vec3 &Node::getScale() const
{
	return m_scale;
}

void Node::updateRenderTransform()
{
	std::function<void(Node*, glm::mat4&)> updateTreeRenderTransform = [&updateTreeRenderTransform](Node * node, glm::mat4 & parentRenderTransform)
	{
		node->m_renderTransform = parentRenderTransform * node->getTransform();
		for (auto child : node->children())
		{
			updateTreeRenderTransform(child.get(), node->m_renderTransform);
		}
	};

	glm::mat4 parentRenderTransform = m_parent ? m_parent->getRenderTransform() : glm::mat4(1.0f);
	updateTreeRenderTransform(this, parentRenderTransform);
}

void Node::onResize(float width, float height)
{
}

void Node::onRender()
{
}