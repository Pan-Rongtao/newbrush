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

	bool connect(const std::string &ip, int port);

	void send(const std::string &data);

	struct MessageArrivedArgs { std::string message; };
	nb::Event<MessageArrivedArgs>	MessageArrived;

	Poco::Net::StreamSocket m_socket;
private:

	void onAppMessage(uint32_t id);
	void revc();

};

