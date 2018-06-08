#pragma once

#include <map>
#include <list>
#include <vector>
#include <typeinfo>

#include "RefObject.h"
#include "DependencyProperty.h"
#include "Assembly.h"

class PropertyInternal;

namespace nb { namespace Core {

class TypeInternal;

class NB_CORE_DECLSPEC_X_INTERFACE Type : public RefObject
{
public:
//	typedef OriginObject *(* NewObjectAssemblerFun)();

	typedef bool (* IsEqualObjectFun)(const OriginObject &left, const OriginObject &right);
	typedef void (* CopyObjectFun)(OriginObject &dest, const OriginObject &src);

public:
	virtual ~Type(void);

//	static Type * RegisterType(const std::type_info &type, Type *pParentType, Assembly *pAssembly);
	static Type * GetType(const std::type_info &type);

	template<class T>
	static Type * GetType() {	return GetType(typeid(T));}

	Type * GetParent() const;

	Assembly * GetAssembly() const;

	DependencyProperty * GetExternalProperty(const char *pKey) const;

	IsEqualObjectFun GetIsEqualObjectFun() const;
	CopyObjectFun GetCopyObjectFun() const;

	static void * PrepargeType(const std::type_info &type, const std::type_info &parentType, Assembly *pAssembly, IsEqualObjectFun funIsEqual, CopyObjectFun funCopy);

	template<class T>
	static void * PrepargeTypeT(const std::type_info &parentType, Assembly *pAssembly)
	{
	}


	template<class T>
	static T * CreateObjectInstance()
	{
		Type *pType = Type::GetType(typeid(T));
		if(pType == NULL)
		{
			ThrowException("指定的类型未注册。");
		}

		OriginObject *pObject = pType->GetAssembly()->CreateObjectInstance();
		if(pObject == NULL)
		{
			ThrowException("构建对象失败。");
		}

		T *pT = dynamic_cast<T *>(pObject);
		if(pT == NULL)
		{
			ThrowException("对象类型不符。");
		}

		return pT;
	}

	template<class T>
	static bool IsEqualFun(const OriginObject &left, const OriginObject &right)
	{
		const T *pLeft = dynamic_cast<const T *>(&left);
		if(pLeft == NULL) ThrowException("对象比较时，左侧类型不允许。");

		const T *pRight = dynamic_cast<const T *>(&right);
		if(pRight == NULL) ThrowException("对象比较时，右侧类型不允许。");

		return *pLeft == *pRight;
	}

	bool IsRefType() const;

	const std::string &GetTypeName() const {return m_sTypeName;}

	int GetPropertyCount() const;
	int GetParentPropertyCount() const;

	bool ContainProperty(DependencyProperty *prop) const;
	DependencyProperty * GetPropertyAt(size_t index) const;

private:
	static void * PropergeType(Type *pUse, const std::type_info &parentType, Assembly *pAssembly)
	{
//		new TypeT<int>();
		return NULL;
	}

//	static void * PrepareProperty(constt std::type_info &type);

protected:
private:
	Type(const std::type_info &type, Type *pParent, Assembly *pAssembly, IsEqualObjectFun funIsEqualObject, CopyObjectFun funCopy, int selfPropertyCount);
	Type(const std::string &typeName, Type *pParent, Assembly *pAssembly, IsEqualObjectFun funIsEqualObject, CopyObjectFun funCopy, int selfPropertyCount);

	friend class TypeInternal;
	friend class DependencyPropertyInternal;

	void AttachPropertyPrivate(const std::string &key, DependencyProperty *pProperty);
	void AttachExternalPropertyPrivate(const std::string &key, DependencyProperty *pProperty);

private:
	Type * const m_pParent;
	//const std::type_info &m_typeInfo;
	const std::string m_sTypeName;

	const bool m_bIsRefType;

	struct ProperitesInfo
	{
		std::map<std::string, DependencyPropertyPtr> m_map;
		std::vector<DependencyPropertyPtr> m_vec;
	} *m_pProperties, *m_pExternalProperties;

	AssemblyPtr m_pAssembly;

	IsEqualObjectFun m_funIsEqualObject;
	CopyObjectFun m_funCopyObject;

	mutable int m_nParentPropertyCount;
	const int m_selfPropertyCount;
};

typedef nbObjectPtrDerive<Type, RefObjectPtr> TypePtr;

template<class T>
class NB_EXPORT_NO TypeT : public Type
{
private:
	TypeT(Type *pParent, Assembly *pAssembly=NULL)
		: Type(typeid(T), pParent, pAssembly)
	{
	}

public:
	static bool IsEqual(const T &left, const T &right) {return left == right;}

	virtual bool IsTheType(const OriginObject &object)
	{
		return dynamic_cast<const T *>(&object) != NULL;
	}

	static TypeT & Instance()
	{
		static TypeT<T> type;
		return type;
	}
};

}}

#define NB_TYPE(TYPE) (nb::Core::Type::GetType(typeid(TYPE)))
