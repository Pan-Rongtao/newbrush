#include "system/topology/Connect.h"
#include "system/topology/Node.h"
#include "system/topology/Pipe.h"

using namespace nb::System::Topology;

Connect::Connect(void)
{
}

Connect::~Connect(void)
{
}

bool Connect::Bind(Node *node, NodeArgu *nodeArgu, Pipe *pipe, PipeArgu *pipeArgu)
{
	if(!node->IsCanConnectPipe(pipe, nodeArgu) || !pipe->IsCanConnectNode(node, pipeArgu))
	{
		return false;
	}

	node->ConnectPipeRecord(pipe, nodeArgu);
	pipe->ConnectNodeRecord(node, pipeArgu);

	return true;
}
