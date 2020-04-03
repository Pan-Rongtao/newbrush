#include "ShaderServerStub.h"
#include <thread>
#include "newbrush/core/Log.h"

Status ShaderServerStub::BuildShader(::ServerContext* context, const BuildShaderRequest* request, BuildShaderReply* response)
{
	auto app = nb::Application::current();
	bool done = false;
	app->connect([this, request, response, &done, app]()
	{
		auto program = makeProgram(request->vshadercode(), request->fshadercode());
		if (program)
		{
			auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
			rc->setValue<BrushPtr>(Rectangle::FillProperty(), std::make_shared<EffectBrush>());
			rc->renderObject()->setProgram(program);
			rc->renderObject()->storeUniform("mouse", glm::vec2(0.5, 0.5));
			auto sz = rc->getValue<Size>(Shape::ActualSizeProperty());
			rc->renderObject()->storeUniform("resolution", glm::vec2(sz.width(), sz.height()));


			auto varInfos = response->mutable_uniforminfos();
			getUniforms(varInfos, request->vshadercode(), request->fshadercode());
		}
		done = true;
	});

	while (!done) {}
	return Status::OK;
}

Status ShaderServerStub::UniformBool(ServerContext * context, const UniformBoolRequest * request, NoneReply * response)
{
	auto app = nb::Application::current();
	bool done = false;
	app->connect([this, request, response, &done, app]()
	{
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto uniformName = request->name();
		auto uniformValue = request->value();
		rc->renderObject()->storeUniform(uniformName, uniformValue);
		done = true;
	});

	while (!done) {}
	return Status::OK;
}

Status ShaderServerStub::UniformFloat(ServerContext * context, const UniformFloatRequest * request, NoneReply * response)
{
	auto app = nb::Application::current();
	bool done = false;
	app->connect([this, request, response, &done, app]()
	{
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto uniformName = request->name();
		auto uniformValue = request->value();
		rc->renderObject()->storeUniform(uniformName, uniformValue);
		done = true;
	});

	while (!done) {}
	return Status::OK;
}

Status ShaderServerStub::UniformInteger(ServerContext * context, const UniformIntegerRequest * request, NoneReply * response)
{
	auto app = nb::Application::current();
	bool done = false;
	app->connect([this, request, response, &done, app]()
	{
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto uniformName = request->name();
		auto uniformValue = request->value();
		rc->renderObject()->storeUniform(uniformName, uniformValue);
		done = true;
	});

	while (!done) {}
	return Status::OK;
}

Status ShaderServerStub::UniformVec2(ServerContext * context, const UniformVec2Request * request, NoneReply * response)
{
	auto app = nb::Application::current();
	bool done = false;
	app->connect([this, request, response, &done, app]()
	{
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto uniformName = request->name();
		auto uniformValue = request->value();
		rc->renderObject()->storeUniform(uniformName, glm::vec2{uniformValue.x(), uniformValue.y()});
		done = true;
	});

	while (!done) {}
	return Status::OK;
}

Status ShaderServerStub::UniformVec3(ServerContext * context, const UniformVec3Request * request, NoneReply * response)
{
	auto app = nb::Application::current();
	bool done = false;
	app->connect([this, request, response, &done, app]()
	{
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto uniformName = request->name();
		auto uniformValue = request->value();
		rc->renderObject()->storeUniform(uniformName, glm::vec3{ uniformValue.x(), uniformValue.y(), uniformValue.z() });
		done = true;
	});

	while (!done) {}
	return Status::OK;
}

Status ShaderServerStub::UniformVec4(ServerContext * context, const UniformVec4Request * request, NoneReply * response)
{
	auto app = nb::Application::current();
	bool done = false;
	app->connect([this, request, response, &done, app]()
	{
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto uniformName = request->name();
		auto uniformValue = request->value();
		rc->renderObject()->storeUniform(uniformName, glm::vec4{ uniformValue.x(), uniformValue.y(), uniformValue.z(), uniformValue.w() });
		done = true;
	});

	while (!done) {}
	return Status::OK;
}

Status ShaderServerStub::UniformMat3x3(ServerContext * context, const UniformMat3x3Request * request, NoneReply * response)
{
	return Status();
}

Status ShaderServerStub::UniformMat4x4(ServerContext * context, const UniformMat4x4Request * request, NoneReply * response)
{
	return Status();
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
	catch (std::runtime_error e)
	{
		Log::error("%s", e.what());
		return nullptr;
	}
}

void ShaderServerStub::getUniforms(google::protobuf::Map<std::string, UniformType>* &ref, const std::string &vShaderCode, const std::string &fShaderCode)
{
	SourceDecoder sd;
	auto uniforms = sd.decode(vShaderCode, fShaderCode);

	for (auto const &u : uniforms)
	{
		auto t = static_cast<UniformType>(u.second);
		if(!(u.first.size() >= 2 && u.first.substr(0, 2) == "nb"))
			ref->insert( MapPair<std::string, UniformType>(u.first, t));
	}
}
