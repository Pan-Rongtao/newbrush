#pragma once
#include <map>
#include <string>
#include <typeindex>
#include <functional>
#include "newbrush/core/Def.h"
#include "newbrush/core/Object.h"

namespace nb {

class NB_API MetaData
{
public:
	std::type_index								type;
	std::function<std::shared_ptr<Object>()>	constructor;
};

#define NB_STATIC_MOUDULE(classType) \
public:\
	static std::shared_ptr<classType> create()\
	{\
		return std::make_shared<classType>();\
	}\
	static MetaData getMetaData()\
	{\
		MetaData md { typeid(classType), classType::create };\
		return md;\
	}

class NB_API MetaType
{
public:
	template<class T>
	static void registerClass()
	{
		static_assert(std::is_base_of<Object, T>::value, "[T] must be [Object] type or it's derived type.");
		if (registeredClasses().size() >= std::numeric_limits<size_t>::max())
		{
			nbThrowException(std::out_of_range, "registered classes count has overflow[%d]", registeredClasses().size());
		}

		MetaData md{ typeid(T), T::create };
		auto p = registeredClasses().insert({ nb::getFullName(typeid(T)), md });
		if (!p.second)
		{
			nbThrowException(std::logic_error, "[%s] has already been registered.", typeid(T).name());
		}
	}

	static std::shared_ptr<Object> makeObject(const std::string &className);
	
private:
	static std::map<std::string, MetaData>	&registeredClasses();
};


}
