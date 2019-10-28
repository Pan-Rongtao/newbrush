#pragma once
#include <vector>
#include "Model.h"

namespace nb{
namespace gl{

class NB_API Strips : public Model
{
public:
	//构建一个空的带状
	Strips();

	//构建一个带状，它的折点为breaks
	Strips(const std::vector<glm::vec2> &breaks);

	//构建一个带状，它的折点为breaks，厚度为thickness
	Strips(const std::vector<glm::vec2> &breaks, float thickness);

	//构建一个带状，它的折点为breaks，厚度为thickness，间隔样式为dashArray，偏移量为dashOffset
	Strips(const std::vector<glm::vec2> &breaks, float thickness, const std::vector<float> &dashArray, float dashOffset);

	//厚度
	void setThickness(float thickness);
	const float &thickness() const;

	//间隔样式
	void setDashArray(const std::vector<float> &array);
	const std::vector<float> &dashArray() const;

	//偏移量
	void setDashOffset(float offset);
	float dashOffset() const;

	//

private:
	//线段类 y = kx + b
	class LineSegment
	{
	public:
		LineSegment(const glm::vec2 &p0, const glm::vec2 &p1);

		//两点p0, p1
		const glm::vec2 &p0() const;
		const glm::vec2 &p1() const;

		//水平和垂直方向的距离值，可为负数
		float xDiff() const;
		float yDiff() const;

		//线段长度
		float length() const;

		float evalX(float y) const;

		float evalY(float x) const;
		//执行虚线计算
		void dashing(float offset, const std::vector<float> &array, float thickness, std::vector<glm::vec2> &points);

	private:
		glm::vec2	m_p0;
		glm::vec2	m_p1;
		float		m_k;
		float		m_b;
	};

	void updateVertexs();
	float nextArrayElementInLoop(uint32_t nCurrentIndex);
	std::vector<uint16_t> getIndices(int vertexCount) const;

	float					m_thickness;
	float					m_dashOffset;
	std::vector<float>		m_dashArray;
	std::vector<glm::vec2>	m_breaks;
};

}}