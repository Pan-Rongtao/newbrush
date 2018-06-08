/*******************************************************
**	Program
**
**	程序
**	
**		程序是是运行于GPU的程序。一般而言，它需要关联上Shader
**	才有意义，link后程序就可以随时使用
**
**	Program（程序）
**	ProgramFactory（程序工厂）
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "core/NewBrushDef.h"
#include "math/Vec2.h"
#include "math/Vec2I.h"
#include "math/Vec3.h"
#include "math/Vec3I.h"
#include "math/Vec4.h"
#include "math/Vec4I.h"
#include "math/Matrix2x2.h"
#include "math/Matrix3x3.h"
#include "math/Matrix4x4.h"

namespace nb{ namespace gl{ namespace Gles{

class VertexShader;
class FragmentShader;
class NB_EXPORT Program
{
public:
	//设置顶点着色器和片元着色器
	void SetVertexShader(VertexShader *verShader);
	void SetFragmentShader(FragmentShader *fragShader);
	void SetShader(VertexShader *verShader, FragmentShader *fragShader);

	//链接
	//异常：
	void Link();

	//获取program中attribute类型变量sName的位置/地址
	//如果未找到变量，返回-1
	int GetAttributeLocation(const char *name) const;

	//获取program中uniform类型变量sName的位置/地址
	//如果未找到变量，返回-1
	int GetUniformLocation(const char *name) const;

	//使用
	//异常：
	void Use();

	//取消使用
	//异常：
	void UnUse();

	//是否与program相同
	bool Equal(Program *program) const;

	//更新位置为location的attribute
	void VertexAttribute(int location, float v);
	void VertexAttribute(int location, const nb::Math::Vec2 &vec);
	void VertexAttribute(int location, const nb::Math::Vec3 &vec);
	void VertexAttribute(int location, const nb::Math::Vec4 &vec);
	void VertexAttribute(int location, nb::Math::Vec2 *vec);
	void VertexAttribute(int location, nb::Math::Vec3 *vec);
	void VertexAttribute(int location, nb::Math::Vec4 *vec);
	void VertexAttributePointer(int location, int dimension, int stride, const void *data);

	//更新位置为location的unform
	void Uniform(int location, float v);
	void Uniform(int location, float *v, int count);
	void Uniform(int location, const nb::Math::Vec2 &vec);
	void Uniform(int location, nb::Math::Vec2 *vec, int count);
	void Uniform(int location, const nb::Math::Vec3 &vec);
	void Uniform(int location, nb::Math::Vec3 *vec, int count);
	void Uniform(int location, const nb::Math::Vec4 &vec);
	void Uniform(int location, nb::Math::Vec4 *vec, int count);

	void Uniform(int location, int v);
	void Uniform(int location, int *v, int count);
	void Uniform(int location, const nb::Math::Vec2I &vec);
	void Uniform(int location, nb::Math::Vec2I *vec, int count);
	void Uniform(int location, const nb::Math::Vec3I &vec);
	void Uniform(int location, nb::Math::Vec3I *vec, int count);
	void Uniform(int location, const nb::Math::Vec4I &vec);
	void Uniform(int location, nb::Math::Vec4I *vec, int count);

	void Uniform(int location, const nb::Math::Matrix2x2 &matrix);
	void Uniform(int location, nb::Math::Matrix2x2 *matrix, int count);
	void Uniform(int location, const nb::Math::Matrix3x3 &matrix);
	void Uniform(int location, nb::Math::Matrix3x3 *matrix, int count);
	void Uniform(int location, const nb::Math::Matrix4x4 &matrix);
	void Uniform(int location, nb::Math::Matrix4x4 *matrix, int count);

public:
	//构建一个Program，未指定顶点着色器和片元着色器
	Program();

	//构建一个Program，并为它指定了顶点着色器和片元着色器
	Program(VertexShader *verShader, FragmentShader *fragShader);
	~Program();

public:
	static Program *Common();

private:
	VertexShader	*m_VertexShader;
	FragmentShader	*m_FragmentShader;
	unsigned int	m_ProgramHandle;
};

}}}
