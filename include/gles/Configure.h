#pragma once
#include "../core/Def.h"
#include "Display.h"

namespace nb{ namespace gl{

class NB_API Configure
{
public:
	Configure(std::shared_ptr<Display> display, int *attributes);

	bool isNull() const;

	int *attributes() const;

	void *handle() const;

public:
	//系统推荐的配置最大数
	static int systemRecommendMaxSupportCount(std::shared_ptr<Display> display);

	//从系统推荐中构建
	static Configure fromSystemRecommend(std::shared_ptr<Display> display, int index);

private:
	Configure();
	void						*m_handle;
	std::shared_ptr<Display>	m_display;
};

}}
