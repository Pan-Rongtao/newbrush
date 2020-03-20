#pragma once
#include <memory>
#include "newbrush/gui/Application.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/media/SolidColorBrush.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Parser.h"
#include "nlohmann/json.hpp"

enum CommandID
{
	Command_Shader_Build,
	Command_Shader_Uniform_Var,
};

//执行command的excute已经是主线程
class Command
{
public:
	//执行相应的动作
	//data：json格式的数据
	//返回值：json格式的数据
	virtual std::string excute(const std::string &data) = 0;

protected:
	Command() {}
};

class CommandFactory
{
public:
	static std::shared_ptr<Command> createCommand(CommandID);
};