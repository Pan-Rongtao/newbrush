#include "GlesProgram.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GLES2/gl2.h>

namespace nb{ namespace gl{ namespace Gles{

//--------GlesShaderObject--------//
GlesShaderObject::GlesShaderObject()
: m_ShaderHandle(0)
{

}

GlesShaderObject::~GlesShaderObject()
{
if(m_ShaderHandle != 0)
{
	glDeleteShader(m_ShaderHandle);
	m_ShaderHandle = 0;
}
}

void GlesShaderObject::CompileShader(GLenum type, const char* sShaderStr)
{
GLuint shader;
GLint compiled;
shader = glCreateShader(type);
if (shader == 0)
{
	throw nb::Core::ExceptionPtr::GetPtrInstance("glCreateShader() -- return fail");
}
glShaderSource(shader, 1, &sShaderStr, NULL);
glCompileShader(shader);
glGetShaderiv (shader, GL_COMPILE_STATUS, &compiled);
if (!compiled)
{
  GLint infoLen = 0;
  std::string comliteInfo;
  glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLen);
  if (infoLen > 1)
  {
	 char* infoLog = (char*)malloc(sizeof(char) * infoLen);
	 glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
	 comliteInfo = infoLog;
	 free(infoLog);
	 
  }
  glDeleteShader(shader);

  comliteInfo = "glCompileShader() -- fail, reason is:" + comliteInfo;
  throw nb::Core::ExceptionPtr::GetPtrInstance(comliteInfo);
}

if(m_ShaderHandle != 0)
{
	glDeleteShader(m_ShaderHandle);
}

m_ShaderHandle = shader;
}

std::string GlesShaderObject::ReadShaderSrcFromFile(const std::string& sFilePath)
{
FILE * fptr = NULL;
fptr = fopen(sFilePath.c_str(), "rb");
if (fptr == NULL)
{
	std::string expStr = "Cannot open file:" + sFilePath;
	throw nb::Core::ExceptionPtr::GetPtrInstance(expStr);
}
int length;
fseek(fptr, 0, SEEK_END);
length = ftell(fptr);
fseek(fptr, 0 ,SEEK_SET);

length ++;
char * shaderSource = (char*)malloc(sizeof (char) * length);
if (shaderSource == NULL)
{
	throw nb::Core::ExceptionPtr::GetPtrInstance("Out of memory,cannot malloc!");
}

memset(shaderSource, 0, length);
fread(shaderSource, length-1, 1, fptr);

std::string sRet = shaderSource;
free(shaderSource);
fclose(fptr);

return sRet;
}

bool GlesShaderObject::IsValid()
{
return (m_ShaderHandle == 0) ? false : true;
}



//--------GlesVertexShader--------//
GlesVertexShader::GlesVertexShader()
{

}

GlesVertexShader::GlesVertexShader(const std::string& sVertextShaderSrc)
{
GlesShaderObject::CompileShader(GL_VERTEX_SHADER,sVertextShaderSrc.c_str());
}

GlesVertexShader * GlesVertexShader::ReadShaderFromPath(const std::string& sVertexShaderFilePath)
{
std::string sVertexSource = GlesShaderObject::ReadShaderSrcFromFile(sVertexShaderFilePath);
GlesVertexShader * vShader = new GlesVertexShader();
vShader->CompileShader(GL_VERTEX_SHADER,sVertexSource.c_str());
return vShader;
}


//--------GlesFragmentShader--------//
GlesFragmentShader::GlesFragmentShader()
{

}

GlesFragmentShader::GlesFragmentShader(const std::string& sFragmentShaderSrc)
{
GlesShaderObject::CompileShader(GL_FRAGMENT_SHADER,sFragmentShaderSrc.c_str());
}

GlesFragmentShader * GlesFragmentShader::ReadShaderFromPath(const std::string& sFragmentShaderFilePath)
{
std::string sFragmentSource = GlesShaderObject::ReadShaderSrcFromFile(sFragmentShaderFilePath);
GlesFragmentShader * fShader= new GlesFragmentShader();
fShader->CompileShader(GL_FRAGMENT_SHADER,sFragmentSource.c_str());
return fShader;
}


//--------GlesProgram--------//
GlesProgram::GlesProgram()
: m_ProgramObject(0)
{

}

GlesProgram * GlesProgram::CreateWithByteArrays(const char* vShaderByteArray, const char* fShaderByteArray)
{
GlesProgram * glProgram = new GlesProgram();
glProgram->m_pVertexShader = new GlesVertexShader(vShaderByteArray);
glProgram->m_pFragmentShader = new GlesFragmentShader(fShaderByteArray);
try{
	glProgram->CompileProgram();
}
catch(nb::Core::ExceptionPtr ex)
{
	std::cout << ex->GetErrorMessageData() << std::endl;
}
return glProgram;
}

GlesProgram * GlesProgram::CreateWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename)
{
GlesProgram * glProgram = new GlesProgram();
glProgram->m_pVertexShader = GlesVertexShader::ReadShaderFromPath(vShaderFilename);
glProgram->m_pFragmentShader = GlesFragmentShader::ReadShaderFromPath(fShaderFilename);
try{
	glProgram->CompileProgram();
}
catch(nb::Core::ExceptionPtr ex)
{
	std::cout << ex->GetErrorMessageData() << std::endl;
}
return glProgram;
}

GlesProgram::~GlesProgram()
{
if (IsValid())
{
	glDeleteProgram(m_ProgramObject);
}
}

int GlesProgram::GetAttribLocation(const std::string &sName)
{
Use();
return glGetAttribLocation(m_ProgramObject, sName.data());
}

int GlesProgram::GetUniformLocation(const std::string &sName)
{
Use();
return glGetUniformLocation(m_ProgramObject, sName.data());
}

void GlesProgram::Use()
{
glUseProgram(m_ProgramObject);
}

void GlesProgram::UnUse()
{
glUseProgram(0);
}
	
bool GlesProgram::IsValid() const
{
return (m_ProgramObject == 0) ? false : true;
}

void GlesProgram::CompileProgram()
{
GLuint programObject;
GLint linked;

programObject = glCreateProgram();
if ( programObject == 0 )
{
	throw nb::Core::ExceptionPtr::GetPtrInstance("glCreateProgram() -- return fail");
}

if((!m_pVertexShader->IsValid()) ||(!m_pFragmentShader->IsValid())) 
{
	throw nb::Core::ExceptionPtr::GetPtrInstance("vertex shader or fragment shader is not valid now!");
}

glAttachShader(programObject, m_pVertexShader->Get());
glAttachShader(programObject, m_pFragmentShader->Get());

glLinkProgram(programObject);
glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

if ( !linked )
{
  GLint infoLen = 0;
  std::string sLinkInfo;
  glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
  if(infoLen > 1)
  {
	  char* infoLog =(char*)malloc(sizeof(char) * infoLen);
	  glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
	  sLinkInfo = infoLog;
	  free(infoLog);
  }
  glDeleteProgram(programObject);

  sLinkInfo = "glLinkProgram() -- fail, reason is:" + sLinkInfo;
  throw nb::Core::ExceptionPtr::GetPtrInstance(sLinkInfo);
}

if(m_ProgramObject != 0)
{
	glDeleteProgram(m_ProgramObject);
}
m_ProgramObject = programObject;
}

}}}