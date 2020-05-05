#pragma once
#include "StudioPlugin.h"

namespace nb {

class NB_API BuildinStudioPlugin : public StudioPlugin
{
public:
	virtual void getMetametaObjectsOverride(std::vector<std::shared_ptr<MetaObject>> &metaObjects) override;
};

}