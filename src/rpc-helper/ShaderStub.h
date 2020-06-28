#include "Shader.grpc.pb.h"
#include "StubBase.h"

using namespace nbrpc;
class ShaderStub : public ShaderRpc::Service, public StubBase
{
	virtual Status BuildShader(ServerContext* context, const BuildShaderRequest* request, BuildShaderReply* response);
	virtual Status UniformBool(ServerContext* context, const UniformBoolRequest* request, CommonReply* response);
	virtual Status UniformFloat(ServerContext* context, const UniformFloatRequest* request, CommonReply* response);
	virtual Status UniformInteger(ServerContext* context, const UniformIntegerRequest* request, CommonReply* response);
	virtual Status UniformVec2(ServerContext* context, const UniformVec2Request* request, CommonReply* response);
	virtual Status UniformVec3(ServerContext* context, const UniformVec3Request* request, CommonReply* response);
	virtual Status UniformVec4(ServerContext* context, const UniformVec4Request* request, CommonReply* response);
	virtual Status UniformMat3x3(ServerContext* context, const UniformMat3x3Request* request, CommonReply* response);
	virtual Status UniformMat4x4(ServerContext* context, const UniformMat4x4Request* request, CommonReply* response);
	virtual Status LoadModel(ServerContext* context, const LoadModelRequest* request, CommonReply* response);

	ProgramPtr makeProgram(const std::string &vShaderCode, const std::string &fShaderCode);
	void getUniforms(google::protobuf::Map< std::string, UniformType >* &ref, const std::string &vShaderCode, const std::string &fShaderCode);
};