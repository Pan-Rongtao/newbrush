#pragma once
#include "ElementRender.h"
#include "gles/Quadrangle.h"
#include "gui/Brush.h"
#include "gui/Transform.h"

namespace nb{ namespace gl{ namespace Gles{

class RenderObject;
class Quadrangle;

}}}

namespace nb{ namespace Gui {

class Rectangle;
class Rectangle_Internal : public IElementRender
{
public:
	Rectangle_Internal(Rectangle *owner);
	virtual ~Rectangle_Internal();

	virtual void OnRender(float x, float y);

	void OnFillChanged(nb::Core::PropertyValueChangedEventArgs &args);

private:
	Rectangle						*m_owner;
	nb::gl::Gles::RenderObject		*m_GlRenderObject;
	nb::gl::Gles::Quadrangle		*m_GlQuadrangle;
};

}}
