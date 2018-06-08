#include "gui/ScaleTransform.h"

using namespace nb::Media;

ScaleTransform::ScaleTransform()
:m_CenterX(0.0)
,m_CenterY(0.0)
,m_ScaleX(0.0)
,m_ScaleY(0.0)
{
//	m_matrix.Identity();

}

ScaleTransform::ScaleTransform(float scaleX , float scaleY)
:m_ScaleX(scaleX)
,m_ScaleY(scaleY)
,m_CenterX(0.0)
,m_CenterY(0.0)
{
//	m_matrix.Identity();
	m_matrix.Scale(scaleX , scaleY);
}

ScaleTransform::ScaleTransform(float scaleX , float scaleY , float centerX , float centerY)
:m_ScaleX(scaleX)
,m_ScaleY(scaleY)
,m_CenterX(centerX)
,m_CenterY(centerY)
{
//	m_matrix.Identity();
	Update(m_ScaleX,m_ScaleY,m_CenterX,m_CenterY);

}

ScaleTransform::~ScaleTransform()
{

}

nb::Math::Matrix3x3 ScaleTransform::Value()
{
	return m_matrix;
}

void ScaleTransform::SetCenterXY(float centerX,float centerY)
{
	m_CenterX = centerX;
	m_CenterY = centerY;
//	m_matrix.Identity();
	Update(m_ScaleX,m_ScaleY,m_CenterX,m_CenterY);
}

void ScaleTransform::SetScaleXY(float scaleX,float scaleY)
{
	m_ScaleX = scaleX;
	m_ScaleY = scaleY;
//	m_matrix.Identity();
	Update(m_ScaleX,m_ScaleY,m_CenterX,m_CenterY);
}

float ScaleTransform::GetCenterX() const
{
	return m_CenterX;
}

float ScaleTransform::GetCenterY() const
{
	return m_CenterY;
}

float ScaleTransform::GetScaleX() const
{
	return m_ScaleX;
}

float ScaleTransform::GetScaleY() const
{
	return m_ScaleY;
}

void ScaleTransform::Update(float scaleX,float scaleY,float centerX,float centerY)
{
	m_matrix.Translate(-centerX,-centerY);
	m_matrix.Scale(scaleX,scaleY);
	m_matrix.Translate(centerX,centerY);
}
