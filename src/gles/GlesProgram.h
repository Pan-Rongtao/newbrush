#pragma once

#include "core/Object.h"
#include "core/Exception.h"
#include <string>

namespace nb{ namespace gl{ namespace Gles{

//------------------GlesShaderObject class------------------//
class GlesShaderObject : public nbObject
{
public:
	GlesShaderObject();

	virtual ~GlesShaderObject();

	bool IsValid();

	unsigned int Get() {return m_ShaderHandle;}

protected:
	void CompileShader(unsigned int type, const char* sShaderStr);

	static std::string ReadShaderSrcFromFile(const std::string& sFilePath);

private:
	unsigned int m_ShaderHandle;
};

typedef nbObjectPtrDerive<GlesShaderObject, nbObjectPtr> GlesShaderObjectPtr;


//------------------GlesVertexShader class------------------//
class GlesVertexShader : public GlesShaderObject 
{
public:
	GlesVertexShader();

	GlesVertexShader(const std::string& sVertextShaderSrc);

	static GlesVertexShader * ReadShaderFromPath(const std::string& sVertexShaderFilePath);
};

typedef nbObjectPtrDerive<GlesVertexShader, GlesShaderObjectPtr> GlesVertexShaderPtr;


//------------------GlesFragmentShader class------------------//
class GlesFragmentShader : public GlesShaderObject 
{
public:
	GlesFragmentShader();

	GlesFragmentShader(const std::string& sFragmentShaderSrc);

	static GlesFragmentShader * ReadShaderFromPath(const std::string& sFragmentShaderFilePath);
};
typedef nbObjectPtrDerive<GlesFragmentShader, GlesShaderObjectPtr> GlesFragmentShaderPtr;


//------------------GlesProgram class------------------//
class GlesProgram : public nbObject
{
public:
	GlesProgram();

	~GlesProgram();

	static GlesProgram * CreateWithByteArrays(const char* vShaderByteArray, const char* fShaderByteArray);

	static GlesProgram * CreateWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename);

	//获取program中attribute类型变量sName的位置/地址
	//如果未找到变量，返回-1
	int GetAttribLocation(const std::string &sName);

	//获取program中uniform类型变量sName的位置/地址
	//如果未找到变量，返回-1
	int GetUniformLocation(const std::string &sName);

	//之后将私有化Use()和UnUse(),内部自己保证use和unuse的时机
	void Use();

	void UnUse();
	
	bool IsValid() const;

private:
	void CompileProgram();

	GlesVertexShaderPtr							m_pVertexShader;
	GlesFragmentShaderPtr						m_pFragmentShader;
	unsigned int								m_ProgramObject;
};

typedef nbObjectPtrDerive<GlesProgram, nbObjectPtr> GlesProgramPtr;

}}}
