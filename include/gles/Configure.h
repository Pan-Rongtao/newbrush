#pragma once
#include "core/NewBrushDef.h"

namespace nb{ namespace gl{ namespace egl{

class NB_EXPORT Configure
{
public:
	Configure();
	Configure(int *attributes);

	bool IsNull() const;

	int *GetAttributes() const;

	void *GetEGLHandle() const;

public:
	//系统推荐的配置最大数
	static int SystemRecommendMaxSupportCount();

	//从系统推荐中构建
	static Configure FromSystemRecommend(int index);

private:
	Configure(void *eglHandle);

	void		*m_Handle;
};

}}}
