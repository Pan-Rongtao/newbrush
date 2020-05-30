/*******************************************************
**	RenderObject
**
**	渲染物
**	
**	渲染物是描述可渲染对象的数据结构
**
**	一般而言，渲染物都有自己的模型结构、材质等
**		
**		
**		潘荣涛
**	
********************************************************/
#pragma once
#include <string>
#include "newbrush/gles/Model.h"
#include "newbrush/gles/Material.h"
#include "newbrush/gles/Camera.h"
#include "newbrush/gles/Projection.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/gles/TextureMipmap.h"

struct aiNode;
struct aiMesh;
struct aiScene;
namespace nb{
	
class NB_API RenderObject
{
public:
	//构建一个空的RenderObject，它的可渲染状态为true
	RenderObject();

	//构建一个空的RenderObject，它的可渲染状态为bRenderable
	RenderObject(std::shared_ptr<Model> model);

	//构建一个RenderObject，它的模型为model，程序为program，可渲染状态为true
	RenderObject(std::shared_ptr<Model> model, std::shared_ptr<Program> program);

public:	
	//从文件中加载
	void loadFromFile(const std::string &modelPath, const std::string &picPath = "");

	//设置是否可渲染，这将决定物体是否绘制
	void setRenderable(bool bRenderable);

	//是否可渲染
	bool renderable() const;

	//设置模型
	void setModel(std::shared_ptr<Model> model);

	//获取模型
	std::shared_ptr<Model> model();

	//设置program
	void setProgram(std::shared_ptr<Program> program);

	//获取program
	std::shared_ptr<Program> program();

	//存储uniform变量，以便下次刷新使用
	void storeUniform(const std::string &name, const var &v);
	
	//绘制，重写此方法以构建自己的渲染方式
	virtual void draw(const Camera &camera, const Projection &projection) const;

private:
	void loopNode(aiNode * node, const aiScene * scene, const std::string &picPath);
	Mesh processMesh(aiMesh * mesh, const aiScene * scene, const std::string &picPath);

	std::shared_ptr<Model>		m_model;
	std::shared_ptr<Program>	m_program;
	std::map<std::string, var>	m_uniforms;
	bool						m_renderable;
};

}
