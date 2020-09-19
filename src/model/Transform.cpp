#include "newbrush/model/Transform.h"

using namespace nb;

Transform::Transform()
	: m_position(glm::vec3(0.0f))
	, m_rotate(glm::vec3(0.0f))
	, m_scale(glm::vec3(1.0f))
	, m_scaleCenter(glm::vec3(0.0f))
{
}

bool Transform::isIdentity() const
{
	return glm::isIdentity(value(), 0.00001f);
}

Transform Transform::identity()
{
	return Transform();
}

void Transform::setPosition(const glm::vec3 & position)
{
	m_position = position;
}

const glm::vec3 & Transform::position() const
{
	return m_position;
}

void Transform::setRotate(const glm::vec3 & rotate)
{
	m_rotate = rotate;
}

const glm::vec3 & Transform::rotate() const
{
	return m_rotate;
}

void Transform::setScale(const glm::vec3 & scale)
{
	m_scale = scale;
}

const glm::vec3 & Transform::scale() const
{
	return m_scale;
}

void Transform::setScaleCenter(const glm::vec3 & center)
{
	m_scaleCenter = center;
}

const glm::vec3 & Transform::scaleCenter() const
{
	return m_scaleCenter;
}

//转换为平移、旋转、缩放。注意，转换后的缩放vec可能和C4D等编辑器中显示的符号相反，欧拉角也和C4D等编辑器上的数值不一致，
//不必在意，因此C4D使用的是左手定则只要最后相乘计算得到的矩阵=value就可以了
void Transform::setValue(const glm::mat4x4 & value)
{
	glm::vec3 skew;
	glm::quat orientation;
	glm::vec4 perspective;
	//分解为scale、orientation四元素和position
	glm::decompose(value, m_scale, orientation, m_position, skew, perspective);

	//四元素转旋转矩阵
	auto rMatrix = glm::mat4_cast(orientation);	

	//旋转矩阵提取欧拉角
	glm::extractEulerAngleYXZ(rMatrix, m_rotate.y, m_rotate.x, m_rotate.z);

	//一系列转换后，最终计算矩阵一定与原value相等
	/*
	lm::vec3 degree = { glm::degrees(m_rotate.x), glm::degrees(m_rotate.y), glm::degrees(m_rotate.z) };
	auto getV = this->value();
	auto b0 = glm::all(glm::equal(value, getV, 0.01f));
	if (!b0)
	{
		int xx = 10;
	}
	*/

}

glm::mat4x4 Transform::value() const
{
	auto translateMatrix = glm::translate(glm::mat4x4(1.0f), m_position);
	//旋转	HPB{朝向，仰俯，侧倾}，或者YPR ： yaw(航向) pitch(仰俯) roll(滚转)，分别对应YXZ轴旋转
	auto rotateMatrix = glm::yawPitchRoll(m_rotate.y, m_rotate.x, m_rotate.z);
	auto scaleMatrix = glm::translate(glm::mat4x4(1.0f), glm::vec3(m_scaleCenter.x * (1 - m_scale.x), m_scaleCenter.y * (1 - m_scale.y), m_scaleCenter.z * (1 - m_scale.z)));
	scaleMatrix = glm::scale(scaleMatrix, m_scale);

	return translateMatrix * rotateMatrix * scaleMatrix;
}
