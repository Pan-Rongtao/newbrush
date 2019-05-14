#pragma once
#include <string>
#include "Display.h"
#include "Configure.h"
#include "Surface.h"
#include "Context.h"

namespace nb{ namespace gl
{
	//获取Egl版本
	NB_API std::string getVersion();

	//获取
	NB_API std::string getVendor(); 

	//初始化
	NB_API void initialize(const Display &display);

	//获取当前显示设备
	NB_API const Display &getCurrentDisplay();

	//设置egl配置
	NB_API void setConfigure(const Configure &configure);

	//获取egl设置
	NB_API const Configure &getCurrentConfigure();

	//设置当前渲染surface和context
	NB_API void makeCurrent(std::shared_ptr<Surface> onScreen, std::shared_ptr<Surface> offScreen, std::shared_ptr<Context> context);
	
	//
	NB_API void swapBuffers(const Surface *surface);

	//设置视口大小
	NB_API void Viewport(int x, int y, unsigned int width, unsigned height);

}}
