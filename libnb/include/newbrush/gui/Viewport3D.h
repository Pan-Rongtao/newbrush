#pragma once
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/ModeVisual3D.h"

namespace nb {

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