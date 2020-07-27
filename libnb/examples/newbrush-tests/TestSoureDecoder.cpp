#include "newbrush/rvl/gles/SourceDecoder.h"
#include "newbrush/rvl/gles/Program.h"
#include "newbrush/rvl/gles/Shader.h"
#include "newbrush/gui/Window.h"
#include <vector>
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test nb::SourceDecoder", "[SourceDecoder]")
{
	Window w;
	
	SourceDecoder sd;
	auto program0 = Programs::phong();

	auto k = nb::getTickCount();
	auto uniforms = sd.decode(program0->vertexShader()->source(), program0->fragmentShader()->source());
	printf("decode cost [%d] ms\n", int(nb::getTickCount() - k));

	for(auto const &one : uniforms)
		printf("%s:%d\n", one.first.data(), one.second);
	
	while (true)
	{

	}
}
