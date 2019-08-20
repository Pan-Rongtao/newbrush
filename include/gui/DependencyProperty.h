#pragma once
#include <string>
#include <map>
#include "../core/Def.h"
#include "../core/Any.h"

namespace nb{ namespace gui{

class UIElement;
class DependencyObject;
class NB_API DependencyProperty
{
public:
	//注册一个依赖属性，如果此属性已存在，则只修改属性值
	//element：目标元素
	//property_name：属性名
	//property_v：属性值
	static void registerAttached(std::shared_ptr<UIElement> element, const std::string &property_name, const core::Any &property_v);

	
	//查询依赖属性值，如果查询不到，将返回一个空的Any
	//element：目标元素
	//property_name：属性名
	static core::Any findAttached(std::shared_ptr<UIElement> element, const std::string &property_name);

	//注册依赖属性
	//异常：std::logic_error已经注册过同类型属性
	template<class ownerType, class propertyType>
	static DependencyProperty registerDependency(const std::string & name, const propertyType &defaultValue = propertyType())
	{
		static std::map<std::size_t, DependencyProperty> g_dependencyProperties;
		static_assert(std::is_base_of<DependencyObject, ownerType>::value, "registerDependency<ownerType, propertyType> : ownerType must be DependencyObject or it's derived type.");

		auto h0 = typeid(ownerType).hash_code();
		std::hash<std::string> shash;
		auto h1 = shash(name);
		auto hs = h0 ^ h1;
		if (g_dependencyProperties.find(hs) != g_dependencyProperties.end())
			nbThrowException(std::logic_error, "[%s] has already been registered for [%s]", name.data(), typeid(ownerType).name());

		DependencyProperty dp;
		dp.m_name = name;
		dp.m_hash = hs;
		dp.m_defaultV = defaultValue;
		g_dependencyProperties[hs] = dp;
		return dp;
	}

	//名字
	std::string name() const;

	//哈希值，唯一
	size_t hash() const;

	//是否可改写
	bool isSealed() const;

	//默认值
	core::Any defaultValue() const;

	bool operator == (const DependencyProperty &other) const;

private:
	std::string	m_name;
	size_t		m_hash{0};
	bool		m_isSealed{ true };
	core::Any	m_defaultV;

	static std::map<std::shared_ptr<UIElement>, std::map<std::string, core::Any>>	m_attProperties;
};

}
}