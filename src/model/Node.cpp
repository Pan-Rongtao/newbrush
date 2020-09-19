#include "newbrush/model/Node.h"

using namespace nb;

Node::Node()
	: Node("")
{
}

Node::Node(const std::string & name)
	: m_name(name)
	, m_transform(std::make_shared<Transform>())
	, m_parent(nullptr)
{
}

void Node::setName(const std::string & name)
{
	m_name = name;
}

const std::string & Node::name()
{
	return m_name;
}

const Node *const Node::parent() const
{
	return m_parent;
}

void Node::addChild(NodePtr child)
{
	child->m_parent = this;
	m_children.push_back(child);
}

void Node::removeChild(NodePtr child)
{
	auto iter = std::find(m_children.begin(), m_children.end(), child);
	if (iter != m_children.end())
	{
		m_children.erase(iter);
	}
}

void Node::removeAt(uint32_t index)
{
	if (index >= m_children.size())
	{
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %zu)", index, m_children.size());
	}
	m_children.erase(m_children.begin() + index);
}

NodePtr Node::childAt(uint32_t index)
{
	if (index >= m_children.size())
	{
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %zu)", index, m_children.size());
	}
	return m_children[index];
}

uint32_t Node::childCount() const
{
	return m_children.size();
}

void Node::setTransform(TransformPtr transform)
{
	m_transform = transform;
}

TransformPtr Node::transform()
{
	return m_transform;
}

glm::mat4 Node::getRenderTransform() const
{
	glm::mat4 mat(1.0);
	auto p = this;
	do {
		auto transform = p->m_transform ? p->m_transform->value() : glm::mat4(1.0f);
		mat = transform * mat;
	} while ((p->m_parent) && (p = p->m_parent));
	return mat;
}

NodePtr Node::find(const std::string & name)
{
	std::function<void(NodePtr node, const std::string &name, NodePtr &ret)> loopFind = [&loopFind](NodePtr node, const std::string &name, NodePtr &ret)
	{
		if (!node) return;
		if (ret) return;

		if (node && node->name() == name)
		{
			ret = node;
		}

		//未找到就才需要再继续了
		if (ret == nullptr)
		{
			for (auto i = 0u; i != node->childCount(); ++i)
			{
				auto child = node->childAt(i);
				loopFind(child, name, ret);
			}
		}
	};

	NodePtr ret;
	loopFind(shared_from_this(), name, ret);
	return ret;
}

void Node::setMaterial(MaterialPtr material)
{
	loopSetMaterial(this, material);
}

void Node::getInfo(int32_t & meshCount, int32_t & triangleCount, int32_t & vertexCount)
{
	std::function<void(Node * node, int32_t & meshCount, int32_t & triangleCount, int32_t & vertexCount)> loopGet;
	loopGet = [&loopGet](Node * node, int32_t & meshCount, int32_t & triangleCount, int32_t & vertexCount)
	{
		if (!node) return;

		if (is<MeshNode>(node))
		{
			auto mesh = (as<MeshNode>(node))->mesh();
			meshCount += 1;
			triangleCount += mesh->triangleCount();
			vertexCount += mesh->vertexs.size();
		}
		else
		{
			for (auto i = 0u; i != node->childCount(); ++i)
			{
				auto child = node->childAt(i);
				loopGet(child.get(), meshCount, triangleCount, vertexCount);
			}
		}
	};
	loopGet(this, meshCount, triangleCount, vertexCount);
}

void Node::loopSetMaterial(Node * node, MaterialPtr material)
{
	if (!node || !material) return;

	if (is<MeshNode>(node))
	{
		auto mesh = (as<MeshNode>(node))->mesh();
		mesh->material = material;
	}
	else
	{
		for (auto i = 0u; i != node->childCount(); ++i)
		{
			auto child = node->childAt(i);
			loopSetMaterial(child.get(), material);
		}
	}
}

void Node::printTree()
{
}

MeshNode::MeshNode(const std::string &name, MeshPtr mesh)
	: Node(name)
	, m_mesh(mesh)
{
}

const MeshPtr & MeshNode::mesh() const
{
	return m_mesh;
}
