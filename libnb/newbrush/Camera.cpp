#include "newbrush/Camera.h"
#include "glm/ext.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/matrix_query.hpp"
#include "glm/gtx/euler_angles.hpp"

using namespace nb;

PerspectiveCamera::PerspectiveCamera()
	: m_translate(0.0f, 0.0f, -10.0f)
	, m_rotate(0.0)
	, m_scale(1.0)
	, m_fov(45.0f)
	, m_aspect(1.7777777f)
	, m_nearPlane(0.3f)
	, m_farPlane(1000.0f)
{
	updateMatrix();
}

void PerspectiveCamera::setTranslate(const glm::vec3 &translate)
{
	m_translate = translate;
	updateMatrix();
}

void PerspectiveCamera::setRotate(const glm::vec3 &rotate)
{
	m_rotate = rotate;
	updateMatrix();
}

void PerspectiveCamera::setScale(const glm::vec3 &scale)
{
	m_scale = scale;
	updateMatrix();
}

const glm::vec3 &PerspectiveCamera::getTranslate() const
{
	return m_translate;
}

const glm::vec3 &PerspectiveCamera::getRotate() const
{
	return m_rotate;
}

const glm::vec3 &PerspectiveCamera::getScale() const
{
	return m_scale;
}

void PerspectiveCamera::setFov(float fov)
{
	m_fov = fov;
	updateMatrix();
}

void PerspectiveCamera::setAspect(float aspect)
{
	m_aspect = aspect;
	updateMatrix();
}

void PerspectiveCamera::setNearPlane(float nearPlane)
{
	m_nearPlane = nearPlane;
	updateMatrix();
}

void PerspectiveCamera::setFarPlane(float farPlane)
{
	m_farPlane = farPlane;
	updateMatrix();
}

float PerspectiveCamera::getFov() const
{
	return m_fov;
}

float PerspectiveCamera::getAspect() const
{
	return m_aspect;
}

float PerspectiveCamera::getNearPlane() const
{
	return m_nearPlane;
}

float PerspectiveCamera::getFarPlane() const
{
	return m_farPlane;
}

const glm::mat4 &PerspectiveCamera::getViewProjectionMatrix() const
{
	return m_viewProjectionMatrix;
}

void PerspectiveCamera::updateMatrix()
{
	auto translateMatrix = glm::translate(glm::mat4x4(1.0f), m_translate);
	//旋转	HPB{朝向，仰俯，侧倾}，或者YPR ： yaw(航向) pitch(仰俯) roll(滚转)，分别对应YXZ轴旋转
	auto rotateMatrix = glm::yawPitchRoll(m_rotate.y, m_rotate.x, m_rotate.z);
	auto scaleMatrix = glm::scale(glm::mat4x4(1.0f), m_scale);

	auto viewMatrix = translateMatrix * rotateMatrix * scaleMatrix;

	m_viewProjectionMatrix = glm::perspective(glm::radians(m_fov), m_aspect, m_nearPlane, m_farPlane) * viewMatrix;
}

/////////////
OrthographicCamera::OrthographicCamera()
	: m_matrix(1.0f)
{}

void OrthographicCamera::resize(float width, float height)
{
	m_matrix = glm::ortho(0.0f, width, height, 0.0f, -1000.0f, 1000.0f);
}

const glm::mat4 &OrthographicCamera::getViewProjectionMatrix() const
{
	return m_matrix;
}

/////////////
ref<OrthographicCamera> nb::sharedCamera2D()
{
	static auto sharedCamera = createRef<OrthographicCamera>();
	return sharedCamera;
}
