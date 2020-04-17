#include "newbrush/core/MetaType.h"

using namespace nb;

std::map<std::string, MetaData>	g_registeredClasses;

std::shared_ptr<Object> MetaType::makeObject(const std::string & className)
{
	auto iter = registeredClasses().find(className);
	if (iter != registeredClasses().end())
	{
		return iter->second.constructor();
	}
	return nullptr;
}

std::map<std::string, MetaData>& MetaType::registeredClasses()
{
	return g_registeredClasses;
}
