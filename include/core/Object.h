#pragma once
#include <map>
#include <stddef.h>
#include "RefObject.h"
#include "ValueObject.h"
#include "DependencyProperty.h"
#include "PropertyValueToucher.h"
#include "PropertyLock.h"

#define NB_X_OBJECT_EXTERNAL_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::core::DependencyProperty * externalProperty_##propertyName; \
	static nb::core::DependencyProperty * propertyName##Property(); \

#define NB_X_OBJECT_EXTERNAL_PROPERTY_IMPLEMENT(className, propertyName, propertyType) \
	nb::core::DependencyProperty * className::externalProperty_##propertyName = nb::core::DependencyProperty::PrepareExternalProperty<className, propertyType>(#propertyName, NULL); \
	nb::core::DependencyProperty * className::propertyName##Property() {return externalProperty_##propertyName;} \

#define NB_X_OBJECT_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::core::DependencyProperty * propertyName##Property(); \
	class NB_API ____##propertyName##PV : public nb::core::PV< propertyType > \
	{ \
	public: \
		nb::core::DependencyProperty * GetProperty() const; \
		static nb::core::DependencyProperty * GetPropertyStatic(); \
		void operator = (propertyType *object);\
	private:\
		static nb::core::DependencyProperty * const m_prop; \
		nbObject * GetBelongToObject() const; \
	};  \
	____##propertyName##PV propertyName; \

#define NB_X_OBJECT_PROPERTY_DECLARE_IMMOBILE(propertyName, propertyType, User) \
	static nb::core::DependencyProperty * propertyName##Property(); \
	class NB_API ____##propertyName##PV : public nb::core::ImmobilePV< propertyType, User > \
	{ \
		friend class User;\
	public: \
		nb::core::DependencyProperty * GetProperty() const; \
		static nb::core::DependencyProperty * GetPropertyStatic(); \
	private: \
		void operator = (propertyType *object);\
	private:\
		static nb::core::DependencyProperty * const m_prop; \
		nbObject * GetBelongToObject() const; \
	};  \
	____##propertyName##PV propertyName; \

#define NB_X_OBJECT_PROPERTY_DECLARE_1(propertyName, propertyType) \
	private:\
	static nb::core::DependencyProperty * property_##propertyName; \
	static nb::core::DependencyProperty * propertyName##Property(); \
	PV< propertyType > propertyName; \
	private:\

#define NB_X_ROCK_OBJECT_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::core::DependencyProperty * propertyName##Property(); \
	class NB_API ____##propertyName##PV : public nb::core::RockPV< propertyType > \
	{ \
	public: \
		nb::core::DependencyProperty * GetProperty() const; \
		static nb::core::DependencyProperty * GetPropertyStatic(); \
		void operator = (propertyType *object);\
		void operator = (const propertyType::t &v) {Set(new propertyType(v), GetPropertyStatic(), GetBelongToObject());}\
	private:\
		static nb::core::DependencyProperty * const m_prop; \
		nbObject * GetBelongToObject() const; \
	};  \
	____##propertyName##PV propertyName; \

#define NB_X_OBJECT_PROPERTY_IMPLEMENT(className, propertyName, propertyType, propertyChangedFun) \
	nb::core::DependencyProperty * const className::____##propertyName##PV::m_prop = nb::core::DependencyProperty::PrepareProperty<className, propertyType>((unsigned long)(&((className *)(NULL))->propertyName), #propertyName, false, \
			static_cast<nb::core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::core::DependencyProperty * className::propertyName##Property() {return className::____##propertyName##PV::GetPropertyStatic();} \
	nb::core::DependencyProperty * className::____##propertyName##PV::GetProperty() const {return m_prop;} \
	nb::core::DependencyProperty * className::____##propertyName##PV::GetPropertyStatic() {return m_prop;} \
	void className::____##propertyName##PV::operator = (propertyType *object)\
	{\
		Set(object, GetPropertyStatic(), GetBelongToObject());\
	}\
	nbObject * className::____##propertyName##PV::GetBelongToObject() const\
	{\
		className * x = NULL;\
		unsigned long offset = (unsigned long)&x->propertyName;\
		className *belongTo = (className *)(((unsigned long)this) - offset);\
		return belongTo;\
	}\

#define NB_X_OBJECT_PROPERTY_IMPLEMENT_IMMOBILE(className, propertyName, propertyType, propertyChangedFun) \
	nb::core::DependencyProperty * const className::____##propertyName##PV::m_prop = nb::core::DependencyProperty::PrepareProperty<className, propertyType>((unsigned long)(&((className *)(NULL))->propertyName), #propertyName, true, \
			static_cast<nb::core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::core::DependencyProperty * className::propertyName##Property() {return className::____##propertyName##PV::GetPropertyStatic();} \
	nb::core::DependencyProperty * className::____##propertyName##PV::GetProperty() const {return m_prop;} \
	nb::core::DependencyProperty * className::____##propertyName##PV::GetPropertyStatic() {return m_prop;} \
	void className::____##propertyName##PV::operator = (propertyType *object)\
	{\
		Set(object, GetPropertyStatic(), GetBelongToObject());\
	}\
	nbObject * className::____##propertyName##PV::GetBelongToObject() const\
	{\
		className * x = NULL;\
		unsigned long offset = (unsigned long)&x->propertyName;\
		className *belongTo = (className *)(((unsigned long)this) - offset);\
		return belongTo;\
	}\


#define NB_OBJECT_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::core::DependencyPropertyPtr property_##propertyName; \
	static nb::core::DependencyProperty * Get##propertyName##Property(); \
	nb::core::PropertyValueToucher< propertyType > propertyName() \
	{ \
		return nb::core::PropertyValueToucher< propertyType >(this, Get##propertyName##Property()); \
	}\

#define NB_OBJECT_PROPERTY_IMPLEMENT(className, propertyName, propertyType) \
	nb::core::DependencyPropertyPtr className::property_##propertyName = nb::core::DependencyProperty::PrepareProperty(#propertyName, typeid(className), typeid(propertyType)); \
	nb::core::DependencyProperty * className::Get##propertyName##Property() const {return property_##propertyName;} \


#define NB_OBJECT_PROPERTY_IMPLEMENT_EX_1(className, propertyName, propertyType, propertyChangedFun) \
	nb::core::DependencyPropertyPtr className::property_##propertyName = nb::core::DependencyProperty::PrepareProperty(#propertyName, typeid(className), typeid(propertyType), \
		static_cast<nb::core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::core::DependencyProperty * className::Get##propertyName##Property() {return property_##propertyName;} \


#define NB_OBJECT_PROPERTY_IMPLEMENT_EX(className, propertyName, propertyType, propertyChangedFun) \
	nb::core::DependencyPropertyPtr className::property_##propertyName = nb::core::DependencyProperty::PrepareProperty<className, propertyType>(#propertyName, \
		static_cast<nb::core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::core::DependencyProperty * className::Get##propertyName##Property() {return property_##propertyName;} \

#define NB_OBJECT_VALUE_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::core::DependencyPropertyPtr property_##propertyName; \
	static nb::core::DependencyProperty * Get##propertyName##Property(); \
	nb::core::ValuePropertyValueToucher< propertyType > propertyName() \
	{ \
		return nb::core::ValuePropertyValueToucher< propertyType >(this, Get##propertyName##Property()); \
	}\

#define NB_OBJECT_VALUE_PROPERTY_IMPLEMENT_EX(className, propertyName, propertyType, propertyChangedFun) \
	nb::core::DependencyPropertyPtr className::property_##propertyName = nb::core::DependencyProperty::PrepareProperty(#propertyName, typeid(className), typeid(propertyType), \
		static_cast<nb::core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::core::DependencyProperty * className::Get##propertyName##Property() const {return property_##propertyName;}

#define NB_OBJECT_VALUE_PROPERTY_IMPLEMENT_EX_1(className, propertyName, propertyType, propertyChangedFun) \
	nb::core::DependencyPropertyPtr className::property_##propertyName = nb::core::DependencyProperty::PrepareProperty(#propertyName, typeid(className), typeid(propertyType), \
		static_cast<nb::core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::core::DependencyProperty * className::propertyName##Property() {return property_##propertyName;}

#define NB_OBJECT_ENUM_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::core::DependencyPropertyPtr property_##propertyName; \
	static nb::core::DependencyProperty * Get##propertyName##Property(); \
	nb::core::EnumPropertyValueToucher< propertyType > propertyName() \
	{ \
		return nb::core::EnumPropertyValueToucher< propertyType >(this, Get##propertyName##Property()); \
	}\

#define NB_OBJECT_GENERICS_PROPERTY_DECLARE(propertyName) \
	static nb::core::DependencyPropertyPtr property_##propertyName; \
	nb::core::DependencyProperty * Get##propertyName##Property() const; \
	GenericsPropertyValueToucher propertyName() \
	{ \
		return GenericsPropertyValueToucher(this, Get##propertyName##Property()); \
	}\

#define NB_OBJECT_ENUM_PROPERTY_DECLARE_NEW(propertyName, propertyType) \
	static nb::core::DependencyPropertyPtr property_##propertyName; \
	static nb::core::DependencyProperty * Get##propertyName##Property(); \
	nb::core::EnumPropertyValueToucher_New< propertyType > propertyName() \
	{ \
		return nb::core::EnumPropertyValueToucher_New< propertyType >(this, Get##propertyName##Property()); \
	}\


#define NB_OBJECT_EXTERNAL_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::core::DependencyPropertyPtr property_##propertyName; \
	static nb::core::DependencyProperty * Get##propertyName##Property(); \

#define NB_OBJECT_EXTERNAL_PROPERTY_IMPLEMENT(className, propertyName, propertyType) \
	nb::core::DependencyPropertyPtr className::property_##propertyName = nb::core::DependencyProperty::PrepareProperty<className, propertyType>(#propertyName, \
		NULL); \
	nb::core::DependencyProperty * className::Get##propertyName##Property() {return property_##propertyName;} \

class nbEventBase;
class nbEventPrivate;
namespace nb {	namespace core {

class Type;
class PropertyValuesMgr;
class TypesPropertyValuesStore;
class ObjectAttachmentSymbol;
class ObjectAttachmentsMgr;
class ObjectKeyTagsMgr;
class PropertyValueBase
{
public:
	virtual ~PropertyValueBase(){}
	virtual bool Equal(const PropertyValueBase &right) const = 0;
private:
	DependencyPropertyPtr m_pProperty;
};

template<class ValueType>
class PropertyValue : public PropertyValueBase
{
public:
	PropertyValue() {}
	PropertyValue(const ValueType &value) : m_value(value){}
	ValueType value() const{ return m_value;}
	void SetValue(const ValueType &value) {m_value = value;}

	bool operator == (const ValueType &right) const
	{
		return m_value == right;
	}

	bool operator == (const PropertyValue<ValueType> &right) const
	{
		return m_value == right.m_value;
	}

	bool Equal(const PropertyValueBase &right) const
	{
		const PropertyValue<ValueType> *ps = dynamic_cast<const PropertyValue<ValueType> *>(&right);
		if(ps == NULL) return false;
		return m_value == ps->m_value;
	}

private:
	ValueType m_value;
};

class NB_API PVBaseBase
{
public:
	PVBaseBase(){}
	~PVBaseBase(){} // 非虚函数？？原来是没有构造和析构函数的，为了在vs2015上编译通过，添加的

	virtual DependencyProperty * GetProperty() const {return NULL;}
	virtual nbObject * GetBelongToObject() const {return NULL;}

	PropertyLock *m_lock;
};

class NB_API RefPVBase : public PVBaseBase
{
	friend class ::nbObject;
public:
	inline void operator = (RefObject *object)
	{
		Set(object);
	}

	inline void Set(RefObject *object)
	{
		if(m_object == object) return;

		SubFromObject(m_object);
		m_object = object;
		AddToObject(m_object);
	}


	RefObject * Get() const {return m_object;}

	bool IsNull() const {return m_object == NULL;}

protected:
	void Set(RefObject *object, DependencyProperty *prop, nbObject *belongToObject)
	{
		if(m_object == object) return;

		if(prop != NULL)
		{
			RefObject *oldObject = m_object;

			SubFromObject(m_object);
			m_object = object;
			AddToObject(m_object);

			DependencyProperty::funPropertyValueChanged fun = prop->GetValueChangedFun();
			if(fun != NULL)
			{
				PropertyValueChangedEventArgs args;
				args.m_property = prop;
				args.m_isContentChange = false;
				args.m_newObject = object;
				args.m_oldObject = oldObject;
				(belongToObject->*(fun))(args);//pProperty, pv, pOld);
			}
		}
		else
		{
			m_object = object;
		}
	}

	RefObjectPtr m_object;

private:
	nbObject *DynamicCastToObject(RefObject *object);
	void AddToObject(RefObject *object);
	void SubFromObject(RefObject *object);
};

template<class T>
class NB_API PV : public RefPVBase
{
public:
	PV() {}

	void operator = (T *object)
	{
		Set(object);
	}

	operator T * () const
	{
		return (T *)(RefObject *)m_object;
	}

	T * operator ->() const
	{
		return (T *)(RefObject *)m_object;
	}

};

template<class T, class UserT>
class NB_API ImmobilePV : public RefPVBase
{
//Linux不支持，暂时屏蔽		friend UserT;
public:
	ImmobilePV(){}

	operator T * () const
	{
		return (T *)(RefObject *)m_object;
	}

	T * operator ->() const
	{
		return (T *)(RefObject *)m_object;
	}

//Linux不支持，暂时屏蔽	private:
	void operator = (T *object)
	{
		Set(object);
	}
};

class NB_API EnumPVBase : public PVBaseBase
{
	inline void set(int v) {m_value = v;}

	inline int Get() const {return m_value;}
private:
	int m_value;
};

template<class T>
class NB_API RockPV : public RefPVBase
{
public:
	void operator = (const T &v)
	{
		Set(new T(v));
	}

	void operator = (const typename T::t &v)
	{
		Set(new T(v));
	}

	operator T() const
	{
		return *(T *)Get();
	}

	operator typename T::t() const
	{
		T * v = (T *)Get();
		if(v == NULL)
		{
			nb::core::OriginObject::ThrowException("[RockPV]不能获取空值。");
		}
		return *v;
	}

	T * operator -> () const
	{
		return (T *)Get();
	}
};

class ObjectPVsMgr;
}}

//dependency
class NB_API nbObject : public nb::core::RefObject
{
	NB_OBJECT_TYPE_DECLARE();
	friend class nb::core::RefPVBase;
public:
	nbObject(void);
	virtual ~nbObject(void);

	static nb::core::Type *GetType(const std::type_info &info);

public:
	static void *s_pMallocingObject;

	template<class T>
	void SetValue(nb::core::DependencyProperty *pProp, const T &v)
	{
		nb::core::PropertyValue<T> *ps = new nb::core::PropertyValue<T>(v);
		SetBaseValue(pProp, ps);
	}

	template<class T>
	void GetValue(nb::core::DependencyProperty *pProp, T &v) const
	{
		nb::core::PropertyValue<T> *ps = dynamic_cast<nb::core::PropertyValue<T> *>(GetBaseValue(pProp));
		if(ps != NULL)
		{
			v = ps->value();
		}
	}

	void SetBaseValue(nb::core::DependencyProperty *pProp, nb::core::PropertyValueBase *pv);
	nb::core::PropertyValueBase * GetBaseValue(nb::core::DependencyProperty *pProp) const;

	template<class T>
	T GetValue(nb::core::DependencyProperty &prop){return NULL;}

	// 是否已保存有指定的属性值
	bool IsSavedPropertyValue(nb::core::DependencyProperty *pProp) const;

	void SetRefValue(nb::core::DependencyProperty *pProp, RefObject *pv);
	void SetValueValue(nb::core::DependencyProperty *pProp, const nb::core::ValueObject &v, nb::core::PropertyLock *lock=NULL);
	void SetEnumValue(nb::core::DependencyProperty *pProp, int v);

	RefObject * GetRefValue(nb::core::DependencyProperty *pProp) const;
	const nb::core::ValueObject &GetValueValue(nb::core::DependencyProperty *pProp) const;
	int GetEnumValue(nb::core::DependencyProperty *pProp) const;

	nb::core::TypesPropertyValuesStore *GetTypesPropertyValuesStore() const;

	nb::core::PropertyLock * LockPropertyValue(nb::core::DependencyProperty *pProp);

	void GetAllRefProperties(std::list<nb::core::DependencyPropertyPtr> &lst) const;
	void GetAllValueProperties(std::list<nb::core::DependencyPropertyPtr> &lst) const;

	void SetAttachment(nb::core::ObjectAttachmentSymbol *symbol, nb::core::RefObject *value, bool isWeakRef=true);
	nb::core::RefObject * GetAttachment(nb::core::ObjectAttachmentSymbol *symbol) const;

protected:
	void operator = (nbObject &right) {}
	void OnPropertyChanged(const nbObject *pNewValue, const nbObject *pOldValue);
public:
	void NotifyContentChanged();

private:
	nb::core::ObjectAttachmentsMgr * TakeObjectAttachmentsMgr();
	nb::core::ObjectAttachmentsMgr * GetObjectAttachmentsMgr() const {return m_pObjectAttachmentsMgr;}

//	public:
	void AddPV(nb::core::PVBaseBase *pv);
	void SubPV(nb::core::PVBaseBase *pv);
private:

	// 关联的nbEvent
	friend class nbEventBase;
	friend class nbEventPrivate;
	void EventRefAdd(nbEventBase *pEvent);
	void EventRefRelease(nbEventBase *pEvent);

	std::map<nbEventBase *, int> *m_psetEvent;
	nb::core::PropertyValuesMgr *TakePropertyValuesMgr();
	nb::core::PropertyValuesMgr *GetPropertyValuesMgr() const;
	nb::core::PropertyValuesMgr *m_pPropertyValuesMgr;
	nb::core::TypesPropertyValuesStore *m_pTypesPropertyValuesStore;
	nb::core::ObjectAttachmentsMgr *m_pObjectAttachmentsMgr;
	nb::core::ObjectPVsMgr * m_pvs;
};

typedef nbObjectPtrDerive<nbObject, nb::core::RefObjectPtr> nbObjectPtr;
