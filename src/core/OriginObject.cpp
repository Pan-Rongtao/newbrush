#include "core/OriginObject.h"
#include "core/Assembly.h"
#include "core/Type.h"
#include "core/Exception.h"

using namespace nb::core;

NB_OBJECT_TYPE_IMPLEMENT(OriginObject, OriginObject, NULL, NULL);

NB_OBJECT_TYPE_IMPLEMENT(EnumObject, OriginObject, NULL, NULL);

NB_OBJECT_TYPE_IMPLEMENT(RockOriginObject, OriginObject, NULL, NULL);

OriginObject::OriginObject(void)
{
}

OriginObject::~OriginObject(void)
{
}

Assembly * OriginObject::CreateAssembly(NewObjectAssemblerFun pFun, NewCopyObjectAssemblerFun pFunCopy)
{
	return new Assembly(pFun, pFunCopy);
}

void * OriginObject::PrepargeType(const std::type_info &type, const std::type_info &parentType, Assembly *pAssembly, IsEqualTypeObjectFun funIsEqualTypeObject, CopyObjectFun funCopy)
{
	return Type::PrepargeType(type, parentType, pAssembly, funIsEqualTypeObject, funCopy);
}

void OriginObject::ThrowException(const char *pMessage)
{
	NB_THROW_EXCEPTION(pMessage);
}
