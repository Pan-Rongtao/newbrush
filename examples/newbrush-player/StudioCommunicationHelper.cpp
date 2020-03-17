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
	: m_ready(false)
{
}

void StudioCommunicationHelper::startWorking()
{
	if (m_ready)
	{
		return;
	}

	auto app = nb::Application::current();
	if (!app)
	{
		nbThrowException(std::logic_error, "app has not been instanced");
	}
	app->UserMessage += std::bind(&StudioCommunicationHelper::onApplicationMessage, this, std::placeholders::_1);

	try 
	{
		m_socket.connect(Poco::Net::SocketAddress("127.0.0.1", 8888));
	}
	catch (...) 
	{
		Log::error("connect to studio fail."); 
	}

	std::thread t(&StudioCommunicationHelper::recv, this);
	t.detach();
	m_ready = true;
}

void StudioCommunicationHelper::send(const std::string & data)
{
	m_socket.sendBytes(data.data(), data.size());
}

//application thread
void StudioCommunicationHelper::onApplicationMessage(uint32_t id)
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

void StudioCommunicationHelper::recv()
{
	while (true)
	{
		char *buffer = new char[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE);
		try 
		{
			m_socket.receiveBytes(buffer, BUFFER_SIZE);
		}
		catch (...) 
		{ 
			Log::error("m_socket.receiveBytes error.");
			delete[]buffer;
			break; 
		};

		std::string recvStr(buffer);
		delete[]buffer;
		parseRecvMessage(recvStr);
	}
}

void StudioCommunicationHelper::parseRecvMessage(const std::string & s)
{
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result;
	try
	{
		result = parser.parse(s);
	}
	catch (...) {}
	
	if(result.isEmpty())
	{
		Log::error("parseRecvMessage error, not a json string.");
		return;
	}

	try 
	{
		Poco::JSON::Object::Ptr root = result.extract<Poco::JSON::Object::Ptr>();
		int msgId = root->get("msg_id");
		Application::current()->sendMessage(msgId);
	}
	catch (...)
	{
		Log::error("parseRecvMessage error, can't recgnize msg id.");
	}
}
