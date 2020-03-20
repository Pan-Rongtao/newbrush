#include "StudioCommunicationHelper.h"
#include <thread>
#include "newbrush/core/Log.h"
#include "ShaderServerStub.h"

using namespace nb;

StudioCommunicationHelper::StudioCommunicationHelper()
{
}

void StudioCommunicationHelper::startWorking()
{
	if (m_server)
	{
		return;
	}

	std::thread t(&StudioCommunicationHelper::runGrpcServer, this);
	t.detach();
}

void StudioCommunicationHelper::runGrpcServer()
{
	std::string address("127.0.0.1:8888");
	grpc::ServerBuilder builder;
	builder.AddListeningPort(address, grpc::InsecureServerCredentials());
	builder.RegisterService(new ShaderServerStub());
	m_server = builder.BuildAndStart();
	std::cout << "Server listening on " << address << std::endl;
	m_server->Wait();
}
