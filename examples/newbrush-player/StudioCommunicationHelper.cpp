#include "StudioCommunicationHelper.h"
#include <thread>
#include "newbrush/gui/Application.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/gui/Window.h"
#include "newbrush/core/Log.h"

using namespace nb;

constexpr int BUFFER_SIZE = 3 * 1024 * 1024;
StudioCommunicationHelper::StudioCommunicationHelper()
{
	auto app = nb::Application::current();
	assert(app != nullptr);
	app->UserMessage += std::bind(&StudioCommunicationHelper::onAppMessage, this, std::placeholders::_1);
}

bool StudioCommunicationHelper::connect(const std::string &ip, int port)
{
	try {
		m_socket.connect(Poco::Net::SocketAddress(ip, port));
	}
	catch (...) { return false; }

	std::thread t(&StudioCommunicationHelper::revc, this);
	t.detach();
	return true;
}

void StudioCommunicationHelper::send(const std::string & data)
{
	m_socket.sendBytes(data.data(), data.size());
}

void StudioCommunicationHelper::onAppMessage(uint32_t id)
{
	Log::info("onAppMessage:%d", id);
	auto rc = std::dynamic_pointer_cast<nb::Rectangle>(Application::current()->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));

	switch (id)
	{
	case Update_Shader_Source:
	{
		rc->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
		Poco::JSON::Object::Ptr root = new Poco::JSON::Object();
		root->set("msg_id", id);
		auto str = Poco::Dynamic::Var(root).toString();
		m_socket.sendBytes(str.data(), str.size());
	}
	break;
	default:
		break;
	}
}

void StudioCommunicationHelper::revc()
{
	while (true)
	{
		char *buffer = new char[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE);
		try {
			m_socket.receiveBytes(buffer, BUFFER_SIZE);
			bool b = false;
		}
		catch (...) { printf("socket recv data error.\n"); break; };

		std::string recvStr(buffer);

		Poco::JSON::Parser parser;
		auto result = parser.parse(buffer);
		Poco::JSON::Object::Ptr root = result.extract<Poco::JSON::Object::Ptr>();
		int msgId = root->get("msg_id");
		Application::current()->sendMessage(msgId);
	}
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