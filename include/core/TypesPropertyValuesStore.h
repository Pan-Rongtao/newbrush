#pragma once

#include <map>
#include "ValueObject.h"
#include <vector>


namespace nb { namespace Core {

class Type;
class DependencyProperty;
class RefObject;

class TypesPropertyValuesStorePrivate;
class NB_CORE_DECLSPEC_X_INTERFACE TypesPropertyValuesStore
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
