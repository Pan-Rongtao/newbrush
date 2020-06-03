#pragma once
#include "newbrush/core/Def.h"

namespace nb {

class StudioPlugin
{
public:
	virtual void getMetametaObjectsOverride() = 0;

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

}