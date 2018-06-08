#include "gles/RenderObject.h"
#include "gles/Program.h"
#include "system/Singleton.h"
#include "BatchingsDrawcalls.h"

using nb::gl::Gles::RenderObject;
using nb::gl::Gles::Model;
using nb::gl::Gles::Material;
using nb::gl::Gles::Program;

RenderObject::RenderObject()
: m_bRenderable(false)
, m_Model(NULL)
, m_Material(NULL)
, m_RenderMode(RenderObject::RenderMode_Color)
{
	m_Model->SetListener(this);
	m_Material->SetListener(this);
}

RenderObject::RenderObject(bool bRenderable)
: m_bRenderable(bRenderable)
, m_Model(NULL)
, m_Material(NULL)
, m_RenderMode(RenderObject::RenderMode_Color)
{
	m_Model->SetListener(this);
	m_Material->SetListener(this);
}

RenderObject::RenderObject(Model *model, Material *material)
: m_bRenderable(true)
, m_Model(model)
, m_Material(material)
, m_RenderMode(RenderObject::RenderMode_Color)
{
	m_Model->SetListener(this);
	m_Material->SetListener(this);
}

RenderObject::RenderObject(Model *model, Material *material, bool bRenderable)
: m_bRenderable(bRenderable)
, m_Model(model)
, m_Material(material)
, m_RenderMode(RenderObject::RenderMode_Color)
{
	m_Model->SetListener(this);
	m_Material->SetListener(this);
}

void RenderObject::SetRenderable(bool bRenderable)
{
	m_bRenderable = bRenderable;
}

bool RenderObject::IsRenderable() const
{
	return m_bRenderable;
}

void RenderObject::SetModel(Model *model)
{
	m_Model = model;
}

Model *RenderObject::GetModel() const
{
	return m_Model;
}

void RenderObject::SetMaterial(Material *material)
{
	m_Material = material;
}

Material *RenderObject::GetMaterial() const
{
	return m_Material;
}

void RenderObject::SetRenderMode(RenderObject::RenderMode mode)
{
	m_RenderMode = mode;
}

RenderObject::RenderMode RenderObject::GetRenderMode() const
{
	return m_RenderMode;
}

bool RenderObject::CanBatchWith(const RenderObject *renderObject) const
{
	return this == renderObject;

	///////
	if(GetRenderMode() == RenderMode_Color && renderObject->GetRenderMode() == RenderObject::RenderMode_Color)
	{
		return true;
	}
	else
	{
		return GetMaterial()->Equal(renderObject->GetMaterial());
	}
}

void RenderObject::On_ModelData_Changed(Model::VertexAttributesType type)
{
	nb::System::Singleton<BatchingsDrawcalls>::Current()->UpdateModel(this);
}

void RenderObject::On_Texture_Changed()
{
	nb::System::Singleton<BatchingsDrawcalls>::Current()->UpdateMaterial(this);
}
