#pragma once
#include "grpcpp/grpcpp.h"

//由于std::unique_ptr 模板必须要包含模板类的实现头文件，即grpc::Server
//因此做个RpcServiceImpl把此隐藏起来
namespace nb{

class RpcServiceImpl
{
public:
	RpcServiceImpl(const std::string &address);

	const std::string &address() const;

	void startup();

private:
	void runGrpcServer();

	std::string						m_address;
	std::unique_ptr<grpc::Server>	m_server;
};

}