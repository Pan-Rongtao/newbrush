#pragma once

#include <typeinfo>
#include "NewBrushDef.h"
#include "CoreDef.h"

#define NB_OBJECT_TYPE_DECLARE() \
	private: \
	static void *s_pPrepareType; \

#define NB_OBJECT_TYPE_IMPLEMENT(thisClass, parentClass, TypeObjectIsEqualFun, TypeObjectCopyFun) \
	void *thisClass::s_pPrepareType = nb::Core::OriginObject::PrepargeType<thisClass, parentClass>(TypeObjectIsEqualFun, TypeObjectCopyFun);

#define NB_OBJECT_NO_ASSEMBLY_TYPE_IMPLEMENT(thisClass, parentClass) \
	void *thisClass::s_pPrepareType = nb::Core::OriginObject::PrepargeNoAssemblyType<thisClass, parentClass>();

class Assembly;
namespace nb { namespace Core{

class NB_CORE_DECLSPEC_X_INTERFACE InterfaceBase
{
public:
	virtual ~InterfaceBase() {}
};

class NB_CORE_DECLSPEC_X_INTERFACE OriginObject
{
	NB_OBJECT_TYPE_DECLARE();

public:
	typedef nb::Core::OriginObject * (* NewObjectAssemblerFun)(); 
	typedef nb::Core::OriginObject *(* NewCopyObjectAssemblerFun)(const nb::Core::OriginObject &);
	typedef bool (* IsEqualTypeObjectFun)(const OriginObject &left, const OriginObject &right);
	typedef void (* CopyObjectFun)(nb::Core::OriginObject &dest, const nb::Core::OriginObject &src);

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
	static bool IsEqualFun(const nb::Core::OriginObject &left, const nb::Core::OriginObject &right)
	{
		const T *pLeft = dynamic_cast<const T *>(&left);
		if(pLeft == NULL) ThrowException("对象比较时，左侧类型不允许。");

		const T *pRight = dynamic_cast<const T *>(&right);
		if(pRight == NULL) ThrowException("对象比较时，右侧类型不允许。");

		return *pLeft == *pRight;
	}

	template<class T>
	static void CopyFun(nb::Core::OriginObject &dest, const nb::Core::OriginObject &src)
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

//protected:
//	static void *s_pPrepareType;

private:
	template<class T>
	static OriginObject * NewObjectAssembler()
	{
		return new T();
	}


	template<class T>
	static nb::Core::OriginObject * NewObjectCopyAssembler(const nb::Core::OriginObject &other)
	{
		const T *t = dynamic_cast<const T *>(&other);

		if(t == NULL)
		{
			ThrowException("NewObjectCopyAssembler失败。 ");
		}
		return new T(*t);
	}
};


class NB_CORE_DECLSPEC_X_INTERFACE EnumObject : public OriginObject
{
	NB_OBJECT_TYPE_DECLARE();
};

class NB_CORE_DECLSPEC_X_INTERFACE RockOriginObject : public OriginObject
{
	NB_OBJECT_TYPE_DECLARE();
};

//template<class T>
//class EnumObject : public BaseEnumObject
//{
//};

}}

