#pragma once
#include <typeinfo>
#include <stdio.h>
#include "Def.h"

#define NB_OBJECT_TYPE_DECLARE() \
	private: \
	static void *s_pPrepareType; \

#define NB_OBJECT_TYPE_IMPLEMENT(thisClass, parentClass, TypeObjectIsEqualFun, TypeObjectCopyFun) \
	void *thisClass::s_pPrepareType = nb::core::OriginObject::PrepargeType<thisClass, parentClass>(TypeObjectIsEqualFun, TypeObjectCopyFun);

#define NB_OBJECT_NO_ASSEMBLY_TYPE_IMPLEMENT(thisClass, parentClass) \
	void *thisClass::s_pPrepareType = nb::core::OriginObject::PrepargeNoAssemblyType<thisClass, parentClass>();

class Assembly;
namespace nb { namespace core{

class NB_API InterfaceBase
{
public:
	virtual ~InterfaceBase() {}
};

class NB_API OriginObject
{
	NB_OBJECT_TYPE_DECLARE();

public:
	typedef nb::core::OriginObject * (* NewObjectAssemblerFun)(); 
	typedef nb::core::OriginObject *(* NewCopyObjectAssemblerFun)(const nb::core::OriginObject &);
	typedef bool (* IsEqualTypeObjectFun)(const OriginObject &left, const OriginObject &right);
	typedef void (* CopyObjectFun)(nb::core::OriginObject &dest, const nb::core::OriginObject &src);

public:
	OriginObject(void);
	virtual ~OriginObject(void);

	static Assembly * CreateAssembly(NewObjectAssemblerFun pFun, NewCopyObjectAssemblerFun pFunCopy);


	template<class Derive, class Parent>
	static void *PrepargeType(IsEqualTypeObjectFun funIsEqual, CopyObjectFun funCopy)
	{
	//	NewObjectCopyAssembler<Derive>;
		Assembly *pAss = CreateAssembly(&OriginObject::NewObjectAssembler<Derive>, &OriginObject::NewObjectCopyAssembler<Derive>);

		return PrepargeType(typeid(Derive), typeid(Parent), pAss, funIsEqual, funCopy);
	}

	template<class Derive, class Parent>
	static void *PrepargeNoAssemblyType()
	{
		return PrepargeType(typeid(Derive), typeid(Parent), NULL, NULL, NULL);
	}

	template<class T>
	static bool IsEqualFun(const nb::core::OriginObject &left, const nb::core::OriginObject &right)
	{
		const T *pLeft = dynamic_cast<const T *>(&left);
		if(pLeft == NULL) ThrowException("对象比较时，左侧类型不允许。");

		const T *pRight = dynamic_cast<const T *>(&right);
		if(pRight == NULL) ThrowException("对象比较时，右侧类型不允许。");

		return *pLeft == *pRight;
	}

	template<class T>
	static void CopyFun(nb::core::OriginObject &dest, const nb::core::OriginObject &src)
	{
		T *pDest = dynamic_cast<T *>(&dest);
		if(pDest == NULL) ThrowException("对象复制时，目标类型不允许。");

		const T *pSrc = dynamic_cast<const T *>(&src);
		if(pSrc == NULL) ThrowException("对象复制时，源类型不允许。");

		*pDest = *pSrc;
	}

	static void ThrowException(const char *pMessage);

	template<class T>
	T * GetInterface() {return dynamic_cast<T *>(GetInterfaceOverride(typeid(T)));}

protected:
	static void * PrepargeType(const std::type_info &type, const std::type_info &parentType, Assembly *pAssembly, IsEqualTypeObjectFun funIsEqualTypeObject, CopyObjectFun funCopy);

	virtual InterfaceBase * GetInterfaceOverride(const std::type_info &type) {return NULL;}

private:
	template<class T>
	static OriginObject * NewObjectAssembler()
	{
		return new T();
	}


	template<class T>
	static nb::core::OriginObject * NewObjectCopyAssembler(const nb::core::OriginObject &other)
	{
		const T *t = dynamic_cast<const T *>(&other);

		if(t == NULL)
		{
			ThrowException("NewObjectCopyAssembler失败。 ");
		}
		return new T(*t);
	}
};

class NB_API EnumObject : public OriginObject
{
	NB_OBJECT_TYPE_DECLARE();
};

class NB_API RockOriginObject : public OriginObject
{
	NB_OBJECT_TYPE_DECLARE();
};

}}

