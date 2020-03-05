#include "newbrush/gles/Strips.h"
#include <numeric>
#include <GLES2/gl2.h>

using namespace nb;

Strips::Strips()
	: Model(std::vector<Mesh>{ Mesh() })
{
}

void Strips::update(const std::vector<glm::vec2>& breaks, float thickness, const std::vector<float>& dashArray, float offset, PenLineJoinE lineJionStyle)
{
	if (breaks.empty())
		return;

	std::vector<Vertex> vertexs;
	//计算外接矩形
	std::vector<glm::vec2> outBreaks;	//外接点集合
	for (size_t i = 0; i < breaks.size() - 1; ++i)
	{
		LineSegment centerLine(breaks[i], breaks[i + 1]);
		glm::vec2 diff = { thickness * 0.5 * centerLine.yDiff() / centerLine.length(), thickness * 0.5 * centerLine.xDiff() / centerLine.length() };
		auto p0 = glm::vec2(centerLine.p0.x + diff.x, centerLine.p0.y - diff.y);
		outBreaks.push_back(p0);
		if (i == breaks.size() - 2)
		{
			auto p1 = glm::vec2(centerLine.p1.x + diff.x, centerLine.p1.y - diff.y);
			outBreaks.push_back(p1);
		}
	}
	auto xMinMax = std::minmax_element(outBreaks.begin(), outBreaks.end(), [](const glm::vec2 &p0, const glm::vec2 &p1) { return p1.x > p0.x; });
	auto yMinMax = std::minmax_element(outBreaks.begin(), outBreaks.end(), [](const glm::vec2 &p0, const glm::vec2 &p1) { return p1.y > p0.y; });
	glm::vec4 box = { xMinMax.first->x, yMinMax.first->y, xMinMax.second->x, yMinMax.second->y };	//（x, y, r, b)

	for (size_t i = 0; i < breaks.size() - 1; ++i)
	{
		//构建中线线段对象
		LineSegment centerLine(breaks[i], breaks[i + 1]);
		//计算厚度两边的水平|垂直差值
		glm::vec2 diff = { thickness * 0.5 * centerLine.yDiff() / centerLine.length(), thickness * 0.5 * centerLine.xDiff() / centerLine.length() };
		//构建中线两边的线段对象
		LineSegment line0(glm::vec2(centerLine.p0.x + diff.x, centerLine.p0.y - diff.y), glm::vec2(centerLine.p1.x + diff.x, centerLine.p1.y - diff.y));
		LineSegment line1(glm::vec2(centerLine.p0.x - diff.x, centerLine.p0.y + diff.y), glm::vec2(centerLine.p1.x - diff.x, centerLine.p1.y + diff.y));

		std::vector<glm::vec2> line0points;
		std::vector<glm::vec2> line0texcoords;
		std::vector<glm::vec2> line1points;
		std::vector<glm::vec2> line1texcoords;
		line0.dashing(offset, dashArray, thickness, line0points, box, line0texcoords, false);
		line1.dashing(offset, dashArray, thickness, line1points, box, line1texcoords, true);
		offset += (line0.length() / thickness);
		for (auto i = 0u; i <= line0points.size() - 2; i += 2)
		{
			vertexs.push_back(Vertex(glm::vec3(line0points[i], 0.0f), glm::vec4(1.0f), line0texcoords[i], glm::vec3()));
			vertexs.push_back(Vertex(glm::vec3(line0points[i + 1], 0.0f), glm::vec4(1.0f), line0texcoords[i + 1], glm::vec3()));
			vertexs.push_back(Vertex(glm::vec3(line1points[i + 1], 0.0f), glm::vec4(1.0f), line1texcoords[i + 1], glm::vec3()));
			vertexs.push_back(Vertex(glm::vec3(line1points[i], 0.0f), glm::vec4(1.0f), line1texcoords[i], glm::vec3()));
		}
	}
	meshes[0].vertexs = vertexs;
	auto getIndices = [](size_t vertexCount)->std::vector<uint16_t> 
	{
		std::vector<uint16_t> ret(vertexCount / 4 * 6);
		int x = 0;
		for (int i = 0; i != ret.size() / 6; ++i)
		{
			ret[x++] = (4 * i + 0);		ret[x++] = (4 * i + 1);		ret[x++] = (4 * i + 2);
			ret[x++] = (4 * i + 0);		ret[x++] = (4 * i + 2);		ret[x++] = (4 * i + 3);
		}
		return ret;
	};
	meshes[0].indices = getIndices(vertexs.size());
}

//////LineSegment
Strips::LineSegment::LineSegment(const glm::vec2 &p0, const glm::vec2 &p1)
	: p0(p0)
	, p1(p1)
{
}

float Strips::LineSegment::xDiff() const
{
	return p1.x - p0.x;
}
float Strips::LineSegment::yDiff() const
{
	return p1.y - p0.y;
}

float Strips::LineSegment::length() const
{
	return std::hypotf(xDiff(), yDiff());
}

void Strips::LineSegment::dashing(float offset, const std::vector<float> &array, float thickness, std::vector<glm::vec2> &points, 
	const glm::vec4 &box, std::vector<glm::vec2> &texCoords, bool innerLine)
{
	auto box_x = box.x;
	auto box_y = box.x;
	auto box_w = std::fabs(box.z - box.x);
	auto box_h = std::fabs(box.w - box.y);
	auto calcTexCoor = [&box_x, &box_y, &box_w, &box_h](const glm::vec2 &p)->glm::vec2 {
		return glm::vec2{ (p.x - box_x) / box_w, 1 - (p.y - box_y) / box_h };
	};
	//如果不做dash，则仅存入p0和p1
	if (array.empty())
	{
		points.push_back(p0);
		points.push_back(p1);
		texCoords.push_back(calcTexCoor(p0));
		texCoords.push_back(calcTexCoor(p1));
		return;
	}

	//否则
	//计算开始位置
	auto offsetTemp = 0.0f;
	offset = std::fmod(offset, std::accumulate(array.begin(), array.end(), 0.0f) * 2);
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
		points.push_back(p0);
		texCoords.push_back(glm::vec2{ (p0.x - box_x) / box_w, 1 - (p0.y - box_y) / box_h });
	}
	else
	{
		if (solid)
		{
			points.push_back(p0);
			texCoords.push_back(calcTexCoor(p0));
		}

		auto x = xDiff() * (dashedLen <= dashedLen ? dashedLen : totalLen) / totalLen;
		auto y = yDiff() * (dashedLen <= dashedLen ? dashedLen : totalLen) / totalLen;
		auto p = p0 + glm::vec2(x, y);
		points.push_back(p);
		texCoords.push_back(calcTexCoor(p));
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
			auto p = p0 + glm::vec2(x, y);
			points.push_back(p);
			texCoords.push_back(calcTexCoor(p));
			iter = iter == array.end() - 1 ? array.begin() : iter + 1;
		}
		else
		{
			auto p = p0 + glm::vec2(xDiff(), yDiff());
			points.push_back(p);
			texCoords.push_back(calcTexCoor(p));
			break;
		}
	}

}