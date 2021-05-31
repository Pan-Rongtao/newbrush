#pragma once
#include <vector>
#include "newbrush/Core.h"
#include "newbrush/Components.h"

namespace nb
{

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoord;
	glm::vec3 normal;
#define BONE_MAX 4
	float boneIndexs[BONE_MAX] = { 0.0f };
	float boneWeights[BONE_MAX] = { 0.0f };

	bool addBone(float boneIndex, float boneWeight);
};

class NB_API Mesh
{
public:
	Mesh(const std::vector<Vertex> &vertexs, const std::vector<uint16_t> &indices, ref<Material> materia);
	~Mesh();

	//渲染参数虚函数,glEnable等
	virtual void drawFlags() const;
	virtual void draw(const glm::mat4 &matrix, ref<Camera> camera, const std::vector<ref<Light>> &lights) const;

	std::string name;
	ref<Material> material;
	bool hasBone;
	bool renderAble;

protected:
	void setup(const std::vector<Vertex> &vertexs, const std::vector<uint16_t> &indices);

private:
	uint32_t vao, vbo, ebo, indicesSize;
};

class NB_API Cube : public Mesh
{
public:
	Cube();
	Cube(const glm::vec3 &center, float uniformLenght);
	Cube(const glm::vec3 &center, float lenght, float width, float height);
};

class NB_API SkyBox : public Cube
{
public:
	SkyBox();

	virtual void drawFlags() const;
	virtual void draw(const glm::mat4 &matrix, ref<Camera> camera, const std::vector<ref<Light>> &lights) const;
};

}
