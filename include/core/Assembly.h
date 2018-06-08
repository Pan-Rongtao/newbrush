#pragma once

#include "RefObject.h"

class NB_CORE_DECLSPEC_X_INTERFACE Assembly : public nb::Core::RefObject
{
public:
	typedef nb::Core::OriginObject *(* NewObjectAssemblerFun)();
	typedef nb::Core::OriginObject *(* NewCopyObjectAssemblerFun)(const nb::Core::OriginObject &);


	Assembly(NewObjectAssemblerFun pFun, NewCopyObjectAssemblerFun pFunCopy);
	virtual ~Assembly(void);

//	template<class T>
//	static nb::Core::OriginObject * NewObjectAssembler()
//	{
//		return new T();
//	}

//	template<class T>
//	static nb::Core::OriginObject * NewObjectCopyAssembler(const nb::Core::OriginObject &other)
//	{
//		const T *t = dynamic_cast<const T *>(&other);
//
//		if(t == NULL)
//		{
//			ThrowException("NewObjectCopyAssembler失败。");
//		}
//		return new T(*t);
//	}

	nb::Core::OriginObject * CreateObjectInstance();

	nb::Core::OriginObject * CreateObjectInstance(const nb::Core::OriginObject &other);

private:
	NewObjectAssemblerFun m_pFun;
	NewCopyObjectAssemblerFun m_pFunCopy;
};

typedef nbObjectPtrDerive<Assembly, nb::Core::RefObjectPtr> AssemblyPtr;

namespace nb { namespace Core {

template<class T>
class NB_EXPORT_NO AssemblyT : public Assembly
{
public:
	AssemblyT() : Assembly(&Assembly::NewObjectAssembler<T>)	{}

	//bool IsEqual(const T &left, const T &right) {return left == right;}

};

}}
