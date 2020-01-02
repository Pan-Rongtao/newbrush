#pragma once
#include <functional>
#include <string>
#include <map>
#include <typeindex>
#include "../core/Any.h"

namespace nb{

class DependencyObject;
class PropertyMetadata;
using ValidateValueCallback = std::function<bool(const Any &value)>;
class NB_API DependencyProperty final
{
public:
	//属性名字
	const std::string &name() const;

	//宿主类型
	std::type_index ownerType() const;

	//宿主类型
	std::type_index propertyType() const;

	//元数据
	std::shared_ptr<PropertyMetadata> defaultMetadata() const;

	//是否可改写
	bool readOnly() const;

	//唯一标识值
	size_t globalIndex() const;

	//检验回调
	ValidateValueCallback validateValueCallback() const;

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
	//propertyType：属性值类型
	//ownerType：属性宿主类型
	//异常：std::logic_error已经注册过同类型属性
	template<class ownerType, class propertyType>
	static DependencyProperty registerDependency(const std::string & name, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback)
	{
		static_assert(std::is_base_of<DependencyObject, ownerType>::value, "registerDependency<ownerType, propertyType> : ownerType must be DependencyObject or a derived type.");

		std::hash<std::string> _shash;
		auto hash = typeid(ownerType).hash_code() ^ _shash(name);
		if (g_dependencyProperties.find(hash) != g_dependencyProperties.end())
			nbThrowException(std::logic_error, "[%s] has already been registered for [%s]", name.data(), typeid(ownerType).name());

		DependencyProperty dp(name, propertyType, ownerType, metadata, validateValueCallback);
		dp.m_hash = hash;
		g_dependencyProperties.insert({ hash, dp });
		return dp;
	}


	static Any unsetValue();

private:
	DependencyProperty(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback);
	static DependencyProperty registerCommon(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback);
	static std::shared_ptr<PropertyMetadata> autoGeneratePropertyMetadata(std::type_index propertyType, ValidateValueCallback validateValueCallback, const std::string &name, std::type_index ownerType);

	std::string							m_name;
	std::type_index						m_propertyType;
	std::type_index						m_ownerType;
	std::shared_ptr<PropertyMetadata>	m_metadata;
	ValidateValueCallback				m_validateValueCallback;
	size_t								m_hash;

	static std::map<std::size_t, DependencyProperty> g_dependencyProperties;
	static std::map<std::shared_ptr<DependencyObject>, std::map<std::string, Any>>	m_attProperties;
};

}