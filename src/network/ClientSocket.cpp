#include "ClientSocket.h"
#include <stdio.h>
#include <errno.h>

using nb::Network::ClientSocket;

ClientSocket::ClientSocket(const std::string &sIp, unsigned int nPort)
: Socket(sIp, nPort)
{
}

bool ClientSocket::Connect()
{
	int err = connect(m_SocketHandle,(sockaddr *)&m_Socket_Addr_in, sizeof(sockaddr));
	if(err != 0)
		printf("connect error code[%d]\r\n", errno);
	return err == 0;
}
