#include "grpcpp/grpcpp.h"
#include "helloworld.grpc.pb.h"
#include "newbrush/gui/Application.h"

class ShaderServerStub final : public helloworld::Greeter::Service
{
	virtual grpc::Status SayHello(::grpc::ServerContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloReply* response)
	{
		auto app = nb::Application::current();
		app->connect([request, response]() {
			response;
		});
		return grpc::Status::OK;
	}


};