#pragma once
#include "Model.h"

namespace nb{ namespace gl{

class NB_API Line : public Model
{
public:
	Line();

	Line(float x0, float y0, float x1, float y1);

};

}}