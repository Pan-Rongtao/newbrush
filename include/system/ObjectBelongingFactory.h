#pragma once

#include "core/ObjectFactory.h"
#include "Array.h"

namespace nb { namespace System {

class ObjectBelongingFactoryPrivate;
class ObjectBelongingFactoryCollection;

class NB_EXPORT ObjectBelongingFactory : public nb::Core::ObjectFactory, public nb::System::IHasChildrenArray
{
	NB_OBJECT_TYPE_DECLARE();

public:
	ObjectBelongingFactory(Core::Type *type);
	virtual ~ObjectBelongingFactory(void);

	inline ObjectBelongingFactoryPrivate * GetPrivate() const {return m_private;}

	ObjectBelongingFactoryCollection * Children();

	IArray * GetChildrenArray();

	nb::Core::RefObject * CreateObject(Core::ObjectFactoryCreateObjectResponser *responser = NULL);

protected:
	virtual nb::Core::InterfaceBase * GetInterfaceOverride(const std::type_info &type);
	virtual void SetObjectContent(nbObject *object, Core::ObjectFactoryCreateObjectResponser *responser);

private:
	ObjectBelongingFactoryPrivate *m_private;

};

template<class T>
class ObjectBelongingFactoryT : public ObjectBelongingFactory
{
public:
	ObjectBelongingFactoryT() : ObjectBelongingFactory(Core::Type::GetType<T>()){}
};

typedef nbObjectPtrDerive<ObjectBelongingFactory, Core::ObjectFactoryPtr> ObjectBelongingFactoryPtr;

}}
