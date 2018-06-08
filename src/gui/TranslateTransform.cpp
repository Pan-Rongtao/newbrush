#include "gui/TranslateTransform.h"

using namespace nb::Media;

TranslateTransform::TranslateTransform()
:m_xOffset(0.0)
,m_yOffset(0.0)
{
//	m_matrix.Identity();

}

TranslateTransform::TranslateTransform(float offsetX , float offsetY)
{
	SetTranslationXY(offsetX,offsetY);
}

TranslateTransform::~TranslateTransform()
{

}

nb::Math::Matrix3x3 TranslateTransform::Value()
{
	return m_matrix;
}

void TranslateTransform::SetTranslationXY(float x , float y)
{
//	m_matrix.Identity();
	m_matrix.Translate(x , y);
	m_xOffset = x;
	m_yOffset = y;
}

float TranslateTransform::GetTranslationX() const
{
	return m_xOffset;
}

float TranslateTransform::GetTranslationY() const
{
	return m_yOffset;
}
