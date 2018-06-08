#include "gui/Brush.h"
#include "system/System.h"

using namespace nb::Media;

NB_OBJECT_NO_ASSEMBLY_TYPE_IMPLEMENT(Brush, nbObject);

Brush::Brush()
{ 
	SetOpacity(1.0f);
}

Brush::Brush(float opacity)
{
	SetOpacity(opacity);
}

Brush::~Brush()
{

}

void Brush::SetOpacity(float opacity)
{
	m_fOpacity = System::Bound(0.0f, 1.0f, opacity);
}

float Brush::GetOpacity() const
{
	return m_fOpacity;
}
