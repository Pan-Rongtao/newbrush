#include "TestEgl.h"
#include "gles/Egl.h"

using namespace nb::gl;
void TestEgl::Test()
{
	Display display = nb::gl::getCurrentDisplay();

	nb::gl::initialize(Display::defaultx());

	Display display1 = nb::gl::getCurrentDisplay();

	std::string sVersion = nb::gl::getVersion();

	int x = Configure::systemRecommendMaxSupportCount();
	Configure cfg = Configure::fromSystemRecommend(0);

	std::string sVendor = nb::gl::getVendor();
	
	printf("egl version[ %s ], vendor[ %s ]\r\n", sVersion.data(), sVendor.data());
}
