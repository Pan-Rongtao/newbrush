#pragma once
#include <string>
#include "RefObject.h"

class nbObject;

namespace nb { namespace core {

class Type;
class DependencyProperty;
class PropertyValueBase;
class DependencyPropertyInternal;

class PropertyValueChangedEventArgs
{
public:
	DependencyProperty *m_property;
	bool m_isContentChange;
	OriginObject *m_newObject;
	OriginObject *m_oldObject;
};

class NB_API DependencyProperty : public RefObject
{
	NB_OBJECT_TYPE_DECLARE();

	friend class ::nbObject;

public:
	typedef void (nbObject::* funPropertyChanged_Old)(DependencyProperty *pProperty, PropertyValueBase *pNew, PropertyValueBase *pOld);
	typedef void (nbObject::* funPropertyValueChanged_Old)(DependencyProperty *pProperty, OriginObject *pNew, OriginObject *pOld);

	typedef void (nbObject::* funPropertyValueChanged)(PropertyValueChangedEventArgs &args);

	DependencyProperty(void);
	virtual ~DependencyProperty(void);

	Type * GetElementType() const;

	funPropertyChanged_Old GetChangedFun_Old() const {return m_funPropertyChanged_Old;}
	funPropertyValueChanged GetValueChangedFun() const {return m_funPropertyValueChanged;}

	static DependencyProperty * PrepareProperty(const std::string &key, const std::type_info &type, const std::type_info &propertyType, funPropertyValueChanged fun=NULL);
	static DependencyProperty * PrepareProperty(const char *pkey, const std::type_info &type, const std::type_info &propertyType, funPropertyValueChanged fun=NULL);
	static DependencyProperty * PrepareProperty(int offset, const char *pkey, const std::type_info &type, const std::type_info &propertyType, bool isImmobile, funPropertyValueChanged fun);
	static DependencyProperty * PrepareExternalProperty(const char *pkey, const std::type_info &type, const std::type_info &propertyType, funPropertyValueChanged fun=NULL);

	template<class T, class propT>
	static DependencyProperty * PrepareProperty(const char *pkey, funPropertyValueChanged fun=NULL)
	{
		return PrepareProperty(pkey, typeid(T), typeid(propT), fun);
	}

	template<class T, class propT>
	static DependencyProperty * PrepareProperty(int offset, const char *pkey, bool isImmobile, funPropertyValueChanged fun)
	{
		return PrepareProperty(offset, pkey, typeid(T), typeid(propT), isImmobile, fun);
	}

	template<class T, class propT>
	static DependencyProperty * PrepareExternalProperty(const char *pkey, funPropertyValueChanged fun=NULL)
	{
		return PrepareExternalProperty(pkey, typeid(T), typeid(propT), fun);
	}

	static size_t GetPreparePropertyCount(const std::string & typeName);

	std::string GetName() const {return m_name;}
	bool IsImmobile() const {return m_isImmobile;}

private:
	Type *m_pType;
	Type *m_pElementType;

	std::string m_name;
	int m_offset;
	int m_index;
	bool m_isImmobile;

	funPropertyChanged_Old m_funPropertyChanged_Old;
	funPropertyValueChanged m_funPropertyValueChanged;

	friend class DependencyPropertyInternal;
	friend class Type;
};

class NB_API DependencyPropertyPtr : public nbObjectPtrDerive<DependencyProperty, RefObjectPtr>
{
public:
	DependencyPropertyPtr(){}
	DependencyPropertyPtr(DependencyProperty *pObject) : nbObjectPtrDerive(pObject){}
	virtual ~DependencyPropertyPtr(){}
};

}}
