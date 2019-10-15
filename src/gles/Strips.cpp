#include "gles/Strips.h"
#include <GLES2/gl2.h>

using namespace nb::gl;

Strips::Strips()
	: Strips({}, 1.0)
{
}

Strips::Strips(const std::vector<glm::vec2>& breaks)
	: Strips(breaks, 1.0)
{
}

Strips::Strips(const std::vector<glm::vec2>& breaks, float thickness)
	: m_thickness(thickness)
	, m_dashOffset(0)
	, m_breaks(breaks)
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
	//获取中线上任意偏移位置的x,y坐标：p0为起点坐标，p1位终点坐标，offset为距起点的沿终点的长度
	//k为线的斜率
	auto getXYOnLine = [&](const glm::vec2 &p0, const glm::vec2 &p1, float offset) {
		float k = (p1.y - p0.y) / (p1.x - p0.x);
		
		//x^2 + (kx)^2 = offset^2
		glm::vec2 ret;
	};
	for (auto i = 0; i != m_breaks.size() - 1; ++i)
	{
		glm::vec2 stripBeg = m_breaks[i];
		glm::vec2 stripEnd = m_breaks[i + 1];
		auto xDiff = stripEnd.x - stripBeg.x;
		auto yDiff = stripEnd.y - stripBeg.y;
		auto stripLen = std::hypotf(xDiff, yDiff);	//一条带的长度
		//利用相似三角形计算一条带实际的四个点位置
		glm::vec2 p0 = { stripBeg.x + (m_thickness * 0.5) * (yDiff / stripLen), stripBeg.y - (m_thickness * 0.5) * (xDiff / stripLen) };
		glm::vec2 p1 = { stripEnd.x + (m_thickness * 0.5) * (yDiff / stripLen), stripEnd.y - (m_thickness * 0.5) * (xDiff / stripLen) };
		glm::vec2 p2 = { stripEnd.x - (m_thickness * 0.5) * (yDiff / stripLen), stripEnd.y + (m_thickness * 0.5) * (xDiff / stripLen) };
		glm::vec2 p3 = { stripBeg.x - (m_thickness * 0.5) * (yDiff / stripLen), stripBeg.y + (m_thickness * 0.5) * (xDiff / stripLen) };
		
//		glm::vec4 stripArea = { p0, p1, p2, p3 };
		std::vector<Vertex> vertexs{ Vertex(glm::vec3(m_breaks[i], 0)) };
		meshes().push_back(Mesh(vertexs, {0, 1, 2, 0, 2, 3}));
	}
}

float Strips::nextArrayElementInLoop(uint32_t currentIndex)
{
	return m_dashArray[currentIndex + 1 > m_dashArray.size() ? 0 : currentIndex + 1];

}
