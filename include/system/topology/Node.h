/**************************************************************************************************

 * Copyright (c) 2017，德赛西威汽车电子有限公司

 * All rights reserved
 
 * 技术中心 → ... → MF组 → UI Framework团队

 * 编 写 者: 何平

 * 编写日期: 2017-03

 * 简要描述: 拓扑图中的节点。

			对于一个拓扑图，包含有节点（Node）、连接器（Pipe）两种主要的元素。其中，节点为拓扑图的
			基础，节点间通过连接器进行连接。在这个系统中，没有“拓扑图”这种对象的类，所有离散的节
			点都是独立存在的，它们通过连接器连接起来，就组成了一个拓扑图。

			当一个节点被释放的时候，与它相连接的连接器可能还会存在，但连接器指向该节点的记录将会为
			空，该节点自动从所在的拓扑图中移除掉。

			节点可以派生出多种类型的节点，比如可以与多个连接器对接的节点（MultiPipeNode），也可以是
			通过Key来访问的节点。

			连接器也同样可以派生出多种类型的连接器。


			拓扑图示例：

			【Node】──Pipe──【Node】──Pipe──【Node】──Pipe──【Node】
			  │＼                                    ／         │
			  │  Pipe                     Pipe───            │
			  │     ＼                   ／                     │
			 Pipe   【Node】──Pipe--【Node】                【Node】
			  │                  │
			  │                  │
			【Node】──Pipe──【Node】



			对于任何一个节点，可以通过RecursiveTraverseTopologyGraph函数递归访问该节点所在的拓扑图的
			其它所有的节点。由于是递归访问，所以，调用RecursiveTraverseTopologyGraph时，构建的拓扑图
			不能太大，否则将会有堆栈溢出的风险。
			每一个被访问的节点，都将会触发虚函数OnVisited的调用。可通过派生的方式使用。

 * 修改记录:

 **************************************************************************************************/

#pragma once

#include "../../core/Object.h"
#include "Connect.h"

namespace nb { namespace Core {
/*
template<class T>
class InternalObjectPtr
{
	T *m_user;

public:
	~InternalObjectPtr()
	{
		delete m_user;
	}
};*/

}}

namespace nb { namespace System { namespace Topology {

class Pipe;
class P2PPipe;
class NodeInternal;
class Token;
class NB_API Node : public nbObject
{
	friend class Pipe;
	friend class Connect;
public:

	class PipeIteratorContentBase : public nbObject
	{
	public:
		virtual bool Equal(const PipeIteratorContentBase &content) const {return false;}
		virtual void Next(){}
		virtual Pipe * GetPipe() {return NULL;}
		virtual PipeIteratorContentBase * Clone() const = 0;
	};

	typedef nbObjectPtrDerive<PipeIteratorContentBase, nbObjectPtr> PipeIteratorContentBasePtr;

	class PipeIterator
	{
	public:
		PipeIterator() {}

		PipeIterator(PipeIteratorContentBasePtr content) : m_content(content) {}

		PipeIterator(const PipeIterator &right)
		{
			m_content = right.m_content->Clone(); //这里有bug
		}

		Pipe * GetPipe() const
		{
			if(m_content != NULL) return m_content->GetPipe();
			else return NULL;
		}

		virtual bool IsEnd() const {return true;}

		void operator ++ () { if(m_content != NULL) m_content->Next(); }
		bool operator != (const PipeIterator &itor) { return ! operator == (itor); }
		bool operator == (const PipeIterator &itor)
		{
			if(m_content == NULL && itor.m_content == NULL) return true;
			if(m_content == NULL && itor.m_content != NULL) return false;
			if(m_content != NULL && itor.m_content == NULL) return false;

			return m_content->Equal(*itor.m_content);
		}

		void operator = (const PipeIterator &right)
		{
			m_content = right.m_content->Clone();
		}

	protected:

		PipeIteratorContentBasePtr m_content;
	};

public:
	Node(void);
	virtual ~Node(void);


	//以此节点为入口，递归遍历拓扑图上的所有节点
	void RecursiveTraverseTopologyGraph(bool isVisitOwner, Token *token=NULL, Pipe *enterPipe=NULL, nbObject *tag=NULL, Node **outHandledNode=NULL);

//	::coreInternalObjectPtr<NodeInternal> xx;

	PipeIterator BeginPipe() { return BeginPipeOverride();}
	PipeIterator EndPipe() {return EndPipeOverride();}

	PipeIterator FindPipe(Pipe *pipe) const { return FindPipeOverride(pipe); }

protected:
	virtual void OnVisited(nbObject *tag, bool &isHandled) {}

	virtual PipeIterator BeginPipeOverride() {return PipeIterator(NULL);}
	virtual PipeIterator EndPipeOverride() {return PipeIterator(NULL);}
	virtual PipeIterator FindPipeOverride(Pipe *pipe) const { return PipeIterator(); }

	virtual bool IsCanConnectPipe(Pipe *pipe, Connect::NodeArgu *nodeArgu) {return false;}
	virtual void ConnectPipeRecord(Pipe *pipe, Connect::NodeArgu *nodeArgu){}

private:
	void __RecursiveTraverseTopologyGraph(bool isVisitOwner, Token *token, Pipe *enterPipe, bool &isHandled, long long visitID, nbObject *tag, Node **outHandledNode);

	NodeInternal * m_internal;
};
typedef nbObjectPtrDerive<Node, nbObjectPtr> NodePtr;


class MultiPipNodeInternal;
class NB_API MultiPipeNode : public Node
{
public:
	MultiPipeNode();
	virtual ~MultiPipeNode();

	Pipe * ConnectToNode(MultiPipeNode * other);

	void ConnectToNode(MultiPipeNode * other, P2PPipe *pipe);

protected:
	virtual PipeIterator BeginPipeOverride();
	virtual PipeIterator EndPipeOverride();
	virtual PipeIterator FindPipeOverride(Pipe *pipe) const;

	virtual bool IsCanConnectPipe(Pipe *pipe, Connect::NodeArgu *nodeArgu) {return true;}
	virtual void ConnectPipeRecord(Pipe *pipe, Connect::NodeArgu *nodeArgu);

private:
	MultiPipNodeInternal * m_internal;
};
typedef nbObjectPtrDerive<MultiPipeNode, NodePtr> MultiPipeNodePtr;

template<class KeyT>
class KeyPipeNode : public Node
{
};

}}}
