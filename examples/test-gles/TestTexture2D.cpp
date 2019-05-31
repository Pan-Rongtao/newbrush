#include "TestTexture2D.h"
#include "gles/Texture2D.h"
#include "gles/Egl.h"
#include "gles/Window.h"

using namespace nb::gl;

void TestTexture2D::test()
{
	nb::gl::initialize(std::make_shared<Display>(Display::defaultx()));
	nb::gl::setConfigure(std::make_shared<Configure>(Configure::fromSystemRecommend(0)));
	auto window = std::make_shared<Window>();
	auto surface = std::make_shared<WindowSurface>(window->width(), window->height(), window->handle());
//	nb::gl::makeCurrent(surface, surface, std::make_shared<Context>(nb::gl::getConfigure()));

	Texture2D texture2d;
	int maxWidth = Texture2D::maxWidthSupported();
	int maxHeight = Texture2D::maxHeightSupported();
	printf("Texture2D.maxWidthSupported=%d\nTexture2D.maxHeightSupported=%d\n", maxWidth, maxHeight);
}