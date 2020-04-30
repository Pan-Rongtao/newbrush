#pragma once
#include <string>
#include "newbrush/core/Def.h"

namespace nb {

struct NB_API Descriptor
{
	Descriptor() = default;
	Descriptor(size_t _id, const std::string &_category, const std::string &_displayName, const std::string &_description);

	size_t			id;
	std::string		category;
	std::string		displayName;
	std::string		description;
};

class NB_API MetaObject
{
public:
	MetaObject(const Descriptor &classDescriptor, MetaObject *surrperClass);

	const Descriptor &descriptor() const;

	const MetaObject *supperClass() const;

	void addProperty(const Descriptor &propertyDescriptor);

	const std::vector<Descriptor> &propertys() const;

private:
	Descriptor					m_classDescriptor;
	MetaObject					*m_supperClass;	//父类元对象
	std::vector<Descriptor>		m_propertys;
//	std::vector<RoutedEvent>	events;
};

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
}