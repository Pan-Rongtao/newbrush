#include "gui/NameRealm.h"
#include "core/Exception.h"
#include "core/ObjectAttachmentSymbol.h"
#include "system/String.h"

using namespace nb::Gui;
using namespace nb::Core;
using namespace nb::System;

namespace nb { namespace Gui {

class NameRealmPrivate
{
public:
//	class ObjectAttachment : public RefObject
//	{
//		ObjectAttachment(NameRealm *nr, const char *name) : m_nameRealm(nr), m_name(name) {}
//		
//		NameRealm *m_nameRealm;
//		std::string m_name;
//	};

	NameRealmPrivate(NameRealm *owner) : m_owner(owner) {}

	~NameRealmPrivate()
	{
	}

	NameRealm *m_owner;
	std::map<std::string, nb::Core::RefObjectWeatPtrT<nbObject> > m_objects;
	std::list<nb::Core::RefObjectWeatPtrT<nbObject> > m_nonameObjects;

	ObjectAttachmentSymbolPtr m_pObjectAttachmentSymbol;
	ObjectAttachmentSymbolPtr m_pObjectNameAttachmentSymbol;


	void AddObject(nbObject *object, const char *name)
	{
		if(object->GetAttachment(m_objectAttachmentSymbol) != NULL)
		{
			throw ExceptionPtr::GetPtrInstance("(NameRealm::AddObject)存储对象已加入名称域，不能重复加入其它的名称域。");
		}

		if(name == NULL || name[0] == '\0')
		{
			m_nonameObjects.push_back(object);
			object->SetAttachment(m_objectAttachmentSymbol, m_owner, false);
			return;
		}

		if(IsExistName(name))
		{
			throw ExceptionPtr::GetPtrInstance("(NameRealm::AddObject)给定的名称已存储，不能存储相同的名称。");
		}


		m_objects[name] = object;

		object->SetAttachment(m_objectAttachmentSymbol, m_owner, false);

		StringPtr str = new String(name);
		object->SetAttachment(m_objectNameSymbol, str, false);
	}

	void RemoveObject(const char *name)
	{
		std::map<std::string, nb::Core::RefObjectWeatPtrT<nbObject> >::iterator itor = m_objects.find(name);
		if(itor == m_objects.end()) return;

		nbObject *object = itor->second;

		m_objects.erase(itor);

		object->SetAttachment(m_objectAttachmentSymbol, NULL);
		object->SetAttachment(m_objectNameSymbol, NULL);
	}

	bool IsExistName(const char *name) const
	{
		return m_objects.find(name) != m_objects.end();
	}

	nbObject * FindObject(const char *name) const
	{
		std::map<std::string, nb::Core::RefObjectWeatPtrT<nbObject> >::const_iterator itor = m_objects.find(name);
		if(itor == m_objects.end()) return NULL;

		nbObject *pObject = itor->second;
		if(pObject == NULL)
		{
			NameRealmPrivate *pThis = const_cast<NameRealmPrivate *>(this);
			pThis->m_objects.erase(name);
		}

		return pObject;
	}

	static ObjectAttachmentSymbolPtr m_objectAttachmentSymbol;
	static ObjectAttachmentSymbolPtr m_objectNameSymbol;

	static bool FindNameRealm(nbObject *object, NameRealm * & outNameRealm, String * & outName)
	{
		RefObject *v = object->GetAttachment(m_objectAttachmentSymbol);
		outNameRealm = dynamic_cast<NameRealm *>(v);
		if(outNameRealm == NULL) return false;

		v = object->GetAttachment(m_objectNameSymbol);
		outName = dynamic_cast<String *>(v);

		return true;
	}

};

ObjectAttachmentSymbolPtr NameRealmPrivate::m_objectAttachmentSymbol = new ObjectAttachmentSymbol();
ObjectAttachmentSymbolPtr NameRealmPrivate::m_objectNameSymbol = new ObjectAttachmentSymbol();

}}


NameRealm::NameRealm(void)
{
	m_private = new NameRealmPrivate(this);
}

NameRealm::~NameRealm(void)
{
	delete m_private;
}

void NameRealm::AddObject(nbObject *object, const char *name)
{
	GetPrivate()->AddObject(object, name);
}

void NameRealm::RemoveObject(const char *name)
{
	GetPrivate()->RemoveObject(name);
}

bool NameRealm::IsExistName(const char *name) const
{
	return GetPrivate()->IsExistName(name);
}

nbObject * NameRealm::FindObject(const char *name) const
{
	return GetPrivate()->FindObject(name);
}

bool NameRealm::FindNameRealm(nbObject *object, NameRealm * & outNameRealm, String * & outName)
{
	return NameRealmPrivate::FindNameRealm(object, outNameRealm, outName);
}

