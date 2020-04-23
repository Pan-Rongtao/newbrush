#pragma once
#include "StudioPlugin.h"

namespace nb {

class BuildinStudioPlugin : public StudioPlugin
{
public:
	virtual std::vector<MetaData> getMetaClassesOverride() override;
};

}