#include "system/ObjectBelongingFactory.h"
#include "system/ObjectBelongingFactoryCollection.h"

using namespace nb::Core;
using namespace nb::System;

NB_OBJECT_NO_ASSEMBLY_TYPE_IMPLEMENT(ObjectBelongingFactory, ObjectFactory);

namespace nb { namespace System {

class ObjectBelongingFactoryPrivate
{
public:
	ObjectBelongingFactoryCollection m_children;
};

}}


ObjectBelongingFactory::ObjectBelongingFactory(Type *type)
	: ObjectFactory(type)
{
	m_private = new ObjectBelongingFactoryPrivate();
}

ObjectBelongingFactory::~ObjectBelongingFactory(void)
{
	delete m_private;
}

IArray * ObjectBelongingFactory::GetChildrenArray()
{
	return &GetPrivate()->m_children;
}

ObjectBelongingFactoryCollection * ObjectBelongingFactory::Children()
{
	return &GetPrivate()->m_children;
}

nb::Core::InterfaceBase * ObjectBelongingFactory::GetInterfaceOverride(const std::type_info &type)
{
	std::string typeName = type.name();

	if(typeName == typeid(nb::System::IHasChildrenArray).name())
	{
		return dynamic_cast<nb::System::IHasChildrenArray *>(this);
	}
	else
	{
		return NULL;
	}
}

nb::Core::RefObject * ObjectBelongingFactory::CreateObject(ObjectFactoryCreateObjectResponser *responser)
{
	RefObject *object = ObjectFactory::CreateObject(responser);
	if(object == NULL) return NULL;

	return object;
}

void ObjectBelongingFactory::SetObjectContent(nbObject *object, ObjectFactoryCreateObjectResponser *responser)
{
	nb::Core::ObjectFactory::SetObjectContent(object, responser);

	IArray *arr = object->GetInterface<IArray>();
	if(arr == NULL)
	{
		IHasChildrenArray *hasChildren = object->GetInterface<IHasChildrenArray>();
		if(hasChildren != NULL)
		{
			arr = hasChildren->GetChildrenArray();
		}
	}

	if(arr == NULL) return;

	ObjectBelongingFactoryCollection *ch = Children();
	int count = ch->GetCount();

	for(int i=0; i<count; i++)
	{
		RefObject *childObject = ch->GetAt(i)->CreateObject(responser);
		arr->Add(childObject);
	}
}

