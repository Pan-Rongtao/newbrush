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

	void send(const std::string &data);

private:
	void onApplicationMessage(const nb::Application::UserMessageArgs &e);
	void recv();
	void parseRecvMessage(const std::string &s);

	bool					m_ready;
	Poco::Net::StreamSocket m_socket;
};

