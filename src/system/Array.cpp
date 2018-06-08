#include "system/Array.h"
#include "core/ObjectAttachmentSymbol.h"
#include "core/Exception.h"

#include <vector>

using namespace nb::System;

NB_OBJECT_NO_ASSEMBLY_TYPE_IMPLEMENT(ObjectArrayBase, nbObject);
//NB_OBJECT_TYPE_IMPLEMENT(ObjectArrayItemBase, nbObject, NULL, NULL);

namespace nb { namespace System {
class ObjectArrayBasePrivate
{
public:
	std::vector<nb::Core::RefObjectPtr> m_items;
	static Core::ObjectAttachmentSymbolPtr m_symbol;
};

Core::ObjectAttachmentSymbolPtr ObjectArrayBasePrivate::m_symbol = new Core::ObjectAttachmentSymbol();

}}


ObjectArrayBase::ObjectArrayBase(void)
{
	m_private = new ObjectArrayBasePrivate;
}

ObjectArrayBase::~ObjectArrayBase(void)
{
	delete m_private;
}

int ObjectArrayBase::GetCount() const
{
	return (int)GetPrivate()->m_items.size();
}

void ObjectArrayBase::Clear()
{
	if(GetPrivate()->m_items.empty()) return;

	int count = GetCount();
	for(int i=0; i<count; i++)
	{
//		ObjectArrayItemBase *item = dynamic_cast<ObjectArrayItemBase *>((RefObject *)GetPrivate()->m_items[i]);
//		if(item != NULL) item->m_belongToArray = NULL;

		nbObject *obj = dynamic_cast<nbObject *>((RefObject *)GetPrivate()->m_items[i]);
		if(obj != NULL) obj->SetAttachment(ObjectArrayBasePrivate::m_symbol, NULL);
	}

	GetPrivate()->m_items.clear();
	OnChanged();
}

void ObjectArrayBase::RemoveAt(int index)
{
//	ObjectArrayItemBase *item = dynamic_cast<ObjectArrayItemBase *>((RefObject *)GetPrivate()->m_items[index]);
//	if(item != NULL) item->m_belongToArray = NULL;

	nbObject *obj = dynamic_cast<nbObject *>((RefObject *)GetPrivate()->m_items[index]);
	if(obj != NULL) obj->SetAttachment(ObjectArrayBasePrivate::m_symbol, NULL);

	GetPrivate()->m_items.erase(GetPrivate()->m_items.begin() + index);
	OnChanged();
}

void ObjectArrayBase::AddBase(RefObject *object)
{
//	ObjectArrayItemBase *item = dynamic_cast<ObjectArrayItemBase *>(object);
//	if(item != NULL) item->m_belongToArray = this;

	nbObject *obj = dynamic_cast<nbObject *>(object);
	if(obj != NULL)
	{
		if(obj->GetAttachment(ObjectArrayBasePrivate::m_symbol) != NULL)
		{
			NB_THROW_EXCEPTION("对象已加入ObjectArray，不能重复加入到其它的ObjectArray。");
		}

		obj->SetAttachment(ObjectArrayBasePrivate::m_symbol, this);
	}

	GetPrivate()->m_items.push_back(object);
	OnChanged();
}

void ObjectArrayBase::InsertBase(int index, RefObject *object)
{
//	ObjectArrayItemBase *item = dynamic_cast<ObjectArrayItemBase *>(object);
//	if(item != NULL) item->m_belongToArray = this;

	nbObject *obj = dynamic_cast<nbObject *>(object);
	if(obj != NULL)
	{
		if(obj->GetAttachment(ObjectArrayBasePrivate::m_symbol) != NULL)
		{
			NB_THROW_EXCEPTION("对象已加入ObjectArray，不能重复加入到其它的ObjectArray。");
		}

		obj->SetAttachment(ObjectArrayBasePrivate::m_symbol, this);
	}

	GetPrivate()->m_items.insert(GetPrivate()->m_items.begin() + index, object);
	OnChanged();
}

nb::Core::RefObject * ObjectArrayBase::GetAt(int index) const
{
	return GetPrivate()->m_items[index];
}

nb::Core::InterfaceBase * ObjectArrayBase::GetInterfaceOverride(const std::type_info &type)
{
	std::string typeName = type.name();

	if(typeName == typeid(IArray).name())
	{
		return dynamic_cast<IArray *>(this);
	}
	else
	{
		return NULL;
	}
}

ObjectArrayBase * ObjectArrayBase::FindObjectBelongToArray(nbObject *object)
{
	return (ObjectArrayBase *)object->GetAttachment(ObjectArrayBasePrivate::m_symbol);
}
