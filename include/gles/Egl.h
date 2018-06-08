#pragma once
#include "system/String.h"
#include "gles/Display.h"
#include "gles/Configure.h"
#include "gles/Surface.h"
#include "gles/Context.h"

namespace nb{ namespace gl{ namespace egl
{
	//获取Egl版本
	NB_EXPORT nb::System::String GetVersion();

	//获取
	NB_EXPORT nb::System::String GetVendor(); 

	//初始化
	NB_EXPORT void Initialize(const Display &display);

	//获取当前显示设备
	NB_EXPORT const Display &GetCurrentDisplay();

	//设置egl配置
	NB_EXPORT void SetConfigure(const Configure &configure);

	//获取egl设置
	NB_EXPORT const Configure &GetCurrentConfigure();

	//设置当前渲染surface和context
	NB_EXPORT void MakeCurrent(const Surface *onScreen, const Surface *offScreen, const Context *context);
	
	//
	NB_EXPORT void SwapBuffers(const Surface *surface);
}}}
