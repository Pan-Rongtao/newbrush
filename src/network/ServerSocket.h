#pragma once
#include "Socket.h"

namespace nb{ namespace Network{

class ServerSocket : public Socket
{
public:
	//°ó¶¨
	bool Bind();

	//¼àÌı£¨×èÈû£©
	Socket *Listen() const;

public:
	ServerSocket(const std::string &sIp, unsigned int nPort);
	virtual ~ServerSocket();
};

}}