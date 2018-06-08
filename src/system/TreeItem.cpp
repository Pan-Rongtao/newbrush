#include "system/TreeItem.h"
#include "core/Exception.h"

using namespace nb::System;
using namespace nb::Core;

TreeItem::TreeItem()
	: m_Parent(NULL)
	, m_ChildCount(0)
	, m_pTag(NULL)
{
}

TreeItem::~TreeItem()
{
}

void TreeItem::AddChild(TreeItem *item)
{
	if(item->GetParent() != NULL)
	{
		NB_THROW_EXCEPTION("(TreeItem::AddChild) 已经存在有父节点，不允许再次加入到其它的节点。");
	}

	item->m_Parent = this;

	if(m_FirstChild == NULL)
	{
		m_FirstChild = item;
		m_LastChild = item;
	}
	else
	{
		m_LastChild->m_NextSibling = item;
		item->m_PrevSibling = m_LastChild;
		m_LastChild = item;
	}

	m_ChildCount++;
}
