/**************************************************************************************************

 * Copyright (c) 2017，德赛西威汽车电子有限公司

 * All rights reserved
 
 * 技术中心 → ... → MF组 → UI Framework团队

 * 编 写 者: 何平

 * 编写日期: 2017-03

 * 简要描述: 拓扑图中的连接器。

			详细描述请参看Node.h文件。

			特别强调：
			对于Pipe的派生类，假如需要保存相应的Node，应该使用弱指针，以避免Node内部因为使用强指针
			指向Pipe而导致的相互保存，以至于内存无法释放的问题。

 * 修改记录:

 **************************************************************************************************/

#pragma once

#include "../../core/Object.h"
#include "Token.h"
#include "Connect.h"

namespace nb { namespace System { namespace Topology {

class Node;
class Token;
class NB_API Pipe : public nbObject
{
	friend class Node;
	friend class Connect;

public:
	class NodeIteratorContentBase : public nbObject
	{
	public:
		virtual bool Equal(const NodeIteratorContentBase &content) const {return false;}
		virtual void Next(){}
		virtual Node * GetNode() {return NULL;}
		virtual NodeIteratorContentBase * Clone() const = 0;

	};
	typedef nbObjectPtrDerive<NodeIteratorContentBase, nbObjectPtr> NodeIteratorContentBasePtr;


	class NodeIterator
	{
	public:
		NodeIterator() {}

		NodeIterator(NodeIteratorContentBasePtr content) : m_content(content) {}

		NodeIterator(const NodeIterator &right)
		{
			m_content = right.m_content->Clone();
		}

		Node * GetNode() const
		{
			if(m_content != NULL) return m_content->GetNode();
			else return NULL;
		}

		virtual bool IsEnd() const {return true;}

		void operator ++ () { if(m_content != NULL) m_content->Next(); }
		bool operator != (const NodeIterator &itor) { return ! operator == (itor); }
		bool operator == (const NodeIterator &itor)
		{
			if(m_content == NULL && itor.m_content == NULL) return true;
			if(m_content == NULL && itor.m_content != NULL) return false;
			if(m_content != NULL && itor.m_content == NULL) return false;

			return m_content->Equal(*itor.m_content);
		}

		void operator = (const NodeIterator &right)
		{
			m_content = right.m_content->Clone();
		}

	protected:

		NodeIteratorContentBasePtr m_content;
	};




	Pipe(void);
	virtual ~Pipe(void);

	void __RecursiveTraverseTopologyGraph(Token *token, Node *enterNode, bool &isHandled, long long visitID, nbObject *tag, Node **outHandledNode);

	NodeIterator BeginNode() const {return BeginNodeOverride();}
	NodeIterator EndNode() const {return EndNodeOverride();}

protected:
	virtual NodeIterator FindNodeOverride(Node *node) const { return NodeIterator(); }

	virtual NodeIterator BeginNodeOverride() const {return NodeIterator();}
	virtual NodeIterator EndNodeOverride() const {return NodeIterator();}

	//是否允许从fromNode通行到toNode；toke为通行令牌
	virtual bool IsAdmitted(Token *toke, Node *fromNode, Node *toNode) {return true;}

	virtual bool IsCanConnectNode(Node *node, Connect::PipeArgu *argu){return false;}
	virtual void ConnectNodeRecord(Node *node, Connect::PipeArgu *argu){}

private:
	NodeIterator FindNode(Node *node) const { return FindNodeOverride(node); }

};
typedef nbObjectPtrDerive<Pipe, nbObjectPtr> PipePtr;


class P2PPipeInternal;

class NB_API P2PPipe : public Pipe
{
public:
	class ConnectArgu : public Connect::PipeArgu
	{
	public:
		bool m_isFirstNode;
	};

	P2PPipe();
	P2PPipe(Node *node0, Node *node1);
	virtual ~P2PPipe();

	Node * GetNode0() const;
	Node * GetNode1() const;

//	void Connect(Node * node0, Node * node1);

protected:
	virtual NodeIterator FindNodeOverride(Node *node) const;
	virtual NodeIterator BeginNodeOverride() const;
	virtual NodeIterator EndNodeOverride() const;

	virtual bool IsCanConnectNode(Node *node, Connect::PipeArgu *argu);
	virtual void ConnectNodeRecord(Node *node, Connect::PipeArgu *argu);

private:
	P2PPipeInternal *m_internal;
private:
};
typedef nbObjectPtrDerive<P2PPipe, PipePtr> P2PPipePtr;


class NB_API KeyPipeBase : public P2PPipe
{

};

template<class KeyT>
class KeyPipe : public KeyPipeBase
{
public:
	KeyPipe(const KeyT &key) : m_key(key) {}

protected:
	virtual bool IsAdmitted(Token *toke, Node *fromNode, Node *toNode)
	{
		KeyToken<KeyT> *kt = dynamic_cast<KeyToken<KeyT> *>(toke);
		if(kt == NULL) return false;

		return m_key == kt->GetKey();
	}

private:
	KeyT m_key;
};

}}}
