#pragma once
#include <vector>
#include "newbrush/gles/Model.h"
#include "newbrush/media/Media.h"

namespace nb{

class NB_API Strips : public Model
{
public:
	//构建一个空的带状
	Strips();

	//
	void update(const std::vector<glm::vec2> &breaks, float thickness, const std::vector<float> &dashArray, float offset, PenLineJoinE lineJionStyle);

private:
	//线段类 y = kx + b
	class LineSegment
	{
	public:
		LineSegment(const glm::vec2 &p0, const glm::vec2 &p1);
		
		//水平和垂直方向的距离值，可能为负数
		//线段长度
		float xDiff() const;
		float yDiff() const;
		float length() const;

		//执行虚线计算
		void dashing(float offset, const std::vector<float> &array, float thickness, std::vector<glm::vec2> &points, const glm::vec4 &box, std::vector<glm::vec2> &texCoords, bool innerLine);

		glm::vec2	p0;
		glm::vec2	p1;
	};

};

}