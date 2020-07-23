#include "newbrush/gui/Viewport3D.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/media/Camera.h"
#include "newbrush/gui/ModeVisual3D.h"

using namespace nb;

DependencyPropertyPtr Viewport3D::CameraProperty()
{
	static auto dp = DependencyProperty::registerDependency<Viewport3D, std::shared_ptr<Camera3D>>("Camera", nullptr, nullptr);
	return dp;
}

std::vector<ModeVisual3DPtr>& Viewport3D::children()
{
	return m_children;
}

void Viewport3D::onRender(DrawingContextPtr dc)
{
}
