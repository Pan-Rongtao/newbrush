#pragma once
#include <string>
#include "newbrush/core/Event.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Parser.h"

enum MESSAGE_ID
{
	Update_Shader_Source,
};

class StudioCommunicationHelper
{
public:
	StudioCommunicationHelper();

	void startWorking();

	void send(const std::string &data);

	struct MessageArrivedArgs { std::string message; };
	nb::Event<MessageArrivedArgs>	MessageArrived;

private:
	void onApplicationMessage(uint32_t id);
	void recv();
	void parseRecvMessage(const std::string &s);

	bool					m_ready;
	Poco::Net::StreamSocket m_socket;
};

