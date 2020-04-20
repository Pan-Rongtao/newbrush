#include "Node.grpc.pb.h"
#include "StubBase.h"

using namespace nbrpc;

class NodeStub : public NodeRpc::Service, public StubBase
{
	Status AddNode(ServerContext* context, const AddNodeRequest* request, CommonReply* response);
	Status RemoveNode(ServerContext* context, const RemoveNodeRequest* request, CommonReply* response);
	Status RenameNode(ServerContext* context, const RenameNodeRequest* request, CommonReply* response);
};