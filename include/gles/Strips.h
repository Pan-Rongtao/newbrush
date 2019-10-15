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
	void updateVertexs();
	float nextArrayElementInLoop(uint32_t nCurrentIndex);

	float					m_thickness;
	float					m_dashOffset;
	std::vector<float>		m_dashArray;
	std::vector<glm::vec2>	m_breaks;
};

}}