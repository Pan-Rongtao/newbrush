#pragma once

#include <list>
#include "gui/UIElementFactory.h"
#include "core/ObjectFactory.h"

namespace nb { namespace Gui {

class UIElementFactory;
class UIElementFactoryPrivate
{
public:
	UIElementFactoryPrivate(UIElementFactory *owner, Core::Type *type);
	virtual ~UIElementFactoryPrivate(void);

	void AppendChild(UIElementFactory *factory, const char *name);

	void SetElementPropertyValue(Core::DependencyProperty *prop, nb::Core::RefObject *value, const char *name);

	UIElementPtr CreateElement() const;

private:
	struct PropValueInfo
	{
		nb::Core::RefObjectPtr m_value;
		std::string m_name;
	};

private:
	UIElement * CreateOwnerElement() const;

	UIElementFactory *m_owner;
	std::list<UIElementFactoryPtr> m_childs;
	std::map<std::string, UIElementFactoryPtr> m_mapNameChilds;

//	std::map<nbDependencyProperty *, Core::RefObject> m_PropValues;
//	std::map<std::string, Core::RefObject> m_mapNameProps;

	std::map<Core::DependencyPropertyPtr, PropValueInfo> m_PropValues;

	Core::Type *m_type;
};

}}
