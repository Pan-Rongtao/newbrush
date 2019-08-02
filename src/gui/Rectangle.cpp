#include "gui/Rectangle.h"
#include "gles/Quadrangle.h"
#include "gles/Program.h"
#include "gles/Context.h"
#include "gles/Texture2D.h"

using namespace nb::core;
using namespace nb::gl;
using namespace nb::gui;

Rectangle::Rectangle()
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	Rect rc(Offset().x(), Offset().y(), ActualSize);
	Renderer()->setModel(std::make_shared<gl::Quadrangle>(glm::vec2(rc.left(), rc.bottom()), glm::vec2(rc.right(), rc.bottom()), 
		glm::vec2(rc.right(), rc.top()), glm::vec2(rc.left(), rc.top())));
	Renderer()->setMaterial(std::make_shared<gl::Material>(Programs::primitive()));
	drawContext->queue(Renderer());

	if (!Fill())
		return;

	if (typeid(*Fill()) == typeid(ImageBrush))
	{
		auto imgbrush = std::dynamic_pointer_cast<ImageBrush>(Fill());
		Renderer()->storage()->set(nb::gl::Program::nbColorModeLocationStr, 0);
		if(imgbrush->Source())
			Renderer()->material()->textures().push_back(std::make_shared<Texture2D>(*(imgbrush->Source()->Bm())));
	}
	else if (typeid(*Fill()) == typeid(SolidColorBrush))
	{
		auto solidbrush = std::dynamic_pointer_cast<SolidColorBrush>(Fill());
		auto color = solidbrush->Color();
		Renderer()->storage()->set(nb::gl::Program::nbColorModeLocationStr, 1);
		Renderer()->model()->meshes()[0].unifyColor({ color.redF(), color.greenF(), color.blueF(), color.alphaF() });
	}
}

Size Rectangle::measureOverride(const Size & availableSize)
{
	m_availableSize = availableSize;
	return availableSize;
}

Size Rectangle::arrangeOverride(const Size & finalSize)
{
	return m_availableSize;
}
