#include "system/LinkageEvents.h"
#include "system/topology/Node.h"

using namespace nb::System;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace nb { namespace System {
class LinkageEventsInternal
{
	class EventTag : public nbObject
	{
	public:
		size_t m_leOffset;
		nbEventParam * m_param;
	};

	class TopologyNode : public Topology::MultiPipeNode
	{
	public:
		LinkageEventsInternal *m_leInternal;

		virtual void OnVisited(nbObject *tag, bool &isHandled)
		{
			EventTag * eventTag = dynamic_cast<EventTag *>(tag);
			if(eventTag == NULL) return;

			size_t userAddress = (size_t)(m_leInternal->m_user);
			size_t leAddress = userAddress + eventTag->m_leOffset;
			LinkageEvents::LEventBase *le = (LinkageEvents::LEventBase *)leAddress;

			le->GetTriggerEvent()->Dispatch(*eventTag->m_param);

			if(eventTag->m_param->m_bHandled == true) isHandled = true;
		}
	};
	typedef nbObjectPtrDerive<TopologyNode, Topology::MultiPipeNodePtr> TopologyNodePtr;



public:
	LinkageEventsInternal()
	{
		m_node = new TopologyNode();
		m_node->m_leInternal = this;
	}

	void Dispatch(LinkageEvents::LEventBase *lEvent, nbEventParam &param, bool isOwnerRespond)
	{
		size_t userAddress = (size_t)m_user;
		size_t leAddress = (size_t)lEvent;

		EventTag eventTag;
		eventTag.m_leOffset = leAddress - userAddress;
		eventTag.m_param = &param;
		m_node->RecursiveTraverseTopologyGraph(isOwnerRespond, NULL, NULL, &eventTag);
	}

	TopologyNodePtr m_node;
	LinkageEvents * m_user;
};

}}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void LinkageEvents::LEventBase::Dispatch(nbEventParam &param, bool isOwnerRespond)
{
	GetLinkageEvents()->m_internal->Dispatch(this, param, isOwnerRespond);
}



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

LinkageEvents::LinkageEvents(void)
{
	m_internal = new LinkageEventsInternal();
	m_internal->m_user = this;
}

LinkageEvents::~LinkageEvents(void)
{
	delete m_internal;
}

void LinkageEvents::ContentTo(LinkageEvents * le)
{
	m_internal->m_node->ConnectToNode(le->m_internal->m_node);
}
