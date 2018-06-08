#pragma once

#include <map>
#include "core/Object.h"

namespace nb
{
	namespace System
	{
		class String;
	}

	namespace Gui
	{

		class NameRealmPrivate;
		class NB_EXPORT NameRealm : public nbObject
		{
		public:
			NameRealm(void);
			virtual ~NameRealm(void);

			void AddObject(nbObject *object, const char *name = NULL);
			void RemoveObject(const char *name);
			bool IsExistName(const char *name) const;

			nbObject * FindObject(const char *name) const;

			const char * FindNameByObject(nbObject *object) const;

			NameRealmPrivate * GetPrivate() const {return m_private;}

			static bool FindNameRealm(nbObject *object, NameRealm * & outNameRealm, System::String * & outName);

		//	static ObjectAttachmentSymbol * GetObjectAttachmentSymbol();
		//	static ObjectAttachmentSymbol * GetObjectNameAttachmentSymbol();
		private:

			NameRealmPrivate * m_private;
		};

		typedef nbObjectPtrDerive<NameRealm, nbObjectPtr> NameRealmPtr;
		
	}
}
