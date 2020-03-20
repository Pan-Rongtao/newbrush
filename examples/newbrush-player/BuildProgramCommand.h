#pragma once
#include "Command.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/gles/Shader.h"

class BuildProgramCommand : public Command
{
public:
	virtual std::string excute(const std::string &data) override
	{
		using namespace nb;
		using nlohmann::json;
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(Application::current()->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto program = rc->renderObject()->program();
		auto vShader = program->vertexShader();
		auto fShader = program->fragmentShader();
		//vShader->setSource();
		rc->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
	//	Poco::JSON::Object::Ptr root = new Poco::JSON::Object();
	//	root->set("msg_id", id);
	//	auto str = Poco::Dynamic::Var(root).toString();
	//	m_socket.sendBytes(str.data(), str.size());
		return "";
	}
};