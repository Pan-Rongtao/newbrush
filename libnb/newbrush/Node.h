#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "newbrush/Object.h"

namespace nb 
{

class Node;
class Mesh;

class NB_API Node : public Object
{
	RTTR_ENABLE(Object)
public:
	Node();
	Node(const std::string &name);

	void setName(const std::string &name);
	const std::string &getName() const;

	void addChild(ref<Node> child);
	void removeChild(unsigned index);
	const std::vector<ref<Node>> &children() const;
	unsigned childCount() const;
	ref<Node> getChildAt(unsigned index);
	void clearChildren();

	void setMesh(ref<Mesh> mesh);
	ref<Mesh> mesh() const;

	void setTranslate(const glm::vec3 &translate);
	void setRotate(const glm::vec3 &rotate);
	void setScale(const glm::vec3 &scale);
	const glm::vec3 &getTranslate() const;
	const glm::vec3 &getRotate() const;
	const glm::vec3 &getScale() const;

	void setTransform(const glm::mat4 &matrix);
	glm::mat4 getTransform() const;
	const glm::mat4 &getRenderTransform() const;

	Node *getParent() const;

	virtual void onRender();
	virtual void onResize(float width, float height);

private:
	void updateRenderTransform();

	std::string m_name;
	Node *m_parent;
	ref<Mesh> m_mesh;
	std::vector<ref<Node>> m_children;

	glm::vec3 m_translate;		//平移
	glm::vec3 m_rotate;			//旋转（欧拉角旋转弧度，传入请按{x, y, z}顺序传入）
	glm::vec3 m_scale;			//缩放
	glm::mat4 m_renderTransform;
};

}