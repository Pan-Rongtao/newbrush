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
#include "../core/EnumFlags.h"
#include "glm/glm.hpp"
#include <vector>

namespace nb{ namespace gl{

class NB_API Vertex
{
public:
	//顶点属性类型
	enum VertexAttributeE
	{
		positionAttribute			= 0x00000001 << 0,		//位置
		colorAttribute				= 0x00000001 << 1,		//颜色
		textureCoordinateAttribute	= 0x00000001 << 2,		//纹理坐标
		normalAttribute				= 0x00000001 << 3,		//法线
	};

public:
	Vertex();
	explicit Vertex(const glm::vec3 &position);
	Vertex(const glm::vec3 &position, const glm::vec4 &color);
	Vertex(const glm::vec3 &position, const glm::vec4 &color, const glm::vec2 &texCoord);
	Vertex(const glm::vec3 &position, const glm::vec4 &color, const glm::vec2 &texCoord, const glm::vec3 &normal);

	//获取位置数据|颜色数据|颜色数据|法线数据的组件数
	static constexpr int positionDimension			= 3;
	static constexpr int colorDimension				= 4;
	static constexpr int textureCoordinateDimension = 2;
	static constexpr int normalDimension			= 3;

	glm::vec3	position;
	glm::vec4	color;
	glm::vec2	texCoord;
	glm::vec3	normal;
};

class NB_API Mesh
{
public:
	Mesh(const nb::core::EnumFlags<Vertex::VertexAttributeE> &attributes);

	//vertexs：顶点集合
	//indices：顶点序列（逆时针，且隐藏背面）
	Mesh(const nb::core::EnumFlags<Vertex::VertexAttributeE> &attributes, const std::vector<Vertex> &vertexs, const std::vector<uint16_t> &indices);

	//是否有属性
	bool hasAttribute(Vertex::VertexAttributeE attr) const;

	//获取位置|颜色|纹理坐标|法向量数据
	float *positionData();
	const float *positionData() const;
	float *colorData();
	const float *colorData() const;
	float *textureCoordinateData();
	const float *textureCoordinateData() const;
	float *normalData();
	const float *normalData() const;

	//顶点集合
	std::vector<Vertex> &vertexs();
	const std::vector<Vertex> &vertexs() const;

	//顶点序列(逆时针)
	const std::vector<uint16_t> &indices() const;

	//将所有顶点颜色统一
	void unifyColor(const glm::vec4 &color);

private:
	nb::core::EnumFlags<Vertex::VertexAttributeE>	m_attributes;
	std::vector<Vertex>								m_vertexs;
	std::vector<uint16_t>							m_indices;
};

class NB_API Model
{
public:
	//构建一个模型，它的顶点个数为_vertexCount，属性类型为flags
	//异常：nVertexCount < 0
	Model();
	virtual ~Model() = default;

	//mesh集合
	std::vector<Mesh> &meshes();
	const std::vector<Mesh> &meshes() const;

	//设置模型矩阵(经过了平移、旋转、缩放）
	void setMatrix(const glm::mat4x4 &matrix);

	//获取模型矩阵(经过了平移、旋转、缩放）
	const glm::mat4x4 &getMatrix() const;

	//平移
	void translate(float x, float y, float z);

	//旋转（角度）
	void rotate(float angle, float x, float y, float z);

	//缩放
	void scale(float x, float y, float z);

	//命中测试
	virtual bool hitTest(int x, int y) const;

	bool triangleTest(const glm::vec3 & a, const glm::vec3 &b, const glm::vec3 &c, int x, int y) const;

	//剔除表面，不重写则禁用
	virtual void cullFace();

	//绘制方式，不重写则默认为GL_TRIANGLES
	virtual unsigned int drawMode() const;

private:
	glm::mat4x4								m_matrix;
	glm::mat4x4								m_translateMatrix;
	glm::mat4x4								m_rotateMatrix;
	glm::mat4x4								m_scaleMatrix;
	std::vector<Mesh>						m_meshes;
};

}}
