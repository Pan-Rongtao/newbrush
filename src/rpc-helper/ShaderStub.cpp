#include "ShaderStub.h"
#include "glm/gtc/matrix_transform.hpp"

Status ShaderStub::BuildShader(::ServerContext* context, const BuildShaderRequest* request, BuildShaderReply* response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto program = makeProgram(request->vshadercode(), request->fshadercode());
		if (program)
		{
			auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
			if (rc)
			{
				rc->setValue<BrushPtr>(Rectangle::FillProperty(), std::make_shared<EffectBrush>());
				auto sz = rc->getValue<Size>(Shape::ActualSizeProperty());
				rc->renderObject()->storeUniform("resolution", glm::vec2(sz.width(), sz.height()));
				rc->renderObject()->setProgram(program);
				auto varInfos = response->mutable_uniforminfos();
				getUniforms(varInfos, request->vshadercode(), request->fshadercode());
			}
		}
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status ShaderStub::UniformBool(ServerContext * context, const UniformBoolRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto uniformName = request->name();
		auto uniformValue = request->value();
		//rc->renderObject()->storeUniform(uniformName, uniformValue);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status ShaderStub::UniformFloat(ServerContext * context, const UniformFloatRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto uniformName = request->name();
		auto uniformValue = request->value();
		rc->renderObject()->storeUniform(uniformName, uniformValue);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status ShaderStub::UniformInteger(ServerContext * context, const UniformIntegerRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto uniformName = request->name();
		auto uniformValue = request->value();
		rc->renderObject()->storeUniform(uniformName, uniformValue);
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status ShaderStub::UniformVec2(ServerContext * context, const UniformVec2Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto uniformName = request->name();
		auto uniformValue = request->value();
		rc->renderObject()->storeUniform(uniformName, glm::vec2{uniformValue.x(), uniformValue.y()});
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status ShaderStub::UniformVec3(ServerContext * context, const UniformVec3Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto uniformName = request->name();
		auto uniformValue = request->value();
		rc->renderObject()->storeUniform(uniformName, glm::vec3{ uniformValue.x(), uniformValue.y(), uniformValue.z() });
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status ShaderStub::UniformVec4(ServerContext * context, const UniformVec4Request * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		auto uniformName = request->name();
		auto uniformValue = request->value();
		rc->renderObject()->storeUniform(uniformName, glm::vec4{ uniformValue.x(), uniformValue.y(), uniformValue.z(), uniformValue.w() });
		this->taskReady();
	};

	return waitForTaskReady(task);
}

Status ShaderStub::UniformMat3x3(ServerContext * context, const UniformMat3x3Request * request, CommonReply * response)
{
	return Status();
}

Status ShaderStub::UniformMat4x4(ServerContext * context, const UniformMat4x4Request * request, CommonReply * response)
{
	return Status();
}

Status ShaderStub::LoadModel(ServerContext * context, const LoadModelRequest * request, CommonReply * response)
{
	auto task = [this, request, response]()
	{
		auto app = Application::current();
		auto rc = std::dynamic_pointer_cast<nb::Rectangle>(app->mainWindow()->getValue<UIElementPtr>(Window::ContentProperty()));
		if (rc)
		{
			rc->setValue<BrushPtr>(Rectangle::FillProperty(), std::make_shared<EffectBrush>());
			rc->renderObject()->setProgram(Programs::model());
			auto sz = rc->getValue<Size>(Shape::ActualSizeProperty());
			auto modelPath = request->modelpath();
			auto texturePath = request->texturepath();
			rc->renderObject()->loadFromFile(modelPath, texturePath);

			glm::mat4 model = glm::mat4(1.0f);
			float strength = 20.0f;
			model = glm::translate(model, glm::vec3(sz.width() / 2, sz.height() / 2, 0));
			model = glm::scale(model, glm::vec3(strength, strength, strength));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			rc->renderObject()->model()->matrix = model;

		}
		this->taskReady();
	};

	return waitForTaskReady(task);
}

ProgramPtr ShaderStub::makeProgram(const std::string &vShaderCode, const std::string &fShaderCode)
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
		return nullptr;
	}
}

void ShaderStub::getUniforms(google::protobuf::Map<std::string, UniformType>* &ref, const std::string &vShaderCode, const std::string &fShaderCode)
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
