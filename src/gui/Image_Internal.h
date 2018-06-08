#pragma once
#include "ElementRender.h"
#include "gui/Image.h"
#include "gui/ImageSource.h"

namespace nb{ namespace gl{namespace Gles {

class RenderObject;
class Quadrangle;

}}}

namespace nb{ namespace Gui{

class Image_Internal : public IElementRender
{
public:
	Image_Internal(Image *pOwner);
	~Image_Internal();

	void OnSourceChanged(Core::PropertyValueChangedEventArgs &args);

private:
	virtual void OnRender(float x, float y);

	Image						*m_owner;
	nb::gl::Gles::RenderObject	*m_GlRenderObject;
	nb::gl::Gles::Quadrangle	*m_GlQuadrangle;
};
		
}}
