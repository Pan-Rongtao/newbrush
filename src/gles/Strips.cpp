#include "gles/Strips.h"
#include <GLES2/gl2.h>

using namespace nb::gl;

Strips::Strips()
	: Strips({}, 1.0, {}, 0.0)
{
}

Strips::Strips(const std::vector<glm::vec2>& breaks)
	: Strips(breaks, 1.0, {}, 0.0)
{
}

Strips::Strips(const std::vector<glm::vec2>& breaks, float thickness)
	: Strips(breaks, thickness, {}, 0.0)
{
}

Strips::Strips(const std::vector<glm::vec2>& breaks, float thickness, const std::vector<float>& dashArray, float dashOffset)
	: m_thickness(thickness)
	, m_breaks(breaks)
	, m_dashArray(dashArray)
	, m_dashOffset(dashOffset)
{
	updateVertexs();
}

void Strips::setThickness(float thickness)
{
	m_thickness = thickness;
	updateVertexs();
}

const float & Strips::thickness() const
{
	return m_thickness;
}

void Strips::setDashArray(const std::vector<float>& array)
{
	m_dashArray = array;
	updateVertexs();
}

const std::vector<float>& Strips::dashArray() const
{
	return m_dashArray;
}

void Strips::setDashOffset(float offset)
{
	m_dashOffset = offset;
	updateVertexs();
}

float Strips::dashOffset() const
{
	return m_dashOffset;
}

void Strips::updateVertexs()
{
	std::vector<Vertex> vertexs;
	auto offset = m_dashOffset;
	for (auto i = 0; i != m_breaks.size() - 1; ++i)
	{
		//构建中线线段对象
		LineSegment centerLine(m_breaks[i], m_breaks[i + 1]);
		//计算厚度两边的水平|垂直差值
		glm::vec2 diff = { m_thickness * 0.5 * centerLine.yDiff() / centerLine.length(), m_thickness * 0.5 * centerLine.xDiff() / centerLine.length() };
		//构建中线两边的线段对象
		LineSegment line0(glm::vec2(centerLine.p0().x + diff.x, centerLine.p0().y - diff.y), glm::vec2(centerLine.p1().x + diff.x, centerLine.p1().y - diff.y));
		LineSegment line1(glm::vec2(centerLine.p0().x - diff.x, centerLine.p0().y + diff.y), glm::vec2(centerLine.p1().x - diff.x, centerLine.p1().y + diff.y));

		std::vector<glm::vec2> line0points;
		std::vector<glm::vec2> line1points;
		line0.dashing(offset, m_dashArray, m_thickness, line0points);
		line1.dashing(offset, m_dashArray, m_thickness, line1points);
		offset += (line0.length() / m_thickness);
		for (auto i = 0u; i <= line0points.size() - 2; i += 2)
		{
			vertexs.push_back(Vertex(glm::vec3(line0points[i], 0.0f)));
			vertexs.push_back(Vertex(glm::vec3(line0points[i + 1], 0.0f)));
			vertexs.push_back(Vertex(glm::vec3(line1points[i + 1], 0.0f)));
			vertexs.push_back(Vertex(glm::vec3(line1points[i], 0.0f)));
		}
	}
	meshes().clear();
	meshes().push_back(Mesh(vertexs, getIndices(vertexs.size())));
	
}

float Strips::nextArrayElementInLoop(uint32_t currentIndex)
{
	return m_dashArray[currentIndex + 1 > m_dashArray.size() ? 0 : currentIndex + 1];

}

std::vector<uint16_t> Strips::getIndices(int vertexCount) const
{
	std::vector<uint16_t> ret(vertexCount / 4 * 6);
	int x = 0;
	for (int i = 0; i != ret.size() / 6; ++i)
	{
		ret[x++] = (4 * i + 0);
		ret[x++] = (4 * i + 1);
		ret[x++] = (4 * i + 2);
		ret[x++] = (4 * i + 0);
		ret[x++] = (4 * i + 2);
		ret[x++] = (4 * i + 3);
	}
	return ret;
}

//////LineSegment
Strips::LineSegment::LineSegment(const glm::vec2 &p0, const glm::vec2 &p1)
	: m_p0(p0)
	, m_p1(p1)
	, m_k((p1.y - p0.y) / (p1.x - p0.x))
	, m_b(p0.y - m_k * p0.x)
{
}

const glm::vec2 &Strips::LineSegment::p0() const
{
	return m_p0;
}

const glm::vec2 &Strips::LineSegment::p1() const
{
	return m_p1;
}

float Strips::LineSegment::xDiff() const
{
	return m_p1.x - m_p0.x;
}
float Strips::LineSegment::yDiff() const
{
	return m_p1.y - m_p0.y;
}

float Strips::LineSegment::length() const
{
	return std::hypotf(xDiff(), yDiff());
}

float Strips::LineSegment::evalX(float y) const
{
	return (y - m_b) / m_k;
}

float Strips::LineSegment::evalY(float x) const
{
	return m_k * x + m_b;
}

void Strips::LineSegment::dashing(float offset, const std::vector<float> &array, float thickness, std::vector<glm::vec2> &points)
{
	//如果不做dash，则仅存入p0和p1
	if (array.empty())
	{
		points.push_back(p0());
		points.push_back(p1());
		return;
	}

	//否则
	//计算开始位置
	auto offsetTemp = 0.0f;
	bool forwardOffset = offset >= 0;
	auto iter = forwardOffset ? array.begin() : array.end() - 1;
	bool solid = forwardOffset;
	while (true)
	{
		offsetTemp = offsetTemp + (*iter * (forwardOffset ? 1 : -1));
		if ((forwardOffset && offsetTemp > offset) || (!forwardOffset && offsetTemp <= offset))
		{
			break;
		}
		else
		{
			iter = forwardOffset ? (iter == array.end() - 1 ? array.begin() : iter + 1) : (iter == array.begin() ? array.end() - 1 : iter - 1);
			solid = !solid;
		}
	}
	//std::abs(offsetTemp - offset)为第一个实心点实际元素array一个元素的偏移量
	//dashedLen为已经执行dash的长度
	auto totalLen = length();
	auto dashedLen = forwardOffset ? std::abs(offsetTemp - offset) * thickness : (*iter - (offset - offsetTemp)) * thickness;
	if (dashedLen == 0.0f)
	{
		points.push_back(p0());
	}
	else
	{
		if (solid)
			points.push_back(p0());

		auto x = xDiff() * (dashedLen <= dashedLen ? dashedLen : totalLen) / totalLen;
		auto y = yDiff() * (dashedLen <= dashedLen ? dashedLen : totalLen) / totalLen;
		points.push_back(p0() + glm::vec2(x, y));
		iter = iter == array.end() - 1 ? array.begin() : iter + 1;
	}

	//根据dashArray计算所有points
	while (true)
	{
		dashedLen = dashedLen + *iter * thickness;
		if (dashedLen <= totalLen)
		{
			//相似三角形计算x, y
			auto x = xDiff() * dashedLen / totalLen;
			auto y = yDiff() * dashedLen / totalLen;
			points.push_back(p0() + glm::vec2(x, y));
			iter = iter == array.end() - 1 ? array.begin() : iter + 1;
		}
		else
		{
			points.push_back(p0() + glm::vec2(xDiff(), yDiff()));
			break;
		}
	}

}