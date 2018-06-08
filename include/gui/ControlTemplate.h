#pragma once

#include "UIElementFactory.h"
#include "NameRealm.h"

namespace nb { namespace Gui {

class NB_EXPORT ControlTemplate : public nbObject
{
	NB_OBJECT_TYPE_DECLARE();

public:
	ControlTemplate(void);
	virtual ~ControlTemplate(void);

	NB_OBJECT_PROPERTY_DECLARE(VisualTree, UIElementFactory);

	void SetNameRealm(NameRealm *nr) {m_NameRealm = nr;}
	const NameRealmPtr &GetNameRealm() const {return m_NameRealm;}
private:
	NameRealmPtr m_NameRealm;
};

typedef nbObjectPtrDerive<ControlTemplate, nbObjectPtr> ControlTemplatePtr;

}}
