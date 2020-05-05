#pragma once
#include <string>
#include <map>
#include <functional>
#include <type_traits>
#include "newbrush/core/Def.h"
#include "newbrush/core/DependencyProperty.h"

namespace nb {

class Object;
struct NB_API Descriptor
{
	Descriptor() = default;
	Descriptor(const std::string &_category, const std::string &_displayName, const std::string &_description);

	std::string		category;
	std::string		displayName;
	std::string		description;
};

class MetaObject;
struct NB_API ClassDescriptor : public Descriptor
{
	ClassDescriptor(std::type_index _type, const std::string &_category, const std::string &_displayName, const std::string &_description, std::shared_ptr<MetaObject> _supperClass, std::function<std::shared_ptr<Object>()> _constructor);

	std::type_index								type;
	std::function<std::shared_ptr<Object>()>	constructor;
	std::shared_ptr<MetaObject> 				surperClass;	//父类元对象
};

struct NB_API PropertyDescriptor : public Descriptor
{
	enum ValueType : short
	{
		Boolean,
		Int8,
		Int16,
		Int32,
		Int64,
		UInt8,
		UInt16,
		UInt32,
		UInt64,
		Single,
		Double,
		String,
		Vec2,
		Vec3,
		Vec4,
		Mat2x2,
		Mat2x3,
		Mat2x4,
		Mat3x2,
		Mat3x3,
		Mat3x4,
		Mat4x2,
		Mat4x3,
		Mat4x4,
		Color,
		Date,
		Time,
		DateTime,
		TimeSpan,
		Thickness,
		Enum,
	};

	PropertyDescriptor(size_t _type, const std::string &_category, const std::string &_displayName, const std::string &_description, ValueType _valueType, const std::string &_extra = "");

	size_t		type;
	ValueType	valueType;
	std::string	extra;
};

class NB_API MetaObject
{
public:
	const ClassDescriptor &classDescriptor() const;

	void addProperty(const DependencyProperty &dp, const std::string &category, const std::string &description, PropertyDescriptor::ValueType valueType, const std::string &extra = "");

	const std::vector<PropertyDescriptor> &properties() const;

	std::vector<PropertyDescriptor> getAllProperties() const;

	static std::shared_ptr<Object> makeObject(std::string id);

	template<class thisClass, class baseClass>
	static typename std::enable_if<!std::is_void<baseClass>::value, std::shared_ptr<MetaObject>>::type get(const std::string classCategory, const std::string &classDisplayName, const std::string &classDescription, std::function<std::shared_ptr<Object>()> constructor)
	{
		static_assert(std::is_base_of<Object, thisClass>::value, "[thisClass] must be as [Object] type.");
		static_assert(std::is_base_of<Object, baseClass>::value, "[baseClass] must be as [Object] type.");
		static_assert(!std::is_same<thisClass, baseClass>::value, "thisClass must not be same with baseClass.");
		auto& metaObjects = MetaObject::registeredMetaObjects();
		auto key = nb::getFullName(typeid(thisClass));
		auto iter = metaObjects.find(key);
		if (iter == metaObjects.end())
		{
			std::shared_ptr<MetaObject> metaObj(new MetaObject(ClassDescriptor(typeid(thisClass), classCategory, classDisplayName, classDescription, baseClass::getMetaObject(), constructor)));
			auto ret = metaObjects.insert({ key, metaObj });
			return ret.first->second;
		}
		else
		{
			iter->second->seal = true;
			return iter->second;
		}
	}

	template<class thisClass, class baseClass>
	static typename std::enable_if<std::is_void<baseClass>::value, std::shared_ptr<MetaObject>>::type get(const std::string classCategory, const std::string &classDisplayName, const std::string &classDescription, std::function<std::shared_ptr<Object>()> constructor)
	{
		static_assert(std::is_base_of<Object, thisClass>::value, "[thisClass] must be as [Object] type.");
		static_assert(!std::is_same<thisClass, baseClass>::value, "thisClass must not be same with baseClass.");
		auto& metaObjects = MetaObject::registeredMetaObjects();
		auto key = nb::getFullName(typeid(thisClass));
		auto iter = metaObjects.find(key);
		if (iter == metaObjects.end())
		{
			std::shared_ptr<MetaObject> metaObj(new MetaObject(ClassDescriptor(typeid(thisClass), classCategory, classDisplayName, classDescription, nullptr, constructor)));
			auto ret = metaObjects.insert({ key, metaObj });
			return ret.first->second;
		}
		else
		{
			iter->second->seal = true;
			return iter->second;
		}
	}

	bool seal{ false };

private:
	MetaObject(const ClassDescriptor &classDescriptor);

	static std::map<std::string, std::shared_ptr<MetaObject>>	&registeredMetaObjects();

	ClassDescriptor					m_classDescriptor;
	std::vector<PropertyDescriptor>	m_properties;
//	std::vector<RoutedEvent>	events;
};

}