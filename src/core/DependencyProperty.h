#pragma once
#include <string>
#include <map>
#include <typeindex>
#include "../core/Any.h"
#include "../core/PropertyMetadata.h"

namespace nb{

class DependencyObject;
using ValidateValueCallback = std::function<bool(const Any &value)>;
class NB_API DependencyProperty final
{
public:
	//名字
	std::string name() const;

	//哈希值，唯一
	size_t hash() const;

	//是否可改写
	bool isSealed() const;

	//默认值
	Any &defaultValue();
	const Any &defaultValue() const;

	bool operator == (const DependencyProperty &other) const;
	bool operator != (const DependencyProperty &other) const;
	
	//注册一个依赖属性，如果此属性已存在，则只修改属性值
	//element：目标元素
	//property_name：属性名
	//property_v：属性值
	static void registerAttached(std::shared_ptr<DependencyObject> element, const std::string &property_name, const Any &property_v);

	
	//查询依赖属性值，如果查询不到，将返回一个空的Any
	//element：目标元素
	//property_name：属性名
	static Any findAttached(std::shared_ptr<DependencyObject> element, const std::string &property_name);

	//注册依赖属性
	//name：属性名
	static const DependencyProperty &registerDependency(const std::string & name, std::type_index propertyType, std::type_index ownerType)
	{
		registerDependency(name, propertyType, ownerType, nullptr, nullptr);
	}

	//注册依赖属性
	//name：属性名
	static const DependencyProperty &registerDependency(const std::string & name, std::shared_ptr<PropertyMetadata> metadata)
	{
		registerDependency(name, metadata, nullptr);
	}
	
	//注册依赖属性
	//name：属性名
	//propertyType：属性值类型
	//ownerType：属性宿主类型
	//异常：std::logic_error已经注册过同类型属性
	static const DependencyProperty &registerDependency(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback)
	{
		static std::map<std::size_t, DependencyProperty> g_dependencyProperties;

		std::hash<std::string> _shash;
		auto hash = typeid(ownerType).hash_code() ^ _shash(name);
		if (g_dependencyProperties.find(hash) != g_dependencyProperties.end())
		{
			nbThrowException(std::logic_error, "[%s] has already been registered for [%s]", name.data(), typeid(ownerType).name());
		}

		DependencyProperty dp;
		dp.m_name = name;
		dp.m_hash = hash;
		dp.m_isSealed = isSealed;
		dp.m_defaultV = defaultValue;
		g_dependencyProperties[hash] = dp;
		return g_dependencyProperties[hash];
	}

private:
	std::string							m_name;
	std::type_index						m_ownerType;
	std::type_index						m_propertyType;
	std::shared_ptr<PropertyMetadata>	m_metadata;
	size_t								m_hash{0};
	ValidateValueCallback				m_validateValueCallback;

	static std::map<std::shared_ptr<DependencyObject>, std::map<std::string, Any>>	m_attProperties;
};

}