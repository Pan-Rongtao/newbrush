#pragma once
#include <functional>
#include <string>
#include <map>
#include <typeindex>
#include "newbrush/core/Def.h"

namespace nb{

class DependencyObject;
class PropertyMetadata;
struct DependencyPropertyChangedEventArgs;
using PropertyChangedCallback = std::function<void(DependencyObject *, DependencyPropertyChangedEventArgs *)>;
using CoerceValueCallback = std::function<var(DependencyObject *, var)>;
using ValidateValueCallback = std::function<bool(const var &value)>;

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

	static const std::map<std::string, std::shared_ptr<PropertyCategory>> &getAll();

	static std::shared_ptr<PropertyCategory> get(const std::string &name, int order);

	static std::shared_ptr<PropertyCategory> Brush();
	static std::shared_ptr<PropertyCategory> Appearance();
	static std::shared_ptr<PropertyCategory> Public();
	static std::shared_ptr<PropertyCategory> Automation();
	static std::shared_ptr<PropertyCategory> Layout();
	static std::shared_ptr<PropertyCategory> Text();
	static std::shared_ptr<PropertyCategory> Transform();
	static std::shared_ptr<PropertyCategory> Misc();
	static std::shared_ptr<PropertyCategory> Custom();

private:
	std::string m_name;
	int			m_order;
	static std::map<std::string, std::shared_ptr<PropertyCategory>> s_propertyCategorys;
};
using PropertyCategoryPtr = std::shared_ptr<PropertyCategory>;

class NB_API PropertyMetadata
{
public:
	//构建一个PropertyMetadata
	//defaulValue：默认值
	//propertyChangedCallback：属性已改变回调
	//coerceValueCallback：属性值矫正回调
	PropertyMetadata(const var &defaultValue, PropertyChangedCallback propertyChangedCallback = nullptr, CoerceValueCallback coerceValueCallback = nullptr, 
		PropertyCategoryPtr category = nullptr, const std::string &description = "", int order = std::numeric_limits<int>::max(), std::shared_ptr<Range> range = nullptr);

	void setDefaultValue(const var &value) &;
	var defaultValue() const;
	bool isSealed() const;
	PropertyChangedCallback propertyChangedCallback();
	CoerceValueCallback coerceValueCallback();
	PropertyCategoryPtr category() const;
	const std::string &description() const;
	int order() const;
	std::shared_ptr<Range> range() const;
	
private:
	var						m_defaultValue;
	PropertyChangedCallback	m_propertyChangedCallback;
	CoerceValueCallback		m_coerceValueCallback;
	PropertyCategoryPtr		m_category;
	std::string				m_description;
	int						m_order;
	std::shared_ptr<Range>	m_range;
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
	static void registerAttached(std::shared_ptr<DependencyObject> element, const std::string &property_name, const var &property_v);

	
	//查询依赖属性值，如果查询不到，将返回一个空的var
	//element：目标元素
	//property_name：属性名
	static var findAttached(std::shared_ptr<DependencyObject> element, const std::string &property_name);

	//注册依赖属性
	//name：属性名
	//propertyType：属性值类型
	//ownerType：属性宿主类型
	//异常：std::invalid_argument [name]参数为空
	//异常：std::logic_error已经注册过同类型属性
	template<class OwnerType, class PropertyType>
	static std::shared_ptr<DependencyProperty> registerDependency(const std::string &name, const PropertyType &defaultValue, PropertyChangedCallback propertyChangedCallback = nullptr,
		CoerceValueCallback coerceValueCallback = nullptr, ValidateValueCallback validateValueCallback = nullptr, PropertyCategoryPtr category = nullptr, const std::string &description = "",
		int order = std::numeric_limits<int>::max(), std::shared_ptr<Range> range = nullptr)
	{
		static_assert(std::is_base_of<DependencyObject, OwnerType>::value, "[ownerType] must be DependencyObject type or DependencyObject derived type.");
		auto metadata = std::make_shared<PropertyMetadata>(defaultValue, propertyChangedCallback, coerceValueCallback, category, description, order, range);
		return registerCommon(name, rttr::type::get<OwnerType>(), rttr::type::get<PropertyType>(), metadata, validateValueCallback);
	}

	static void getTypePropertys(rttr::type ownerType, std::vector<std::shared_ptr<DependencyProperty>> &ret);
	
	static var unsetValue();

	static std::shared_ptr<DependencyProperty> find(size_t globalIndex);

private:
	DependencyProperty(const std::string & name, rttr::type ownerType, rttr::type propertyType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback, size_t hash);

	static std::shared_ptr<DependencyProperty> registerCommon(const std::string &name, rttr::type ownerType, rttr::type propertyType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback);

	//如果不适用std::shared_ptr<DependencyProperty>而是DependencyProperty，会发现studio插件在FreeLibrary时挂死
	//后续要处理这个事情，把DependencyProperty改为std::shared_ptr<DependencyProperty>
	static std::map<std::size_t, std::shared_ptr<DependencyProperty>> &dependencyProperties();

	static std::vector<std::shared_ptr<DependencyProperty>> getTypePropertys(rttr::type t);

	std::string							m_name;
	rttr::type							m_propertyType;
	rttr::type							m_ownerType;
	std::shared_ptr<PropertyMetadata>	m_metadata;
	ValidateValueCallback				m_validateValueCallback;
	size_t								m_hash;

	static std::map<std::shared_ptr<DependencyObject>, std::map<std::string, var>>	m_attProperties;
};

}