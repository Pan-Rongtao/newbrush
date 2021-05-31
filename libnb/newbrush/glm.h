#pragma once
//要使GLM_FORCE_XYZW_ONLY生效，不能include单独的glm/glm.hpp或者其他glm头文件，只能include此文件
#ifndef GLM_FORCE_XYZW_ONLY
#define GLM_FORCE_XYZW_ONLY
#endif
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/matrix_query.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/random.hpp"
