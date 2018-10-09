#pragma once
#include "ValueObject.h"

namespace nb { namespace core {

class Type;
class DependencyProperty;
class RefObject;

class TypesPropertyValuesStorePrivate;
class NB_API TypesPropertyValuesStore
{
public:
	TypesPropertyValuesStore(void);
	virtual ~TypesPropertyValuesStore(void);

	void SaveRefValue(const Type *type, DependencyProperty *prop, RefObject *pv);
	void SaveValueValue(const Type *type, DependencyProperty *prop, const ValueObject &v);

	RefObject * GetRefValue(const Type *type, DependencyProperty *prop) const;
	const ValueObject &GetValueValue(const Type *type, DependencyProperty *prop) const;

	bool IsSavedValue(const Type *type, DependencyProperty *prop) const;

	inline TypesPropertyValuesStorePrivate * GetPrivate() const {return m_pPrivate;}

private:
	TypesPropertyValuesStorePrivate *m_pPrivate;
};

}}
