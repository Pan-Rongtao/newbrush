#include "gui/UIElementFactory.h"
#include "gui/NameRealm.h"
#include "UIElementFactoryPrivate.h"
#include "system/String.h"

using namespace nb::Gui;

using namespace nb::Core;
using namespace nb::System;

UIElementFactory::NameRealmCreateObjectResponser::NameRealmCreateObjectResponser()
	: m_nameRealm(new NameRealm)
{
}

void UIElementFactory::NameRealmCreateObjectResponser::OnCreatedObject(ObjectFactory *factory, RefObject *object)
{
	//if(m_nameRealm == NULL) return;

	nbObject *x = dynamic_cast<nbObject *>(object);
	if(x == NULL) return;

//	m_nameRealm->AddObject(object);

//	NameRealm *nr = dynamic_cast<NameRealm *>(factory->GetAttachment(NameRealm::GetObjectAttachmentSymbol()));
//	if(nr == NULL) return;

	NameRealm *factoryNameRealm = NULL;
	nb::System::String *name = NULL;
	NameRealm::FindNameRealm(factory, factoryNameRealm, name);

	if(name == NULL) m_nameRealm->AddObject(x);
	else m_nameRealm->AddObject(x, name->ToUtf8().GetData());

//	nr->RemoveObject(factory);

	//x->SetAttachment(NameRealm::GetObjectAttachmentSymbol(), NULL);

//	m_nameRealm->AddObject(object);
	//m_nameRealm->FindObject("");

}

NB_OBJECT_NO_ASSEMBLY_TYPE_IMPLEMENT(UIElementFactory, ObjectBelongingFactory);

UIElementFactory::UIElementFactory(Type *type)
	: ObjectBelongingFactory(type)
{
	m_private = new UIElementFactoryPrivate(this, type);
}

UIElementFactory::~UIElementFactory(void)
{
	delete m_private;
}

void UIElementFactory::AppendChild(UIElementFactory *factory, const char *name)
{
	GetPrivate()->AppendChild(factory, name);
}

UIElementFactoryPrivate * UIElementFactory::GetPrivate() const
{
	return m_private;
}

UIElementPtr UIElementFactory::CreateElement(NameRealm *nameRealm)
{
	NameRealmCreateObjectResponser responser;
//	responser.m_nameRealm = nameRealm;

	RefObjectPtr obj = ObjectBelongingFactory::CreateObject(&responser);
	UIElementPtr element = obj.DynamicCast<UIElement *>();
	return element;

//	return GetPrivate()->CreateElement();

/*	nb::Core::OriginObject * obj = m_type->GetAssembly()->CreateObjectInstance();
	UIElement * element = dynamic_cast<UIElement *>(obj);

	std::list<nbDependencyPropertyPtr> lst;
	GetAllRefProperties(lst);
	
	std::list<nbDependencyPropertyPtr>::iterator itor = lst.begin();
	for(; itor != lst.end(); itor++)
	{
		RefObject *obj = GetRefValue(*itor);
		element->SetRefValue(*itor, obj);
	}

	lst.clear();
	GetAllValueProperties(lst);
	itor = lst.begin();
	for(; itor != lst.end(); itor++)
	{
		const ValueObject &v = GetValueValue(*itor);
		element->SetValueValue(*itor, v);
	}

	return element;*/
}

void UIElementFactory::SetElementPropertyValue(DependencyProperty *prop, nb::Core::RefObject *value, const char *name)
{
	GetPrivate()->SetElementPropertyValue(prop, value, name);
}
