#include "UIElementFactoryPrivate.h"
#include "gui/Panel.h"
#include "core/Exception.h"

using namespace nb::Gui;

using namespace nb::Core;
using namespace nb::System;

UIElementFactoryPrivate::UIElementFactoryPrivate(UIElementFactory *owner, Type *type)
	: m_owner(owner)
	, m_type(type)
{
}

UIElementFactoryPrivate::~UIElementFactoryPrivate(void)
{
//	std::map<nbDependencyPropertyPtr, PropValueInfo *>::iterator itor = m_PropValues.begin();
//	for(; itor != m_PropValues.end(); itor++)
//	{
//		PropValueInfo *info = itor->second;
//		delete info;
//	}
}

void UIElementFactoryPrivate::AppendChild(UIElementFactory *factory, const char *name)
{
	m_childs.push_back(factory);

	if(name != NULL && name[0] != '\0')
	{
		std::map<std::string, UIElementFactoryPtr>::iterator itor = m_mapNameChilds.find(name);
		if(itor != m_mapNameChilds.end())
		{
			throw ExceptionPtr::GetPtrInstance("名称已存在，不能使用相同的名称。");
		}

		m_mapNameChilds[name] = factory;
	}
}

UIElement * UIElementFactoryPrivate::CreateOwnerElement() const
{
	nb::Core::OriginObject * obj = m_type->GetAssembly()->CreateObjectInstance();
	UIElement * element = dynamic_cast<UIElement *>(obj);

	std::map<DependencyPropertyPtr, PropValueInfo>::const_iterator itorPV = m_PropValues.begin();
	for(; itorPV != m_PropValues.end(); itorPV++)
	{
		const PropValueInfo &info = itorPV->second;
		ObjectFactory *of = dynamic_cast<ObjectFactory *>((RefObject *)info.m_value);
		if(of != NULL)
		{
			element->SetRefValue(itorPV->first, of->CreateObject());
		}
		else
		{
			element->SetRefValue(itorPV->first, info.m_value);
		}
	}


	//这么模式需要淘汰掉
	std::list<DependencyPropertyPtr> lst;
	m_owner->GetAllRefProperties(lst);
	
	std::list<DependencyPropertyPtr>::iterator itor = lst.begin();
	for(; itor != lst.end(); itor++)
	{
		RefObject *obj = m_owner->GetRefValue(*itor);
		element->SetRefValue(*itor, obj);
	}

	lst.clear();
	m_owner->GetAllValueProperties(lst);
	itor = lst.begin();
	for(; itor != lst.end(); itor++)
	{
		const ValueObject &v = m_owner->GetValueValue(*itor);
		element->SetValueValue(*itor, v);
	}

	return element;
}

UIElementPtr UIElementFactoryPrivate::CreateElement() const
{
/*	UIElement *element = CreateOwnerElement();

	Panel *panel = dynamic_cast<Panel *>(element);

	if(panel != NULL)
	{
		std::list<UIElementFactoryPtr>::const_iterator itor = m_childs.begin();
		for(; itor != m_childs.end(); itor++)
		{
			UIElementPtr child = (*itor)->CreateElement();
			panel->AddChild(child);
		}
	}

	return element;*/

	return NULL;
}

void UIElementFactoryPrivate::SetElementPropertyValue(DependencyProperty *prop, nb::Core::RefObject *value, const char *name)
{
	PropValueInfo info;
	info.m_value = value;
	if(name != NULL) info.m_name = name;
	m_PropValues[prop] = info;
}
