#pragma once
#include "RefObject.h"

class NB_API Assembly : public nb::core::RefObject
{
public:
	typedef nb::core::OriginObject *(* NewObjectAssemblerFun)();
	typedef nb::core::OriginObject *(* NewCopyObjectAssemblerFun)(const nb::core::OriginObject &);

	Assembly(NewObjectAssemblerFun pFun, NewCopyObjectAssemblerFun pFunCopy);
	virtual ~Assembly(void);

	nb::core::OriginObject * CreateObjectInstance();
	nb::core::OriginObject * CreateObjectInstance(const nb::core::OriginObject &other);

private:
	NewObjectAssemblerFun m_pFun;
	NewCopyObjectAssemblerFun m_pFunCopy;
};

typedef nbObjectPtrDerive<Assembly, nb::core::RefObjectPtr> AssemblyPtr;
