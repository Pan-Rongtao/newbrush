#include "StudioCommunicationHelper.h"
#include <thread>
#include "newbrush/core/Log.h"
#include "Command.h"

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
void StudioCommunicationHelper::onApplicationMessage(const Application::UserMessageArgs &e)
{
	Log::info("onApplicationMessage:%d", e.id);
	auto cmd = CommandFactory::createCommand((CommandID)e.id);
	auto ret = cmd->excute(e.data);
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
		Application::current()->sendMessage(msgId, Poco::Dynamic::Var(root).toString());
	}
	catch (...)
	{
		Log::error("parseRecvMessage error, can't recgnize msg id.");
	}
}
