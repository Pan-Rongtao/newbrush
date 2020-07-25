/*******************************************************
**	Program/Programs
**
**	Program程序
**	
**		程序是是运行于GPU的程序。一般而言，它需要关联上Shader
**	才有意义，link后程序就可以随时使用
**
**	Programs则提供常用的Program对象，如primitive、phong、cube等
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "newbrush/rvl/gles/Shader.h"
#include "glm/glm.hpp"

namespace nb{

class NB_API Program
{
public:
	//nb固定location和locationStr
	static constexpr int nbPositionLocation			= 0;
	static constexpr int nbColorLocation			= 1;
	static constexpr int nbTexCoordLocaltion		= 2;
	static constexpr int nbNormalLocation			= 3;
	static constexpr char *nbPositionLocationStr	= "nbPos";
	static constexpr char *nbColorLocationStr		= "nbColor";
	static constexpr char *nbTexCoordLocaltionStr	= "nbTexCoord";
	static constexpr char *nbNormalLocationStr		= "nbNormal";
	static constexpr char *nbMvpStr					= "nbMvp";
	static constexpr char *nbMStr					= "nbM";
	static constexpr char *nbVStr					= "nbV";
	static constexpr char *nbPStr					= "nbP";

public:
	//构建一个Program，未指定顶点着色器和片元着色器
	Program();

	//构建一个Program，并为它指定了顶点着色器和片元着色器
	Program(VertexShaderPtr verShader, FragmentShaderPtr fragShader);
	virtual ~Program();

public:
	//设置顶点着色器
	void setVertexShader(VertexShaderPtr verShader);

	//获取顶点着色器
	VertexShaderPtr vertexShader();

	//设置片元着色器
	void setFragmentShader(FragmentShaderPtr fragShader);

	//获取片元着色器
	FragmentShaderPtr fragmentShader();

	//链接
	//异常：
	void link();

	//获取program中attribute类型变量sName的位置/地址
	//如果未找到变量，返回-1
	int getAttributeLocation(const char *name) const;

	//获取program中uniform类型变量sName的位置/地址
	//如果未找到变量，返回-1
	int getUniformLocation(const char *name) const;

	//绑定attribute位置
	void bindAttributeLocation(unsigned int location, const char *name);

	//使用
	//异常：
	void use();

	//取消使用
	//异常：
	void disuse();

	//更新位置为location的attribute
	void vertexAttribute(int location, float v);
	void vertexAttribute(int location, const glm::vec2 &vec);
	void vertexAttribute(int location, const glm::vec3 &vec);
	void vertexAttribute(int location, const glm::vec4 &vec);
	void vertexAttributePointer(int location, int dimension, int stride, const void *data);

	//更新位置为location的unform
	//float
	void uniform(int location, float v);
	void uniform(int location, const std::vector<float> &v);
	void uniform(int location, const glm::vec2 &v);
	void uniform(int location, const std::vector<glm::vec2> &v);
	void uniform(int location, const glm::vec3 &v);
	void uniform(int location, const std::vector<glm::vec3> &v);
	void uniform(int location, const glm::vec4 &v);
	void uniform(int location, const std::vector<glm::vec4> &v);

	//int
	void uniform(int location, int v);
	void uniform(int location, const std::vector<int> &v);
	void uniform(int location, const glm::ivec2 &vec);
	void uniform(int location, const std::vector<glm::ivec2> &v);
	void uniform(int location, const glm::ivec3 &vec);
	void uniform(int location, const std::vector<glm::ivec3> &v);
	void uniform(int location, const glm::ivec4 &vec);
	void uniform(int location, const std::vector<glm::ivec4> &v);

	//mat
	void uniform(int location, const glm::mat2x2 &matrix);
	void uniform(int location, const std::vector<glm::mat2x2> &v);
	void uniform(int location, const glm::mat3x3 &matrix);
	void uniform(int location, const std::vector<glm::mat3x3> &v);
	void uniform(int location, const glm::mat4x4 &matrix);
	void uniform(int location, const std::vector<glm::mat4x4> &v);

private:
	VertexShaderPtr	m_vertexShader;
	FragmentShaderPtr	m_fragmentShader;
	unsigned int					m_programHandle;
};

using ProgramPtr = std::shared_ptr<Program>;

class NB_API Programs
{
public:
	//简单program
	static ProgramPtr primitive();

	//渐变图元
	static ProgramPtr gradientPrimitive();

	//图片program
	static ProgramPtr image();

	//phong program
	static ProgramPtr phong();

	//cube program
	static ProgramPtr cube();

	static ProgramPtr model();

	//glyp program
	static ProgramPtr glpy();

private:
	static ProgramPtr compileBindLink(const std::string &vs, const std::string &fs);
};

}
