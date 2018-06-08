/**************************************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved
 
 * 技术中心 → ... → MF组 → UI Framework团队

 * 编 写 者: 何平

 * 编写日期: 2017-03

 * 简要描述: 拓扑图中的Node与Pipe的连接操作

 * 修改记录:

 **************************************************************************************************/

#pragma once

#include "core/Object.h"

namespace nb { namespace System { namespace Topology {

class Node;
class Pipe;
class Connect : public nbObject
{
public:
	class NodeArgu
	{
	public:
		virtual ~NodeArgu() {}
	};

	class PipeArgu
	{
	public:
		virtual ~PipeArgu() {}
	};

	Connect(void);
	virtual ~Connect(void);

	static bool Bind(Node *node, NodeArgu *nodeArgu, Pipe *pipe, PipeArgu *pipeArgu);
};

}}}
