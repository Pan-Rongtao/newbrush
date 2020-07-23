#pragma once
#include "UIElement.h"

namespace nb {

class ModeVisual3D;
using ModeVisual3DPtr = std::shared_ptr<ModeVisual3D>;
class Viewport3D : public UIElement
{
public:
	DependencyPropertyPtr CameraProperty();		//…„œÒÕ∑“¿¿µ Ù–‘

	std::vector<ModeVisual3DPtr> &children();

protected:
	virtual void onRender(DrawingContextPtr dc) override;


private:
	std::vector<ModeVisual3DPtr> m_children;
};

}