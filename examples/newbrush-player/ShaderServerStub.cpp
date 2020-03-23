#include "ShaderServerStub.h"

grpc::Status ShaderServerStub::BuildShader(::grpc::ServerContext* context, const ::NBPlayer::BuildShaderRequest* request, ::NBPlayer::BuildShaderReply* response)
{
	auto app = nb::Application::current();
	bool done = false;
	app->connect([this, request, response, &done, app]()
	{
		auto program = makeProgram(request->vshadercode(), request->fshadercode());
		if (program)
		{
			auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
			rc->renderObject()->setProgram(program);
			rc->setValue<BrushPtr>(Rectangle::FillProperty(), std::make_shared<EffectBrush>());
			rc->renderObject()->storeUniform("mouse", glm::vec2(0.5, 0.5));
			auto sz = rc->getValue<Size>(Shape::ActualSizeProperty());
			rc->renderObject()->storeUniform("resolution", glm::vec2(sz.width(), sz.height()));


			auto varInfos = response->mutable_varinfos();
			getUniforms(varInfos, request->vshadercode(), request->fshadercode());
		}
		done = true;
	});

	while (!done)
	{
	}
	return grpc::Status::OK;
}

::grpc::Status ShaderServerStub::SetUniform(::grpc::ServerContext * context, const::NBPlayer::SetUniformRequest * request, ::NBPlayer::SetUniformReply * response)
{
	auto app = nb::Application::current();
	bool done = false;
	app->connect([this, request, response, &done, app]()
	{
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto name = request->name();
		auto value = request->value();
		rc->renderObject()->storeUniform(name, value);
		done = true;
	});

	while (!done)
	{

	}
	return grpc::Status::OK;
}

std::shared_ptr<Program> ShaderServerStub::makeProgram(const std::string &vShaderCode, const std::string &fShaderCode)
{
	auto vShader = std::make_shared<VertexShader>(vShaderCode);
	auto fShader = std::make_shared<FragmentShader>(fShaderCode);
	auto program = std::make_shared<Program>(vShader, fShader);
	try
	{
		vShader->compile();
		fShader->compile();
		program->bindAttributeLocation(Program::nbPositionLocation, Program::nbPositionLocationStr);
		program->bindAttributeLocation(Program::nbColorLocation, Program::nbColorLocationStr);
		program->bindAttributeLocation(Program::nbTexCoordLocaltion, Program::nbTexCoordLocaltionStr);
		program->bindAttributeLocation(Program::nbNormalLocation, Program::nbNormalLocationStr);
		program->link();
		return program;
	}
	catch (...)
	{
		return nullptr;
	}
}

void ShaderServerStub::getUniforms(google::protobuf::Map<std::string, ::NBPlayer::BuildShaderReply_ShaderVarType>* &ref, const std::string &vShaderCode, const std::string &fShaderCode)
{
	SourceDecoder sd;
	auto uniforms = sd.decode(vShaderCode, fShaderCode);

	for (auto const &u : uniforms)
	{
		NBPlayer::BuildShaderReply_ShaderVarType t = static_cast<NBPlayer::BuildShaderReply_ShaderVarType>(u.second);
		ref->insert( MapPair<std::string, ::NBPlayer::BuildShaderReply_ShaderVarType>(u.first, t));
	}
}
