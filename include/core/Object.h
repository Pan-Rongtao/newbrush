#pragma once

#include <map>
#include <stddef.h>

#include "RefObject.h"
#include "ValueObject.h"
#include "DependencyProperty.h"
#include "PropertyValueToucher.h"

namespace nb { namespace Core {
class Type;
}}

class nbEventBase;
class nbEventPrivate;
class Assembly;


#define NB_X_OBJECT_EXTERNAL_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::Core::DependencyProperty * externalProperty_##propertyName; \
	static nb::Core::DependencyProperty * propertyName##Property(); \

#define NB_X_OBJECT_EXTERNAL_PROPERTY_IMPLEMENT(className, propertyName, propertyType) \
	nb::Core::DependencyProperty * className::externalProperty_##propertyName = nb::Core::DependencyProperty::PrepareExternalProperty<className, propertyType>(#propertyName, NULL); \
	nb::Core::DependencyProperty * className::propertyName##Property() {return externalProperty_##propertyName;} \


#define NB_X_OBJECT_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::Core::DependencyProperty * propertyName##Property(); \
	class NB_EXPORT ____##propertyName##PV : public nb::Core::PV< propertyType > \
	{ \
	public: \
		nb::Core::DependencyProperty * GetProperty() const; \
		static nb::Core::DependencyProperty * GetPropertyStatic(); \
		void operator = (propertyType *object);\
	private:\
		static nb::Core::DependencyProperty * const m_prop; \
		nbObject * GetBelongToObject() const; \
	};  \
	____##propertyName##PV propertyName; \


/*#define NB_X_OBJECT_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::Core::DependencyProperty * property_##propertyName; \
	static nb::Core::DependencyProperty * propertyName##Property(); \
	PV< propertyType > propertyName; \ */

#define NB_X_OBJECT_PROPERTY_DECLARE_IMMOBILE(propertyName, propertyType, User) \
	static nb::Core::DependencyProperty * propertyName##Property(); \
	class NB_EXPORT ____##propertyName##PV : public nb::Core::ImmobilePV< propertyType, User > \
	{ \
		friend class User;\
	public: \
		nb::Core::DependencyProperty * GetProperty() const; \
		static nb::Core::DependencyProperty * GetPropertyStatic(); \
	private: \
		void operator = (propertyType *object);\
	private:\
		static nb::Core::DependencyProperty * const m_prop; \
		nbObject * GetBelongToObject() const; \
	};  \
	____##propertyName##PV propertyName; \

/*#define NB_X_OBJECT_PROPERTY_DECLARE_IMMOBILE(propertyName, propertyType, User) \
	static nb::Core::DependencyProperty * property_##propertyName; \
	static nb::Core::DependencyProperty * propertyName##Property(); \
	ImmobilePV< propertyType, User > propertyName; \
	//*/

#define NB_X_OBJECT_PROPERTY_DECLARE_1(propertyName, propertyType) \
	private:\
	static nb::Core::DependencyProperty * property_##propertyName; \
	static nb::Core::DependencyProperty * propertyName##Property(); \
	PV< propertyType > propertyName; \
	private:\

#define NB_X_ROCK_OBJECT_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::Core::DependencyProperty * propertyName##Property(); \
	class NB_EXPORT ____##propertyName##PV : public nb::Core::RockPV< propertyType > \
	{ \
	public: \
		nb::Core::DependencyProperty * GetProperty() const; \
		static nb::Core::DependencyProperty * GetPropertyStatic(); \
		void operator = (propertyType *object);\
		void operator = (const propertyType::t &v) {Set(new propertyType(v), GetPropertyStatic(), GetBelongToObject());}\
	private:\
		static nb::Core::DependencyProperty * const m_prop; \
		nbObject * GetBelongToObject() const; \
	};  \
	____##propertyName##PV propertyName; \

/*#define NB_X_ROCK_OBJECT_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::Core::DependencyProperty * property_##propertyName; \
	static nb::Core::DependencyProperty * propertyName##Property(); \
	RockPV< propertyType > propertyName; \
//*/

/*#define NB_X_OBJECT_PROPERTY_IMPLEMENT(className, propertyName, propertyType, propertyChangedFun) \
	nb::Core::DependencyProperty * className::property_##propertyName = nb::Core::DependencyProperty::PrepareProperty<className, propertyType>((int)(&((className *)(NULL))->propertyName), #propertyName, false, \
			static_cast<nb::Core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::Core::DependencyProperty * className::propertyName##Property() {return property_##propertyName;} \
//*/

#define NB_X_OBJECT_PROPERTY_IMPLEMENT(className, propertyName, propertyType, propertyChangedFun) \
	nb::Core::DependencyProperty * const className::____##propertyName##PV::m_prop = nb::Core::DependencyProperty::PrepareProperty<className, propertyType>((unsigned long)(&((className *)(NULL))->propertyName), #propertyName, false, \
			static_cast<nb::Core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::Core::DependencyProperty * className::propertyName##Property() {return className::____##propertyName##PV::GetPropertyStatic();} \
	nb::Core::DependencyProperty * className::____##propertyName##PV::GetProperty() const {return m_prop;} \
	nb::Core::DependencyProperty * className::____##propertyName##PV::GetPropertyStatic() {return m_prop;} \
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
///offsetof()

/*#define NB_X_OBJECT_PROPERTY_IMPLEMENT_IMMOBILE(className, propertyName, propertyType, propertyChangedFun) \
	nb::Core::DependencyProperty * className::property_##propertyName = nb::Core::DependencyProperty::PrepareProperty<className, propertyType>((int)(&((className *)(NULL))->propertyName), #propertyName, true, \
			static_cast<nb::Core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::Core::DependencyProperty * className::propertyName##Property() {return property_##propertyName;} \
//*/

#define NB_X_OBJECT_PROPERTY_IMPLEMENT_IMMOBILE(className, propertyName, propertyType, propertyChangedFun) \
	nb::Core::DependencyProperty * const className::____##propertyName##PV::m_prop = nb::Core::DependencyProperty::PrepareProperty<className, propertyType>((unsigned long)(&((className *)(NULL))->propertyName), #propertyName, true, \
			static_cast<nb::Core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::Core::DependencyProperty * className::propertyName##Property() {return className::____##propertyName##PV::GetPropertyStatic();} \
	nb::Core::DependencyProperty * className::____##propertyName##PV::GetProperty() const {return m_prop;} \
	nb::Core::DependencyProperty * className::____##propertyName##PV::GetPropertyStatic() {return m_prop;} \
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
	static nb::Core::DependencyPropertyPtr property_##propertyName; \
	static nb::Core::DependencyProperty * Get##propertyName##Property(); \
	nb::Core::PropertyValueToucher< propertyType > propertyName() \
	{ \
		return nb::Core::PropertyValueToucher< propertyType >(this, Get##propertyName##Property()); \
	}\

#define NB_OBJECT_PROPERTY_IMPLEMENT(className, propertyName, propertyType) \
	nb::Core::DependencyPropertyPtr className::property_##propertyName = nb::Core::DependencyProperty::PrepareProperty(#propertyName, typeid(className), typeid(propertyType)); \
	nb::Core::DependencyProperty * className::Get##propertyName##Property() const {return property_##propertyName;} \


#define NB_OBJECT_PROPERTY_IMPLEMENT_EX_1(className, propertyName, propertyType, propertyChangedFun) \
	nb::Core::DependencyPropertyPtr className::property_##propertyName = nb::Core::DependencyProperty::PrepareProperty(#propertyName, typeid(className), typeid(propertyType), \
		static_cast<nb::Core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::Core::DependencyProperty * className::Get##propertyName##Property() {return property_##propertyName;} \


#define NB_OBJECT_PROPERTY_IMPLEMENT_EX(className, propertyName, propertyType, propertyChangedFun) \
	nb::Core::DependencyPropertyPtr className::property_##propertyName = nb::Core::DependencyProperty::PrepareProperty<className, propertyType>(#propertyName, \
		static_cast<nb::Core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::Core::DependencyProperty * className::Get##propertyName##Property() {return property_##propertyName;} \


//#define NB_OBJECT_REF_PROPERTY_DECLARE(propertyName, propertyType) \
//	static nb::Core::DependencyPropertyPtr property_##propertyName; \
//	nb::Core::DependencyProperty * Get##propertyName##Property() const; \
//	RefPropertyValueToucher< propertyType > propertyName() \
//	{ \
//		return RefPropertyValueToucher< propertyType >(this, Get##propertyName##Property()); \
//	}\


#define NB_OBJECT_VALUE_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::Core::DependencyPropertyPtr property_##propertyName; \
	static nb::Core::DependencyProperty * Get##propertyName##Property(); \
	nb::Core::ValuePropertyValueToucher< propertyType > propertyName() \
	{ \
		return nb::Core::ValuePropertyValueToucher< propertyType >(this, Get##propertyName##Property()); \
	}\

#define NB_OBJECT_VALUE_PROPERTY_IMPLEMENT_EX(className, propertyName, propertyType, propertyChangedFun) \
	nb::Core::DependencyPropertyPtr className::property_##propertyName = nb::Core::DependencyProperty::PrepareProperty(#propertyName, typeid(className), typeid(propertyType), \
		static_cast<nb::Core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::Core::DependencyProperty * className::Get##propertyName##Property() const {return property_##propertyName;}

#define NB_OBJECT_VALUE_PROPERTY_IMPLEMENT_EX_1(className, propertyName, propertyType, propertyChangedFun) \
	nb::Core::DependencyPropertyPtr className::property_##propertyName = nb::Core::DependencyProperty::PrepareProperty(#propertyName, typeid(className), typeid(propertyType), \
		static_cast<nb::Core::DependencyProperty::funPropertyValueChanged>(propertyChangedFun)); \
	nb::Core::DependencyProperty * className::propertyName##Property() {return property_##propertyName;}

#define NB_OBJECT_ENUM_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::Core::DependencyPropertyPtr property_##propertyName; \
	static nb::Core::DependencyProperty * Get##propertyName##Property(); \
	nb::Core::EnumPropertyValueToucher< propertyType > propertyName() \
	{ \
		return nb::Core::EnumPropertyValueToucher< propertyType >(this, Get##propertyName##Property()); \
	}\

#define NB_OBJECT_GENERICS_PROPERTY_DECLARE(propertyName) \
	static nb::Core::DependencyPropertyPtr property_##propertyName; \
	nb::Core::DependencyProperty * Get##propertyName##Property() const; \
	GenericsPropertyValueToucher propertyName() \
	{ \
		return GenericsPropertyValueToucher(this, Get##propertyName##Property()); \
	}\

#define NB_OBJECT_ENUM_PROPERTY_DECLARE_NEW(propertyName, propertyType) \
	static nb::Core::DependencyPropertyPtr property_##propertyName; \
	static nb::Core::DependencyProperty * Get##propertyName##Property(); \
	nb::Core::EnumPropertyValueToucher_New< propertyType > propertyName() \
	{ \
		return nb::Core::EnumPropertyValueToucher_New< propertyType >(this, Get##propertyName##Property()); \
	}\


#define NB_OBJECT_EXTERNAL_PROPERTY_DECLARE(propertyName, propertyType) \
	static nb::Core::DependencyPropertyPtr property_##propertyName; \
	static nb::Core::DependencyProperty * Get##propertyName##Property(); \

#define NB_OBJECT_EXTERNAL_PROPERTY_IMPLEMENT(className, propertyName, propertyType) \
	nb::Core::DependencyPropertyPtr className::property_##propertyName = nb::Core::DependencyProperty::PrepareProperty<className, propertyType>(#propertyName, \
		NULL); \
	nb::Core::DependencyProperty * className::Get##propertyName##Property() {return property_##propertyName;} \


namespace nb {	namespace Core {

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
	ValueType GetValue() const{ return m_value;}
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


	class NB_CORE_DECLSPEC_X_INTERFACE PVBaseBase
	{
	public:
		PVBaseBase(){}
		~PVBaseBase(){} // 非虚函数？？原来是没有构造和析构函数的，为了在vs2015上编译通过，添加的


	//	virtual ~PVBaseBase(){}

		//nbDependencyProperty *m_property;
		PropertyLock *m_lock;

		virtual DependencyProperty * GetProperty() const {return NULL;}
		virtual nbObject * GetBelongToObject() const {return NULL;}
	};

	class NB_CORE_DECLSPEC_X_INTERFACE RefPVBase : public PVBaseBase
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
	class NB_EXPORT PV : public RefPVBase
	{
	public:
		PV() {}

		void operator = (T *object)
		{
		//	if(m_object == object) return;
		//	m_object = object;

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
	class NB_EXPORT ImmobilePV : public RefPVBase
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

	class NB_EXPORT EnumPVBase : public PVBaseBase
	{
		inline void set(int v) {m_value = v;}

		inline int Get() const {return m_value;}
	private:
		int m_value;
	};

/*	template<class T>
	class NB_EXPORT EnumPV
	{
		void operator = (T e)
		{
			Set(e);
		}

		operator T() const
		{
			return (T)Get();
		}
	};*/

	template<class T>
	class NB_EXPORT RockPV : public RefPVBase
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
				nb::Core::OriginObject::ThrowException("[RockPV]不能获取空值。");
			}
			return *v;
		}

		T * operator -> () const
		{
			return (T *)Get();
		}

//		bool operator == (int v) const
//		{
//			if(v != 0) throw nbExceptionPtr::GetPtrInstance("此函数限制这只传递参数零。");
//			return Get() == NULL;
//		}

//		bool operator != (int v) const
//		{
//			return !operator == (v);
//		}
	};

	class ObjectPVsMgr;

	//	template<class T>
	//	inline bool operator == (int v, const RockPVx<T> &pv) {return pv.operator == (v);}
}}

//dependency
class NB_CORE_DECLSPEC_X_INTERFACE nbObject : public nb::Core::RefObject
{
	NB_OBJECT_TYPE_DECLARE();

//	typedef void (nbObject::* funPropertyChanged)(nbDependencyProperty *pProperty, PropertyValueBase *pNew, PropertyValueBase *pOld);

	friend class nb::Core::RefPVBase;

public:
	nbObject(void);
	virtual ~nbObject(void);

	virtual void Test();

	static nb::Core::Type *GetType(const std::type_info &info);

public:
	static void *s_pMallocingObject;

	template<class T>
	void SetValue(nb::Core::DependencyProperty *pProp, const T &v)
	{
		nb::Core::PropertyValue<T> *ps = new nb::Core::PropertyValue<T>(v);
		SetBaseValue(pProp, ps);
	}

	template<class T>
	void GetValue(nb::Core::DependencyProperty *pProp, T &v) const
	{
		nb::Core::PropertyValue<T> *ps = dynamic_cast<nb::Core::PropertyValue<T> *>(GetBaseValue(pProp));
		if(ps != NULL)
		{
			v = ps->GetValue();
		}
	}

	void SetBaseValue(nb::Core::DependencyProperty *pProp, nb::Core::PropertyValueBase *pv);
	nb::Core::PropertyValueBase * GetBaseValue(nb::Core::DependencyProperty *pProp) const;

	template<class T>
	T GetValue(nb::Core::DependencyProperty &prop){return NULL;}

	// 是否已保存有指定的属性值
	bool IsSavedPropertyValue(nb::Core::DependencyProperty *pProp) const;

	void SetRefValue(nb::Core::DependencyProperty *pProp, RefObject *pv);
	void SetValueValue(nb::Core::DependencyProperty *pProp, const nb::Core::ValueObject &v, nb::Core::PropertyLock *lock=NULL);
	void SetEnumValue(nb::Core::DependencyProperty *pProp, int v);

	RefObject * GetRefValue(nb::Core::DependencyProperty *pProp) const;
	const nb::Core::ValueObject &GetValueValue(nb::Core::DependencyProperty *pProp) const;
	int GetEnumValue(nb::Core::DependencyProperty *pProp) const;

	nb::Core::TypesPropertyValuesStore *GetTypesPropertyValuesStore() const;

	nb::Core::PropertyLock * LockPropertyValue(nb::Core::DependencyProperty *pProp);

	void GetAllRefProperties(std::list<nb::Core::DependencyPropertyPtr> &lst) const;
	void GetAllValueProperties(std::list<nb::Core::DependencyPropertyPtr> &lst) const;

	void SetAttachment(nb::Core::ObjectAttachmentSymbol *symbol, nb::Core::RefObject *value, bool isWeakRef=true);
	nb::Core::RefObject * GetAttachment(nb::Core::ObjectAttachmentSymbol *symbol) const;

	//待实现
//	void SetKeyTag(RefObject *key, RefObject *value);
//	RefObject * GetKeyTag(RefObject *key) const;


/*	void SetPV(nbDependencyProperty *pProp, RefObject *pv) {SetRefValue(pProp, pv);}

	template<class T>
	void SetRockPV(nbDependencyProperty *pProp, T t)
	{
		PVBaseBase *p = GetPVer(pProp);
		if(p != NULL)
		{
			nb::Core::RockPV<T> *rockPV = dynamic_cast<nb::Core::RockPV<T> *>(p);
			if(rockPV != NULL)
			{
				*rockPV = t;
				return;
			}


			nb::Core::RockAllowNullPV<T> *rockAllowNullPV = dynamic_cast<nb::Core::RockAllowNullPV<T> *>(p);
			if(rockAllowNullPV != NULL)
			{
				*rockAllowNullPV = t;
				return;
			}
		}
		else
		{
//			nb::Core::RefRockValueObject<T> x = new nb::Core::RefRockValueObject<T>(t);
		}
	}*/

	
protected:
//	nbObject(nbObject &right) {}
	void operator = (nbObject &right) {}


	void OnPropertyChanged(const nbObject *pNewValue, const nbObject *pOldValue);
public:
	void NotifyContentChanged();

private:
//	PVBaseBase * GetPVer(nbDependencyProperty *pProp) const;

	nb::Core::ObjectAttachmentsMgr * TakeObjectAttachmentsMgr();
	nb::Core::ObjectAttachmentsMgr * GetObjectAttachmentsMgr() const {return m_pObjectAttachmentsMgr;}

//	public:
	void AddPV(nb::Core::PVBaseBase *pv);
	void SubPV(nb::Core::PVBaseBase *pv);
private:

	// 关联的nbEvent
	friend class nbEventBase;
	friend class nbEventPrivate;
	void EventRefAdd(nbEventBase *pEvent);
	void EventRefRelease(nbEventBase *pEvent);
	std::map<nbEventBase *, int> *m_psetEvent;


	nb::Core::PropertyValuesMgr *TakePropertyValuesMgr();
	nb::Core::PropertyValuesMgr *GetPropertyValuesMgr() const;

	nb::Core::PropertyValuesMgr *m_pPropertyValuesMgr;


	nb::Core::TypesPropertyValuesStore *m_pTypesPropertyValuesStore;

	nb::Core::ObjectAttachmentsMgr *m_pObjectAttachmentsMgr;

	nb::Core::ObjectPVsMgr * m_pvs;

//待实现	nb::Core::ObjectKeyTagsMgr * m_pObjectKeyTagsMgr;
};

class NB_CORE_DECLSPEC_X_INTERFACE TestObject
{
public:
	int a();

};

typedef nbObjectPtrDerive<nbObject, nb::Core::RefObjectPtr> nbObjectPtr;

//#define new DEBUG_NEW
