/*******************************************************
**	Model
**
**	模型
**	
**	模型是描述集合物体构造的数据结构
**	它的核心是顶点集合，
**		一般有一维、二维、三维模型
**
**		零维是一个无限小的点，一维是一个无限细的线，
**		二维是一个无限薄的平面，三维是一个无限大的立方体
**
**		Vertext：	Position	Color		TextureCoordinate		Normal
**						3		  4					2				  3			= 12
**		
**		潘荣涛
**	
********************************************************/
#pragma once
#include "math/Vec3.h"
#include "math/Matrix4x4.h"
#include "system/EnumFlags.h"
#include "gles/IndicesSequece.h"

namespace nb{ namespace gl{ namespace Gles{

class ModelEventListener;
class NB_EXPORT Model
{
public:
	//顶点属性类型
	enum VertexAttributesType
	{
		Vertex_Attribute_Position				= 0x00000001 << 0,	//位置
		Vertex_Attribute_Color					= 0x00000001 << 1,	//颜色
		Vertex_Attribute_TextureCoordinate		= 0x00000001 << 2,	//纹理坐标
		Vertex_Attribute_Normal					= 0x00000001 << 3,	//法线
	};

public:
	//构建一个模型，它的顶点数据类型为flags
	//异常：nVertexCount < 0
	Model(int nVertexCount, nb::System::EnumFlags<VertexAttributesType> flags);

	virtual ~Model();

public:
	//是否包含顶点属性
	bool HasVertexAttribute(VertexAttributesType type) const;

	//获取数据
	float *GetData() const;

	//获取顶点个数
	int GetVertexCount() const;

	//设置位置数据
	void SetPositionArrayData(float *data);
	void SetPositionAt(int vertexIndex, const nb::Math::Vec3 &position);

	//获取位置数据
	float *GetPositionArrayData() const;
	nb::Math::Vec3 GetPositionAt(int vertexIndex) const;

	//设置颜色数据
	void SetColorArrayData(float *data);
	void SetColorAt(int vertexIndex, const nb::Math::Vec4 &color);

	//获取颜色数据
	float *GetColorArrayData() const;
	nb::Math::Vec4 GetColorAt(int vertexIndex) const;

	//设置纹理坐标数据
	void SetTextureCoordinateArrayData(float *data);
	void SetTextureCoordinateAt(int vertexIndex, const nb::Math::Vec2 &texCoord);

	//获取纹理坐标数据
	float *GetTextureCoordinateArrayData() const;
	nb::Math::Vec2 GetTextureCoordinateAt(int vertexIndex) const;

	//设置纹理坐标数据
	void SetNormalArrayData(float *data);
	void SetNormalAt(int vertexIndex, const nb::Math::Vec3 &texCoord);

	//获取法线数据
	float *GetNormalArrayData() const;
	nb::Math::Vec3 GetNormalAt(int vertexIndex) const;

	//获取顶点数据间的单元间隔，
	//比如如果顶点属性为Vertex_Attribute_Position | Vertex_Attribute_Color | Vertex_Attribute_TextureCoordinate，返回3 + 4 + 2=9
	int GetVertexStrideUnit() const;

	//将所有顶点颜色统一
	void UnifyColor(const nb::Math::Vec4 &color);

	//顶点序列，默认为顺序。如果需要重置序列，重写此方法
	virtual IndicesSequece VertextsSequenceOverride() const;

	//设置模型矩阵
	void SetMatrix(const nb::Math::Matrix4x4 &matrix);

	//获取模型矩阵
	nb::Math::Matrix4x4 &GetMatrix();
	const nb::Math::Matrix4x4 &GetMatrix() const;

	//命中测试
	virtual bool HitTest(int x, int y) const;

	bool TriangleTest(const nb::Math::Vec3 & a, const nb::Math::Vec3 &b, const nb::Math::Vec3 &c, int x, int y) const;

	//设置事件监听
	void SetListener(ModelEventListener *listener);

public:
	//获取位置数据组件数
	static int PositionDimension();

	//获取颜色数据组件数
	static int ColorDimension();

	//获取纹理坐标数据组件数
	static int TextureCoordinateDimension();

	//获取法线数据组件数
	static int NormalDimension();

private:
	int											m_nVertexCount;
	nb::System::EnumFlags<VertexAttributesType>	m_AttributeFlags;
	float										*m_Data;
	nb::Math::Matrix4x4							m_Matrix;
	ModelEventListener							*m_Listener;
};

class NB_EXPORT ModelEventListener
{
public:
	virtual void On_ModelData_Changed(Model::VertexAttributesType type) { (void)type; }
};

}}}
