#pragma once
#include <vector>
#include "Model.h"

namespace nb{ namespace gl{

class NB_API Polyline : public Model
{
public:
	Polyline();

	Polyline(const std::vector<glm::vec2> &points);

};

}}