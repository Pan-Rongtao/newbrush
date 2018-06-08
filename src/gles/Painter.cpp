#include "gles/Painter.h"
#include "system/Singleton.h"
#include "gles/Context.h"
#include "gles/RenderObject.h"
#include "BatchingsDrawcalls.h"

using namespace nb::gl::Gles;

Painter::Painter(const nb::gl::egl::Context *context)
{
}

Painter::~Painter()
{
}

void Painter::Paint(RenderObject *renderObject)
{
	nb::System::Singleton<BatchingsDrawcalls>::Current()->Charge(renderObject);
}
