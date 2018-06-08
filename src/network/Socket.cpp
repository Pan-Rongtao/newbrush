#include <assert.h>
#include <stdio.h>
#include "Socket.h"

using nb::Network::Socket;

//WSAStartup和WSACleanup配套使用，使用多次只是计数的加减法。所以
Socket::Socket(const std::string &sIp, unsigned int nPort)
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	WORD VersionRequest = MAKEWORD(1,1);
	WSADATA Data;
	int err = WSAStartup(VersionRequest, &Data);
	if(err != 0)
	{
		printf("[%d]Can't Startup WinSock.\n", nb::System::Platform::GetCurrentProcessId());
		assert(err == 0);
	}
#endif

	//ipv4、字节流、tcp
	m_SocketHandle = (unsigned int)socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

	m_Socket_Addr_in.sin_family = AF_INET;
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	m_Socket_Addr_in.sin_addr.S_un.S_addr = inet_addr(sIp.data());
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	m_Socket_Addr_in.sin_addr.s_addr = inet_addr(sIp.data());
#endif
	m_Socket_Addr_in.sin_port = htons(nPort);
}

Socket::Socket(int socketHandle, sockaddr_in addr)
: m_SocketHandle(socketHandle)
, m_Socket_Addr_in(addr)
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	WORD VersionRequest = MAKEWORD(1,1);
	WSADATA Data;
	int err = WSAStartup(VersionRequest, &Data);
	if(err != 0)
	{
		printf("[%d]Can't Startup WinSock.\n", nb::System::Platform::GetCurrentProcessId());
		assert(err == 0);
	}
#endif
}

Socket::~Socket()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	closesocket(m_SocketHandle);
	WSACleanup();
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	close(m_SocketHandle);
#endif
}

std::string Socket::GetIp() const
{
	char *p = NULL;
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	p = inet_ntoa(m_Socket_Addr_in.sin_addr);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	p = inet_ntoa(m_Socket_Addr_in.sin_addr);
#endif
	return std::string(p);
}

unsigned int Socket::GetPort() const
{
	return ntohs(m_Socket_Addr_in.sin_port);
}

int Socket::SendData(const char *pData, int nLenBytes)
{
	//TCP阻塞方式，send会在内核处理完所有的data，用户层不用做多次send
	int nSendBytes = send(m_SocketHandle, pData, nLenBytes, 0);
	if(nSendBytes == -1)
		printf("[%d]send data error, remote quit.\n", nb::System::Platform::GetCurrentProcessId());
	return nSendBytes;
}

int Socket::RecvData(char *pBuf, int nLenBytes)
{
	return recv(m_SocketHandle, pBuf, nLenBytes, 0);
}
