#pragma once
#include "Socket.h"

namespace nb{ namespace Network{

class ClientSocket : public Socket
{
public:
	//Á¬½Ó
	bool Connect();

public:
	ClientSocket(const std::string &sIp, unsigned int nPort);

};

}}