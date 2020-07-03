#include "RpcServiceImpl.h"
#include <thread>
#include "newbrush/core/Log.h"
#include "ShaderStub.h"
#include "NodeStub.h"
#include "newbrush/gui/RttrRegistration.h"

using namespace nb;

RpcServiceImpl::RpcServiceImpl(const std::string &address)
	: m_address(address)
{
	RttrRegistration::doRegister();
}

const std::string &RpcServiceImpl::address() const
{
	return m_address;
}

void RpcServiceImpl::startup()
{
	if (m_server)
	{
		return;
	}

	std::thread t(&RpcServiceImpl::runGrpcServer, this);
	t.detach();
}

void RpcServiceImpl::runGrpcServer()
{
	grpc::ServerBuilder builder;
	builder.AddListeningPort(m_address, grpc::InsecureServerCredentials());
	builder.RegisterService(new ShaderStub());
	builder.RegisterService(new NodeStub());
	m_server = builder.BuildAndStart();
	m_server->Wait();
}
