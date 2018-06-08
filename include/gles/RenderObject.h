/*******************************************************
**	RenderObject
**
**	渲染物
**	
**	渲染物是描述可渲染对象的数据结构
**
**	一般而言，渲染物都有自己的模型结构、材质和program等
**		
**		
**		潘荣涛
**	
********************************************************/
#pragma once
#include "system/Global.h"
#include "gles/Model.h"
#include "gles/Material.h"

namespace nb{ namespace gl{ namespace Gles{

class Model;
class Material;
class Program;
class NB_EXPORT RenderObject : public ModelEventListener, public MaterialEventListener
{
public:
	//渲染模式
	enum RenderMode
	{
		RenderMode_Mapping	= 0,		//贴图
		RenderMode_Color	= 1,		//颜色
	};

public:	
	//设置是否可渲染，这将决定物体是否绘制
	void SetRenderable(bool bRenderable);

	//是否可渲染
	bool IsRenderable() const;

	//设置模型
	void SetModel(Model *model);

	//获取模型
	Model *GetModel() const;

	//设置材质
	void SetMaterial(Material *material);

	//获取材质
	Material *GetMaterial() const;

	//设置渲染模式
	void SetRenderMode(RenderMode mode);

	//获取渲染模式
	RenderMode GetRenderMode() const;

	//是否可以进行batching
	bool CanBatchWith(const RenderObject *renderObject) const;

public:
	//构建一个空的RenderObject，它的可渲染状态为true
	RenderObject();

	//构建一个空的RenderObject，它的可渲染状态为bRenderable
	RenderObject(bool bRenderable);

	//构建一个RenderObject，它的模型为model，材质为materia，可渲染状态为true
	RenderObject(Model *model, Material *material);

	//构建一个RenderObject，它的模型为model，材质为materia，可渲染状态为bRenderable
	RenderObject(Model *model, Material *material, bool bRenderable);

private:
	virtual void On_ModelData_Changed(Model::VertexAttributesType type);
	virtual void On_Texture_Changed();

	bool					m_bRenderable;
	Model					*m_Model;
	Material				*m_Material;
	RenderMode				m_RenderMode;
};

}}}
