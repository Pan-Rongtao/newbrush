#pragma once
#include <string>
#include "newbrush/core/Event.h"
#include "Poco/Net/StreamSocket.h"
#include "newbrush/gui/Application.h"
#include "grpcpp/grpcpp.h"

class StudioCommunicationHelper
{
public:
	StudioCommunicationHelper();

	void startWorking();

private:
	void runGrpcServer();

	std::unique_ptr<grpc::Server>	m_server;
};

