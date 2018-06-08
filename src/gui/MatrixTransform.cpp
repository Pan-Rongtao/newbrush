#include "gui/MatrixTransform.h"

using namespace nb::Media;

MatrixTransform::MatrixTransform()
{
//	m_matrix.Identity();
}

nb::Media::MatrixTransform::MatrixTransform(const nb::Math::Matrix3x3& matrix)
{
	m_matrix = matrix;
}

 MatrixTransform::MatrixTransform(float M11,float M12,float M21,float M22,float OffsetX,float OffsetY)
//:m_matrixTransform(M11, M12, M21, M22, OffsetX, OffsetY)
 {
	m_matrix = m_matrixTransform;
 }

MatrixTransform::~MatrixTransform()
{

}

nb::Math::Matrix3x3 MatrixTransform::Value()
{
	return m_matrix;
}

void nb::Media::MatrixTransform::SetMatrix(nb::Math::Matrix3x3 matrix)
{
	m_matrix = matrix;

}
