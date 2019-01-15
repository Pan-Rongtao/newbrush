#pragma once
#include "../core/Def.h"

namespace nb{ namespace gl{

class NB_API Application
{
public:
	//构建一个Application对象
	//异常：多次构建
	Application();
	virtual ~Application();

	//运行
	int run();

protected:
	//初始化
	virtual void InitializeOverride();

	//渲染前
	virtual void PreRenderOverride();

	//渲染后
	virtual void PostRenderOverride();

	//空闲
	virtual void IdledOverride();


private:
	void initialize();
	void render();
};

}}
