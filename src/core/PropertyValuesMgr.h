#pragma once
#include <map>
#include <list>
#include "core/DependencyProperty.h"
#include "core/Object.h"
#include "core/ValueObject.h"
#include "core/RefObject.h"
#include "core/PropertyLock.h"

namespace nb {	namespace core {


class PropertyValuesMgr
{
public:
	PropertyValuesMgr(void);
	virtual ~PropertyValuesMgr(void);

	void SetPtrPropertyValue(DependencyProperty *pProperty, nbObject *pValue);

	template<class ValueType>
	void SetPropertyValue(DependencyProperty *pProperty, ValueType &value){}


	nbObject * GetPtrPropertyValue();

	void SaveRefValue(DependencyProperty *pProperty, RefObject *pv, nbObject *pObject, PropertyLock *lock=NULL);
	RefObject * GetRefValue(DependencyProperty *pProp) const;

	void SaveValueValue(DependencyProperty *pProperty, const ValueObject &v, nbObject *pObject, PropertyLock *lock=NULL);
	const ValueObject &GetValueValue(DependencyProperty *pProp) const;

	void SaveValue(DependencyProperty *pProperty, PropertyValueBase *pv, nbObject *pObject, PropertyLock *lock=NULL);
	PropertyValueBase *GetValue(DependencyProperty *pProperty) const;

	void SaveEnumValue(DependencyProperty *pProperty, int v, PropertyLock *lock=NULL);
	int GetEnumValue(DependencyProperty *pProperty) const;
	
	bool IsSavedPropertyValue(DependencyProperty *prop) const;

	PropertyLock * LockProperty(DependencyProperty *prop);
	bool IsLockedProperty(DependencyProperty *prop) const;
	PropertyLock * GetPropertyLock(DependencyProperty *prop) const;

	bool TestLock(DependencyProperty *prop, const PropertyLock *lock) const;

	void Clear();

	void GetAllRefProperties(std::list<DependencyPropertyPtr> &lst) const;
	void GetAllValueProperties(std::list<DependencyPropertyPtr> &lst) const;

private:
	std::map<DependencyPropertyPtr, PropertyValueBase *> m_propertyValues;

	std::map<DependencyPropertyPtr, RefObjectPtr> m_RefValues;
	std::map<DependencyPropertyPtr, ValueObject *> m_ValueValues;
	std::map<DependencyPropertyPtr, int> m_EnumValues;

	std::map<DependencyPropertyPtr, PropertyLockPtr> m_propertyLocks;
};

}}
