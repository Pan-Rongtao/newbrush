#pragma once
#include <string>
#include <map>
#include <functional>
#include "newbrush/core/Def.h"

namespace nb {

class Object;
struct NB_API Descriptor
{
	Descriptor() = default;
	Descriptor(size_t _id, const std::string &_category, const std::string &_displayName, const std::string &_description);

	size_t			id;
	std::string		category;
	std::string		displayName;
	std::string		description;
};

class MetaObject;
struct NB_API ClassDescriptor : public Descriptor
{
	ClassDescriptor() = default;
	ClassDescriptor(size_t _id, const std::string &_category, const std::string &_displayName, const std::string &_description, MetaObject *_supperClass, std::function<std::shared_ptr<Object>()> _constructor);

	std::function<std::shared_ptr<Object>()>	constructor;
	MetaObject									*surperClass{ nullptr };	//父类元对象
};

class NB_API MetaObject
{
public:
	MetaObject(const ClassDescriptor &classDescriptor);

	const ClassDescriptor &classDescriptor() const;

	void addProperty(const Descriptor &propertyDescriptor);

	const std::vector<Descriptor> &propertys() const;

	static std::shared_ptr<Object> makeObject(size_t id);

	template<class thisClass, class baseClass>
	static std::shared_ptr<MetaObject> get(const std::string classCategory, const std::string &classDisplayName, const std::string &classDescription, std::function<std::shared_ptr<Object>()> constructor)
	{
		static_assert(std::is_base_of<Object, thisClass>::value, "[T] must be as [Object] type.");
		auto& metaObjects = registeredMetaObjects();
		auto iter = metaObjects.find(typeid(thisClass).hash_code());
		if (iter == metaObjects.end())
		{
			auto metaObj = std::make_shared<MetaObject>(ClassDescriptor(typeid(thisClass).hash_code(), classCategory, classDisplayName, classDescription, baseClass::getMetaObject(), constructor));
			auto ret = registeredMetaObjects().insert({ metaObj->classDescriptor().id, metaObj });
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
	static std::map<size_t, std::shared_ptr<MetaObject>>	&registeredMetaObjects();

	ClassDescriptor				m_classDescriptor;
	std::vector<Descriptor>		m_propertys;
//	std::vector<RoutedEvent>	events;

};

/*
class NBObject
{
public:
	static MetaObject *getMetaObject()
	{
		static MetaObject metaObj(Descriptor{}, nullptr);
		return &metaObj;
	}

	virtual MetaObject *metaObject()
	{
		return getMetaObject();
	}

};


#define NB_OBJECT\
	static MetaObject *getMetaObject();\
	virtual MetaObject *metaObject() override\
	{\
		return getMetaObject();\
	}
	*/
}