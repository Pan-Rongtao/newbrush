#include "gui/RotateTransform.h"

using namespace nb::Media;

RotateTransform::RotateTransform()
:m_CenterX(0.0)
,m_CenterY(0.0)
,m_Angle(0.0)
{
//	m_matrix.Identity();
}

RotateTransform::RotateTransform(float angleInRadians)
:m_CenterX(0.0)
,m_CenterY(0.0)
,m_Angle(angleInRadians)
{
//	m_matrix.Identity();
//	m_matrix.Rotate(angleInRadians);
}

//二维平面上绕固定点旋转步骤为：先平移坐标系，旋转矩阵后，最后反平移
RotateTransform::RotateTransform(float angleInRadians , float centerX , float centerY)
:m_CenterX(centerX)
,m_CenterY(centerY)
,m_Angle(angleInRadians)
{
//	m_matrix.Identity();
	Update(m_Angle , m_CenterX , m_CenterY);
}

RotateTransform::~RotateTransform()
{

}

nb::Math::Matrix3x3 RotateTransform::Value()
{
	return m_matrix;
}

void RotateTransform::SetCenterXY(float centerX , float centerY)
{
	m_CenterX = centerX;
	m_CenterY = centerY;
//	m_matrix.Identity();
	Update(m_Angle , m_CenterX , m_CenterY);
}

void RotateTransform::SetAngle(float angle)
{
	m_Angle = angle;
//	m_matrix.Identity();
	Update(m_Angle , m_CenterX , m_CenterY);
}

 float RotateTransform::GetCenterX() const
 {
 	return m_CenterX;
 }
 
 float RotateTransform::GetCenterY() const
 {
 	return m_CenterY;
 }

float RotateTransform::GetAngle() const
{
	return m_Angle;

}

void RotateTransform::Update(float angleInRadians, float centerX, float centerY)
{
	m_matrix.Translate(-centerX,-centerY);
//	m_matrix.Rotate(angleInRadians);
	m_matrix.Translate(centerX,centerY);
}
