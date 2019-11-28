#include "TestSoureDecoder.h"
#include "gles/SourceDecoder.h"
#include "gles/Program.h"
#include "gles/Shader.h"
#include "gles/Egl.h"
#include <vector>

using namespace nb::gl;

void TestSoureDecoder::test()
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
