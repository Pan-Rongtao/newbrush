#include "gui/Transform.h"

using namespace nb::Media;
//NB_OBJECT_TYPE_IMPLEMENT(Transform, nbObject, NULL, NULL);
NB_OBJECT_NO_ASSEMBLY_TYPE_IMPLEMENT(Transform, nbObject);

Transform::Transform()
{
//	m_matrix.Identity();
}

Transform::~Transform(void)
{

}

Point Transform::Translate(Point point)
{
	return point*Value();
}
