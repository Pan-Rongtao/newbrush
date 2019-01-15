#pragma once
#include "../core/Def.h"

namespace nb{ namespace gl{

class NB_API Configure
{
public:
	Configure();
	Configure(int *attributes);

	bool isNull() const;

	int *attributes() const;

	void *handle() const;

public:
	//系统推荐的配置最大数s
	static int systemRecommendMaxSupportCount();

	//从系统推荐中构建
	static Configure fromSystemRecommend(int index);

private:
	void		*m_handle;
};

}}
