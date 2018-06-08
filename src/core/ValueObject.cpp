#include "core/ValueObject.h"
#include "InternalCore.h"

#ifdef new
#undef new
#endif

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

using namespace nb::Core;

NB_OBJECT_TYPE_IMPLEMENT(ValueObject, OriginObject, NULL, NULL);

//NB_OBJECT_TYPE_IMPLEMENT(Int, ValueObject, &ValueObject::IsEqualFun<Int>, &ValueObject::CopyFun<Int>);
//NB_OBJECT_TYPE_IMPLEMENT(Long, ValueObject, &ValueObject::IsEqualFun<Long>, &ValueObject::CopyFun<Long>);
//NB_OBJECT_TYPE_IMPLEMENT(Float, ValueObject, &ValueObject::IsEqualFun<Float>, &ValueObject::CopyFun<Float>);
//NB_OBJECT_TYPE_IMPLEMENT(Double, ValueObject, &ValueObject::IsEqualFun<Double>, &ValueObject::CopyFun<Double>);
//NB_OBJECT_TYPE_IMPLEMENT(Bool, ValueObject, &ValueObject::IsEqualFun<Bool>, &ValueObject::CopyFun<Bool>);

#define NB_ROCK_VALUE_OBJECT_PROPARE_TYPE_IMPLEMENT(T) \
	void *RockValueObjectsPropareType::s_p##T##PrepareType = nb::Core::OriginObject::PrepargeType<T, ValueObject>(&ValueObject::IsEqualFun<T>, &ValueObject::CopyFun<T>);

class RockValueObjectsPropareType
{
public:
	static void *s_pIntPrepareType;
	static void *s_pLongPrepareType;
	static void *s_pFloatPrepareType;
	static void *s_pDoublePrepareType;
	static void *s_pBoolxPrepareType;
};

//void *RockValueObjectsPropareType::s_pIntPrepareType = nb::Core::OriginObject::PrepargeType<Int, ValueObject>(&ValueObject::IsEqualFun<Int>, &ValueObject::CopyFun<Int>);

NB_ROCK_VALUE_OBJECT_PROPARE_TYPE_IMPLEMENT(Int);
NB_ROCK_VALUE_OBJECT_PROPARE_TYPE_IMPLEMENT(Long);
NB_ROCK_VALUE_OBJECT_PROPARE_TYPE_IMPLEMENT(Float);
NB_ROCK_VALUE_OBJECT_PROPARE_TYPE_IMPLEMENT(Double);
NB_ROCK_VALUE_OBJECT_PROPARE_TYPE_IMPLEMENT(Boolx);



ValueObject::ValueObject(void)
{
//	nbInternalCore::GetObjectLiveMonitor()->ObjectHeapConstructPermit(this);

//	RockValueObjectsPropareType x;
//	x.s_pIntPrepareType = NULL;
}

ValueObject::~ValueObject(void)
{
}

void * ValueObject::operator new(size_t t)
{
	void *p = nbInternalCore::GetObjectLiveMonitor()->Malloc(t, false, NULL, 0);
	return p;
}

void ValueObject::operator delete(void *p)
{
	if(p == NULL) return;
	nbInternalCore::GetObjectLiveMonitor()->Free(p);
}
