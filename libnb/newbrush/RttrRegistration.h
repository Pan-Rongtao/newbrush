#pragma once

namespace nb 
{

class RttrRegistration
{
public:
	//执行注册
	static void doRegister();

private:
	static void registerEnums();
	static void registerTypes();
	static void registerConverters();
};

}