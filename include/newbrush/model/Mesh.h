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
#include "newbrush/model/Material.h"
#include "newbrush/model/Light.h"
#include "newbrush/model/Camera.h"
#include "newbrush/glm.h"

namespace nb{

class NB_API Vertex
{
public:
	Vertex();
	explicit Vertex(const glm::vec3 &position);
	Vertex(const glm::vec3 &position, const glm::vec4 &color);
	Vertex(const glm::vec3 &position, const glm::vec2 &texCoord);
	Vertex(const glm::vec3 &position, const glm::vec4 &color, const glm::vec2 &texCoord);
	Vertex(const glm::vec3 &position, const glm::vec4 &color, const glm::vec2 &texCoord, const glm::vec3 &normal);

	//获取位置数据|颜色数据|颜色数据|法线数据的组件数以及组件间隔
	static constexpr int positionDimension	= 3;
	static constexpr int colorDimension		= 4;
	static constexpr int texCoordDimension	= 2;
	static constexpr int normalDimension	= 3;
	static constexpr int stride				= (positionDimension + colorDimension + texCoordDimension + normalDimension) * sizeof(float);

	glm::vec3	position;
	glm::vec4	color;
	glm::vec2	texCoord;
	glm::vec3	normal;
};

class NB_API Mesh
{
public:
	Mesh();

	//vertexs：顶点集合
	//indices：顶点序列（逆时针，且隐藏背面）
	Mesh(const std::vector<Vertex> &_vertexs, const std::vector<uint16_t> &_indices);

	Mesh(const std::vector<Vertex> &_vertexs, const std::vector<uint16_t> &_indices, MaterialPtr materia);

	Mesh(const Mesh &other);
	Mesh(const Mesh &&other);
	void operator = (const Mesh &other);
	void operator = (const Mesh &&other);

	//将所有顶点颜色统一
	void unifyColor(const glm::vec4 &color);

	//三角形数
	uint32_t triangleCount() const;

	virtual void draw(CameraPtr camera, const std::vector<LightPtr> &lights) const;

	std::vector<Vertex> vertexs;	//顶点属性
	std::vector<uint16_t> indices;	//顶点序列(逆时针)
	MaterialPtr material;
	glm::mat4x4 matrix;
	uint8_t mode;		//绘画模式（默认GL_TRIANGLES，注意：为了内存，类型定义为1个字节）

private:
	//获取位置|颜色|纹理坐标|法向量数据
	float *positionData();
	const float *positionData() const;
	float *colorData();
	const float *colorData() const;
	float *textureCoordinateData();
	const float *textureCoordinateData() const;
	float *normalData();
	const float *normalData() const;

};

using MeshPtr = std::shared_ptr<Mesh>;
}
