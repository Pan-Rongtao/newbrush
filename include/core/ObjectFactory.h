#pragma once

#include "Object.h"

namespace nb { namespace Core {

class ObjectFactory;
class NB_CORE_DECLSPEC_X_INTERFACE ObjectFactoryCreateObjectResponser : public nbObject
{
public:
	virtual void OnCreatedObject(ObjectFactory *factory, RefObject *object){}
};

class NB_CORE_DECLSPEC_X_INTERFACE ObjectFactory : public nbObject
{
	NB_OBJECT_TYPE_DECLARE();

public:
	ObjectFactory(Type *type);
	virtual ~ObjectFactory(void);

	virtual RefObject * CreateObject(ObjectFactoryCreateObjectResponser *responser=NULL);

	void SetPropertyFactory(ObjectFactory * factory);

protected:
	virtual void SetObjectContent(nbObject *object, ObjectFactoryCreateObjectResponser *responser);

private:

	Type * m_type;
};

typedef nbObjectPtrDerive<ObjectFactory, nbObjectPtr> ObjectFactoryPtr;

}}
