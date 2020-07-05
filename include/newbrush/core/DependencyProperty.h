#pragma once
#include <functional>
#include <string>
#include <map>
#include <typeindex>
#include "newbrush/core/Def.h"

namespace nb{

class DependencyObject;
using DependencyObjectPtr = std::shared_ptr<DependencyObject>;
class PropertyMetadata;
using PropertyMetadataPtr = std::shared_ptr<PropertyMetadata>;
class DependencyProperty;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;
struct DependencyPropertyChangedEventArgs;
using PropertyChangedCallback = std::function<void(DependencyObject *, DependencyPropertyChangedEventArgs *)>;
using CoerceValueCallback = std::function<var(DependencyObject *, var)>;
using ValidateValueCallback = std::function<bool(const var &value)>;

class NB_API PropertyMetadata
{
public:
	//构建一个PropertyMetadata
	//defaulValue：默认值
	//propertyChangedCallback：属性已改变回调
	//coerceValueCallback：属性值矫正回调
	PropertyMetadata(const var &defaultValue, PropertyChangedCallback propertyChangedCallback = nullptr, CoerceValueCallback coerceValueCallback = nullptr);

	void setDefaultValue(const var &value) &;
	var defaultValue() const;

	bool isSealed() const;

	PropertyChangedCallback propertyChangedCallback();
	CoerceValueCallback coerceValueCallback();
	
private:
	var						m_defaultValue;
	PropertyChangedCallback	m_propertyChangedCallback;
	CoerceValueCallback		m_coerceValueCallback;
};

class NB_API DependencyProperty final
{
public:
	//属性名字
	const std::string &name() const;

	//宿主类型
	rttr::type ownerType() const;

	//宿主类型
	rttr::type propertyType() const;

	//元数据
	PropertyMetadataPtr defaultMetadata() const;

	//是否可改写
	bool readOnly() const;

	//唯一标识值
	size_t globalIndex() const;

	//检验回调
	ValidateValueCallback validateValueCallback() const;

	bool operator == (const DependencyProperty &other) const;
	bool operator != (const DependencyProperty &other) const;

	//注册依赖属性
	//name：属性名
	//propertyType：属性值类型
	//ownerType：属性宿主类型
	//异常：std::invalid_argument [name]参数为空
	//异常：std::logic_error已经注册过同类型属性
	template<class OwnerType, class PropertyType>
	static DependencyPropertyPtr registerDependency(const std::string &name, const PropertyType &defaultValue, PropertyChangedCallback propertyChangedCallback = nullptr,
		CoerceValueCallback coerceValueCallback = nullptr, ValidateValueCallback validateValueCallback = nullptr)
	{
		static_assert(std::is_base_of<DependencyObject, OwnerType>::value, "[ownerType] must be DependencyObject type or DependencyObject derived type.");
		auto metadata = std::make_shared<PropertyMetadata>(defaultValue, propertyChangedCallback, coerceValueCallback);
		return registerCommon(name, rttr::type::get<OwnerType>(), rttr::type::get<PropertyType>(), metadata, validateValueCallback);
	}

	//注册附加属性
	template<class OwnerType, class PropertyType>
	static DependencyPropertyPtr registerAttached(const std::string &name, const PropertyType &defaultValue, PropertyChangedCallback propertyChangedCallback = nullptr,
		CoerceValueCallback coerceValueCallback = nullptr, ValidateValueCallback validateValueCallback = nullptr)
	{
		static_assert(std::is_base_of<DependencyObject, OwnerType>::value, "[ownerType] must be DependencyObject type or DependencyObject derived type.");
		auto metadata = std::make_shared<PropertyMetadata>(defaultValue, propertyChangedCallback, coerceValueCallback);
		return registerCommon(name, rttr::type::get<OwnerType>(), rttr::type::get<PropertyType>(), metadata, validateValueCallback);
	}

	static DependencyPropertyPtr find(size_t globalIndex);

private:
	DependencyProperty(const std::string & name, rttr::type ownerType, rttr::type propertyType, PropertyMetadataPtr metadata, ValidateValueCallback validateValueCallback, size_t hash);

	static DependencyPropertyPtr registerCommon(const std::string &name, rttr::type ownerType, rttr::type propertyType, PropertyMetadataPtr metadata, ValidateValueCallback validateValueCallback);

	//如果不适用DependencyPropertyPtr而是DependencyProperty，会发现studio插件在FreeLibrary时挂死
	//后续要处理这个事情，把DependencyProperty改为DependencyPropertyPtr
	static std::map<std::size_t, DependencyPropertyPtr> &dependencyProperties();
	
	std::string				m_name;
	rttr::type				m_propertyType;
	rttr::type				m_ownerType;
	PropertyMetadataPtr		m_metadata;
	ValidateValueCallback	m_validateValueCallback;
	size_t					m_hash;
};

}