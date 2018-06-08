#include "Image_Internal.h"
#include "gles/RenderObject.h"
#include "gles/Painter.h"
#include "gles/Quadrangle.h"
#include "gles/Program.h"
#include "gles/Shader.h"
#include "gles/Material.h"
#include "UIElementPrivate.h"

using nb::Math::Vec2;
using nb::Math::Vec3;
using nb::System::Size;
using nb::Gui::Image;
using nb::Gui::Image_Internal;
using nb::gl::Gles::Painter;
using nb::gl::Gles::RenderObject;
using nb::gl::Gles::Program;
using nb::gl::Gles::Shader;
using nb::gl::Gles::Material;
using nb::gl::Gles::Texture2D;
using nb::gl::Gles::Material;

Image_Internal::Image_Internal(Image *owner)
: m_owner(owner)
{
	m_GlQuadrangle = new nb::gl::Gles::Quadrangle();
	m_GlQuadrangle->SetTextureCoordinateAt(0, Vec2(0.0, 1.0));
	m_GlQuadrangle->SetTextureCoordinateAt(1, Vec2(1.0, 1.0));
	m_GlQuadrangle->SetTextureCoordinateAt(2, Vec2(1.0, 0.0));
	m_GlQuadrangle->SetTextureCoordinateAt(3, Vec2(0.0, 0.0));
	m_GlRenderObject = new nb::gl::Gles::RenderObject(m_GlQuadrangle, new Material(Program::Common()));
	m_GlRenderObject->SetRenderMode(RenderObject::RenderMode_Mapping);
	if(m_owner->Source)
		m_GlRenderObject->GetMaterial()->SetTexture(m_owner->Source->GetTexture());
}

Image_Internal::~Image_Internal()
{
	delete m_GlRenderObject;
	delete m_GlQuadrangle;
}

void Image_Internal::OnSourceChanged(nb::Core::PropertyValueChangedEventArgs &args)
{
	m_GlRenderObject->GetMaterial()->SetTexture(((nb::Media::ImageSource *)(args.m_newObject))->GetTexture());
}

void Image_Internal::OnRender(float x, float y)
{
	Size pixcelSize = m_owner->GetPixcelSize();
	Size sz;
	nb::Media::Stretch stretch = m_owner->Stretch();
	switch(stretch)
	{
	case nb::Media::Fill:
		sz = Size(m_owner->GetActualWidth(), m_owner->GetActualHeight());
		break;
	case nb::Media::Origion:
		sz = Size(pixcelSize.GetWidth(), pixcelSize.GetHeight());
		break;
	case nb::Media::Uniform:
		{
			float pixcelRatio = pixcelSize.Width() / pixcelSize.Height();
			float containerRatio = m_owner->GetActualWidth() / m_owner->GetActualHeight();
			if(pixcelRatio < containerRatio)
			{
				sz.Height() = m_owner->GetActualHeight();
				sz.Width() = sz.Height() * pixcelRatio;
				x = x + (m_owner->GetActualWidth() - sz.Width()) / 2;
			}
			else
			{
				sz.Width() = m_owner->GetActualWidth();
				sz.Height() = sz.Width() / pixcelRatio;
				y = y + (m_owner->GetActualHeight() - sz.Height()) / 2;
			}
		}
		break;
	case nb::Media::UniformToFill:
		{
			float pixcelRatio = pixcelSize.Width() / pixcelSize.Height();
			float containerRatio = m_owner->GetActualWidth() / m_owner->GetActualHeight();
			if(pixcelRatio < containerRatio)
			{
				sz.Width() = m_owner->GetActualWidth();
				sz.Height() = sz.Width() / pixcelRatio;
			}
			else
			{
				sz.Height() = m_owner->GetActualHeight();
				sz.Width() = sz.Height() * pixcelRatio;
			}
		}
		break;
	default:	//will never do
		break;
	}

	m_GlQuadrangle->SetPositionAt(0, Vec3(x, y, 0.0f));
	m_GlQuadrangle->SetPositionAt(1, Vec3(x + sz.Width(), y, 0.0f));
	m_GlQuadrangle->SetPositionAt(2, Vec3(x + sz.Width(), y + sz.Height(), 0.0f));
	m_GlQuadrangle->SetPositionAt(3, Vec3(x, y + sz.Height(), 0.0f));

	Painter painter(NULL);
	painter.Paint(m_GlRenderObject);
}
