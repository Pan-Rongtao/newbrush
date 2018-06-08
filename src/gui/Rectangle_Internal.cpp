#include "Rectangle_Internal.h"
#include "gles/Shader.h"
#include "gles/Program.h"
#include "gles/Painter.h"
#include "gles/Material.h"
#include "gles/RenderObject.h"
#include "gles/Texture2D.h"
#include "gui/Brush.h"
#include "gui/SolidColorBrush.h"
#include "gui/ImageBrush.h"
#include "gui/Rectangle.h"

using nb::Gui::Rectangle_Internal;
using nb::Math::Vec2;
using nb::Math::Vec3;
using nb::Math::Vec4;
using nb::Math::Matrix4x4;
using nb::Media::Brush;
using nb::Media::SolidColorBrush;
using nb::Media::ImageBrush;
using nb::gl::Gles::RenderObject;
using nb::gl::Gles::Program;
using nb::gl::Gles::Shader;
using nb::gl::Gles::Material;
using nb::gl::Gles::Painter;

Rectangle_Internal::Rectangle_Internal(nb::Gui::Rectangle *owner)
: m_owner(owner)
{
	m_GlQuadrangle = new nb::gl::Gles::Quadrangle();
	m_GlRenderObject = new nb::gl::Gles::RenderObject(m_GlQuadrangle, new Material(Program::Common()));
	m_GlQuadrangle->SetTextureCoordinateAt(0, Vec2(0.0, 1.0));
	m_GlQuadrangle->SetTextureCoordinateAt(1, Vec2(1.0, 1.0));
	m_GlQuadrangle->SetTextureCoordinateAt(2, Vec2(1.0, 0.0));
	m_GlQuadrangle->SetTextureCoordinateAt(3, Vec2(0.0, 0.0));
}

Rectangle_Internal::~Rectangle_Internal()
{
	delete m_GlQuadrangle;
	delete m_GlRenderObject;
}

void Rectangle_Internal::OnFillChanged(nb::Core::PropertyValueChangedEventArgs &args)
{
	nb::Media::Brush *brush = m_owner->Fill;
	if(dynamic_cast<SolidColorBrush *>(brush))
	{
		m_GlRenderObject->SetRenderMode(RenderObject::RenderMode_Color);
		nb::System::Color clr = dynamic_cast<SolidColorBrush *>(brush)->GetColor();
		m_GlQuadrangle->UnifyColor(Vec4(clr.GetRedF(), clr.GetGreenF(), clr.GetBlueF(), clr.GetAlphaF()));
	}
	else if(dynamic_cast<ImageBrush *>(brush))
	{
		m_GlRenderObject->SetRenderMode(RenderObject::RenderMode_Mapping);
		nb::gl::Gles::Texture2D *texture = dynamic_cast<ImageBrush *>(brush)->GetImageSource()->GetTexture();
		m_GlRenderObject->GetMaterial()->SetTexture(texture);
	}
}

void Rectangle_Internal::OnRender(float x, float y)
{
	m_GlQuadrangle->SetPositionAt(0, Vec3(x, y, 0.0f));
	m_GlQuadrangle->SetPositionAt(1, Vec3(x + m_owner->GetActualWidth(), y, 0.0f));
	m_GlQuadrangle->SetPositionAt(2, Vec3(x + m_owner->GetActualWidth(), y + m_owner->GetActualHeight(), 0.0f));
	m_GlQuadrangle->SetPositionAt(3, Vec3(x, y + m_owner->GetActualHeight(), 0.0f));
	Painter painter(NULL);
	painter.Paint(m_GlRenderObject);
}
