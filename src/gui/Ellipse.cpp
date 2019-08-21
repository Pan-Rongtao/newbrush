#include "gui/Ellipse.h"
#include "gles/Ellipse.h"
#include "gles/Program.h"
#include "gles/Context.h"
#include "gles/Texture2D.h"

using namespace nb;
using namespace nb::gui;
Ellipse::Ellipse()
{
}

void Ellipse::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	Rect rc(Offset().x(), Offset().y(), ActualSize());
	Renderer()->setModel(std::make_shared<gl::Ellipse>(static_cast<float>(rc.center().x()), static_cast<float>(rc.center().y()), static_cast<float>(rc.width() / 2), static_cast<float>(rc.height() / 2), false));
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::Programs::primitive()));
	drawContext->queue(Renderer());

	if (!Fill())
		return;

	if (typeid(*Fill()) == typeid(ImageBrush))
	{
		auto imgbrush = std::dynamic_pointer_cast<ImageBrush>(Fill());
		Renderer()->storage()->set(nb::gl::Program::nbColorModeLocationStr, 0);
		if (imgbrush->Source())
			Renderer()->material()->textures().push_back(std::make_shared<gl::Texture2D>(*(imgbrush->Source()->Bm())));
	}
	else if (typeid(*Fill()) == typeid(SolidColorBrush))
	{
		auto solidbrush = std::dynamic_pointer_cast<SolidColorBrush>(Fill());
		auto color = solidbrush->Color();
		Renderer()->storage()->set(nb::gl::Program::nbColorModeLocationStr, 1);
		Renderer()->model()->meshes()[0].unifyColor({ color.redF(), color.greenF(), color.blueF(), color.alphaF() });
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
