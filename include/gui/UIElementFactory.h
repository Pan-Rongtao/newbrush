#pragma once

#include "gui/UIElement.h"
#include "core/Type.h"
#include "core/ObjectFactory.h"
#include "core/DependencyProperty.h"
#include "system/ObjectBelongingFactory.h"

namespace nb { namespace Gui {

class UIElementFactoryPrivate;
class NameRealm;

class NB_EXPORT UIElementFactory : public nb::System::ObjectBelongingFactory
{
	NB_OBJECT_TYPE_DECLARE();

	class NameRealmCreateObjectResponser : public nb::Core::ObjectFactoryCreateObjectResponser
	{
	public:
		NameRealmCreateObjectResponser();

	private:
		void OnCreatedObject(ObjectFactory *factory, RefObject *object);
		Core::RefObjectPtrT<NameRealm> m_nameRealm;
	};

public:
	UIElementFactory(Core::Type *type);
	virtual ~UIElementFactory(void);

	void AppendChild(UIElementFactory *factory, const char *name=NULL);

	UIElementFactoryPrivate * GetPrivate() const;

	UIElementPtr CreateElement(NameRealm *nameRealm);

	void SetElementPropertyValue(Core::DependencyProperty *prop, nb::Core::RefObject *value, const char *name=NULL);

private:
	UIElementFactoryPrivate *m_private;

};


template<class T>
class UIElementFactoryT : public UIElementFactory
{
public:
	UIElementFactoryT() : UIElementFactory(Core::Type::GetType<T>()){}
};

typedef nbObjectPtrDerive<UIElementFactory, nb::System::ObjectBelongingFactoryPtr> UIElementFactoryPtr;

}}
