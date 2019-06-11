#include "gui/Ellipse.h"
#include "gles/Ellipse.h"
#include "gles/Program.h"
#include "gles/Context.h"
#include "gles/Texture2D.h"

using namespace nb::core;
using namespace nb::gui;
Ellipse::Ellipse()
{
}

void Ellipse::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	Rect rc(Offset().x(), Offset().y(), ActualSize);
	Renderer()->setModel(std::make_shared<gl::Ellipse>(rc.center().x(), rc.center().y(), rc.width() / 2, rc.height() / 2, false));
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::Programs::primitive()));
	drawContext->queue(Renderer());

	if (!Fill())
		return;

	if (typeid(*Fill()) == typeid(ImageBrush))
	{
		auto imgbrush = std::dynamic_pointer_cast<ImageBrush>(Fill());
		Renderer()->storage()->insert("unif_colorMode", 0);
		if (imgbrush->Source())
			Renderer()->material()->textures().push_back(std::make_shared<gl::Texture2D>(*(imgbrush->Source()->Bm())));
	}
	else if (typeid(*Fill()) == typeid(SolidColorBrush))
	{
		auto solidbrush = std::dynamic_pointer_cast<SolidColorBrush>(Fill());
		auto color = solidbrush->Color();
		Renderer()->storage()->insert("unif_colorMode", 1);
		Renderer()->model()->mesh(0).unifyColor({ color.redF(), color.greenF(), color.blueF(), color.alphaF() });
	}
}

Size Ellipse::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Ellipse::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}
