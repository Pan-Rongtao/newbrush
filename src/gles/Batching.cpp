#include "Batching.h"
#include "gles/RenderObject.h"
#include "gles/Model.h"
#include "gles/Material.h"
#include "gles/Program.h"
#include "gles/Texture.h"
#include <GLES2/gl2.h>
#include "system/Singleton.h"
#include "gles/Projection.h"
#include "gles/Camera.h"
#include <algorithm>

using nb::Math::Matrix4x4;
using nb::gl::Gles::Batching;
using nb::gl::Gles::RenderObject;
using nb::gl::Gles::Model;
using nb::gl::Gles::Program;
using nb::gl::Gles::Texture;
using nb::gl::Gles::PerspectiveProjection;
using nb::gl::Gles::Camera;

Batching::Batching()
: m_nActualIndicesCount(0)
{
}

Batching::~Batching()
{
}
//never do this bellow
Batching::Batching(const Batching &other)
{
}
void Batching::operator = (const Batching &other)
{
}

void Batching::Charge(RenderObject *renderObject)
{
	if(std::find(m_ChargedRenderObjects.begin(), m_ChargedRenderObjects.end(), renderObject) != m_ChargedRenderObjects.end())
		return;

	Model *model = renderObject->GetModel();
	int oneModelSize = model->GetVertexStrideUnit() * model->GetVertexCount();
	m_ModelsDatas.insert(m_ModelsDatas.end(), model->GetData(), model->GetData() + oneModelSize);
	IndicesSequece indices = model->VertextsSequenceOverride();
	for(int i = 0; i != indices.GetSize(); ++i)
	{
		unsigned short one = m_nActualIndicesCount + indices[i];
		m_ModelsIndicesSequence.push_back(one);
	}
	m_ChargedRenderObjects.push_back(renderObject);
	m_nActualIndicesCount += model->GetVertexCount();
}

void Batching::Eject(RenderObject *renderObject)
{
	for(int i = 0; i != m_ChargedRenderObjects.size(); ++i)
	{
		if(m_ChargedRenderObjects[i] == renderObject)
		{
			Model *model = renderObject->GetModel();
			int oneModelSize = model->GetVertexStrideUnit() * model->GetVertexCount();
			m_ModelsDatas.erase(m_ModelsDatas.begin() + i * oneModelSize, m_ModelsDatas.begin() + (i + 1) * oneModelSize);
			m_ChargedRenderObjects.erase(m_ChargedRenderObjects.begin() + i);
			m_nActualIndicesCount -= model->GetVertexCount();
			break;
		}
	}

}

void Batching::UpdateModel(RenderObject *renderObject)
{
	for(int i = 0; i != m_ChargedRenderObjects.size(); ++i)
	{
		if(m_ChargedRenderObjects[i] == renderObject)
		{
			Model *model = renderObject->GetModel();
			int oneModelSize = model->GetVertexStrideUnit() * model->GetVertexCount();
			memcpy(&(m_ModelsDatas[0]) + (i * oneModelSize), model->GetData(), oneModelSize * sizeof(float));
			
			break;
		}
	}
	
}

int Batching::GetObjectsCount() const
{
	return (int)m_ChargedRenderObjects.size();
}

const RenderObject *Batching::GetRenderObejct(int index) const
{
	return (index >= 0 && index < (int)m_ChargedRenderObjects.size()) ? m_ChargedRenderObjects[index] : NULL;
}

int Batching::Find(RenderObject *renderObject)
{
	std::vector<RenderObject *>::const_iterator iterFind = std::find(m_ChargedRenderObjects.begin(), m_ChargedRenderObjects.end(), renderObject);
	return iterFind == m_ChargedRenderObjects.end() ? -1 : int(iterFind - m_ChargedRenderObjects.begin());
}

void Batching::Draw() const
{
	if(m_ChargedRenderObjects.empty())	return;

	Model *model = m_ChargedRenderObjects[0]->GetModel();
	Program *program = m_ChargedRenderObjects[0]->GetMaterial()->GetProgram();
	Texture *texture = m_ChargedRenderObjects[0]->GetMaterial()->GetTexture();
	int nPos = program->GetAttributeLocation("attr_position");
	int nColor = program->GetAttributeLocation("attr_color");
	int nTexture = program->GetAttributeLocation("attr_textureCoord");
	int nMvp = program->GetUniformLocation("unif_mvp");
	int nColorMode = program->GetUniformLocation("unif_colorMode");

//	program->Uniform(nMvp, matModel);
	Matrix4x4 matMVP = PerspectiveProjection().GetMatrix() * Camera().GetMatrix() * model->GetMatrix();
	program->Use();
	program->Uniform(nMvp, matMVP);
	program->VertexAttributePointer(nPos, Model::PositionDimension(), model->GetVertexStrideUnit() * sizeof(float), &(m_ModelsDatas[0]));
	program->VertexAttributePointer(nColor, Model::ColorDimension(), model->GetVertexStrideUnit() * sizeof(float), &(m_ModelsDatas[Model::PositionDimension()]));
	program->Uniform(nColorMode, m_ChargedRenderObjects[0]->GetRenderMode());
	if(texture)
	{
		texture->Bind();
		program->VertexAttributePointer(nTexture, Model::TextureCoordinateDimension(), model->GetVertexStrideUnit() * sizeof(float), &(m_ModelsDatas[Model::PositionDimension() + Model::ColorDimension()]));
		
	}
	glDrawElements(GL_TRIANGLES, (int)m_ModelsIndicesSequence.size(), GL_UNSIGNED_SHORT, &(m_ModelsIndicesSequence[0]));
	if(texture)
		texture->Unbind();
	program->UnUse();
}
