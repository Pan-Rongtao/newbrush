#include "newbrush/gles/SourceDecoder.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Shader.h"
#include <vector>
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test nb::SourceDecoder", "[SourceDecoder]")
{
/*	nb::gl::initialize(std::make_shared<Display>(Display::defaultx()));
	nb::gl::setConfigure(std::make_shared<Configure>(Configure::fromSystemRecommend(0)));
	auto window = std::make_shared<Window>();
	auto surface = std::make_shared<WindowSurface>(window->width(), window->height(), window->handle());
	nb::gl::makeCurrent(surface, surface, std::make_shared<Context>(nb::gl::getConfigure()));

	SourceDecoder sd;
	auto program0 = Programs::phong();
	auto k = nb::getTickCount();
	sd.decode(program0->vertexShader()->source(), program0->fragmentShader()->source());
	printf("decode cost [%d] ms\n", int(nb::getTickCount() - k));
	std::map<std::string, SourceDecoder::VarTypeE> uniforms;
	sd.getUniforms(uniforms);

	for(auto const &one : uniforms)
		printf("%s:%d\n", one.first.data(), one.second);
		*/
}
