#include <GLES2/gl2.h>
#include <assert.h>
#include "gles/Model.h"
#include "core/Exception.h"

using nb::Math::Vec2;
using nb::Math::Vec3;
using nb::Math::Vec4;
using nb::Math::Matrix4x4;
using nb::gl::Gles::Model;
using nb::gl::Gles::ModelEventListener;
using nb::gl::Gles::IndicesSequece;

Model::Model(int nVertexCount, nb::System::EnumFlags<Model::VertexAttributesType> flags)
: m_AttributeFlags(flags)
, m_Data(NULL)
, m_nVertexCount(nVertexCount)
, m_Matrix(Matrix4x4::Identify())
, m_Listener(NULL)
{
	if(nVertexCount < 0)
	{
		m_nVertexCount = 0;
		NB_THROW_EXCEPTION("invalid param");
	}

	m_Data = new float[GetVertexStrideUnit() * nVertexCount];
}

Model::~Model()
{
	delete [] m_Data;
}

bool Model::HasVertexAttribute(VertexAttributesType type) const
{
	return m_AttributeFlags.TestFlag(type);
}

float *Model::GetData() const
{
	return m_Data;
}

int Model::GetVertexCount() const
{
	return m_nVertexCount;
}

void Model::SetPositionArrayData(float *data)
{
	for(int i = 0; i != GetVertexCount(); ++i)
		SetPositionAt(i, Vec3(*(data + PositionDimension() * i), *(data + PositionDimension() * i + 1), *(data + PositionDimension() * i + 2)));
	if(m_Listener)
		m_Listener->On_ModelData_Changed(Vertex_Attribute_Position);
}

void Model::SetPositionAt(int vertexIndex, const nb::Math::Vec3 &position)
{
	if(GetPositionArrayData() == NULL)
		NB_THROW_EXCEPTION("no such attribute");
	float *p = GetPositionArrayData() + vertexIndex * GetVertexStrideUnit();
	*(p + 0) = position.X();
	*(p + 1) = position.Y();
	*(p + 2) = position.Z();
	if(m_Listener)
		m_Listener->On_ModelData_Changed(Vertex_Attribute_Position);
}

float *Model::GetPositionArrayData() const
{
	return HasVertexAttribute(Vertex_Attribute_Position) ? m_Data : NULL;
}

Vec3 Model::GetPositionAt(int vertexIndex) const
{
	if(GetPositionArrayData() == NULL)
		NB_THROW_EXCEPTION("no such attribute");
	float *p = GetPositionArrayData() + vertexIndex * GetVertexStrideUnit();
	return Vec3(*(p + 0), *(p + 1), *(p + 2));
}

void Model::SetColorArrayData(float *data)
{
	for(int i = 0; i != GetVertexCount(); ++i)
		SetColorAt(i, Vec4(*(data + ColorDimension() * i), *(data + ColorDimension() * i + 1), *(data + ColorDimension() * i + 2), *(data + ColorDimension() * i + 3)));
	if(m_Listener)
		m_Listener->On_ModelData_Changed(Vertex_Attribute_Color);
}

void Model::SetColorAt(int vertexIndex, const nb::Math::Vec4 &color)
{
	if(GetColorArrayData() == NULL)
		NB_THROW_EXCEPTION("no such attribute");
	float *p = GetColorArrayData() + vertexIndex * GetVertexStrideUnit();
	*(p + 0) = color.X();
	*(p + 1) = color.Y();
	*(p + 2) = color.Z();
	*(p + 3) = color.W();
	if(m_Listener)
		m_Listener->On_ModelData_Changed(Vertex_Attribute_Color);
}

float *Model::GetColorArrayData() const
{
	return m_Data + (HasVertexAttribute(Vertex_Attribute_Position) ? PositionDimension() : 0);
}

Vec4 Model::GetColorAt(int vertexIndex) const
{
	if(GetColorArrayData() == NULL)
		NB_THROW_EXCEPTION("no such attribute");
	float *p = GetColorArrayData() + vertexIndex * GetVertexStrideUnit();
	return Vec4(*(p + 0), *(p + 1), *(p + 2), *(p + 3));
}

void Model::SetTextureCoordinateArrayData(float *data)
{
	for(int i = 0; i != GetVertexCount(); ++i)
		SetTextureCoordinateAt(i, Vec2(*(data + TextureCoordinateDimension() * i), *(data + TextureCoordinateDimension() * i + 1)));
	if(m_Listener)
		m_Listener->On_ModelData_Changed(Vertex_Attribute_TextureCoordinate);
}

void Model::SetTextureCoordinateAt(int vertexIndex, const nb::Math::Vec2 &texCoord)
{
	if(GetTextureCoordinateArrayData() == NULL)
		NB_THROW_EXCEPTION("no such attribute");
	float *p = GetTextureCoordinateArrayData() + vertexIndex * GetVertexStrideUnit();
	*(p + 0) = texCoord.X();
	*(p + 1) = texCoord.Y();
	if(m_Listener)
		m_Listener->On_ModelData_Changed(Vertex_Attribute_TextureCoordinate);
}

float *Model::GetTextureCoordinateArrayData() const
{
	int offset = 0;
	if(HasVertexAttribute(Vertex_Attribute_Position))	offset += PositionDimension();
	if(HasVertexAttribute(Vertex_Attribute_Color))		offset += ColorDimension();
	return m_Data + offset;
}

Vec2 Model::GetTextureCoordinateAt(int vertexIndex) const
{
	if(GetTextureCoordinateArrayData() == NULL)
		NB_THROW_EXCEPTION("no such attribute");
	float *p = GetTextureCoordinateArrayData() + vertexIndex * GetVertexStrideUnit();
	return Vec2(*(p + 0), *(p + 1));
}

void Model::SetNormalArrayData(float *data)
{
	for(int i = 0; i != GetVertexCount(); ++i)
		SetNormalAt(i, Vec3(*(data + NormalDimension() * i), *(data + NormalDimension() * i + 1), *(data + NormalDimension() * i + 2)));
	if(m_Listener)
		m_Listener->On_ModelData_Changed(Vertex_Attribute_Normal);
}

void Model::SetNormalAt(int vertexIndex, const nb::Math::Vec3 &texCoord)
{
	if(GetNormalArrayData() == NULL)
		NB_THROW_EXCEPTION("no such attribute");
	float *p = GetNormalArrayData() + vertexIndex * GetVertexStrideUnit();
	*(p + 0) = texCoord.X();
	*(p + 1) = texCoord.Y();
	*(p + 2) = texCoord.Z();
	if(m_Listener)
		m_Listener->On_ModelData_Changed(Vertex_Attribute_Normal);
}

float *Model::GetNormalArrayData() const
{
	int offset = 0;
	if(HasVertexAttribute(Vertex_Attribute_Position))			offset += PositionDimension();
	if(HasVertexAttribute(Vertex_Attribute_Color))				offset += ColorDimension();
	if(HasVertexAttribute(Vertex_Attribute_TextureCoordinate))	offset += TextureCoordinateDimension();
	return m_Data + offset;
}

Vec3 Model::GetNormalAt(int vertexIndex) const
{
	if(GetNormalArrayData() == NULL)
		NB_THROW_EXCEPTION("no such attribute");
	float *p = GetNormalArrayData() + vertexIndex * GetVertexStrideUnit();
	return Vec3(*(p + 0), *(p + 1), *(p + 2));
}

int Model::GetVertexStrideUnit() const
{
	int units = 0;
	if(HasVertexAttribute(Vertex_Attribute_Position))			units += PositionDimension();
	if(HasVertexAttribute(Vertex_Attribute_Color))				units += ColorDimension();
	if(HasVertexAttribute(Vertex_Attribute_TextureCoordinate))	units += TextureCoordinateDimension();
	if(HasVertexAttribute(Vertex_Attribute_Normal))				units += NormalDimension();
	return units;
}

void Model::UnifyColor(const nb::Math::Vec4 &color)
{
	if(GetColorArrayData() == NULL)
		NB_THROW_EXCEPTION("no such attribute");
	for(int i = 0; i != GetVertexCount(); ++i)
		SetColorAt(i, color);
}

IndicesSequece Model::VertextsSequenceOverride() const
{
	unsigned short count = GetVertexCount();
	unsigned short *indices = new unsigned short[count];
	for(unsigned short i = 0; i != count; ++i)
		indices[i] = i;
	IndicesSequece ret(indices, count);
	delete []indices;
	return ret;
}

void Model::SetMatrix(const nb::Math::Matrix4x4 &matrix)
{
	m_Matrix = matrix;
}

nb::Math::Matrix4x4 &Model::GetMatrix()
{
	return m_Matrix;
}

const nb::Math::Matrix4x4 &Model::GetMatrix() const
{
	return m_Matrix;
}

bool Model::HitTest(int x, int y) const
{
	return false;
}

bool Model::TriangleTest(const nb::Math::Vec3 & a, const nb::Math::Vec3 &b, const nb::Math::Vec3 &c, int x, int y) const
{
/*	CELL::Ray ray = Domain::GetInstance()->GetCamera()->GetPrivateData()->CreateRayFromScreen(x, y);
	float t, u, v;
	CELL::float4 tranVec1 = GetModelMatrix().GetPrivateData()->m_matrix * CELL::float4(a.X(),a.Y(),a.Z(),1.0);
	CELL::float4 tranVec2 = GetModelMatrix().GetPrivateData()->m_matrix * CELL::float4(b.X(),b.Y(),b.Z(), 1.0);
	CELL::float4 tranVec3 = GetModelMatrix().GetPrivateData()->m_matrix * CELL::float4(c.X(),c.Y(),c.Z(),1.0);

	CELL::float3 v1(tranVec1.x, tranVec1.y, tranVec1.z);
	CELL::float3 v2(tranVec2.x, tranVec2.y, tranVec2.z);
	CELL::float3 v3(tranVec3.x, tranVec3.y, tranVec3.z);
	return CELL::intersectTriangle<float>(ray.getOrigin(), ray.getDirection(), v1, v2, v3, &t, &u, &v);*/
	return false;
}

int Model::PositionDimension()
{
	return 3;
}

int Model::ColorDimension()
{
	return 4;
}

int Model::TextureCoordinateDimension()
{
	return 2;
}

int Model::NormalDimension()
{
	return 3;
}

void Model::SetListener(ModelEventListener *listener)
{
	m_Listener = listener;
}
