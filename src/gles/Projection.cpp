#include "gles/Projection.h"
#include "glm/gtc/matrix_transform.hpp"
#include <math.h>

using namespace nb::gl;

Projection::Projection()
	: m_matrix(1)
{
}

glm::mat4x4 &Projection::matrix()
{
	return m_matrix;
}

const glm::mat4x4 &Projection::matrix() const
{
	return m_matrix;
}

void Projection::ortho(float left, float right, float bottom, float top, float near, float far)
{
	m_matrix = glm::ortho(left, right, bottom, top, near, far);
}

void Projection::perspective(float fovy, float aspect, float near, float far)
{
	m_matrix = glm::perspective(fovy, aspect, near, far);
}

std::shared_ptr<Projection> Projection::instance()
{
	static std::shared_ptr<Projection> p;
	if (!p)
		p = std::make_shared<Projection>();
	return p;
}
