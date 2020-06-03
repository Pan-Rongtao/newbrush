#pragma once
#include "newbrush/core/MetaObject.h"

namespace nb {

class StudioPlugin
{
public:
	virtual void getMetametaObjectsOverride(std::vector<std::shared_ptr<MetaObject>> &metaObjects) = 0;

};

struct CPropertyInfo
{
	uint64_t	typeID = 0;			//属性ID（唯一）
	char	valueTypeName[128] = {};//值类型
	char	category[64] = {};		//分类
	char	displayName[64] = {};	//显示名
	char	description[256] = {};	//描述
	char	enumSource[512] = {};	//枚举值字符串组合（如果是枚举类型），形如 "Enum0|Enum1|Enum2"，以'|'作为分隔符
};

struct CClassInfo
{
	char	typeName[64] = {};
	char	category[64] = {};
	char	displayName[64] = {};
	char	description[256] = {};
	CPropertyInfo propertys[100] = {};
};

#define NB_PLUGIN_ENTRY_FOR_STUDIO(pluginClass) \
\
extern "C" NB_API int getMetaClassesCount()\
{\
	pluginClass plugin;\
	std::vector<std::shared_ptr<MetaObject>> metaObjects;\
	plugin.getMetametaObjectsOverride(metaObjects);\
	return metaObjects.size();\
}\
\
extern "C" NB_API void getMetaClasses(CClassInfo *infos, int count)\
{\
	pluginClass plugin;\
	std::vector<std::shared_ptr<MetaObject>> metaObjects;\
	plugin.getMetametaObjectsOverride(metaObjects);\
	for (size_t i = 0; i < (size_t)count && i < metaObjects.size(); ++i)\
	{\
		auto obj = metaObjects[i];\
		auto classDsp = obj->classDescriptor();\
		strcpy(infos[i].typeName, nb::getFullName(classDsp.type).data());\
		strcpy(infos[i].displayName, classDsp.displayName.data());\
		strcpy(infos[i].description, classDsp.description.data());\
	}\
}\

}