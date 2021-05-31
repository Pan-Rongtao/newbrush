#include "newbrush/Transform.h"

using namespace nb;

static const glm::mat4 g_sIdentityMat4(1.0f);

Transform::Transform(const glm::vec3 &translate, const glm::vec3 &rotation, const glm::vec3 &scale)
	: m_translate(translate)
	, m_rotate(rotation)
	, m_scale(scale)
	, m_rotateCenter(0.0f)
	, m_scaleCenter(0.0f)
{
	updateMatrix();
}

void Transform::setTranslate(const glm::vec3 &translate)
{
	m_translate = translate;
	updateMatrix();
}

void Transform::setRotate(const glm::vec3 &rotate)
{
	m_rotate = rotate;
	updateMatrix();
}

void Transform::setRotateCenter(const glm::vec3 & center)
{
	m_rotateCenter = center;
	updateMatrix();
}

void Transform::setScale(const glm::vec3 &scale)
{
	m_scale = scale;
	updateMatrix();
}

void Transform::setScaleCenter(const glm::vec3 & center)
{
	m_scaleCenter = center;
	updateMatrix();
}

const glm::vec3 &Transform::getTranslate() const
{
	return m_translate;
}

const glm::vec3 &Transform::getRotate() const
{
	return m_rotate;
}

const glm::vec3 &Transform::getScale() const
{
	return m_scale;
}

bool Transform::isIdentity() const
{ 
	return glm::isIdentity(value(), 0.00001f); 
}

const Transform &Transform::identity()
{
	static Transform t;
	return t;
}

//转换为平移、旋转、缩放。注意，转换后的缩放vec可能和C4D等编辑器中显示的符号相反，
//欧拉角也和C4D等编辑器上的数值不一致。不必在意，因为C4D使用的是左手定则，
//只要最后相乘计算得到的矩阵=value就可以了
void Transform::setValue(const glm::mat4x4 & value)
{
	glm::vec3 skew;
	glm::quat orientation;
	glm::vec4 perspective;
	//分解为scale、orientation四元素和position
	glm::decompose(value, m_scale, orientation, m_translate, skew, perspective);

	//四元素转旋转矩阵
	auto rMatrix = glm::mat4_cast(orientation);

	//旋转矩阵提取欧拉角
	glm::extractEulerAngleYXZ(rMatrix, m_rotate.y, m_rotate.x, m_rotate.z);
	m_matrix = value;
}

const glm::mat4x4 &Transform::value() const
{
	return m_matrix;
}

void Transform::updateMatrix()
{
	auto translateMatrix = glm::translate(glm::mat4x4(1.0f), m_translate);
	//旋转	HPB{朝向，仰俯，侧倾}，或者YPR ： yaw(航向) pitch(仰俯) roll(滚转)，分别对应YXZ轴旋转
	auto rotateMatrix = glm::yawPitchRoll(m_rotate.y, m_rotate.x, m_rotate.z);
	auto scaleMatrix = glm::scale(glm::mat4x4(1.0f), m_scale);

	m_matrix = translateMatrix * rotateMatrix * scaleMatrix;
}

TranslateTransform2D::TranslateTransform2D()
	: TranslateTransform2D(0.0f, 0.0f)
{

}

TranslateTransform2D::TranslateTransform2D(float x, float y)
	: m_x(x)
	, m_y(y)
{
}

void TranslateTransform2D::setX(float x)
{
	m_x = x;
}

float TranslateTransform2D::getX() const
{
	return m_x;
}

void TranslateTransform2D::setY(float y)
{
	m_y = y;
}

float TranslateTransform2D::getY() const
{
	return m_y;
}

glm::mat4x4 TranslateTransform2D::value()
{
	return glm::translate(g_sIdentityMat4, glm::vec3(m_x, m_y, 0.0f));
}

RotateTransform2D::RotateTransform2D()
	: RotateTransform2D(0.0f, 0.0f, 0.0f)
{
}

RotateTransform2D::RotateTransform2D(float angle)
	: RotateTransform2D(angle, 0.0f, 0.0f)
{
}

RotateTransform2D::RotateTransform2D(float angle, float centerX, float centerY)
	: m_angle(angle)
	, m_centerX(centerX)
	, m_centerY(centerY)
{
}

void RotateTransform2D::setAngle(float angle)
{
	m_angle = angle;
}

float RotateTransform2D::getAngle() const
{
	return m_angle;
}

void RotateTransform2D::setCenterX(float centerX)
{
	m_centerX = centerX;
}

float RotateTransform2D::getCenterX() const
{
	return m_centerX;
}

void RotateTransform2D::setCenterY(float centerY)
{
	m_centerY = centerY;
}

float RotateTransform2D::getCenterY() const
{
	return m_centerY;
}

glm::mat4x4 RotateTransform2D::value()
{
	auto matrix = glm::translate(g_sIdentityMat4, glm::vec3(m_centerX, m_centerY, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(m_angle), glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::translate(matrix, glm::vec3(-m_centerX, -m_centerY, 0.0f));

	return matrix;
}

ScaleTransform2D::ScaleTransform2D()
	: ScaleTransform2D(0.0f, 0.0f, 0.0f, 0.0f)
{
}

ScaleTransform2D::ScaleTransform2D(float scaleX, float scaleY)
	: ScaleTransform2D(scaleX, scaleY, 0.0f, 0.0f)
{
}

ScaleTransform2D::ScaleTransform2D(float scaleX, float scaleY, float centerX, float centerY)
	: m_scaleX(scaleX)
	, m_scaleY(scaleY)
	, m_centerX(centerX)
	, m_centerY(centerY)
{
}

void ScaleTransform2D::setScaleX(float scaleX)
{
	m_scaleX = scaleX;
}

float ScaleTransform2D::getScaleX() const
{
	return m_scaleX;
}

void ScaleTransform2D::setScaleY(float scaleY)
{
	m_scaleY = scaleY;
}

float ScaleTransform2D::getScaleY() const
{
	return m_scaleY;
}

void ScaleTransform2D::setScale(glm::vec2 scale)
{
	m_scaleX = scale.x;
	m_scaleY = scale.y;
}

glm::vec2 ScaleTransform2D::getScale() const
{
	return {m_scaleX, m_scaleY};
}

void ScaleTransform2D::setCenterX(float centerX)
{
	m_centerX = centerX;
}

float ScaleTransform2D::getCenterX() const
{
	return m_centerX;
}

void ScaleTransform2D::setCenterY(float centerY)
{
	m_centerY = centerY;
}

float ScaleTransform2D::getCenterY() const
{
	return m_centerY;
}

glm::mat4x4 ScaleTransform2D::value()
{
	auto matrix = glm::translate(g_sIdentityMat4, glm::vec3(m_centerX * (1 - m_scaleX), m_centerY * (1 - m_scaleY), 0.0f));
	matrix = glm::scale(matrix, glm::vec3(m_scaleX, m_scaleY, 1.0f));

	return matrix;
}

TransformGroup2D::TransformGroup2D()
{

}

TransformGroup2D::TransformGroup2D(const std::vector<ref<Transform2D>>& children)
	: m_children(children)
{
}

void TransformGroup2D::add(ref<Transform2D> t)
{
	m_children.push_back(t);
}

uint32_t TransformGroup2D::count() const
{
	return m_children.size();
}

glm::mat4x4 TransformGroup2D::value()
{
	glm::mat4x4 matrix = g_sIdentityMat4;
	for (size_t i = 0; i < m_children.size(); i++)
	{
		matrix = m_children[i]->value() * matrix;
	}
	return matrix;
}
