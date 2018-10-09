#pragma once
#include <map>
#include "core/ValueObject.h"
#include "PropertyValuesMgr.h"

namespace nb { namespace core {

class Type;
class DependencyProperty;
class RefObject;
class PropertyValuesMgr;
class TypesPropertyValuesStorePrivate
{
public:
	TypesPropertyValuesStorePrivate(void);
	~TypesPropertyValuesStorePrivate(void);

	inline void SaveRefValue(const Type *type, DependencyProperty *prop, RefObject *pv)
	{
		TakeStore(type)->SaveRefValue(prop, pv, NULL);
	}

	inline void SaveValueValue(const Type *type, DependencyProperty *prop, const ValueObject &v)
	{
		TakeStore(type)->SaveValueValue(prop, v, NULL);
	}

	RefObject * GetRefValue(const Type *type, DependencyProperty *prop) const;
	const ValueObject &GetValueValue(const Type *type, DependencyProperty *prop) const;

	bool IsSavedValue(const Type *type, DependencyProperty *prop) const;

	PropertyValuesMgr * GetStore(const Type *type) const;
	PropertyValuesMgr * TakeStore(const Type *type);

private:
	std::map<const Type *, PropertyValuesMgr *> m_typesStore;
};

}}
