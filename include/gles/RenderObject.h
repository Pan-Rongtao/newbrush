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
#include "../core/Any.h"
#include "../gles/Model.h"
#include "../gles/Material.h"

struct aiNode;
struct aiMesh;
struct aiScene;
namespace nb{ namespace gl{

class NB_API RenderObject
{
public:
	//构建一个空的RenderObject，它的可渲染状态为true
	RenderObject();

	//构建一个空的RenderObject，它的可渲染状态为bRenderable
	RenderObject(bool bRenderable);

	//构建一个RenderObject，它的模型为model，材质为materia，可渲染状态为true
	RenderObject(std::shared_ptr<Model> model, std::shared_ptr<Material> material);

	//构建一个RenderObject，它的模型为model，材质为materia，可渲染状态为bRenderable
	RenderObject(std::shared_ptr<Model> model, std::shared_ptr<Material> material, bool bRenderable);

public:	
	//从文件中加载
	void loadFromFile(const std::string &path);

	//设置是否可渲染，这将决定物体是否绘制
	void setRenderable(bool bRenderable);

	//是否可渲染
	bool renderable() const;

	//设置模型
	void setModel(std::shared_ptr<Model> model);

	//获取模型
	std::shared_ptr<Model> model();

	//设置材质
	void setMaterial(std::shared_ptr<Material> material);

	//获取材质
	std::shared_ptr<Material> material();

	//存储变量
	void set(const std::string &name, const Any &v);
	
	//绘制，重写此方法以构建自己的渲染方式
	virtual void draw() const;

private:
	void loopNode(aiNode * node, const aiScene * scene);
	Mesh processMesh(aiMesh * mesh, const aiScene * scene);

	bool						m_renderable;
	std::shared_ptr<Model>		m_model;
	std::shared_ptr<Material>	m_material;
	std::map<std::string, Any>	m_uniforms;
};

}}
