#pragma once
#include <string>
#include "system/Platform.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	#include <WinSock2.h>
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
#endif

namespace nb{ namespace Network{

class Socket
{
public:
	std::string GetIp() const;

	unsigned int GetPort() const;
	
	int SendData(const char *pData, int nLenBytes);

	int RecvData(char *pBuf, int nLenBytes);

public:
	Socket(const std::string &sIp, unsigned int nPort);
	Socket(int socketHandle, sockaddr_in addr);
	~Socket();

protected:
	int					m_SocketHandle;
	sockaddr_in			m_Socket_Addr_in;

private:
	Socket(const Socket &other);
	void operator = (const Socket &other);

};

}}
