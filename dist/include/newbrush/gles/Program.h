/*******************************************************
**	Program
**
**	程序
**	
**		程序是是运行于GPU的程序。一般而言，它需要关联上Shader
**	才有意义，link后程序就可以随时使用
**
**	Program（程序）
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "../core/Def.h"
#include "../core/Vec2.h"
#include "../core/Vec3.h"
#include "../core/Vec4.h"
#include "../core/Matrix2x2.h"
#include "../core/Matrix3x3.h"
#include "../core/Matrix4x4.h"
#include "SourceDecoder.h"

namespace nb{ namespace gl{

class VertexShader;
class FragmentShader;
class NB_API Program
{
public:
	enum AttributeLocation
	{
		positionLocation	= 0,	//"nb_Position"
		colorLocation,				//"nb_Color"
		texCoordLocaltion,			//"nb_TextCoord"
		normalLocation,				//"nb_Normal"
	};

public:
	//构建一个Program，未指定顶点着色器和片元着色器
	Program();

	//构建一个Program，并为它指定了顶点着色器和片元着色器
	Program(std::shared_ptr<VertexShader> verShader, std::shared_ptr<FragmentShader> fragShader);
	~Program();

public:
	//设置顶点着色器
	void setVertexShader(std::shared_ptr<VertexShader> verShader);

	//获取顶点着色器
	std::shared_ptr<VertexShader> vertexShader();

	//设置片元着色器
	void setFragmentShader(std::shared_ptr<FragmentShader> fragShader);

	//获取片元着色器
	std::shared_ptr<FragmentShader> fragmentShader();

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
	void vertexAttribute(int location, const nb::core::Vec2 &vec);
	void vertexAttribute(int location, const nb::core::Vec3 &vec);
	void vertexAttribute(int location, const nb::core::Vec4 &vec);
	void vertexAttribute(int location, nb::core::Vec2 *vec);
	void vertexAttribute(int location, nb::core::Vec3 *vec);
	void vertexAttribute(int location, nb::core::Vec4 *vec);
	void vertexAttributePointer(int location, int dimension, int stride, const void *data);

	//更新位置为location的unform
	void uniform(int location, float v);
	void uniform(int location, float *v, int count);
	void uniform(int location, const nb::core::Vec2 &vec);
	void uniform(int location, nb::core::Vec2 *vec, int count);
	void uniform(int location, const nb::core::Vec3 &vec);
	void uniform(int location, nb::core::Vec3 *vec, int count);
	void uniform(int location, const nb::core::Vec4 &vec);
	void uniform(int location, nb::core::Vec4 *vec, int count);

	void uniform(int location, int v);
	void uniform(int location, int *v, int count);
	void uniform(int location, const nb::core::Vec2I &vec);
	void uniform(int location, nb::core::Vec2I *vec, int count);
	void uniform(int location, const nb::core::Vec3I &vec);
	void uniform(int location, nb::core::Vec3I *vec, int count);
	void uniform(int location, const nb::core::Vec4I &vec);
	void uniform(int location, nb::core::Vec4I *vec, int count);

	void uniform(int location, const nb::core::Matrix2x2 &matrix);
	void uniform(int location, nb::core::Matrix2x2 *matrix, int count);
	void uniform(int location, const nb::core::Matrix3x3 &matrix);
	void uniform(int location, nb::core::Matrix3x3 *matrix, int count);
	void uniform(int location, const nb::core::Matrix4x4 &matrix);
	void uniform(int location, nb::core::Matrix4x4 *matrix, int count);

	//解析并提交所有的uniform变量
	void uniformDefault();

private:
	std::shared_ptr<VertexShader>	m_VertexShader;
	std::shared_ptr<FragmentShader>	m_FragmentShader;
	unsigned int					m_ProgramHandle;
};

}}
