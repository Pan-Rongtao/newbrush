#pragma once
#include "newbrush/Object.h"
#include "rcf/RCF.hpp"

class RpcHelper
{
public:
	static void starup();

};

RCF_BEGIN(Interface, "Interface")
RCF_METHOD_V3(void, addNode, const std::string &, const std::string &, const std::string &);
RCF_METHOD_V2(void, removeNode, const std::string &, const std::string &);
RCF_METHOD_V3(void, setProperty, const std::string &, const std::string &, const std::string &);
RCF_METHOD_V2(void, addResource, const std::string &, const std::string &);
RCF_END(Interface)

class Stub
{
public:
	static Stub* get();

	void addNode(const std::string &parentPath, const std::string &childName, const std::string &childType);

	void removeNode(const std::string &parentPath, const std::string &childName);

	void setProperty(const std::string &path, const std::string &propName, const std::string &value);

	//添加一个资源
	void addResource(const std::string &name, const std::string &type);
};

