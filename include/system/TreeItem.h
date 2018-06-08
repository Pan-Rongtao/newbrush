/**********************************************************
**
**
**
**********************************************************/

#pragma once

#include "core/Object.h"

namespace nb
{
	namespace System
	{
		class NB_EXPORT TreeItem : public nb::Core::RefObject
		{
		public:
			TreeItem();
			virtual ~TreeItem();

			TreeItem * GetFirstChild() const {return m_FirstChild;}
			TreeItem * GetLastChild() const {return m_LastChild;}
			TreeItem * GetNextSibling() const {return m_NextSibling;}
			TreeItem * GetPrevSibling() const {return m_PrevSibling;}
			TreeItem * GetParent() const {return m_Parent;}
			void AddChild(TreeItem * item);

			int GetChildCount() const {return m_ChildCount;}

			//待完善函数
			void AddChildToFirst(TreeItem * item);
			void InsertBefore(TreeItem * sibling);
			void InsertAfter(TreeItem * sibling);
			
			void RemoveFromParent();
			void RemoveAllChild();

			void SetTag(void *pTag) {m_pTag = pTag;}
			void * GetTag() const {return m_pTag;}


		private:
			nbObjectPtrDerive<TreeItem, Core::RefObjectPtr> m_FirstChild;
			nbObjectPtrDerive<TreeItem, Core::RefObjectPtr> m_LastChild;
			nbObjectPtrDerive<TreeItem, Core::RefObjectPtr> m_NextSibling;
			nbObjectPtrDerive<TreeItem, Core::RefObjectPtr> m_PrevSibling;
			TreeItem * m_Parent;
			int m_ChildCount;

			void * m_pTag;
		};

		typedef nbObjectPtrDerive<TreeItem, Core::RefObjectPtr> TreeItemPtr;

		template<class T>
		class NB_EXPORT TreeItemT : public TreeItem
		{
		};
	}
}
