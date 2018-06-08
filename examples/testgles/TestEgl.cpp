#include "TestEgl.h"
#include "gles/Egl.h"

using nb::gl::egl::Display;
using nb::gl::egl::Configure;
void TestEgl::Test()
{
	Display display = nb::gl::egl::GetCurrentDisplay();

	nb::gl::egl::Initialize(Display::Default());

	Display display1 = nb::gl::egl::GetCurrentDisplay();

	nb::System::String s = nb::gl::egl::GetVersion();
	std::string sVersion = s.ToAscii().GetData();

	int x = Configure::SystemRecommendMaxSupportCount();
	Configure cfg = Configure::FromSystemRecommend(0);

	nb::System::String ss = nb::gl::egl::GetVendor();
	std::string sVendor = ss.ToAscii().GetData();
	
	printf("egl version[ %s ], vendor[ %s ]\r\n", sVersion.data(), sVendor.data());
}