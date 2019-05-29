/*******************************************************
**	Application
**
**	app类
**		Application提供GL的初始化，包括Display和Configure等
**	当app运行后，主循环将对所有的渲染物进行渲染
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "../core/Def.h"

namespace nb{ namespace gl{

class Display;
class Configure;
class NB_API Application
{
public:
	//构建一个Application对象
	//display：显示对象，如果不指定将使用默认的display
	//configure：配置对象，如果不指定将使用默认的configure
	//异常：多次构建
	Application(std::shared_ptr<Display> display = nullptr, std::shared_ptr<Configure> configure = nullptr);
	virtual ~Application() = default;

	//运行
	int run();

protected:
	//渲染前
	virtual void preRender()	{}

	//渲染后
	virtual void postRender()	{}

private:
	void render();
};

}}
