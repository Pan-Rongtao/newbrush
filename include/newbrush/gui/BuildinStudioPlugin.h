#pragma once
#include "StudioPlugin.h"

namespace nb {

class NB_API BuildinStudioPlugin : public StudioPlugin
{
public:
	virtual void getMetametaObjectsOverride() override;
};

extern "C" NB_API int getCategoryOrderCount();
extern "C" NB_API void getCategoryOrders(CCategoryOrder *categorys, int count);
extern "C" NB_API int getMetaClassCount();
extern "C" NB_API void getMetaClasses(CClass *classes, int count);
}