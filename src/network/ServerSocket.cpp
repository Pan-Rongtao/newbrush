#include "ServerSocket.h"
#include "system/Platform.h"

using nb::Network::ServerSocket;
using nb::Network::Socket;

ServerSocket::ServerSocket(const std::string &sIp, unsigned int nPort)
: Socket(sIp, nPort)
{
}

ServerSocket::~ServerSocket()
{

}

bool ServerSocket::Bind()
{
	if(bind(m_SocketHandle, (sockaddr *)&m_Socket_Addr_in, sizeof(sockaddr)) != 0)
		return false;
	if(listen(m_SocketHandle, 100) != 0)		//请求队列最长100，也就是未accept之前队列中最多存在100个请求
		return false;
	return true;
}

Socket *ServerSocket::Listen() const
{
	sockaddr_in newAddr;
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	int nLen = sizeof(sockaddr);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	socklen_t nLen = sizeof(sockaddr);
#endif
	int sk = (unsigned int)accept(m_SocketHandle, (sockaddr *)&newAddr, &nLen);
	if(sk < 0)
		return NULL;
	else
		return new Socket(sk, newAddr);
}
