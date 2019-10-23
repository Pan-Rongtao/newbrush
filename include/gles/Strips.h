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

	//构建一个带状，它的折点为breaks
	Strips(const std::vector<glm::vec2> &breaks, float thickness);

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
	//直线方程式类 y = kx + b
	class LinearEquation
	{
	public:
		LinearEquation(const glm::vec2 &p0, const glm::vec2 &p1)
			: m_p0(p0)
			, m_p1(p1)
			, m_k((p1.y - p0.y) / (p1.x - p0.x))
			, m_b(p0.y - m_k * p0.x)
		{
		}

		float xLen() const
		{
			return std::abs(m_p1.x - m_p0.x);
		}
		float yLen() const
		{
			return std::abs(m_p1.y - m_p0.y);
		}

		float length() const
		{
			return std::hypotf(xLen(), yLen());
		}

		float evalX(float y) const
		{
			return (y - m_b) / m_k;
		}

		float evalY(float x) const
		{
			return m_k * x + m_b;
		}

	private:
		glm::vec2	m_p0;
		glm::vec2	m_p1;
		float		m_k;
		float		m_b;
	};

	void updateVertexs();
	float nextArrayElementInLoop(uint32_t nCurrentIndex);

	float					m_thickness;
	float					m_dashOffset;
	std::vector<float>		m_dashArray;
	std::vector<glm::vec2>	m_breaks;
};

}}