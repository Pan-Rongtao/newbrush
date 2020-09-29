#pragma once
#include "newbrush/model/Def.h"
#include "newbrush/model/Object.h"

namespace nb {

//请勿修改枚举值的顺序和定向指定值
enum class RttrMetadataIndex
{
	ClassDescriptor = 0,
	Property0,
	Property1,
	Property2,
	Property3,
	Property4,
	Property5,
	Property6,
	Property7,
	Property8,
	Property9,
	Property10,
	Property11,
	Property12,
	Property13,
	Property14,
	Property15,
	Property16,
	Property17,
	Property18,
	Property19,
	Property20,
	Property21,
	Property22,
	Property23,
	Property24,
	Property25,
	Property26,
	Property27,
	Property28,
	Property29,
	Property30,
	Property31,
	Property32,
	Property33,
	Property34,
	Property35,
	Property36,
	Property37,
	Property38,
	Property39,
	Property40,
	Property41,
	Property42,
	Property43,
	Property44,
	Property45,
	Property46,
	Property47,
	Property48,
	PropertyMax,

};

class NB_API ClassDescriptor
{
public:
	std::string category;
	std::string displayName;
	std::string description;

private:
	ClassDescriptor(const std::string &_category, const std::string &_dispayName, const std::string &_description)
		: category(_category)
		, displayName(_dispayName)
		, description(_description)
	{}
	friend detail::metadata ClassDescriptorMetadata(const std::string &category, const std::string &dispayName, const std::string &description);
};
detail::metadata ClassDescriptorMetadata(const std::string &category, const std::string &dispayName, const std::string &description);

class NB_API RttrRegistration
{
public:
	//执行注册
	static void doRegister();

private:
	static void registerEnums();
	static void registerTypes();
	static void registerConverters();
};

}