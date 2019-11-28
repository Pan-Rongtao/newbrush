#pragma once
#include <string>
#include "Context.h"
#include "Camera.h"
#include "Projection.h"

namespace nb{ namespace gl
{
	//设置摄像机
	NB_API void setCamera(std::shared_ptr<Camera> camera);

	//获取摄像机
	NB_API std::shared_ptr<Camera> getCamera();

	//设置投影
	NB_API void setProjection(std::shared_ptr<Projection> projection);

	//获取投影
	NB_API std::shared_ptr<Projection> getProjection();
		
	//设置视口大小
	NB_API void viewport(int x, int y, unsigned int width, unsigned height);

}}
