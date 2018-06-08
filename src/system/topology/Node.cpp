#include "system/topology/Node.h"
#include "system/topology/Pipe.h"

using namespace nb::System::Topology;

namespace nb { namespace System { namespace Topology {
class NodeInternal
{
public:
	NodeInternal() : m_visitID(0) {}

	long long m_visitID;
};

class MultiPipNodeInternal
{
public:
	class IteratorContent : public Node::PipeIteratorContentBase
	{
	public:
		IteratorContent(std::list<PipePtr>::iterator itor) : m_itor(itor) {}

		virtual bool Equal(const PipeIteratorContentBase &content) const
		{
			const IteratorContent * r = dynamic_cast<const IteratorContent *>(&content);
			if(r == NULL) return false;
			return m_itor == r->m_itor;
		}

		virtual void Next() { m_itor++; }

		virtual Pipe * GetPipe() {return *m_itor;}

		virtual PipeIteratorContentBase * Clone() const
		{
			return new IteratorContent(m_itor);
		}

		std::list<PipePtr>::iterator m_itor;
	};

	std::list<PipePtr> m_pipes;
};

}}}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

static long long s_nodeVisitingID = 0;

Node::Node(void)
{
	m_internal = new NodeInternal;
}

Node::~Node(void)
{
	delete m_internal;
}


void Node::RecursiveTraverseTopologyGraph(bool isVisitOwner, Token *token, Pipe *enterPipe, nbObject *tag, Node **outHandledNode)
{
	s_nodeVisitingID++;
	bool isHandled = false;
	__RecursiveTraverseTopologyGraph(isVisitOwner, token, enterPipe, isHandled, s_nodeVisitingID, tag, outHandledNode);
}

void Node::__RecursiveTraverseTopologyGraph(bool isVisitOwner, Token *token, Pipe *enterPipe, bool &isHandled, long long visitID, nbObject *tag, Node **outHandledNode)
{
	if(m_internal->m_visitID == visitID)
		return;
	m_internal->m_visitID = visitID;


	if(isVisitOwner) OnVisited(tag, isHandled);
	if(isHandled)
	{
		if(outHandledNode != NULL) *outHandledNode = this;
		return;
	}


	if(enterPipe == NULL)
	{
		PipeIterator itor = BeginPipe();
		for(; itor != EndPipe(); ++itor)
		{
			Pipe * pipe = itor.GetPipe();
			if(pipe != NULL)
			{
				pipe->__RecursiveTraverseTopologyGraph(token, this, isHandled, visitID, tag, outHandledNode);
				if(isHandled) return;
			}
		}
	}
	else 
	{
		PipeIterator itor = FindPipe(enterPipe);
		if(itor == EndPipe()) return;

		++itor;
		for(; itor != EndPipe(); ++itor)
		{
			Pipe * pipe = itor.GetPipe();
			if(pipe != NULL)
			{
				pipe->__RecursiveTraverseTopologyGraph(token, this, isHandled, visitID, tag, outHandledNode);
				if(isHandled) return;
			}
		}

		itor = BeginPipe();
		for(; itor != EndPipe(); ++itor)
		{
			Pipe *pipe = itor.GetPipe();
			if(pipe == enterPipe) break;
			if(pipe != NULL)
			{
				pipe->__RecursiveTraverseTopologyGraph(token, this, isHandled, visitID, tag, outHandledNode);
				if(isHandled) return;
			}
		}
	}

}


MultiPipeNode::MultiPipeNode()
{
	m_internal = new MultiPipNodeInternal();
}

MultiPipeNode::~MultiPipeNode()
{
	delete m_internal;
}

Node::PipeIterator MultiPipeNode::BeginPipeOverride()
{
	return PipeIterator(new MultiPipNodeInternal::IteratorContent(m_internal->m_pipes.begin()));
}

Node::PipeIterator MultiPipeNode::EndPipeOverride()
{
	return PipeIterator(new MultiPipNodeInternal::IteratorContent(m_internal->m_pipes.end()));
}

Node::PipeIterator MultiPipeNode::FindPipeOverride(Pipe *pipe) const
{
	std::list<PipePtr>::iterator itor = m_internal->m_pipes.begin();
	for(; itor != m_internal->m_pipes.end(); itor++)
	{
		if((Pipe *)*itor == pipe) return PipeIterator(new MultiPipNodeInternal::IteratorContent(itor));
	}

	return PipeIterator();
}

Pipe * MultiPipeNode::ConnectToNode(MultiPipeNode * other)
{
	PipePtr pipe = new P2PPipe(this, other);

	m_internal->m_pipes.push_back(pipe);
	other->m_internal->m_pipes.push_back(pipe);

	return pipe;
}

void MultiPipeNode::ConnectToNode(MultiPipeNode * other, P2PPipe *pipe)
{
	P2PPipe::ConnectArgu argu;
	argu.m_isFirstNode = true;

	if(!Connect::Bind(this, NULL, pipe, &argu)) return;

	argu.m_isFirstNode = false;
	Connect::Bind(other, NULL, pipe, &argu); 
}

void MultiPipeNode::ConnectPipeRecord(Pipe *pipe, Connect::NodeArgu *nodeArgu)
{
	m_internal->m_pipes.push_back(pipe);
}

/*void MultiPipeNode::UnconnectPipeRecord(Pipe *pipe)
{
	std::list<PipePtr>::iterator itor = m_internal->m_pipes.begin();
	for(; itor != m_internal->m_pipes.end() ;)
	{
		PipePtr &p = *itor;
		if(p.GetRealize() == pipe)
		{
			std::list<PipePtr>::iterator itorErase = itor;
			itor++;
			m_internal->m_pipes.erase(itorErase);
		}
		else
		{
			itor++;
		}
	}
}*/
