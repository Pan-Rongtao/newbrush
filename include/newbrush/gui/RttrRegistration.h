#pragma once
#include "newbrush/core/Def.h"

namespace nb {

//请勿修改枚举值的顺序和定向指定值
enum class RttrMetadataIndex : int8_t
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

class Range;
class ClassDescriptor;
class PropertyDescriptor;
class DependencyProperty;
using RangePtr = std::shared_ptr<Range>;
using ClassDescriptorPtr = std::shared_ptr<ClassDescriptor>;
using PropertyDescriptorPtr = std::shared_ptr<PropertyDescriptor>;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;

class NB_API ClassDescriptor
{
public:
	ClassDescriptor(const std::string &category, const std::string &dispayName, const std::string &description);

	const std::string &category() const;
	const std::string &displayName() const;
	const std::string &description() const;

private:
	std::string m_category;
	std::string m_displayName;
	std::string m_description;
};

class NB_API Range
{
public:
	Range(var lowerBound, var upperBound, var step);

	var lowerBound() const;
	var upperBound() const;
	var step() const;

private:
	var m_lowerBound;
	var m_upperBound;
	var m_step;
};

class NB_API PropertyCategory
{
public:
	const std::string &name() const;
	int order() const;

	static const PropertyCategory &get(const std::string &name, int order);

	static const PropertyCategory &brush();
	static const PropertyCategory &appearance();
	static const PropertyCategory &common();
	static const PropertyCategory &automation();
	static const PropertyCategory &layout();
	static const PropertyCategory &text();
	static const PropertyCategory &transform();
	static const PropertyCategory &misc();
	static const PropertyCategory &custom();

	static const std::map<std::string, PropertyCategory> &getAll();

private:
	std::string m_name;
	int			m_order;
	static std::map<std::string, PropertyCategory> s_propertyCategorys;
};

class NB_API PropertyDescriptor
{
public:
	PropertyDescriptor(DependencyPropertyPtr dp, const PropertyCategory &category, const std::string &description, int order, RangePtr range);

	const DependencyPropertyPtr &property() const;
	const PropertyCategory &category() const;
	const std::string &description() const;
	int order() const;
	const RangePtr &range() const;

private:
	DependencyPropertyPtr m_property;
	PropertyCategory m_category;
	std::string m_description;
	int m_order;
	RangePtr m_range;
};

class NB_API RttrRegistration
{
public:
	//执行注册
	static void doRegister();

	//获取类型的自身属性（不包括继承的属性）
	static std::vector<PropertyDescriptorPtr> getTypeSelfPropertys(rttr::type t);

	//获取类型的所有属性（包括继承的属性）
	static std::vector<PropertyDescriptorPtr> getTypeAllPropertys(rttr::type ownerType);

private:
	static void registerEnums();
	static void registerUIElementTypes();
	static void registerConverters();
};

NB_API rttr::detail::metadata ClassDescriptorMetadata(const std::string &category, const std::string &dispayName, const std::string &description);
NB_API rttr::detail::metadata PropertyDescriptorMetadata(RttrMetadataIndex index, DependencyPropertyPtr dp, const PropertyCategory &category, const std::string &description, int order, RangePtr range = nullptr);


}