#pragma once
#include <vector>
#include "newbrush/glm.h"
#include "newbrush/model/Mesh.h"
#include "newbrush/model/Transform.h"

namespace nb {

class Node;
using NodePtr = std::shared_ptr<Node>;

class NB_API Node : public std::enable_shared_from_this<Node>, public Object
{
	RTTR_ENABLE(Object)
public:
	Node();
	Node(const std::string &name);
	virtual ~Node() = default;

	void setName(const std::string &name);
	const std::string &name();

	const Node *const parent() const;

	void addChild(NodePtr child);
	void removeChild(NodePtr child);
	void removeAt(uint32_t index);
	NodePtr childAt(uint32_t index);
	uint32_t childCount() const;

	void setTransform(TransformPtr transform);
	TransformPtr transform();
	
	glm::mat4 getRenderTransform() const;

	//模型node下所有的子节点名称都是唯一的，无例外
	NodePtr find(const std::string &name);

	void setMaterial(MaterialPtr material);

	void getInfo(int32_t &meshCount, int32_t &triangleCount, int32_t &vertexCount);

	void printTree();

private:
	void loopSetMaterial(Node *node, MaterialPtr material);

	std::string m_name;
	Node *m_parent;
	TransformPtr m_transform;
	std::vector<NodePtr> m_children;
};

class NB_API MeshNode : public Node
{
	RTTR_ENABLE(Node)
public:
	MeshNode(const std::string &name, MeshPtr mesh);

	const MeshPtr &mesh() const;

private:
	MeshPtr m_mesh;
};

using NodePtr = std::shared_ptr<Node>;
using MeshNodePtr = std::shared_ptr<MeshNode>;
}