#include "core/ObjectFactory.h"
#include "core/Exception.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace nb::Core;

NB_OBJECT_NO_ASSEMBLY_TYPE_IMPLEMENT(ObjectFactory, nbObject);

ObjectFactory::ObjectFactory(Type *type)
: m_type(type)
{
	if(type == NULL)
	{
		NB_THROW_EXCEPTION("[ObjectFactory::ObjectFactory] Type不能为空");
	}
}

ObjectFactory::~ObjectFactory(void)
{
}

void ObjectFactory::SetPropertyFactory(ObjectFactory * factory)
{
}

RefObject * ObjectFactory::CreateObject(ObjectFactoryCreateObjectResponser *responser)
{
	OriginObject * originObj = m_type->GetAssembly()->CreateObjectInstance();

	nbObject *object = dynamic_cast<nbObject *>(originObj);
	if(object == NULL)
	{
		delete originObj;
		return NULL;
	}
	if(responser != NULL) responser->OnCreatedObject(this, object);

	SetObjectContent(object, responser);

	return object;
}

void ObjectFactory::SetObjectContent(nbObject *object, ObjectFactoryCreateObjectResponser *responser)
{
	std::list<DependencyPropertyPtr> lst;
	GetAllRefProperties(lst);

	std::list<DependencyPropertyPtr>::iterator itor = lst.begin();
	for(; itor != lst.end(); itor++)
	{
		DependencyProperty * prop = *itor;
		if(prop->IsImmobile())
		{
			RefObject *propValue = GetRefValue(prop);
			ObjectFactory *propFactory = dynamic_cast<ObjectFactory *>(propValue);

			if(propFactory != NULL)
			{
				nbObject *child = dynamic_cast<nbObject *>(object->GetRefValue(prop));
				if(child != NULL)
				{
					propFactory->SetObjectContent(child, responser);
				}
			}
		}
		else
		{
			RefObject *propValue = GetRefValue(prop);
			ObjectFactory *propFactory = dynamic_cast<ObjectFactory *>(propValue);
			if(propFactory != NULL) propValue = propFactory->CreateObject(responser);

			object->SetRefValue(*itor, propValue);
		}
	}

	lst.clear();
	GetAllValueProperties(lst);
	itor = lst.begin();
	for(; itor != lst.end(); itor++)
	{
		const ValueObject &propValue = GetValueValue(*itor);
		object->SetValueValue(*itor, propValue);
	}
}
