#pragma once
#include "newbrush/core/MetaType.h"

namespace nb {

class StudioPlugin
{
public:
	virtual std::vector<MetaData> getMetaClassesOverride() = 0;

};

struct CInfo
{
	char	type[64];
	char	defaultName[64];
	char	description[256];
};


#define NB_PLUGIN_ENTRY_FOR_STUDIO(pluginClass) \
\
extern "C" NB_API int getMetaClassesCount()\
{\
	pluginClass p;\
	return p.getMetaClassesOverride().size();\
}\
\
extern "C" NB_API void getMetaClasses(CInfo *infos, int count)\
{\
	pluginClass p;\
	std::vector<MetaData> metas = p.getMetaClassesOverride();\
	for (size_t i = 0; i < (size_t)count && i < metas.size(); ++i)\
	{\
		auto m = metas[i];\
		strcpy(infos[i].type, nb::getFullName(m.type).data());\
		strcpy(infos[i].defaultName, nb::getClassName(m.type).data());\
		strcpy(infos[i].description, "this is xxx");\
	}\
}\

}