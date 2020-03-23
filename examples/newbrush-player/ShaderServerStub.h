#include "grpcpp/grpcpp.h"
#include "Shader.grpc.pb.h"
#include "newbrush/gui/Application.h"
#include "newbrush/gles/SourceDecoder.h"
#include "newbrush/gles/Shader.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/media/EffectBrush.h"
#include "newbrush/media/GradientBrush.h"

using namespace nb;
using namespace google::protobuf;

class ShaderServerStub final : public NBPlayer::Shader::Service
{
	virtual ::grpc::Status BuildShader(::grpc::ServerContext* context, const ::NBPlayer::BuildShaderRequest* request, ::NBPlayer::BuildShaderReply* response) override;
	virtual ::grpc::Status SetUniform(::grpc::ServerContext* context, const ::NBPlayer::SetUniformRequest* request, ::NBPlayer::SetUniformReply* response) override;


	std::shared_ptr<Program> makeProgram(const std::string &vShaderCode, const std::string &fShaderCode);
	void getUniforms(google::protobuf::Map< std::string, ::NBPlayer::BuildShaderReply_ShaderVarType >* &ref, const std::string &vShaderCode, const std::string &fShaderCode);
};