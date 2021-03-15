#include "RpcHelper.h"

void RpcHelper::starup()
{
	RCF::init();

	RCF::RcfServer server(RCF::TcpEndpoint("127.0.0.1", 8888));
	server.bind<Interface>(*Stub::get());
	server.start();
}

Stub* Stub::get()
{
	static Stub *p = nullptr;
	if (!p) p = new Stub(); 
	return p; 
}

void Stub::addNode(const std::string & parentPath, const std::string & childName, const std::string & childType)
{
}

void Stub::removeNode(const std::string & parentPath, const std::string & childName)
{
}

void Stub::setProperty(const std::string & path, const std::string & propName, const std::string & value)
{
}

void Stub::addResource(const std::string &name, const std::string &type)
{
}
