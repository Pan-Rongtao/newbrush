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
	static const DependencyProperty &registerDependency(const std::string & name, std::type_index propertyType, std::type_index ownerType);
	static const DependencyProperty &registerDependency(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata);
	static const DependencyProperty &registerDependency(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback);

private:
	DependencyProperty(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback);
	static const DependencyProperty &registerCommon(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback);
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