#include "TestEgl.h"
#include "gles/Egl.h"

using namespace nb::gl;
void TestEgl::test()
{
	auto display = nb::gl::getDisplay();

	display = std::make_shared<Display>(Display::defaultx());
	nb::gl::initialize(display);
	auto configure = std::make_shared<Configure>(Configure::fromSystemRecommend(display, 0))/*Configure((int *)NULL)*/;
	nb::gl::setConfigure(configure);

	auto display1 = nb::gl::getDisplay();

	std::string sVersion = nb::gl::getVersion();

	auto x = Configure::systemRecommendMaxSupportCount(display);
	Configure cfg = Configure::fromSystemRecommend(display, 0);

	std::string sVendor = nb::gl::getVendor();
	
	printf("egl version[ %s ], vendor[ %s ]\r\n", sVersion.data(), sVendor.data());
}
