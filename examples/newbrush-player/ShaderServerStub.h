#include "grpcpp/grpcpp.h"
#include "helloworld.grpc.pb.h"
#include "newbrush/gui/Application.h"

class ShaderServerStub final : public helloworld::Greeter::Service
{
	virtual grpc::Status SayHello(::grpc::ServerContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloReply* response)
	{
		return grpc::Status::OK;
	}
};