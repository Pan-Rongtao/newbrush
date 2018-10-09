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
#include "../core/Vec3.h"
#include "../core/Matrix4x4.h"
#include "../core/EnumFlags.h"
#include <vector>

namespace nb{ namespace gl{

class NB_API Vertex
{
public:
	//顶点属性类型
	enum VertexAttribute
	{
		positionAttribute			= 0x00000001 << 0,		//位置
		colorAttribute				= 0x00000001 << 1,		//颜色
		textureCoordinateAttribute	= 0x00000001 << 2,		//纹理坐标
		normalAttribute				= 0x00000001 << 3,		//法线
	};

public:
	Vertex();
	explicit Vertex(const nb::core::Vec3 &position);
	Vertex(const nb::core::Vec3 &position, const nb::core::Vec4 &color);
	Vertex(const nb::core::Vec3 &position, const nb::core::Vec4 &color, const nb::core::Vec2 &texCoord);
	Vertex(const nb::core::Vec3 &position, const nb::core::Vec4 &color, const nb::core::Vec2 &texCoord, const nb::core::Vec3 &normal);

	//位置
	nb::core::Vec3 &position();
	const nb::core::Vec3 &position() const;

	//颜色
	nb::core::Vec4 &color();
	const nb::core::Vec4 &color() const;

	//纹理坐标
	nb::core::Vec2 &texCoord();
	const nb::core::Vec2 &texCoord() const;

	//法向量
	nb::core::Vec3 &normal();
	const nb::core::Vec3 &normal() const;

public:
	//获取位置数据组件数
	static int positionDimension();

	//获取颜色数据组件数
	static int colorDimension();

	//获取纹理坐标数据组件数
	static int textureCoordinateDimension();

	//获取法线数据组件数
	static int normalDimension();

private:
	nb::core::Vec3	m_position;
	nb::core::Vec4	m_color;
	nb::core::Vec2	m_texCoord;
	nb::core::Vec3	m_normal;
};

class NB_API Mesh
{
public:
	Mesh(const nb::core::EnumFlags<Vertex::VertexAttribute> &attributes);
	Mesh(const nb::core::EnumFlags<Vertex::VertexAttribute> &attributes, const std::vector<Vertex> &vertexs, const std::vector<uint16_t> &indices);

	//是否有属性
	bool hasAttribute(Vertex::VertexAttribute attr) const;

	//获取顶点个数
	uint32_t vertexCount() const;

	//获取位置数据
	float *positionData();
	const float *positionData() const;

	//设置第vertexIndex个顶点的位置为position
	void setPositionAt(uint32_t vertexIndex, const nb::core::Vec3 &position);

	//获取第vertexIndex个顶点的位置数据
	nb::core::Vec3 positionAt(uint32_t vertexIndex) const;

	//获取颜色数据
	float *colorData();
	const float *colorData() const;

	//设置第vertexIndex个顶点的颜色为color
	void setColorAt(uint32_t vertexIndex, const nb::core::Vec4 &color);

	//获取第vertexIndex个顶点的颜色
	nb::core::Vec4 colorAt(uint32_t vertexIndex) const;

	//获取纹理坐标数据
	float *textureCoordinateData();
	const float *textureCoordinateData() const;

	//设置第vertexIndex个顶点的纹理坐标为texCoord
	void setTextureCoordinateAt(uint32_t vertexIndex, const nb::core::Vec2 &texCoord);

	//获取第vertexIndex个顶点的纹理坐标
	nb::core::Vec2 textureCoordinateAt(uint32_t vertexIndex) const;

	//获取法线数据
	float *normalData();
	const float *normalData() const;

	//设置第vertexIndex个顶点的法线为texCoord
	void setNormalAt(uint32_t vertexIndex, const nb::core::Vec3 &normal);

	//获取第vertexIndex个顶点的法线
	nb::core::Vec3 normalAt(uint32_t vertexIndex) const;

	//将所有顶点颜色统一
	void unifyColor(const nb::core::Vec4 &color);

	//顶点序列(逆时针)
	const std::vector<uint16_t> &indices() const;

private:
	nb::core::EnumFlags<Vertex::VertexAttribute>	m_attributes;
	std::vector<Vertex>								m_vertexs;
	std::vector<uint16_t>							m_indices;
};

class NB_API Model
{
public:
	//构建一个模型，它的顶点个数为_vertexCount，属性类型为flags
	//异常：nVertexCount < 0
	Model();
	virtual ~Model();

public:
	//mesh个数
	uint32_t meshCount() const;

	//mesh
	Mesh &mesh(uint32_t index);
	const Mesh &mesh(uint32_t index) const;

	std::vector<Mesh> &meshs();
	const std::vector<Mesh> &meshs() const;

	//设置模型矩阵(经过了平移、旋转、缩放）
	void setMatrix(const nb::core::Matrix4x4 &matrix);

	//获取模型矩阵(经过了平移、旋转、缩放）
	const nb::core::Matrix4x4 &getMatrix() const;

	//平移
	void translate(float x, float y, float z);

	//旋转（角度）
	void rotate(float angle, float x, float y, float z);

	//缩放
	void scale(float x, float y, float z);

	//命中测试
	virtual bool hitTest(int x, int y) const;

	bool triangleTest(const nb::core::Vec3 & a, const nb::core::Vec3 &b, const nb::core::Vec3 &c, int x, int y) const;

	virtual void cullFace();

protected:
	std::vector<Mesh>								m_meshs;

private:
	nb::core::Matrix4x4								m_matrix;
	nb::core::Matrix4x4								m_TranslateMatrix;
	nb::core::Matrix4x4								m_RotateMatrix;
	nb::core::Matrix4x4								m_ScaleMatrix;
};

}}
