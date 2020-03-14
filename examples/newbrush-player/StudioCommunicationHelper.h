#pragma once
#include <string>
#include "Poco/Net/StreamSocket.h"

class StudioCommunicationHelper
{
public:
	static void connect();

private:
	std::string getLocalIp() const;
};

