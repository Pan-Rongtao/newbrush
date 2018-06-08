#include "PropertyValuesMgr.h"
#include "core/Exception.h"
#include "core/Type.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace nb::Core;

PropertyValuesMgr::PropertyValuesMgr(void)
{
	///这里的nb::Core命名空间是哪里来的？？？这个异常时测试使用	throw ExceptionPtr::GetPtrInstance("存储数据时，锁验证失败。");
}

PropertyValuesMgr::~PropertyValuesMgr(void)
{
	Clear();
}

void PropertyValuesMgr::Clear()
{
	std::map<DependencyPropertyPtr, PropertyValueBase *>::iterator itor = m_propertyValues.begin();
	for(; itor != m_propertyValues.end(); itor++)
	{
		PropertyValueBase *pCell = itor->second;
		delete pCell;
	}

	m_propertyValues.clear();


	std::map<DependencyPropertyPtr, ValueObject *>::iterator itorValue = m_ValueValues.begin();
	for(; itorValue != m_ValueValues.end(); itorValue++)
	{
		OriginObject *pObject = itorValue->second;
		delete pObject;
	}

	m_ValueValues.clear();


	m_RefValues.clear();
}

nbObject * PropertyValuesMgr::GetPtrPropertyValue()
{
	return NULL;
}

void PropertyValuesMgr::SetPtrPropertyValue(DependencyProperty *pProperty, nbObject *pValue)
{
/*	std::map<DependencyPropertyPtr, PropertyStorageCellBase *>::iterator itor = m_propertyValues.find(pProperty);
	PtrPropertyStorageCell *pCell;
	if(itor == NULL)
	{
		pCell = new PtrPropertyStorageCell();
		m_propertyValues[pProperty] = pCell;
	}
	else
	{
		pCell = dynamic_cast<PtrPropertyStorageCell *>(itor->second);
		NB_THROW_EXCEPTION("pProperty并不是指针类型。");
	}

	//还没有判断存储的类型与Property指定的类型是否相符合

	pCell->m_pValue = pValue;*/
}

void PropertyValuesMgr::SaveRefValue(DependencyProperty *pProperty, RefObject *pv, nbObject *pObject, PropertyLock *lock)
{
	if(!TestLock(pProperty, lock))
	{
		NB_THROW_EXCEPTION("存储数据时，锁验证失败。");
	}

	RefObject *pOld = NULL;

	std::map<DependencyPropertyPtr, RefObjectPtr>::iterator itor = m_RefValues.find(pProperty);
	if(itor != m_RefValues.end())
	{
		pOld = itor->second.GetRealize();
		if(pOld == pv) return;

		itor->second = pv;
	}
	else
	{
		m_RefValues[pProperty] = pv;
	}


	if(pOld != NULL)
	{
//		DependencyProperty::funPropertyChanged fun = pProperty->GetChangedFun();
//		if(fun != NULL)
//		{
//			(pObject->*(fun))(pProperty, pv, pOld);
//		}

//		delete pOld;
	}

	// 发出改变消息
	DependencyProperty::funPropertyValueChanged fun = pProperty->GetValueChangedFun();
	if(fun != NULL)
	{
		PropertyValueChangedEventArgs args;
		args.m_property = pProperty;
		args.m_isContentChange = false;
		args.m_newObject = pv;
		args.m_oldObject = pOld;
//		(pObject->*(fun))(args);//pProperty, pv, pOld);
	}
}

RefObject * PropertyValuesMgr::GetRefValue(DependencyProperty *pProp) const
{
	std::map<DependencyPropertyPtr, RefObjectPtr>::const_iterator itor = m_RefValues.find(pProp);
	if(itor == m_RefValues.end())
	{
		return NULL;
	}
	else
	{
		return itor->second.GetRealize();
	}
}

void PropertyValuesMgr::SaveValueValue(DependencyProperty *pProperty, const ValueObject &v, nbObject *pObject, PropertyLock *lock)
{
	if(!TestLock(pProperty, lock))
	{
		NB_THROW_EXCEPTION("存储数据时，锁验证失败。");
	}

	const ValueObject *pxxx = &v;

	ValueObject *pOld = NULL;
	ValueObject *pNew;

	std::map<DependencyPropertyPtr, ValueObject *>::iterator itor = m_ValueValues.find(pProperty);
	if(itor != m_ValueValues.end())
	{
		pOld = itor->second;
	//	if(*pOld == v) return;

		 //判断是否相等，如果相等，则返回，不做变动
		Type::IsEqualTypeObjectFun fun = pProperty->GetElementType()->GetIsEqualObjectFun();
		if(fun != NULL)
		{
			if(fun(v, *pOld)) return;
		}

	//	nbType::CopyObjectFun funCopy = pProperty->GetElementType()->GetCopyObjectFun();
	//	if(funCopy == NULL)
	//	{
	//		NB_THROW_EXCEPTION("在保存属性值时失败，原因是缺少属性的复制函数。");
	//	}
	//	funCopy(*pOld, v);


		OriginObject *pOriginObject = pProperty->GetElementType()->GetAssembly()->CreateObjectInstance(v);
		if(pOriginObject == NULL)
		{
			NB_THROW_EXCEPTION("构建值对象失败。");
		}

		pNew = dynamic_cast<ValueObject *>(pOriginObject);
		if(pNew == NULL)
		{
			delete pOriginObject;
			NB_THROW_EXCEPTION("将对象从原始对象转换为值对象失败。");
		}

		m_ValueValues[pProperty] = pNew;
	}
	else
	{
		OriginObject *pOriginObject = pProperty->GetElementType()->GetAssembly()->CreateObjectInstance(v);
		if(pOriginObject == NULL)
		{
			NB_THROW_EXCEPTION("构建值对象失败。");
		}

		pNew = dynamic_cast<ValueObject *>(pOriginObject);
		if(pNew == NULL)
		{
			delete pOriginObject;
			NB_THROW_EXCEPTION("将对象从原始对象转换为值对象失败。");
		}

		m_ValueValues[pProperty] = pNew;
	}


	// 发出改变消息
	DependencyProperty::funPropertyValueChanged fun = pProperty->GetValueChangedFun();
	if(fun != NULL)
	{
		PropertyValueChangedEventArgs args;
		args.m_property = pProperty;
		args.m_isContentChange = false;
		args.m_newObject = pNew;
		args.m_oldObject = pOld;
		(pObject->*(fun))(args);//pProperty, pNew, pOld);
	}

	delete pOld;
}

const ValueObject &PropertyValuesMgr::GetValueValue(DependencyProperty *pProp) const
{
	std::map<DependencyPropertyPtr, ValueObject *>::const_iterator itor = m_ValueValues.find(pProp);
	if(itor == m_ValueValues.end())
	{
		NB_THROW_EXCEPTION("指定的属性尚未存储有值对象。");
	}
	
	return *itor->second;
}

void PropertyValuesMgr::SaveValue(DependencyProperty *pProperty, PropertyValueBase *pv, nbObject *pObject, PropertyLock *lock)
{
	if(!TestLock(pProperty, lock))
	{
		NB_THROW_EXCEPTION("存储数据时，锁验证失败。");
	}

	PropertyValueBase *pOld = NULL;

	std::map<DependencyPropertyPtr, PropertyValueBase *>::iterator itor = m_propertyValues.find(pProperty);
	if(itor != m_propertyValues.end())
	{
		if(m_propertyValues[pProperty]->Equal(*pv))
		{
			delete pv;
			return;
		}

		pOld = m_propertyValues[pProperty];
	}
	m_propertyValues[pProperty] = pv;

	if(pOld != NULL)
	{
		DependencyProperty::funPropertyChanged_Old fun = pProperty->GetChangedFun_Old();
		if(fun != NULL)
		{
			(pObject->*(fun))(pProperty, pv, pOld);
		}

		delete pOld;
	}
}

PropertyValueBase * PropertyValuesMgr::GetValue(DependencyProperty *pProperty) const
{
	std::map<DependencyPropertyPtr, PropertyValueBase *>::const_iterator itor = m_propertyValues.find(pProperty);
	if(itor == m_propertyValues.end())
	{
		return NULL;
	}
	else
	{
		return itor->second;
	}
}

bool PropertyValuesMgr::IsSavedPropertyValue(DependencyProperty *prop) const
{
	if(m_RefValues.find(prop) != m_RefValues.end()) return true;
	if(m_EnumValues.find(prop) != m_EnumValues.end()) return true;
	return m_ValueValues.find(prop) != m_ValueValues.end();
}


void PropertyValuesMgr::SaveEnumValue(DependencyProperty *pProperty, int v, PropertyLock *lock)
{
	if(!TestLock(pProperty, lock))
	{
		NB_THROW_EXCEPTION("存储数据时，锁验证失败。");
	}

//	ValueObject *pOld = NULL;
//	ValueObject *pNew;

	std::map<DependencyPropertyPtr, int>::iterator itor = m_EnumValues.find(pProperty);
	if(itor != m_EnumValues.end())
	{
		int old = itor->second;

		 //判断是否相等，如果相等，则返回，不做变动
		if(old == v) return;

		m_EnumValues[pProperty] = v;
	}
	else
	{
		m_EnumValues[pProperty] = v;
	}


	// 发出改变消息
//	DependencyProperty::funPropertyValueChanged fun = pProperty->GetValueChangedFun();
//	if(fun != NULL)
//	{
//		(pObject->*(fun))(pProperty, pNew, pOld);
//	}

}

int PropertyValuesMgr::GetEnumValue(DependencyProperty *pProperty) const
{
	std::map<DependencyPropertyPtr, int>::const_iterator itor = m_EnumValues.find(pProperty);
	if(itor == m_EnumValues.end())
	{
		NB_THROW_EXCEPTION("指定的属性尚未存储有枚举对象。");
	}
	else
	{
		return itor->second;
	}
}

PropertyLock * PropertyValuesMgr::LockProperty(DependencyProperty *prop)
{
	if(IsLockedProperty(prop))
	{
		NB_THROW_EXCEPTION("属性已被锁定，无法重复加锁。");
	}

	PropertyLock *lock = new PropertyLock();
	m_propertyLocks[prop] = lock;

	return lock;
}

bool PropertyValuesMgr::IsLockedProperty(DependencyProperty *prop) const
{
	return m_propertyLocks.find(prop) != m_propertyLocks.end();
}

PropertyLock * PropertyValuesMgr::GetPropertyLock(DependencyProperty *prop) const
{
	std::map<DependencyPropertyPtr, PropertyLockPtr>::const_iterator itor = m_propertyLocks.find(prop);
	if(itor == m_propertyLocks.end()) return NULL;
	else return itor->second;
}

bool PropertyValuesMgr::TestLock(DependencyProperty *prop, const PropertyLock *lock) const
{
	std::map<DependencyPropertyPtr, PropertyLockPtr>::const_iterator itor = m_propertyLocks.find(prop);
	if(itor == m_propertyLocks.end()) return true;

	return lock == itor->second;
}

void PropertyValuesMgr::GetAllRefProperties(std::list<DependencyPropertyPtr> &lst) const
{
	lst.clear();

	std::map<DependencyPropertyPtr, RefObjectPtr>::const_iterator itor = m_RefValues.begin();
	for(; itor != m_RefValues.end(); itor++)
	{
		lst.push_back(itor->first);
	}
}

void PropertyValuesMgr::GetAllValueProperties(std::list<DependencyPropertyPtr> &lst) const
{
	lst.clear();

	std::map<DependencyPropertyPtr, ValueObject *>::const_iterator itor = m_ValueValues.begin();
	for(; itor != m_ValueValues.end(); itor++)
	{
		lst.push_back(itor->first);
	}
}
