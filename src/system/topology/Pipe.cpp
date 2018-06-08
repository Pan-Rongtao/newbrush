#include "system/topology/Pipe.h"
#include "system/topology/Node.h"

using namespace nb::System::Topology;

namespace nb { namespace System { namespace Topology {
class P2PPipeInternal
{
public:
	class NodeIteratorContent : public Pipe::NodeIteratorContentBase
	{
	public:
		NodeIteratorContent(const P2PPipe *pipe, Node *node) : m_pipe(const_cast<P2PPipe *>(pipe)), m_node(node) {}

		virtual bool Equal(const NodeIteratorContentBase &content) const
		{
			const NodeIteratorContent *r = dynamic_cast<const NodeIteratorContent *>(&content);
			if(r == NULL) return false;

			if(m_pipe == r->m_pipe && m_node == r->m_node) return true;
			else return false;
		}

		virtual void Next()
		{
			if((Node *)m_node == m_pipe->GetNode0()) m_node = m_pipe->GetNode1();
			else m_node = NULL;
		}

		virtual Node * GetNode()
		{
			return m_node;
		}

		virtual NodeIteratorContentBase * Clone() const
		{
			return new NodeIteratorContent(m_pipe, m_node);
		}

		P2PPipePtr m_pipe;
		NodePtr m_node;
	};

	P2PPipeInternal(Node *node0, Node *node1)
		: m_node0(node0)
		, m_node1(node1)
	{}

	P2PPipeInternal()
	{}

	virtual Pipe::NodeIterator FindNodeOverride(Node *node) const
	{
		if(node == m_node0)
		{
			//return Pipe::Iterator(new IteratorContent(
		}

		return Pipe::NodeIterator();
	}

	Core::RefObjectWeatPtrT<Node> m_node0;
	Core::RefObjectWeatPtrT<Node> m_node1;

};
}}}



Pipe::Pipe(void)
{
}

Pipe::~Pipe(void)
{
}


void Pipe::__RecursiveTraverseTopologyGraph(Token *token, Node *enterNode, bool &isHandled, long long visitID, nbObject *tag, Node **outHandledNode)
{
	if(enterNode == NULL)
	{
		return;
	}
	else
	{
		NodeIterator itorFirst = FindNode(enterNode);
		NodeIterator itor = itorFirst;
		++itor;

		for(; itor != EndNode(); ++itor)
		{
			Node *node = itor.GetNode();
			if(token != NULL && !IsAdmitted(token, enterNode, node))
			{
				continue;
			}

			node->__RecursiveTraverseTopologyGraph(true, token, this, isHandled, visitID, tag, outHandledNode);
			if(isHandled) break;
			//++itor;
		}

		itor = BeginNode();
		for(; itor != EndNode(); ++itor)
		{
			Node *node = itor.GetNode();
			if(node == enterNode) break;
			if(node != NULL)
			{
				if(token != NULL && !IsAdmitted(token, enterNode, node))
				{
					continue;
				}

				node->__RecursiveTraverseTopologyGraph(true, token, this, isHandled, visitID, tag, outHandledNode);
				if(isHandled) return;
			}
		}
	}
}



P2PPipe::P2PPipe()
{
	m_internal = new P2PPipeInternal();
}

P2PPipe::P2PPipe(Node *node0, Node *node1)
{
	m_internal = new P2PPipeInternal(node0, node1);
}

P2PPipe::~P2PPipe()
{
	delete m_internal;
}

Node * P2PPipe::GetNode0() const
{
	return m_internal->m_node0;
}

Node * P2PPipe::GetNode1() const
{
	return m_internal->m_node1;
}

Pipe::NodeIterator P2PPipe::FindNodeOverride(Node *node) const
{
	return NodeIterator(new P2PPipeInternal::NodeIteratorContent(this, node));
}

Pipe::NodeIterator P2PPipe::BeginNodeOverride() const
{
	if((Node *)m_internal->m_node0 != NULL) return NodeIterator(new P2PPipeInternal::NodeIteratorContent(this, m_internal->m_node0));
	else if((Node *)m_internal->m_node1 != NULL) return NodeIterator(new P2PPipeInternal::NodeIteratorContent(this, m_internal->m_node1));
	else return NodeIterator(new P2PPipeInternal::NodeIteratorContent(this, NULL));
}

Pipe::NodeIterator P2PPipe::EndNodeOverride() const
{
	return NodeIterator(new P2PPipeInternal::NodeIteratorContent(this, NULL));
}

//void P2PPipe::Connect(Node * node0, Node * node1)
//{
//}

bool P2PPipe::IsCanConnectNode(Node *node, Connect::PipeArgu *argu)
{
	ConnectArgu * ta = dynamic_cast<ConnectArgu *>(argu);

	if(ta == NULL || ta->m_isFirstNode)
	{
		if((Node *)(m_internal->m_node0) != NULL)
		{
			return false;
		}
	}
	else
	{
		if((Node *)(m_internal->m_node1) != NULL)
		{
			return false;
		}
	}

	return true;
}

void P2PPipe::ConnectNodeRecord(Node *node, Connect::PipeArgu *argu)
{
	ConnectArgu * ta = dynamic_cast<ConnectArgu *>(argu);

	if(ta == NULL || ta->m_isFirstNode)
	{
		m_internal->m_node0 = node;
	}
	else
	{
		m_internal->m_node1 = node;
	}

}
