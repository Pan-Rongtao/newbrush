/*******************************************************
**	Vertex/Mesh/Model
**
**	
**		模型由Mesh集合构成，Mesh则由顶点集合构成，一个顶点包含position、color、texCoord以及normal属性数据，
**		一般而言，简单的模型由一个Mesh构成，而复杂的模型可能由多个Mesh构成。
**	
**		顶点的构成如下：
**		Vertex：	Position	Color		TextureCoordinate		Normal
**						3		  4					2				  3			= 12
**		Mesh可选择性的构建这些属性，Mesh中的顶点集合使用同样的属性构成，也就是说，Mesh中的
**		每个顶点都拥有相同的数据空间，比如Position|Color；而如果一个模型有多个Mesh，理论上每个Mesh
**		都可以拥有自己的顶点属性构成，因为在实际绘制过程中，每个Mesh都是单独绘制的。但即使这样，
**		也没有区分使用不同顶点属性构成的必要。
**		
**		潘荣涛
**	
********************************************************/
#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "newbrush/Core.h"

namespace nb
{

class Camera;
class Light;
class Material;

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class NB_API Mesh
{
public:
	Mesh(const std::vector<Vertex> &vertexs, const std::vector<uint16_t> &indices, ref<Material> materia);
	~Mesh();

	//渲染参数虚函数,glEnable等
	virtual void drawFlags() const;
	virtual void draw(const glm::mat4 &matrix, ref<Camera> camera, const std::vector<ref<Light>> &lights) const;

	ref<Material> material;

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
