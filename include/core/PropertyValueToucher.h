#pragma once

#include "Type.h"
#include "ValueObject.h"

namespace nb {	namespace Core {
	
class RefObject;
class PropertyLock;
class NB_CORE_DECLSPEC_X_INTERFACE PropertyValueToucherBase
{
public:
	bool IsRefTypeOfProperty() const;

	PropertyValueToucherBase(nbObject *pObject, DependencyProperty *pProperty)
		: m_pObject(pObject), m_pProperty(pProperty) {}
	virtual ~PropertyValueToucherBase() {}

	void ThrowException(const char *pMessage) const;

	void SetRefValue(DependencyProperty *pProp, RefObject *pv);
	void SetValueValue(DependencyProperty *pProp, const ValueObject &v);
	void SetEnumValue(DependencyProperty *pProp, int v);

	RefObject * GetRefValue(DependencyProperty *pProp) const;
	const ValueObject &GetValueValue(DependencyProperty *pProp) const;
	int GetEnumValue(DependencyProperty *pProp) const;

	bool IsNull() const;

	PropertyLock * Lock();

protected:
	DependencyProperty *m_pProperty;
	nbObject *m_pObject;

};

template<class ValueType>
class NB_EXPORT PropertyValueToucher : public PropertyValueToucherBase
{
public:
	PropertyValueToucher(nbObject *pObject, DependencyProperty *pProperty)
		: PropertyValueToucherBase(pObject, pProperty) {}

	void operator = (ValueType *value)
	{
		if(IsRefTypeOfProperty())
		{
			SetRefValue(m_pProperty, value);
		}
		else
		{
			ThrowException("值对象不能传递存储指针。");
		}
	}

	void operator = (const ValueType &value)
	{
		if(IsRefTypeOfProperty())
		{
			ThrowException("引用对象只能传递存储引用指针。");
		}
		else
		{
			SetValueValue(m_pProperty, value);
		}
	}

	operator const ValueType & () const
	{
		const ValueObject &v = GetValueValue(m_pProperty);
		const ValueType *pv = dynamic_cast<const ValueType *>(&v);
		if(pv == NULL)
		{
			ThrowException("值对象类型错误。");
		}

		return *pv;
	}

	operator ValueType * () const
	{
		RefObject *ref = GetRefValue(m_pProperty);
		if(ref == NULL) return NULL;

		ValueType *pv = dynamic_cast<ValueType *>(ref);
		if(pv == NULL)
		{
			ThrowException("引用值对象类型错误。");
		}
		return pv;
	}

	ValueType * operator ->() const
	{
		return operator ValueType *();
	}
};


template<class ValueType>
class NB_EXPORT ValuePropertyValueToucher : public PropertyValueToucherBase
{
public:
	ValuePropertyValueToucher(nbObject *pObject, DependencyProperty *pProperty)
		: PropertyValueToucherBase(pObject, pProperty) {}

	void operator = (const ValueType &value)
	{
		if(IsRefTypeOfProperty())
		{
			ThrowException("引用对象只能传递存储引用指针。");
		}
		else
		{
			SetValueValue(m_pProperty, value);
		}
	}

	operator const ValueType & () const
	{
		const ValueObject &v = GetValueValue(m_pProperty);
		const ValueType *pv = dynamic_cast<const ValueType *>(&v);
		if(pv == NULL)
		{
			ThrowException("值对象类型错误。");
		}

		return *pv;
	}

	operator const ValueType * () const
	{
		const ValueObject &v = GetValueValue(m_pProperty);
		const ValueType *pv = dynamic_cast<const ValueType *>(&v);
		if(pv == NULL)
		{
			ThrowException("值对象类型错误。");
		}

		return pv;
	}

	const ValueType * operator ->() const
	{
		return operator const ValueType *();
	}
};

template<class ValueType>
class NB_EXPORT RefPropertyValueToucher : public PropertyValueToucherBase
{
public:
	RefPropertyValueToucher(nbObject *pObject, DependencyProperty *pProperty)
		: PropertyValueToucherBase(pObject, pProperty) {}

	void operator = (ValueType *value)
	{
		if(IsRefTypeOfProperty())
		{
			SetRefValue(m_pProperty, value);
		}
		else
		{
			ThrowException("值对象不能传递存储指针。");
		}
	}

	operator ValueType * () const
	{
		RefObject *ref = GetRefValue(m_pProperty);
		if(ref == NULL) return NULL;

		ValueType *pv = dynamic_cast<ValueType *>(ref);
		if(pv == NULL)
		{
			ThrowException("引用值对象类型错误。");
		}
		return pv;
	}

};


template<class ValueType>
class NB_EXPORT EnumPropertyValueToucher : public PropertyValueToucherBase
{
public:
	EnumPropertyValueToucher(nbObject *pObject, DependencyProperty *pProperty)
		: PropertyValueToucherBase(pObject, pProperty) {}

	void operator = (const ValueType &value)
	{
		SetEnumValue(m_pProperty, value);
	}

	operator ValueType () const
	{
		int v = GetEnumValue(m_pProperty);
		return (ValueType)v;
	}

	operator const ValueType * () const
	{
		const ValueObject &v = GetValueValue(m_pProperty);
		const ValueType *pv = dynamic_cast<const ValueType *>(&v);
		if(pv == NULL)
		{
			ThrowException("值对象类型错误。");
		}

		return pv;
	}

	const ValueType * operator ->() const
	{
		return operator const ValueType *();
	}
};

template<class ValueType>
class NB_EXPORT EnumPropertyValueToucher_New : public PropertyValueToucherBase
{
public:
	EnumPropertyValueToucher_New(nbObject *pObject, DependencyProperty *pProperty)
		: PropertyValueToucherBase(pObject, pProperty) {}

	void operator = (const ValueType &value)
	{
		SetRefValue(m_pProperty, new RefEnumObject<ValueType>(value));
	}

	operator ValueType () const
	{
	//	int v = GetEnumValue(m_pProperty);
	//	return (ValueType)v;

		RefEnumObject<ValueType> *obj = dynamic_cast<RefEnumObject<ValueType> * >(GetRefValue(m_pProperty));
		if(obj == NULL)
		{
			ThrowException("枚举值未存储或者存储的类型不对。");
		}

		return *obj;
	}

	operator const ValueType * () const
	{
		const ValueObject &v = GetValueValue(m_pProperty);
		const ValueType *pv = dynamic_cast<const ValueType *>(&v);
		if(pv == NULL)
		{
			ThrowException("值对象类型错误。");
		}

		return pv;
	}

	const ValueType * operator ->() const
	{
		return operator const ValueType *();
	}
};

class NB_EXPORT GenericsPropertyValueToucher : public PropertyValueToucherBase
{
public:
	GenericsPropertyValueToucher(nbObject *pObject, DependencyProperty *pProperty)
		: PropertyValueToucherBase(pObject, pProperty) {}

	template<class T>
	RefPropertyValueToucher<T> RefProp()
	{
		return RefPropertyValueToucher<T>(m_pObject, m_pProperty);
	}

	template<class T>
	ValuePropertyValueToucher<T> ValueProp()
	{
		return ValuePropertyValueToucher<T>(m_pObject, m_pProperty);
	}

	template<class T>
	EnumPropertyValueToucher<T> EnumProp()
	{
		return EnumPropertyValueToucher<T>(m_pObject, m_pProperty);
	}

};

}}
