#include "StudioCommunicationHelper.h"

void StudioCommunicationHelper::connect()
{
}
/*
std::string StudioCommunicationHelper::getLocalIp() const
{
#ifdef WIN32
	WSADATA Data;
	auto x = WSAStartup(MAKEWORD(1, 1), &Data);
	char hostName[256] = { 0 };
	gethostname(hostName, sizeof(hostName));
	PHOSTENT hostinfo;
	hostinfo = gethostbyname(hostName);
	std::string ip = inet_ntoa(*(struct in_addr*)*hostinfo->h_addr_list);
	WSACleanup();
	return ip;
#else
	auto getDeviceIp = [](const std::string &sDev)->std::string {
		char ip[80] = { 0 };
		struct ifreq ifr;
		int sk = socket(AF_INET, SOCK_DGRAM, 0);
		strcpy(ifr.ifr_name, sDev.data());
		if (ioctl(sk, SIOCGIFADDR, &ifr) == 0)
			strcpy(ip, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
		close(sk);
		return ip;
	};

	auto eth = getDeviceIp("ens160");
	if (eth.empty())
	{
		eth = getDeviceIp("eth1");
		if (eth.empty())
			eth = getDeviceIp("mlan0");
	}
	return eth;
#endif
}*/